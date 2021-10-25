#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main (void)
{
  int ny=4;
  int nu=4;
  double tS=0.01;/*sampling time*/
  double tS1=0.5;/*virtual sampling time*/
  int kS,kS1=tS1/tS;
  int tt=50;//total time in sec
  int Tu=5;
  int itt=tt/tS1;
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

  double a1[8]={
    //    2,-1,0,0,0.00125,0.00125,0,0
    //m=10
    3.292879401515547,
    -4.192289468385533,
    2.505940738008382,
    -0.60653067106865,
    2.1607298042996149E-4,
    7.9001360607741178E-4,
    -1.7832657134227696E-4,
    -1.1491619285558408E-4
//

  };
  int n,m,i,j;
  double t;
  for(n=0;n<ny;n++) a[n+1]=a1[n];
  for(m=0;m<nu;m++,n++) b[m+1]=a1[n];

  double umax=10;
  double yt=0,ut1=0;
  for(i=0;i<itt;i++){
    t=i*tS1;
    double aa=0.8;
    if(t<Tu) u[1]=aa*umax;
    else if(t<2*Tu) u[1]=0;
    else if(t<3*Tu) u[1]=-aa*umax;
    else u[1]=0;
    
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
    fprintf(stdout,"%.1f %+.5f %+.5f %d %.5f #t y[t] u[t-1] i y[t]\n",i*tS1,yt,ut1,i,y[0]);
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
