#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define RADIUS 3
int BLOCK_SIZE = 16;
int N = 16;

void stencil_1d(int *in, int *out, int N, int block, int thread) {
  //int temp[BLOCK_SIZE + 2 * RADIUS];
  int gindex = thread + block * BLOCK_SIZE;
  if(gindex>N)
    return;
  // Read input elements into shared memory
  /*temp[lindex] = in[gindex];
  if (threadIdx.x < RADIUS) {
    
    // Resolvemos el problema de índices fuera de rango
    int in_index_ini = gindex - RADIUS;
    if(in_index_ini < 0){
      in_index_ini = 0;
    }

    int in_index_fin = gindex + BLOCK_SIZE;
    if(in_index_fin >= N){
      in_index_fin = N-1;
    }

    temp[lindex - RADIUS] = in[in_index_ini];
    temp[lindex + BLOCK_SIZE] = in[in_index_fin];
  }*/
  
  // Apply the stencil
  int result = 0;
    for (int offset = -RADIUS ; offset <= RADIUS ; offset++){
      int ind = gindex + offset;
      if(ind<0){
        ind=0;
      }else if(ind>=N){
        ind=N-1;
      }
      result += in[ind];
    }

  // Store the result
  out[gindex] = result;
}

void fill_ints(int *x, int n) {
  fill_n(x, n, 1);
}

int main(int argc, char *argv[]) {
  int N = 16;
  
  int size;
  int *in, *out;      // host copies of a, b, c
  int *d_in, *d_out;  // device copies of a, b, c
  struct timeval ini, fin;

  if(argc < 3){
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

  gettimeofday(&ini,NULL);
  for(int i = 0; i <= N/BLOCK_SIZE; i++) //lanza estos bloques
    for(int j = 0; j < BLOCK_SIZE; j++) //lanza los threads
      stencil_1d(in, out, N, i, j);

  gettimeofday(&fin,NULL);


  printf("%d %f\n", N, ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);

/* debug
printf("\n");
  for (int i=0; i!=N; i++){
    printf(" %d", out[i]);
  }*/

  // Cleanup
  free(in); free(out);
  return 0;
}
