/*************
http://www.swin.edu.au/astronomy/pbourke/analysis/fft2d/
Example of usage:
(1) init_para_FFT(30000);
     ---> 
(2) FFT(x_re,x_im,1);フーリエ変換
(2) FFT(x_re,x_im,-1);フーリエ逆変換

********/
#include <math.h>
#include <stdio.h>
/**********/
#define TRUE 1
#define FALSE 0
int FFT_N=-1;
int FFT_N1;
int FFT_m;
FLOAT *x_re,*x_im;
/*struct fftdata {
  int N;
  int N2;
  int m;
  FLOAT *re,*im,*xp,xp_sum;
} fft;*/


int Powerof2(int nx,int *m,int *twopm)
{
  m[0]=0;
  twopm[0]=1;
  for(;;){
    if(twopm[0]==nx) return(TRUE);
    if(twopm[0]>nx) return(FALSE);
    m[0]++;
    twopm[0] *=2;
  }
}
#define FFT_VER1
#ifdef FFT_VER1
#undef PI
#define PI  3.141592653589793

FLOAT *rot_re,*rot_im;
FLOAT *u_re,*u_im;
FLOAT *hw;
int *rd;

int init_para_FFT(int nn)
{
  int i,j;

  FFT_N1=FFT_N;
  Powerof2(nn,&FFT_m,&FFT_N);
  if(FFT_N1 != FFT_N){
    if(x_re!=NULL){
      free(x_re);x_re=NULL;
      free(x_im);x_im=NULL;
      free(rd);rd=NULL;
      free(hw);hw=NULL;
      free(rot_re);rot_re=NULL;
      free(rot_im);rot_im=NULL;
      free(u_re);u_re=NULL;
      free(u_im);u_im=NULL;
    }
    x_re=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    x_im=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    rd=(int *)malloc(sizeof(int)*FFT_N);
    hw=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    rot_re=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    rot_im=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    u_re=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    u_im=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    for(i=0;i<FFT_N;i++) {
      rd[i]=0x00;
      for(j=0;(i>>j)>=1;j++){
	rd[i] |= (((i>>j)&0x01)<<(FFT_m-j-1));
      }
      hw[i]=0.54-0.46*cos(2.*PI*(FLOAT)i/((FLOAT)FFT_N));
      hw[i]=1;
      rot_re[i]=cos((FLOAT)i*PI/(FLOAT)FFT_N);
      rot_im[i]=sin((FLOAT)i*PI/(FLOAT)FFT_N);
    }
  }
}
FLOAT FFT(FLOAT *x,FLOAT *y,int dir)
{
  FLOAT	aa,bb,power;
  int	i,j,k,kk,ki,FFT_Nk;
  FLOAT	wr,wi,xr,xi;
  /* Exchange radix and window by Hamming window */
  if(dir == 1){ /* fft*/
    for(i = 0; i<FFT_N ; i++){
      u_re[i] = x[rd[i]];
      u_im[i] = y[rd[i]];
    }
  }
  else { /* inverse fft */
    for(i = 0; i<FFT_N ; i++){
      u_re[i] = x[rd[i]]/FFT_N;
      u_im[i] = y[rd[i]]/FFT_N;
    }
  }
  for(i = 0; i<FFT_N ; i++){
    x[i] = u_re[i];
    y[i] = u_im[i];
  }
  
  /* Fast calculation */
  for(k=1;k<FFT_N;k*=2){
    kk=k<<1;
    FFT_Nk=FFT_N/k;
    for(j=0;j<k;j++){
      wr=rot_re[FFT_Nk*j];
      wi=(FLOAT)(-dir)*rot_im[FFT_Nk*j];
      for(i=j;i<FFT_N;i+=kk){
	ki=k+i;
	xr=x[ki]*wr-y[ki]*wi;
	xi=x[ki]*wi+y[ki]*wr;
	x[ki]=x[i]-xr;
	y[ki]=y[i]-xi;
	x[ i]+=xr;
	y[ i]+=xi;
      }
    }
  }
  return(TRUE);
}
#endif
#ifdef FFT_VER2
int init_para_FFT(int nn)
{
  FFT_N1=FFT_N;
  Powerof2(nn,&FFT_m,&FFT_N);
  if(FFT_N1 != FFT_N){
    if(x_re!=NULL) {free(x_re);x_re=NULL;}
    if(x_im!=NULL) {free(x_im);x_im=NULL;}
    x_re=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
    x_im=(FLOAT *)malloc(sizeof(FLOAT)*FFT_N);
  }
}
int FFT(FLOAT *x,FLOAT *y,int dir)
{
  long i,i1,j,k,i2,l,l1,l2;
  FLOAT c1,c2,tx,ty,t1,t2,u1,u2,z;
  
   /* Do the bit reversal */
   i2 = FFT_N >> 1;
   j = 0;
   for (i=0;i<FFT_N-1;i++) {
      if (i < j) {
         tx = x[i];
         ty = y[i];
         x[i] = x[j];
         y[i] = y[j];
         x[j] = tx;
         y[j] = ty;
      }
      k = i2;
      while (k <= j) {
         j -= k;
         k >>= 1;
      }
      j += k;
   }

   /* Compute the FFT */
   c1 = -1.0;
   c2 = 0.0;
   l2 = 1;
   for (l=0;l<FFT_m;l++) {
      l1 = l2;
      l2 <<= 1;
      u1 = 1.0;
      u2 = 0.0;
      for (j=0;j<l1;j++) {
         for (i=j;i<FFT_N;i+=l2) {
            i1 = i + l1;
            t1 = u1 * x[i1] - u2 * y[i1];
            t2 = u1 * y[i1] + u2 * x[i1];
            x[i1] = x[i] - t1;
            y[i1] = y[i] - t2;
            x[i] += t1;
            y[i] += t2;
         }
         z =  u1 * c1 - u2 * c2;
         u2 = u1 * c2 + u2 * c1;
         u1 = z;
      }
      c2 = sqrt((1.0 - c1) / 2.0);
      if (dir == 1) c2 = -c2;
      c1 = sqrt((1.0 + c1) / 2.0);
   }

   /* Scaling for forward transform */
   if (dir == 1) {
      for (i=0;i<FFT_N;i++) {
         x[i] /= (FLOAT)FFT_N;
         y[i] /= (FLOAT)FFT_N;
      }
   }
   return(TRUE);
}
#endif

