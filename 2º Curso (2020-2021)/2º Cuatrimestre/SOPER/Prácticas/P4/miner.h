#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define OK 0
#define MAX_MINERS 10
#define MAX_String 500
#define SHM_NAME_NET "/netdata"
#define SHM_NAME_BLOCK "/block "
#define SEM_NAME "/sem_winner "
#define SEM_HILOS "/sem_hilos"
#define MQ_NAME "/monitor"
/**
 *  En caso de que la solucion sea correcta, debera actualizar su cadena de bloques creando
 *  un nuevo bloque con la informaci´on compartida por el ganador en memoria compartida, en el
 *  segmento de nombre SHM_NAME_BLOCK:
*/
typedef struct _Block {
    int wallets [MAX_MINERS]; //registro de monedas conseguidas por cada mineto
    long int target; //número del que se quiere encontrar solución
    long int solution; //operando que da solución al target
    int id; //identificador de bloque
    int is_valid; //si considera como válida la respuesta
    struct _Block * next ; //puede no utilizarse
    struct _Block * prev ; //puede no utilizarse
    sem_t winner; //semaforo para usar al escribir la solucion del POW en memoria compartida
    int quorum;
    sem_t vote[MAX_MINERS];
    int mutex;
    sem_t semMutex;
}Block ;

typedef struct _NetData{
    pid_t miners_pid [MAX_MINERS]; //tabla con los identificadores de proceso de los mineros
    char voting_pool [MAX_MINERS]; //votos de cada minero
    int last_miner; //posición en la tabla del último minero activo
    int total_miners; //número total de mineros
    pid_t monitor_pid; //pid del monitor, se empleará uno
    pid_t last_winner; //ultimo minero ganador
}NetData;

long int simple_hash(long int number);

void print_blocks(Block * plast_block, int num_wallets);