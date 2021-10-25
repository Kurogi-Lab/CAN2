#ifndef __calcAinvb__
#define __calcAinvb__

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix_double.h>
//#include <gsl/gsl_multimin.h>
#include <gsl/gsl_multiroots.h>
//#include "my_misc.c"
//#define GSL 1
#define GSL 1
int GSLtag;
void least_gsl_error_handler( const char * reason,
			      const char * file,
			      int line,
			      int gsl_errno)
{
  //  printf("%s:%d: %s (gsl_error: %s)\n", 
  //	 file, line, reason, gsl_strerror(gsl_errno));
  printf("%s:%d: %s (gsl_error %d)\n", 
	 file, line, reason,gsl_errno);
  GSLtag=1;
}
double VarY;
void calc_Ainvb(double *M, double *A_data, double *b_data, int nx, int ndata,int nxmarume)
{
  /* b= A M  --> M= Ainv b
     b  in R^{ndata x 1}
     A  in R^{ndata x nx}   (ndata>nx)
     M  in R^{nx    x 1}
   */
  int i;
  gsl_vector *S;
  gsl_vector *work;
  gsl_vector *x;
  gsl_vector *b;
  gsl_matrix *V;
  gsl_matrix *A;
  if(ndata<=0){
    M[0]=1;
    for(i=1;i<nx;i++) M[i]=1./nx;
  }
  else{
    A =gsl_matrix_alloc(ndata,nx);
    b =gsl_vector_alloc(ndata);b->data=b_data;
    A->data=A_data;  
    //  for(i=0;i<ndata;i++){printf("%e %e %d #bi,Ai\n",A->data[i],b->data[i],i); }
    
    V = gsl_matrix_alloc (nx,nx); 
    S = gsl_vector_alloc (nx); 
    work = gsl_vector_alloc(nx); 
    x = gsl_vector_alloc(nx); 
    
    gsl_set_error_handler( &least_gsl_error_handler );GSLtag=0;
    
#if GSL == 1
    gsl_linalg_SV_decomp_jacobi (A, V, S); //higer accuracy than Golub-Reinsh
#elif GSL == 2
    gsl_linalg_SV_decomp (A, V, S, work); //Golub-Reinsh
#elif GSL == 3
    {//faster
      gsl_matrix *X;
      X = gsl_matrix_alloc (nx,nx); 
      gsl_linalg_SV_decomp_mod (A, X, V, S, work); 
      gsl_matrix_free(X);
    }
#endif
    //    for(i=nxmarume;i<nx;i++){
    
    fprintf(stdout,"Lambda");
    for(i=0;i<nx;i++){
      //      if(nx>40) break;
      //      fprintf(stdout,"S->data[%d]=%e;",i,S->data[i]);
      fprintf(stdout,"(%d)%e",i,S->data[i]);
    }
    fprintf(stdout,"\n");
    VarY=0;
    if(GSLtag==1){
      fprintf(stderr,"\nEigenValue=");for(i=0;i<nx;i++) fprintf(stderr,"%e ",S->data[i]); fprintf(stderr,"\n");
      for(i=0;i<nx;i++) M[i]=1./nx;
    }
    else{
      if(nxmarume>=0){//Principal Component Analysis
	for(i=nxmarume;i<nx;i++) S->data[i]=0;
	for(i=0;i<nxmarume;i++) VarY+=S->data[i];
	gsl_linalg_SV_solve(A,V,S,b,x);
	for(i=0;i<nx;i++) M[i]=gsl_vector_get(x,i);
	//    {//check
	//      double err=0,yhat;
	//      int j;
	//      for(i=0;i<ndata;i++){
	//	if(i>10) break;
	//	yhat=b_data[i];
	//	for(j=0;j<nx;j++){
	//	  yhat-= M[j]*A_data[i*nx+j];
	//	}
	//	err+=square(yhat);
	//	fprintf(stderr,"err=%e=%e/%d. yhat=%e=(%e",err/(i+1.),err,i,yhat,b_data[i]);
	//	for(j=0;j<nx;j++) fprintf(stderr,"-(%e)*(%e)",M[j],A_data[i*nx+j]);
	//	fprintf(stderr,")^2\n");
	//      }
	//    }
      }
      else{//Minor Component Analysis
	int ii=0;
	int im=-nxmarume;
	for(i=nx-1;i>=0;i--){
	  if(S->data[i]>1e-20){
	    ii++;
	    VarY+=S->data[i];
	    if(ii>=im) break;
	  }
	}
	int j;

	double M0=-V->data[i];
	for(j=1;j<nx;j++){
	  M[j-1]=V->data[j*nx+i]/M0;
	}
//	double M0=-V->data[i*nx];
//	for(j=1;j<nx;j++){
//	  M[j-1]=V->data[i*nx+j]/M0;
//	}

      }
    }
    gsl_vector_free(S);
    gsl_vector_free(work);
    gsl_vector_free(x);
    gsl_matrix_free(V);
    gsl_matrix_free(A);
    gsl_vector_free(b);
  }
}
void calc_AtinvbMCA(double *M, double *At_data, double *b_data, int nx, int ndata,int nxmarume)
{ 
  /* b= A M  --> M= Ainv b
     b  in R^{ndata x 1}
     A=At  in R^{ndata x nx} 
     M  in R^{nx    x 1}
   */
  int nx1=nx+1,i,j,jnx1;
  gsl_matrix *A  =gsl_matrix_alloc(ndata,nx1);
  for(j=0;j<ndata;j++){
    jnx1=j*nx1;
    A->data[jnx1]=b_data[j];
    for(i=0;i<nx;i++){
      A->data[jnx1+i+1]=At_data[i*ndata+j];
    }
  }
  calc_Ainvb(M, (double *)(A->data), b_data, nx1, ndata, -nxmarume);
  
  gsl_matrix_free(A);
}
void calc_Atinvb(double *M, double *At_data, double *b_data, int nx, int ndata,int nxmarume)
{ 
  /* b= A M  --> M= Ainv b
     b  in R^{ndata x 1}
     A=At  in R^{ndata x nx} 
     M  in R^{nx    x 1}
   */
  gsl_matrix *At =gsl_matrix_alloc(nx,ndata);
  gsl_matrix *A  =gsl_matrix_alloc(ndata,nx);
  At->data=At_data;
  gsl_matrix_transpose_memcpy(A, At);
  calc_Ainvb(M, (double *)(A->data), b_data, nx, ndata, nxmarume);
  gsl_matrix_free(A);
  gsl_matrix_free(At);
}

#endif // __calcAinvb__
