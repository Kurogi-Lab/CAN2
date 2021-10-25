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
  double *_dydt_in;
  double *_dydt_out;
  double _t;
} CRANE;

#define dim_crane 4
int cranefunc (double t, const double y[], double f[], void *params)
{
  CRANE *c = (CRANE *)params;
  f[0] = y[1];
  f[1] = (-(2*c->dr+c->C)*y[1] -c->ddX*cos(y[0]) -c->g*sin(y[0]))/c->r;
  f[2] = y[3];  
  f[3] = (c->F+c->T*sin(y[0]))/c->M;
  return GSL_SUCCESS;
}
////////////////
#define square(x) ((x)*(x))
CRANE crane;
int initialize()
{
  crane.kx=3;
  crane.ku=1;
  crane.k=crane.kx+ku;
  double *a=(double*)malloc(sizeof(double)*ka);
  double *b=&a[kx];
  double *x=(double*)malloc(sizeof(double)*k+1);
  double *u=&x[kx];
  crane.umax=20.0;//check//  crane.Fmax=30;//check

#ifdef CRANESUB
  //  crane.Fmax=_crane_Fmax;//check//  crane.Fmax=30;//check
  //  crane.xmax=20.0;//check//  crane.Fmax=30;//check
  if(_AP_umax>0) AP_u_max=crane.umax=_AP_umax;
  else AP_u_max=crane.umax;

  AP_u_min=-AP_u_max;
  rr=AP_r=_AP_r;//10
  rr_kyoyou=_rr_kyoyou;
  C_MODE=11;
#else
  crane.h=0.01;
#endif
  crane._t=0;
  int i;for(i=0;i<crane._dim;i++) crane._dydt_in[i]=0;

  return(0);
}
#ifndef CRANESUB
char *fn="crane2io.dat";
FILE *fp;
#endif//#ifndef CRANESUB

double plant(double uu)
{
  //store previous x and u
  int i,kx_1=crane.kx-1;
  for(i=0;i<kx_1;i++) crane.x[i+1]=crane.x[i];
  int ku_1=crane.ku-1;
  for(i=0;i<ku_1;i++) crane.u[i+1]=crane.u[i];
  //store former output
  crane.x[0]=crane.y;

  //current input
  if(uu>crane.umax) crane.u[0]=crane.umax;  
  else if(uu<-crane.umax) crane.u[0]=-crane.umax; 
  // current output
  crane.y=0;
  for(i=0;i<crane.k;i++) crane.y+=crane.a[i]*crane.x[i];
  crane._t++;

#ifndef CRANESUB
  fprintf(fp,"%.7e %.7e %.7e %.7e", crane._t,crane.u[0],crane.x[0],crane.y);//crane.a,crane.da
  fprintf(fp,"\n");
#endif
  return(crane.x);
  //  return(crane.X);
}

#ifndef CRANESUB
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
  int M=(t4/crane.h)+1;
  double *ddX=(double*)malloc(sizeof(double)*M);
  //  double *F  =(double*)malloc(sizeof(double)*M);
  double Vmax=1;//dX/dt=1[m/s]

  int n;
  double t;
  ////////////////////////////////////////////////////
  ///   set ddX                                    ///
  ////////////////////////////////////////////////////
  int n0 =t0/crane.h+0.5, n4=t4/crane.h+0.5;
  for(t=0;t<t4;t+=crane.h){
    n=t/crane.h;
    if(t<=t0) ddX[n]=0; //zero
    else if(t<=t1) ddX[n]=Vmax/(t1-t0); //accelerate
    else if(t<=t2) ddX[n]=0;            //free move
    else if(t<=t3) ddX[n]=-Vmax/(t3-t2);//decelerate
    else ddX[n]=0;                      //free move
  }
  ////////////////////////////////////////////////////
  ///   Solve by the Runge Kutta Method of GSL     ///
  ////////////////////////////////////////////////////
  fp=fopen(fn,"w");
  fprintf(fp,"#%.7e %d %d %.7e %.7e %.7e %.7e #h,n0,n4,M,n,r\n",crane.h,n0,n4,crane.M,crane.m,crane.r,crane.C);
  //  double dx0=0,dy0=0,da0=0;
  //  for(n=0;n<n4;){
  for(t=0;t<t4;t+=crane.h){
    n=t/crane.h;
    plant(ddX[n]);
  }
  fclose(fp);
  fprintf(stdout,"Results are stored in '%s'.\n",fn);

  gsl_odeiv_step_free (crane._s);
  return 0;
}

#ifndef CRANESUB
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
  int M=(t4/crane.h)+1;
  double *ddX=(double*)malloc(sizeof(double)*M);
  //  double *F  =(double*)malloc(sizeof(double)*M);
  double Vmax=1;//dX/dt=1[m/s]

  int n;
  double t;
  ////////////////////////////////////////////////////
  ///   set ddX                                    ///
  ////////////////////////////////////////////////////
  int n0 =t0/crane.h+0.5, n4=t4/crane.h+0.5;
  for(t=0;t<t4;t+=crane.h){
    n=t/crane.h;
    if(t<=t0) ddX[n]=0; //zero
    else if(t<=t1) ddX[n]=Vmax/(t1-t0); //accelerate
    else if(t<=t2) ddX[n]=0;            //free move
    else if(t<=t3) ddX[n]=-Vmax/(t3-t2);//decelerate
    else ddX[n]=0;                      //free move
  }
  ////////////////////////////////////////////////////
  ///   Solve by the Runge Kutta Method of GSL     ///
  ////////////////////////////////////////////////////
  fp=fopen(fn,"w");
  fprintf(fp,"#%.7e %d %d %.7e %.7e %.7e %.7e #h,n0,n4,M,n,r\n",crane.h,n0,n4,crane.M,crane.m,crane.r,crane.C);
  //  double dx0=0,dy0=0,da0=0;
  //  for(n=0;n<n4;){
  for(t=0;t<t4;t+=crane.h){
    n=t/crane.h;
    plant(ddX[n]);
  }
  fclose(fp);
  fprintf(stdout,"Results are stored in '%s'.\n",fn);

  gsl_odeiv_step_free (crane._s);
  return 0;
}
#endif //#ifndef SUB
