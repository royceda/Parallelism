#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef union u_tick {
  unsigned long long tick;
  struct {
    unsigned low;
    unsigned high;
  }z;
} tick_t;

#define GET_TICK(t) \
	   __asm__ volatile("rdtsc" : "=a" ((t).z.low), "=d" ((t).z.high))
#define TICK_DIFF(t1, t2) \
	   ((t2).tick - (t1).tick)

#define N 128
#define N1 1024
#define N2 1280

typedef long matrix[N][N1][N2];

long int diff[N], resultat[N];

matrix film;

void fillmatrix(matrix A) {
  int i,j,n,r;
  for (i=0;i<N1;i++)
    for (n=1;n<N;n++)
      
      for (j=0;j<N2;j++)
	{
	  r = random()&1;
	  A[n][i][j] = A[n-1][i][j] + r;
	  resultat[n] += r;
	}
}

void difference(){
  for(int i=0; i < N1; i++)
    #pragma omp parallel for
    for(int n=1; n < N; n++)
   
      for(int j=0; j < N2; j++){
#pragma omp critical
	//if (film[n-1][i][j] != film[n][i][j])
	diff[n] += (film[n-1][i][j] != film[n][i][j]);
      }
}


void check()
{
  for(int n=1; n < N-1; n++)
    if (diff[n] != resultat[n])
      {
	printf("erreur pour %d\n",n);
	exit(1);
      }
}

int main(void) {
  tick_t t1,t2;
  
  fillmatrix(film);
  
  GET_TICK(t1);
  difference();
  GET_TICK(t2);
  check();
  printf("%.3f Mcycles\n",((float)TICK_DIFF(t1,t2))/1000000);
  
  return 0;
}
