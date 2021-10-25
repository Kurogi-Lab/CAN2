#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int size_mb = 100;                    /* mallocサイズ(100MB) */
  int size    = 1024 * 1024 * size_mb;  /* mallocサイズ計算(単位:Bytes) */
  //  long size    = 1024 * 1024 * 1024 * size_mb;  /* mallocサイズ計算(単位:Bytes) */
  int times   = atoi(argv[1]);          /* malloc回数 */
                                        /* 例) 500000回だと100MBx500000=50TB */

  char *str;                            /* malloc()で確保した領域 */
  int i;

  printf("start\n");

  for(i = 0; i < times; i++)            /* 引数で指定した回数分malloc() */
  {
    str = (char *)malloc(size);


    if (str == NULL)                    /* malloc()失敗 */
    {
      printf("malloc() error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    printf("malloc(i%07d/%07d,total-mem%.0f)\n", i, times,(double)i*size);
  }

  printf("end\n");

  return(EXIT_SUCCESS);
}
