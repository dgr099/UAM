#include <signal.h>

#include "../include/common.h"
#include "../include/utils.h"

void *threadFunction(void *dataS);
void handler(int sig);
char* conf(char* string);
void free_all(char *str1, char *str2);
pthread_t *pool = NULL; //array para guardar identificadores de los hilos
int sockfd;             //File descriptors

int main(int argc, char *argv[]){
    int clilen;             //Client address size
    int threadNum = 0;      //asignador del hilo
    struct sigaction act;
    int maximumLineLength = 128, yes = 1;
    char *lineBuffer = NULL;
    dataServer data_server;
    
    /**
     * The variable serv_addr is a structure of type struct sockaddr_in. 
     * This structure has four fields. 
     */
    struct sockaddr_in serv_addr, cli_addr;
    FILE *f=NULL; // fichero de configuración del server
    if((f=fopen("server.conf", "r"))==NULL){
        errorFunction("Conf file not found");
    }

    /*inicializamos los valores del data_server*/
    data_server.serv_root = NULL;
    data_server.maxClient = 0;
    data_server.listenPort = 0;
    data_server.serverSignature = NULL;
    data_server.sockfd = 0;
    
    if((lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength))==NULL){
        errorFunction("Not memory enought");
    }
    
    /*mientras queden lineas por leer*/
    while(fgets(lineBuffer, maximumLineLength, f)) {
        if(lineBuffer[0]=='#')  continue;

        if(strncmp (lineBuffer, "server_root", sizeof("server_root")-1)==0){
            data_server.serv_root = strdup(conf(lineBuffer));          
        }
        if(strncmp (lineBuffer, "max_clients", sizeof("max_clients")-1)==0){ 
            data_server.maxClient = atoi(conf(lineBuffer));;   
        }
        if(strncmp (lineBuffer, "listen_port", sizeof("listen_port")-1)==0){ 
            data_server.listenPort = atoi(conf(lineBuffer));  
        }
        if(strncmp (lineBuffer, "server_signature", sizeof("server_signature")-1)==0){ 
            data_server.serverSignature = strdup(conf(lineBuffer)); 
        }
    
    }
    fprintf(stdout, "Server root: %s\n", data_server.serv_root);
    fprintf(stdout, "Maximum of clients: %d\n", data_server.maxClient);
    fprintf(stdout, "Listen port: %d\n", data_server.listenPort);
    fprintf(stdout, "Server signature: %s\n", data_server.serverSignature);
    free(lineBuffer);
    fclose(f);
    /**
        struct sockaddr_in 
        { 
        short int sin_family;         Familia de la Direccion              
        unsigned short int sin_port;  Puerto                               
        struct in_addr sin_addr;      Direccion de Internet               
        unsigned char sin_zero[8];    Del mismo tamanio que struct sockaddr 
        }
    */

    // We chosed a stream_socket because we're working with TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        errorFunction("ERROR opening socket");
    }

    //bzero((char *)&serv_addr, sizeof(serv_addr)); obsoleta
    memset(&serv_addr, 0, sizeof(serv_addr));
    //cogemos el número de puerto de los argumentos pasados por teclado
    
    /**
     * The first field is short sin_family, 
     * which contains a code for the address family. 
     * It should always be set to the symbolic constant AF_INET. 
     */
    serv_addr.sin_family = AF_INET;
    /*
    * The second field of serv_addr is unsigned short sin_port, which contain the port number. 
    * it is necessary to convert this to network byte order
    */
    serv_addr.sin_port = htons(data_server.listenPort);
    /**
     * The third field of sockaddr_in is a structure of type struct 
     * in_addr which contains only a single field unsigned long s_addr.
     * his field contains the IP address of the host. 
     * and there is a symbolic constant INADDR_ANY which gets this address.
     */
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1){
        errorFunction("Error en setsockopt");
    }

    /*
    * La llamada bind() se usa cuando los puertos locales de nuestra maquina estan en nuestros planes (usualmente cuando utilizamos la llamada listen()). 
    * Su funcion esencial es asociar un socket con un puerto (de nuestra maquina). Analogamente socket(), devolvera -1 en caso de error.
    */
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){ //si no se puede hacer bind (ya sea por socket ocupado u otra causa)
        errorFunction("ERROR on binding");
    }

    /**
     * La funcion listen() se usa si se estan esperando conexiones entrantes, 
     * lo cual significa, si se quiere, que alguien pueda conectarse a nuestra maquina.
     */
    if(listen(sockfd, data_server.maxClient) <0){
        errorFunction("ERROR on listen");
    }

    /* Reservamos memoria para el pool de hilos con el tamaño de la cola de listen */
    pool = (pthread_t *)malloc(data_server.maxClient * sizeof(pthread_t));
    if (pool == NULL){
        errorFunction("ERROR saving memory for pool of threads");
    }

    /**    //fprintf(stdout, "Envio:\n%s", retMessage);
     * Cuando alguien intenta conectarse a nuestra computadora, se debe usar accept() para conseguir 
     * la conexion. Alguien solo podra conectarse (asociese con connect()) a nuestra maquina, 
     * si nosotros aceptamos (asociese con accept())
     */

    clilen = sizeof(cli_addr);

    /* Preparamos la salida con Ctrl+C */
    act.sa_handler = handler;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;
    
    if (sigaction(SIGINT, &act, NULL) < 0){
        errorFunction("ERROR on sigaction");
    }

    /* Primer hilo en aceptar una petición */
    while (1){
        /* El padre espera conexiones */
        if ((data_server.sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (unsigned int *) &clilen)) < 0)
            errorFunction("ERROR on accept");
        /* Si no hay error, asigna a un hilo la conexion con el cliente */
        int ret=0;
        if((ret=pthread_create(&pool[threadNum], NULL, threadFunction, &data_server))!=0){
            char errorMessage[17+1+6];
            sprintf(errorMessage, "Error con código %d", ret);
            errorFunction(errorMessage);
        }
        pthread_detach(pool[threadNum]);
        /* Se asignan los clientes a los hilos de forma circular */
        threadNum = (threadNum+1)%data_server.maxClient;
    }
    /*termina la ejecución del programa*/
    return 0;
}

