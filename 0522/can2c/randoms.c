/*
 * randam.c
 * 乱数発生プログラム
 *
 */
#include "randoms.h"
#if RAND == ZMTRAND
#include "share/zmtrand.c"
#elif RAND == MYRAND
#include <stdio.h>

/***********************************************************************
 * 値域[0,1]で乱数を発生
 ***********************************************************************/
double myrandom()
{
#if rand_M1 == 4294967296
  _randn = (unsigned long)(_randn*rand_a+rand_c);
  if((unsigned long)rand_M1!=0) _randn%=rand_M1; 
//!!! (unsigned long)rand_M1=(unsigned long)4294967296==0 Ubuntu12.04, !=0 Ubuntu14.04
// sizeof(unsigned long)=4 for Ubuntu12.04, 8 for Ubuntu14.04
//  printf("#####size of unsigned long=%lu, %d\n",sizeof(unsigned long),(unsigned long)rand_M1==0);
//  if((double)_randn>=4294967296.0){
//    printf("#####_randon=%lu, %lu \n",_randn,rand_M1);
//  }
//  else{
//    printf("#####?_randon=%lu, %lu\n",_randn,rand_M1);
//  }
  //_randn %=((unsigned long)rand_M1);//avoid division with rand_M1=0=(unsigned long)4294967296
#else
  _randn = _randn*rand_a+rand_c;
  //_randn %=M;
  _randn %=((unsigned long)rand_M1);//050329
#endif
  return((double)_randn/(double)rand_M1);/*for being [0,1] 64biy計算機*/
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
#endif
