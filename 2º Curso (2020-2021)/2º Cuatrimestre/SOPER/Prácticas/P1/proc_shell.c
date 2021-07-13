#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LENGHT 100
#define MAX_CMD 50
#define MESSAGE_INICIO "Introduce un comando (puedes pulsar CTRL+D para salir): "
#define Separadores " \t\n"
#define Read 0
#define Writte 1

typedef struct
{
    char entrada[MAX_LENGHT];
    char *cmd[MAX_CMD];
} Comando;

void *procesadoDeLinea(void *arg)
{
    int aux = 0;
    Comando *cmd = arg;
    char h[10];
    cmd->cmd[aux] = strtok(cmd->entrada, Separadores);
    while (cmd->cmd[aux])
    {
        aux++;
        (cmd->cmd[aux]) = strtok(NULL, Separadores);
    }
}


int main()
{
    Comando cmd;
    pthread_t h1, h2;
    int id=0;
    int cod=0;
    int fd[2]={0,0};
    int pid=0;
    char log[MAX_LENGHT]={};
    char entrada[MAX_LENGHT]={};
    FILE *f = NULL;
    if (!(f = fopen("log.txt", "w")))
    {
        perror("fopen");
        fprintf(stdout, "\nSaliendo de la consola, error en la apertura del log...\n");
        exit(EXIT_FAILURE);
    }
    else /*si no hubo errores ni en la tubería ni en el log*/
    {
        while (fprintf(stdout, MESSAGE_INICIO), fgets(entrada, MAX_LENGHT, stdin))
        { /*<-mientras no lea EOF*/
            if (pipe(fd) == -1) /*creo la tubería y compruebo errores*/
            {
                perror("pipe");
                fprintf(stdout, "\nSaliendo de la consola, error en el pipe...\n");
                exit(EXIT_FAILURE);
            }

            fflush(stdout); /*limpio buffers por si acaso*/
            fflush(stdin);
            strtok(entrada, "\n"); /*no me gusta el \n del final :-)*/
            strcpy(cmd.entrada, entrada); /*copio la entrada en la estructura de comando*/
            cod = pthread_create(&h1, NULL, procesadoDeLinea, &cmd); /*hilo para trocear el comando*/
            if (cod)
            {
                fprintf(stdout, "Error en pthread_create: %s\n", strerror(cod));
                exit(EXIT_FAILURE);
            }
            cod = pthread_join(h1, NULL); /*espero al hilo para continuar*/
            if (cod)
            {
                fprintf(stdout, "Error en pthread_join: %s\n", strerror(cod));
                exit(EXIT_FAILURE);
            }
            /*tras esto, queda trozeado el comando*/
            id = fork(); /*<- fork para el hijo encargado de ejecutar el comando*/

            if (id < 0)/*error en el fork*/
            {
                fprintf(stdout, "Error en fork: %s\n", strerror(cod));
                exit(EXIT_FAILURE);
            }

            else if (id == 0)/*si se trata del hijo*/
            {                                            
                if ((cod = execvp(cmd.cmd[0], cmd.cmd))) /*<- ejecuta la instrucción que se pida*/
                {
                    fprintf(stdout, "Error en execvp: %s\n", strerror(cod));
                    exit(EXIT_FAILURE);
                }
                fclose(f);
                exit(EXIT_SUCCESS);
            }

            waitpid(id, &cod, 0); /*<- espera al hijo encargado de ejecutar el comando*/
            id = fork(); /*nuevo fork para guardar en log*/
            if (id < 0)
            {
                fprintf(stdout, "Error en fork: %s\n", strerror(cod));
                exit(EXIT_FAILURE);
            }
            if (id == 0)/*<- si se trata del hijo*/
            { 
                close(fd[Writte]); /*cerramos el extremo que no usamos*/
                int n_bytes = 0;
                do
                {
                    n_bytes = read(fd[0], log, sizeof(log));
                    if (n_bytes == -1)
                    {
                        perror("read");
                        exit(EXIT_FAILURE);
                    }
                } while (!n_bytes); /*bucle hasta que lea algo*/
                close(fd[Read]);
                fprintf(f, "%s\n", log); /*escribe lo que le manda el padre en el fichero log*/
                fclose(f);
                exit(EXIT_SUCCESS);
            }
            /*esto es el padre*/
            if (WIFEXITED(cod))
            {
                sprintf(log, "%s:\tExited with value <%d>", entrada,WEXITSTATUS(cod));
            }
            else
            {
                sprintf(log, "%s:\tTerminated by signal <%d>",entrada,WIFSIGNALED(cod));
            }
            fprintf(stdout, "%s\n", log);/*imprime por pantalla lo que ocurra*/
            close(fd[Read]); /*<- cerramos el extremo que no usamos*/
            dprintf(fd[Writte], "%s\n", log); /*escribe en la tubería el log*/
            close(fd[Writte]);
            waitpid(id, NULL, 0); /*<-espera al hijo*/
        }
    }
    fclose(f);
    fprintf(stdout, "\nSaliendo de la consola...\n");
    exit(EXIT_SUCCESS);
}