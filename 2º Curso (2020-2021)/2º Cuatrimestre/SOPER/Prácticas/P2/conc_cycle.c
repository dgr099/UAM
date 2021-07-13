#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#define TIME 10
int s;
int pid = 0;
int num_proc;
int t=0;

void liberar(int num){
    while(num>=0){
        char name[12];
        sprintf(name, "%d", num);
        sem_unlink(name);
        num--;
    }
}

int toString(char *str)
{
    int num = 0;
    int i;
    for (i = 0; str[i]; i++)
    {
        num = num * 10 + str[i] - '0';
    }
    return num;
}

void manejador_2(int signo)
{
    liberar(num_proc); //libero los semáforos
    kill(pid, SIGTERM); //le manda sigterm a su hijo
    //Imprimir mensaje para debug
    if(signo==SIGALRM)
        printf("Alarma de tiempo %d\t%d\n", getpid(), pid);
        else{
            printf("SIGINT %d\t%d\n", getpid(), pid);
        }
        s=4;
        wait(NULL);
        exit(EXIT_SUCCESS);    
    return;
}

void manejador(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("Señal SIGUSR1 recibida proc:%d\n", getpid());
        s = 1;
        return;
    }
    //en otro caso es sig term
    kill(pid, SIGTERM); //le mando la señal al hijo
    s = 2; //esto realmente es para debugear más que otra cosa
    wait(NULL);
    exit(EXIT_SUCCESS); 
}

int main(int argc, char **argv)
{
    struct sigaction act;
    sigset_t test;
    int f_pid = getpid();
    if (argc < 2)
    {
        printf("Error falta pasar el número de procesos prueba ./conc_cycle numero_de_procesos\n");
        return 1;
    }

    /*conf el manejador para SIGUSR1 y SIGTERM*/
    act.sa_handler = manejador;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(SIGUSR1, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGTERM, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    /*conf el manejador para SIGUSR1 y SIGTERM*/

    /*leyendo el número de procesos a lanzar*/
    num_proc = toString(argv[1]) - 1; //hay que hacer procesos-1 forks

    /*debug*/
    //liberar(num_proc+1);
    //return 0;
    /*leyendo el número de procesos a lanzar*/


    /*una vez sabes el número de procesos, creas los semáforos*/
    sem_t *sem[num_proc + 1];
    for (int i = 0; i <= num_proc; i++)
    {
        char name[12];
        sprintf(name, "%d", i);
        /*vas creando los semáforos*/
        if ((sem[i] = sem_open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED)
        {
            perror(" sem_open ");
            exit(EXIT_FAILURE);
        }
    }

    /*se bloquean todas las señales menos las que nos interesan*/
    sigfillset(&test);
    sigdelset(&test, SIGUSR1);
    sigdelset(&test, SIGTERM);

    /*pones la alarma de tiempo*/
    if (alarm(TIME))
    {
        fprintf(stderr, " Existe una alarma previa establecida \n");
    }

    /*bucle para lanzar procesos*/
    for (pid = 0, t = 0; !pid && t != num_proc; ++t)
    {
        pid = fork(); /*se hacen todos los forks*/
    }

    /*se configura el manejador de alarma y sigint del padre*/
    if (t == 1)
    {
        struct sigaction act_1;
        act_1.sa_handler = manejador_2;
        sigemptyset(&act_1.sa_mask);
        act_1.sa_flags = 0;

        if (sigaction(SIGALRM, &act_1, NULL) < 0)
        {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        if (sigaction(SIGINT, &act_1, NULL) < 0)
        {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        /*la máscara del padre es sensible también a SIGALRM y SIGINT y no lo es a SIGTERM*/
        sigfillset(&test);
        sigdelset(&test, SIGALRM);
        sigdelset(&test, SIGINT);
        sigdelset(&test, SIGUSR1);
        printf("PID: %d\tPadre: %d\tHijo: %d\tNº Ciclo: %d\n", getpid(), getppid(), pid, t); /*imprimo mi pid y ciclo*/        
        sem_post(sem[t]); /*pone el semáforo a activo para que su hijo pueda imprimir*/
    }
    if(pid==0)  t++;
    while(1){ //bucle que se repite infinito hasta que recibe la alarma o el sigint
        //primero envía la señal
        if(pid!=0){
            kill(pid, SIGUSR1); /*le manda la señal a su hijo, el manejador a su vez se la manda al hijo del hijo y así*/
        }
        else{
            kill(f_pid, SIGUSR1); /*si es el último, se la manda al primero*/
        }
        sleep((rand() % 10) + 2); //espera aleatoria despues de enviar la señal
        //debug
        //printf("Proceso: %d Espera semáforo: %d y pone semáforo %d, y su hijo es: %d\n", getpid(), t-1, t, pid);
        /*luego espera a que su padre se la envie*/
        while(s==0) /*por si se envia ántes del sigsuspend*/
            sigsuspend(&test); /*espero a recibir la señal*/
        sem_wait(sem[t-1]); /*espero a que imprima el padre*/
        printf("PID: %d\tPadre: %d\tHijo: %d\tNº Ciclo: %d\n", getpid(), getppid(), pid, t); /*imprimo mi pid y ciclo*/        
        sleep(0.5); //para ir viendo poco a poco los mensajes
        sem_post(sem[t%(num_proc+1)]); /*le digo al hijo que puede imprimir*/
        s=0;
    }
    liberar(num_proc);
    wait(NULL);
    return 0;
}
