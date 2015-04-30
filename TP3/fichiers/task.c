#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int f()
{
  
  int i;
  int k = 100 + omp_get_thread_num() ;
  
#pragma omp single nowait
  for(i = 0; i < 10 ; i++)
#pragma omp task shared(k) firstprivate(i)
    {
      printf("DEB %d [k : %d] pour %d \n",i,k,omp_get_thread_num());
      sleep(1);
      printf("FIN %d [k : %d] pour %d \n",i,k,omp_get_thread_num());
    }

  //#pragma omp taskwait
}



int main()
{

#pragma omp parallel
  {
    f();
    printf("%d fin \n", omp_get_thread_num());
  }
}
  