int FFT_NX=-1,FFT_NY=-1;
int FFT_NX1,FFT_NY1;
int FFT_mx,FFT_my;
FLOAT *c_re=NULL,*c_im=NULL;
int init_para_FFT2D(int nx,int ny)
{
  int i,m;

  FFT_NX1=FFT_NX;
  FFT_NY1=FFT_NY;
  Powerof2(nx,&FFT_mx,&FFT_NX);
  Powerof2(ny,&FFT_my,&FFT_NY);
  if(c_re==NULL || c_im==NULL || FFT_NX!=FFT_NX1 || FFT_NY!=FFT_NY1){
    if(c_re!=NULL) {free(c_re);c_re=NULL;}
    if(c_im!=NULL) {free(c_im);c_im=NULL;}
    c_re=(FLOAT *)malloc(sizeof(FLOAT)*FFT_NX*FFT_NY);
    c_im=(FLOAT *)malloc(sizeof(FLOAT)*FFT_NX*FFT_NY);
  }
}
free_para_FFT2D()
{
  if(c_re!=NULL) {free(c_re);c_re=NULL;}
  if(c_im!=NULL) {free(c_im);c_im=NULL;}
  FFT_NX=FFT_NY=-1;
}
int FFT2D(FLOAT *c_re,FLOAT *c_im,int dir)
{
   int i,j;
   int m,twopm;
   FLOAT *real,*imag;

   /* Transform the rows */
   if(FFT_NX==-1 || FFT_N!=FFT_NX) init_para_FFT(FFT_NX);
   for (j=0;j<FFT_NY;j++) {
      for (i=0;i<FFT_NX;i++) {
         x_re[i] = c_re[j*FFT_NX+i];
         x_im[i] = c_im[j*FFT_NX+i];
      }
      FFT(x_re,x_im,dir);
      for (i=0;i<FFT_NX;i++) {
         c_re[j*FFT_NX+i] = x_re[i];
         c_im[j*FFT_NX+i] = x_im[i];
      }
   }

   /* Transform the columns */
   if(FFT_N!=FFT_NY) init_para_FFT(FFT_NY);
   for (i=0;i<FFT_NX;i++) {
      for (j=0;j<FFT_NY;j++) {
         x_re[j] = c_re[j*FFT_NX+i];
         x_im[j] = c_im[j*FFT_NX+i];
      }
      FFT(x_re,x_im,dir);
      for (j=0;j<FFT_NY;j++) {
         c_re[j*FFT_NX+i] = x_re[j];
         c_im[j*FFT_NX+i] = x_im[j];
      }
   }
   return(TRUE);
}
/******/
