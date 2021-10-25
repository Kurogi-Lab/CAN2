#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <math.h>
#ifndef CRANESUB
char *fn1="crane1io.dat";
char *fn2="crane2io.dat";
FILE *fp;
#endif//#ifndef CRANESUB
typedef struct{
  double g;//gravity
  double M;//mass of the car
  double m;//mass of the load
  double r;//length of the rope
  double C;//damping coefficient

  double F;//input force
  double T;//tension to the rope

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
  //  int *initialize;
  int (*cranefunc)();
  double (*plant)();
  //int (*p) (int num);    /* 関数ポインタpを宣言 */
} CRANE;

#define dim_crane 4
//double ddXn;//for check
int crane1func (double t, const double y[], double f[], void *params)
{
  CRANE *c = (CRANE *)params;
  //y[0]=crane->p, y[1]=crane->dp, y[2]=crane->X, y[3]=crane->dX
  f[0] = y[1];
  f[1] = (-(2*c->dr+c->C)*y[1] -c->ddX*cos(y[0]) -c->g*sin(y[0]))/c->r;
  //  f[1] = (-2*c->dr -c->ddX*cos(y[0]) -c->g*sin(y[0]))/c->r;
  f[2] = y[3];  
  f[3] = c->ddX;
  //  if(fabs(t-(int)t)<1e6) fprintf(stderr,"check t=%g f=%g,%g,%g,%g\n ",t,f[0],f[1],f[2],f[3]);
  //  if(fabs(t-(int)(t+0.5))<1e8) fprintf(stderr,"check t=%g y=%g,%g,%g,%g\n ",t,y[0],y[1],y[2],y[3]);
//  if(ddXn>0){
//    fprintf(stderr,"t=%g check?? ddXn=%g=?=%g\n",t,ddXn,c->ddX);
//  }
//  double dd=fabs(t-(int)(t+0.5)); if(t>5 && dd<1e-12){
//    fprintf(stderr,"check t=%g c->ddX=%g, t=%g, it=%d.dd=%g\n ",t,c->ddX,t,(int)(t+0.5),dd);
//  }
  return GSL_SUCCESS;
}
////////////////
//#define square(x) ((x)*(x))
double square(double x){return((x)*(x));}
//double plant(double uu)
double plant1(double uu,CRANE *crane)
{
  //  fprintf(stderr,"check uu=%g, ",uu);
  if(uu>crane->ddXmax) uu=crane->ddXmax;  
  else if(uu<-crane->ddXmax) uu=-crane->ddXmax; 
  //  fprintf(stderr,"->%g, \n",uu);
  int n;
  for(n=0;n<crane->nh;n++){
    crane->ddX=uu;//crane->ddX=(uu<crane->ddXmax)?uu:crane->ddXmax;
//    if(ddXn>0){
//      fprintf(stderr,"ddXn=%g=?=%g\n",ddXn,crane->ddX);
//    }
    if(crane->dX>=crane->dXmax && crane->ddX>0) crane->ddX=0;
    else if(crane->dX<=-crane->dXmax && crane->ddX<0) crane->ddX=0;
    int status = gsl_odeiv_step_apply (crane->_s, crane->_t, crane->_h, 
				       crane->_y, crane->_y_err, 
				       crane->_dydt_in, 
				       crane->_dydt_out, 
				       &crane->_sys);
    if (status != GSL_SUCCESS) {fprintf(stderr,"### failure of plant calc.\n"); break;}
    
    int i;for(i=0;i<dim_crane;i++) crane->_dydt_in[i]=crane->_dydt_out[i];
    crane->_t+=crane->_h;
    crane->a  =crane->_y[0];
    crane->da =crane->_y[1];
    crane->X  =crane->_y[2];
    crane->dX =crane->_y[3];
    crane->x  =crane->X+crane->r * sin(crane->a); //output y
    crane->y  =crane->r*cos(crane->a);

    crane->dx=(crane->x-crane->x0)/crane->_h;
    crane->dy=(crane->y-crane->y0)/crane->_h;
    crane->ddx=(crane->dx-crane->dx0)/crane->_h;
    crane->ddy=(crane->dy-crane->dy0)/crane->_h;
    crane->T=crane->m*sqrt(square(crane->ddx)+square(crane->ddy-crane->g));
    crane->F=crane->M*crane->ddX-crane->T*sin(crane->a);
    crane->dda=(crane->da-crane->da0)/crane->_h;
    crane->x0=crane->x;
    crane->y0=crane->y;
    crane->dx0=crane->dx;
    crane->dy0=crane->dy;
    crane->da0=crane->da;
  }
#ifndef CRANESUB
  fprintf(fp,"%.7e %.7e %.7e", crane->_t,crane->_y[0],crane->_y[1]);//crane->a,crane->da
  fprintf(fp," %.7e %.7e %.7e" ,crane->X,crane->dX,crane->ddX);
  fprintf(fp," %.7e %.7e %.7e" ,crane->x,crane->dx,crane->ddx);
  fprintf(fp," %.7e %.7e %.7e" ,crane->y,crane->dy,crane->ddy);
  fprintf(fp," %.7e %.7e" ,crane->T,crane->F);
  fprintf(fp,"\n");
#endif //#ifndef CRANESUB
  return(crane->x);//crane->x in [0,AP_y=10?] ==> rt in [0,1]
}
int initialize1(CRANE *crane)
{
  crane->cranefunc=crane1func;
  crane->plant=plant1;
  crane->g=9.8;
  crane->M=100;
  crane->m=20;//10;//20
  crane->r=5;//5;
  crane->C=1;//5;

  crane->dr=crane->ddr=0;
  crane->x0=0;
  crane->y0=crane->r;
  crane->dx0=crane->dy0=crane->da0=0;
  crane->dXmax=1.;//??ddXmax=(dXmax-dX)/dt;//??
  crane->ddXmax=0.2;//??ddXmax=(dXmax-dX)/dt;//??
  crane->Fmax=30.0;//check//  crane->Fmax=30;//check
#ifdef CRANESUB
  crane->h=AP_tS;
  crane->m=_crane_m;
  crane->r=_crane_r;
  crane->dXmax=_crane_dXmax;
  if(_AP_umax>0) AP_u_max=crane->ddXmax=_AP_umax;
  else AP_u_max=crane->ddXmax;
  AP_u_min=-AP_u_max;
  //  starttime=0;
  //  totaltime=50;
  rr=AP_r=_AP_r;//10
  rr_kyoyou=_rr_kyoyou;
  //  p=(double *)malloc(buffsize*sizeof(double));
  C_MODE=11;
  //  iteration=_iteration;
#else
  crane->h=0.01;
#endif
  crane->nh=10;
  crane->_h=crane->h/crane->nh;//0.001
  crane->_dim=4;
  if(crane->_y==NULL){
    crane->_y=(double*)malloc(crane->_dim*sizeof(double));
    crane->_y_err=(double*)malloc(crane->_dim*sizeof(double));
    crane->_dydt_in=(double*)malloc(crane->_dim*sizeof(double));
    crane->_dydt_out=(double*)malloc(crane->_dim*sizeof(double));
  }
  crane->_T= gsl_odeiv_step_rk4;
  crane->_s= gsl_odeiv_step_alloc (crane->_T, crane->_dim);
  crane->_sys= (gsl_odeiv_system){crane1func, NULL, crane->_dim, crane};
  //  crane->_sys= (gsl_odeiv_system){crane1func, NULL, crane->_dim, &crane};
  //  crane->_sys= (gsl_odeiv_system){crane->cranefunc, NULL, crane->_dim, &crane};
  //initialize variables
  crane->_t=crane->_y[0]=crane->_y[1]=crane->_y[2]=crane->_y[3]=0;
  int i;for(i=0;i<crane->_dim;i++) crane->_dydt_in[i]=0;
  GSL_ODEIV_FN_EVAL(&(crane->_sys), crane->_t, crane->_y, crane->_dydt_in);
//  crane->a  =crane->_y[0];
//  crane->da =crane->_y[1];
//  crane->X  =crane->_y[2];
//  crane->dX =crane->_y[3];
//  crane->x  =crane->X+crane->r * sin(crane->a); //output y
//  crane->y  =crane->r*cos(crane->a);
//  crane->dXmax=1.;//??ddXmax=(dXmax-dX)/dt;//??
//  crane->ddXmax=0.2;//??ddXmax=(dXmax-dX)/dt;//??
  return(0);
}//endof initialize1

