#ifndef __RANDOM_H__
#define __RANDOM_H__
#include <math.h>
#define MYRANDOM
#undef MYRANDOM
/*
 * パラメータの設定
 */
#define PI 3.141592653589793
#define PARA 2

#if PARA == 1
#define rand_a 78125
#define rand_c 1013904223
#define rand_M 4294967296
#define rand_M1 4294967295.0
#elif PARA == 2
#define rand_a 1664525
#define rand_c 1013904223
#define rand_M 4294967295
#define rand_M1 4294967296.0
#endif

//unsigned long _randn = 1;
unsigned long _randn;

/*
 * 値域[0,1]で乱数を発生
 */
double myrandom();

/*
 * polar method for Gaussian
 * N(mu,sigma)=N(0,1)
 */
double gauss();


#endif /* __RANDOM_H__ */

