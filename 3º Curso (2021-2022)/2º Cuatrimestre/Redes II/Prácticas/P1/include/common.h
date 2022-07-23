#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/stat.h>

#include "../include/picohttpparser.h"

#define BUFFER_LENGTH 4096
#define TRUE 1
#define FALSE 0

typedef struct{
    char *serv_root;
    int maxClient;
    int listenPort;
    char *serverSignature;
    int sockfd;
} dataServer;
/********
* FUNCIÓN: void errorFunction(char *msg);
* ARGS_IN: char *msg - Mensaje de error para escribir
* DESCRIPCIÓN: Cierra y libera los recursos mostrando el mensaje de error pertinente
* ARGS_OUT: void
********/
void errorFunction(char *msg);

#endif