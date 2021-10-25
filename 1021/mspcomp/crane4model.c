#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
int main (int argc,char **argv)
{
  int ny=4;
  int nu=4;
  double tS=0.01;/*sampling time*/
  double tS1=0.5;/*virtual sampling time*/
  int kS,kS1=tS1/tS;
  int tt=50;//total time in sec
  int Tu=5;
  int nynu=ny+nu;
  int ny1=ny+1;
  int nu1=nu+1;
  int ny1nu1=ny1+nu1;
  double *a=(double *)malloc(nynu*sizeof(double));
  double *b=&a[ny];
  double *x=(double*)malloc(ny1nu1*sizeof(double));
  double *y=&x[0];
  double *u=&x[ny1];
  double *dx=(double*)malloc(ny1nu1*sizeof(double));
  double *dy=&dx[0];
  double *du=&dx[ny1];

  double a1[80]={
    //M[0] obtained by M[0] of the result from sh crane4model.sh with I in 1
    0.001458, 0.001271, 0.000851, 0.000132, 1.248710, -0.206041, 0.354766, -0.397559, //crane4model.sh
    //0.001098, 1.791673, -0.973249, 0.258141, -0.076784,  0, 0, 0,                //iconip2014exp2.sh
    //m=10
    3.292879401515547,
    -4.192289468385533,
    2.505940738008382,
    -0.60653067106865,
    2.1607298042996149E-4,
    7.9001360607741178E-4,
    -1.7832657134227696E-4,
    -1.1491619285558408E-4,
//m=40
    3.720360330034425,
    -5.280177686268928,
    3.399274383172754,
    -0.83945702693866,
    5.895359274604567E-5,
    2.3816857695537014E-4,
    -4.7505038982069532E-5,
    -3.6944458957165394E-5,
    //m=70
    3.800543740235394,
    -5.486741771056344,
    3.571852320329751,
    -0.88565428950928,
    3.4181363466104196E-5,
    1.4036908886617388E-4,
    -2.7382990951603394E-5,
    -2.2004892397928481E-5,
    //m=100
    3.833910348741944,
    -5.572658098588409,
    3.643585150267391,
    -0.90483740042,
    2.4067085281143667E-5,
    9.9487247138612246E-5,
    -1.9234297084280119E-5,
    -1.5661220461420435E-5,
//
  };
  int n,m,i,j;
  double t;
  for(i=1;i<argc;i++){
    if(strncmp(argv[i],"TS:",3)==0){
      sscanf(&argv[i][3],"%lf",&tS1);
    }
    if(strncmp(argv[i],"a:",2)==0){
      double _a1;
      j=0;
      char *p=&argv[i][1];
      for(;;){
	if(*p==0) break;
	if(*p==':'){
	  sscanf(++p,"%lf",&a1[j++]);
	}
	p++;
      }
    }
  }
  for(n=0;n<ny;n++) a[n+1]=a1[n];
  for(m=0;m<nu;m++,n++) b[m+1]=a1[n];
  fprintf(stderr,"#a");
  for(n=1;n<=nynu;n++) fprintf(stderr,":%g",a[n]);
  for(;n<80;n++) a[n]=0;
  fprintf(stderr,"\n");

  double umax=10;
  double yt=0,ut1=0,yyt=0;
  int itt=tt/tS1;
  for(i=0;i<itt;i++){
    t=i*tS1;
    double aa=0.8;
    if(t<Tu) u[1]=aa*umax;
    else if(t<2*Tu) u[1]=0;
    else if(t<3*Tu) u[1]=-aa*umax;
    else u[1]=0;
    //    u[1]*=10;

    y[0]=0;//y_t=y[0],y_{t-j}=y[j];
    for(j=1;j<=ny;j++) y[0]+=a[j]*y[j];
    for(j=1;j<=nu;j++) y[0]+=b[j]*u[j];
    //    fprintf(stdout,"%.1f %+.5f %+.5f %d #t y[t] u[t-1] i\n",i*tS1,y[0],u[1],i);
    for(n=ny;n>=1;n--) y[n]=y[n-1];
    for(n=nu;n>=2;n--) u[n]=u[n-1];


    if(t==0) du[1]=aa*umax;
    else if(t==Tu) du[1]=-aa*umax;
    else if(t==2*Tu) du[1]=-aa*umax;
    else if(t==3*Tu) du[1]=+aa*umax;
    else du[1]=0;
    dy[0]=0;//y_t=y[0],y_{t-j}=y[j];
    for(j=1;j<=ny;j++) dy[0]+=a[j]*dy[j];
    for(j=1;j<=nu;j++) dy[0]+=b[j]*du[j];
    yt+=dy[0];
    ut1+=du[1];
    yyt+=yt;
    fprintf(stdout,"%.1f %+.5f %+.5f %d %.5f %.5f #t yt u[t-1] i y[t] yyt\n",i*tS1,yt,ut1,i,y[0],yyt);
    for(n=ny;n>=1;n--) dy[n]=dy[n-1];
    for(n=nu;n>=2;n--) du[n]=du[n-1];
    //
  }
  fprintf(stdout,"#a:");
  for(n=1;n<=ny;n++) fprintf(stdout,"%e ",a[n]);
  fprintf(stdout,"\n#b:");
  for(n=1;n<=nu;n++) fprintf(stdout,"%e ",b[n]);
  fprintf(stdout,"\n");
}
