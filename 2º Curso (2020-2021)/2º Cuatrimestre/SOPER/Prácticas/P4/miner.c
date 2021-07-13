#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <mqueue.h>
#include <sys/stat.h>
#include "miner.h"

#define PRIME 99997669
#define BIG_X 435679812
#define BIG_Y 100001819



/*
1. Registrar minero en la red.
2. Preparar y lanzar ronda de minado.
3. Minar.
4. Comunicar ganador y actualizar la cadena de bloques.
5. Lanzar nueva ronda de minado.
*/

/*
    Estructura dedicada a los trabajadores
*/
typedef struct {
    long int target;
    pid_t id;
    sem_t hilos;
    int solucion_encontrada;
    long int solucion;
    int is_valid;
} Pthread_struct;

Pthread_struct *ps = NULL;
NetData *netdata = NULL;
Block *block = NULL, *propio = NULL;
long int num_rounds;
long int num_workers;
pthread_t *workers = NULL;
long int sol;
int miPos;

/*worker*/
void *trabajador(void *s){
    long int miSol;
    while(sol < PRIME) { 
        if(ps->solucion_encontrada){ /*si solución encontrada*/
            sem_wait(&ps->hilos); /*se paran y esperan a que el proceso padre los reactive*/
            sem_post(&ps->hilos); /*esperan a reactivarse y le envian a otro que este esperando que se active y así todo el roto*/
            if(ps->is_valid){
                pthread_exit(NULL);
            }
        }
        
        miSol = sol++;
        fprintf(stdout, "Searching... %6.2f%%\r", 100.0 * miSol / PRIME);
        if (ps->target == simple_hash(miSol) && !ps->is_valid) { //si encuentra la solución
            fprintf(stdout, "\nSolution: %ld\n", miSol);
            ps->solucion_encontrada = 1;
            ps->solucion = miSol; //pone el valor de la solución
            kill(ps->id, SIGCHLD); //comunica al padre que ha encontrado una solución
        }
    }
    fprintf(stderr, "\nSearch failed\n");
    exit(EXIT_FAILURE);
}

/* Dicha ronda se iniciará de forma sincrónica, es decir, todos los procesos recibirán una notificación de inicio “al mismo tiempo”.*/
/* La comunicación de ganador se realizará enviando una señal SIGUSR2 al resto de mineros.
Por tanto, recibir una señal SIGUSR2 implica que el minero se considere perdedor en esa ronda de minado.*/
long int simple_hash(long int number) {
    long int result = (number * BIG_X + BIG_Y) % PRIME;
    return result;
}

void print_blocks(Block *plast_block, int num_wallets) {
    Block *block = NULL;
    int i, j;
    char name[20];
    FILE * f;
    
    sprintf(name, "%d", getpid());
    strcat(name, ".txt");
    f = fopen(name, "w");

    for(i = 0, block = plast_block; block != NULL; block = block->prev, i++) {
        fprintf(f, "Block number: %d; Target: %ld; Solution: %ld\n", block->id, block->target, block->solution);
        for(j = 0; j < num_wallets; j++) {
            if(netdata->miners_pid[j] != -1)
                fprintf(f, "%d: %d coins; ", netdata->miners_pid[j], block->wallets[j]);
        }
        fprintf(f, "\n\n\n");
    }
    fprintf(f, "A total of %d blocks were printed\n", i);

    fclose(f);    
}

