#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

int N=2048;
int P=8;

int index = 0;


//pthread_mutex_t mut[P]; 

typedef union u_tick {
  unsigned long long tick;
  struct {
    unsigned low;
    unsigned high;
  };
} tick_t;


#define GET_TICK(t)						\
  __asm__ volatile("rdtsc" : "=a" ((t).low), "=d" ((t).high))
#define TICK_DIFF(t1, t2)			\
  ((t2).tick - (t1).tick)



int (*fun)(int);



int get_index(){
  int ret;
  ret= index++;
  return ret;
}

int fcroissant (int i)
{

  volatile int s = 0,x;
  int max = i/4;
  for(x=0; x < max ; x++)
    {
      int y;
      for(y=0; y < max ; y++)
	s+=y;
    }
  return s;
}

int fpetit (int i)
{
  return 1;
}


int fconstant (int i)
{
  volatile int s = 0,x;
  int max = 50;
  for(x=0; x < max ; x++)
    {
      int y;
      for(y=0; y < max ; y++)
	s+=y;
    }
  return s;
}

int fperiodique (int i)
{
  volatile int s = 0,x;
  int max = i%200;
  if (max<2)
    max=5000;

  for(x=0; x < max ; x++)
    {
      int y;
      for(y=0; y < max ; y++)
	s+=y;
    }
  return s;
}


long long sequentiel()
{
  int i;
  tick_t t1,t2;

  GET_TICK(t1);

  for(i=0; i< N; i++)
    fun(i);

  GET_TICK(t2);
  
  return TICK_DIFF(t1,t2);
}

void *cyclique(void *param)
{
  int i, a = (intptr_t)param;
  for(i=a; i<N;i += P)
    fun(i);
  
  return NULL;
}

void *bloc(void *param)
{

  int i, a = (intptr_t)param;
  for(i=a; i<a+a*N/P; ++i)
    fun(i);
  
  return NULL;
}

void *dynamique(void *param)
{

  int i;
  while((i=get_index()) < N){
    fun(i);
  }

  return NULL;
}


long long lance(void *(thread_fun)(void *param))
{
  tick_t t1,t2;
  pthread_t t[P];
  int i;
  GET_TICK(t1);

  for(i=0; i<P; ++i)
    pthread_create(&t[i], NULL, fun, (void*)(intptr_t)i);

  for(i=0; i<P; ++i)
    pthread_join(t[i], NULL);
  
  GET_TICK(t2);
  
  return TICK_DIFF(t1,t2);
}

void benchmark(char *s)
{
  float f, b,c,d;

  printf("%s (P=%d, N=%d)\n",s, P, N);

  f = ((float)sequentiel())/1000000;
  printf("sequentiel: \t%.3f Mcycles\n",f);

  b = ((float)lance(bloc))/1000000;
  printf("bloc:   \t%.3f Mcycles\t accélération %.1f\n",b,f/b);
  
  c = ((float)lance(cyclique))/1000000;
  printf("cyclique: \t%.3f Mcycles\t accélération %.1f\n",c,f/c);
  
  d = ((float)lance(dynamique))/1000000;
  printf("dynamique: \t%.3f Mcycles\t accélération %.1f\n",d,f/d);
}

int main(int argc, char **argv){	

  if(argc != 2)
    {
      fprintf(stderr,"%s nbthreads\n",argv[0]);
      exit(1);
    }
  
  P=atoi(argv[1]);
  int i;
  pthread_mutex_t mut[P];
  for(i=0; i<P; ++i)
    mut[i] = PTHREAD_MUTEX_INITIALIZER;
  
  
  fun = fpetit;
  benchmark("    PETIT");

  fun = fconstant;
  benchmark("    CONSTANT");

  fun = fcroissant;
  benchmark("    CROISSANT"); 
  
  fun = fperiodique;
  benchmark("    PERIODIQUE"); 
  
  return 0;
}
