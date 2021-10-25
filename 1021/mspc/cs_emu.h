/*#include "cs.h"*/
/*GLOBAL	UBYTE	MV_N;		/*  操作量	: 0.5％/bit	*/
/*************************************************************/
/*以下は実際のコンパイルでは必要ない（他で決定）＞＞＞       */
/*************************************************************/
#define GLOBAL 
#define M_MAX 100                /* 操作量上限:200%          */
#define M_MIN 0                  /* 操作量下限:0%            */
#define	UBYTE	unsigned char		/*  unsigned byte	*/
#define	WORD	int  		/*  signed word:16 bits	*/
#define	LONG	long			/*  signed long:32 bits	*/

double SMV;        /* 操作量 0-200%   */
double PV1;        /* 入力：センサ温度 PV1温度 0.01℃/bit*/

GLOBAL	UBYTE	C_WDT;		/*  ｳｫｯﾁﾄﾞｯｸﾀｲﾏｰ ｶｳﾝﾀ		*/
GLOBAL 	UBYTE	MODE_TYPE=0x00;		/* モードタイプ */
GLOBAL 	UBYTE 	RUN=1;		/* 0:停止中,1:運転中 */
#define	STD_MODE	0x02	/*  通常ﾓｰﾄﾞ			*/
#define chk_ad_data()   ;
#define chk_ad_hokan()  ;
#define chk_at_calc()   ;	
GLOBAL 	WORD SV;              /* 制御用目標値:  0.01℃/bit*/
#define SSV     SV
/* 設定変更ﾌﾗｸﾞ */
struct 	CHG_FLG{
	UBYTE 	SV:	1;	/* 目標温度設定変更有り */
	UBYTE 	P:	1;	/* 比例定数設定変更有り */
	UBYTE 	I:	1;	/* 積分定数設定変更有り */
	UBYTE 	D:	1;	/* 微分定数設定変更有り */
	UBYTE 	reserve:4;
};
GLOBAL 	union 	CHG{
	struct 	CHG_FLG  b;
	UBYTE 	d;
} CHG;
struct 	AT_FLG {
	/* 適応予測制御の組込			99/07/29 T.Arita*/
/*	UBYTE 	reserve:	3;*/
	UBYTE 	reserve:	2;
	UBYTE 	AT_APC_F:	1;	/* 適応予測制御ATﾌﾗｸﾞ */
	UBYTE 	AT_CALC_F:	1;	/* AT計算開始ﾌﾗｸﾞ */
	UBYTE 	AT_ZC_F:	1;	/* ｾﾞﾛｸﾛｽﾌﾗｸﾞ */
	UBYTE 	AT_CYCLE_F:	1;	/* 演算ｻｲｸﾙﾌﾗｸﾞ */
	UBYTE 	AT_MV:		1;	/* AT初回ＭＶ決定ﾌﾗｸﾞ */
	UBYTE 	AT_RUN_F:	1;	/* 制御Onﾌﾗｸﾞ */
};

GLOBAL	union	ATF	{		/*  ｵｰﾄﾁｭｰﾆﾝｸﾞ制御ﾌﾗｸﾞ	*/
	struct	AT_FLG	b;
	UBYTE	d;
} ATF;

/*************************************************************/
/*＜＜＜以上は実際のコンパイルでは必要ない（他で決定）       */
/*************************************************************/

double MV;
UBYTE MV_N;
int C_250MS;
int PP;
int C_MODE;

#define ad_hokan() ;
/*#define rst_pid()  ;*/
void rst_pid(void) ;/**/
#define rst_strl() ;
#define calc_s2dof_pid() ;
void calc_pid(void) ;
#define calc_onoff() ;
#define rst_ctrl() ;
/* マニュアル設定用 */
int AP_tau=1000; /* 1sec/bit  応答速度パラメタ*/
int AP_0=1250;   /* 0.001/bit 応答速度パラメタ*/
double AP_under=0.2;            /* アンダーシュート補正*/
int AT_FLAG=0;
#define SHIFT	2		/* 2:設定ｻﾝﾌﾟﾘﾝｸﾞ時間250ms 	*/
GLOBAL	double	KK;		/*  比例ゲイン			*/
GLOBAL	double	KI;		/*  積分ゲイン			*/
GLOBAL	double	KD;		/*  微分ゲイン			*/
GLOBAL	double	SMV;		/*  操作量			*/
GLOBAL	double	SM0;		/*  操作量 比例＋積分		*/
GLOBAL	double	UM0;		/*  操作量 微分			*/
GLOBAL	double	SMN;		/*  １ｻｲｸﾙ前の操作量		*/
GLOBAL	double	UMN;		/*  １ｻｲｸﾙ前の操作量 微分	*/
GLOBAL	WORD	SEK0;		/*  偏差量			*/
GLOBAL	WORD	SEK1;		/*  １ｻｲｸﾙ前の偏差量		*/
GLOBAL	double	U1K;		/*  比例操作量			*/
GLOBAL	double	U2K;		/*  積分操作量	 		*/
GLOBAL	double	U2K_1;		/*  一回前積分操作量 		*/

GLOBAL 	WORD 	II;		/* 積分定数:1sec/bit # */
GLOBAL 	WORD 	DD;		/* 微分定数:1sec/bit # */


#define	NORM_PID	00		/* PID制御(従来)	*/
#define	AROM_PID	01		/* PID制御(A-Rom)	*/
#define	DEF_APC		10		/* 適応予測制御(発熱なし)*/
#define	SPM_APC		11		/* 適応予測制御(硫酸過水)*/
#define	SC2_APC		12		/* 適応予測制御(塩酸過水)*/
#define	AT_APC		13		/* 新しいATモード*/
/* 適応予測制御の機能追加			99/08/17 T.Arita*/
GLOBAL	WORD	AP_RESET_T;	/* 制御ﾊﾟﾗﾒｰﾀﾘｾｯﾄ温度:0.01℃/bit */
/* 適応予測制御の機能追加			99/09/06 T.Arita*/
/*  定常偏差補正速度の追加					*/
GLOBAL	WORD	AP_THHS;	/* 定常偏差補正速度:0.01/bit */
GLOBAL	WORD	AP_tau_B_S;	/* 設定変更の確認ﾊﾞｯﾌｧ */
GLOBAL	WORD	AP_0_B_S;	/* 設定変更の確認ﾊﾞｯﾌｧ */
GLOBAL	WORD	AP_tau_D;	/* 自動設定ﾓｰﾄﾞの計算値 */
GLOBAL	WORD	AP_0_D;		/* 自動設定ﾓｰﾄﾞの計算値 */
GLOBAL	WORD	AP_RESET_T_D;	/* 自動設定ﾓｰﾄﾞの計算値 */
GLOBAL	WORD	AP_THHS_D;	/* 自動設定ﾓｰﾄﾞの計算値 */
/* ﾓﾆﾀ通信用変数 */
GLOBAL	WORD	AP_tau_M;
GLOBAL	WORD	AP_0_M;
GLOBAL	WORD	AP_SV_M;


GLOBAL 	UBYTE 	AT_END;		/* AT終了ﾌﾗｸﾞ */
#define	BYTE	char			/*  signed byte 	*/
GLOBAL	BYTE	GET_PV_DATA;	/*  現在温度の取得OK		*/
#define	ON		1
#define	OFF		0
#define rst_at() ATF.d = 0;
LONG	hokan(LONG,LONG *,WORD)	;
double time;
