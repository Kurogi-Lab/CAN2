#include<stdio.h>
#include<omp.h>
#define N 1000

void add(int *a, int *b, int *c, int min, int max);
void mul(int *a, int *b, int *d, int min, int max);
void add_add(int *a, int *b, int *e, int min, int max);
void mul_mul(int *a, int *b, int *f, int min, int max);

int main(){
  int a[N];
  int b[N];
  int c[N];
  int d[N];
  int e[N];
  int f[N];
  int i;

  #pragma omp parallel for
  for(i=0; i < N; i++){
    a[i] = i;
    b[i] = 1;
  }

  #pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int num = N/4;
    int thread_part = num * thread_id;

    add(a,b,c,thread_part,thread_part + num);
    mul(a,b,d,thread_part,thread_part + num);
    add_add(a,b,e,thread_part,thread_part + num);
    mul_mul(a,b,f,thread_part,thread_part + num);
  }


  for(i=0; i < N; i++){
    printf("c : %d\n",c[i]);
    printf("d : %d\n",d[i]);
    printf("e : %d\n",e[i]);
    printf("f : %d\n",f[i]);
  }

  return 0;
}
