#ifndef __calcAinvb__
#define __calcAinvb__
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_multiroots.h>
#define GSL 2
int GSLtag;
void least_gsl_error_handler( const char * reason,
			      const char * file,
			      int line,
			      int gsl_errno)
{
  fprintf(stderr,"%s:%d: %s (gsl_error %d)\n",  file, line, reason,gsl_errno);
  GSLtag=1;
}

#define ZERO (1e-10)
double VarY;
int calcAinvb1(double *x_data, double *A_data, double *b_data, int nx, int ndata)
{
  /* 
    b= A x  --> x= Ainv b
     b  in R^{ndata x 1}
     A  in R^{ndata x nx}   (ndata>nx)
     x  in R^{nx    x 1}
   */
  int i;
  
  if(ndata<=0){
    x_data[0]=1;
    for(i=1;i<nx;i++) x_data[i]=1./nx;
  }
  else{
    gsl_matrix *A =gsl_matrix_alloc(ndata,nx);
    gsl_vector *b =gsl_vector_alloc(ndata);
    gsl_matrix *V = gsl_matrix_alloc (nx,nx); 
    gsl_vector *S = gsl_vector_alloc (nx); 
    gsl_vector *work = gsl_vector_alloc(nx); 
    gsl_vector *x = gsl_vector_alloc(nx); 
    A->data=A_data;  
    b->data=b_data;
    x->data=x_data;
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
    VarY=0;
    if(GSLtag==1){
      fprintf(stderr,"\nError:EigenValue=");
      for(i=0;i<nx;i++) fprintf(stderr,"%e ",S->data[i]); fprintf(stderr,"\n");
      for(i=0;i<nx;i++) x_data[i]=1./nx;
    }
    else{
      int i,j,l;
      double *Si=(double*)malloc(sizeof(double)*nx);
      double *Ai=(double*)malloc(sizeof(double)*nx*ndata);
      for(i=0;i<nx;i++) if(S->data[i]>1e-10) Si[i]=1./S->data[i]; else Si[i]=0;
      for(i=0;i<nx;i++){
	for(j=0;j<ndata;j++){
	  double *Ai_ij=&Ai[i*ndata+j];
	  Ai_ij[0]=0;
	  for(l=0;l<nx;l++) Ai_ij[0]+=V->data[i*nx+l]*Si[l]*A->data[j*nx+l];
	}
      }
      //      for(i=0;i<nx;i++) x->data[i]=0;
      x->data[0]=0;for(j=0;j<nx;j++) x->data[0]+=Ai[j]*b->data[j];
//      int check=0;
//      if(check){
//	gsl_linalg_SV_solve(A,V,S,b,x);
//	double xi;
//	for(i=0;i<nx;i++){
//	  xi=0;
//	  for(j=0;j<nx;j++) xi+= Ai[i*ndata+j]*b->data[j];
//	  fprintf(stderr,"x[%d]=%g =?= %g\n",i,xi,x->data[i]);
//	}
//	fprintf(stderr,"p:");
//	for(i=0;i<nx;i++){
//	  fprintf(stderr,"\n p(i%d,*):",i);
//	  for(j=0;j<nx;j++){
//	    fprintf(stderr,"%+.3f ",Ai[i*nx+j]);
//	  }
//	}
//	fprintf(stderr,"\n:");
//	fprintf(stderr,"check\n");
//      }
      free(Si);
      free(Ai);
    }
    gsl_vector_free(S);
    gsl_vector_free(work);
    gsl_vector_free(x);
    gsl_matrix_free(V);
    gsl_matrix_free(A);
    gsl_vector_free(b);
  }
  return 0;
}
int calc_Ainvb(double *x_data, double *A_data, double *b_data, int nx, int ndata,int nxmarume)
{
  /* 
    b= A x  --> x= Ainv b
     b  in R^{ndata x 1}
     A  in R^{ndata x nx}   (ndata>nx)
     x  in R^{nx    x 1}
   */
  int i;
  
  if(ndata<=0){
    x_data[0]=1;
    for(i=1;i<nx;i++) x_data[i]=1./nx;
  }
  else{
    gsl_matrix *A =gsl_matrix_alloc(ndata,nx);
    gsl_vector *b =gsl_vector_alloc(ndata);
    //A->data=A_data;  
    //	b->data=b_data;
    {
      int n=ndata*nx;
	for(i=0;i<n;i++){
	  A->data[i]=A_data[i];
	}
	for(i=0;i<ndata;i++) b->data[i]=b_data[i];
    }

    gsl_matrix *V = gsl_matrix_alloc (nx,nx); 
    gsl_vector *S = gsl_vector_alloc (nx); 
    gsl_vector *work = gsl_vector_alloc(nx); 
    gsl_vector *x = gsl_vector_alloc(nx); 
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
    VarY=0;
    if(GSLtag==1){
      fprintf(stderr,"\nError:EigenValue=");for(i=0;i<nx;i++) fprintf(stderr,"%e ",S->data[i]); fprintf(stderr,"\n");
      for(i=0;i<nx;i++) x_data[i]=1./nx;
    }
    else{
      if(nxmarume>=0){//Principal Component Analysis
	for(i=0;i<nxmarume;i++) VarY+=S->data[i];
	for(i=nxmarume;i<nx;i++) S->data[i]=0;
	gsl_linalg_SV_solve(A,V,S,b,x);
	for(i=0;i<nx;i++) x_data[i]=gsl_vector_get(x,i);
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
	  x_data[j-1]=V->data[j*nx+i]/M0;
	}
      }
    }
    gsl_vector_free(S);
    gsl_vector_free(work);
    gsl_vector_free(x);
    gsl_matrix_free(V);
    gsl_matrix_free(A);
    gsl_vector_free(b);
  }
  //  fprintf(stderr,"OK");
  return 0;
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
