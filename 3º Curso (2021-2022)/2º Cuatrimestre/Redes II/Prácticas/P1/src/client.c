#include <netdb.h>

#include "../include/common.h"

struct sockaddr_in serv_addr; //dirección del server

int main(int argc, char *argv[]){
    int sockfd;  //File descriptors
    int portno;             //Port Number
    struct hostent *server;
    char buffer[BUFFER_LENGTH];
    int n;                  //return value for read() and write()
    /*struct  hostent{
        char    *h_name;         official name of host 
        char    **h_aliases;     alias list 
        int     h_addrtype;      host address type 
        int     h_length;        length of address 
        char    **h_addr_list;   list of addresses from name server 
        #define h_addr  h_addr_list[0]   address, for backward compatiblity 
        };*/

    /*lo mismo que con el server*/
    if (argc < 3) {
        errorFunction("ERROR, no port provided\n");
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        errorFunction("ERROR opening socket");
    }
    /*get host by name retorna pointer to a hostent a partir del nombre*/
    /*si es null indica que no se pudo encontar el host*/
    if ((server = gethostbyname(argv[1])) == NULL){
        errorFunction("ERROR, no such host");
    }
    /*se inicializan los campos del server*/
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    
    //bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    /*probamos a establecer la conexión*/
    if (connect(sockfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        errorFunction("ERROR connecting");
    }

    //sprintf(buffer, "Hola pepe soy %d\n", getpid());

    sprintf(buffer, "GET /index.html HTTP/1.1\r\nHost: example.com\r\nCookie: \r\n\r\nEste es el cuerpo del mensaje");
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
        errorFunction("ERROR writing to socket");
    bzero(buffer,BUFFER_LENGTH+1);
    while ((n = read(sockfd, buffer, BUFFER_LENGTH)) > 0)
        fprintf(stdout,"%s\n",buffer);

    close(sockfd);

    return 0;
}

void errorFunction(char *msg){
    perror(msg);
    exit(1);
}
