#include <stdlib.h>
#include <stdio.h>
//#include <x86intrin.h>
#include <immintrin.h>
#define ARRAY_SIZE 10
#define NUMBER_OF_TRIALS 1

/*
    MULTIPLOS DE 4
 * Statically allocate our arrays.  Compilers can
 * align them correctly.
 */
 //double = 8 bytes = 64 bits

static double a[ARRAY_SIZE], b[ARRAY_SIZE], c;
int main(int argc, char *argv[]) {
    int i,t;

    double m = 1.0001;

    /* Populate A and B arrays */
    asm("#populate");
    int dif=ARRAY_SIZE%4;
    for (i=0; i < ARRAY_SIZE-dif; i+=4) { //vamos de 4 en 4
        //b[i] = i;
        //a[i] = i+1;
        __m256d vb = {i, i+1, i+2, i+3}; //en 256 bits caben 4 double
        __m256d va = {i+1, i+2, i+3, i+4};
        _mm256_store_pd(&a[i], va);
        _mm256_store_pd(&b[i], vb);
    }

    for (i=ARRAY_SIZE-dif; i<ARRAY_SIZE; i++){
        a[i]=i+1;
        b[i]=i;
    }

    for(i=0; i!=12; i++){
        printf("%f ", a[i]);
    }
    printf("\n");
    for(i=0; i!=12; i++){
        printf("%f ", b[i]);
    }
    /* Perform an operation a number of times */
    asm("#operation");
    __m256d mm = {1.0001, 1.0001, 1.0001, 1.0001};
    for (t=0; t < NUMBER_OF_TRIALS; t++) {       
        for (i=0; i < ARRAY_SIZE-dif; i+=4) {
            //c += m*a[i] + b[i];
            __m256d sum = {0.0, 0.0, 0.0, 0.0}; // to hold partial sums
            // Load arrays
            __m256d va = _mm256_load_pd(&a[i]);
            __m256d vb = _mm256_load_pd(&b[i]);
            // Compute m*a+b
            __m256d tmp = _mm256_fmadd_pd (mm, va, vb);
            // Accumulate results
            sum = _mm256_add_pd (tmp, sum);
            /*Now sum holds summations of all products in four parts and we want a scalar result.*/
            for (int j = 0; j < 4; j++) {
                c += sum[j];
            }
            /*
              // Get sum[2], sum[3]
                __m128d xmm = _mm256_extractf128_pd (sum, 1);
                // Extend to 256 bits: sum[2], sum[3], 0, 0
                __m256d ymm = _mm256_castpd128_pd256(xmm);
                // Perform sum[0]+sum[1], sum[2]+sum[3], sum[2]+sum[3], 0+0
                sum = _mm256_hadd_pd (sum, ymm); 
                // Perform sum[0]+sum[1]+sum[2]+sum[3]…
                sum = _mm256_hadd_pd (sum, sum);
                c = sum[0]; 
             */
        }
        for (i=ARRAY_SIZE-dif; i<ARRAY_SIZE; i++){
            c+=m*a[i]+b[i];

        }
    }
    printf("%f\n", c);

    return 0;
}
