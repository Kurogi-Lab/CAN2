#include <stdio.h>
#include <omp.h>
#define N 1200

void add(int *a, int *b, int *c, int min, int max){
  int i;
  printf("add thread_id=%d\n",omp_get_thread_num());
  for(i=min; i < max; i++){
    c[i] = a[i] + b[i];
  }
}

void mul(int *a, int *b, int *d, int min, int max){
  int i;
  printf("mul thread_id=%d \n",omp_get_thread_num());
  for(i=min; i < max; i++){
    d[i] = a[i] * b[i];
  }
}

void add_add(int *a, int *b, int *e, int min,int max){
  int i;
  printf("add_add thread_id=%d\n",omp_get_thread_num());
  for(i=min; i < max; i++){
    e[i] = a[i] + b[i] + b[i];
  }
}

void mul_mul(int *a, int *b, int *f, int min, int max){
  int i;
  printf("mul_mul thread_id=%d\n",omp_get_thread_num());
  for(i=min; i < max; i++){
    f[i] = a[i] * b[i] * b[i];
  }
}

int main(){
  int a[N];
  int b[N];
  int c[N];
  int d[N];
  int e[N];
  int f[N];
  int i;

  //  #pragma omp parallel for
  for(i=0; i < N; i++){
    a[i] = i;
    b[i] = 1;
  }
  omp_set_num_threads(5);
  #pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int M = omp_get_max_threads();
    int num = N/M;
    int thread_part = num * thread_id;
    printf("thread_id=%d <%d\n",omp_get_thread_num(),M);
    add(a,b,c,thread_part,thread_part + num);
    mul(a,b,d,thread_part,thread_part + num);
    add_add(a,b,e,thread_part,thread_part + num);
    mul_mul(a,b,f,thread_part,thread_part + num);
  }


  for(i=0; i < N; i++){
    printf("%d %d %d %d %d %d\n",a[i],b[i],c[i],d[i],e[i],f[i]);
//    printf("c : %d\n",c[i]);
//    printf("d : %d\n",d[i]);
//    printf("e : %d\n",e[i]);
//    printf("f : %d\n",f[i]);
  }

  return 0;
}