/*manejador del minero cuando un trabajador tiene una posible solución encontrada manejador sigchild*/
void manejador_ganador (int sig){ //, Pthread_struct *ps, Block *block, NetData *netdata
    int i, votos = 0, fd_shm;
    Block *new, *newPropio;

    printf("Ganador - Cierro la seccion critica\n");
    if(netdata->total_miners > 1){
        while(1){printf("Ganador - Bajo el semaforo mutex\n");
            sem_wait(&(block->winner));    /*baja el semáforo de ganador*/
            printf("Ganador - He pasado del semaforo\n");
            if(block->mutex == 1){      //metodo para evadir la posibilidad de interrupciones
                block->mutex = 0;
                break;                  //y su posterior salto de comando
            }
            if(ps->is_valid){
                printf("Ganador - Realmente perdi\n");
                return;
            }
        }
    }
    printf("Ganador - Preparo el recuento de activos\n");
    block->quorum = 1; /*sémaforo de espera activa*/
    if(netdata->last_winner == -1){
        netdata->last_winner = getpid();
    }
    printf("Ganador - Envio la señal al antiguo ganador\n");
    kill(netdata->last_winner, SIGCONT); /*envia un sigcont al ganador de la ronda anterior (el que actua como monitor*/
    printf("Ganador - Espero al antiguo ganador\n");
    while(block->quorum); /*bloque de espera activa hasta actualizar la lista de mineros activos*/
    block->quorum = 1; /*para que el resto de mineros después de votar esperen*/
    printf("Ganador - Preparo los votos: %d\n", netdata->total_miners);
    block->solution = ps->solucion; /*actualiza la solución*/
    for(i=0; i<netdata->total_miners; i++){ /*bucle por todos los mineros activos para comprobar su voto*/
        netdata->voting_pool[i] = '-'; //se inicializa a un valor diferente a ok o no ok :-)
        if(ps->id != netdata->miners_pid[i]){ /*comprobación de que no se auto envie*/
            printf("Ganador - Envio señal al perdedor\n");
            kill(netdata->miners_pid[i],SIGUSR2);   
        }
        else   
            miPos = i;
    }
    printf("Ganador - Espero a que voten\n");
    /* espera a la votacion */
    for(i=0; i!=netdata->total_miners; i++){
        if(netdata->miners_pid[i] != ps->id){
            sem_post(&(block->vote[i]));
            sem_wait(&(block->semMutex));
        }
    }
    printf("Ganador - Cuento los votos\n");
    /* cuenta los votos */
    for(i=0; i<netdata->total_miners; i++){
        if(netdata->voting_pool[i] == '1') 
            votos++;
    }
    printf("Ganador - Compruebo los votos\n");
    /* si los votos superan el 50%, prepara el nuevo bloque */
    if(netdata->total_miners/2 <= votos){ //si la solucion es aceptada como válida
        printf("Ganador - Hay mayoria. Mato a mis hilos\n");
        block->is_valid = 1;    // marca que ha sido valido
        ps->is_valid = 1;
        sem_post(&(ps->hilos));
        block->wallets[miPos]++;
        printf("Ganador - Doy paso a los perdedores\n");
        block->quorum = 0;      // da paso a los demas mineros para que lo comprueben
        printf("Ganador - Espero a que los perdedores generen los nuevos bloques\n");
        for(i = 0; i < netdata->total_miners; i++) 
            if(i != miPos){
                sem_post(&(block->vote[i]));   // espera a que todos los mineros creen el nuevo bloque propio
                sem_wait(&(block->semMutex));
            }
        printf("Ganador - Genero mi nuevo bloque\n");
        for(i= 0; i<MAX_MINERS; i++)
            propio->wallets[i] = block->wallets[i];
        propio->target = block->target;
        propio->solution = block->solution;
        propio->id = block->id;
        propio->is_valid = block->is_valid;
        if(num_rounds>0){
            newPropio = (Block *)malloc(sizeof(Block));   // Crea el nuevo bloque para enlazarlo
            if(new == NULL){
                return;
            }
            propio->next = newPropio;
            newPropio->prev = propio;
            propio = newPropio;
        }
        printf("Ganador - Genero el nuevo bloque compartido\n");
        munmap(block, sizeof(Block));
        if((fd_shm = shm_open(SHM_NAME_BLOCK, O_RDWR, 0)) == -1)
            return;
        new  = mmap(NULL, sizeof(Block), PROT_READ | PROT_WRITE , MAP_SHARED , fd_shm , 0);
        close (fd_shm); 
        if (block == MAP_FAILED) {
            return;
        }    
        for(i=0; i<MAX_MINERS; i++){
            new->wallets[i] = block->wallets[i];
            new->vote[i] = block->vote[i];
        }
        new->target = block->solution;
        new->id = block->id+1;
        new->target = simple_hash((block->id+1)*500000);
        new->is_valid = 0;
        new->mutex = block->mutex;
        new->winner = block->winner;
        new->quorum = block->quorum;
        new->semMutex = block->semMutex;
        block->next = new;
        new->prev = block;
        block = new;
        netdata->last_winner = getpid();
        printf("Ganador - Despierto a los perdedores\n");
        for(i=0; i< netdata->total_miners; i++) // Una vez creado el bloque, reactiva a los perdedores
            if(i != miPos)
                sem_post(&(block->vote[i]));   
        sem_post(&(block->winner));
    }
    else{
        printf("Ganador - No era la solucion\n");
        block->is_valid = 0;    // marca que no ha sido valido
        block->quorum = 0;      // permite que los demas mineros lo comprueben 
        ps->solucion_encontrada = 0;    // y reactiva a sus trabajadores
        sem_post(&(ps->hilos));
    }
    printf("Ganador - Salgo de la zona critica\n");
    block->mutex = 1;       // sale de la zona critica
}

