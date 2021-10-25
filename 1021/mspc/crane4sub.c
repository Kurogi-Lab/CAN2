/////////////////
//example25.5.c
/////////////////
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <math.h>

typedef struct{
  double g;//gravity
  double M;//mass of the car
  double m;//mass of the load
  double r;//length of the rope
  double k;//spring constant
  double C;//damping coefficient

  double F;//input force proportional to torque
  double T;//tension to the rope
  //  double FF;//Fictitious force

  double x,x0;//x position of the load
  double y,y0;//y position of the load
  double X;//X position of the car
  double a;//angle (theta)

  double dx,dx0;
  double dy,dy0;
  double dX,dX0;
  double dr;
  double da,da0;

  double ddx;
  double ddy;
  double ddX;
  double ddr;
  double dda;
  double dXmax;
  double ddXmax;
  double Fmax;//Force

  double h;
  int nh;
  double _h;
  int _dim;
  double *_y;
  double *_y_err;
  double *_dydt_in;
  double *_dydt_out;
  const gsl_odeiv_step_type *_T;
  gsl_odeiv_step *_s;
  gsl_odeiv_system _sys;
  double _t;
} CRANE;

#define dim_crane 4
int cranefunc (double t, const double y[], double f[], void *params)
{
  CRANE *c = (CRANE *)params;
  //#define ICONIP2014
#ifdef ICONIP2014 //wrong dynamics
  f[0] = y[1];
  f[1] = -c->k*(y[0]-y[2])/c->m - c->C*(y[1]-y[3])/c->m;//iconip2014
  f[2] = y[3];  
  f[3] = (c->k*(y[0]-y[2]) + c->F)/c->M;//iconip2014
#else //corrected dynamics
  f[0] = y[1];
  f[1] = (-c->k*(y[0]-y[2]) - c->C*(y[1]-y[3]))/c->m;//iconip2014
  f[2] = y[3];  
  f[3] = (c->k*(y[0]-y[2]) + c->C*(y[1]-y[3]) + c->F)/c->M;//iconip2014
#endif

//  f[0] = y[1];
//  f[1] = -c->k*y[0]/c->m - c->C*y[1]/c->m - c->ddX;
//  f[2] = y[3];  
//  f[3] = (c->k*y[0] + c->F)/c->M;
//
//  f[0] = y[1];
//  f[1] = -c->k*y[0]/c->m - c->C*y[1]/c->m - c->ddX;
//  f[2] = y[3];  
//  f[3] = (c->k*y[0] + c->F)/c->M;
//
//  f[0] = y[1];
//  f[1] = (-(2*c->dr+c->C)*y[1] -c->ddX*cos(y[0]) -c->g*sin(y[0]))/c->r;
//  f[2] = y[3];  
//  f[3] = (c->F+c->T*sin(y[0]))/c->M;
  return GSL_SUCCESS;
}
////////////////
#define square(x) ((x)*(x))
CRANE crane;
int initialize()
{
  
  crane.Fmax=30;//check  crane.Fmax=20.0;//check//  
  //  crane.dXmax=1.0;
  crane.dXmax=1.0;
  crane.ddXmax=0.2;
  crane.g=9.8;
  crane.M=100;
  //  crane.m=20;//10;//10;//20
  crane.r=5;//5;
  crane.C=10;//5;
  crane.k=15;//
  crane.dr=crane.ddr=0;
  crane.x0=0;
  crane.y0=crane.r;
  crane.dX0=crane.dx0=crane.dy0=crane.da0=0;
#ifdef CRANESUB
  //  crane.Fmax=_crane_Fmax;//check//  crane.Fmax=30;//check
  crane.h=AP_tS;
  crane.m=_crane_m;
  crane.r=_crane_r;
  crane.C=_crane_C;
  crane.k=_crane_k;//
  crane.dXmax=_crane_dXmax;
  if(_AP_umax>0) AP_u_max=crane.Fmax=_AP_umax;
  else AP_u_max=crane.Fmax;
  AP_u_min=-AP_u_max;
  rr=AP_r=_AP_r;//10
  rr_kyoyou=_rr_kyoyou;
  C_MODE=11;
#else
  crane.h=0.01;
#endif
  crane.nh=10;
  crane.F=crane.a=crane.da=crane.dda=0;
  crane.T=crane.m*crane.g;
  crane._h=crane.h/crane.nh;//0.001
  crane._dim=4;
  if(crane._y==NULL){
    crane._y=(double*)malloc(crane._dim*sizeof(double));
    crane._y_err=(double*)malloc(crane._dim*sizeof(double));
    crane._dydt_in=(double*)malloc(crane._dim*sizeof(double));
    crane._dydt_out=(double*)malloc(crane._dim*sizeof(double));
  }
  crane._T= gsl_odeiv_step_rk4;//?
  crane._s= gsl_odeiv_step_alloc (crane._T, crane._dim);
  crane._sys= (gsl_odeiv_system){cranefunc, NULL, crane._dim, &crane};
  crane._t=crane._y[0]=crane._y[1]=crane._y[2]=crane._y[3]=0;
  //  crane.FF=0;

  int i;for(i=0;i<crane._dim;i++) crane._dydt_in[i]=0;
  GSL_ODEIV_FN_EVAL(&(crane._sys), crane._t, crane._y, crane._dydt_in);
  return(0);
}
#ifndef CRANESUB
char *fn="crane4io.dat";
FILE *fp;
#endif//#ifndef CRANESUB

