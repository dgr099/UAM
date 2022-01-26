#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../include/arqo3.h"
//no es necesario que devuelva nada
//las dos matrices a multiplicar, la matriz donde guardar el resultado y su tam
void mul(tipo **matrix1, tipo **matrix2,tipo **matrix3, int n);

int main(int argc, char**argv){
    int n;
	tipo **m1=NULL;
    tipo **m2=NULL;
    tipo **m3=NULL;
    struct timeval fin,ini;
    if(argc!=2){ //si no se introduce el tamaño de la matriz retorna error
        printf("Error: ./%s <matrix size>\n", argv[0]);
		return -1;
    }
    n=atoi(argv[1]);
	m1=generateMatrix(n);
	if( !m1 )
	{
		return -1;
	}
    m2=generateMatrix(n);
	if( !m2 )
	{
        freeMatrix(m1);
		return -1;
	}
    m3=generateEmptyMatrix(n);
	if( !m3 )
	{
        freeMatrix(m1);
        freeMatrix(m2);
		return -1;
	}
    gettimeofday(&ini,NULL);
    mul(m1,m2, m3, n);
    gettimeofday(&fin,NULL);
    printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(m3);

}

void mul(tipo **matrix1, tipo **matrix2,tipo **matrix3, int n){
    if(n<=0){
        return;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            matrix3[i][j]=0; //inicializamos a 0 la posición
            for(int z=0; z<n; z++){
                matrix3[i][j]+=matrix1[i][z]*matrix2[z][j];
            }
        }
    }
}