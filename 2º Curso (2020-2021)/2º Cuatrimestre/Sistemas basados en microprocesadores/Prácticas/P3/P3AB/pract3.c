/*********************************************************************
 * pract3a.c
 *
 * Sistemas Basados en Microprocesador
 * 2020-2021
 * Practica 3
 * Painting geometrical figures
 * ddga
 *
 *********************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

#define MAXCOL 640
#define MAXROW 480

#define MAXPOINTS 400

#define OK 0
#define ERR -1

/***** Declaracion de funciones *****/

/*------------------------------- Ejercicio 1 ---------------------------------*/
/*******************************************************************************
* Nombre: pintaPixel
* 
* funcionalidad: pasa a modo video, pinta un pixel de color COLOR en la posicion
*				 de la pantalla dado por X e Y
* Parámetros de entrada:
* 				- unsigned char COLOR : color del pixel a pintar
*				- unsigned char X : posicion fila en pantalla
*				- unsigned char Y : posicion columna en pantalla
* Valores retorno:
*				-  char: -1 si posicion fuera de rango permitido; 0 si ok 
******************************************************************************/
char pintaPixel(unsigned char color, int x, int y);


/*********************************************************************************
* Nombre: pintaCuadrado
* 
* funcionalidad: pasa a modo video, pinta un pixel de color “COLOR” en la posicion
*				 de la pantalla dado por “X” e “Y” además de continuar 
*				pintando todos  los pixeles vecinos hasta completar un 
*				cuadrado de dimensiones “tam”
* Parámetros de entrada:
* 				- unsigned char: COLOR
*				- int tam; dimensión en pixeles del lado del cuadrado
*				- int X ; posicion fila en pantalla donde comienza el cuadrado
*				- int Y ; posicion columna en pantalla comienzo de cuadrado
* Valores retorno:
*				-  char: -1 si posicion fuera de rango permitido; 0 si ok 

*******************************************************************************/
char pintaCuadrado(unsigned char color, int tam, int x, int y);


/*------------------------------- Ejercicio 2 ---------------------------------*/

/*******************************************************************************
* Nombre: pintaListaPixeles
* 
* funcionalidad: pintar en pantalla todos los pixeles dados por las 
*				 posiciones X e Y de los vectores de entrada
* Parámetros de entrada:
* 				- unsigned int numPixeles: total elementos de los vectores de entrada
* 				- unsigned char bgcolor: color de fondo de la pantalla
* 				- long int tiempoEspera: tiempo en milisegundos espera-activa tras pintar
*				- int* pixelList_x : puntero array de posiciones X (filas) en pantalla
*				- int* pixelList_y : puntero array de posiciones Y (columnas) en pantalla
*				- unsigned char* pixelList_color : puntero array de colores para
*												   cada par X, Y a pintar en pantalla
* Valores retorno:
*				-  no return value
******************************************************************************/
void pintaListaPixeles(unsigned int numPixeles, unsigned char bgcolor, long int tiempoEspera, int* pixelList_x, int* pixelList_y, unsigned char* pixelList_color); 


