#include "../include/common.h"
#include "../include/utils.h"
char* conf(char* buffer){
    char * token = NULL;
    if(!buffer){
        return NULL;
    }
    token = strtok(buffer, " ");
    if(strcmp(token, "=")){
        token = strtok(NULL, " ");
        token = strtok(NULL, "\n\0");
        return token; //para saltar el espacio
    }
    else return NULL;
}

void get_response(char *path, char *body, dataServer *data_server){
    FILE *f = NULL;
    char buffer[BUFFER_LENGTH];
    char *retMessage = NULL;
    char *type = NULL;
    int errorFlag = 0;
    
    if(!(retMessage = (char*)calloc(BUFFER_LENGTH, sizeof(char)))){
        pthread_exit("ERROR on memory calloc\n");
    }
    if(!(type = (char*)calloc(20, sizeof(char)))){
        pthread_exit("ERROR on memory calloc\n");
    }
    
    getContentType(path, body, &f, type);
    
    printf("Type: %s\n", type);
    if (f == NULL){
        if(strncmp(type, "err", 3)==0){
            sprintf(retMessage, "HTTP/1.0 400 Bad Request\r\n");
        }else
            sprintf(retMessage, "HTTP/1.0 404 Not Found\r\n");
        errorFlag = 1;
    }
    else{
        sprintf(retMessage, "HTTP/1.0 200 OK\r\n");
    }
    
    //printf("La error flag es: %d\n", errorFlag);
    int size=0;
    
    if(strcmp(type, "py")==0 || strcmp(type, "php")==0){ /*si se quiere lanzar un script*/
    /*cojo los argumentos*/
        char comando[strlen(path)+8]; //para escribir lenguaje + path

        memset(comando, 0, strlen(path)+8);
        if(strcmp(type, "py") == 0)
            strcat(comando, "python ");
        else
            strcat(comando, "php ");
        printf("Comando: %s\n", comando);
        strcat(comando, path); 
        printf("%s\n\n", comando); 
        f = popen(comando, "r"); /*ejecutamos el código*/
    }
    
    createHeader(retMessage, path, data_server, type, &size, 0);
    /*intenta mandar al cliente la cabecera*/
    if (write(data_server->sockfd,retMessage,strlen(retMessage)) < 0){
        printf("1\n");
        pthread_exit("ERROR writing to socket\n");
    }

    if(!errorFlag){
        int rret;
        
        memset(buffer, 0, 4096);
        
        rret = fread(buffer, BUFFER_LENGTH, 1, f);
        printf("Script:\n%s\n", buffer);
        while (rret > 0){ /*si hay que hacer particiones*/
            //mandamos el archivo
            if (write(data_server->sockfd,buffer,BUFFER_LENGTH) < 0){
                printf("ERROR writing to socket\n");
                pthread_exit("ERROR writing to socket\n");
            }
            rret = fread(buffer, BUFFER_LENGTH, 1, f);
        }

        size=size%BUFFER_LENGTH;

        if (write(data_server->sockfd,buffer,size) < 0){
                printf("ERROR writing to socket 2\n");
                pthread_exit("ERROR writing to socket\n");
        }
        
        if(strcmp(type, "py")==0 || strcmp(type, "php")==0){
            pclose(f);
        }else
            fclose(f);
    }

    free(retMessage);
    free(type);      
}

