#undef FLT
/*#define FLT /*$B$3$l$r@8$+$9$H(Bfloat$B7?$K$J$k(B*/
#ifdef FLT
#define FLOAT float
#define LF "%f"
#else
#define FLOAT double
#define LF "%lf"
#endif
char ffff[80];
