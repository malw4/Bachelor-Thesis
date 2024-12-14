#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "structures.h"


void mat_vec_csc(double* x, double* y,struct CSC csc,long int nn,long int nt){
  register long int i;
	//int j;
//	 #pragma omp parallel 
#pragma omp parallel default(none) firstprivate(x,y,csc,nn,i) // num_threads(nt)
	{
	 double* ylocal = malloc(nn * sizeof(double));
	 register long int pom;
   register long int n=nn;
   register long int j;
   register long int x0;
   //#pragma omp for
   for(i=0;i<n;i++){
		 //printf("%d\n",i);
			long int edge=csc.col_ptr[i+1]-1;
			for(j=csc.col_ptr[i];j<=edge;j++){
				x0=csc.row_ind[j];
				ylocal[x0]+=csc.a_csc[j] * x[i];
			}
    }
		#pragma omp critical(y)
		for(i=0;i<n;i++)
			y[i]+=ylocal[i];
	}
//for(i=0;i<nn;i++)
	//printf("y[%ld] = %lf \n",16612,y[16612]);
//printf("y[%ld] = %lf \n",16613,y[16613]);
}