#ifndef CRANESUB
int main1(int argc,char **argv)
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
  CRANE crane[1];
//  int (*initialize)();
//  if(1==1){
//    initialize=initialize1;
//  }
//  (*initialize)(crane);
  crane->_y=NULL;
  initialize1(crane);
  int M=(t4/crane->h)+1;
  //  ddX=(double*)malloc(sizeof(double)*M);
  double *ddX=(double*)malloc(sizeof(double)*M);
  //  double *F  =(double*)malloc(sizeof(double)*M);
  double Vmax=1;//dX/dt=1[m/s]
  int n;
  double t;
  ////////////////////////////////////////////////////
  ///   set ddX                                    ///
  ////////////////////////////////////////////////////
  int n0 =t0/crane->h+0.5, n4=t4/crane->h+0.5;
  for(t=0;t<t4;t+=crane->h){
    n=t/crane->h;
    if(t<=t0) ddX[n]=0; //zero
    else if(t<=t1) ddX[n]=Vmax/(t1-t0); //accelerate
    else if(t<=t2) ddX[n]=0;            //free move
    else if(t<=t3) ddX[n]=-Vmax/(t3-t2);//decelerate
    else ddX[n]=0;                      //free move
  }
  ////////////////////////////////////////////////////
  ///   Solve by the Runge Kutta Method of GSL     ///
  ////////////////////////////////////////////////////
  //  char *fn="crane1io.dat";
  fp=fopen(fn1,"w");
  fprintf(fp,"#%.7e %d %d %.7e %.7e %.7e %.7e #h,n0,n4,M,n,r\n",crane->h,n0,n4,crane->M,crane->m,crane->r,crane->C);
  //  double dx0=0,dy0=0,da0=0;
  //  for(n=0;n<n4;){
  for(t=0;t<t4;t+=crane->h){
    n=t/crane->h;
//    ddXn=ddX[n];if(n>500 && n<510){
//      fprintf(stderr,"check n=%d,t=%g ddX=%g\n",n,t,ddX[n]);
//    }
    //    (*(crane->plant))(ddX[n],crane);
    plant1(ddX[n],crane);
  }
  fclose(fp);
  fprintf(stdout,"Results are stored in '%s'.\n",fn1);

  gsl_odeiv_step_free (crane->_s);
  return 0;
}//endof main1
#endif//endof #ifndef CRANESUB
/////////////////////////
int crane2func (double t, const double y[], double f[], void *params)
{
  CRANE *c = (CRANE *)params;
  //y[0]=crane->p, y[1]=crane->da, y[2]=crane->X, y[3]=crane->dX
  f[0] = y[1];
  f[1] = (-(2*c->dr+c->C)*y[1] -c->ddX*cos(y[0]) -c->g*sin(y[0]))/c->r;
  //  f[1] = (-2*c->dr -c->ddX*cos(y[0]) -c->g*sin(y[0]))/c->r;
  f[2] = y[3];  
  //  f[3] = c->ddX;
  f[3] = (c->F+c->T*sin(y[0]))/c->M;
  return GSL_SUCCESS;
}//endof crane2func

