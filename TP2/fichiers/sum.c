#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <malloc.h>
#include <sys/time.h>

/* macro de mesure de temps, retourne une valeur en �secondes */
#define TIME_DIFF(t1, t2) \
        ((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))

int 
main(int argc, char *argv[]) 
{
  struct timeval t1, t2;
  int i, sum;
  int taille = 1024 * 1024 * 10;
  int *tab = malloc(taille * sizeof(int));
  unsigned long temps;

  srand(1);

  for (i=0; i<taille;i++)
    tab[i] = rand();

  sum = 0;
  gettimeofday(&t1,NULL);

  // version s�quentielle
  for (i=0; i<taille;i++)
    sum += tab[i];

  gettimeofday(&t2,NULL);
  
  temps = TIME_DIFF(t1,t2);
  printf("seq  = %ld.%03ldms\t sum = %u\n", temps/1000, temps%1000, sum);

  sum = 0;
  gettimeofday(&t1,NULL);

  omp_lock_t lock;
  omp_init_lock(&lock);
  
  // premiere technique, TODO
#pragma omp parallel for schedule(static)
  for (i=0; i<taille;i++){
    omp_set_lock(&lock);
    sum += tab[i];
    omp_unset_lock(&lock);
  }
  gettimeofday(&t2,NULL);
  
  temps = TIME_DIFF(t1,t2);
  printf("1ere = %ld.%03ldms\t sum = %u\n", temps/1000, temps%1000, sum);


  sum = 0;
  gettimeofday(&t1,NULL);

  // deuxi�me technique, TODO
#pragma omp parallel for
  for (i=0; i<taille;i++)
#pragma omp critical
    sum += tab[i];

  gettimeofday(&t2,NULL);
  
  temps = TIME_DIFF(t1,t2);
  printf("2eme = %ld.%03ldms\t sum = %u\n", temps/1000, temps%1000, sum);


  sum = 0;
  gettimeofday(&t1,NULL);

   // autre technique, TODO
#pragma omp parallel for reduction (+:sum)
  for (i=0; i<taille;i++){
    //#pragma omp atomic
    sum += tab[i];
  }
  gettimeofday(&t2,NULL);

  temps = TIME_DIFF(t1,t2);
  printf("3eme = %ld.%03ldms\t sum = %u\n", temps/1000, temps%1000,sum);

  return 0;
}
