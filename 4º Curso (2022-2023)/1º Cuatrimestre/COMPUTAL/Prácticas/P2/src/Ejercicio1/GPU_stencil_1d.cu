#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sys/time.h>
using namespace std;
#define RADIUS 3
//#define BLOCK_SIZE 16
int N = 16;
int BLOCK_SIZE = 16;


__global__ void stencil_1d(int *in, int *out, int N, int BLOCK_SIZE) {
  extern __shared__ int temp[/*BLOCK_SIZE + 2 * RADIUS*/];
  int gindex = threadIdx.x + blockIdx.x * blockDim.x;
  int lindex = threadIdx.x + RADIUS;


  // Read input elements into shared memory
  //solucionamos desbordes cuando n/block_size da un decimal
  if(gindex>=N) temp[lindex] = in[N-1]; else
  temp[lindex] = in[gindex];
  if (threadIdx.x < RADIUS) {
    
    // Resolvemos el problema de índices fuera de rango
    int in_index_ini = gindex - RADIUS;
    if(in_index_ini < 0){ //si desborda por la izq
      in_index_ini = 0;
    }

    int in_index_fin = gindex + BLOCK_SIZE;
    if(in_index_fin >= N){ //si desborda por la derecha
      in_index_fin = N-1;
    }

    temp[lindex - RADIUS] = in[in_index_ini];
    temp[lindex + BLOCK_SIZE] = in[in_index_fin];
  }
  
  // Synchronize (ensure all the data is available)
  __syncthreads();
  
  // Apply the stencil
  int result = 0;
    for (int offset = -RADIUS ; offset <= RADIUS ; offset++){
      result += temp[lindex + offset];
    }
  if(gindex>N)
    return;
  // Store the result
  out[gindex] = result;
}

void fill_ints(int *x, int n) {
  fill_n(x, n, 1);
}

int main(int argc, char *argv[]) {
  int N = 16;
  //int BLOCK_SIZE = 16;
  int size;
  int *in, *out;      // host copies of a, b, c
  int *d_in, *d_out;  // device copies of a, b, c
  struct timeval ini, fin;

  if(argc < 2){
    printf("insuficientes argumentos: ./exec N BLOCK_SIZE");
    return 0;
  }
  else{
    N = atoi(argv[1]);
    BLOCK_SIZE = atoi(argv[2]);
  }

  size = N * sizeof(int);

  // Alloc space for host copies and setup values
  in = (int *)malloc(size); fill_ints(in, N);
  out = (int *)malloc(size); fill_ints(out, N);

  // Alloc space for device copies
  cudaMalloc((void **)&d_in, size);
  cudaMalloc((void **)&d_out, size);

  // Copy to device
  cudaMemcpy(d_in, in, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_out, out, size, cudaMemcpyHostToDevice);

  // Launch stencil_1d() kernel on GPU
  gettimeofday(&ini,NULL);

  if(N%BLOCK_SIZE==0)
    stencil_1d<<<N/BLOCK_SIZE,BLOCK_SIZE, (BLOCK_SIZE + 2 * RADIUS)*sizeof(int)>>>(d_in, d_out, N, BLOCK_SIZE);
  else
    stencil_1d<<<N/BLOCK_SIZE+1,BLOCK_SIZE, (BLOCK_SIZE + 2 * RADIUS)*sizeof(int)>>>(d_in, d_out, N, BLOCK_SIZE);

  gettimeofday(&fin,NULL);

  printf("%d %f\n", N, ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
  
  // Copy result back to host
  cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);
/* debug
printf("\n");
  for (int i=0; i!=N; i++){
    printf(" %d", out[i]);
  }*/

  // Cleanup
  free(in); free(out);
  cudaFree(d_in); cudaFree(d_out);
  return 0;
}
