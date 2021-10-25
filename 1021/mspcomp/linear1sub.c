/////////////////
//example25.5.c
/////////////////
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <math.h>

typedef struct{
  double *a; //y=a[0]x[0]+a[1]x[1]+...a[ka]y[ka]+b[0]u[0]+b[1]u[1]+...+b[kb]u[kb]
  //  double *a; //y[t+1]=a[0]y[t]+a[1]y[t-1]+...a[ka]y[t-ka]+b[0]u[t]+b[1]u[t-1]+...+b[kb]u[t-kb]
  double *b;
  double *x;
  double *u;
  int k,kx,ku;
  double xmax;
  double umax;
  double y;
  int _dim;
  double *_y;
  double *_y_err;
  //  double *_dydt_in;
  //  double *_dydt_out;
  double h;
  double _t;
} LINEAR;

//#define dim_linear 4
//int linearfunc (double t, const double y[], double f[], void *params)
//{
//  LINEAR *c = (LINEAR *)params;
//  f[0] = y[1];
//  f[1] = (-(2*c->dr+c->C)*y[1] -c->ddX*cos(y[0]) -c->g*sin(y[0]))/c->r;
//  f[2] = y[3];  
//  f[3] = (c->F+c->T*sin(y[0]))/c->M;
//  return GSL_SUCCESS;
//}
////////////////
#define square(x) ((x)*(x))
LINEAR linear;
int PLANT_NO=1;
int initialize()
{
  if(PLANT_NO==1){
    linear.kx=1;
    linear.ku=1;
    linear.k=linear.kx+linear.ku;
    linear.a=(double*)malloc(sizeof(double)*linear.k);
    linear.b=&linear.a[linear.kx];
    linear.x=(double*)malloc(sizeof(double)*linear.k+1);
    linear.u=&linear.x[linear.kx];
    
    linear.a[0]=0.9;
    linear.b[0]=1;
  }
  else if(PLANT_NO==2){
    linear.kx=3;
    linear.ku=1;
    linear.k=linear.kx+linear.ku;
    linear.a=(double*)malloc(sizeof(double)*linear.k);
    linear.b=&linear.a[linear.kx];
    linear.x=(double*)malloc(sizeof(double)*linear.k+1);
    linear.u=&linear.x[linear.kx];
    
    linear.a[0]=1;
    linear.a[1]=1;
    linear.a[2]=1;
    linear.b[0]=1;
  }
  linear.umax=6.0;//check//  linear.Fmax=30;//check
  int i;for(i=0;i<linear.kx;i++) linear.x[i]=0;
#ifdef LINEARSUB
  //  linear.Fmax=_linear_Fmax;//check//  linear.Fmax=30;//check
  //  linear.xmax=20.0;//check//  linear.Fmax=30;//check
  if(_AP_umax>0) AP_u_max=linear.umax=_AP_umax;
  else AP_u_max=linear.umax;

  AP_u_min=-AP_u_max;
  rr=AP_r=_AP_r;//10
  rr_kyoyou=_rr_kyoyou;
  C_MODE=11;
#else
  linear.h=0.01;
#endif
  linear._t=0;
  //  int i;for(i=0;i<linear._dim;i++) linear._dydt_in[i]=0;

  return(0);
}
#ifndef LINEARSUB
char *fn="linear2io.dat";
FILE *fp;
#endif//#ifndef LINEARSUB

double plant(double uu)
{
  //store previous x and u
  int i;
  for(i=0;i<linear.kx-1;i++) linear.x[i+1]=linear.x[i];
  for(i=0;i<linear.ku-1;i++) linear.u[i+1]=linear.u[i];
  //store former output
  linear.x[0]=linear.y;

  //current input
  if(uu>linear.umax) linear.u[0]=linear.umax;  
  else if(uu<-linear.umax) linear.u[0]=-linear.umax;
  else linear.u[0]=uu;
  // current output
  linear.y=0;
  for(i=0;i<linear.k;i++) linear.y+=linear.a[i]*linear.x[i];
  linear._t++;

  //  fprintf(stdout,"y%g=(%g)*(%g)+(%g)*(%g) %g %g %g\n",linear.y,linear.a[0],linear.x[0],linear.a[1],linear.x[1],uu,linear.u[0],linear.x[1]);

#ifndef LINEARSUB
  fprintf(fp,"%g %g %g %g", linear._t,linear.y,linear.u[0],linear.x[0]);//linear.a,linear.da
  //  fprintf(fp,"%.7e %.7e %.7e %.7e", linear._t,linear.y,linear.x[0],linear.u[0]);//linear.a,linear.da
  fprintf(fp,"\n");
#endif
  return(linear.y);
  //  return(linear.X);
}

#ifndef LINEARSUB
int main()
{
  ////////////////////////////////////////////////////
  /// method 1                                     ///
  /// input ddX                                    ///
  /// output a,x,y,F                               ///
  ////////////////////////////////////////////////////
  //  double h = 0.001;//,hh=0.1; h = 0.0001;//,hh=0.1;
  double t0=5;     //stationary 
  double t1=5.0+t0;//accelerate(speed up)
  double t2=2.0+t1;//free run
  double t3=5.0+t2;//decelerate(slow down)
  double t4=20+t3;   //free run

  initialize();
  linear.h=1;
  int M=(t4/linear.h)+1;
  double *uu=(double*)malloc(sizeof(double)*M);
  double uumax=20;//

  int n;
  double t;
  ////////////////////////////////////////////////////
  ///   set ddX                                    ///
  ////////////////////////////////////////////////////
  int n0 =t0/linear.h+0.5, n4=t4/linear.h+0.5;
  for(t=0;t<t4;t+=linear.h){
    n=t/linear.h;
    if(t<=t0) uu[n]=0; //zero
    else if(t<=t1) uu[n]=uumax/(t1-t0); //accelerate
    else if(t<=t2) uu[n]=0;            //free move
    else if(t<=t3) uu[n]=-uumax/(t3-t2);//decelerate
    else uu[n]=0;                      //free move
    //    fprintf(stdout,"uu[%d]=%e\n",n,uu[n]);
  }
  ////////////////////////////////////////////////////
  ///   Solve by the Runge Kutta Method of GSL     ///
  ////////////////////////////////////////////////////
  fp=fopen(fn,"w");
  fprintf(fp,"#%.7e %d %d %.7e %.7e %.7e %.7e #h,n0,n4,a[0]-a[3]\n",linear.h,n0,n4,linear.a[0],linear.a[1],linear.a[2],linear.a[3]);
  fprintf(fp,"#t,y,x,u\n");
  for(t=0;t<t4;t+=linear.h){
    n=t/linear.h;
    plant(uu[n]);
  }
  fclose(fp);
  fprintf(stdout,"Results are stored in '%s'.\n",fn);

  return 0;
}

#endif //#ifndef SUB