void getContentType(char* path, char *body, FILE **f, char* type){
    char *token=NULL;
    if(type==NULL){
        return;
    }
    if(path==NULL){
        sprintf(type, "err");
        return;
    }
    //si es un options para todo será error para get pero no para options
    if(strcmp(path, ".*")==0){ 
        sprintf(type, "err2");
        return;
    }

    if (body && strstr(path, "?") != NULL){
        sprintf(type, "err2");
        return;
    }

    token =  strrchr(path, '.') + 1;
    if(!token){
        sprintf(type, "err");
        return;
    }
    printf("token: %s\n", token);
    printf("path: %s\n", path);

    if(strcmp(token, "txt")==0 || strcmp(token, "html")==0 || strcmp(token, "htm")==0){
        *f = fopen(path, "r");
    }else{
        if(strncmp(token, "py", 2)==0 || strncmp(token, "php", 3)==0){
            char *aux_path = malloc(strlen(path));
            char *aux_body = NULL;

            if(!aux_path){
                sprintf(type, "err");
                return;
            }

            strcpy(aux_path, path);
            aux_path = strtok(aux_path, "?"); //cojemos el path verdadero del fichero
            printf("Aux_path: %s\n", aux_path);

            if (body){
                if ((aux_body = malloc(strlen(body)))==NULL){
                    free(aux_path);
                    sprintf(type, "err");
                    return;
                }
                strcpy(aux_body, body);
                printf("Aux_body: %s\n", aux_body);
            }
            
            *f = fopen(aux_path, "r"); //lo abrimos para conocer su info de modificación etc
            char *args = NULL;
            args = getArguments(path, body);
            char comando[BUFFER_LENGTH];
            memset(comando, 0, BUFFER_LENGTH); 
            //reescribimos el path con los args bien escritos para poder ejecutar
            sprintf(path, "%s \"%s\"", aux_path, args);
            printf("Path: %s\n", path);
            free(aux_path);
            if (body)
                free(aux_body);
        }
        else{
            printf("Este es el path: %s",path);
            *f = fopen(path, "rb");
        }
    }
    if(strcmp(token, "txt")==0){
        sprintf(type, "text/plain");
        return;
    }
    if(strcmp(token, "html")==0 || strcmp(token, "htm")==0 ){
        sprintf(type, "text/html");
        return;
    }
    if(strcmp(token, "gif")==0){
        sprintf(type, "image/gif");
        return;
    }
    if(strcmp(token, "jpeg")==0 || strcmp(token, "jpg")==0 ){
        sprintf(type, "image/jpeg");
        return;
    }
    if(strcmp(token, "mpeg")==0 || strcmp(token, "mpg")==0 ){
        sprintf(type, "video/mpeg");
        return;
    }
    if(strcmp(token, "docx")==0 ){
        sprintf(type, "application/msword");
        return;
    }
    if(strcmp(token, "pdf")==0){
        sprintf(type, "application/pdf");
        return;
    }
    if(strncmp(token, "py", 2)==0){
        sprintf(type, "py");
        return;
    }
    if(strncmp(token, "php", 3)==0){
        sprintf(type, "php");
        return;
    }
    sprintf(type, "err");
}

void createHeader(char *retMessage, char* path, dataServer *data_server, char *type, int *size, int method){
    char date[100];
    if(!retMessage || !path || !size){
        return;
    }
    /*obtenemos el tiempo para la cabecera*/
    time_t now = time(0);
    struct tm tm = *gmtime(&now);
    strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S %Z", &tm); /*cojemos la fecha*/
    
    /*escribimos la cabecera*/

    /*primero ponemos la fecha*/
    strcat(retMessage, "Date: ");
    strcat(retMessage, date);

    /*luego va el signatura*/
    strcat(retMessage, "\r\nServer: ");
    strcat(retMessage, data_server->serverSignature);
    struct stat attrib;
    /*ahora va el last modified*/
    if(strcmp(path, "*")!=0 ){
        strcat(retMessage, "\r\nLast-Modified: ");
        /*cojo los atributos del fichero llamado*/
        stat(path, &attrib);
        tm = *gmtime(&(attrib.st_mtime)); 
        strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S %Z", &tm); /*cojemos la fecha*/
        strcat(retMessage, date);
    }
    /*content lenght*/
    strcat(retMessage, "\r\nContent-Length: ");
    if (strcmp(type, "py")==0 || strcmp(type, "php")==0){
        strcat(retMessage, "200");
    }
    else if(method==0){
        /*reutilizo el date xd*/
        sprintf(date, "%d", (int)attrib.st_size);
        *size = atoi(date); //guardo el valor del size
        strcat(retMessage, date);
    }
    else{
        strcat(retMessage, "0"); //el options no envia contenido
    }

    /*content type*/
    strcat(retMessage, "\r\nContent-Type: ");
    if(strcmp(type, "err2")!=0){
        if (strcmp(type, "py")==0 || strcmp(type, "php")==0)
            strcat(retMessage, "text/plain");
        else
            strcat(retMessage, type);
    }
    else{
        strcat(retMessage, "No file requested");
    }
    /*fin de cabecera*/
    if(method==1){
        strcat(retMessage, "\r\nAllow: ");
        if(strcmp(type, "py")==0 || strcmp(type, "php")==0 || strcmp(type, "err2")==0){
            strcat(retMessage, "GET POST OPTIONS");
        }
        else{
            strcat(retMessage, "GET OPTIONS");
        }
    }
    strcat(retMessage, "\r\n\r\n");
    printf("\n%s\n", retMessage);
}

