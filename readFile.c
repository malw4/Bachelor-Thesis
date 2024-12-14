#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "structures.h"

struct Wpis *readFile(){
  int ilosc,i;
  struct Wpis *wpisy = (struct Wpis*)malloc(NONZ * sizeof(struct Wpis));
  for(i=0;i<NONZ;i++){
    wpisy[i].col=0;
    wpisy[i].row=0;
    //wpisy[i].value=1.0;
  }
  //printf("%d\n",sizeof(struct Wpis *));
  FILE* f = NULL;
  if(FILENR==1) f = fopen("fileS.txt", "r");
  if(FILENR==2) f = fopen("bc30.txt", "r");
  if(FILENR==3) f = fopen("fileM37.txt", "r");
  if(FILENR==4) f = fopen("file.txt", "r");
  if (f == NULL) {
    //printf("Nie mozna otworzyc pliku.\n");
    exit(1);
  }
  else {
    for (ilosc = 0; ilosc < NONZ; ilosc++) { //pętla po wartościach niezerowych
      int c, r;
      double v;
      fscanf(f, "%d", &r);
      fscanf(f, "%d", &c); 
      
      if(FILENR==2) v = 1.0; // bc30.txt
      else fscanf(f, "%lf", &v); // all files except
      
      struct Wpis wpis;
      wpis.col = c;
      wpis.row = r;
      wpis.value = v;
      wpisy[ilosc] = wpis;
    }
  }
  
  fclose(f);//zamknięcie pliku
  printf(" readFile zamknalem plik\n");
  return wpisy;
}