//////////////////////////////////////////////////////////////////////////
///// -------------------------- MAIN ------------------------------ /////
//////////////////////////////////////////////////////////////////////////
int main( void ){
	// Declaracion de variables
	unsigned char opcion = 'e';
	unsigned char op_mov = 1;
	int pos_x = 0, pos_y = 0, tamano = 0;
	unsigned int num_pix_array = 1;
	int i = 1;
	char ret = 2;

	unsigned char color = 15;//color_fondo = 2;
	unsigned char color_fondo = 2;
	long int waitMS = 6000000;
	//int ArrayPixelesX[MAXPOINTS]={11,12,13,14,15,16,17,18,19,20,100}, ArrayPixelesY[MAXPOINTS]={21,22,23,24,25,26,27,28,29,30,31}; //ArrayPixeles[0] = X, ArrayPixeles[1] = Y
	//unsigned char ArrayColores[MAXPOINTS]={1,2,3,4,5,6,7,8,9,10,11};
	int ArrayPixelesX[MAXPOINTS]={0}, ArrayPixelesY[MAXPOINTS]={0}; 
	unsigned char ArrayColores[MAXPOINTS]={0};
	
	//Pinta instrucciones para usuario
	printf("Instrucciones generales:\n");
	printf(" - El modo video se configura para pantalla de 640x480\n");
	printf(" - Las posiciones X deberan estar en el rango [0, 640]\n");
	printf(" - Las posiciones Y deberan estar en el rango [0, 480]\n");
	printf(" - El rango de colores serán valores de 0 a 15\n\n");
	
	
	//Solicita una opcion al usuario
	printf("Elija la opcion que desea probar: \n");
	printf("a - pintar 1 pixel \n");
	printf("b - pintar 1 cuadrado  \n");
	printf("c - pintar varios pixeles \n");
	printf("d - pintar y mover un cuadrado \n");
	scanf("%c", &opcion);
	
	//Comprueba es una opcion valida del menu
	if (opcion >= 'a' && opcion <= 'd'){
		printf("-Opcion Elegida --> %c -\n",opcion);
	}else{
		printf("-Opcion %c: incorrecta fuera de [a,b,c,d]\n Bye\n",opcion);
		return ERR;
	}
	
	//Dependiendo de la opcion elegida ejecuta una funcion ensamblador u otra
	switch(opcion){
		
		
		//opcion pintar un pixel
		case 'a': 
				printf("Introduzca separado por espacios la posicion x e y del pixel a pintar seguido del color\n(e.g. 40 50 2): \n");
				scanf("%d %d %u", &pos_x, &pos_y, &color);
				ret = pintaPixel(color,pos_x, pos_y); //LLAMA A FUNCION EN ENSAMBLADOR
				if(ret == ERR)
					printf("Posicion pixel fuera de rango 640x480\n");
				break;
				
				
		//opcion pintar un cuadrado
		case 'b': 
				printf("Introduzca separado por espacios la posicion x e y del cuadrado a pintar seguido del tamano y color\n(e.g. 40 50 10 2): \n");
				scanf("%d %d %d %u", &pos_x, &pos_y, &tamano, &color);
				ret = pintaCuadrado(color, tamano, pos_x, pos_y);  //LLAMA A FUNCION EN ENSAMBLADOR
				//printf("Pixel %d %d %d %d %u\n",pos_x,pos_y,tam,tamano,color);
				if(ret == ERR)
					printf("Posicion pixel fuera de rango 640x480\n");
				break;	
				
				
		//opcion pintar un array de pixeles (que podría servir para pintar un fichero de texto con una imagen)
		case 'c': 
				printf("De 1 a %d, cuantos pixeles quiere pintar para su dibujo?\n", MAXPOINTS);
				scanf("%ud", &num_pix_array);
				if(num_pix_array > MAXPOINTS){
					printf("Error: Numero de elementos mayor que el maximo permitido\n");
					break;
				}
				for(i=0;i<num_pix_array;i++){
					//printf("%d. ",i+1);
					ArrayPixelesX[i] = i+11;
					ArrayPixelesY[i] = i+21;
					ArrayColores[i] = i % 16;
					printf("%d %d %d\n", ArrayPixelesX[i], ArrayPixelesY[i], ArrayColores[i]);
					printf("%d %d %d\n", ArrayPixelesX, ArrayPixelesY, ArrayColores);
				}
				printf("Introduzca color para el fondo (valor de 0 a 15): \n");
				scanf("%u", &color_fondo);
				// LLAMA A FUNCION ENSAMBLADOR PARA PINTAR LOS VECTORES DE PIXELES
				pintaListaPixeles(num_pix_array, color_fondo, waitMS, ArrayPixelesX, ArrayPixelesY, ArrayColores);   //LLAMA A FUNCION EN ENSAMBLADOR
				break;	
								
		//opcion pintar y mover un cuadrado
		/*case 'd': 
				printf("Instrucciones: Cuando se le solicite un movimiento, use las fechas del teclado numerico para mover el cuadrado\n");
				printf("       8      \n");
				printf("       ^      \n");
				printf("       |      \n");
				printf("4 <--- * ---> 6\n");
				printf("       |      \n");
				printf("       v      \n");
				printf("       2      \n\n");
				printf("0 cero para salir\n");
				printf("Introduzca separado por espacios la posicion x e y del cuadrado a pintar seguido del tamano y color\n(e.g. 40 50 10 2): \n");
				scanf("%d %d %d %u", &pos_x, &pos_y, &tamano, &color);
				if(ret == ERR){
					printf("Posicion pixel fuera de rango 640x480\n");
					break;
				}else{
					// BUCLE DO-WHILE para desplazar el cuadrado por la pantalla
					do{
						ret = pintaCuadrado(color,tamano, pos_x, pos_y);  //LLAMA A FUNCION EN ENSAMBLADOR
						//printf("%u: %u,%u\n",ret, pos_x,pos_y);
						
						printf("Realice movimiento (cero salir)\n               ");
						scanf("%c", &op_mov);
						//printf("\n");
						switch(op_mov){
							//izquierda
							case '4': 
									if(pos_x > (0+tamano))
										pos_x = pos_x - tamano;
									else pos_x = MAXCOL-1-tamano;
									printf("Case 4 - %c\n",op_mov);
									break;
							
							//arriba
							case '8': 
									if(pos_y>(0+tamano))
										pos_y = pos_y - tamano;
									else pos_y = MAXROW-1-tamano;
									printf("Case 8 - %c\n",op_mov);
									break;
							
							//derecha
							case '6': 
									if(pos_x<(MAXCOL-1-tamano))
										pos_x += tamano;
									else pos_x = 0+tamano;
									printf("Case 6 - %c\n",op_mov);
									break;
							
							//abajo						
							case '2': 
									if(pos_y<(MAXROW-1-tamano))
										pos_y += tamano;
									else pos_y = 0+tamano;
									printf("Case 2 - %c\n",op_mov);
							
							default: break;
											
						}// fin de switch(op_mov)
						
					}while(op_mov != '0'); //fin bucle do-while para desplazamiento
					
				} // fin de switch (*/
								
		default: break;
							
	} //fin de switch(opcion)
	
	return OK;
}