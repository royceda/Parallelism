#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>


int
main()
{
  int i,j;
  double x=0;

#pragma omp parallel for schedule(static)
  
  for(i=0; i < 100; i++)
    {
      /* calcul bidon plus ou moins lourd */
      x = 100000 * fabs(cos(i*i));
      //le temps de calcul augmente avec i
      
      for(j=0;j<100+i*20000;j++)
        x += sqrt(sqrt(543*j)*fabs(sin(j)));
      printf("%d traite %2d [%g]\n",omp_get_thread_num(),i,x);
    }
}
