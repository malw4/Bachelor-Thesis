#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "structures.h"

struct CSC cooToCsc(struct CSC CSC,struct Wpis *wpisy){
  CSC.a_csc = (double*)malloc(NONZ * sizeof(double));
  CSC.col_ptr = (int*)malloc((WYMIAR + 1) * sizeof(int));
  CSC.col_ind = (int*)malloc(NONZ * sizeof(int));
  CSC.row_ind = (int*)malloc(NONZ * sizeof(int));
  int i,ilosc=0,k=0,row_sum=1;
  int pomptr[2];
  
  for(i=0; i<WYMIAR+1; i++){
    CSC.col_ptr[i]=0;
  }
  for(i=0;i<NONZ;i++){
    CSC.col_ind[i]=0;
    CSC.row_ind[i]=0;
    CSC.a_csc[i]=0.0;
  }
  
  
  //obliczanie i zapis do ptr
  for (ilosc = 0; ilosc < NONZ; ilosc++) {
    int wiersz = wpisy[ilosc].col;
    CSC.col_ptr[wiersz] ++;
  }
  
  for (i = 1; i <= WYMIAR; i++) {
    CSC.col_ptr[i] += CSC.col_ptr[i-1]; 
  }	
  
  
  
  for(i=1;i<=WYMIAR;i++){
    for (ilosc = 0; ilosc < NONZ; ilosc++) {
      if(wpisy[ilosc].col==i){
	CSC.row_ind[k]=wpisy[ilosc].row -1;
	CSC.col_ind[k]=i-1;
	CSC.a_csc[k]=wpisy[ilosc].value;
	k++;
      }
    }
  }
  
		//wypisanie wartosci row_ptr
	/*printf("col_ptr=[");
	for (i = 0; i < (WYMIAR + 1); i++) 
		printf("  %d  ", CSC.col_ptr[i]);	
	printf("]\n");
	printf("\n");
		printf("row_ind=[");
	for (i = 0; i < NONZ; i++) 
		printf("  %d  ", CSC.row_ind[i]);	
	printf("]\n");
	printf("\n");/*
	printf("col_ind=[");
	for (i = 0; i < NONZ; i++) 
		printf("  %d  ", CSC.col_ind[i]);	
	printf("]\n");
	printf("\n");
	printf("val=[");
	for (i = 0; i < NONZ; i++) 
		printf("  %.1lf  ", CSC.a_csc[i]);	
	printf("]\n");
	printf("\n");*/
  printf("skonczylem csc\n");
  
  return CSC;
}
