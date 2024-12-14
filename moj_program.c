#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "pomiar_czasu.h"
#include "structures.h"

//wymiary macierzy z pliku .mtx 16614 1091362
//testowaæ z -g do debugu

void mat_vec(double* a, double* x, double* y, long int n, long int nt);
void mat_vec_crs(double* x, double* y, struct CSR csr, long int n, long int nt);
void mat_vec_csc(double* x, double* y, struct CSC csc, long int n, long int nt);
void mat_vec_sell(double* x, double* y, struct Sell sell, long int nn,long int nt);
void mat_vec_vector(double *x,double* y,struct Sell sell,long int nt);
struct Sell csrToSell(struct Sell sell,struct CSR CSR);
struct CSR cooToCsr(struct CSR csr, struct Wpis *wpisy);
struct CSC cooToCsc(struct CSC csc,struct Wpis *wpisy);
struct Wpis *readFile();

int main() {	
  struct Wpis *wpisy;
  struct Sell sell;
  struct CSR csr;
  struct CSC csc;
  static double x[WYMIAR], y[WYMIAR], z[WYMIAR], y_csr[WYMIAR],y_csc[WYMIAR],  y_sell[WYMIAR];
  double* a = (double*)malloc(ROZMIAR * sizeof(double));
  
  double t1;
  long int n, i, j, k;
  long int ilosc = 0, row_sum = 1;
  const long int ione = 1;
  const double done = 1.0;
  const double dzero = 0.0;
  
  
  for (i = 0; i < WYMIAR; i++) x[i] = 0.1 * (WYMIAR - i); //inicjowanie x[]
  for (i = 0; i < ROZMIAR; i++) a[i] = 0.0; //inicjowanie a[]
  
  printf("\njestem przed read\n");
  //inicjuj_czas();
  wpisy=readFile();
  //drukuj_czas();
  printf("\nprzepisanie do csr\n");
  //inicjuj_czas();
  csr=cooToCsr(csr,wpisy);
  //drukuj_czas();
  printf("\nprzepisanie do csc\n");
 // inicjuj_czas();
  csc=cooToCsc(csc,wpisy);
 // drukuj_czas();
  printf("\nprzepisanie do  sell\n");
 // inicjuj_czas();
  sell=csrToSell(sell,csr);
 // drukuj_czas();
  
  printf("\nprzepisanie do formatu standardowego\n");
  inicjuj_czas();
  for(k=0;k<NONZ;k++){
    i=csr.row_ind[k];
    j=csr.col_ind[k];
    a[i*WYMIAR+j]=csr.a_csr[k];
    //printf("%d, %d ->  %lf  ,",i,j,a[i*WYMIAR+j]);
  }	
  drukuj_czas();
  
  n = WYMIAR;
  
  printf("\nObliczenie wartosci referenceyjnych\n");
  // test
  //  printf("TEST\n");
  
  inicjuj_czas();
  t1 = omp_get_wtime();
  //#pragma omp parallel for firstprivate(n) private(j) 
  for (i = 0; i < n; i++) {
    double t = 0.0;
    long int ni = n * i;
    for (j = 0; j < n; j++) {
      t += a[ni + j] * x[j];
      //printf("%d, %d -> y %lf,  a %lf  ,  x %lf\n",i,j,t,a[ni+j],x[j]);
    }
    z[i] = t;
  }
  t1 = omp_get_wtime() - t1;
  drukuj_czas();
  
  int fake = 0;
  
  //nt = 8;
  //printf("Podaj liczbe watkow: "); scanf("%d",&nt);
  
  for (i = 0; i < WYMIAR; i++) y[i] = 0.0;
  
  printf("\nPoczatek procedury macierz-wektor: rozmiar macierzy %ld (%ldx%ld)\n",
	 ROZMIAR, WYMIAR, WYMIAR);
  inicjuj_czas();
  t1 = omp_get_wtime();
  mat_vec(a, x, y, n, fake);
  //printf("po matve");
  t1 = omp_get_wtime() - t1;
  drukuj_czas();
  
  
  printf("\nKoniec procedury macierz-wektor\n");
  printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",
	 t1, 2.0e-9 * ROZMIAR / t1, (1.0 + 1.0 / n) * 8.0e-9 * ROZMIAR / t1);
  
  printf("\nSprawdzenie poprawnosci\n");
  for (i = 0; i < WYMIAR; i++) {
    // printf("%d %lf %lf\n",  i, y[i], z[i]); getchar();
    if (fabs(y[i] - z[i]) > 1.e-5 * fabs(z[i]))
      printf("Blad! bo fabs(y[%ld]=%20.15lf-z[%ld]=%20.15lf)=%20.15lf a fabs(1.e-5*z[i])=%20.15lf\n", i, y[i], i, z[i], fabs(y[i] - z[i]), 1.e-5 * fabs(z[i]));
    
  }
  
  
  printf("\nPoczatek procedury macierz-wektor CRS: rozmiar macierzy %ld (%ldx%ld)\n",
	 ROZMIAR, WYMIAR, WYMIAR);
  
  for (i = 0; i < WYMIAR; i++) y_csr[i] = 0.0;
  
  inicjuj_czas();
  t1 = omp_get_wtime();
  mat_vec_crs( x, y_csr, csr, n, fake);
  t1 = omp_get_wtime() - t1;
  drukuj_czas();
  
  
  printf("\nKoniec procedury macierz-wektor\n");
  printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",
	 t1, 2.0e-9 * NONZ / t1, (1.0 + 1.0 / n) * 8.0e-9 * NONZ / t1);
  
  printf("\nSprawdzenie poprawnosci\n");
  for (i = 0; i < WYMIAR; i++) {
    // printf("%d %lf %lf\n",  i, y_csr[i], z[i]); getchar();
    if (fabs(y_csr[i] - z[i]) > 1.e-5 * fabs(z[i]))
      printf("Blad! bo fabs(y_csr[%ld]=%20.15lf-z[%ld]=%20.15lf)=%20.15lf a fabs(1.e-5*z[i])=%20.15lf\n", i, y_csr[i], i, z[i], fabs(y_csr[i] - z[i]), 1.e-5 * fabs(z[i]));
  }

  
  printf("\nPoczatek procedury macierz-wektor CSC: rozmiar macierzy %ld (%ldx%ld)\n",
	 ROZMIAR, WYMIAR, WYMIAR);
  
  for (i = 0; i < WYMIAR; i++) y_csc[i] = 0.0;
  
  inicjuj_czas();
  t1 = omp_get_wtime();
  mat_vec_csc( x, y_csc, csc, n, fake);
  t1 = omp_get_wtime() - t1;
  drukuj_czas();
  
  
  printf("\nKoniec procedury macierz-wektor\n");
  printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",
	 t1, 2.0e-9 * NONZ / t1, (1.0 + 1.0 / n) * 8.0e-9 * NONZ / t1);
  
  printf("\nSprawdzenie poprawnosci\n");
  for (i = 0; i < WYMIAR; i++) {
    // printf("%d %lf %lf\n",  i, y_csc[i], z[i]); getchar();
   // if (fabs(y_csc[i] - z[i]) > 1.e-4 * fabs(z[i]))
    //  printf("Blad! bo fabs(y_csc[%ld]=%20.15lf-z[%ld]=%20.15lf)=%20.15lf a fabs(1.e-5*z[i])=%20.15lf\n", i, y_csc[i], i, z[i], fabs(y_csc[i] - z[i]), 1.e-5 * fabs(z[i]));
    
  }
  
  
  
  printf("\nPoczatek procedury macierz-wektor SELL: rozmiar macierzy %ld (%ldx%ld)\n",
	 ROZMIAR, WYMIAR, WYMIAR);
  
  for (i = 0; i < WYMIAR; i++) y_sell[i] = 0.0;
  
  inicjuj_czas();
  t1 = omp_get_wtime();
  mat_vec_sell( x, y_sell,sell, n, fake);
  t1 = omp_get_wtime() - t1;
  drukuj_czas();
  
  
  printf("\nKoniec procedury macierz-wektor\n");
  printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",
	 t1, 2.0e-9 * NONZ / t1, (1.0 + 1.0 / n) * 8.0e-9 * NONZ / t1);
  
   printf("\nSprawdzenie poprawnosci\n");
 
  for (i = 0; i < WYMIAR; i++) {
    //printf("%d %lf %lf\n",  i, y_sell[i], z[i]);
    if (fabs(y_sell[i] - z[i]) > 1.e-5 * fabs(z[i]))
      printf("Blad! bo fabs(y_sell[%ld]=%20.15lf-z[%ld]=%20.15lf)=%20.15lf a fabs(1.e-5*z[i])=%20.15lf\n", i, y_sell[i], i, z[i], fabs(y_sell[i] - z[i]), 1.e-5 * fabs(z[i]));
    
  }
  
  printf("\nPoczatek procedury macierz-wektor SELL wektorowy: rozmiar macierzy %ld (%ldx%ld)\n",
	 ROZMIAR, WYMIAR, WYMIAR);
  
  for (i = 0; i < WYMIAR; i++) y_sell[i] = 0.0;
  
  inicjuj_czas();
  t1 = omp_get_wtime();
  mat_vec_vector( x, y_sell,sell, fake);
  t1 = omp_get_wtime() - t1;
  drukuj_czas();
  
  
  printf("\nKoniec procedury macierz-wektor\n");
  printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n",
	 t1, 2.0e-9 * NONZ / t1, (1.0 + 1.0 / n) * 8.0e-9 * NONZ / t1);
  
   printf("\nSprawdzenie poprawnosci\n");
 
  for (i = 0; i < WYMIAR; i++) {
    //printf("%d %lf %lf\n",  i, y_sell[i], z[i]);
    if (fabs(y_sell[i] - z[i]) > 1.e-5 * fabs(z[i]))
      printf("Blad! bo fabs(y_sell[%ld]=%20.15lf-z[%ld]=%20.15lf)=%20.15lf a fabs(1.e-5*z[i])=%20.15lf\n", i, y_sell[i], i, z[i], fabs(y_sell[i] - z[i]), 1.e-5 * fabs(z[i]));
    
  }
}