double plant2(double uu,CRANE *crane)
{
  //  crane->F=uu;
  if(uu>crane->Fmax) uu=crane->Fmax;  
  else if(uu<-crane->Fmax) uu=-crane->Fmax; 
  int n;
  for(n=0;n<crane->nh;n++){
    crane->F=uu;//
    if(crane->dX>=crane->dXmax && crane->F>0) crane->F=0;
    else if(crane->dX<=-crane->dXmax && crane->F<0) crane->F=0;
    int status = gsl_odeiv_step_apply (crane->_s, crane->_t, crane->_h, 
				       crane->_y, crane->_y_err, 
				       crane->_dydt_in, 
				       crane->_dydt_out, 
				       &crane->_sys);
    if (status != GSL_SUCCESS)   break;
    
    int i;for(i=0;i<dim_crane;i++) crane->_dydt_in[i]=crane->_dydt_out[i];
    crane->_t+=crane->_h;

    crane->a  =crane->_y[0];
    crane->da =crane->_y[1];
    crane->X  =crane->_y[2];
    crane->dX =crane->_y[3];

    crane->x  =crane->X+crane->r * sin(crane->a);
    crane->y  =crane->r*cos(crane->a);
    crane->dx=(crane->x-crane->x0)/crane->_h;
    crane->dy=(crane->y-crane->y0)/crane->_h;
    crane->ddx=(crane->dx-crane->dx0)/crane->_h;
    crane->ddy=(crane->dy-crane->dy0)/crane->_h;
    crane->T=crane->m*sqrt(square(crane->ddx)+square(crane->ddy-crane->g));
    crane->ddX=(crane->dX-crane->dX0)/crane->_h;
    //    crane->F=crane->M*crane->ddX-crane->T*sin(crane->a);
    crane->dda=(crane->da-crane->da0)/crane->_h;
    /*    crane->dda=(-2*crane->dr*crane->da-crane->g*sin(crane->a)-ddX[n]*cos(crane->a))/crane->r; */
    crane->x0=crane->x;
    crane->y0=crane->y;
    crane->dx0=crane->dx;
    crane->dy0=crane->dy;
    crane->da0=crane->da;
    crane->dX0=crane->dX;
  }
#ifndef CRANESUB
  fprintf(fp,"%.7e %.7e %.7e", crane->_t,crane->_y[0],crane->_y[1]);//crane->a,crane->da
  fprintf(fp," %.7e %.7e %.7e" ,crane->X,crane->dX,crane->ddX);
  fprintf(fp," %.7e %.7e %.7e" ,crane->x,crane->dx,crane->ddx);
  fprintf(fp," %.7e %.7e %.7e" ,crane->y,crane->dy,crane->ddy);
  fprintf(fp," %.7e %.7e" ,crane->T,crane->F);
  fprintf(fp,"\n");
#endif
  return(crane->x);
  //  return(crane->X);
}//endof plant2
int initialize2(CRANE *crane)
{
  crane->cranefunc=crane2func;
  crane->plant=plant2;
  crane->Fmax=20.0;//check//  crane->Fmax=30;//check
  //  crane->dXmax=1.0;
  crane->dXmax=1.0;
  crane->ddXmax=0.2;
  crane->g=9.8;
  crane->M=100;
  crane->m=20;//10;//10;//20
  crane->r=5;//5;
  crane->C=1;//5;
  crane->dr=crane->ddr=0;
  crane->x0=0;
  crane->y0=crane->r;
  crane->dX0=crane->dx0=crane->dy0=crane->da0=0;
#ifdef CRANESUB
  //  crane->Fmax=_crane_Fmax;//check//  crane->Fmax=30;//check
  crane->m=_crane_m;
  crane->r=_crane_r;
  crane->h=AP_tS;
  crane->dXmax=_crane_dXmax;
  if(_AP_umax>0) AP_u_max=crane->Fmax=_AP_umax;
  else AP_u_max=crane->Fmax;
  AP_u_min=-AP_u_max;
  //  starttime=0;
  //  totaltime=100;//  totaltime=40;
  //  totaltime=50;//  totaltime=40;
  //  int kmax=totaltime/AP_tS;
  //  _rr=(double*)malloc(kmax*sizeof(double));
  rr=AP_r=_AP_r;//10
  //  int k;for(k=0;k<kmax;k++) _rr[k]=AP_r;//10;
  rr_kyoyou=_rr_kyoyou;
  //  p=(double *)malloc(buffsize*sizeof(double));
  C_MODE=11;
  //  iteration=_iteration;
  //  fprintf(stdout,"?????????iteration=%d\n",_iteration);
#else
  crane->h=0.01;
#endif
  crane->nh=10;
  crane->F=crane->a=crane->da=crane->dda=0;
  crane->T=crane->m*crane->g;
  crane->_h=crane->h/crane->nh;//0.001
  crane->_dim=4;
  {//  if(crane->_y==NULL){
    crane->_y=(double*)malloc(crane->_dim*sizeof(double));
    crane->_y_err=(double*)malloc(crane->_dim*sizeof(double));
    crane->_dydt_in=(double*)malloc(crane->_dim*sizeof(double));
    crane->_dydt_out=(double*)malloc(crane->_dim*sizeof(double));
  }
  crane->_T= gsl_odeiv_step_rk4;
  crane->_s= gsl_odeiv_step_alloc (crane->_T, crane->_dim);
  crane->_sys= (gsl_odeiv_system){crane->cranefunc, NULL, crane->_dim, crane};
  //  crane->_sys= (gsl_odeiv_system){crane->cranefunc, NULL, crane->_dim, &crane};
  crane->_t=crane->_y[0]=crane->_y[1]=crane->_y[2]=crane->_y[3]=0;
  int i;for(i=0;i<crane->_dim;i++) crane->_dydt_in[i]=0;
  GSL_ODEIV_FN_EVAL(&(crane->_sys), crane->_t, crane->_y, crane->_dydt_in);
  return(0);
}
#ifndef CRANESUB
int main2(int argc, char** argv)
{
  //  CRANE crane;
  CRANE crane[1];
  crane->g=9.8;
  crane->M=100;
  crane->m=20;
  crane->r=5;
  crane->dr=crane->ddr=0;
  ////////////////////////////////////////////////////
  /// method 2                                     ///
  /// input F                                     ///
  /// output p,x,y,X,...                          ///
  ////////////////////////////////////////////////////
  double h;//,hh=0.1;
  //result for different h
  /*gnuplot
   set style data lines;n=1;
   n=n+1;plot "crane1io.dat" using 1:n, "crane2io.dat" using 1:n;print "n=",n
   #strange at n=9(ddx),12(ddy),13(T)
  */
  ////////////////////////////////////////////////////
  ///   read F                                    ///
  ////////////////////////////////////////////////////
  //  char *fn1="crane1io.dat";
  FILE *fp1=fopen(fn1,"r");
  int n4;
#define buffsize 512
  char buff[buffsize];
  int n0;
  if(fgets(buff,buffsize,fp1)!=NULL)
    sscanf(buff,"#%lf%d%d%lf%lf%lf%lf",&h,&n0,&n4,&crane->M,&crane->m,&crane->r,&crane->C);
  crane->h=h;
  double t4=n4*h;
  double *F  =(double*)malloc(sizeof(double)*(n4+1));
  //  int M=n4+1;double *F  =(double*)malloc(sizeof(double)*M);
  //  double *ddX=(double*)malloc(sizeof(double)*M);
  
  int n;
  double t;
  //  double dx0=0,dy0=0,dX0=0,da0=0;
  //  double x0=0,y0=crane->r;

  if(fgets(buff,buffsize,fp1)!=NULL);  //??  fgets(buff,buffsize,fp1);
  for(n=0;n<n4;n++){//
    double _x1,_x2,_x3,_x4,_x5,_x6,_x7,_x8,_x9,_x10,_x11,_x12,_x13,_x14;
    if(fgets(buff,buffsize,fp1)!=NULL) //      fgets(buff,buffsize,fp1);
      sscanf(buff,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
	     &_x1,&_x2,&_x3,&_x4,&_x5,&_x6,&_x7,&_x8,&_x9,&_x10,&_x11,&_x12,&_x13,&_x14);
    F[n]=_x14;
  }
  ////////////////////////////////////////////////////
  ///   Solve by the Runge Kutta Method of GSL     ///
  ////////////////////////////////////////////////////
  crane->_y=NULL;
  initialize2(crane);
  fp=fopen(fn2,"w");
  for(t=0;t<t4;t+=crane->h){
    n=t/crane->h;
    plant2(F[n],crane);
    //    (*(crane->plant))(F[n],crane);
  }
  fclose(fp);
  fprintf(stdout,"Results are stored in '%s'.\n",fn2);

  gsl_odeiv_step_free (crane->_s);
  return 0;
}//main2
#endif //#ifndef CRANESUB

#ifndef CRANESUB
int main(int argc,char **argv)
{
  if(argc<2){
    fprintf(stderr,"Usage:%s [1|2]\n",argv[0]);
    return(1);
  }
  if(argv[1][0]!='2') main1(argc,argv);
  else main2(argc,argv);
  return(0);
}
#endif //#ifndef CRANESUB
