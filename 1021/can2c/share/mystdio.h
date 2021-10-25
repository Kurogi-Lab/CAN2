#ifndef __MYSTDIO_H__
#define __MYSTDIO_H__

#include <stdio.h>

int myscanf(char *form, int var0, int var1, int var2,
	    int var3, int var4, int var5, int var6, int var7);

void scanbuff2argv(void);

void myprintf(char *form, double a, double b, double c, double d,
	      double e, double f, double g, double h, double i,
	      double j, double k, double l, double m, double n);


#endif /* __MYSTDIO_H__ */