/*manejador de SIGUSR2 :-)*/
void manejador_perdedor(int sig){ 
    int i;
    Block *new;
    printf("Perdedor: Paro a mis trabajadores\n");
    ps->solucion_encontrada = 1; /*como el anterior, para que se metan en el if y esperen*/
    printf("Perdedor: Realizo la votacion\n");
    for(i=0; i<netdata->total_miners; i++){ /*votación, viva la democracia*/
        if(netdata->miners_pid[i] == ps->id){ /*busca su sitio de votacion*/
            miPos = i;
            sem_wait(&(block->vote[miPos]));
            if(block->target == simple_hash(block->solution)){
                printf("Perdedor: Voto positivo\n");
                netdata->voting_pool[miPos] = '1'; //solución correcta todo gucci
            }
            else {
                printf("Perdedor: Voto negativo\n");
                netdata->voting_pool[miPos] = '0'; //solucion incorrecta estafador
            }
            printf("Perdedor: He votado, se lo indico al ganador\n");
            /*subir semáforo de votación */
            sem_post(&(block->semMutex));
            break;
        }
    }

    printf("Perdedor: Espero a que el ganador cuente los votos\n");
    while(block->quorum); //espera activa a que el posible ganador cuente los votos
    
    printf("Perdedor: Compruebo si es valido\n");
    if(block->is_valid == 1){ // Si la solucion era valida, prepara nueva ronda
        sem_post(&(block->vote[miPos])); //Espera a que el ganador le de permiso para crear el nuevo bloque
        printf("Perdedor: Ha sido valido. Genero mi bloque nuevo\n");
        for(i=0; i<MAX_MINERS; i++)
            propio->wallets[i] = block->wallets[i];
        propio->target = block->target;
        propio->solution = block->solution;
        propio->id = block->id;
        propio->is_valid = block->is_valid;
        if(num_rounds>0){
            new = (Block *)malloc(sizeof(Block));   // Crea el nuevo bloque para enlazarlo
            if(new == NULL){
                return;
            }
            propio->next = new;
            new->prev = propio;
            propio = new;
        }printf("Perdedor: Indico que ya prepare mi bloque nuevo al ganador\n");
        sem_post(&(block->semMutex));   // Indica que ya ha preparado su nuevo bloque
        printf("Perdedor: Espero a que el ganador prepare el nuevo bloque compartido\n");
        sem_wait(&(block->vote[miPos]));   // Espera a que el ganador prepare el nuevo bloque
        printf("Perdedor: Despierto a mis trabajdores para finalizar\n");
        ps->is_valid = 1;
        sem_post(&(ps->hilos));
    }
    else{   // si no era valido, reactiva a sus trabajadores
        printf("Perdedor: No ha sido valido, reanudo a mis trabajadores\n");
        ps->solucion_encontrada = 0;
        sem_post(&(ps->hilos));
    }
}

void manejador_activo(int sig){
    return;
}

/*manejador para el ultimo proceso ganador (monitor)
  manda SIGUSR1 a todos los mineros para ver quienes están activos
  va sumando el número de mineros activos y guardando la lista de mineros activos
  */
void manejador_antiguo_ganador(int sig){
    pid_t activos[MAX_MINERS];
    int i, r, coins[MAX_MINERS];
    sem_t semaforos[MAX_MINERS];

    netdata->total_miners = 0; 
    for(i = 0; i<MAX_MINERS; i++){
        if(netdata->miners_pid[i] != -1){
            if(getpid() != netdata->miners_pid[i]){
                r = kill(netdata->miners_pid[i], SIGUSR1);
                if(r == 0){
                    activos[netdata->total_miners] = netdata->miners_pid[i];
                    coins[netdata->total_miners] = block->wallets[i]; printf("Minero: %d tiene %d monedas\n", netdata->miners_pid[i], block->wallets[i]);
                    semaforos[netdata->total_miners] = block->vote[i];  
                    netdata->total_miners++;
                }
            }
            else miPos = i;
        }
    }
    activos[netdata->total_miners] = getpid();
    coins[netdata->total_miners] = block->wallets[miPos];
    semaforos[netdata->total_miners] = block->vote[miPos];
    netdata->last_miner = netdata->total_miners;
    netdata->total_miners++;
    
    for(i = 0; i < netdata->total_miners; i++){
        netdata->miners_pid[i] = activos[i];
        block->wallets[i] = coins[i];
        block->vote[i] = semaforos[i];
    }
    for(i = netdata->total_miners; i<MAX_MINERS; i++){
        netdata->miners_pid[i] = -1;
        block->wallets[i] = 0;
        sem_destroy(&(block->vote[i]));
        sem_init(&(block->vote[i]), 1, 0);
    }

    for(i=0; i<netdata->total_miners; i++){
        printf("Minero %d: %d\n", i, netdata->miners_pid[i]);
    }

    block->quorum = 0; //ya he terminado de hacer las comprobaciones de procesos activos, el resto de procesos terminan la espera activa
}

