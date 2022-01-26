#ifndef ALFA_H
#define ALFA_H 1

#include <stdio.h>

/* Macro para cuerpo de funciones en macros */
#define F_BLOCK(block) do { block } while (0)
#define NO_USO(arg) ((void)(arg))

#define MAX_LONG_ID 100
#define MAX_LONG_VECTOR 64

/* Extension de los ficheros en lenguaje ALFA */
#define INPUT_EXTENSION ".alfa"

/* Codigos de errores */
typedef enum ErrorCode
{
    NO_ERR,
    ERR_MORFOLOGICO,
    ERR_SINTACTICO
} ErrorCode;

/* Tipos de variables*/
typedef enum
{
    BOOLEAN,
    INT
} Tipo;

/* Estructura para ficheros de entrada y salida */
extern struct ALFA_UTILS
{
    FILE *fin;          /* Fichero de entrada */
    char *fin_name;     /* Nombre de fichero de entrada */
    FILE *fasm;         /* Fichero de compilacion */
    FILE *fdbg;         /* Fichero de debug (logs de flex/bison) */
    FILE *ferr;         /* Fichero de salida de errores */

    ErrorCode error;    /* Codigo de error */

    unsigned int line, col;/* Numeros de linea y columna */
} alfa_utils_T;

typedef struct {
    char lexema[MAX_LONG_ID+1];    /* lexema de Identificador */
    int valor_entero;               /* valor de constante entera */
    int es_direccion;               /* Variable o Constante*/

    Tipo tipo;                      /* boolean o entero */

    int etiqueta;                   /* para generacion NASM */

    int num_parametros_llamada_actual; /* Para llamadas a funciones */
} tipo_atributos;



/* Funcion para manejar errores */
void manage_error(char *msg, char *s);

/* Funcion Principal que llama al analizador */
int main(int argc, char *argv[]);


#endif /* ALFA_H */