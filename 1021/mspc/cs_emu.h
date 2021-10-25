/*#include "cs.h"*/
/*GLOBAL	UBYTE	MV_N;		/*  �����	: 0.5��/bit	*/
/*************************************************************/
/*�ȉ��͎��ۂ̃R���p�C���ł͕K�v�Ȃ��i���Ō���j������       */
/*************************************************************/
#define GLOBAL 
#define M_MAX 100                /* ����ʏ��:200%          */
#define M_MIN 0                  /* ����ʉ���:0%            */
#define	UBYTE	unsigned char		/*  unsigned byte	*/
#define	WORD	int  		/*  signed word:16 bits	*/
#define	LONG	long			/*  signed long:32 bits	*/

double SMV;        /* ����� 0-200%   */
double PV1;        /* ���́F�Z���T���x PV1���x 0.01��/bit*/

GLOBAL	UBYTE	C_WDT;		/*  �����ޯ���ϰ ����		*/
GLOBAL 	UBYTE	MODE_TYPE=0x00;		/* ���[�h�^�C�v */
GLOBAL 	UBYTE 	RUN=1;		/* 0:��~��,1:�^�]�� */
#define	STD_MODE	0x02	/*  �ʏ�Ӱ��			*/
#define chk_ad_data()   ;
#define chk_ad_hokan()  ;
#define chk_at_calc()   ;	
GLOBAL 	WORD SV;              /* ����p�ڕW�l:  0.01��/bit*/
#define SSV     SV
/* �ݒ�ύX�׸� */
struct 	CHG_FLG{
	UBYTE 	SV:	1;	/* �ڕW���x�ݒ�ύX�L�� */
	UBYTE 	P:	1;	/* ���萔�ݒ�ύX�L�� */
	UBYTE 	I:	1;	/* �ϕ��萔�ݒ�ύX�L�� */
	UBYTE 	D:	1;	/* �����萔�ݒ�ύX�L�� */
	UBYTE 	reserve:4;
};
GLOBAL 	union 	CHG{
	struct 	CHG_FLG  b;
	UBYTE 	d;
} CHG;
struct 	AT_FLG {
	/* �K���\������̑g��			99/07/29 T.Arita*/
/*	UBYTE 	reserve:	3;*/
	UBYTE 	reserve:	2;
	UBYTE 	AT_APC_F:	1;	/* �K���\������AT�׸� */
	UBYTE 	AT_CALC_F:	1;	/* AT�v�Z�J�n�׸� */
	UBYTE 	AT_ZC_F:	1;	/* ��۸۽�׸� */
	UBYTE 	AT_CYCLE_F:	1;	/* ���Z�����׸� */
	UBYTE 	AT_MV:		1;	/* AT����l�u�����׸� */
	UBYTE 	AT_RUN_F:	1;	/* ����On�׸� */
};

GLOBAL	union	ATF	{		/*  �������ݸސ����׸�	*/
	struct	AT_FLG	b;
	UBYTE	d;
} ATF;

/*************************************************************/
/*�������ȏ�͎��ۂ̃R���p�C���ł͕K�v�Ȃ��i���Ō���j       */
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
/* �}�j���A���ݒ�p */
int AP_tau=1000; /* 1sec/bit  �������x�p�����^*/
int AP_0=1250;   /* 0.001/bit �������x�p�����^*/
double AP_under=0.2;            /* �A���_�[�V���[�g�␳*/
int AT_FLAG=0;
#define SHIFT	2		/* 2:�ݒ�����ݸގ���250ms 	*/
GLOBAL	double	KK;		/*  ���Q�C��			*/
GLOBAL	double	KI;		/*  �ϕ��Q�C��			*/
GLOBAL	double	KD;		/*  �����Q�C��			*/
GLOBAL	double	SMV;		/*  �����			*/
GLOBAL	double	SM0;		/*  ����� ���{�ϕ�		*/
GLOBAL	double	UM0;		/*  ����� ����			*/
GLOBAL	double	SMN;		/*  �P���ّO�̑����		*/
GLOBAL	double	UMN;		/*  �P���ّO�̑���� ����	*/
GLOBAL	WORD	SEK0;		/*  �΍���			*/
GLOBAL	WORD	SEK1;		/*  �P���ّO�̕΍���		*/
GLOBAL	double	U1K;		/*  ��ᑀ���			*/
GLOBAL	double	U2K;		/*  �ϕ������	 		*/
GLOBAL	double	U2K_1;		/*  ���O�ϕ������ 		*/

GLOBAL 	WORD 	II;		/* �ϕ��萔:1sec/bit # */
GLOBAL 	WORD 	DD;		/* �����萔:1sec/bit # */


#define	NORM_PID	00		/* PID����(�]��)	*/
#define	AROM_PID	01		/* PID����(A-Rom)	*/
#define	DEF_APC		10		/* �K���\������(���M�Ȃ�)*/
#define	SPM_APC		11		/* �K���\������(���_�ߐ�)*/
#define	SC2_APC		12		/* �K���\������(���_�ߐ�)*/
#define	AT_APC		13		/* �V����AT���[�h*/
/* �K���\������̋@�\�ǉ�			99/08/17 T.Arita*/
GLOBAL	WORD	AP_RESET_T;	/* �������Ұ�ؾ�ĉ��x:0.01��/bit */
/* �K���\������̋@�\�ǉ�			99/09/06 T.Arita*/
/*  ���΍��␳���x�̒ǉ�					*/
GLOBAL	WORD	AP_THHS;	/* ���΍��␳���x:0.01/bit */
GLOBAL	WORD	AP_tau_B_S;	/* �ݒ�ύX�̊m�F�ޯ̧ */
GLOBAL	WORD	AP_0_B_S;	/* �ݒ�ύX�̊m�F�ޯ̧ */
GLOBAL	WORD	AP_tau_D;	/* �����ݒ�Ӱ�ނ̌v�Z�l */
GLOBAL	WORD	AP_0_D;		/* �����ݒ�Ӱ�ނ̌v�Z�l */
GLOBAL	WORD	AP_RESET_T_D;	/* �����ݒ�Ӱ�ނ̌v�Z�l */
GLOBAL	WORD	AP_THHS_D;	/* �����ݒ�Ӱ�ނ̌v�Z�l */
/* ����ʐM�p�ϐ� */
GLOBAL	WORD	AP_tau_M;
GLOBAL	WORD	AP_0_M;
GLOBAL	WORD	AP_SV_M;


GLOBAL 	UBYTE 	AT_END;		/* AT�I���׸� */
#define	BYTE	char			/*  signed byte 	*/
GLOBAL	BYTE	GET_PV_DATA;	/*  ���݉��x�̎擾OK		*/
#define	ON		1
#define	OFF		0
#define rst_at() ATF.d = 0;
LONG	hokan(LONG,LONG *,WORD)	;
double time;
