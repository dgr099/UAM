/**************************************************
Nombre del modulo: p2_e2.c
Descripcion: Paso de infijo a postfijo
Autor:  
Fecha: 06-03-20
Modulos propios que necesita:
- stack_fp.h
- stack_types.h
Notas:
Modificaciones:
Mejoras pendientes:
**************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include "stack_fp.h"
#include "stack_types.h"
#include <string.h>


/*=== Definiciones ==========================================================*/

#define OPERATORS {'+', '-','*', '/', '%', '^'}
#define MENOR {'+', '-'}
#define MAYOR {'*', '/', '%'}
#define TOP {'^'}


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------
Nombre: isOperator
Descripcion: Determina si el caracter leido es un operador o no
Argumentos de entrada:
1. c, puntero al caracter leido del string
Retorno:s 
- TRUE, si el caracter es un operador
- FALSE, si el caracter no es un operador
-----------------------------------------------------------------------------*/
Bool isOperator (const char *c) {
    char ope[] = OPERATORS;
    int i, ope_n;
    ope_n=strlen(ope);
    for(i=0; i!=ope_n; i++){
        if(*c==ope[i]){
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
Nombre: integerPrec
Descripcion: Determina la precedencia del caracter leido
Argumentos de entrada:
1. c, puntero al caracter leido del string
Retorno:
- 0, si el caracter es un operador
- -1, si el caracter leido es una apertura de parentesis
- 1 en caso contario
-----------------------------------------------------------------------------*/
int integerPrec (const char *c){
    int i, num_m;
    char cad[] = MENOR;
    num_m=strlen(cad);
    for(i=0; i!=num_m; i++){
        if(cad[i]==*c){
            return 0;
        }
    }
    if(*c=='('){
        return -1;
    }
    return 1;
}

/*-----------------------------------------------------------------------------
Nombre: infix2postfix
Descripcion: Determina la precedencia del caracter leido
Argumentos de entrada:
1. suf, el string en sufijo
2. in, el string en infijo
Retorno:
- ERROR, si falla
- OK, en caso contrario
-----------------------------------------------------------------------------*/
Status infix2postfix (char *suf, const char *in){
	/*Bool ret = TRUE;*/
	Stack *s = NULL;
    char *car = NULL;
	int i = 0, z = 0;
	if (!in || !suf) {
		return ERROR;
	}
	s = stack_init (char_free, char_copy, char_print);
	if (!s) {
		return ERROR;
	}
	for (i=0; in[i] != '\0'; i++) {
		if (isOperator(&in[i]) == TRUE) {
			while (stack_isEmpty(s) == FALSE && integerPrec(stack_top(s))>=integerPrec(&in[i])){
                car=stack_pop(s);
                suf[z]=*car;
                z++;
                free(car);
			}
            stack_push(s, &in[i]);
		}
        else if(in[i]=='('){
            stack_push(s, &in[i]);
        }
        else if(in[i]==')'){
            while(stack_isEmpty(s)!=TRUE && *(car=stack_pop(s))!='('){
                suf[z]=*car;
                z++;
                free(car);
            }
            free(car);
        }
        else if(in[i]==' '){
            
        }
        else{
            suf[z]=in[i];
            z++;        
        }     
	}
    for(; stack_isEmpty(s)!=TRUE; z++){
            car=stack_pop(s);
            if((*car)=='('){
                return ERROR;
            }
            suf[z]=*car;
            free(car);
    }
    stack_free(s);
    return OK;
}


int main(int argc, char **argv){
    char *suf;
    if(argc<2){
        printf("Error debe incluir un argumento de entrada, pruebe poniendo ./ejecutable expresion_matemática");
        return 0;
    }
    if((suf=(char*)calloc(strlen(argv[1]) + 1, sizeof(char)))==NULL){
        return 1;
    }
    printf("Input: %s\n", argv[1]);
    if(infix2postfix (suf, argv[1])==ERROR){
        printf("Error en la ejecución del infix2postfix\n");
        free(suf);
        return 1;
    }
    printf("Output: %s\n", suf);
    free(suf);
    return 0;
}
