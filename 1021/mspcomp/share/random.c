/*
 * randam.c
 * 乱数発生プログラム
 *
 */
#include "random.h"

/***********************************************************************
 * 値域[0,1]で乱数を発生
 ***********************************************************************/
double myrandom()
{
  _randn = _randn*rand_a+rand_c;
  //_randn %=M;
  return(_randn/rand_M1);
  //_randn *= 78125;
  //return( _randn/4294967295.0 ); // 32bit計算機
}

/***********************************************************************
 * polar method for Gaussian
 * N(mu,sigma)=N(0,1)
 ***********************************************************************/
double gauss()
{
  double v1,v2,s,s2,x1,x2;
  for(;;){
    v1=2.*myrandom()-1.;
    v2=2.*myrandom()-1.;
    if((s=v1*v1+v2*v2)<1.0) break;
  }
  x1=v1*sqrt(s2=-2.*log(s)/s);
  x2=v2*sqrt(s2);
  return(x1);
}

