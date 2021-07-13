#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <string.h>
#include <time.h>

#define SHM_NAME "/ejemplo"
#define MQ_NAME "/mq_server"
#define MAX_BUFF 5
#define SEMAPHORES 3
#define MAX_STRING 4

typedef struct {
    int post_pos;
    int get_pos;
    char buff[MAX_BUFF];
    sem_t sem[SEMAPHORES]; /* 0: mutex, 1: fill, 2: empty */
}Shmejemplo;



int main (int argc, char **argv){
    struct msqid_ds *buf;
    struct timespec ts;
    mqd_t queue;
    FILE *f;
    Shmejemplo *shm_struct;
    int fd_shm;
    char character, instruccion[MAX_STRING];
    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 5,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(MAX_STRING)
    };

    queue = mq_open( MQ_NAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR , &attributes);
    if(queue == (mqd_t)-1){
        fprintf(stderr, "Error al abrir la cola \n");
        return EXIT_FAILURE;
    }

    if(argc < 2){
        perror("Faltan argumentos\n");
        mq_close(queue);
        exit ( EXIT_FAILURE );
    }else if((f = fopen(argv[1], "r")) == NULL){
        perror("Error al intentar abrir el archivo de lectura\n");
        mq_close(queue);
        exit ( EXIT_FAILURE );
    }

     /* Se abre el segmento de memoria*/
    if (( fd_shm = shm_open ( SHM_NAME , O_RDWR, S_IRUSR | S_IWUSR )) == -1) {
        perror (" Error al intentar abrir la memoria compartida");
        mq_close(queue);
        fclose(f);
        exit ( EXIT_FAILURE );
    }

    /* Se mapea la memoria para su uso compartido */
    shm_struct = mmap (NULL , sizeof (Shmejemplo), PROT_READ | PROT_WRITE , MAP_SHARED , fd_shm , 0);
    close ( fd_shm );
    
    if (shm_struct == MAP_FAILED) {
        perror (" mmap ");
        fclose(f);
        shm_unlink (SHM_NAME);
        mq_close(queue);
        exit ( EXIT_FAILURE );
    }

    while(1){
         if(mq_receive(queue, instruccion, sizeof(instruccion), NULL) == -1){
            perror("Error recibiendo el mensaje en server");
            fclose(f);
            shm_unlink ( SHM_NAME );
            mq_close(queue);
            munmap(shm_struct, sizeof(Shmejemplo));
            exit( EXIT_FAILURE );
        }
        if(strcmp(instruccion, "exit")==0){
            munmap(shm_struct, sizeof(Shmejemplo));
            fclose(f);
            mq_close(queue);
            exit ( EXIT_SUCCESS );
        }
        if (clock_gettime(CLOCK_REALTIME, &ts) == -1) /*configuras los 2 segundos de tiempo*/
            {   
                perror("clock");
                fclose(f);
                shm_unlink ( SHM_NAME );
                mq_close(queue);
                munmap(shm_struct, sizeof(Shmejemplo));
                exit(EXIT_FAILURE);
            }
            ts.tv_sec+=2; //2 segundos
            if(sem_timedwait(&(shm_struct->sem[2]), &ts)==-1){ //espera 2 segundos a que haya huceo para rellenarlo
                fprintf(stdout, "Tiempo pasado, operación post desechada\n"); /*si han pasado los dos segundos, operacion desechada*/
                continue;
            }
        /* 0: mutex, 1: fill, 2: empty */
        sem_wait(&(shm_struct->sem[0])); /*espera permiso para entrar en el mutex*/

        /* Leemos caracter a caracter del archivo y lo introducimos en el buffer */
        /* de forma circular hasta el final del archivo */
        if(fscanf(f, "%c", &character) != EOF){
            shm_struct->buff[(shm_struct->post_pos)] = character;
            shm_struct->post_pos = (shm_struct->post_pos+1) % MAX_BUFF;
        }
        else
            shm_struct->buff[(shm_struct->post_pos)] = '\0';

        sem_post(&(shm_struct->sem[0]));
        sem_post(&(shm_struct->sem[1]));   
    }

}
