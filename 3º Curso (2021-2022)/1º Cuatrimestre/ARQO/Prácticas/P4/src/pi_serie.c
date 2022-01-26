/*********************************************************/
/*C�lculo PI: M�todo de integraci�n - Version secuencial */
/*********************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) 
{ 
	int i, n = 100000000;
	double x, h, pi, sum = 0.0, t = 0;
	struct timeval t1,t2;

	gettimeofday(&t1,NULL);
	
	h = 1.0/(double) n;
	for (i=1;i<= n; i++)
	{
		x = h*(i-0.5); // h*i - h/2
		//f(x) = 4/(1+x²)
		sum += 4.0/(1.0+x*x);
	}
	//h es una constante sale fuera del sumatorio
	pi = h * sum;

	gettimeofday(&t2,NULL);

	t = (t2.tv_sec -t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/(double)1000000;
	printf("Resultado pi: %f\nTiempo %lf\n", pi, t);
		
	return 0;
}
