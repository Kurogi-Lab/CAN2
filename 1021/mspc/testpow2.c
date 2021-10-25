#include <math.h>
#include <stdio.h>
//#define mypow2(x) pow(x,2.0)         //a=1.66667e+15 real0m6.251suser0m5.996ssys0m0.040s via icc
                                       //a=1.66667e+15 real0m5.913suser0m5.700ssys0m0.028s   via icc 2
                                       //a=1.66667e+15 real0m15.917suser0m14.377ssys0m0.092s via gcc
#define mypow2(x) ((x)*(x))            //a=1.66667e+15 real0m9.508suser0m9.085ssys0m0.040s         icc
                                       //a=1.66667e+15 real0m10.175suser0m9.369ssys0m0.084s      icc
                                       //a=1.66667e+15 real0m15.359suser0m13.753ssys0m0.108s  gcc
//double mypow2(double x){return(x*x);}//a=1.66667e+15 real0m5.905suser0m5.704ssys0m0.028s       icc
                                       //a=1.66667e+15 real0m6.952suser0m5.908ssys0m0.124s       icc
                                       //a=1.66667e+15 real0m15.518suser0m14.313ssys0m0.084s via gcc
int main()
{
  int i,j,k;
  double a;
  for(k=0;k<100;k++){
    a=0;
    for(i=0;i<10000;i++){
      for(j=0;j<10000;j++){
	a+=mypow2(i-j);
      }
    }
  }
  fprintf(stdout,"a=%g\n",a);
  return 1;
}
