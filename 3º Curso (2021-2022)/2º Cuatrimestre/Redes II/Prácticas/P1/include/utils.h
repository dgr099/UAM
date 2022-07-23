#ifndef UTILS_H
#define UTILS_H
/********
* FUNCIÓN: char* conf(char* buffer)
* ARGS_IN: char *buffer - buffer con la lectura de los argumentos sin tokenizar
* DESCRIPCIÓN: Tokeniza para devolver un string con el token del igual
* ARGS_OUT: char * - devuelve un puntero señalado al valor posterior al igual
********/
char* conf(char* buffer);
/********
* FUNCIÓN: void response_to_get(char *path, char *body, dataServer *data_server);
* ARGS_IN: char *path - ruta de la petición
* ARGS_IN: char *body - cuerpo de la petición 
* ARGS_IN: dataServer *data_server - información del server (sockets etc para poder hacer operaciones de write)
* DESCRIPCIÓN: procesa y envía la respuesta ante una solicitud get HTTP
* ARGS_OUT: void
********/
void get_response(char *path, char *body, dataServer *data_server);
/********
* FUNCIÓN: void response_to_options(char *path, dataServer *data_server);
* ARGS_IN: char *path - path de la petición options
* ARGS_IN: dataServer *data_server - información del server (sockets etc para poder hacer operaciones de write)
* DESCRIPCIÓN: procesa y envía la respuesta ante una solicitud options HTTP
* ARGS_OUT: void
********/
void response_to_options(char *path, dataServer *data_server);
/********
* FUNCIÓN: void getContentType(char* path, char *body, FILE **f, char* type)
* ARGS_IN: char *path - path de la petición para poder extraer el tipo de fichero solicitado
* ARGS_IN: char *body - cuerpo de la petición para poder extraer los argumentos en caso de petición POST
* ARGS_IN: FILE **f - fichero pasado por referencia para que si existe abra el fichero solicitado en el path
* ARGS_IN: char *path - path de la petición para poder extraer el tipo de fichero solicitado
* DESCRIPCIÓN: Extraer el tipo de fichero solicitado del path
* ARGS_OUT: void
********/
void getContentType(char* path, char *body, FILE **f, char* type);
/********
* FUNCIÓN: createHeader(char *retMessage, char* path, dataServer *data_server, char *type, int *size, int method)
* ARGS_IN: char *retMessage - array donde se guardara la cabecerá
* ARGS_IN: char *path - path de la petición
* ARGS_IN: dataServer *data_server - información del server
* ARGS_IN: char *type - tipo de fichero
* ARGS_IN: int *size - entero donde se guardará el tamaño del fichero
* ARGS_IN: int method - entero indicador del método del que crear la cabecera (0-get 1-options)
* DESCRIPCIÓN: Se encarga de crear la cabecera http para el método solicitado dado el path
* ARGS_OUT: void
********/
void createHeader(char *retMessage, char* path, dataServer *data_server, char *type, int *size, int method);
/********
* FUNCIÓN: getArguments(char *path, char *body)
* ARGS_IN: char *path - path de la petición que incluye los argumentos del script para GET
* ARGS_IN: char *body - cuerpo de la petición que incluye los argumentos del script para POST
* DESCRIPCIÓN: Obtiene del path los valores de las peticiones 
* ARGS_OUT: char * - devuelve una cadena con los valores de los argumentos de la petición
********/
char* getArguments(char *path, char *body);
/********
* FUNCIÓN: void get_request(dataServer *data_server, char **method, char **path, int *minor_version, struct phr_header *headers, size_t *num_headers, char **body);
* ARGS_IN:
* DESCRIPCIÓN:
* ARGS_OUT:
********/
void get_request(dataServer *data_server, char **method, char **path, int *minor_version, struct phr_header *headers, size_t *num_headers, char **body);

#endif
