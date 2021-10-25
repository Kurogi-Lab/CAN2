#ifndef __RANDOM_H__
#define __RANDOM_H__
#include <math.h>

#define RANDOM 0
#define DRAND48 1 //compatible with 32bit and 64bit?
#define MYRAND 2
#define ZMTRAND 3

#ifndef RAND
#define RAND RANDOM
#endif

#define PI 3.141592653589793
#if RAND == ZMTRAND
#include "share/zmtrand.h"
#elif RAND == MYRAND
/*
 * パラメータの設定
 */
#define PARA 2

#if PARA == 1
#define rand_a 78125
#define rand_c 1013904223
#define rand_M 4294967296
#define rand_M1 4294967295
#elif PARA == 2
#define rand_a 1664525
#define rand_c 1013904223
#define rand_M 4294967295
#define rand_M1 4294967296
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
int random_seed(int seed);
#endif

#if RAND == MYRAND
#define random_unif1() myrandom()
#define random_unifN(N) (myrandom()*(N))
#elif RAND == ZMTRAND
#define random_unif1() NextUnif()
#define random_unifN(N) NextIntEx(N)
#elif RAND == DRAND48
#define random_unif1() drand48()
#define random_unifN(N) ((int)((double)(N)*lrand48()/(RAND_MAX+1.0)))
#elif RAND == RANDOM
#define random_unif1() (random()/(RAND_MAX+1.0))
#define random_unifN(N)  ((int)((double)(N)*random()/(RAND_MAX+1.0)))
#endif

#endif /* __RANDOM_H__ */