char* getArguments(char *path, char *body){
    char *copy = NULL, *token = NULL;
    char *com = NULL;

    if (!path && !body){
        return 0;  
    }

    if(!(com=calloc(BUFFER_LENGTH/2, sizeof(char)))){
        return com;
    }

    if (body){
        copy = (char *)malloc((strlen(body) + 1) * sizeof(char));
        strcpy(copy, body);
        if ((token = strtok(copy, "="))!=NULL){
            if ((token = strtok(NULL, "\0\n"))!=NULL){
                strcat(com, token);
            }
        }
        while((token=strtok(NULL, "="))!=NULL){
            if((token=strtok(NULL, "\0\n"))!=NULL){
                strcat(com, " ");
                strcat(com, token);
            }
        }
    }
    else if (path){
        copy = (char *)malloc((strlen(path) + 1) * sizeof(char));
        strcpy(copy, path);
        
        if((token = strrchr(copy, '?')) != NULL){
            if((token = strtok(token, "="))!=NULL){
                if((token = strtok(NULL, "&"))!=NULL){
                    strcat(com, token);
                }
            }
            while((token = strtok(NULL, "="))!=NULL){
                if((token = strtok(NULL, "&"))!=NULL){
                    strcat(com, " ");
                    strcat(com, token);
                }
            }
        }
    }
    printf("Args: %s\n", com);
    free(copy);
    return com;
}

void get_request(dataServer *data_server, char **method, char **path, int *minor_version, struct phr_header *headers, size_t *num_headers, char **body){
    char buffer[BUFFER_LENGTH];
    int rret;           //return value for read() and write()
    int pret;           //return value for parser
    size_t buflen = 0, prevbuflen = 0, method_len, path_len;
    char aux_path[100];

    memset(buffer, 0, BUFFER_LENGTH);

    while (1){
        while((rret=read(data_server->sockfd, buffer + buflen, sizeof(buffer) - buflen)) == -1 && errno == EINTR);

        if (rret <= 0){
            pthread_exit("Error on read\n");
        }

        prevbuflen = buflen;
        buflen += rret;

        //*num_headers = sizeof(headers) / sizeof(headers[0]);
        *num_headers = 100;

        pret = phr_parse_request(buffer, buflen, (const char **)method, &method_len,
            (const char **)path, &path_len, minor_version, headers, num_headers, prevbuflen);

        if (pret > 0)
            break;            
        else if (pret == -1)
            pthread_exit("Error on request parse\n");

        if (buflen == sizeof(buffer))
            pthread_exit("Error: Request is too long\n");
    }

    sprintf(*body, "%s", buffer + pret);
    sprintf(aux_path, "%s", data_server->serv_root);
    sprintf(*method, "%.*s", (int)method_len, *method);
    sprintf(*path, "%.*s", (int)path_len, *path);
    strcat(aux_path, *path);
    strcpy(*path, aux_path);

    for (int i = 0; i < *num_headers; i++){
        sprintf((char *)headers[i].name, "%.*s", (int)headers[i].name_len, headers[i].name);
        sprintf((char *)headers[i].value, "%.*s", (int)headers[i].value_len, headers[i].value);
    }

    fprintf(stdout, "\nSe han ledído %d datos\n", rret);
    fprintf(stdout, "El metodo usado ha sido %s, con tamaño %d\n", *method, (int)method_len);
    fprintf(stdout, "La ruta enviada ha sido %s, con tamaño %d\n", *path, (int)path_len);
    fprintf(stdout, "La versión HTTP usada ha sido 1.%d\n", *minor_version);
    if (*num_headers > 0)
        fprintf(stdout, "Las cabeceras del mensaje son:\n");
    for (int i = 0; i < *num_headers; i++){
        fprintf(stdout, "%s: %s\n", headers[i].name, headers[i].value);
    }
    printf("\nEl cuerpo del mensaje es:\n");
    printf("%s\n", *body);
}

void response_to_options(char *path, dataServer *data_server){
    FILE *f = NULL;
    char *type = NULL;
    char *retMessage = NULL;
    int size=0;
    if(!(retMessage = (char*)calloc(BUFFER_LENGTH, sizeof(char)))){
        pthread_exit("ERROR on memory calloc\n");
    }
    if(!(type = (char*)calloc(20, sizeof(char)))){
        pthread_exit("ERROR on memory calloc\n");
    }
    getContentType(path, NULL, &f, type);
    if(f==NULL)
        printf("Aux: %s", type);

    if (f == NULL && strcmp(type, "err2")!=0){
        if(strcmp(type, "err")==0){
            sprintf(retMessage, "HTTP/1.0 400 Bad Request\r\n");
        }else
            sprintf(retMessage, "HTTP/1.0 404 Not Found\r\n");
    }
    else{
        sprintf(retMessage, "HTTP/1.0 200 OK\r\n");
    }
    createHeader(retMessage, path, data_server, type, &size, 1);
    //le mandamos la respuesta
    if (write(data_server->sockfd,retMessage,strlen(retMessage)) < 0){
        printf("1\n");
        pthread_exit("ERROR writing to socket\n");
    }
}

