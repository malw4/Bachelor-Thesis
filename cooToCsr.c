#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "structures.h"

struct CSR cooToCsr(struct CSR CSR, struct Wpis *wpisy){
  CSR.a_csr = (double*)malloc(NONZ * sizeof(double));
  CSR.row_ptr = (int*)malloc((WYMIAR + 1) * sizeof(int));
  CSR.col_ind = (int*)malloc(NONZ * sizeof(int));
  CSR.row_ind = (int*)malloc(NONZ * sizeof(int));
  int i,j, ilosc=0,k ,row_sum=1;
  int pomptr[2];
  
  for(i=0; i<WYMIAR+1; i++){
    CSR.row_ptr[i]=0;
  }
  for(i=0;i<NONZ;i++){
    CSR.col_ind[i]=0;
    CSR.row_ind[i]=0;
    CSR.a_csr[i]=0.0;
  }
  //obliczanie i zapis do ptr
  for (ilosc = 0; ilosc < NONZ; ilosc++) {
    int wiersz = wpisy[ilosc].row;
    CSR.row_ptr[wiersz] ++;
  }
  
  for (i = 1; i <= WYMIAR; i++) {
    CSR.row_ptr[i] += CSR.row_ptr[i-1]; 
  }	
  
  k = 0;
  for(i = 0; i <= WYMIAR; i++){
    for (j = 0; j < NONZ; j++) {
      if(wpisy[j].row == i){
	CSR.row_ind[k]=i-1;
	CSR.col_ind[k]=wpisy[j].col-1;
	CSR.a_csr[k]=wpisy[j].value;
	k++;
      }
    }
    //if(i%100==0)
    //printf("jestem w i=%d \n",i);
  }
		
		//wypisanie wartosci row_ptr
	/*printf("row_ptr=[");
	for (i = 0; i < (WYMIAR + 1); i++) 
		printf("  %d  ", CSR.row_ptr[i]);	
	printf("]\n");
	printf("\n");
		/*printf("row_ind=[");
	for (i = 0; i < NONZ; i++) 
		printf("  %d  ", CSR.row_ind[i]);	
	printf("]\n");
	printf("\n");
	printf("col_ind=[");
	for (i = 0; i < NONZ; i++) 
		printf("  %d  ", CSR.col_ind[i]);	
	printf("]\n");
	printf("\n");
	printf("val=[");
	for (i = 0; i < NONZ; i++) 
		printf("  %.1lf  ", CSR.a_csr[i]);	
	printf("]\n");
	printf("\n");*/
  printf("skonczylem csr\n");
   
  return CSR;
}