void errorFunction(char *msg){
    perror(msg);
    if (pool != NULL)
        free(pool);
    exit(1);
}

void *threadFunction(void *dataS){
    char *retMessage=NULL;
    size_t num_headers;
    int minor_version; 
    struct phr_header *headers = malloc(100*sizeof(struct phr_header));
    char *method = NULL, *path = NULL, *body = NULL;
    dataServer data_server = *((dataServer *)dataS);

    if(!(body = (char *)malloc(BUFFER_LENGTH*sizeof(char)))){
        pthread_exit("ERROR memory\n");
    }

    memset(body, 0, BUFFER_LENGTH);

    /*Cuando un cliente se conecte exitosamente pasager
    procedemos a leer empleando el nuevo descriptor obtenido del accept
    el read bloquea el proceso miéntras no tenga nada para leer*/
    get_request(&data_server, &method, &path, &minor_version, headers, &num_headers, &body);
    
    if (strcmp(method, "GET") == 0){
        get_response(path, NULL, &data_server);
    }
    else if (strcmp(method, "POST") == 0){
        get_response(path, body, &data_server);
    }
    else if (strcmp(method, "OPTIONS") == 0){
        response_to_options(path, &data_server);
    }
    else {
        sprintf(retMessage, "HTTP/1.0 405 Method Not Allowed\n");
        //error405()
        if (write(data_server.sockfd,retMessage,strlen(retMessage)) < 0){
            pthread_exit("ERROR writing to socket\n");
        }
    }
    
    close(data_server.sockfd);
    fprintf(stdout, "Conection completed\n");

    free(body);

    pthread_exit(NULL);
}

void handler(int sig){
    close(sockfd);
    errorFunction("\nFin de programa");
}



void free_all(char *str1, char *str2){
    if (str1)
        free(str1);
    if (str2)
        free(str2);
}

