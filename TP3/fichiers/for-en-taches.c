#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>

static int i =0;
int main()
{
#pragma omp parallel shared (i) num_threads(20)  
  {
    //int i;
    //#pragma omp for schedule(dynamic)

#pragma omp single 
    {
      for(i = 0; i < 20 ; i++)
	{
#pragma omp task
	  printf("%d par %d \n",i, omp_get_thread_num());
	  //	i++;
	}
    }
    
    printf("%d fin \n", omp_get_thread_num());
  } 
}


  
