/*********************************************************************
 * pract3b.c
 *
 * Sistemas Basados en Microprocesador
 * 2020-2021
 * Practica 3b
 *
 *********************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR -1
 #define MAX_CADENA 50
 #define CarCuenta 10
/*******************************************************************************
* Nombre: encuentraSubcadena
* 
* funcionalidad: encuentra una subcadena en una cadena de strings
* Parámetros de entrada:
* 				- str la cadena
                -substr la subcadena a buscar en la cadena
* Valores retorno:
*				-  int: posición de la subcadena en la cadena (empezando por 0), -1 si no la encuentra
******************************************************************************/
int encuentraSubcadena (char* str, char* substr);
/*******************************************************************************
* Nombre: calculaSegundoDC
* 
* funcionalidad: devuelve el segundo dígito de control 
* Parámetros de entrada:
* 				- str numCuenta
                -substr la subcadena a buscar en la cadena
* Valores retorno:
*				-  int: posición de la subcadena en la cadena (empezando por 0), -1 si no la encuentra
******************************************************************************/
unsigned int calculaSegundoDC (char* numCuenta);

int main( void ){
    char opcion;
    char cadena[MAX_CADENA];
    char subcadena[MAX_CADENA];
    char numCuenta[CarCuenta];
    int ret=-1;
    printf("Elija la opcion que desea probar: \n");
	printf("a - encontrar subcadena \n");
    printf("b - calcula segundo digito de control \n");
	scanf("%c", &opcion);
    if(opcion>'b' || 'a'>opcion){
        printf("-Opcion %c: incorrecta fuera de [a,b,c,d]\n Bye\n",opcion);
		return ERR;
    } else{
        printf("-Opcion Elegida --> %c -\n",opcion);
    }
    switch (opcion)
    {
    case 'a':
        printf("Introduzca separado por espacio la cadena y la subcadena a buscar: \n");
        scanf("%s %s", &cadena, &subcadena);
        ret = encuentraSubcadena(cadena, subcadena);
        if(ret==-1){
            printf("Subcadena no encontrada");
        }   else{
            printf("Subadena en la posicion %d de la cadena", ret);
        }
        break;
    case 'b':
        printf("Introduzca el numero de 10 bits de la cuenta bancaria: \n");
        scanf("%s", numCuenta);
        ret = calculaSegundoDC (numCuenta);
        if(ret==-1){
            printf("Error en los argumentos (los digitos de la cuenta bancaria no son 10)");
        } else{
            printf("El segundo digito de control es: %d", ret);
        }
        break;
    default:
        break;
    }
    return OK;
}

