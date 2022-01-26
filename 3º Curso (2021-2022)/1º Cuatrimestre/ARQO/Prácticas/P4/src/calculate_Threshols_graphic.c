// ----------- Arqo P4-----------------------
// pescalar_par1
// ¿Funciona correctamente?
//
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/arqo4.h"
#include <math.h>
#define NCiclos 100.0
int main(void)
{
	int flag=-1;
	int nproc;
	float *A=NULL, *B=NULL;
	long long k=0;
	struct timeval fin,ini,fin1, ini1, fin2, ini2;
	double sum=0;
    int a=0;
	FILE *f=NULL;
	if(!(f=fopen("data_Thresholds.dat", "w"))){
		printf("Error apertura de fichero de datos");
		return 0;
	}
    while(1){
		//los hacemos de mayor tamaño para que sirvan en mas de un cálculo
		printf("probando con %d\n", a);
		A = generateVectorOne(ceil(a*1.2));
		B = generateVectorOne(ceil(a*1.2));

		if ( !A || !B )
		{
			printf("Error when allocationg matrix\n");
			freeVector(A);
			freeVector(B);
			return -1;
		}
		
			nproc=omp_get_num_procs();
			omp_set_num_threads(nproc);   
		float tim1=0;
		float tim2=0;
		float tim3=0;
		for(int i=0;i!=NCiclos;i++){
			gettimeofday(&ini,NULL);
			// primero calculamos el tiempo en serie
			sum = 0;
			for(k=0;k<a;k++)
			{
				sum = sum + A[k]*B[k];
			}
			gettimeofday(&fin,NULL);
			
			//despues en paralelo
			//primero para 0.8 de a
			gettimeofday(&ini1,NULL);
			sum = 0;
			int d=ceil(0.8 * a);
        	#pragma omp parallel for reduction(+:sum)
			for(k=0;k<d;k++){
				sum = sum + A[k]*B[k];
			}
			gettimeofday(&fin1,NULL);

			//ahora para 1.2 de a
			gettimeofday(&ini2,NULL);
			sum = 0;
			d=ceil(1.2 * a);
        	#pragma omp parallel for reduction(+:sum)
			for(k=0;k<d;k++){
				sum = sum + A[k]*B[k];
			}
			gettimeofday(&fin2,NULL);
			//vamos sumando los tiempos parciales
			tim1+=((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0;
			tim2+=((fin1.tv_sec*1000000+fin1.tv_usec)-(ini1.tv_sec*1000000+ini1.tv_usec))*1.0/1000000.0;
			tim3+=((fin2.tv_sec*1000000+fin2.tv_usec)-(ini2.tv_sec*1000000+ini2.tv_usec))*1.0/1000000.0;

		}
		//hacemos la media de los 20 resultados
		tim1/=NCiclos;
		tim2/=NCiclos;
		tim3/=NCiclos;
		fprintf(f, "%d\t%.8f\t%.8f\t%.8f\n", a, tim1, tim2, tim3);
		if(tim1<tim2 && tim1>tim3 && tim1!=tim2 && tim1!=tim3 && tim2!=tim3){
			/*printf("Valor de Thresholds: %d\n", a);
			freeVector(A);
			freeVector(B);
			return(0);*/
			printf("Threshold: %d\n", a);
			flag=0;
		}
		if(flag>=0){
			flag++;
			if(flag==11){
				freeVector(A);
				freeVector(B);
				fclose(f);
				return(0);
			}
		}
		a+=1;
	}
	return 0;
}
