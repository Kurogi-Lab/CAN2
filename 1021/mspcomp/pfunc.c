#define _CRT_SECURE_NO_DEPRECATE 1  /* VisualC++2005 での警告抑制 */
#include <stdio.h>

/* プロトタイプ宣言 */
int myabs(int num);

int main(void)
{
  //	int (*p) (int num);    /* 関数ポインタpを宣言 */
	int (*p) ();    /* 関数ポインタpを宣言 */
	int ans;
	int input;
	
	p = myabs;    /* myabs関数のアドレスを代入 */
	
	puts( "整数を入力して下さい" );
	scanf( "%d", &input );
	
	ans = (*p)(input);    /* ans = myabs(input); と同じ */
	printf( "%d\n", ans );

	return 0;
}

int myabs(int num)
{
	return ( num < 0 ? -num : num );
}
