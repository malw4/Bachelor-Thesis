#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include "structures.h"

void mat_vec_sell(double* x, double* y_global, struct Sell sell, long int nn, long int nt) {
  register long int i;
  
#pragma omp parallel default(none) firstprivate(x,y_global,sell,nn,i) // num_threads(nt) 
  {
    register long int n = nn;
    register long int j;
    register long int pom;
    register long int x0;
    int k;
    int wyn = sell.nr_slice;
    
    // pêtla po blokach wierszy
#pragma omp for 
    for (i = 0; i < wyn; i++) {
      
      // pêtla po kolumnach w i-tym bloku wierszy
      for (j = 0; j < sell.cl[i]; j++) {
	for(k=0;k<C;k++){
	  pom = sell.sliceStart[i] + j * C + k;
	  x0 = sell.slice_col[pom];
	  y_global[i * C + k] += sell.val[pom] * x[x0];
	}
      }
    }
  }
  
  //printf("y[%ld] = %lf \n",16612,y[16612]);
  //printf("y[%ld] = %lf \n",16613,y[16613]);
}
