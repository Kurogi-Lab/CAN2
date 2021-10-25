#undef FLT
/*#define FLT /*これを生かすとfloat型になる*/
#ifdef FLT
#define FLOAT float
#define LF "%f"
#else
#define FLOAT double
#define LF "%lf"
#endif
char ffff[80];