double plant(double uu)
{
  //  crane.F=uu;
  if(uu>crane.Fmax) uu=crane.Fmax;  
  else if(uu<-crane.Fmax) uu=-crane.Fmax; 
  int n;
  for(n=0;n<crane.nh;n++){
    crane.F=uu;//
    if(crane.dX>=crane.dXmax && crane.F>0) crane.F=0;
    else if(crane.dX<=-crane.dXmax && crane.F<0) crane.F=0;
    int status = gsl_odeiv_step_apply (crane._s, crane._t, crane._h, 
				       crane._y, crane._y_err, 
				       crane._dydt_in, 
				       crane._dydt_out, 
				       &crane._sys);
    if (status != GSL_SUCCESS)   break;
    
    int i;for(i=0;i<dim_crane;i++) crane._dydt_in[i]=crane._dydt_out[i];
    crane._t+=crane._h;

    crane.x  =crane._y[0];//
    crane.dx =crane._y[1];
    crane.X  =crane._y[2];
    crane.dX =crane._y[3];

    //    crane.x  =crane.X+crane.a; //output y
    //    crane.dx=(crane.x-crane.x0)/crane._h;
    //    crane.x  =crane.X+crane.r * sin(crane.a);
    //    crane.y  =crane.r*cos(crane.a);
    //    crane.dy=(crane.y-crane.y0)/crane._h;
    crane.ddx=(crane.dx-crane.dx0)/crane._h;
    //    crane.ddy=(crane.dy-crane.dy0)/crane._h;
    //    crane.T=crane.m*sqrt(square(crane.ddx)+square(crane.ddy-crane.g));
    crane.ddX=(crane.dX-crane.dX0)/crane._h;
    //    crane.FF=-crane.ddX;
    //    crane.F=crane.M*crane.ddX-crane.T*sin(crane.a);
    //    crane.dda=(crane.da-crane.da0)/crane._h;
    crane.x0=crane.x;
    //    crane.y0=crane.y;
    crane.dx0=crane.dx;
    //    crane.dy0=crane.dy;
    //    crane.da0=crane.da;
    crane.dX0=crane.dX;
  }
#ifndef CRANESUB
  fprintf(fp,"%.7e %.7e %.7e", crane._t,crane._y[0],crane._y[1]);//crane.x,crane.dx
  fprintf(fp," %.7e %.7e %.7e" ,crane.X,crane.dX,crane.ddX);
  fprintf(fp," %.7e %.7e %.7e" ,crane.x,crane.dx,crane.ddx);
  fprintf(fp," %.7e %.7e %.7e" ,crane.y,crane.dy,crane.ddy);
  fprintf(fp," %.7e %.7e" ,crane.T,crane.F);
  fprintf(fp,"\n");
#endif
  return(crane.x);
  //  return(crane.X);
}

