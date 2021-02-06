/******************************************************************************
Nombre del módulo: modelo.c
Descripción: Paso de infijo a postfijo
Autor:  
Fecha: 06/03/20
Modulos propios que necesita:
- stack_fp.h
- stack_types.h
Notas:
Modificaciones:
Mejoras pendientes:
******************************************************************************/

#include <stdio.h>
#include "stack_fp.h"
#include "stack_types.h"
#include <string.h>

/**
* @brief: Get the postfix expression of an infix expression.
* The infix and postfix strings may not overlap and
* the destination postfix string must be
* large enough to receive the infix expression
* (to be checked before calling this function).
*
* @param in Pointer to the infix expression
* @param suf Pointer to the suffix expression
* @return The function returns OK on success or ERROR
* when any of its parametrs is NULL
**/

#define OPERATORS {'+', '-','*', '/', '%', '^'}
#define MENOR {'+', '-'}
#define MAYOR {'*', '/', '%', '^'}

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

int integerPrec (const char *c) {
    int i, num_m;
    char cad[] = MENOR;
    num_m=strlen(cad);
	/*if (c == MENOR) {
		return TRUE;
	}*/
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


Status infix2postfix (char *suf, const char *in) {
	
	Bool ret = TRUE;
	Stack *s = NULL;
    char *car = NULL;
	int i = 0, z = 0;
	
	/* Comprobar que in y suf existen */
	if (!in || !suf) {
		return ERROR;
	}

	/* Inicializar la pila */
	s = stack_init (char_free, char_copy, char_print);
	if (!s) {
		return ERROR;
	}

	/* Recorre la cadena de caracteres */
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
    if((suf=(char*)calloc(strlen(argv[1]), sizeof(char)))==NULL){
        return 1;
    }
    if(infix2postfix (suf, argv[1])==ERROR){
        free(suf);
        return 1;
    }
    printf("%s\n", suf);
    free(suf);
    return 0;

}