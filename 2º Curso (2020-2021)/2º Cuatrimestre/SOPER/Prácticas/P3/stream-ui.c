#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <mqueue.h>
#include <ctype.h>

#define SHM_NAME "/ejemplo"
#define MQ_NAME "/mq_server"
#define MQ_NAME1 "/mq_client"
#define MAX_BUFF 5
#define SEMAPHORES 3
#define MAX_STRING 4

typedef struct {
    int post_pos; //último byte escrito
    int get_pos; //último byte leido
    char buff [MAX_BUFF];
    sem_t sem[SEMAPHORES];  /* 0: mutex, 1: fill, 2: empty */
}Shmejemplo;

typedef struct {
   char mj[MAX_STRING];
} mensaje;

int main(int argc, char *argv[]){ //en argv1 está la entrada y en el otro la sálida
    pid_t pid,pid1;
    int fd_shm, i;
    Shmejemplo * shm_struct;
    char instruccion[MAX_STRING] = "ini";
    mqd_t queue,queue1;

    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 5,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(mensaje)
    };

    
    shm_unlink(SHM_NAME);  /* Desbloquear si se mata el proceso con Ctrl+C */
    
    if(argc < 3){
        perror("Faltan argumentos: archivo de entrada y de salida");
        return -1;
    }

    char *args[]={"./stream-server", argv[1], NULL}; //para ejecutar el server
    char *args1[]={"./stream-client", argv[2], NULL}; //para ejecutar el cliente

    /* Se crea el segmento de memoria*/
    if (( fd_shm = shm_open ( SHM_NAME , O_RDWR | O_CREAT | O_EXCL , S_IRUSR | S_IWUSR )) == -1) {
        perror (" Error al intentar abrir la memoria compartida");
        exit ( EXIT_FAILURE );
    }

    /*Se reacomoda el segmento de memoria */
    if ( ftruncate ( fd_shm , sizeof (Shmejemplo)) == -1) {
        perror (" ftruncate ");
        shm_unlink ( SHM_NAME );
        exit ( EXIT_FAILURE );
    }

    /* Se mapea la memoria para su uso compartido */
    shm_struct = mmap (NULL , sizeof (Shmejemplo), PROT_READ | PROT_WRITE , MAP_SHARED , fd_shm , 0);
    close ( fd_shm );

    if ( shm_struct == MAP_FAILED ) {
        perror (" mmap ");
        shm_unlink ( SHM_NAME );
        exit ( EXIT_FAILURE );
    }

    shm_struct->get_pos = 0;
    shm_struct->post_pos = 0;
    shm_struct->buff[0] = '\0';

    if(sem_init(&(shm_struct->sem[0]), 1, 1)){ //mutex para zona crítica
        perror("Sem_init");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&(shm_struct->sem[1]), 1, 0)){ //huecos llenos para poder sacar
        perror("Sem_init");
        sem_close(&(shm_struct->sem[0]));
        exit(EXIT_FAILURE);
    }
    if(sem_init(&(shm_struct->sem[2]), 1, 5)){ //huecos vacios para poder escribir
        perror("Sem_init");
        sem_close(&(shm_struct->sem[0]));
        sem_close(&(shm_struct->sem[1]));
        exit(EXIT_FAILURE);
    }
    
    queue = mq_open( MQ_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR , &attributes);

    if(queue == (mqd_t)-1){
        fprintf(stderr, "Error al abrir la cola \n");
        sem_close(&(shm_struct->sem[0]));
        
        sem_close(&(shm_struct->sem[1]));
        
        sem_close(&(shm_struct->sem[2]));
        
        return EXIT_FAILURE;
    }
    
    queue1 = mq_open( MQ_NAME1, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR , &attributes);
    if(queue1 == (mqd_t)-1){
        fprintf(stderr, "Error al abrir la cola \n");
        /*liberamos los semáforos*/
        sem_close(&(shm_struct->sem[0]));
        
        sem_close(&(shm_struct->sem[1]));
        
        sem_close(&(shm_struct->sem[2]));
        
        /*liberamos la cola de mensajes anterior*/
        mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 2*/
        mq_close(queue); /*cerramos la cola de mensajes 1*/
        return EXIT_FAILURE;
    }
       /*se hacen los forks*/
    if((pid = fork())==0){ /*primer fork para el server*/
       if (execv (args[0], args)) {
                perror (" Error Streamserver") ;
                shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
                mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
                mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
                mq_close(queue); /*cerramos la cola de mensajes 1*/
                mq_close(queue1); /*cerramos la cola de mensajes 2*/
                munmap(shm_struct, sizeof(Shmejemplo));
                /*liberamos los semáforos*/
                sem_close(&(shm_struct->sem[0]));
                
                sem_close(&(shm_struct->sem[1]));
                
                sem_close(&(shm_struct->sem[2]));
                
                exit ( EXIT_FAILURE ) ;
        }
    }

    if(pid<0){
        perror("Error en el fork1");
        shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
        mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
        mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
        mq_close(queue); /*cerramos la cola de mensajes 1*/
        mq_close(queue1); /*cerramos la cola de mensajes 2*/
        munmap(shm_struct, sizeof(Shmejemplo));
        /*liberamos los semáforos*/
        sem_close(&(shm_struct->sem[0]));
        
        sem_close(&(shm_struct->sem[1]));
        
        sem_close(&(shm_struct->sem[2]));
        
        exit ( EXIT_FAILURE );
    }

    if((pid1 = fork())==0){ /*segundo fork para el server*/
        if(execv (args1[0], args1)){
            perror (" Error Streamclient ");
            shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
            mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
            mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
            mq_close(queue); /*cerramos la cola de mensajes 1*/
            mq_close(queue1); /*cerramos la cola de mensajes 2*/
            munmap(shm_struct, sizeof(Shmejemplo));
            mq_send(queue, instruccion, sizeof(instruccion), 1);
            /*liberamos los semáforos*/
            sem_close(&(shm_struct->sem[0]));
            
            sem_close(&(shm_struct->sem[1]));
            
            sem_close(&(shm_struct->sem[2]));
            
            exit ( EXIT_FAILURE ) ;
        }
    }

    if(pid1<0){
        if(mq_send(queue, "exit", sizeof(instruccion), 1)==-1){ /*le ordenamos que finalize al proceso que se abrió exitosamente*/
            perror("Send_exit pid1 error");
        }
        shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
        mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
        mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
        mq_close(queue); /*cerramos la cola de mensajes 1*/
        mq_close(queue1); /*cerramos la cola de mensajes 2*/
        munmap(shm_struct, sizeof(Shmejemplo)); 
        perror("Error en el fork1");
        /*liberamos los semáforos*/
        sem_close(&(shm_struct->sem[0]));
        
        sem_close(&(shm_struct->sem[1]));
        
        sem_close(&(shm_struct->sem[2]));
        
        exit( EXIT_FAILURE );
    }

    while(1){
        fscanf(stdin, "%s", instruccion);
        
        for(i = 0; i < strlen(instruccion); i++)
            instruccion[i] = tolower(instruccion[i]);

        if(strcmp(instruccion, "post") == 0){
            if(mq_send(queue, instruccion, sizeof(instruccion), 1) == -1){
                perror("Error al enviar la instruccion");
                shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
                mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
                mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
                mq_close(queue); 
                mq_close(queue1);
                munmap(shm_struct, sizeof(Shmejemplo));
                /*liberamos los semáforos*/
                sem_close(&(shm_struct->sem[0]));
                
                sem_close(&(shm_struct->sem[1]));
                
                sem_close(&(shm_struct->sem[2]));
                
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(instruccion, "get") == 0){
            if(mq_send(queue1, instruccion, sizeof(instruccion), 1) == -1){
                perror("Error al enviar la instruccion");
                shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
                mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
                mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
                mq_close(queue); 
                mq_close(queue1);
                munmap(shm_struct, sizeof(Shmejemplo));
                /*liberamos los semáforos*/
                sem_close(&(shm_struct->sem[0]));
                
                sem_close(&(shm_struct->sem[1]));
                
                sem_close(&(shm_struct->sem[2]));
                
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(instruccion, "exit") == 0){
            if(mq_send(queue1, instruccion, sizeof(instruccion), 1) == -1){
                perror("Error al enviar la instruccion");
                shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
                mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
                mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
                mq_close(queue); 
                mq_close(queue1);
                munmap(shm_struct, sizeof(Shmejemplo));
                /*liberamos los semáforos*/
                sem_close(&(shm_struct->sem[0]));
                sem_close(&(shm_struct->sem[1]));
                sem_close(&(shm_struct->sem[2])); 
                exit(EXIT_FAILURE);
            }
            if(mq_send(queue, instruccion, sizeof(instruccion), 1) == -1){
                perror("Error al enviar la instruccion");
                shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
                mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
                mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
                mq_close(queue); 
                mq_close(queue1);
                munmap(shm_struct, sizeof(Shmejemplo));
                /*liberamos los semáforos*/
                sem_close(&(shm_struct->sem[0]));
                
                sem_close(&(shm_struct->sem[1]));
                
                sem_close(&(shm_struct->sem[2]));
                
                exit(EXIT_FAILURE);
            }
            shm_unlink (SHM_NAME); /*unlink de memoria compartida*/
            mq_unlink(MQ_NAME); /*unlink de la cola de mensajes 1*/
            mq_unlink(MQ_NAME1); /*unlink de la cola de mensajes 2*/
            mq_close(queue); 
            mq_close(queue1);
            munmap(shm_struct, sizeof(Shmejemplo));
            /*liberamos los semáforos*/
            sem_close(&(shm_struct->sem[0]));
            sem_close(&(shm_struct->sem[1]));
            sem_close(&(shm_struct->sem[2]));
            wait(NULL);
            wait(NULL);
            exit (EXIT_SUCCESS) ;
        }
        else
            fprintf(stdout, "\nInstruccion incorrecta\n");
    }
}