#ifndef CRANESUB
#ifndef use_crane3io
int main (int argc,char **argv)
{
  //  CRANE crane;
  crane.dr=crane.ddr=0;

  ////////////////////////////////////////////////////
  /// method 2                                     ///
  /// input F                                     ///
  /// output p,x,y,X,...                          ///
  ////////////////////////////////////////////////////
  double h;//,hh=0.1;
  //result for different h
  /*gnuplot
   set style data lines;n=1;
   n=n+1;plot "crane3io.dat" using 1:n, "crane4io.dat" using 1:n;print "n=",n
   #strange at n=9(ddx),12(ddy),13(T)
  */
  ////////////////////////////////////////////////////
  ///   read F                                    ///
  ////////////////////////////////////////////////////
  crane.C=10;
  crane.k=15;
  crane.M=100;
  crane.m=10;
  crane.h=0.01;
  double T=5;
  double t0=0;     //stationary 
  double t1=T+t0;//accelerate(speed up)
  double t2=T+t1;//free run
  double t3=T+t2;//decelerate(slow down)
  double t4=t0+50;   //free run
  int i;
  for(i=1;i<argc;i++){
    if(strncmp(argv[i],"m:",2)==0){
      sscanf(&argv[i][2],"%lf",&crane.m);
    }
  }
  initialize();
  fprintf(stderr,"#C:%g K:%g M:%g m:%g\n",crane.C,crane.k,crane.M,crane.m);

  int n0 =t0/crane.h+0.5, n4=t4/crane.h+0.5;
  int M=(t4/crane.h)+1;
  double *F=(double*)malloc(sizeof(double)*M);
  double t;
  double umax=10;
  int n;
  for(t=0;t<t4;t+=crane.h){
    double u;
    n=t/crane.h;
    if(t<=t0) u=0; //zero
    else if(t<=t1) u=umax*0.8; //accelerate
    else if(t<=t2) u=0;            //free move
    else if(t<=t3) u=-umax*0.8;//decelerate
    else u=0;                      //free move
    F[n]=u;//??
  }
  //  double x0=0,y0=crane.r;

  ////////////////////////////////////////////////////
  ///   Solve by the Runge Kutta Method of GSL     ///
  ////////////////////////////////////////////////////
  fp=fopen(fn,"w");
  for(t=0;t<t4;t+=crane.h){
    n=t/crane.h;
    plant(F[n]);
  }
  fclose(fp);
  fprintf(stdout,"Results are stored in '%s'.\n",fn);

  gsl_odeiv_step_free (crane._s);
  return 0;
}
#else //ifdef crane3io
int main (void)
{
  //  CRANE crane;
  crane.dr=crane.ddr=0;

  ////////////////////////////////////////////////////
  /// method 2                                     ///
  /// input F                                     ///
  /// output p,x,y,X,...                          ///
  ////////////////////////////////////////////////////
  double h;//,hh=0.1;
  //result for different h
  /*gnuplot
   set style data lines;n=1;
   n=n+1;plot "crane3io.dat" using 1:n, "crane4io.dat" using 1:n;print "n=",n
   #strange at n=9(ddx),12(ddy),13(T)
  */
  ////////////////////////////////////////////////////
  ///   read F                                    ///
  ////////////////////////////////////////////////////
  char *fn1="crane3io.dat";
  FILE *fp1=fopen(fn1,"r");
  int n4;
#define buffsize 512
  char buff[buffsize];
  int n0;
  fgets(buff,buffsize,fp1);
  sscanf(buff,"#%lf%d%d%lf%lf%lf%lf",&h,&n0,&n4,&crane.M,&crane.m,&crane.r,&crane.C);
  crane.h=h;
  double t4=n4*h;
  double *F  =(double*)malloc(sizeof(double)*(n4+1));
  //  int M=n4+1;double *F  =(double*)malloc(sizeof(double)*M);
  //  double *ddX=(double*)malloc(sizeof(double)*M);
  
  int n;
  double t;
  //  double dx0=0,dy0=0,dX0=0,da0=0;
  //  double x0=0,y0=crane.r;

  fgets(buff,buffsize,fp1);
  for(n=0;n<n4;n++){//
    double _x1,_x2,_x3,_x4,_x5,_x6,_x7,_x8,_x9,_x10,_x11,_x12,_x13,_x14;
    fgets(buff,buffsize,fp1);
    sscanf(buff,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
	   &_x1,&_x2,&_x3,&_x4,&_x5,&_x6,&_x7,&_x8,&_x9,&_x10,&_x11,&_x12,&_x13,&_x14);
    F[n]=_x14;
  }
  ////////////////////////////////////////////////////
  ///   Solve by the Runge Kutta Method of GSL     ///
  ////////////////////////////////////////////////////
  initialize();
  fp=fopen(fn,"w");
  for(t=0;t<t4;t+=crane.h){
    n=t/crane.h;
    plant(F[n]);
  }
  fclose(fp);
  fprintf(stdout,"Results are stored in '%s'.\n",fn);

  gsl_odeiv_step_free (crane._s);
  return 0;
}
#endif
#endif