// repasarlo 
void manejador_acabar(int sig){

    print_blocks(propio, MAX_MINERS);

    ps->is_valid = 1;
    sem_post(&(ps->hilos));

    for(int i = MAX_MINERS-1; i >= 0; i--){
        if(netdata->miners_pid[i] != getpid()){
             netdata->last_miner = netdata->miners_pid[i];
         }
    }
    if(netdata->last_winner == getpid()){
        netdata->last_winner = -1;
    }

    for(int i = 0; i < MAX_MINERS; i++){
        if(netdata->miners_pid[i] == getpid()){
            netdata->miners_pid[i] = -1;
            netdata->total_miners--;
            netdata->voting_pool[i] = '-';   
        }
    } 
    
    free(workers);
    sem_destroy(&(ps->hilos));
    free(ps);
    free(propio);
    munmap(block, sizeof(Block));
    if(netdata->total_miners == 0){
        for(int i=0; i<MAX_MINERS; i++){
            sem_destroy(&(block->vote[i]));
        }
        sem_destroy(&(block->winner));
        sem_destroy(&(block->semMutex));
        munmap(netdata, sizeof(NetData));
        shm_unlink (SHM_NAME_NET);
        shm_unlink ( SHM_NAME_BLOCK );
    }
    else
        munmap(netdata, sizeof(NetData));

    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]) { 

    long int i;
    int fd_shm, fd_shm1;
    char first = 'f';
    char semaforo[10];
    semaforo[0] = '\0';

    // Descomentar en caso de salida con CTRL+C
    
    /*
    shm_unlink(SHM_NAME_BLOCK);
    shm_unlink(SHM_NAME_NET);
    exit(EXIT_SUCCESS);
    */

    struct sigaction act;
    struct sigaction act1;
    struct sigaction act2;
    struct sigaction act3;
    struct sigaction act4;
     
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGCHLD);
    
    act.sa_handler = manejador_ganador;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    act1.sa_handler = manejador_perdedor;
    sigemptyset(&(act1.sa_mask));
    act1.sa_mask = set;
    act1.sa_flags = 0;

    act2.sa_handler = manejador_antiguo_ganador;
    sigemptyset(&(act2.sa_mask));
    act2.sa_flags = 0;

    act3.sa_handler = manejador_activo;
    sigemptyset(&(act3.sa_mask));
    act3.sa_flags = 0;

    act4.sa_handler = manejador_acabar;
    sigfillset(&(act4.sa_mask));
    act4.sa_flags = 0;

    if (sigaction (SIGCHLD, &act, NULL) < 0){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
    if (sigaction (SIGUSR2, &act1, NULL) < 0){
        perror("sigaction1");
        exit(EXIT_FAILURE);
    }

    if (sigaction (SIGCONT, &act2, NULL) < 0){
        perror("sigaction2");
        exit(EXIT_FAILURE);
    }

    if (sigaction (SIGUSR1, &act3, NULL) < 0){
        perror("sigaction2");
        exit(EXIT_FAILURE);
    }

    if (sigaction (SIGINT, &act4, NULL) < 0){
        perror("sigaction2");
        exit(EXIT_FAILURE);
    }
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <NUM_WORKERS> <Num_Rounds>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /*guardamos el nº de trabajores*/
    num_workers = atol(argv[1]); /*string to long conversion*/
    
    /*guardamos el numero de rondas*/
    num_rounds = atol(argv[2]); /*string to long conversion*/
    
    /* Crear o abrir el segmento de memoria compartida para el bloque */
    if (( fd_shm = shm_open ( SHM_NAME_BLOCK , O_RDWR | O_CREAT | O_EXCL , S_IRUSR | S_IWUSR )) == -1) {
        if ( errno == EEXIST ) { //si existe 
            fd_shm = shm_open ( SHM_NAME_BLOCK , O_RDWR , 0); //prueba a abrirla
                if ( fd_shm == -1) { //si existe un error 
                    perror (" Error opening the shared memory segment 1");
                    exit (EXIT_FAILURE);    
                } 
        }else{
            perror (" Error creating the shared memory segment 1");
            exit ( EXIT_FAILURE );
        }  
    } else{ //si la abre sin error es que es el primero
        if ( ftruncate ( fd_shm , sizeof ( Block )) == -1) {
            perror (" ftruncate ");
            shm_unlink ( SHM_NAME_BLOCK );
            exit ( EXIT_FAILURE );
        }
        first = 't';
    }

    block = mmap(NULL, sizeof(Block), PROT_READ | PROT_WRITE , MAP_SHARED , fd_shm , 0);
    close (fd_shm); 
    if (block == MAP_FAILED) {
        perror (" mmap ");
        shm_unlink ( SHM_NAME_BLOCK );
        exit ( EXIT_FAILURE );
    }
    
    if (( fd_shm1 = shm_open ( SHM_NAME_NET , O_RDWR | O_CREAT | O_EXCL , S_IRUSR | S_IWUSR )) == -1) {
        if ( errno == EEXIST ) { //si existe 
            fd_shm1 = shm_open ( SHM_NAME_NET , O_RDWR , 0); //prueba a abrirla
                if ( fd_shm1 == -1) { //si existe un error 
                    perror (" Error opening the shared memory segment 2");
                    close(fd_shm1);
                    exit (EXIT_FAILURE);    
                } 
        }else{
            perror (" Error creating the shared memory segment 2 \n");
            exit ( EXIT_FAILURE );
        }  
    }
        
    if ( first == 't' && (ftruncate ( fd_shm1 , sizeof ( NetData )) == -1)) {
        perror (" ftruncate ");
        shm_unlink ( SHM_NAME_NET );
        exit ( EXIT_FAILURE );
    }
    
    netdata = mmap(NULL, sizeof(NetData), PROT_READ | PROT_WRITE , MAP_SHARED , fd_shm1 , 0);
    close (fd_shm1); 
    if (netdata == MAP_FAILED || netdata==NULL) {
        perror (" mmap ");
        munmap(block, sizeof(Block));
        shm_unlink ( SHM_NAME_BLOCK );
        shm_unlink ( SHM_NAME_NET);
        exit ( EXIT_FAILURE );
    }

    if(first == 't'){
        if (sem_init(&(block->winner),1,1) == -1){
            perror (" sem_init: winner");
            munmap(netdata, sizeof(NetData));
            munmap(block, sizeof(Block));
            shm_unlink ( SHM_NAME_BLOCK );
            shm_unlink ( SHM_NAME_NET);
            exit ( EXIT_FAILURE );
        }

        if (sem_init(&(block->semMutex),1,0) == -1){
            perror (" sem_init:semMutex");
            munmap(netdata, sizeof(NetData));
            munmap(block, sizeof(Block));
            shm_unlink ( SHM_NAME_BLOCK );
            shm_unlink ( SHM_NAME_NET);
            exit ( EXIT_FAILURE );
        }
        
        for(i = 0; i < MAX_MINERS; i++){
            if(sem_init(&(block->vote[i]),1,0) == -1){
                perror("sem_init: vote");
                sem_destroy(&(block->semMutex));
                sem_destroy(&(block->winner));
                munmap(netdata, sizeof(NetData));
                munmap(block, sizeof(Block));
                shm_unlink ( SHM_NAME_BLOCK );
                shm_unlink ( SHM_NAME_NET);
                exit ( EXIT_FAILURE );
            }
        }
    }  
    
    propio = (Block *)calloc(1, sizeof(Block));
    if(propio == NULL){
        sem_unlink(SEM_NAME);
        munmap(netdata, sizeof(NetData));
        munmap(block, sizeof(Block));
        shm_unlink ( SHM_NAME_BLOCK );
        shm_unlink ( SHM_NAME_NET);
        exit ( EXIT_FAILURE );
    }

    if((ps = (Pthread_struct *)calloc(1, sizeof(Pthread_struct))) == NULL){
        free(propio);
        sem_unlink(SEM_NAME);
        munmap(netdata, sizeof(NetData));
        munmap(block, sizeof(Block));
        shm_unlink ( SHM_NAME_BLOCK );
        shm_unlink ( SHM_NAME_NET);
        exit ( EXIT_FAILURE );
    }

    if(first == 't'){ //si es el primero
        //inicializar block
        for(int i; i<MAX_MINERS; i++){
            block->wallets [i]= 0;    
        }
        block->target = rand() % PRIME;  //número del que se quiere encontrar solución
        block->target = simple_hash(500000);  //número del que se quiere encontrar solución
        block->solution = -1; //operando que da solución al target
        block->id = 0;
        block->is_valid = -1;
        block->next = NULL;
        block->prev = NULL; //puede no utilizarse
        block->quorum = 0;
        block->mutex = 1;

        netdata->monitor_pid = 0; //pid del monitor, se empleará uno
        netdata->total_miners= 1; //número total de mineros
        netdata->last_winner = -1; //ultimo minero ganador
        netdata->last_miner=0; //posición en la tabla del último minero activo
        for(i=0; i<MAX_MINERS; i++)
            netdata->miners_pid[i] = -1;
        netdata->miners_pid[0] = getpid();
        miPos = 0;
    }
    else{
        if(netdata->total_miners == MAX_MINERS){
            perror (" Maximo de mineros alcanzado. No se puede entrar ");
            free(propio);
            munmap(netdata, sizeof(NetData));
            munmap(block, sizeof(Block));
            shm_unlink ( SHM_NAME_BLOCK );
            shm_unlink ( SHM_NAME_NET );
            exit ( EXIT_FAILURE );
        }
        for(i = 0; i<MAX_MINERS; i++){
            if(netdata->miners_pid[i] == -1){
                miPos = i;
                netdata->miners_pid[i] = getpid();
                netdata->voting_pool[i] = '-';
                if(i == netdata->last_miner + 1)
                    netdata->last_miner++;
                break;
            }
        }
        netdata->total_miners++;
    }
    
    while(num_rounds--){

        for(i=0; i<netdata->total_miners; i++)
            printf("Minero %ld: %d\n", i, netdata->miners_pid[i]);

        printf("%d - rondas restantes: %ld\n", getpid(), num_rounds);
        if((workers = (pthread_t *)calloc(num_workers,sizeof(workers[0])))==NULL){ //creas el array de hilos    
            free(ps);
            free(propio);
            munmap(netdata, sizeof(NetData));
            munmap(block, sizeof(Block));
            shm_unlink ( SHM_NAME_BLOCK );
            shm_unlink ( SHM_NAME_NET);
            exit(EXIT_FAILURE);
        }


        printf("Target del siguiente bloque: %ld\n", block->target);

        ps->id = getpid();
        ps->is_valid = 0;
        ps->target = block->target;
        ps->solucion = -1;
        ps->solucion_encontrada = 0;
        if(sem_init(&(ps->hilos), 0, 0) == -1){
            free(ps);
            free(propio);
            munmap(netdata, sizeof(NetData));
            munmap(block, sizeof(Block));
            shm_unlink ( SHM_NAME_BLOCK );
            shm_unlink ( SHM_NAME_NET);
            exit(EXIT_FAILURE);
        }

        sol = 0;
        for(i=0; i<num_workers; i++){ 
            pthread_create(&workers[i], NULL, trabajador, ps); //pones a los trabajadores
        }

        for(i=0; i<num_workers; i++){
            if(workers[i])
                pthread_join(workers[i], NULL);
        }

        free(workers);
    }

    print_blocks(propio, MAX_MINERS);

    for(int i = MAX_MINERS-1; i >= 0; i--){
        if(netdata->miners_pid[i] != getpid()){
             netdata->last_miner = netdata->miners_pid[i];
         }
    }
    if(netdata->last_winner == getpid()){
        netdata->last_winner = -1;
    }

    for(int i = 0; i < MAX_MINERS; i++){
        if(netdata->miners_pid[i] == getpid()){
            netdata->miners_pid[i] = -1;
            netdata->total_miners--;
            netdata->voting_pool[i] = '-';   
        }
    }

    sem_destroy(&(ps->hilos));
    free(ps);
    free(propio);
    munmap(block, sizeof(Block));
    if(netdata->total_miners == 0){
        for(int i=0; i<MAX_MINERS; i++){
            sem_destroy(&(block->vote[i]));
        }
        sem_destroy(&(block->winner));
        sem_destroy(&(block->semMutex));
        munmap(netdata, sizeof(NetData));
        shm_unlink (SHM_NAME_NET);
        shm_unlink ( SHM_NAME_BLOCK );
    }
    else
        munmap(netdata, sizeof(NetData));

    exit(EXIT_SUCCESS);
}
