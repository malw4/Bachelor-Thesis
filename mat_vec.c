#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

void mat_vec(double* a, double* x, double* y,long int nn,long int nt){
  
  //printf("a %lu, x %lu, y %lu, nn %d, nt %d\n", a, x, y, nn, nt);
  
  register long int i;
  //#pragma omp parallel num_threads(nt) 
#pragma omp parallel default(none) firstprivate(a,x,y,nn,i)
  {
    register long int k=0;
    register long int n=nn;
    register long int i;
    register long int j;
    
    //#pragma omp parallel for firstprivate(n) private(j)
#pragma omp for
    for(i=0;i<n;i++){
      double t=0.0;
      long int ni = n*i;
      for(j=0;j<n;j++){
	//t+=a[ni+j]*x[j];
	//printf("i %d, j %d, a[%d] %20.15lf x %lf, y[%ld] = %lf \n",
	//       i,j,ni+j,a[ni+j],x[j],y[i]);
	t+=a[ni+j]*x[j];
	y[i]=t;
      }
    }
    
    /*#pragma omp for
      for(i=0;i<n;i+=4){
      register double ty1 = 0;
      register double ty2 = 0;
      register double ty3 = 0;
      register double ty4 = 0;
      for(j=0;j<n;j+=2){
      register double t0=x[j];
      register double t1=x[j+1];
      register long int n2=2*n;
      register long int n3=3*n;
      k=i*n+j;
      ty1+=a[k]*t0+a[k+1]*t1;
      ty2+=a[k+n]*t0+a[k+1+n]*t1;
      ty3+=a[k+n2]*t0+a[k+1+n2]*t1;
      ty4+=a[k+n3]*t0+a[k+1+n3]*t1;
      }
      y[i]=ty1;
      y[i+1]+=ty2;
      y[i+2]+=ty3;
      y[i+3]+=ty4;
      }*/
    
  }
  //for(i=0;i<nn;i++)
  //printf("y[%ld] = %lf \n",i,y[i]);
}

