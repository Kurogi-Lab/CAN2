/********************************************************
multiple models
次の4つの定義文のうち，ひとつだけコメントをはずして使用すること．
gcc -E -DEMULATE emulate.c >emulate.cccとするとプリプロセッサ結果
********************************************************/
#include <string.h>
void outer_world();
/*#define GPC2/**/
/*#define APC2/**/
/*#define APC1/**/
/*#define GPC1/**/
/////////////////////////
#define MSPC/*multiple models*/
/*********************************************************/
/*#define GAIRANGO_SHOKIKA/*外乱後，定常偏差補正を初期化する*/
/*#define HAJIME_BY_APC/*制御開始時にAPCを使うとき:KELKのSPMでは望ましくない*/
/*********************************************************/
#define FLT
#undef FLT
#ifdef FLT
#define FLOAT float
#define LF "%f"
#else
#define FLOAT double
#define LF "%lf"
#endif

static int hiro=0;
//int AP_KyoyouOndoGosa; /*許容温度誤差：外乱復帰高速化99/11/22 S.Kurogi*/
//FLOAT AP_HoseiKaisiOndo; /* 定常偏差補正開始温度99/11/22 S.Kurogi*/
#ifdef EMULATE
//#define AP_TS1 0.5//2//0.5//2//0.5//12//0.5 //Virtual Sampling Period 仮想サンプリング周期
#define AP_TS1 0.5//2//0.5//2//0.5//12//0.5 //Virtual Sampling Period 仮想サンプリング周期
GLOBAL	WORD AP_N2=10/AP_TS1; // soso N2=20=10/0.5
//GLOBAL	WORD AP_N2=9/AP_TS1; // soso 
//GLOBAL	WORD AP_N2=10/AP_TS1; // soso ICONIP2011
//GLOBAL	WORD AP_N2=20/AP_TS1; // soso 
//GLOBAL	WORD AP_N2=15/AP_TS1; // soso 
//GLOBAL	WORD AP_N2=20*0.5/AP_TS1; //20 soso 
//GLOBAL	WORD AP_N2=20; //20 soso 
//#define AP_TS1 0.5//2//0.5//2//0.5//12//1.0 //
//GLOBAL	WORD AP_N2=10; //AP_NP=AP_N2,AP_N1=0
//GLOBAL	WORD AP_N1=0; //AP_NP=AP_N2,AP_N1=0
//GLOBAL	double AP_LAMBDA=0.05;//OK
#undef originalGPC
#define originalGPC
//GLOBAL	double AP_LAMBDA=0.2;//good for original
#if CRANESUB == 1 || CRANESUB == 3
//GLOBAL	double AP_LAMBDA=0.02;//good for original
GLOBAL	double AP_LAMBDA=0.2;//good for original
//GLOBAL	double AP_LAMBDA=0.2;//good for original
#else 
GLOBAL	double AP_LAMBDA=0.01;//good for original
#endif
GLOBAL	WORD AP_NU=1;	//AP_NU=AP_N2
//GLOBAL	WORD AP_NU=10/AP_TS1-1;	//AP_N2=AP_NU+1 20170122
double mypow2(double x){return(x*x);}
//#define mypow2(x) ((x)*(x))
//#define mypow2(x) pow(x,2.0)
#endif
#ifdef MSPC
#define AP_ny 4//4//4//4//4//4//4//4//4//4//4//4//4//4//4//4//4//4//4//4
#define AP_nu 4//4//4//4//4//4//4//4//4//4//4//4//4//4//1//1//1//1//4//4
int CAN2_T=20;
int CAN2_k=AP_ny+AP_nu;
#undef SPM_REINIT_BY_KASO
#endif

#define AP_NP AP_N2       /*Npが大だとハンチングを抑える*/
//#define AP_NU AP_N2

#define AP_NN (AP_nu+AP_ny+1) /**/
/*MSPC********************************************************/
// replace define AP_NC to emulate.c for cross-validation 
//int AP_NC=1; /*Number Of Cells*/
int AP_NC[200]={1,}; /*Number Of Cells*/
#define theta_e 0.1 /*Error Limit 水の即応性には0.4以下*/
#define theta_v 100
#define AP_IS 2//2//2//2//2//2
int it;
double Err;
char *net0;//050621 modified by kuro
//char net_1[100]; //071203yuno .netファイルのファイル名を保存する配列 
//char net_2[100]; //071203yuno .netファイルのファイル名を保存する配列
char net_n[10][fnsize];//080129yuno .netファイルのファイル名を保存する配列
//char net_n[10][100];//080129yuno .netファイルのファイル名を保存する配列
//char *net_f=&net_n[0][0];
//char net_f[100]; /*060224kuwa .netファイルのファイル名を保存する配列*/
int rise_time,stable_time=0;//050704 tomisaki
#define file_data_N 100
int add_data_N=0; /*tomisaki*/
//double result_data[file_data_N];
//int result_it[file_data_N];
int add_dat[5]={0,0,0,0,0};//tomisaki argv[i] に入っている.datファイルのiの番号
char **dat_file;
//modified tomisaki 2005/11/9
GLOBAL int *st_AP_i;//GLOBAL int st_AP_i[100];//tomisaki 複数のCAN2を用いたときにAP_iを格納
//if(ensemble!=0) st_AP_i=(int*)malloc(sizeof(int)*(net_num+1));
//(num_boosts+1)*(resample_num+1)*n_AP_NC ??
//100>net_num=num_boosts*resample_num*n_AP_NC or (num_boosts*n_AP_NC+n_AP_NC)=(num_boosts+1)*n_AP_NC
GLOBAL int ensemble=0;//アンサンブル学習を使うのか?
GLOBAL int useensrs=1;//ensrsを使うのか?
GLOBAL int f_AP_NC=1;//??printf("The ID number of the first cell:");
GLOBAL int e_AP_NC=1; //kuwa060223 printf("The ID number of the last cell:")
GLOBAL int n_AP_NC=1; //kuwa060224 アンサンブルユニットの数 n_AP_NC=e_AP_NC-f_AP_NC+1;
//modified tomisaki 2005/11/31
int obtain_new=0;//sellect unit by weight vector
int matrix_0=0;//Matrix initial value = 0
int num_tems=0;//number of trained ensemble machines which will be loaded by net-files  //201204kuro 
int num_nets=0;//num_nets=(num_tems+1)*num_bags?
int num_bags=0;//int bag_b=1;//resample_num=bag_b
//double bag_alpha=0.7;//bag_alpha
int bag_seed=1;
int u_limit=0;
double error_hyouka=0;
//double y_pre[100];
//double y_pre[100];
//double F_err[100];
//double y_pre1;
//double u_old;
//double u_old1;
int penalty=0;//-->3
int code;
//int gakusyu=0;

/*bagboostの導入に用いた変数 2006kuwa*/
GLOBAL int bagging_flag=0;
GLOBAL int bagging_flag201204=0;
GLOBAL double bag_alpha=0.7;//1;
GLOBAL int boosting_flag=0;
GLOBAL int num_boosts=1;
GLOBAL double *boosting_c_t,c_t_sum;
//GLOBAL double boosting_c_t[100],c_t_sum;
GLOBAL int resample_num=1;
int net_num;//number of net for boosting?net_num=num_boosts*resample_num*n_AP_NC;?
//090622 yuno
/*080311koshi ネットの統合に用いた変数*/
GLOBAL int ave_flag=0;
GLOBAL int uni_flag=0;
GLOBAL int uni=0;
//GLOBAL int cell_num=0;
//GLOBAL int *uni_AP_NC;//
GLOBAL int uni_AP_NC[10]={0,0,0,0,0,0,0,0,0,0};

//081010koshi 変数
GLOBAL int nuse_flag=0; //merge or select ?
GLOBAL int *st_n_AP_i;//GLOBAL int st_n_AP_i[100];// 複数のCAN2を用いたときにAP_iを格納
GLOBAL int AP_n_out=0;//081013 koshi 
GLOBAL FLOAT *n_err;//GLOBAL FLOAT n_err[100];//to save in y_matrix.dat
//GLOBAL FLOAT ndy=0;
//GLOBAL FLOAT ndy2=0;
GLOBAL FLOAT AP_n_err=0;

GLOBAL int   AP_n_kk;/*制御開始からの時刻カウンタ,エネルギ計算のため*/
GLOBAL int AP_n_kk_Ne;
//10>num_nets
GLOBAL FLOAT *energy_sum_n;//[10]={0,0,0,0,0,0,0,0,0,0}; /*自乗誤差の合計*/
GLOBAL FLOAT *energy_n1;//[10]={0,0,0,0,0,0,0,0,0,0}; /*1ステップ分の自乗誤差*/
GLOBAL FLOAT *energy_n;//[10]={0,0,0,0,0,0,0,0,0,0}; /*エネルギ*/
GLOBAL FLOAT *energy_mean_n;//[10]={0,0,0,0,0,0,0,0,0,0}; /*エネルギの平均*/
GLOBAL FLOAT **mse;//[10][32000];
//GLOBAL FLOAT energy_sum_n[10]={0,0,0,0,0,0,0,0,0,0}; /*自乗誤差の合計*/
//GLOBAL FLOAT energy_n1[10]={0,0,0,0,0,0,0,0,0,0}; /*1ステップ分の自乗誤差*/
//GLOBAL FLOAT energy_n[10]={0,0,0,0,0,0,0,0,0,0}; /*エネルギ*/
//GLOBAL FLOAT energy_mean_n[10]={0,0,0,0,0,0,0,0,0,0}; /*エネルギの平均*/
//GLOBAL FLOAT mse[10][32000];

//#define eval_period 180//mseの保存時間
//#define eval_period 110//mseの保存時間=MSE Ne=eval_period*AP_tS/AP_TS1 for swiching CAN2
//#define eval_period 60//mseの保存時間=MSE Ne=eval_period*AP_tS/AP_TS1 for swiching CAN2
//GLOBAL int Ne=20;//iconip2014 ユニット選択のための過去誤差計算範囲
GLOBAL int Ne=10;//iconip2014 ユニット選択のための過去誤差計算範囲
//GLOBAL int Ne=8;//evaluation period;mseの保存時間=MSE eval_period=Ne*AP_TS1=Ne*0.5 for swiching CAN2 ユニット選択のための過去誤差計算範囲
//GLOBAL int Ne=12;//evaluation period;mseの保存時間=MSE eval_period=Ne*AP_TS1=Ne*0.5 for swiching CAN2 ユニット選択のための過去誤差計算範囲
//GLOBAL int Ne=20;//evaluation period;mseの保存時間=MSE eval_period=Ne*AP_TS1=Ne*0.5 for swiching CAN2
//GLOBAL int Ne=20;//evaluation period;mseの保存時間=MSE eval_period=Ne*AP_TS1=Ne*0.5 for swiching CAN2
//#define eval_period 50//mseの保存時間=MSE Ne=eval_period*AP_tS/AP_TS1 for swiching CAN2
GLOBAL FLOAT SMV_nn;
GLOBAL FLOAT *SMV_n;//GLOBAL FLOAT SMV_n[10];
GLOBAL int p_net=0;
GLOBAL FLOAT p_nerr,perr;
//GLOBAL FLOAT p_err[10];
GLOBAL int flag=1;
GLOBAL FLOAT AP_yyn;
GLOBAL FLOAT *AP_yn;//GLOBAL FLOAT AP_yn[10];
GLOBAL int stab1=-1;//i_mse_min
GLOBAL int stab2=-1;//AP_i
GLOBAL int stab3=-1;//time
GLOBAL FLOAT stab4=0.5;//time
GLOBAL FLOAT crane_X;//20200123Ohgi
//一次差分信号
GLOBAL int difference_flag=1; //2007/12/21/koshi

#define N_matrix 8
#define Q_weight 100.
#define R_weight 1.
double over_r=1.;
double umin_l[N_matrix];
#define D_LAM 0.1
#define D_LAM1 0.001

#define maxn    15          /* Max number of variables   */
#define maxm    15          /* Max number of constraints */
#define maxnz  150          /* Max number of nonzeroes in A */
#define maxqnz 100          /* Max number of nonzeroes in Q */

char yesno[5];//answer (yes or no) for a question
void inv_matrix(double inv_a[N_matrix][N_matrix],double inv_c[N_matrix][N_matrix]);
void tenti(double x_m[N_matrix][N_matrix],int m_m,int n_m,double y_m[N_matrix][N_matrix]);
void multiply(double x_m[N_matrix][N_matrix],int m_m, int n_m,double y_m[N_matrix][N_matrix],int l_m,double z_m[N_matrix][N_matrix]);
char *listSS=NULL;

extern void bpmpd(int *, int *, int *, int *, int *, int *, int *,
       double *, int *, int *, double *, double *, double *, double *,
       double *, double *, double *, int *, double *, int *, double *, int *);
double M00[20]={-1000,};//-1000 is nouse for default.//20150210

/*********************************************************/
void init_MQ_AP(void);          /* 行列の初期化    */
/*void AM_AP(FLOAT *,FLOAT);    /* 最小２乗記憶法  */
/*FLOAT predict_search_AP(void); /* 予測入力探索    */
void set_AP_r(void);            /* 目標温度が変わったとき !!! 99/06/25*/
void reinit_AP(void);           /* 適応制御変数の再初期化 */
void init_AP(void);             /* 適応制御変数の初期化*/
void calc_AP(void);             /* 適応予測制御演算 */

//#ifndef MSPC
//void calc_AP_tau(void);          /* 新しいAT実行後のtauの計算*/
//void exec_AT_APC(void);          /* 新しいATの実行モード*/
//#endif

#ifdef SPM_REINIT_BY_KASO
void spm_reinit_AP();
#endif

/*********************************************************/
/* ATモードを廃止し、ATFふらぐを使用する	99/11/08 T.Arita*/
/*#define	AT_APC		13		/* 新しいATモード*/
#define AP_approx(x,y1,x1,y2,x2) (((y2)-(y1))*((x)-(x1))/((x2)-(x1))+y1)
/* ATでのAP_tauの算出方法の変更		99/08/17 T.Arita*/
#define AP_hosei(x,y,a,b,c,d) (a*x*y + b*x + c*y + d)
#undef fabs
#define fabs(x) (((x)>0)?(x):-(x))
#undef PI
#define PI 3.14159265358979323846
#define AP_ZERO 1.0e-10          /*  零	   */
#define YB 100.0            /*実際の温度との比率 YB=PV1/TB */
//#define AP_r (SV/YB)         /*=SV/100.;SV:水などの場合可変:制御用目標値:0.01℃/bit*/
double AP_r;         /*=SV/100.;SV:水などの場合可変:制御用目標値:0.01℃/bit*/
/*********************************************************/
/*新AT用*/

//#ifndef MSPC
//FLOAT AP_AT_y[7];
//FLOAT AP_AT_j[6];
//int AP_AT_cycle;
//FLOAT AP_AT_jikan;
//FLOAT AP_AT_seitei;
//FLOAT AP_AT_seiteijikan;
//FLOAT AP_AT_seiteijikan_saitan;
//int AP_AT_Np_opt;
//FLOAT      AP_Q[AP_NN][AP_NN];
//FLOAT      AP_M[1][AP_NN];
//#endif

/*MSPC********************************************************/
#ifdef MSPC
typedef struct {
  FLOAT v;/*価値（発火回数、アクセス頻度）*/
  //  FLOAT Q[AP_NN][AP_NN];//no need now
  FLOAT **Q;//  FLOAT Q[AP_NN][AP_NN];//no need now
  FLOAT **M;//  FLOAT M[1][AP_NN];
  FLOAT *w;//  FLOAT w[AP_nu+AP_ny];
  FLOAT *_M,*_Q;
} CELL;
typedef struct {
  int firstcall;
  CELL *cell;//  CELL cell[100];//配列の中身はAP_NC_MAX(50)だった
  int n_cells;
  int k;//AP_NN=AP_nu+AP_ny
} NET;
typedef struct {
  NET *net;
  int num_tems;
  int num_bags;//  int num_nets;
  char *dname;//directory name
  double *se;//square error
} TEM;//Trained ensemble machines
TEM *tem;
NET *net;//NET net[500];//modify tomisaki 2005/11/9
int AP_i=0;
int AP_i1=0;//081022yuno学習後の連想行列を平均化するときにAP_iを格納
int AP_i2=0;
int net_yu =AP_nu+AP_ny,yu,l;//yuno081022
#endif
/*********************************************************/
FLOAT AP_y;             /*AP_y=PV1/100.; PV1 入力：センサ温度 PV1温度 0.01℃/bit*/
FLOAT AP_u;             /* 操作量 [-1:1] [0:200] */
FLOAT AP_u_max;         /* 操作量上限:1,  200 *///  AP_u_max=M_MAX;  /*入力最大値の設定 */
FLOAT AP_u_min;         /* 操作量下限:-1, 0   *///  AP_u_min=M_MIN;  /*入力最大値の設定 */ //061227kuwa
typedef struct{
  int method;
  int totaltime;
  int Tu;
  FLOAT Ru;
  int nTu;
  int nRu;
  int time_i0;
  int time_i;
  int nphase;
  FLOAT u;
} U4IT0;
U4IT0 u4it0[1]={0,0,5,0.8,0};
//FLOAT AP_ur0=0.8;//AP_ur0*AP_umax for it=0
//FLOAT AP_uT0=5;//AP_ur0*AP_umax for it=0
/*************************************************************/
//#define AP_TO 25.  /*  外部温度（仮想でよい）*/
#ifdef CRANESUB
double AP_tS=0.01; 
//#define AP_tS 0.01 /*サンプリング周期(秒) sampling period*/
//AP_tS=0.01 /*サンプリング周期(秒) sampling period*/, AP_TS1=0.5////Virtual Sampling Period 仮想サンプリング周期
//double AP_tS=0.01; /*サンプリング周期(秒) sampling period*/
#else
double AP_tS=0.25;
//#define AP_tS 0.25 /*0.25?サンプリング周期(秒) sampling period*/
#endif
#define Gensui(tau) (1.-4.*AP_tS/(tau)) /*理想はGensui(tau)=exp(-4*AP_tS/tau);/**/
#define INFTY 1e20
//#define AP_ZERO 1e-20
#ifndef MSPC
FLOAT      AP_u_res;/*入力解像度;大きいと早い．振れは大きい．*/
#endif
FLOAT      AP_y_k;
FLOAT      AP_y_k_minus_1;
FLOAT      AP_u_k;
FLOAT      AP_u_k_minus_1;
FLOAT      *AP_z;//FLOAT      AP_z[AP_NN+2];/*2007/02/18/koshi*/
FLOAT      AP_overshoot;/*OverShoot*/
//090622 yuno
/*****************080508 koshi 一次差分信号を保存するため************/
FLOAT      *AP_d;//AP_d[AP_NN];
FLOAT      *AP_du;//AP_du[AP_NN]; 
FLOAT      *AP_dy;//AP_dy[AP_NN];
/********************************************************************/
#ifndef MSPC
FLOAT      AP_y_under;/*定常偏差補正*/
FLOAT      AP_y_under2;/*定常偏差補正*/
FLOAT      AP_y_reach;
FLOAT      AP_y_ave;
#endif

#ifdef SPM_REINIT_BY_KASO
int      AP_y_reach1;
#endif

#ifndef MSPC
FLOAT      AP_y_smooth;
FLOAT      AP_y_smooth_r;
FLOAT      AP_y_smooth_tau;
#endif

FLOAT      AP_y_sum[AP_ny+AP_IS+1];
FLOAT      AP_yy[AP_ny+AP_IS];
FLOAT      AP_u_sum[AP_nu+AP_IS+2];
FLOAT      AP_uu[AP_NN+AP_IS];
FLOAT      AP_kS1;
FLOAT      AP_tS1;/*仮想サンプリング周期(秒)*/
FLOAT      AP_k;/*時刻カウンタ(秒)*/
FLOAT      AP_k_hajime;/*時刻カウンタ(秒)*/
FLOAT      AP_kk;/*制御開始からの時刻カウンタ,エネルギ計算のため*/
FLOAT      AP_yyy;/*予測出力値*/
FLOAT      energy_sum=0; /*自乗誤差の合計*/
FLOAT      energy1=0; /*1ステップ分の自乗誤差*/
FLOAT      energy=0; /*エネルギ*/
FLOAT      energy_mean=0; /*エネルギの平均*/
FLOAT      _AP_RESET_T;
int _AP_THHS; /* 定常偏差補正速度の実行用:1分/bit */
/*************************************************************/
//#ifndef EMULATE
///* 適応予測制御の機能追加			99/11/08 T.Arita*/
///* 機能追加分の変数をAPC.cで参照すると				*/
///* TOO MANY EXTERNAL IDENTIFIERSエラーとなる為、			*/
///* APC.cで使用するインクルードファイルを別ファイルにする			*/
///*#include "CS.H"  */
//#define	APC_KELK
//#include "CS_APC.H"
//extern LONG hokan(LONG,LONG *,WORD);
//#endif
//#ifndef MSPC
//#define AP_AT_TBL_N 11
//const	LONG	AP_AT_TBL[2][AP_AT_TBL_N] = {
//   121, 223, 276, 319, 333, 351, 369, 390, 409, 726, 1420,/*487, 520, 1270,*/
//  -796,-272,-147,   0,  53, 125, 199, 215,1242,1796, 2234/*814, 802, 1060*/
//}; /**/
//#endif
//#ifdef AP_NN3
///*********************************************************/
//void init_MQ_AP(void)                 /* 行列の初期化    */
///*********************************************************/
//{
//  AP_M[0][0]=+1.019383e-02;
//  AP_M[0][1]=+9.295959e-03;
//  AP_M[0][2]=+9.939551e-01;
//  AP_Q[0][0]=+1.000000e+04;
//  AP_Q[0][1]=-1.197140e-09;
//  AP_Q[0][2]=-6.794222e-09;
//  AP_Q[1][0]=-1.197140e-09;
//  AP_Q[1][1]=+8.400848e-10;
//  AP_Q[1][2]=-6.164823e-10;
//  AP_Q[2][0]=-6.794222e-09;
//  AP_Q[2][1]=-6.163944e-10;
//  AP_Q[2][2]=+6.748715e-10;
//}
//#endif
//#ifdef AP_NN4
///*********************************************************/
//void init_MQ_AP(void)                 /* 行列の初期化    */
///*********************************************************/
//{
//  AP_M[0][0]=-4.500449e-02;
//  AP_M[0][1]=+2.173344e-02;
//  AP_M[0][2]=+9.913619e-01;
//  AP_M[0][3]=+2.480479e-03;
//  AP_Q[0][0]=+9.999940e+03;
//  AP_Q[0][1]=-1.758429e-04;
//  AP_Q[0][2]=-8.640277e-04;
//  AP_Q[0][3]=+5.228297e-06;
//  AP_Q[1][0]=-1.758429e-04;
//  AP_Q[1][1]=+1.017217e-07;
//  AP_Q[1][2]=-2.661719e-07;
//  AP_Q[1][3]=+2.308460e-07;
//  AP_Q[2][0]=-8.640277e-04;
//  AP_Q[2][1]=-2.661719e-07;
//  AP_Q[2][2]=+1.096935e-05;
//  AP_Q[2][3]=-1.088859e-05;
//  AP_Q[3][0]=+5.228297e-06;
//  AP_Q[3][1]=+2.308451e-07;
//  AP_Q[3][2]=-1.088859e-05;
//  AP_Q[3][3]=+1.082415e-05;
//}
//#endif//#ifdef AP_NN4

#ifdef MSPC
//NET *pnet;
int _net_load(NET *net,char *fname,int temid){//temmid=treined ensemble machine id
  //int net_load(NET *net,char *fname,int a_n,int units){
  int a_n=0;
  int units=AP_NC[temid];
  int i, k, l;
  FILE *fp;
  FLOAT dummy;
  int idummy;
  double ddummy;
//  {//    check memory allocation
//    //    fprintf(stderr,"pnet=%p before\n",pnet);
//    FILE *fp;if((fp = fopen("can2b.net", "r"))==NULL) {
//      fprintf(stderr,"##2# netfile:'%s' open err.\n","can2b.net");
//      exit(-1);
//    }
//    else fclose(fp);
//    //    double *dum=(double*)malloc(sizeof(double)*10000);free(dum);
//    //    fprintf(stderr,"pnet=%p after\n",pnet);
//  }
  if(fname==NULL){
    printf("Name of the Net File:");
    char fn[fnsize];
    fn[0]=0;scanf("%s",fn);
    if(fn[0]==0) return(0);
    if((fp = fopen(fn, "r"))==NULL){
      fprintf(stderr,"#apc_crane.c:L470 netfile:'%s' open err.\n",fn);
      exit(-1);
      //      return(1);
    }
  }
  else{
    fprintf(stderr,"#apc_crane.c:L478 netfile:'%s' ",fname);fflush(stderr);
    if((fp = fopen(fname, "r"))==NULL) {
      fprintf(stderr,"#open err.\n");
      exit(-1);
      //      return(-1);
    }
    else fprintf(stderr,"opened.\n");

  }
  fread(&(net->n_cells),sizeof(int),1,fp);//net->n_cells  fread(&(idummy),sizeof(int),1,fp);//net->n_cells    
  fread(&(idummy),sizeof(int),1,fp);//net->winit  
  fread(&(idummy),sizeof(int),1,fp);//GlobalTime
  fread(&(idummy),sizeof(int),1,fp);//ReinitTime
  //2006/2/2 tomisaki
  fread(&(idummy),sizeof(int),1,fp);//CAN2_k
  fread(&(idummy),sizeof(int),1,fp);//net->n_compare
  fread(&(ddummy),sizeof(double),1,fp);//net->v_thresh
  fread(&(idummy),sizeof(int),1,fp);//net->vmin
  fread(&(idummy),sizeof(int),1,fp);//net->vmin2
  fread(&(idummy),sizeof(int),1,fp);//net->vmax
  fread(&(ddummy),sizeof(double),1,fp);//et->v_ratio
  fread(&(ddummy),sizeof(double),1,fp);//net->width
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymin
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymax
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ywidth
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymin0
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymax0
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ywidth
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->xmin
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->xmax
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->xwidth
  fread(&(idummy),sizeof(int),1,fp); //net->r1
  if(idummy>0){//if(net->r1>0)
    fread(&(idummy),sizeof(int),1,fp);
    fread(&(idummy),sizeof(int),1,fp);
    fread(&(dummy),sizeof(FLOAT),1,fp);
    for(i=0;i<=idummy;i++){
      fread(&(dummy),sizeof(FLOAT),1,fp);
      fread(&(dummy),sizeof(FLOAT),1,fp);
    }
  }
  for(i=0;i<units;i++){
    for(k=0; k< CAN2_k; k++) fread(&(net[0].cell[i].w[k]),sizeof(FLOAT),1,fp);
    for(k=1; k<=CAN2_k; k++) fread(&(net[0].cell[i].M[0][k]),sizeof(FLOAT),1,fp);
    k=0;fread(&(net[0].cell[i].M[0][k]),sizeof(FLOAT),1,fp);
    //    fprintf(stderr,"sizeofQ=%d\n",sizeof(net[0].cell[i]._Q));
    if(1==0){
      for(k=0; k<AP_NN*AP_NN; k++) fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].S
    }
    else if(1==0){
      for(k=1; k<=CAN2_k; k++){
	for(l=1; l<=CAN2_k; l++)fread(&(net[0].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);
	l=0; fread(&(net[0].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);//because AP_z[0]=1
      }
      k=0;
      for(l=1; l<=CAN2_k; l++) fread(&(net[0].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);
      l=0; fread(&(net[0].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);
    }
    else {
      for(k=1; k<=CAN2_k; k++){
	for(l=1; l<=CAN2_k; l++){
	  //	  fprintf(stderr,"?? i%dj%dk%dl%d, net_Q%p\n",0,i,k,l,&net[0].cell[i]._Q[k*AP_NN+l]);
	  //	  fprintf(stderr,"?? i%dj%dk%dl%d, netQ%p\n",0,i,k,l,&net[0].cell[i].Q[k][l]);
	  fread(&(net[0].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
//	  if(&net[0].cell[i].Q[k][l]!=&net[0].cell[i]._Q[k*AP_NN+l]){
//	    fprintf(stderr,"NG i%dj%dk%dl%d %p!=%p\n",0,i,k,l,&net[0].cell[i].Q[k][l],&net[0].cell[i]._Q[k*AP_NN+l]);
//	  }
	}
	l=0;{ 
	  fread(&(net[0].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);//because AP_z[0]=1
//	  if(&net[0].cell[i].Q[k][l]!=&net[0].cell[i]._Q[k*AP_NN+l]){
//	    fprintf(stderr,"NG i%dj%dk%dl%d %p!=%p\n",0,i,k,l,&net[0].cell[i].Q[k][l],&net[0].cell[i]._Q[k*AP_NN+l]);
//	  }
	}
      }
      k=0;
      for(l=1; l<=CAN2_k; l++) fread(&(net[0].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
      l=0; fread(&(net[0].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
    }
    fread(&(net[0].cell[i].v),sizeof(FLOAT),1,fp);
    fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].S
    fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].E
  }
  //  {int 0=0,i=0,k=0,l=0;fprintf(stderr,"???1 i%dj%dk%dl%d, netQ%p\n",0,i,k,l,&net[0].cell[i].Q[k][l]);}
  if(M00[0]!=-1000){//20150210
    net[0].cell[0].M[0][0]=0;
    for(k=1;k<=CAN2_k;k++) net[0].cell[0].M[0][k]=M00[k-1];
  }

  for(i=0;i<units;i++){
    fprintf(stdout,"M[%d]=",i);
    for(k=0; k<=CAN2_k; k++) printf("%f ",net[0].cell[i].M[0][k]);
    fprintf(stdout,"v%g\n",net[0].cell[i].v);
  }
  fclose(fp);
  if(listSS){
    system("mkdir -p tmp");
    FILE *fpM=fopen("tmp/M.dat","a+");
    for(i=0;i<units;i++){
      for(k=1; k<=CAN2_k; k++) fprintf(fpM,"%f ",net[0].cell[i].M[0][k]);
      fprintf(fpM,"%d %g #M1 ... Mk i v\n",i,net[0].cell[i].v);
    }
    fclose(fpM);
  }

  return(0);
}

int net_load(NET *net,char *fname,int a_n,int units){
  int i, k, l;
  FILE *fp;
  FLOAT dummy;
  int idummy;
  double ddummy;
  //  int net_k=AP_nu+AP_ny;
  //  pnet=net;
  //  {int a_n=0,i=0,k=0,l=0;fprintf(stderr,"???0 i%dj%dk%dl%d, netQ%p\n",a_n,i,k,l,&net[a_n].cell[i].Q[k][l]);}
  //  if(1==0){//    check memory allocation
  //    //    fprintf(stderr,"pnet=%p before\n",pnet);
  //    FILE *fp;if((fp = fopen("can2b.net", "r"))==NULL) {
  //      fprintf(stderr,"##2# netfile:'%s' open err.\n","can2b.net");
  //      exit(-1);
  //    }
  //    else fclose(fp);
  //    //    double *dum=(double*)malloc(sizeof(double)*10000);free(dum);
  //    //    fprintf(stderr,"pnet=%p after\n",pnet);
  //  }
  if(fname==NULL){
    printf("Name of the Net File:");
    char fn[fnsize];
    fn[0]=0;scanf("%s",fn);
    if(fn[0]==0) return(0);
    if((fp = fopen(fn, "r"))==NULL){
      fprintf(stderr,"#apc_crane.c:L609 netfile:'%s' open err.\n",fn);
      exit(-1);
      //      return(1);
    }
  }
  else{
    fprintf(stderr,"#apc_crane.c:L615 netfile:'%s' ",fname);fflush(stderr);
    if((fp = fopen(fname, "r"))==NULL) {
      fprintf(stderr," open err.\n");
      exit(-1);
      //      return(-1);
    }
    else fprintf(stderr," opened.\n");

  }
  fread(&(net[a_n].n_cells),sizeof(int),1,fp);//net->n_cells
  fread(&(idummy),sizeof(int),1,fp);//net->winit  
  fread(&(idummy),sizeof(int),1,fp);//GlobalTime
  fread(&(idummy),sizeof(int),1,fp);//ReinitTime
  //2006/2/2 tomisaki
  fread(&(net[a_n].k),sizeof(int),1,fp);//net->k
  fread(&(idummy),sizeof(int),1,fp);//net->n_compare
  fread(&(ddummy),sizeof(double),1,fp);//net->v_thresh
  fread(&(idummy),sizeof(int),1,fp);//net->vmin
  fread(&(idummy),sizeof(int),1,fp);//net->vmin2
  fread(&(idummy),sizeof(int),1,fp);//net->vmax
  fread(&(ddummy),sizeof(double),1,fp);//et->v_ratio
  fread(&(ddummy),sizeof(double),1,fp);//net->width
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymin
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymax
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ywidth
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymin0
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ymax0
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->ywidth
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->xmin
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->xmax
  fread(&(dummy),sizeof(FLOAT),1,fp);//net->xwidth
  fread(&(idummy),sizeof(int),1,fp); //net->r1
  if(idummy>0){//if(net->r1>0)
    fread(&(idummy),sizeof(int),1,fp);
    fread(&(idummy),sizeof(int),1,fp);
    fread(&(dummy),sizeof(FLOAT),1,fp);
    for(i=0;i<=idummy;i++){
      fread(&(dummy),sizeof(FLOAT),1,fp);
      fread(&(dummy),sizeof(FLOAT),1,fp);
    }
  }
  for(i=0;i<units;i++){
    for(k=0; k< CAN2_k; k++) fread(&(net[a_n].cell[i].w[k]),sizeof(FLOAT),1,fp);
    for(k=1; k<=CAN2_k; k++) fread(&(net[a_n].cell[i].M[0][k]),sizeof(FLOAT),1,fp);
    k=0;fread(&(net[a_n].cell[i].M[0][k]),sizeof(FLOAT),1,fp);
    //    fprintf(stderr,"sizeofQ=%d\n",sizeof(net[a_n].cell[i]._Q));
    if(1==0){
      for(k=0; k<AP_NN*AP_NN; k++) fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].S
    }
    else if(1==0){
      for(k=1; k<=CAN2_k; k++){
	for(l=1; l<=CAN2_k; l++)fread(&(net[a_n].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);
	l=0; fread(&(net[a_n].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);//because AP_z[0]=1
      }
      k=0;
      for(l=1; l<=CAN2_k; l++) fread(&(net[a_n].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);
      l=0; fread(&(net[a_n].cell[i]._Q[k*AP_NN+l]),sizeof(FLOAT),1,fp);
    }
    else {
      for(k=1; k<=CAN2_k; k++){
	for(l=1; l<=CAN2_k; l++){
	  //	  fprintf(stderr,"?? i%dj%dk%dl%d, net_Q%p\n",a_n,i,k,l,&net[a_n].cell[i]._Q[k*AP_NN+l]);
	  //	  fprintf(stderr,"?? i%dj%dk%dl%d, netQ%p\n",a_n,i,k,l,&net[a_n].cell[i].Q[k][l]);
	  fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
//	  if(&net[a_n].cell[i].Q[k][l]!=&net[a_n].cell[i]._Q[k*AP_NN+l]){
//	    fprintf(stderr,"NG i%dj%dk%dl%d %p!=%p\n",a_n,i,k,l,&net[a_n].cell[i].Q[k][l],&net[a_n].cell[i]._Q[k*AP_NN+l]);
//	  }
	}
	l=0;{ 
	  fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);//because AP_z[0]=1
//	  if(&net[a_n].cell[i].Q[k][l]!=&net[a_n].cell[i]._Q[k*AP_NN+l]){
//	    fprintf(stderr,"NG i%dj%dk%dl%d %p!=%p\n",a_n,i,k,l,&net[a_n].cell[i].Q[k][l],&net[a_n].cell[i]._Q[k*AP_NN+l]);
//	  }
	}
      }
      k=0;
      for(l=1; l<=CAN2_k; l++) fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
      l=0; fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
    }
    fread(&(net[a_n].cell[i].v),sizeof(FLOAT),1,fp);
    fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].S
    fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].E
  }
  //  {int a_n=0,i=0,k=0,l=0;fprintf(stderr,"???1 i%dj%dk%dl%d, netQ%p\n",a_n,i,k,l,&net[a_n].cell[i].Q[k][l]);}
  for(i=0;i<units;i++){
    fprintf(stdout,"M[%d]=",i);
    for(k=0; k<=CAN2_k; k++) printf("%f ",net[a_n].cell[i].M[0][k]);
    fprintf(stdout,"v%g\n",net[a_n].cell[i].v);
  }
  fclose(fp);
  return(0);
}


/*********************************************************/
void init_MQ_APi(int n,int def,int a_n)  /* 行列の初期化 good?    */
/*********************************************************/
{
  int i,j;

  if(matrix_0==0){
    if(def==1){
      if(n>=0){/*初めはこの設定*/
	for(i=0;i<AP_NN;i++){
	  net[a_n].cell[n].M[0][i]=0;
	  net[a_n].cell[n].v=0;
	  for(j=0;j<AP_NN;j++){
	    if(i==j) net[a_n].cell[n].Q[i][j]=1e0;
	    else  net[a_n].cell[n].Q[i][j]=0;
	  }
	}   
	/*070126kuwa セル数1 初期温度120で1000回制御した値*/
	net[a_n].cell[n].M[0][0]=-0.002515;
	net[a_n].cell[n].M[0][1]=+0.006144;
	net[a_n].cell[n].M[0][AP_nu+1]=+1.631490;
	net[a_n].cell[n].M[0][AP_nu+2]=-0.630701;      
      }/**/
    }
    else{//if(def==0)
	//2005/11/9 tomisaki
	if(n>=0){
	  //初めはこの設定
	  for(i=0;i<AP_NN;i++){
	    net[a_n].cell[n].M[0][i]=0;
	    net[a_n].cell[n].v=0;
	    for(j=0;j<AP_NN;j++){
	      if(i==j) net[a_n].cell[n].Q[i][j]=1e0;
	      else  net[a_n].cell[n].Q[i][j]=0;
	    }
	  }
//first
//M=+7.411e-05 +1.975e-03 -1.371e-03 -2.961e-03 -2.304e-02 +2.341e-03 -6.576e-03 nVi=  1499.0 S=  0.3185
//	  net[a_n].cell[n].M[0][0]=0;
//	  net[a_n].cell[n].M[0][1]=1;
//	  net[a_n].cell[n].M[0][AP_nu+1]=0.9;  
	  //M[0]=0.002407 -0.000011 0.000054 0.000054 1.333936 -0.879598 0.555816 
	  if(1==0){//2011.09.09 avoid error when AP_NN is small
	    net[a_n].cell[n].M[0][0]=0.002407;
	    net[a_n].cell[n].M[0][1]=-0.000011;
	    net[a_n].cell[n].M[0][2]=0.000054;
	    net[a_n].cell[n].M[0][3]=0.000054 ;
	    net[a_n].cell[n].M[0][4]=1.333936 ;
	    net[a_n].cell[n].M[0][5]=-0.879598;
	    net[a_n].cell[n].M[0][6]=0.555816 ;
	    //M[0]=-0.006576 0.000074 0.001975 -0.001371 -0.002961 -0.023035 0.002341 Done emulate!(Push return-key)
	    net[a_n].cell[n].M[0][0]=-0.006576;
	    net[a_n].cell[n].M[0][1]=0.000074;
	    net[a_n].cell[n].M[0][2]=0.001975;
	    net[a_n].cell[n].M[0][3]=-0.001371;
	    net[a_n].cell[n].M[0][4]=-0.002961;
	    net[a_n].cell[n].M[0][5]=-0.023035;
	    net[a_n].cell[n].M[0][6]= 0.002341;
	  }
	}
    }
  }
  else{
    for(i=0;i<AP_NN;i++){
      net[a_n].cell[n].M[0][i]=0.;
      net[a_n].cell[n].v=0.;
      for(j=0;j<AP_NN;j++){
	if(i==j) net[a_n].cell[n].Q[i][j]=1e0;
	else  net[a_n].cell[n].Q[i][j]=0.;
      }
    }
  }
}/*end of init_MQ_APi*/
/*********************************************************/
void init_MQ_AP()                 /* 行列の初期化    */
/*********************************************************/
{
  int i,j;

  if(ensemble==0){
      for(i=0;i<AP_NC[0];i++){
	init_MQ_APi(i,0,0);
      }
  }
  else{//2005/11/10 tomisaki
    init_MQ_APi(0,0,0);//net[a_n]にMの平均を格納する。
    for(j=1;j<=net_num;j++){//アンサンブル学習に必要なネットの用意
      for(i=0;i<AP_NC[0];i++){
	init_MQ_APi(i,0,j);
      }
    }
  }
}
//FLOAT err[100];//配列の中身はAP_NC
FLOAT *err;//配列の中身はAP_NC
FLOAT init_err=0;
int _obtain_AP_i(FLOAT *x,FLOAT y,NET *net)/*AP_iを１ステップだけで計算 cを求める計算*/
//int obtain_AP_i(FLOAT *x,FLOAT y,NET *net, int a_n, int u_n)/*AP_iを１ステップだけで計算 cを求める計算*/
/***********************************************************************/
{//modify tomisaki 2005/11/9
  int i,j,k,AP_out=0,flag_ob=0;
  FLOAT AP_err=INFTY;//  FLOAT dy,dy2,AP_err;
  if(it==0) AP_out=0;
  else if(obtain_new==0){//
    for(i=0;i<AP_NC[0];i++){
      if(it==0 || net[0].cell[i].w[0]!=0. || net[0].cell[i].w[1]!=0. || net[0].cell[i].w[2]!=0.){
	double dy2=0;
	for(k=0;k<AP_IS;k++){
	  double dy = -AP_yy[k]+net[0].cell[i].M[0][0]*AP_z[0];
	  for(j=1;j<=AP_nu;j++) dy += net[0].cell[i].M[0][j]*AP_uu[k+j];
	  for(j=1;j<=AP_ny;j++) dy += net[0].cell[i].M[0][j+AP_nu]*AP_yy[k+j];
	  dy2+=fabs(dy);
	}
	dy2/=AP_IS;
	err[i]=dy2;
	if(dy2<AP_err){//	  if(i==0||dy2<AP_err){
	  AP_err=dy2;
	  AP_out=i;
	}
      }
    }/**/
  }
  else{/*2007/02/18/koshi*///obtain_new!=0 select by w
    for(i=0;i<AP_NC[0];i++){//AP_NC:number of units
      //      int usew=0;//
      //      int usew=(it==0)?1:0;
      //     int usew=0;for(j=0;j<CAN2_k;j++){if(fabs(net[0].cell[i].w[j])>AP_ZERO){usew=1;break;}}
      int usew=(net[0].cell[i].v>AP_ZERO)?1:0;
      //      int CAN2_k=AP_nu+AP_ny;
      //if(it==0||net[0].cell[i].w[0]!=0.||net[0].cell[i].w[1]!=0.||net[0].cell[i].w[2]!=0.||net[0].cell[i].w[3]!=0.||net[0].cell[i].w[4]!=0. || net[0].cell[i].w[5]!=0.){
      if(usew){
//    if(it>=1){//check memory allocation
//      double *dum=(double*)malloc(sizeof(double)*10000);
//      fprintf(stderr,"#memory-check2 dum=%p AP_du[1]=%g i=%d\n",dum,AP_du[1],i);
//      free(dum);
//    }

	double dy=0;
	for(j=0;j<(CAN2_k);j++){//	for(j=0;j<(AP_nu+AP_ny);j++){
	  if(j<AP_nu) dy+=mypow2((AP_z[j+1]-AP_z[j+2])-net[0].cell[i].w[j]);
	  else dy+=mypow2((AP_z[j+2]-AP_z[j+3])-net[0].cell[i].w[j]);
	  //	  if(j<AP_nu) dy+=pow((AP_z[j+1]-AP_z[j+2])-net[0].cell[i].w[j] , 2);
	  //	  else dy+=pow((AP_z[j+2]-AP_z[j+3])-net[0].cell[i].w[j] , 2);
	  //if(j<AP_nu) dy+=pow((AP_z[j+1]-AP_z[j+2])-net[0].cell[i].w[j] , 2);
	  //if(j>=AP_nu) dy+=pow((AP_z[j+2]-AP_z[j+3])-net[0].cell[i].w[j] , 2);
	}
//    if(it>=1){//check memory allocation
//      double *dum=(double*)malloc(sizeof(double)*10000);
//      fprintf(stderr,"#memory-check2-2 dum=%p AP_du[1]=%g i=%d\n",dum,AP_du[1],i);
//      free(dum);
//    }
    //	err[i]=dy;
	if(i==0 || dy<AP_err){
	  AP_err=dy;
	  AP_out=i;
	}
      }
    }
    //    if(it==0) fprintf(stderr,"check AP_out=%d at it==0\n",AP_out);
  }
  return(AP_out);
}
int obtain_AP_i(FLOAT *x,FLOAT y,NET *net, int a_n, int u_n)/*AP_iを１ステップだけで計算 cを求める計算*/
/***********************************************************************/
{//modify tomisaki 2005/11/9
  int i,j,k,AP_out=0,flag_ob=0;
  FLOAT AP_err=INFTY;//  FLOAT dy,dy2,AP_err;
  if(it==0) AP_out=0;
  else if(obtain_new==0){//
    for(i=0;i<u_n;i++){
      if(it==0 || net[a_n].cell[i].w[0]!=0. || net[a_n].cell[i].w[1]!=0. || net[a_n].cell[i].w[2]!=0.){
	double dy2=0;
	for(k=0;k<AP_IS;k++){
	  double dy = -AP_yy[k]+net[a_n].cell[i].M[0][0]*AP_z[0];
	  for(j=1;j<=AP_nu;j++) dy += net[a_n].cell[i].M[0][j]*AP_uu[k+j];
	  for(j=1;j<=AP_ny;j++) dy += net[a_n].cell[i].M[0][j+AP_nu]*AP_yy[k+j];
	  dy2+=fabs(dy);
	}
	dy2/=AP_IS;
	err[i]=dy2;
	if(dy2<AP_err){//	  if(i==0||dy2<AP_err){
	  AP_err=dy2;
	  AP_out=i;
	}
      }
    }/**/
  }
  else{/*2007/02/18/koshi*///obtain_new!=0 select by w
    for(i=0;i<u_n;i++){//u_n:number of units
      //      int usew=0;//
      //      int usew=(it==0)?1:0;
      //     int usew=0;for(j=0;j<CAN2_k;j++){if(fabs(net[a_n].cell[i].w[j])>AP_ZERO){usew=1;break;}}
      int usew=(net[a_n].cell[i].v>AP_ZERO)?1:0;
      //      int CAN2_k=AP_nu+AP_ny;
      //if(it==0||net[a_n].cell[i].w[0]!=0.||net[a_n].cell[i].w[1]!=0.||net[a_n].cell[i].w[2]!=0.||net[a_n].cell[i].w[3]!=0.||net[a_n].cell[i].w[4]!=0. || net[a_n].cell[i].w[5]!=0.){
      if(usew){
	double dy=0;
	for(j=0;j<(CAN2_k);j++){//	for(j=0;j<(AP_nu+AP_ny);j++){
	  if(j<AP_nu) dy+=mypow2((AP_z[j+1]-AP_z[j+2])-net[a_n].cell[i].w[j]);
	  else dy+=mypow2((AP_z[j+2]-AP_z[j+3])-net[a_n].cell[i].w[j]);
	  //	  if(j<AP_nu) dy+=pow((AP_z[j+1]-AP_z[j+2])-net[a_n].cell[i].w[j] , 2);
	  //	  else dy+=pow((AP_z[j+2]-AP_z[j+3])-net[a_n].cell[i].w[j] , 2);
	  //if(j<AP_nu) dy+=pow((AP_z[j+1]-AP_z[j+2])-net[a_n].cell[i].w[j] , 2);
	  //if(j>=AP_nu) dy+=pow((AP_z[j+2]-AP_z[j+3])-net[a_n].cell[i].w[j] , 2);
	}
	err[i]=dy;
	if(i==0 || dy<AP_err){
	  AP_err=dy;
	  AP_out=i;
	}
      }
    }
    //    if(it==0) fprintf(stderr,"check AP_out=%d at it==0\n",AP_out);
  }
  return(AP_out);
}
#define AP_hoji 1.0
///*======================================================*/
//void AM_AP(FLOAT x[],FLOAT y,int APi,NET *net) /*  最小２乗法  */
///*======================================================*/
///*	入力ベクトル x[4]                               */
///*	出力値       y                                  */
///*======================================================*/
//{
//  int i,j,k;
//  FLOAT hth=0,gtx1;
//  FLOAT h[AP_NN],g[AP_NN],p[AP_NN];
//  FLOAT yhat;
//
//  for(i=0;i<AP_NN;i++) 
//    for(g[i]=0,j=0;j<AP_NN;j++) g[i] += net[0].cell[APi].Q[i][j]*x[j];
//  for(gtx1=AP_hoji,i=0;i<AP_NN;i++) gtx1 += g[i]*x[i];
//  for(i=0;i<AP_NN;i++) p[i] = g[i]/gtx1;/**/
//  for(i=0;i<AP_NN;i++){
//    for(j=0;j<AP_NN;j++){
//      net[0].cell[APi].Q[i][j] = (net[0].cell[APi].Q[i][j] - g[i]*p[j])/AP_hoji;
//    }
//  }
//  for(yhat=0,i=0;i<AP_NN;i++) yhat += net[0].cell[APi].M[0][i]*x[i];
//  for(i=0;i<AP_NN;i++) net[0].cell[APi].M[0][i] += (y-yhat)*p[i];/**/
//}
int s00=0,s01;
FLOAT ste_allerr=0;
FLOAT tra_allerr=0;
FLOAT mid_allerr=0;
FLOAT allerr=0;
int n_of_saishokika=0;
/*********************************************************/
void store_vector_AP(FLOAT *AP_z,FLOAT AP_y)  /*traindate testdataを作成*/
//void store_vector_AP(FLOAT *AP_z,FLOAT AP_y,NET *net)  /*traindate testdataを作成*/
/*********************************************************/
{
  int k,nn;
  int i,j,iii,vsum,vave,nmax=0,modified=-1;
  FLOAT yi; 
  FLOAT temp;
  FLOAT errmin=0;
  //  int *s,ss[100];//配列の中身はAP_NCだった
  FLOAT *z;

  /*2007/02/18/koshi*/
//  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%.9e ",AP_z[i]-AP_z[i+1]); 
//  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%.9e ",AP_z[i]-AP_z[i+1]);
//  fprintf(fptrain,"%.9e %f\n",AP_y-AP_z[AP_nu+2],time);
//  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?testdata
//    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%.9e ",AP_z[i]-AP_z[i+1]);
//    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%.9e ",AP_z[i]-AP_z[i+1]);
//    fprintf(fptest,"%.9e %g\n",AP_y-AP_z[AP_nu+2],time);
//  }
//
//  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%.10e ",AP_z[i]-AP_z[i+1]); 
//  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%.10e ",AP_z[i]-AP_z[i+1]);
//  fprintf(fptrain,"%.10e %f\n",AP_y-AP_z[AP_nu+2],time);
//  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?testdata
//    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%.10e ",AP_z[i]-AP_z[i+1]);
//    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%.10e ",AP_z[i]-AP_z[i+1]);
//    fprintf(fptest,"%.10e %g\n",AP_y-AP_z[AP_nu+2],time);
//  }
//
//  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%.20e ",AP_z[i]-AP_z[i+1]); 
//  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%.20e ",AP_z[i]-AP_z[i+1]);
//  fprintf(fptrain,"%.20e %f\n",AP_y-AP_z[AP_nu+2],time);
//  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?testdata
//    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%.20e ",AP_z[i]-AP_z[i+1]);
//    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%.20e ",AP_z[i]-AP_z[i+1]);
//    fprintf(fptest,"%.20e %g\n",AP_y-AP_z[AP_nu+2],time);
//  }

  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%.8e ",AP_z[i]-AP_z[i+1]); 
  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%.8e ",AP_z[i]-AP_z[i+1]);
  fprintf(fptrain,"%.8e %g\n",AP_y-AP_z[AP_nu+2],time);
  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?testdata
    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%.8e ",AP_z[i]-AP_z[i+1]);
    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%.8e ",AP_z[i]-AP_z[i+1]);
    fprintf(fptest,"%.8e %g\n",AP_y-AP_z[AP_nu+2],time);
  }

//  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%.7e ",AP_z[i]-AP_z[i+1]); 
//  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%.7e ",AP_z[i]-AP_z[i+1]);
//  fprintf(fptrain,"%.7e %f\n",AP_y-AP_z[AP_nu+2],time);
//  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?testdata
//    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%.7e ",AP_z[i]-AP_z[i+1]);
//    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%.7e ",AP_z[i]-AP_z[i+1]);
//    fprintf(fptest,"%.7e %g\n",AP_y-AP_z[AP_nu+2],time);
//  }

//  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%.6e ",AP_z[i]-AP_z[i+1]); 
//  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%.6e ",AP_z[i]-AP_z[i+1]);
//  fprintf(fptrain,"%.6e %f\n",AP_y-AP_z[AP_nu+2],time);
//  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?testdata
//    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%.6e ",AP_z[i]-AP_z[i+1]);
//    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%.6e ",AP_z[i]-AP_z[i+1]);
//    fprintf(fptest,"%.6e %g\n",AP_y-AP_z[AP_nu+2],time);
//  }
//
//  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%g ",AP_z[i]-AP_z[i+1]); 
//  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%g ",AP_z[i]-AP_z[i+1]);
//  fprintf(fptrain,"%g %f\n",AP_y-AP_z[AP_nu+2],time);
//  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?testdata
//    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%g ",AP_z[i]-AP_z[i+1]);
//    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%g ",AP_z[i]-AP_z[i+1]);
//    fprintf(fptest,"%g %g\n",AP_y-AP_z[AP_nu+2],time);
//  }
//
  return;
}	
#endif
//#ifndef MSPC
//#define AP_hoji 1.0
///*======================================================*/
//void AM_AP(x,y)                         /*  最小２乗法  */
///*======================================================*/
///*	入力ベクトル x[AP_NN]                               */
///*	出力値       y                                  */
///*======================================================*/
//FLOAT x[],y;
//{
//  int i,j,k;
//  FLOAT hth=0,gtx1;
//  FLOAT h[AP_NN],g[AP_NN],p[AP_NN];
//  FLOAT yhat;
//
//  for(i=0;i<AP_NN;i++) for(g[i]=0,j=0;j<AP_NN;j++) g[i] += AP_Q[i][j]*x[j];
//  for(gtx1=AP_hoji,i=0;i<AP_NN;i++) gtx1 += g[i]*x[i];
//  for(i=0;i<AP_NN;i++) p[i] = g[i]/gtx1;/**/
//  for(i=0;i<AP_NN;i++){
//    for(j=0;j<AP_NN;j++){
//      AP_Q[i][j] = (AP_Q[i][j] - g[i]*p[j])/AP_hoji;
//    }
//  }
//  for(yhat=0,i=0;i<AP_NN;i++) yhat += AP_M[0][i]*x[i];
//  yhat=AP_M[0][0]*x[0]+AP_M[0][1]*x[1]+AP_M[0][2]*x[2]+AP_M[0][3]*x[3];
//  for(i=0;i<AP_NN;i++) AP_M[0][i] += (y-yhat)*p[i];/**/
//}
//#endif
//#ifdef APC
//#define eval_AP(x) fabs(x)          /**/
///*======================================================*/
//FLOAT predict_AP(FLOAT u)  /*予測値計算・評価*/
///*======================================================*/
//{
//  int i,j;
//  FLOAT J,yk,yk_minus_1,yk_plus_1;
//  J=0;
//  yk=AP_y;/**/
//#ifdef AP_NN4
//  yk_minus_1=AP_z[2];/**/
//#endif
//  for(j=1;j<=AP_Np;j++){
//#ifdef AP_NN4
//    yk_plus_1=AP_M[0][0]*AP_z[0]+AP_M[0][1]*u+AP_M[0][2]*yk+AP_M[0][3]*yk_minus_1;
//#endif
//#ifdef AP_NN3
//    yk_plus_1=AP_M[0][0]*AP_z[0]+AP_M[0][1]*u+AP_M[0][2]*yk;
//#endif
//#ifdef MSPC
//    J += eval_AP(AP_r-yk_plus_1);/**/
//#else
//    J += eval_AP(AP_r-AP_y_smooth-AP_y_under-AP_y_under2-yk_plus_1);/**/
//#endif
//    yk_minus_1=yk;
//    yk=yk_plus_1;
//  }
//  return(J);
//}
///*======================================================*/
//FLOAT predict_search_AP(void)       /* 予測入力探索    */
///*======================================================*/
//{
//  int i;
//  FLOAT uuu,Pmin,Puuu,umin;
//
//  for(i=0;i<=AP_u_res;i++){
//    uuu=i*AP_u_max/AP_u_res;
//    if(uuu>=AP_u_max) uuu=AP_u_max;
//    Puuu=predict_AP(uuu);
//    if(i==0 || Puuu-Pmin<-AP_ZERO){
//      umin=uuu;
//      Pmin=Puuu;
//    }
//  }
//  return(umin);
//}
//#endif

/***********************MSPC******************************/
#ifdef MSPC
//FLOAT *g_buf,*p_buf,*P_buf,*r_buf,*z_buf,*Pr_buf,*rP_buf;
#ifdef EMULATE
FLOAT APC_BUF[27];
#else
FLOAT APC_BUF[27];
#endif
#define p(j) p_buf[(j)]
#define g(j) g_buf[(j)]
#define r(j) r_buf[(j)]
#define P(i,j) P_buf[(i)*AP_NU+(j)]
#define Pr(j) Pr_buf[(j)]
#define rP(j) rP_buf[(j)]
#define z(j) z_buf[(j)]
//2005/12/5 tomidaki
//double lambda=((double)AP_N2)*(AP_LAMBDA)/AP_NU;//AP_N2:L34,AP_LAMBDA:L53,AP_NU:L55,
//#define lambda (AP_N2*AP_LAMBDA)
//#define lambda (AP_N2*AP_LAMBDA/AP_NU)
//#define lambda (AP_N2*(AP_LAMBDA)/AP_NU)
//#define lambda ((double)(AP_N2)*(AP_LAMBDA)/AP_NU)
//#define lambda (AP_N2*(AP_LAMBDA)*1.0e-5/AP_NU)/**/
#endif

#ifdef MSPC
/*********************************************************/
#include "calcAinvb.c"
/*********************************************************/
FLOAT predict_search_AP(int m)
/*********************************************************/
{
  int i,j,k,l;
  FLOAT umin;
  FLOAT *a,*b,c;
  FLOAT rPr_plus_1;
  /*2007/02/16/koshi*/
  b=(FLOAT *)&(net[0].cell[m].M[0][1]);/*b[0..k_u-1]*/
  a=(FLOAT *)&(net[0].cell[m].M[0][AP_nu+1]);/*a[0..k_y-1]*/
  c=net[0].cell[m].M[0][0];//net[0].cell[m].M[0][0]*AP_z[0];//AP_z[0]=1;
//  if(it==1){//check
//    int k;
//    fprintf(stdout,"??time%g,b=",time);
//    for(k=1; k<=AP_nu; k++) printf("%g ",b[k]);
//    fprintf(stdout,"a");
//    for(k=0; k<AP_ny; k++) printf("%g ",a[k]);
//    fprintf(stdout,"c %g\n",c);
//  }

  //c=0; for the CAN2 with BIAS:0
  double g_buf[AP_N2];
  double p_buf[AP_N2];
  double P_buf[AP_NU*AP_NU];
  double r_buf[AP_NU];
  double z_buf[AP_NU];
  double Pr_buf[AP_NU];
  double rP_buf[AP_NU];
  double lambda=((double)AP_N2)*(AP_LAMBDA)/AP_NU;//AP_N2:L34,AP_LAMBDA:L53,AP_NU:L55,
  if(penalty == 0 || penalty ==1){
    //tomisaki
    double G[N_matrix][N_matrix];//N_matrix=8;??
    double G_T[N_matrix][N_matrix];
    double R_w[N_matrix][N_matrix];
    double Q_w[N_matrix][N_matrix];
    double rr0[N_matrix][N_matrix];
    double rr0_T[N_matrix][N_matrix];
    double c_T[N_matrix][N_matrix];
    double Q_m[N_matrix][N_matrix];
    double e_m[N_matrix][N_matrix];
    double e_m1[N_matrix][N_matrix];
    double e_m2[N_matrix][N_matrix];
    double inv_G[N_matrix][N_matrix];
    double delta_u[N_matrix][N_matrix];
    double delta_u_l[N_matrix][N_matrix];
    double lamda[N_matrix][N_matrix];
    double lamda1[N_matrix][N_matrix];
    double lamda2[N_matrix][N_matrix];
    double lamda_l[N_matrix][N_matrix];
    double lamda_T[N_matrix][N_matrix];
    double F_L[2];
    double triangle[N_matrix][N_matrix];
    int m_2, n_2, nz_2, qn_2, qnz_2, acolcnt[maxn+1], acolidx[maxnz], qcolcnt[maxn+1], qcolidx[maxqnz],
      status[maxn+maxm],  memsiz;
    double acolnzs[maxnz], qcolnzs[maxqnz], rhs[maxm], obj[maxn], lbound[maxn+maxm],
      ubound[maxn+maxm], primal[maxn+maxm], dual[maxn+maxm], big, opt;
    //090622 yuno
    int cons_qp=0; //080519koshi 場合分けのための定数
    //  c=AP_y;
    //  for(j=0;j<AP_nu;j++) c-=b[j]*AP_uu[j+1];
    //  for(j=0;j<AP_ny;j++) c-=a[j]*AP_yy[j+1];
    //penalty = 3; on 20100118

    if(penalty == 0){
      //~~~~~~~*** 2次計画法(bpmpd.a)を用いて制約付き最適化問題を解~~~~~~~~
      //printf("２次計画法\n");
      //N_matrix:予測ステップ数
      //単位ステップ応答 g(j)
      for(j=0;j<N_matrix;j++){
	if(j<AP_nu) g(j)=b[j];
	else g(j)=0;
	for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
      }
      //過去の入力に対する応答 y_0(j)
      for(j=0;j<N_matrix;j++){
	p(j)=c;
	for(i=0;i<AP_nu;i++){
	  if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
	  else p(j)+=b[i]*AP_uu[1];
	}
	for(i=0;i<AP_ny;i++){
	  if(j<=i) p(j)+=a[i]*AP_yy[(i-j)];
	  else p(j)+=a[i]*p(j-i-1);
	}
      }
      //行列の準備
      for(i=0;i<N_matrix;i++){
	for(j=0;j<N_matrix;j++){
	  if(i==j){
	    Q_w[i][j]=Q_weight;
	    R_w[i][j]=R_weight;
	    G[i][j]=g(i-j);
	  }
	  else if(j<i){
	    G[i][j]=g(i-j);
	    Q_w[i][j]=0.;
	    R_w[i][j]=0.;
	  }
	  else{
	    Q_w[i][j]=0.;
	    R_w[i][j]=0.;
	    G[i][j]=0.;
	  }
	}
	rr0_T[0][i]=AP_r-p(i);
      }
      
      tenti(G,N_matrix,N_matrix,G_T);
      
      multiply(Q_w,N_matrix,N_matrix,G,N_matrix,e_m);
      for(i=0;i<N_matrix;i++){
	for(j=0;j<N_matrix;j++){
	  e_m1[i][j]=-2.*e_m[i][j];
	}
      }
      multiply(rr0_T,1,N_matrix,e_m1,N_matrix,c_T); 
      multiply(Q_w,N_matrix,N_matrix,G_T,N_matrix,e_m);
      multiply(e_m,N_matrix,N_matrix,G,N_matrix,e_m1);
      for(i=0;i<N_matrix;i++){
	for(j=0;j<N_matrix;j++){
	  Q_m[i][j]=e_m1[i][j]+R_w[i][j];
	}
      }
      
      //2次計画問題を解く
      big    = 1.0e+30;        /* Define inf */
      memsiz = 0;              /* Let the DLL allocate the memory */    
      /*
	m_2:制約式の数
	n_2:変数xの次元
	nz_2:制約式(変数を含む)の係数の数
	qn_2:２次計画法のＱの次元
	qnz_2:２次計画法のＱの係数の数
      */
      m_2=2*N_matrix ; n_2=N_matrix ;
      nz_2=2*N_matrix*N_matrix ;  
      qn_2=N_matrix ;  qnz_2=N_matrix*N_matrix;    
      /*
	ubound(m_2+n_2):制約式(変数を含む)の上限   ex.x[0]<ubound[0]
	lbound(m_2+n_2):制約式(変数を含む)の下限
	rhs(m_2):右側の値                      ex. 0<g[0]<100  -> 100
      */
      for(i=0;i<3*N_matrix;i++){
	if(i<N_matrix){//duの範囲
	  ubound[i]=big;
	  lbound[i]=-big;
	}
	else if(i<2*N_matrix){//uの範囲 -AP_u_max<u<AP_u_max
	  ubound[i]=AP_u_max;
	  lbound[i]=AP_u_min;
	  //	lbound[i]=0;
	  rhs[i-N_matrix]=-AP_z[1];
	}
	else{//yの範囲 r-2<y<r+2-y_0
	  ubound[i]=0;//??
	  lbound[i]=-big;
	  rhs[i-N_matrix]=AP_r+over_r-p(i-2*N_matrix);
	}
      }    
      /*
	obj(n_2):目的関数のc_T
      */    
      for(i=0;i<N_matrix;i++){//c_T
	obj[i]=c_T[0][i];
      }    
      /*
	acolcnt(n_2):制約式の行列のその列にある係数の個数　単位行列(eye(n,n))なら : 1
	acolidx(nz_2):その係数のある位置　　　　　　　　　　単位行列なら : acolidx[i]=i
	acolnzs(nz_2):その係数                              :1
      */
      
      //制約条件の行列の設定
      //係数の個数
      for(i=0;i<N_matrix;i++){
	acolcnt[i]=2*N_matrix;
      }
      //係数の位置とその係数
      for(i=0;i<N_matrix;i++){
	for(j=0;j<N_matrix;j++){
	  //係数の位置
	  //u 0~N-1
	  acolidx[i*2*N_matrix+j]=j+1;
	  //y N~2N-1
	  acolidx[i*2*N_matrix+N_matrix+j]=j+1+N_matrix;
	  //その係数
	  //u
	  if(i>j) acolnzs[i*2*N_matrix+j]=0.;
	  else acolnzs[i*2*N_matrix+j]=1.;
	  //y
	  acolnzs[i*2*N_matrix+N_matrix+j]=G[j][i]; 
	}
      }
      /*
	qcolcnt(qn_2):Qの行列のその列にある係数の個数
	qcolidx(qnz_2)その係数のある位置　
	qcolnzs(qnz_2)その係数 
      */
      
      //Ｑの行列の設定
      //係数の個数
      for(i=0;i<N_matrix;i++){
	qcolcnt[i]=N_matrix;
      }
      //係数の位置とその係数
      for(i=0;i<N_matrix;i++){
	for(j=0;j<N_matrix;j++){
	  qcolidx[i*N_matrix+j]=j+1;
	  qcolnzs[i*N_matrix+j]=2*Q_m[j][i];
	}
      }
      
      //090624 yuno  
#ifdef BPMPD
      bpmpd(&m_2, &n_2, &nz_2, &qn_2, &qnz_2, acolcnt, acolidx, acolnzs, qcolcnt, qcolidx, qcolnzs,
	    rhs, obj, lbound, ubound, primal, dual, status, &big, &code, &opt, &memsiz);
      //printf("primal:%f code:%d dual %f\n",primal[0],code,dual[0]);
      //if(code == 3 )umin=AP_z[1]+dual[0];
      //else umin=AP_z[1]+primal[0];
      umin = AP_z[1]+primal[0];
#endif //#ifdef BPMPD
      umin = AP_z[1];
      //printf("mcode %d %f %f %f %f %f\n",code,primal[0],primal[1],primal[2],primal[3],primal[4]);
      if(code != 2) umin = 0.;
    }//endof if(penalty == 0){   
    else if(penalty == 1){   
      /*    
	    ~~~~~~~~~~~~逆行列による入力の決定~~~~~~~~~~~~~~~
	    N_matrix:予測ステップ数
	    単位ステップ応答 g(j)
      */
      for(j=0;j<N_matrix;j++){
	if(j<AP_nu) g(j)=b[j];
	else g(j)=0;
	for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
      }
      //過去の入力に対する応答 y_0(j)
      for(j=0;j<N_matrix;j++){
	p(j)=c;
	for(i=0;i<AP_nu;i++){
	  if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
	  else p(j)+=b[i]*AP_uu[1];
	}
	for(i=0;i<AP_ny;i++){
	  if(j<=i) p(j)+=a[i]*AP_yy[(i-j)];
	  else p(j)+=a[i]*p(j-i-1);
	}
      }
      //行列の準備
      for(i=0;i<N_matrix;i++){
	for(j=0;j<N_matrix;j++){
	  if(i==j){
	    Q_w[i][j]=Q_weight;
	    R_w[i][j]=R_weight;
	    G[i][j]=g(i-j);
	  }
	  else if(j<i){
	    G[i][j]=g(i-j);
	    Q_w[i][j]=0.;
	    R_w[i][j]=0.;
	  }
	  else{
	    Q_w[i][j]=0.;
	    R_w[i][j]=0.;
	    G[i][j]=0.;
	  }      
	  rr0_T[0][j]=AP_r-p(j);
	  rr0[j][0]=AP_r-p(j);
	}
      } 
      tenti(G,N_matrix,N_matrix,G_T);
      //(QG_TG+R)^-1
      multiply(G_T,N_matrix,N_matrix,G,N_matrix,e_m);
      multiply(Q_w,N_matrix,N_matrix,e_m,N_matrix,e_m1);
      for(i=0;i<N_matrix;i++){
	for(j=0;j<N_matrix;j++){
	  e_m[i][j]=e_m1[i][j]+R_w[i][j];
	}
      }
      
      inv_matrix(e_m,inv_G);
      multiply(inv_G,N_matrix,N_matrix,Q_w,N_matrix,e_m);
      multiply(e_m,N_matrix,N_matrix,G_T,N_matrix,e_m1);
      multiply(e_m1,N_matrix,N_matrix,rr0,1,delta_u);
      umin = AP_z[1] + delta_u[0][0];
    }
  }
  else if(penalty==2){
    /*step 1: ステップ応答を求める*/
#define GPC_KURO
#ifdef GPC_KURO /*GPCの原著ではuに対するステップ応答(Δuはインパルス）*/
    for(j=0;j<AP_N2;j++){
      g(j)=0;
      for(i=0;i<AP_nu;i++) if(i<=j) g(j)+=b[i];//step response
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#else /*インパルス応答*/
    for(j=0;j<AP_N2;j++){
      if(j<AP_nu) g(j)=b[j];
      else g(j)=0;
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#endif
    /*step 2*//*pの計算; natural response?*/
    /**/
    for(j=0;j<AP_N2;j++){
      p(j)=c;
      for(i=0;i<AP_nu;i++){
	if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
	else p(j)+=b[i]*AP_uu[1];//step response?
      }
      for(i=0;i<AP_ny;i++){
	if(j<=i) p(j)+=a[i]*AP_yy[(i-j)];
	else p(j)+=a[i]*p(j-i-1);
      }
    }
    for(i=0;i<AP_NU;i++){
      z(i)=0;
      for(j=0;j<AP_NU;j++){
	if(i==j) P(i,j)=1./lambda;/**/
	else P(i,j)=0;
      }
    }   
    for(j=0;j<AP_N2;j++){
      for(k=0;k<AP_NU;k++){
	if(k<=j) r(k)=g(j-k);
	else r(k)=0;
      }
      for(k=0;k<AP_NU;k++){
	Pr(k)=0;
	rP(k)=0;
	for(l=0;l<AP_NU;l++){
	  Pr(k) += P(k,l)*r(l);
	  rP(k) += r(l)*P(l,k);
	}
      }
      for(rPr_plus_1=1,k=0;k<AP_NU;k++) rPr_plus_1+=rP(k)*r(k);
      for(i=0;i<AP_NU;i++){/**/
#ifdef MSPC
	z(i) += r(i)*(AP_r-p(j));/**/
#else
	z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-AP_y_under2-p(j));/**/
#endif
	for(k=0;k<AP_NU;k++){
	  P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
	}
      }
    }//for(j=0;j<AP_N2;j++)    
    for(umin=AP_z[1],j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
  }//endof  else if(penalty==2)
  else{/*2006/12/26/koshi*/ //penalty==3
    // see. D.W.Clarke and C.Mohtadi, "Properties of Generalized Predictive Control", 
    //      Automatica, Vo.25, No.6, pp.859-875
    // for step1,2,3,4,5
    /*step 1: ステップ応答を求める*/
    ///////////////////////////
    int check=0;
//    if(time>=30){
//      fprintf(stdout,"check20170130");
//    }
    if(check){//check100123
      for(i=0;i<AP_ny;i++) a[i]=0;
      for(i=0;i<AP_nu;i++) b[i]=0;
      a[0]=0.9;
      b[0]=1;
      for(i=0;i<=AP_ny+2;i++) AP_yy[i]=0;
      for(i=0;i<=AP_nu+2;i++) AP_uu[i]=0;
      AP_yy[0]=0;
      AP_r=10;
      AP_LAMBDA=1;
    }
#define GPC_STEP 1
#define GPC_IMPULSE 2
#define GPC_g GPC_IMPULSE //一次差分ではインパルス応答
#if GPC_g == GPC_STEP/*GPCの原著ではu=1に対するステップ応答（Δuはインパルス）*/
    for(j=0;j<AP_N2;j++){//j=0はt+j+1のステップ応答?
      g(j)=0;
      for(i=0;i<AP_nu;i++) if(i<=j) g(j)+=b[i];//g(j=-1)=0;
      for(i=0;i<AP_ny;i++) if(i<j)  g(j)+=a[i]*g(j-i-1);
    }
#elif GPC_g == GPC_IMPULSE /*インパルス応答 for 一次差分*/
    //                t-2, t-1,  t, t+1, t+2,...現時刻t
    //         j =...,  -3,  -2, -1,   0,   1,...
    //       u[j]=...,   0,   0,  1,   1,   1,...(ステップ入力   u[j])に対する応答
    //      du[j]=...,   0,   0,  1,   0,   0,...(インパルス入力du[j])に対する応答
    //dg[j]=dy[j]=...,   0,   0,  0,   ?,   ?,...     応答g(j)=dy[j]
    //dg[0]=dy(0)=                           b[0]*1   (1=du[-1])
    //dg[1]=dy(1)= a[0]*dy(0)               +b[1]*1
    //dg[2]=dy(2)= a[0]*dy(1)+a[1]*dy(0)    +b[2]*1
    //...
    double dg[AP_N2];
    for(j=0;j<AP_N2;j++){//j==0,1,2 <==> 現時刻+1,2,3
      if(j<AP_nu) dg[j]=b[j]; else dg[j]=0; //for du[-1]=1;
      for(i=0;i<AP_ny;i++){
	if(i<j) dg[j]+=a[i]*dg[j-i-1];
	//	fprintf(stderr,"j%d,i%d,dg%d\n",j,i,dg[j]);
      }
    }
    for(j=0;j<AP_N2;j++){//j==0,1,2 <==> 現時刻+1,2,3
      g(j)=0;
      for(i=0;i<=j;i++) g(j)+=dg[i];
    }
//    {//check100123
//      fprintf(stderr,"AP_N2=%d,AP_ny=%d,AP_nu=%d",AP_N2,AP_ny,AP_nu);
//      fprintf(stderr,"\na:");for(i=0;i<AP_ny;i++) fprintf(stderr,"%g,",a[i]);
//      fprintf(stderr,"\nb:");for(i=0;i<AP_ny;i++) fprintf(stderr,"%g,",b[i]);
//      fprintf(stderr,"\ndg:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",dg[i]);
//      fprintf(stderr,"\n g:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",g(i));
//      fprintf(stderr,"\nerrcheck\n");
//    }
#endif
    ////////////////////////////
    /*step 2: u(t+N2-1)=u(t+N2-2)=...=u(t)=u(t-1)とした応答pの計算*/
    //                  t-2 ,  t-1 ,    t ,   t+1,   t+2,...現時刻t
    //         j =...,   -3 ,   -2 ,   -1 ,    0 ,    1 ,    2,...
    //       u[j]=..., u[-3], u[-2], u[-1], u[-1], u[-1],u[-1],...無変化入力u[j]に対する応答
    //      du[j]=...,du[-3],du[-2],du[-1],    0 ,     0,    0,...固有応答
    //       y[j]=..., y[-3], y[-2], y[-1], y[ 0],     ?,    ?,...
    //dp[j]=dy[j]=...,dy[-3],dy[-2],dy[-1],dy[ 0],     ?,   ?,...応答p(j)=dy[j]
    //dp[0]=dy[0]= a[0]*dy[-1]+a[1]*dy[-2]+...+b[0]*du[-1]+b[1]*du[-2]+...=y[0]-y[-1]
    //dp[1]=dy[1]= a[0]*dy[ 0]+a[1]*dy[-1]+...+b[0]*0     +b[1]*du[-1]+...
    //dp[2]=dy[2]= a[0]*dy[ 1]+a[1]*dy[ 0]+...+b[0]*0     +b[1]*0     +...
    ////////////////////////////
    double dp[AP_N2];
    for(j=0;j<AP_N2;j++){
      dp[j]=0;
      for(i=0;i<AP_nu;i++){
	if(j<=i) {
	  dp[j]+=b[i]*(AP_uu[(i-j+1)]-AP_uu[(i-j+2)]);
//	  {//check
//	    fprintf(stderr,"i%d,dp[j%d]=%g\n",i,j,dp[j]);
//	  }
	}
      }
      for(i=0;i<AP_ny;i++){
	if(j-1<=i){
	  dp[j]+=a[i]*(AP_yy[(i-j+1)]-AP_yy[(i-j+2)]);
//	  {//check
//	    fprintf(stderr,"j%d,i%d,dp=%g,yy:%g,%g\n",j,i,dp[j],AP_yy[(i-j+1)],AP_yy[(i-j+2)]);
//	  }
	}
	else{
	  dp[j]+=a[i]*dp[j-i-1];
//	  {//check
//	    fprintf(stderr,"j%d,i%d,dp=%g,dp%g\n",j,i,dp[j],dp[j-i-1]);
//	  }
	}
      }
    }
    for(j=0;j<AP_N2;j++){//j==0,1,2 <==> 現時刻+1,2,3
      p(j)=AP_yy[0];
      for(i=0;i<=j;i++) p(j)+=dp[i];
    }
    //////
    // step 3 ??
    //////
    //////
    // step 4 
    // Compute P=[G^T G+\lambda I]^{-1}, and
    //         z=G^T(w-p)
    //////
#ifndef originalGPC
    //Matrix inverse using SVD 
    double GGI[AP_NU*AP_NU];
#define GGI(i,j) GGI[(i)*AP_NU+(j)]
#define G(i,j) ((i<j)?0:g(i-j))//N2 x NU
    for(i=0;i<AP_NU;i++){
      for(j=0;j<AP_NU;j++){
	if(i==j) {
	  GGI(i,j)=lambda;/**/
	}
	else GGI(i,j)=0;
	for(l=0;l<AP_N2;l++){
	  GGI(i,j)+=G(l,i)*G(l,j);
	}
      }
    }
    for(i=0;i<AP_NU;i++){
      z(i)=0;
      for(j=0;j<AP_N2;j++){
	z(i)+=G(j,i)*(AP_r-p(j));
      }
    }
    double um[AP_NU];
    //    calc_Ainvb(um,GGI,&(z(0)),AP_NU,AP_NU,AP_NU);
    calcAinvb1(um,GGI,&(z(0)),AP_NU,AP_NU);
    umin=AP_uu[1]+um[0];
    if(check){
      for(i=0;i<AP_NU;i++){
	double GGIu=0;
	for(j=0;j<AP_NU;j++) GGIu+=GGI(i,j)*um[j];
	fprintf(stderr,"GGIu=%g =?= z=%g\n",GGIu,z(i));
      }
      fprintf(stderr,"\nAP_y=%g,u[0]=%g,u[-1]=%g,lambda=%g\n",AP_yy[0],AP_uu[0],AP_uu[1],lambda);
      fprintf(stderr,"\ndp:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",dp[i]);
      fprintf(stderr,"\n p:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",p(i));
      fprintf(stderr,"\nGGI:");
      for(i=0;i<AP_NU;i++){
	fprintf(stderr,"\n GGI(i%d,*):",i);
	for(j=0;j<AP_NU;j++){
	  fprintf(stderr,"%+.3f ",GGI(i,j));
	}
      }
      fprintf(stderr,"\n z:");for(i=0;i<AP_NU;i++) fprintf(stderr,"%g,",z(i));
      fprintf(stderr,"\num:");
      for(i=0;i<AP_NU;i++){
	fprintf(stderr,"%g,",um[i]);
      }
      fprintf(stderr,"\nerrcheck\n");
    }
#else //#ifndef originalGPC
    //original
    for(i=0;i<AP_NU;i++){
      z(i)=0;
      for(j=0;j<AP_NU;j++){
	if(i==j) P(i,j)=1./lambda;/**/
	else P(i,j)=0;
      }
    }   
    for(j=0;j<AP_N2;j++){
      for(k=0;k<AP_NU;k++){
	if(k<=j) r(k)=g(j-k);
	else r(k)=0;
      }
      for(k=0;k<AP_NU;k++){
	Pr(k)=0;
	rP(k)=0;
	for(l=0;l<AP_NU;l++){
	  Pr(k) += P(k,l)*r(l);
	  rP(k) += r(l)*P(l,k);
	}
      }
      for(rPr_plus_1=1,k=0;k<AP_NU;k++) rPr_plus_1+=rP(k)*r(k);
      //      if(j>0) p(j) += p(j-1);
      for(i=0;i<AP_NU;i++){/**/
	z(i) += r(i)*(AP_r-p(j));/**/
	for(k=0;k<AP_NU;k++){
	  P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
	}
      }
    }//end of for(j=0;j<AP_N2;j++)   
    //////
    // step 5
    //////
    for(umin=AP_uu[1],i=0;i<AP_NU;i++) umin+=P(0,i)*z(i); //u=u[1]+P(0)[]*z[]
    //    for(umin=0,i=0;i<AP_NU;i++) umin+=P(0,i)*z(i); //u=u[1]+P(0)[]*z[]
    //////
    //    fprintf(stderr,"#penalty==3\n");exit(-1);//check
    if(check){//check100123
    //    if((time>=41.99 && fabs(a[0]-2.605159)<0.00001) || check){//check100123
      // time=35.359999999999999
      fprintf(stderr,"\na:%.6f %.6f %.6f %.6f b:%.6f %.6f %.6f %.6f",a[0],a[1],a[2],a[3],b[0],b[1],b[2],b[3]);
      fprintf(stderr,"\nAP_y=%g,u[0]=%g,u[-1]=%g,lambda=%g\n",AP_yy[0],AP_uu[0],AP_uu[1],lambda);
      fprintf(stderr,"\ndp:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",dp[i]);
      fprintf(stderr,"\n p:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",p(i));
      fprintf(stderr,"\n p:");
      for(i=0;i<AP_NU;i++){
	fprintf(stderr,"\n p(i%d,*):",i);
	for(j=0;j<AP_NU;j++){
	  fprintf(stderr,"%+.3f ",P(i,j));
	}
	//	fprintf(stderr,"\n");
      }
      fprintf(stderr,"\num:");
      for(j=0;j<AP_NU;j++){
	double um;
	for(um=AP_uu[1],i=0;i<AP_NU;i++) um+=P(j,i)*z(i);
	fprintf(stderr,"%g,",um);
      }
      fprintf(stderr,"\nerrcheck\n");
    }
#endif
  }//penalty==3

  if(u_limit==0){
    if(umin>AP_u_max) umin=AP_u_max;
    else if(umin<AP_u_min) umin=AP_u_min;
  }
  return(umin);
}//end ofpredict_search_AP(int m)
/*********************************************************/
//FLOAT predict_search_AP1(int m)
///*********************************************************/
//{
//  int i,j,k,l;
//  FLOAT umin;
//  FLOAT *a,*b,c;
//  FLOAT rPr_plus_1;
//  //tomisaki
//  double G[N_matrix][N_matrix];//N_matrix=8;??
//  double G_T[N_matrix][N_matrix];
//  double R_w[N_matrix][N_matrix];
//  double Q_w[N_matrix][N_matrix];
//  double rr0[N_matrix][N_matrix];
//  double rr0_T[N_matrix][N_matrix];
//  double c_T[N_matrix][N_matrix];
//  double Q_m[N_matrix][N_matrix];
//  double e_m[N_matrix][N_matrix];
//  double e_m1[N_matrix][N_matrix];
//  double e_m2[N_matrix][N_matrix];
//  double inv_G[N_matrix][N_matrix];
//  double delta_u[N_matrix][N_matrix];
//  double delta_u_l[N_matrix][N_matrix];
//  double lamda[N_matrix][N_matrix];
//  double lamda1[N_matrix][N_matrix];
//  double lamda2[N_matrix][N_matrix];
//  double lamda_l[N_matrix][N_matrix];
//  double lamda_T[N_matrix][N_matrix];
//  double F_L[2];
//  double triangle[N_matrix][N_matrix];
//  int    m_2, n_2, nz_2, qn_2, qnz_2, acolcnt[maxn+1], acolidx[maxnz], qcolcnt[maxn+1], qcolidx[maxqnz],
//    status[maxn+maxm],  memsiz;
//  double acolnzs[maxnz], qcolnzs[maxqnz], rhs[maxm], obj[maxn], lbound[maxn+maxm],
//    ubound[maxn+maxm], primal[maxn+maxm], dual[maxn+maxm], big, opt;
//  //090622 yuno
//  int cons_qp=0; //080519koshi 場合分けのための定数
//  double g_buf[AP_N2];
//  double p_buf[AP_N2];
//  double P_buf[AP_NU*AP_NU];
//  double r_buf[AP_NU];
//  double z_buf[AP_NU];
//  double Pr_buf[AP_NU];
//  double rP_buf[AP_NU];
//  /*2007/02/16/koshi*/
//  c=net[0].cell[m].M[0][0]*AP_z[0];
//  b=(FLOAT *)&(net[0].cell[m].M[0][1]);/*b[0..k_u-1]*/
//  a=(FLOAT *)&(net[0].cell[m].M[0][AP_nu+1]);/*a[0..k_y-1]*/
//  
//  //penalty = 3; on 20100118
//  if(penalty == 0){
//  //~~~~~~~*** 2次計画法(bpmpd.a)を用いて制約付き最適化問題を解~~~~~~~~
//  //printf("２次計画法\n");
//  //N_matrix:予測ステップ数
//  //単位ステップ応答 g(j)
//    for(j=0;j<N_matrix;j++){
//      if(j<AP_nu) g(j)=b[j];
//      else g(j)=0;
//      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
//    }
//    //過去の入力に対する応答 y_0(j)
//    for(j=0;j<N_matrix;j++){
//      p(j)=c;
//      for(i=0;i<AP_nu;i++){
//	if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
//	else p(j)+=b[i]*AP_uu[1];
//      }
//      for(i=0;i<AP_ny;i++){
//	if(j<=i) p(j)+=a[i]*AP_yy[(i-j)];
//	else p(j)+=a[i]*p(j-i-1);
//      }
//    }
//    //行列の準備
//    for(i=0;i<N_matrix;i++){
//      for(j=0;j<N_matrix;j++){
//	if(i==j){
//	  Q_w[i][j]=Q_weight;
//	  R_w[i][j]=R_weight;
//	  G[i][j]=g(i-j);
//	}
//	else if(j<i){
//	  G[i][j]=g(i-j);
//	  Q_w[i][j]=0.;
//	  R_w[i][j]=0.;
//	}
//	else{
//	  Q_w[i][j]=0.;
//	  R_w[i][j]=0.;
//	  G[i][j]=0.;
//	}
//      }
//      rr0_T[0][i]=AP_r-p(i);
//    }
//    
//    tenti(G,N_matrix,N_matrix,G_T);
//    
//    multiply(Q_w,N_matrix,N_matrix,G,N_matrix,e_m);
//    for(i=0;i<N_matrix;i++){
//      for(j=0;j<N_matrix;j++){
//	e_m1[i][j]=-2.*e_m[i][j];
//      }
//    }
//    multiply(rr0_T,1,N_matrix,e_m1,N_matrix,c_T); 
//    multiply(Q_w,N_matrix,N_matrix,G_T,N_matrix,e_m);
//    multiply(e_m,N_matrix,N_matrix,G,N_matrix,e_m1);
//    for(i=0;i<N_matrix;i++){
//      for(j=0;j<N_matrix;j++){
//	Q_m[i][j]=e_m1[i][j]+R_w[i][j];
//      }
//    }
//    
//    //2次計画問題を解く
//    big    = 1.0e+30;        /* Define inf */
//    memsiz = 0;              /* Let the DLL allocate the memory */    
//    /*
//      m_2:制約式の数
//      n_2:変数xの次元
//      nz_2:制約式(変数を含む)の係数の数
//      qn_2:２次計画法のＱの次元
//      qnz_2:２次計画法のＱの係数の数
//    */
//    m_2=2*N_matrix ; n_2=N_matrix ;
//    nz_2=2*N_matrix*N_matrix ;  
//    qn_2=N_matrix ;  qnz_2=N_matrix*N_matrix;    
//    /*
//      ubound(m_2+n_2):制約式(変数を含む)の上限   ex.x[0]<ubound[0]
//      lbound(m_2+n_2):制約式(変数を含む)の下限
//      rhs(m_2):右側の値                      ex. 0<g[0]<100  -> 100
//    */
//    for(i=0;i<3*N_matrix;i++){
//      if(i<N_matrix){//duの範囲
//	ubound[i]=big;
//	lbound[i]=-big;
//      }
//      else if(i<2*N_matrix){//uの範囲 -AP_u_max<u<AP_u_max
//	ubound[i]=AP_u_max;
//	lbound[i]=AP_u_min;
//	//	lbound[i]=0;
//	rhs[i-N_matrix]=-AP_z[1];
//      }
//      else{//yの範囲 r-2<y<r+2-y_0
//	ubound[i]=0;//??
//	lbound[i]=-big;
//	rhs[i-N_matrix]=AP_r+over_r-p(i-2*N_matrix);
//      }
//    }    
//    /*
//      obj(n_2):目的関数のc_T
//    */    
//    for(i=0;i<N_matrix;i++){//c_T
//      obj[i]=c_T[0][i];
//    }    
//    /*
//      acolcnt(n_2):制約式の行列のその列にある係数の個数　単位行列(eye(n,n))なら : 1
//      acolidx(nz_2):その係数のある位置　　　　　　　　　　単位行列なら : acolidx[i]=i
//      acolnzs(nz_2):その係数                              :1
//    */
//    
//    //制約条件の行列の設定
//    //係数の個数
//    for(i=0;i<N_matrix;i++){
//      acolcnt[i]=2*N_matrix;
//    }
//    //係数の位置とその係数
//    for(i=0;i<N_matrix;i++){
//      for(j=0;j<N_matrix;j++){
//	//係数の位置
//	//u 0~N-1
//	acolidx[i*2*N_matrix+j]=j+1;
//	//y N~2N-1
//	acolidx[i*2*N_matrix+N_matrix+j]=j+1+N_matrix;
//	//その係数
//	//u
//	if(i>j) acolnzs[i*2*N_matrix+j]=0.;
//	else acolnzs[i*2*N_matrix+j]=1.;
//	//y
//	acolnzs[i*2*N_matrix+N_matrix+j]=G[j][i]; 
//      }
//    }
//    /*
//    qcolcnt(qn_2):Qの行列のその列にある係数の個数
//    qcolidx(qnz_2)その係数のある位置　
//    qcolnzs(qnz_2)その係数 
//    */
//    
//    //Ｑの行列の設定
//    //係数の個数
//    for(i=0;i<N_matrix;i++){
//      qcolcnt[i]=N_matrix;
//    }
//    //係数の位置とその係数
//    for(i=0;i<N_matrix;i++){
//      for(j=0;j<N_matrix;j++){
//	qcolidx[i*N_matrix+j]=j+1;
//	qcolnzs[i*N_matrix+j]=2*Q_m[j][i];
//      }
//    }
//
//     //090624 yuno  
//#ifdef BPMPD
//    bpmpd(&m_2, &n_2, &nz_2, &qn_2, &qnz_2, acolcnt, acolidx, acolnzs, qcolcnt, qcolidx, qcolnzs,
//	  rhs, obj, lbound, ubound, primal, dual, status, &big, &code, &opt, &memsiz);
//#endif //#ifdef BPMPD
//    //printf("primal:%f code:%d dual %f\n",primal[0],code,dual[0]);
//    //if(code == 3 )umin=AP_z[1]+dual[0];
//    //else umin=AP_z[1]+primal[0];
//    umin = AP_z[1]+primal[0];
//    //printf("mcode %d %f %f %f %f %f\n",code,primal[0],primal[1],primal[2],primal[3],primal[4]);
//    if(code != 2) umin = 0.;
//  }
//  else if(penalty == 1){   
//    /*    
//    ~~~~~~~~~~~~逆行列による入力の決定~~~~~~~~~~~~~~~
//    N_matrix:予測ステップ数
//    単位ステップ応答 g(j)
//    */
//
//    for(j=0;j<N_matrix;j++){
//      if(j<AP_nu) g(j)=b[j];
//      else g(j)=0;
//      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
//    }
//    //過去の入力に対する応答 y_0(j)
//    for(j=0;j<N_matrix;j++){
//      p(j)=c;
//      for(i=0;i<AP_nu;i++){
//	if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
//	else p(j)+=b[i]*AP_uu[1];
//      }
//      for(i=0;i<AP_ny;i++){
//	if(j<=i) p(j)+=a[i]*AP_yy[(i-j)];
//	else p(j)+=a[i]*p(j-i-1);
//      }
//    }
//    //行列の準備
//    for(i=0;i<N_matrix;i++){
//      for(j=0;j<N_matrix;j++){
//	if(i==j){
//	  Q_w[i][j]=Q_weight;
//	  R_w[i][j]=R_weight;
//	  G[i][j]=g(i-j);
//	}
//	else if(j<i){
//	  G[i][j]=g(i-j);
//	  Q_w[i][j]=0.;
//	  R_w[i][j]=0.;
//	}
//	else{
//	  Q_w[i][j]=0.;
//	  R_w[i][j]=0.;
//	  G[i][j]=0.;
//	}      
//	rr0_T[0][j]=AP_r-p(j);
//	rr0[j][0]=AP_r-p(j);
//      }
//    } 
//    tenti(G,N_matrix,N_matrix,G_T);
//    //(QG_TG+R)^-1
//    multiply(G_T,N_matrix,N_matrix,G,N_matrix,e_m);
//    multiply(Q_w,N_matrix,N_matrix,e_m,N_matrix,e_m1);
//    for(i=0;i<N_matrix;i++){
//      for(j=0;j<N_matrix;j++){
//	e_m[i][j]=e_m1[i][j]+R_w[i][j];
//      }
//    }
//
//    inv_matrix(e_m,inv_G);
//    multiply(inv_G,N_matrix,N_matrix,Q_w,N_matrix,e_m);
//    multiply(e_m,N_matrix,N_matrix,G_T,N_matrix,e_m1);
//    multiply(e_m1,N_matrix,N_matrix,rr0,1,delta_u);
//  
//    umin = AP_z[1] + delta_u[0][0];
//
//    
//  }
//  else if(penalty==2){
//    /*step 1: ステップ応答を求める*/
//#define GPC_KURO
//#ifdef GPC_KURO /*GPCの原著ではΔuに対するステップ応答*/
//    for(j=0;j<AP_N2;j++){
//      g(j)=0;
//      for(i=0;i<AP_nu;i++) if(i<=j) g(j)+=b[i];
//      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
//    }
//#else /*インパルス応答*/
//    for(j=0;j<AP_N2;j++){
//      if(j<AP_nu) g(j)=b[j];
//      else g(j)=0;
//      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
//    }
//#endif
//    /*step 2*//*pの計算*/
//    /**/
//    for(j=0;j<AP_N2;j++){
//      p(j)=c;
//      for(i=0;i<AP_nu;i++){
//	if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
//	else p(j)+=b[i]*AP_uu[1];
//      }
//      for(i=0;i<AP_ny;i++){
//	if(j<=i) p(j)+=a[i]*AP_yy[(i-j)];
//	else p(j)+=a[i]*p(j-i-1);
//      }
//    }
//    for(i=0;i<AP_NU;i++){
//      z(i)=0;
//      for(j=0;j<AP_NU;j++){
//	if(i==j) P(i,j)=1./lambda;/**/
//	else P(i,j)=0;
//      }
//    }   
//    for(j=0;j<AP_N2;j++){
//      for(k=0;k<AP_NU;k++){
//	if(k<=j) r(k)=g(j-k);
//	else r(k)=0;
//      }
//      for(k=0;k<AP_NU;k++){
//	Pr(k)=0;
//	rP(k)=0;
//	for(l=0;l<AP_NU;l++){
//	  Pr(k) += P(k,l)*r(l);
//	  rP(k) += r(l)*P(l,k);
//	}
//      }
//      for(rPr_plus_1=1,k=0;k<AP_NU;k++) rPr_plus_1+=rP(k)*r(k);
//      for(i=0;i<AP_NU;i++){/**/
//#ifdef MSPC
//	z(i) += r(i)*(AP_r-p(j));/**/
//#else
//	z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-AP_y_under2-p(j));/**/
//#endif
//	for(k=0;k<AP_NU;k++){
//	  P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
//	}
//      }
//    }//for(j=0;j<AP_N2;j++)    
//    for(umin=AP_z[1],j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
//  }//endof  else if(penalty==2)
//
//  else{/*2006/12/26/koshi*/ //penalty==3
//    /*step 1: ステップ応答を求める*/
//#define GPC_KURO ////2010.01.19 by kuro
//#ifdef GPC_KURO/*GPCの原著ではΔuに対するステップ応答*/
//    for(j=0;j<AP_N2;j++){
//      g(j)=0;
//      for(i=0;i<AP_nu;i++) if(i<=j) g(j)+=b[i];
//      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
//    }
//#else /*インパルス応答*/
//    for(j=0;j<AP_N2;j++){
//      if(j<AP_nu) g(j)=b[j];
//      else g(j)=0;
//      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
//    }
//#endif
//    /*step 2 u(t+i)=u(t-1)とした応答pの計算*/
//    /**/
//    for(j=0;j<AP_N2;j++){
//      p(j)=c;
//#define useoriginalGPC //2010.01.19 by kuro
//#ifdef useoriginalGPC      //compensated by kuro because some one omit below from can2b050205.tgz
//      for(i=0;i<AP_nu;i++){
//	if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
//	else p(j)+=b[i]*AP_uu[1];
//      }
//#endif //endof useoriginalGPC
//      //some one omit above
//      for(i=0;i<AP_ny;i++){
//#ifdef nouseoriginal
//	if(j<=i) p(j)+=a[i]*(AP_yy[(i-j+1)]);//do not use this original !?
//#else
//	if(j<=i) p(j)+=a[i]*(AP_yy[(i-j+1)]-AP_yy[(i-j+2)]);//
//	//	if(j<=i) p(j)+=a[i]*(AP_yy[(i-j)]-AP_yy[(i-j+1)]);//not this even if 1st order difference
//#endif
//	else p(j)+=a[i]*p(j-i-1);
//      }
//    }
//    for(i=0;i<AP_NU;i++){
//      z(i)=0;
//      for(j=0;j<AP_NU;j++){
//	if(i==j) P(i,j)=1./lambda;/**/
//	else P(i,j)=0;
//      }
//    }   
//    for(j=0;j<AP_N2;j++){
//      for(k=0;k<AP_NU;k++){
//	if(k<=j) r(k)=g(j-k);
//	else r(k)=0;
//      }
//      for(k=0;k<AP_NU;k++){
//	Pr(k)=0;
//	rP(k)=0;
//	for(l=0;l<AP_NU;l++){
//	  Pr(k) += P(k,l)*r(l);
//	  rP(k) += r(l)*P(l,k);
//	}
//      }
//      for(rPr_plus_1=1,k=0;k<AP_NU;k++) rPr_plus_1+=rP(k)*r(k);
//      if(j>0) p(j) += p(j-1);
//      for(i=0;i<AP_NU;i++){/**/
//#ifdef MSPC
//	z(i) += r(i)*(AP_r-(AP_yy[0]+p(j)));//first order difference?
//#else //#ifdef MSPC
//	z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-AP_y_under2-p(j));/**/
//#endif //#ifdef MSPC
//	for(k=0;k<AP_NU;k++){
//	  P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
//	}
//      }
//    }//for(j=0;j<AP_N2;j++)   
//    for(umin=AP_z[1],j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
//  }//penalty==3
//  //  else if((AP_y<AP_r-1)&& umin<0) umin=0.01*AP_u_max;
//  if(u_limit==0){
//    if(umin>AP_u_max) umin=AP_u_max;
//    else if(umin<AP_u_min) umin=AP_u_min;
//  }
////  if(it==0&&matrix_0==1){
////    umin=AP_u_max*0.10;
////  }
//  //  if(time>starttime && time<starttime+5) umin=AP_u_max; 
//  //  if(time<5) umin=AP_u_max; 
//  return(umin);
//}//endof FLOAT predict_search_AP1(int m)
#endif
/******************EndOfMSPC******************/
//#ifdef GPC
///* mallocが使用できない為、固定にする	99/11/09 S.Kurogi*/
//FLOAT *g_buf,*p_buf,*P_buf,*r_buf,*z_buf,*Pr_buf,*rP_buf;
///* mallocが使用できない為、バッファに変更	99/11/08 T.Arita*/
//#ifdef EMULATE
//FLOAT APC_BUF[27];
//#else
//FLOAT APC_BUF[27];
//#endif
//#define p(j) p_buf[(j)]
//#define g(j) g_buf[(j)]
//#define r(j) r_buf[(j)]
//#define P(i,j) P_buf[(i)*AP_NU+(j)]
//#define Pr(j) Pr_buf[(j)]
//#define rP(j) rP_buf[(j)]
//#define z(j) z_buf[(j)]
//#define lambda (AP_N2*5e-3/AP_NU)
//#endif
//#ifdef GPC1
///*********************************************************/
//FLOAT predict_search_AP()
///**********************************************************/
//{
//  int i,j,k,l;
//  FLOAT umin;
//  FLOAT c;
//  FLOAT rPr_plus_1;
///****/
//  c=AP_M[0][0]*AP_z[0];
//  g(0)=AP_M[0][1];
//  if(AP_NP>1) g(1)=AP_M[0][2]*g(0);
//  for(j=2;j<AP_N2;j++){
//    g(j)=AP_M[0][2]*g(j-1)+AP_M[0][3]*g(j-2);
//  }/**/
//  /*step 2*/
//  for(j=0;j<AP_N2;j++){/*pの計算*/
//    if(j==0) p(0)=AP_M[0][2]*AP_y+AP_M[0][1]*AP_z[1]+c;
//    else if(j>=1) p(j)=AP_M[0][2]*p(j-1)+AP_M[0][1]*AP_z[1]+c;
//  }
//  for(i=0;i<AP_NU;i++){
//    z(i)=0;
//    for(j=0;j<AP_NU;j++){
//      if(i==j) P(i,j)=1./lambda;/**/
//      else P(i,j)=0;
//    }
//  }
//  /*step 3*/
//  for(j=0;j<AP_N2;j++){
//    for(k=0;k<AP_NU;k++){
//      if(k<=j) r(k)=g(j-k);
//      else r(k)=0;
//    }
//    for(k=0;k<AP_NU;k++){
//      Pr(k)=0;
//      rP(k)=0;
//      for(l=0;l<AP_NU;l++){
//	Pr(k) += P(k,l)*r(l);
//	rP(k) += r(l)*P(l,k);
//      }
//    }
//    for(rPr_plus_1=1,k=0;k<AP_NU;k++) rPr_plus_1+=rP(k)*r(k);
//    for(i=0;i<AP_NU;i++){/**/
//#ifdef MSPC
//      z(i) += r(i)*(AP_r-p(j));/**/
//#else
//      z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-AP_y_under_2-p(j));/**/
//#endif
//      for(k=0;k<AP_NU;k++){
//	P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
//      }
//    }
//  }
//  for(umin=0,j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
//  if(umin>AP_u_max) umin=AP_u_max;
//  else if(umin<AP_u_min) umin=AP_u_min;
//  return(umin);
//}
//#endif//#ifdef GPC1
//
//#ifdef GPC2
///*********************************************************/
//FLOAT predict_search_AP()
///*********************************************************/
//{
//  int i,j,k,l;
//  FLOAT umin;
//  FLOAT c;
//  FLOAT rPr_plus_1;
///****/
//  c=AP_M[0][0]*AP_z[0];
//  g(0)=AP_M[0][1];
//  if(AP_NP>1) g(1)=AP_M[0][2]*g(0);
//  for(j=2;j<AP_N2;j++){
//    g(j)=AP_M[0][2]*g(j-1)+AP_M[0][3]*g(j-2);
//  }/**/
//  /*step 2*/
//  for(j=0;j<AP_N2;j++){/*pの計算*/
//    if(j==0) p(0)=AP_M[0][2]*AP_y+AP_M[0][3]*AP_z[2]+AP_M[0][1]*AP_z[1]+c;
//    else if(j==1) p(1)=AP_M[0][2]*p(0)+AP_M[0][3]*AP_y+AP_M[0][1]*AP_z[1]+c;
//    else if(j>=2) p(j)=AP_M[0][2]*p(j-1)+AP_M[0][3]*p(j-2)+AP_M[0][1]*AP_z[1]+c;
//  }
//  for(i=0;i<AP_NU;i++){
//    z(i)=0;
//    for(j=0;j<AP_NU;j++){
//      if(i==j) P(i,j)=1./lambda;/**/
//      else P(i,j)=0;
//    }
//  }
//  /*step 3*/
//  for(j=0;j<AP_N2;j++){
//    for(k=0;k<AP_NU;k++){
//      if(k<=j) r(k)=g(j-k);
//      else r(k)=0;
//    }
//    for(k=0;k<AP_NU;k++){
//      Pr(k)=0;
//      rP(k)=0;
//      for(l=0;l<AP_NU;l++){
//	Pr(k) += P(k,l)*r(l);
//	rP(k) += r(l)*P(l,k);
//      }
//    }
//    for(rPr_plus_1=1,k=0;k<AP_NU;k++) rPr_plus_1+=rP(k)*r(k);
//    for(i=0;i<AP_NU;i++){/**/
//#ifdef MSPC
//      z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-p(j));/**/
//#else
//      z(i) += r(i)*(AP_r-p(j));/**/
//#endif
//      for(k=0;k<AP_NU;k++){
//	P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
//      }
//    }
//  }
//  for(umin=AP_z[1],j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
//  if(umin>AP_u_max) umin=AP_u_max;
//  else if(umin<AP_u_min) umin=AP_u_min;
//  /*printf("umin=%f\n",umin); /**/
//  return(umin);
//}
//#endif//#ifdef GPC2
//#define BWF
//#undef BWF
//#ifdef BWF /*バタワースフィルタ*/
//FLOAT AP_y0,AP_y1,AP_y2,AP_yy1;
///*BWF#3ダメ,4.000000 [Hz],
//パスバンド周波数 : 0.005000 [Hz]
//ストップバンド周波数 : 0.010000 [Hz]
//パスバンド端減衰量 : 3.000000 [dB]
//ストップバンド端減衰量 : 10.000000 [dB]
//#define BWF_k   2.48613807057856018e-01
//#define BWF_b1 -1.98887971173257294e+00
//#define BWF_b2  9.88941201193123343e-01
//#define BWF_a0  6.18323065783157942e-05
//#define BWF_a1  1.23664613156631588e-04
//#define BWF_a2  6.18323065783157942e-05
///**/
///*BWF#1サンプリング周波数 : 20.000000 [Hz]
//パスバンド周波数 : 1.500000 [Hz]
//ストップバンド周波数 : 3.000000 [Hz]
//パスバンド端減衰量 : 3.000000 [dB]
//ストップバンド端減衰量 : 10.000000 [dB]
//#define BWF_k  1.78865175977607815e-01
//#define BWF_b1 -1.34825016312690305e+00
//#define BWF_b2 5.13592652514821890e-01
//#define BWF_a0 2.31099330101878137e-01
//#define BWF_a1 4.62198660203756273e-01
//#define BWF_a2 2.31099330101878137e-01
///**/
///*BWF#2フィルタの次数 : 2
//セクション数 : 1
//種類 : LPF
//サンプリング周波数 : 4.000000 [Hz]
//パスバンド周波数 : 0.050000 [Hz]
//ストップバンド周波数 : 0.100000 [Hz]
//パスバンド端減衰量 : 3.000000 [dB]
//ストップバンド端減衰量 : 10.000000 [dB]*/
//
///* コンパイラの制限により有効桁数を17桁にする	99/11/12 T.Arita*/
///*#define BWF_k   2.36478626953582627e-01
///*#define BWF_b1 -1.88890163277109613e+00
///*#define BWF_b2  8.94756398486225901e-01
///*#define BWF_a0  6.18952946250698934e-03
///*#define BWF_a1  1.23790589250139787e-02
///*#define BWF_a2  6.18952946250698934e-03*/
//#define BWF_k   2.3647862695358263e-01
//#define BWF_b1 -1.8889016327710961e+00
//#define BWF_b2  8.9475639848622590e-01
//#define BWF_a0  6.1895294625069893e-03
//#define BWF_a1  1.2379058925013979e-02
//#define BWF_a2  6.1895294625069893e-03
///**/
//#endif//#ifdef BWF
/*======================================================*/
void set_AP_r(void) /* 目標温度の設定，変更のとき99/06/25*/
/*======================================================*/
{
//  FLOAT tmp;
  CHG.b.SV = 0;
  //  AP_y=PV1/YB;//YB=100
  AP_y=PV1;//YB=100

//#ifndef MSPC
//#ifdef BWF
//  AP_y0=AP_y1=AP_y2=AP_y;/*BWF*/
//#endif
//  if(ATF.b.AT_APC_F){ 
//    /* ATモードを廃止し、ATFフラグを使用する	99/11/08 T.Arita*/
//    /* 新しいAT機能を使用する					*/
////#ifndef MSPC
////    AP_AT_y[0]=AP_y;
////    AP_AT_y[1]=AP_y+0.10*(AP_r-AP_y);
////    AP_AT_y[2]=AP_y+0.50*(AP_r-AP_y);
////    AP_AT_y[3]=AP_y+0.80*(AP_r-AP_y);
////    AP_AT_j[0]=0;/*requested by Mimata ???*/
////    AP_AT_y[6]=AP_y+0.90*(AP_r-AP_y);
////    AP_AT_cycle=1;
////    AP_AT_jikan=0;
////    AP_y_smooth_tau=1000.;
////    AP_y_smooth=(AP_r-AP_y);
////    AP_y_smooth_r=Gensui(AP_y_smooth_tau);/**/
////#endif
//  }
//  else{
//    if(AP_tau==0 && AP_0==0 && AP_RESET_T==0 && AP_THHS==0){/* 自動設定モード */
//      /*if(AP_tau==0 && AP_0==0 && AP_RESET_T==0){/* 自動設定モード */
//      if(C_MODE==DEF_APC){/* 自己発熱がない（水，リン酸など）場合のモード */
//        tmp = 0.8;
//#ifndef MSPC
//        AP_y_smooth=(AP_r-AP_y)*tmp;/**/
//        AP_y_smooth_tau=1000.;
//#endif
//        _AP_RESET_T=0.;
//      }
//      else if(C_MODE==SPM_APC){/*自己発熱がある（硫酸過水）の場合の自動設定モード*/
//	tmp = 1.0;/**/
//#ifndef MSPC
//        AP_y_smooth=(AP_r-AP_y)*tmp;
//        AP_y_smooth_tau=AP_approx(AP_r,2300.,135.,1000.,110.);/*apc-spm990711a.cs*/
//#endif
//#ifndef MSPC
//#ifdef EMULATE
//	/*AP_y_smooth_tau = 1158;/**/
//	AP_y_smooth_tau = 100;/**/
//#endif
//#ifdef APC1
//        AP_y_smooth_tau *= AP_approx(AP_Np,1.3,4.,1.,2.);
//#endif
//#ifdef APC2
///*        AP_y_smooth_tau *= AP_approx(AP_Np,1.1,4.,1.,2.);/**/
//        AP_y_smooth_tau *= AP_approx(AP_Np,1.2,4.,1.,2.);
//#endif
//#ifdef GPC
//        /*AP_y_smooth_tau *= AP_approx(AP_Np,1.05,4.,1.,2.);*/
//#endif
//#endif
//      }
//      else if(C_MODE==SC2_APC){/*自己発熱がある（塩酸過水）の場合の自動設定モード*/
//        tmp = 1.0;
//#ifndef MSPC
//        AP_y_smooth=(AP_r-AP_y)*tmp;
//        /* 塩酸過水の自動設定モードでのAP_y_smooth_tauの補間値変更 */
//        AP_y_smooth_tau=AP_approx(AP_r,1800.,80.,1000.,50.);
//        /*_AP_RESET_T=0.;/*コメントアウト by 99/11/12/ Kurogi*/
//#endif
//      }
//      /* 自動設定モードでのAP_y_smooth_tauのリミッタ追加 */
//      /*if(AP_y_smooth_tau<1000.)	AP_y_smooth_tau=1000.;/* AP_y_smooth_tauは1000以上とする */
//      /*if(AP_y_smooth_tau<500.)	AP_y_smooth_tau=500.;/* AP_y_smooth_tauは1000以上とする */
//      _AP_THHS=100;/*99/11/24*/
//      _AP_RESET_T=0;/*by 99/11/12/ Kurogi*/
//      /* 自動設定モードでの設定値表示の為、値を設定する */
//      AP_0_D=(WORD)(tmp*1000.+.5);
//#ifndef MSPC
//      AP_tau_D=(WORD)(AP_y_smooth_tau+.5);/**/
//#endif
//      AP_RESET_T_D=(WORD)(_AP_RESET_T*100.+.5);
//      AP_THHS_D=_AP_THHS;/*？？有田さんチェックお願い99/11/22*/
//    }
//    else{/* マニュアルモード */
//#ifndef  MSPC
//      tmp = (FLOAT)AP_0/1000.;
//      AP_y_smooth=(AP_r-AP_y)*tmp;/**/
//      AP_y_smooth_tau=(FLOAT)AP_tau;/**/
//      _AP_RESET_T=(FLOAT)AP_RESET_T/100.;
//      _AP_THHS=AP_THHS;/*99/11/24*/
//#endif
//    }
//  }
//  /* もにた通信用の為、値を設定する */
//  AP_0_M=(WORD)(tmp*1000.+.5);
//#ifndef MSPC
//  AP_tau_M=(WORD)(AP_y_smooth_tau+.5);/**/
//#endif
//  /*理想はAP_y_smooth_r=exp(-4*AP_tS/AP_y_smooth_tau);/**/
//  /*  AP_y_smooth_r=1.-AP_tS*4./AP_y_smooth_tau;/**/
//#ifndef MSPC
//  AP_y_smooth_r=Gensui(AP_y_smooth_tau);/**/
//  AP_y_under=0;/**/
//  AP_y_under2=0;/**/
//  AP_y_reach=-1;/**/
//#endif
//#ifdef SPM_REINIT_BY_KASO
//  AP_y_reach1=0;/**/
//#endif#ifdef SPM_REINIT_BY_KASO
//#endif
}
/*======================================================*/
void reinit_AP(void)  /* 適応制御再初期化:行列は初期化しない*/
/*======================================================*/
{
  int i;
  allerr=0;
  ste_allerr=0;
  tra_allerr=0;
  mid_allerr=0;
  n_of_saishokika=0;
  init_err=0;
  energy_sum=0;
  energy1=0;
  energy=0;
  energy_mean=0;
  AP_yyy=0;
  /* 適応予測制御の機能追加				99/11/08 T.Arita*/
  /*  予測ステップ数、仮想サンプリング時間の追加				*/
  /* GPCの予測ステップ数=4はRAM領域の関係上、できない			*/
  /* GPCの予測ステップ数=3にする為、仮想サンプリング周期は80秒			*/
  /*  AP_Np=4;*/
  /*  AP_Np=AP_NP;*/
  AP_tS1=(FLOAT)AP_TS1;    /*仮想サンプリング周期(秒)*/
  /*  AP_tS1=80.00;    /*仮想サンプリング周期(秒)*/
  /*  AP_tS1=40.00;    /*仮想サンプリング周期(秒)*/
  /*  AP_tS1=60.00;    /*仮想サンプリング周期(秒)*/
  /*  AP_u_res=5;     /*入力分解能*/
  /*  AP_u_res=50;     /*入力分解能*/
#ifndef MSPC
  AP_u_res=10;     /*入力分解能*/
#endif
/*  AP_z[0]=1e-10;   /*最小二乗の定数項の重み  */
/*    AP_z[0]=1e-4;   /*最小二乗の定数項の重み  */
  AP_z[0]=1.0;   /*最小二乗の定数項の重み  */
  //  AP_u_max=M_MAX;  /*入力最大値の設定 M_MAX in cs_emu.h*/
  //  AP_u_min=M_MIN;  /*入力最大値の設定 M_MAX in cs_emu.h*/ //061227kuwa
  //  AP_u_max=crane.dXmax/5.;  /*入力最大値の設定 */
  //  AP_u_min=-crane.dXmax/5.;  /*入力最大値の設定 */ //061227kuwa
  AP_kS1=AP_tS1/AP_tS;  
  /*********************/
  set_AP_r();/*目標温度の設定・変更*/
  /*********************/
#ifndef MSPC
  AP_y_ave=AP_y;   /*出力平均値*/
#endif
  AP_y_k=AP_y_k_minus_1=AP_y;
  AP_u_k=AP_u_k_minus_1=0;
  AP_k= AP_k_hajime=0;
  AP_kk=0;
  AP_overshoot=0;
  for(i=0;i<AP_nu+AP_IS+1;i++) AP_u_sum[i]=0;
  for(i=0;i<AP_ny+AP_IS+1;i++) AP_y_sum[i]=0;
  /* AT方法変更の為、削除		99/11/08 T.Arita*/
  /* 適応予測制御の組込			99/07/29 T.Arita*/
  /* AT機能の処理追加					*/
/*  AP_AT_MAX = 3600 / (int)AP_tS1;
/*  AP_AT_CNT = 0;
  /* ATの終了チェックの追加			99/08/17 T.Arita*/
  /* SV-PVが±0.3℃以内に10分安定でもAT終了とする	*/
/*  AP_AT_ANTEI_CNT = 0;
*/
 /*目標温度に到達しない場合があるのは蒸発の影響と考え，
   温度の変数とした.99/11/15
   また，グローバル変数にした.99/11/22*/
  //    AP_HoseiKaisiOndo=AP_approx(AP_r,3.0,80.,0.5,30.);
  //    if(AP_HoseiKaisiOndo>6) AP_HoseiKaisiOndo=6;/*135℃では5.75*/
}
/*======================================================*/
void init_AP(void)          /* 適応制御の準備と初期化 */
/*======================================================*/
{
  //  AP_KyoyouOndoGosa=2;
  init_MQ_AP();
  reinit_AP();
#ifdef MSPC
//  if( AP_NP > 11 ) AP_NP=11;
//  if( AP_NP >= 7 ){
//    AP_NU = 1;
//  }else if( AP_NP > 3 ){
//    AP_NU = 2;
//  }else {
//    AP_NU = AP_NP;
//  }
//  /*AP_N2=AP_NU=4;/**/
//  /*AP_N2=AP_NU=4;/**/
///*  AP_N2=AP_NU=3;/**/
//  p_buf=&APC_BUF[0];
//  g_buf=&p_buf[AP_N2];
//  P_buf=&g_buf[AP_N2];
//  r_buf=&P_buf[AP_NU*AP_NU];
//  z_buf=&r_buf[AP_NU];
//  Pr_buf=&z_buf[AP_NU];
//  rP_buf=&Pr_buf[AP_NU];
#endif
//#ifdef GPC
//  /* AP_NUの追加				99/11/12 T.Arita*/
//  /* AP_NP<=11, AP_NU<=AP_NP,N2*2+Nu*(Nu+4)<=27 の追加	99/11/14 Kurogi*/
//  if( AP_NP > 11 ) AP_NP=11;
//  if( AP_NP >= 7 ){
//    AP_NU = 1;
//  }else if( AP_NP > 3 ){
//    AP_NU = 2;
//  }else {
//    AP_NU = AP_NP;
//  }
//  p_buf=&APC_BUF[0];
//  g_buf=&p_buf[AP_N2];
//  P_buf=&g_buf[AP_N2];
//  r_buf=&P_buf[AP_NU*AP_NU];
//  z_buf=&r_buf[AP_NU];
//  Pr_buf=&z_buf[AP_NU];
//  rP_buf=&Pr_buf[AP_NU];
//#endif
}
//#ifdef SPM_REINIT_BY_KASO
//void spm_reinit_AP()
//{
//  if(_AP_RESET_T!=0.0){/*SPM_REINIT_BY_SETTEI/**/
//    if(AP_y>=_AP_RESET_T && AP_y_reach1==0) {
//      /*制御パラメータリセット温度が設定されていて、その温度になったら軌道再設定*/
//        reinit_AP();
//        AP_y_reach1=1;
//    }
//  }
//  else{ /*SPM_REINIT_BY_KASO/**/
///*実温が100℃以下で仮想目標温度より5℃以上高いと再初期化：
//　実際の制御と同じにしないといけない：上の行参照*/
//    if(AP_y<100.0 &&
//       ((AP_y-(AP_r-AP_y_smooth)>+5.0 && AP_r-AP_y>0)||
//	(AP_y-(AP_r-AP_y_smooth)<-5.0 && AP_r-AP_y<0)))
//      reinit_AP();
//  }
//}
//#endif
/*======================================================*/
void     calc_AP(void)               /* 適応予測制御演算*/
/*======================================================*/
/*	入力  ：  センサ温度 	PV1			*/
/*	出力  ：  操作量	SMV			*/
/*======================================================*/
{
  int j,i,m,bag_i,boost_i;
  FLOAT aaa;
  /**/
  //090622 yuno
  //081010koshi
  int k; //AP_n_out
  int hi;
  FILE *fpi; //090204koshi
  AP_y=PV1;
  //  AP_y=PV1/YB;/*YB=100*/
  /*  AP_y=(PV1+((2.*random()-1.)*0.7)*YB)/YB;/**/
  /*  AP_y=0.9*AP_y +0.1*PV1/YB+((2.*random()-1.)*0.07);*/
  if(AP_y-AP_r>AP_overshoot) AP_overshoot=AP_y-AP_r;
  if(flag==1){
    //    if((nuse_flag==1)&&(uni_flag==1)&&(it>=1)){
    if((nuse_flag==1)&&(uni_flag==1)){//kuro20100125
      if((fpi=fopen("input.dat","w+"))==NULL){//090127koshi
	exit(1);
      }
      fprintf(fpi,"time ");
      for(hi=1;hi<=num_nets;hi++){
	fprintf(fpi,"SMV_n[%d] ",hi);
      }
      fprintf(fpi,"select_net ");
      fprintf(fpi,"out_put ");
      for(hi=1;hi<=num_nets;hi++){
	fprintf(fpi,"predictive_error[%d] ",hi);
      }
      fprintf(fpi,"real_error");
      fprintf(fpi,"\n");
      fclose(fpi);
      flag=0;
      if((fpi=fopen("t-AP_i.dat","w+"))==NULL){
	fprintf(stderr,"#Stop by Error at opeining t-AP_i.dat");
	exit(1);
      }
      fprintf(fpi,"#time i_net AP_i M0-Mn #case2\n");
      fclose(fpi);
    }
    //    else if((num_nets==1)&&(it>=1)){
    else if((num_nets==1)){//20100125kuro
      if((fpi=fopen("input.dat","w+"))==NULL){//090127koshi
	exit(1);
      }
      fprintf(fpi,"time ");
      fprintf(fpi,"SMV ");
      fprintf(fpi,"out_put ");
      fprintf(fpi,"predictive_output[ ");
      fprintf(fpi,"\n");
      fclose(fpi);
      flag=0;
      if((fpi=fopen("t-AP_i.dat","w+"))==NULL){
	fprintf(stderr,"#Stop by Error at opeining t-AP_i.dat");
	exit(1);
      }
      fprintf(fpi,"#time i_net AP_i M0-Mn #case1\n");
      fclose(fpi);
    }
    else{
    }


  }
  /*00/10/05に変更*/
  if(AP_k==0){//AP_kS1毎original? AP_k=[0,AP_kS1] Virtual sampling
    AP_u_sum[0] += 0.5*AP_u;
    AP_y_sum[0] += 0.5*AP_y;
    AP_u_sum[0]=AP_u_sum[0]/AP_kS1;
    AP_y_sum[0]=AP_y_sum[0]/AP_kS1;
    for(i=AP_nu+AP_IS+1;i>=1;i--) AP_u_sum[i]=AP_u_sum[i-1];
    for(i=AP_ny+AP_IS+1;i>=1;i--) AP_y_sum[i]=AP_y_sum[i-1];
    AP_u_sum[0]=AP_y_sum[0]=0;
    AP_u_sum[0] += 0.5*AP_u;
    AP_y_sum[0] += 0.5*AP_y;
  }
  else{
    AP_u_sum[0] += AP_u;
    AP_y_sum[0] += AP_y;
  }/**/
//090624 yuno結果が大きく変わった
  double AP_k_start=AP_kS1*(AP_ny);/*100119kuro*/
//  double AP_k_start=AP_kS1*(AP_ny+AP_IS);/*090331kuro*/
  //  if(AP_k_start<630) AP_k_start=605;/*090331kuro; good for rca*/
  if(AP_k_hajime>=AP_k_start){/*090331kuro*/
    FLOAT aaaa;
    aaa=0.5-(FLOAT)AP_k/(FLOAT)AP_kS1;
    for(i=1;i<AP_IS+AP_ny;i++){
      AP_uu[i]=AP_u_sum[i]-(AP_u_sum[i]-AP_u_sum[i+1])*aaa;
    }
    for(i=1;i<AP_IS+AP_ny;i++){
      AP_yy[i]=AP_y_sum[i]-(AP_y_sum[i]-AP_y_sum[i+1])*aaa;
    }
    AP_yy[0]=AP_y;
    for(i=1;i<=AP_nu+1;i++) AP_z[i]=AP_uu[i];/*2007/02/18/koshi*/
    for(i=1;i<=AP_ny+1;i++) AP_z[i+AP_nu+1]=AP_yy[i];
    //090622 yuno
    /****一次差分信号を保存****/ //080508koshi
    AP_d[0]=0;
    AP_dy[0]=AP_yy[0]-AP_yy[1];
    AP_du[0]=0;
    for(i=1;i<=AP_nu;i++) AP_du[i]=AP_uu[i]-AP_uu[i+1];
    for(i=1;i<=AP_ny;i++) AP_dy[i]=AP_yy[i]-AP_yy[i+1];
    for(i=1;i<=AP_nu;i++) AP_d[i]=AP_du[i];
    for(i=1;i<=AP_ny;i++) AP_d[i+AP_nu]=AP_dy[i];

#ifdef MSPC
    //090622 yuno
    if(it>0){//??
      AP_n_kk++;//every sampling period AP_tS
      AP_n_kk_Ne=AP_n_kk%Ne;//for mse
    if(ensemble==0){
      //if((it>=1)&&(uni_flag==1)&&(nuse_flag==1)){
      if((uni_flag==1)&&(nuse_flag==1)){//kuro20100125-- 
	//multiple nets (num_nets>=2) and switching 
	//各ネットでユニットを選択する
	for(i=1;i<=num_nets;i++) st_n_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,uni_AP_NC[i]);//(works 20120412)
	//	AP_n_kk++;//every sampling period AP_tS
	//	AP_n_kk_Ne=AP_n_kk%Ne;//for mse
	//エネルギから選択
	for(i=1;i<=num_nets;i++){//check for ICONIP2010 
	  energy_n1[i]=-AP_y+net[i].cell[st_n_AP_i[i]].M[0][0]*AP_z[0]+AP_yy[1];
	  for(hi=1;hi<=AP_nu;hi++) energy_n1[i] += net[i].cell[st_n_AP_i[i]].M[0][hi]*AP_du[hi];
	  for(hi=1;hi<=AP_ny;hi++) energy_n1[i] += net[i].cell[st_n_AP_i[i]].M[0][hi+AP_nu]*AP_dy[hi];
	  energy_sum_n[i]+=(energy_n1[i]*energy_n1[i]);
	  energy_n[i]=energy_sum_n[i]/AP_n_kk;
	  energy_mean_n[i]+=energy_n[i];
	  //ndy2=energy_n[i];
	  mse[i][AP_n_kk_Ne]=(energy_n1[i]*energy_n1[i]);//energy of i-th net at AP_n_kk(time)
	  double ndy2=0;
	  if(AP_n_kk<Ne){for(hi=1;hi<=AP_n_kk;hi++) {int hi_Ne=hi%Ne;ndy2+=mse[i][hi_Ne];}}//?? total period?
	  else{for(hi=AP_n_kk-Ne;hi<=AP_n_kk;hi++) {int hi_Ne=hi%Ne;ndy2+=mse[i][hi_Ne];}}//
	  n_err[i]=ndy2;
	  if(i==1||ndy2<AP_n_err){
	    AP_n_err=ndy2;
	    AP_n_out=i;
	  }
	}//endof  for(i=1;i<=num_nets;i++)
	AP_i=st_n_AP_i[AP_n_out];
	for(i=0;i<=AP_nu+AP_ny;i++){
	  net[0].cell[AP_i].M[0][i]=net[AP_n_out].cell[st_n_AP_i[AP_n_out]].M[0][i];
	}
      }//end of if((it>=1)&&(uni_flag==1)&&(nuse_flag==1))
      else {//single net if(!((uni_flag==1)&&(nuse_flag==1))){
	//single net original (num_nets=1) or merged (num_nets>=2 & uni_flag==1 & nuse_flag=0)
//	if(it==1 && time>=11.16){//      if(it==1 && time>=11.18){
//	  fprintf(stderr,"#check PV1=%g at time=%g\n",PV1,time);
//	}
	AP_i=obtain_AP_i(AP_z,AP_y,net,0,AP_NC[0]);// 荷重ベクトルによるユニットの選択 (works 20120412)
//	if(it==1 && time>=11.16){//      if(it==1 && time>=11.18){
//	  fprintf(stderr,"#check PV1=%g at time=%g,AP_i=%d\n",PV1,time,AP_i);
//	}
//	AP_n_kk++;
//	AP_n_kk_Ne=AP_n_kk%Ne;
	double ndy2=0;
	energy_n1[0]=-AP_y+net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_yy[1];
	for(hi=1;hi<=AP_nu;hi++) energy_n1[0] += net[0].cell[AP_i].M[0][hi]*AP_du[hi];
	for(hi=1;hi<=AP_ny;hi++) energy_n1[0] += net[0].cell[AP_i].M[0][hi+AP_nu]*AP_dy[hi];
	energy_sum_n[0]+=(energy_n1[0]*energy_n1[0]);
	energy_n[0]=energy_sum_n[0]/AP_n_kk;
	energy_mean_n[0]+=energy_n[0];
      }//else{//single net if(!((uni_flag==1)&&(nuse_flag==1)))
    }//end of if(ensemble==0)
    //else if(bagging_flag==1 && num_boosts==1 && num_nets==0){//ensemble!=0 <== else of if(ensemble==0) 
    //void below until the next void ?
    else if(bagging_flag==1 && num_boosts==1){//ensemble!=0 <== else of if(ensemble==0) 
#define netid(i,j) ((i)*(num_nets)+(j))
      for(i=1;i<=num_nets;i++){
	for(j=1;j<=num_bags;j++){
	  st_AP_i[netid(i,j)]=obtain_AP_i(AP_z,AP_y,net,netid(i,j),uni_AP_NC[i]);//unitの選択
	  //	    st_AP_i[id(i,j)]=obtain_AP_i(AP_z,AP_y,net,in(i,j),bag_i+f_AP_NC-1);//unitの選択
	  //f_AP_NC:ID number of the first cell
	  //e_AP_NC:ID number of the last cell:
	  //n_AP_NC=e_AP_NC-f_AP_NC+1;
	  //AP_NC=f_AP_NC; ?
	  //st_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,bag_i+f_AP_NC-1);//unitの選択
	  //   st_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,in(i,bag_i+f_AP_NC-1);//unitの選択
	  //	    if((i%(resample_num*num_boosts))==0) bag_i++;
	}
      }
      AP_i=0;//ユニット1のため
      //連想行列の平均を取る
      for(i=0;i<AP_NN;i++){
	//ネットの初期化
	net[0].cell[AP_i].M[0][i]=0;
	for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){
	  net[net_num+m].cell[AP_i].M[0][i]=0;
	}
	//Mの計算
	bag_i=1;
	for(m=1;m<=net_num;m++){//Bagging
	  net[net_num+bag_i].cell[AP_i].M[0][i]+=net[m].cell[st_AP_i[m]].M[0][i];
	  if((m%resample_num)==0){
	    net[net_num+bag_i].cell[AP_i].M[0][i]/=resample_num;//resampe_num=bag_b
	    bag_i++;
	  }
	}
	boost_i=1;	
	for(m=1;m<=(num_boosts*n_AP_NC);m++){//Boosting?? no boosting for num_boosts=1 ?
	  net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].M[0][i]);
	  if((m%num_boosts)==0){
	    net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i]/=c_t_sum;
	    net[0].cell[AP_i].M[0][i] += net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i];
	    boost_i++;
	  }
	}
	net[0].cell[AP_i].M[0][i] = net[0].cell[AP_i].M[0][i]/n_AP_NC;
	for(j=0;j<AP_NN;j++){
	  //ネットの初期化
	  net[0].cell[AP_i].Q[i][j]=0;
	  for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){
	    net[net_num+m].cell[AP_i].Q[i][j]=0;
	  }	  
	  //Qの計算
	  bag_i=1;
	  for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){//Bagging
	    net[net_num+bag_i].cell[AP_i].Q[i][j]+=net[m].cell[st_AP_i[m]].Q[i][j];
	    if((m%resample_num)==0){
	      net[net_num+bag_i].cell[AP_i].Q[i][j]/=resample_num;
	      bag_i++;
	    }
	  }
	  boost_i=1;	
	  for(m=1;m<=(num_boosts*n_AP_NC);m++){//Boosting
	    net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].Q[i][j]);
	    if((m%num_boosts)==0){
	      net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]/=c_t_sum;
	      net[0].cell[AP_i].Q[i][j] += net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j];
	      boost_i++;
	    }
	  } 
	  net[0].cell[AP_i].Q[i][j]=net[0].cell[AP_i].Q[i][j]/n_AP_NC;
	}
      }
      //***平均取り終わり*********
    }//end of else if(bagging_flag==1 && boosting_flag==1){//ensemble!=0 <== else of if(ensemble==0) 
    else if(bagging_flag==1 && boosting_flag==1){//ensemble!=0 <== else of if(ensemble==0) 
      //    else{//ensemble!=0 <== else of if(ensemble==0) 
      bag_i=1;
      for(i=1;i<=net_num;i++){
      	st_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,bag_i+f_AP_NC-1);//unitの選択
	if((i%(resample_num*num_boosts))==0) bag_i++;
      }     
      AP_i=0;//ユニット1のため
      //連想行列の平均を取る
      for(i=0;i<AP_NN;i++){
	//ネットの初期化
	net[0].cell[AP_i].M[0][i]=0;
	for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){
	  net[net_num+m].cell[AP_i].M[0][i]=0;
	}
	//Mの計算
	bag_i=1;
	for(m=1;m<=net_num;m++){//Bagging
	  net[net_num+bag_i].cell[AP_i].M[0][i]+=net[m].cell[st_AP_i[m]].M[0][i];
	  if((m%resample_num)==0){
	    net[net_num+bag_i].cell[AP_i].M[0][i]/=resample_num;//resampe_num=bag_b
	    bag_i++;
	  }
	}
	boost_i=1;	
	for(m=1;m<=(num_boosts*n_AP_NC);m++){//Boosting?? no boosting for num_boosts=1 ?
	  net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].M[0][i]);
	  if((m%num_boosts)==0){
	    net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i]/=c_t_sum;
	    net[0].cell[AP_i].M[0][i] += net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i];
	    boost_i++;
	  }
	}
	net[0].cell[AP_i].M[0][i] = net[0].cell[AP_i].M[0][i]/n_AP_NC;
	for(j=0;j<AP_NN;j++){
	  //ネットの初期化
	  net[0].cell[AP_i].Q[i][j]=0;
	  for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){
	    net[net_num+m].cell[AP_i].Q[i][j]=0;
	  }	  
	  //Qの計算
	  bag_i=1;
	  for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){//Bagging
	    net[net_num+bag_i].cell[AP_i].Q[i][j]+=net[m].cell[st_AP_i[m]].Q[i][j];
	    if((m%resample_num)==0){
	      net[net_num+bag_i].cell[AP_i].Q[i][j]/=resample_num;
	      bag_i++;
	    }
	  }
	  boost_i=1;	
	  for(m=1;m<=(num_boosts*n_AP_NC);m++){//Boosting
	    net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].Q[i][j]);
	    if((m%num_boosts)==0){
	      net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]/=c_t_sum;
	      net[0].cell[AP_i].Q[i][j] += net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j];
	      boost_i++;
	    }
	  } 
	  net[0].cell[AP_i].Q[i][j]=net[0].cell[AP_i].Q[i][j]/n_AP_NC;
	}
      }
      //***平均取り終わり*********
    }//end of if(ensemble==0...else if(bagging_flag==1 && num_boosts==1)..else if(bagging_flag==1 && boosting_flag==1){//ensemble!=0 <== else of if(ensemble==0) 
    else{
      if(bagging_flag201204){
	if(num_tems==0 && it>0){//deal with the net for learning, not loaded nets for num_tems>0. 
	  //  num_tems=1 is possible
	  //  net[0].cell[0].M[0][k] is for final answer
	  //  net[netid(i,j)].cell[l].M[0][k] is for the i-th lm(learning machine=baggedCAN2), j-th bag
	  //  net_n[i] is the name of the i-th lm(learning machine=baggedCAN2)
	  //#define netid(i,j) ((i)*(num_nets)+(j))
	  for(i=0;i<1;i++){//	for(i=0;i<num_tems;i++){
	    int k;for(k=0;k<=CAN2_k;k++) tem[i].net[0].cell[0].M[0][k]=0;//連想行列の平均を取る
	    for(j=1;j<=num_bags;j++){
	      AP_i=_obtain_AP_i(AP_z,AP_y,&(tem[i].net[j]));//unitの選択
	      for(k=0;k<=CAN2_k;k++) tem[i].net[0].cell[0].M[0][k]+=tem[i].net[j].cell[AP_i].M[0][k];
	      if(1==1){//20160523check
		FILE *fptmp=fopen("tmp.dat","a+");
		fprintf(fptmp,"%f %d ",time,AP_i);
		for(k=0;k<=CAN2_k;k++) fprintf(fptmp,"%e ",tem[i].net[j].cell[AP_i].M[0][k]);
		fprintf(fptmp,"#case1 \n");
		fclose(fptmp);
	      }
	    }
	    for(k=0;k<=CAN2_k;k++) tem[i].net[0].cell[0].M[0][k]/=num_bags;
	  }//
	  AP_i=0;//
	}//endof if(num_tems==0 && it>0)
	else{//num_tems>=1 ; MSPC (model switching predictive control)
	  double mse_min=INFTY;
	  int i_mse_min=1;
	  int AP_i_buff[num_tems];
	  for(i=1;i<=num_tems;i++){//	for(i=0;i<num_tems;i++){
	    int k;for(k=0;k<=CAN2_k;k++) tem[i].net[0].cell[0].M[0][k]=0;//連想行列の平均を取る
	    //	    fprintf(stderr,"#i%d M%e %e %e %e\n",i,tem[1].net[1].cell[0].M[0][1],tem[1].net[1].cell[0].M[0][2],tem[1].net[1].cell[0].M[0][3],tem[1].net[1].cell[0].M[0][4]);
	    for(j=1;j<=num_bags;j++){
	      AP_i=_obtain_AP_i(AP_z,AP_y,&(tem[i].net[j]));//unitの選択
	      //AP_i=obtain_AP_i(AP_z,AP_y,&(tem[i].net[0]),j,AP_NC);//unitの選択
	      for(k=0;k<=CAN2_k;k++) tem[i].net[0].cell[0].M[0][k]+=tem[i].net[j].cell[AP_i].M[0][k];//copy AP_i to net[0].cell[0]
	      AP_i_buff[i]=AP_i; //bank of AP_i
	    }
	    for(k=0;k<=CAN2_k;k++) tem[i].net[0].cell[0].M[0][k]/=num_bags;
	    //	    fprintf(stderr,"#i%d M%e %e %e %e\n",i,tem[1].net[1].cell[0].M[0][1],tem[1].net[1].cell[0].M[0][2],tem[1].net[1].cell[0].M[0][3],tem[1].net[1].cell[0].M[0][4]);
//	    if(1==0){//check	    if(time<10){//check
//	      fprintf(stdout,"check i%d M[%d]=",i,AP_i);
//	      for(k=0; k<=CAN2_k; k++) fprintf(stdout,"%f ",tem[i].net[0].cell[0].M[0][k]);
//	      fprintf(stdout,"\n");
//	    }
	  //mspc; select by error for Ne
	  //Ne区間のmseから選択
	    double err=-AP_y+tem[i].net[0].cell[0].M[0][0]*AP_z[0]+AP_yy[1];
	    for(hi=1;hi<=AP_nu;hi++) err += tem[i].net[0].cell[0].M[0][hi]*AP_du[hi];
	    for(hi=1;hi<=AP_ny;hi++) err += tem[i].net[0].cell[0].M[0][hi+AP_nu]*AP_dy[hi];
	    tem[i].se[AP_n_kk_Ne]=(err*err);
	    //	    mse[i][AP_n_kk_Ne]=(err*err);//energy of i-th net at AP_n_kk(time)
	    double mse=0;
	    if(AP_n_kk<Ne){for(hi=1;hi<=AP_n_kk;hi++) {int hi_Ne=hi%Ne;mse+=tem[i].se[hi_Ne];}}//?? total period?
	    else{for(hi=AP_n_kk-Ne;hi<=AP_n_kk;hi++) {int hi_Ne=hi%Ne;mse+=tem[i].se[hi_Ne];}}//
	    //	    mse/=Ne;
	    if(mse<mse_min){
	      mse_min=mse;
	      i_mse_min=i;//AP_i minimizing mse of Ne horizon
	    }
//check 20160922
//	    if(AP_n_kk<=2){//AP_n_kk=1,2,... not 0
//	      fprintf(stderr,"#%.2f %d %d %e %d %d#check time AP_n_kk i mse Ne\n",time,i,AP_i_buff[i],mse,AP_n_kk,Ne);
//	      fprintf(stderr,"#i%d M%e %e %e %e\n",i,tem[i].net[0].cell[0].M[0][1],tem[i].net[0].cell[0].M[0][2],tem[i].net[0].cell[0].M[0][3],tem[i].net[0].cell[0].M[0][4]);
//	      fprintf(stderr,"#tem[1]%e %e %e ",tem[1].se[0],tem[1].se[1],tem[1].se[2]);
//	      fprintf(stderr,"#tem[2]%e %e %e \n",tem[2].se[0],tem[2].se[1],tem[2].se[2]);
//	    }
	  }//endof for(i=1;i<num_tems;i++){
	  {//for(i=1;i<=num_tems;i++){//??
	    //int modify4sotu2019=0; //make DEBUG=-g emulate_crane4
            //	    if(modify4sotu2019==1){
	    if(stab1>0 && num_tems>=2 && (time-starttime>=stab3 ||fabs(crane_X)>AP_r*stab4)){//20200123Ohgi){
          //	    if(stab1>0 && num_tems>=2 && time-starttime>=stab3){
          //i_mse_min=2;//number of the net 1 and 2 for weight 20 and 50, respectively
          //              AP_i=7-1;//7th unit   
              
          //              i_mse_min=1;//number of the net 1 and 2 for weight 20 and 50, respectively
          //              AP_i=8-1;//8th unit   
          
          i_mse_min=stab1;//The number of net
          AP_i=stab2-1;//The number of unit

          AP_i_buff[i_mse_min]=AP_i;
          int j=1; //bag number ;=1 for control problem
          int k;for(k=0;k<=CAN2_k;k++) tem[0].net[0].cell[0].M[0][k]=tem[i_mse_min].net[j].cell[AP_i].M[0][k];//recopy 
	    }
	    else{ //original before if(modify4sotu2019==1){
	      int k;for(k=0;k<=CAN2_k;k++) tem[0].net[0].cell[0].M[0][k]=tem[i_mse_min].net[0].cell[0].M[0][k];//recopy 
	    }
	  }
	  AP_i=0;//
	  if(1==1){//20160523check
	    FILE *fpi=fopen("t-AP_i.dat","a+");
	    fprintf(fpi,"%f %d %d ",time,i_mse_min,AP_i_buff[i_mse_min]);
	    for(k=0;k<=CAN2_k;k++) fprintf(fpi,"%e ",tem[0].net[0].cell[0].M[0][k]);
	    fprintf(fpi,"%.3f %e %d #case2 M[] y mse AP_n_kk\n",AP_y,mse_min,AP_n_kk);
	    fclose(fpi);
	  }
	  if(1==0){//check
	    fprintf(stdout,"time%g <M>=",time);
	    for(k=0; k<=CAN2_k; k++) printf("%f ",tem[0].net[0].cell[0].M[0][k]);
	    fprintf(stdout,"v%g\n",tem[0].net[0].cell[i].v);
	  }
	}//endof else{
      }//end of else if(bagging_flag201204 && num_nets==0){
    }//else if ensemble==0
    }//end of if(it>0)
    store_vector_AP(AP_z,AP_y); //    store_vector_AP(AP_z,AP_y,net);

    /*エネルギのE計算*/
    AP_kk++;/*エネルギ計算のため*//*2007/02/18/koshi*/
    energy1=-AP_y+net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_z[AP_nu+2];
    for(i=1;i<=AP_nu;i++) energy1 += net[0].cell[AP_i].M[0][i]*AP_du[i];
    for(i=1;i<=AP_ny;i++) energy1 += net[0].cell[AP_i].M[0][i+AP_nu]*AP_dy[i];
    energy_sum+=(energy1*energy1);
    energy=energy_sum/AP_kk;/*エネルギEの計算*/
    energy_mean+=energy;/*エネルギの平均の計算*/
    /*energy=energy_sum;/*自乗誤差総和の計算*/
    /*printf("%f,AP_kk=%f\n",time,AP_kk);/**/
    AP_yyy=0;//for record?
    AP_yyy+=net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_z[3];
    for(i=1;i<=AP_nu;i++) AP_yyy += net[0].cell[AP_i].M[0][i]*(AP_uu[i]-AP_uu[i+1]);
    for(i=1;i<=AP_ny;i++) AP_yyy += net[0].cell[AP_i].M[0][i+AP_nu]*(AP_yy[i]-AP_yy[i+1]);
    SMV=AP_u=predict_search_AP(AP_i);  /*操作量決定*///??for record?calc blow?
    if(1==0){//20160523check
      FILE *fptmp=fopen("tmp.dat","a+");
      fprintf(fptmp,"%f %f %d ",time,AP_u,AP_i);
      for(i=1;i<=AP_nu;i++) fprintf(fptmp,"%e ",net[0].cell[AP_i].M[0][i]);
      for(i=1;i<=AP_ny;i++) fprintf(fptmp,"%e ",net[0].cell[AP_i].M[0][i+AP_nu]);
      fprintf(fptmp,"\n");
      fclose(fptmp);
    }
    if((nuse_flag==1)&&(uni_flag==1)){//kuro20100125
      //      for(hi=1;hi<=num_nets;hi++){p_err[hi]=0;   }
      for(hi=1;hi<=num_nets;hi++){
	AP_yyn=0;
	AP_yyn+=net[hi].cell[st_n_AP_i[hi]].M[0][0]*AP_z[0]+AP_yy[1];
	for(i=1;i<=AP_nu;i++) AP_yyn += net[hi].cell[st_n_AP_i[hi]].M[0][i]*AP_du[i];
	for(i=1;i<=AP_ny;i++) AP_yyn += net[hi].cell[st_n_AP_i[hi]].M[0][i+AP_nu]*AP_dy[i];
	for(i=0;i<AP_NN;i++) net[0].cell[AP_i].M[0][i]=net[hi].cell[st_n_AP_i[hi]].M[0][i];
	AP_yn[hi]=AP_y-AP_yyn;//予測誤差
	SMV_n[hi]=predict_search_AP(AP_i);
      }
      //ファイルに書き込み
      if((fpi=fopen("input.dat","a+"))==NULL){
	exit(1);
      }
      fprintf(fpi,"%f ",time);
      for(hi=1;hi<=num_nets;hi++) fprintf(fpi,"%f ",SMV_n[hi]);
      fprintf(fpi,"%d ",AP_n_out);
      fprintf(fpi,"%f ",AP_y);
      for(hi=1;hi<=num_nets;hi++) fprintf(fpi,"%f ",AP_yn[hi]);
      fprintf(fpi,"%f ",AP_y-AP_yyy);
      //      fprintf(fpi,"%d %d #AP_i num_nets?",st_n_AP_i[1],num_nets);//20160523 for analyze
      fprintf(fpi,"\n");
      fclose(fpi);	
    }
    //    else if((num_nets==1)&&(it>=1)){
    else if((num_nets==1)){//kuro20100125
      if((fpi=fopen("input.dat","a+"))==NULL){
	exit(1);
      }
      fprintf(fpi,"%f ",time);
      fprintf(fpi,"%f ",SMV-AP_uu[1]);
      fprintf(fpi,"%f ",AP_y);
      fprintf(fpi,"%f ",AP_y-AP_yyy);
      fprintf(fpi,"%d #AP_i",AP_i);//20160523 for analyze
      fprintf(fpi,"\n");
      fclose(fpi);
    }
    else{
    }
    //#else //#ifdef MSPC
    //    SMV=AP_u=predict_search_AP(); /*操作量決定*/
#endif
#ifdef EMULATE
    //    SMV=AP_u=(AP_u_max/200.)*(int)(AP_u/(AP_u_max/200.)+0.5);
#endif
    /*    if(time<1000) printf("***%5.2f %f\n",time, SMV);*/
  }
  else {/*if(AP_k_hajime>=AP_k_start){/*090331kuro*/
    AP_k_hajime++;
#ifdef HEN
//20101213    /*制御開始時にもAPCで実行するように変更．99/11/15 Kurogi*/
//20101213    /*KELKでのSPM に対応ため上を元に戻す．99/11/17 Kurogi*/
//20101213    /*    if(C_MODE==SPM_APC){/*SPM 許容範囲2℃以内but自己発熱がある*/
//20101213#define ICONIP2001 1
//20101213    /*if(C_MODE==DEF_APC){/*SPM 許容範囲2℃以内but自己発熱がある*/
//20101213    /*if(1){/*SPM 許容範囲2℃以内but自己発熱がある*/
//20101213    /*if(AP_r>AP_y+10) SMV=AP_u=AP_u_max; /*操作量決定*/
//20101213    /*else if(AP_r>AP_y) SMV=AP_u=0.15*(AP_u_max-AP_u_min)+AP_u_min;
//20101213      /*else SMV=AP_u=0.0; /*操作量決定*/
//20101213    /* }*/
//20101213    /*else{/*許容範囲1℃以内*/
//20101213    AP_yy[0]=AP_y;
//20101213    /*for(i=1;i<=AP_nu;i++) AP_z[i]=AP_uu[i]=0.1*AP_u_max;/*80℃スタートの場合*/
//20101213    /*for(i=1;i<=AP_ny;i++) AP_z[i+AP_nu]=AP_yy[i]=AP_y;/*80℃スタートの場合*/
//20101213    //?for(i=1;i<=AP_nu;i++) AP_z[i]=AP_uu[i]=0.2*AP_u_max;/*エネルギがOSに良く反映するが,入力の変化に問題ありかも*/
//20101213    //?for(i=1;i<=AP_ny;i++) AP_z[i+AP_nu]=AP_yy[i]=AP_y-3.0*i;/*エネルギがOSに良く反映するが,入力の変化に問題ありかも*/
//20101213#ifdef MSPC
//20101213    if(ensemble==0){
//20101213      //      if((it>=1)&&(uni_flag==1)&&(nuse_flag==1)){
//20101213      if((uni_flag==1)&&(nuse_flag==1)){//kuro20100125
//20101213	//各ネットでユニットを選択する
//20101213	for(i=1;i<=num_nets;i++){
//20101213	  st_n_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,uni_AP_NC[i]);
//20101213	}  
//20101213	//各ネットで選択されたユニットに対して,さらに観測値との誤差により選択//should check
//20101213	for(i=1;i<=num_nets;i++){
//20101213	  ndy2=0;int Ne=3;
//20101213	  for(k=0;k<Ne;k++){
//20101213	    ndy = -AP_yy[k]+AP_yy[k+1]+net[i].cell[st_n_AP_i[i]].M[0][0]*AP_z[0];
//20101213	    for(j=1;j<=AP_nu;j++) ndy += net[i].cell[st_n_AP_i[i]].M[0][j]*(AP_uu[k+j]-AP_uu[k+j+1]);
//20101213	    for(j=1;j<=AP_ny;j++) ndy += net[i].cell[st_n_AP_i[i]].M[0][j+AP_nu]*(AP_yy[k+j]-AP_yy[k+j+1]);
//20101213	    ndy2+=fabs(ndy);
//20101213	  }
//20101213	  //ndy2/=AP_IS;
//20101213	  n_err[i]=ndy2;
//20101213	  if(i==1||ndy2<AP_n_err){
//20101213	    AP_n_err=ndy2;
//20101213	    AP_n_out=i;
//20101213	  }
//20101213	}
//20101213	AP_i=st_n_AP_i[AP_n_out];	  
//20101213	for(i=0;i<=AP_nu+AP_ny;i++){
//20101213	  net[0].cell[AP_i].M[0][i]=net[AP_n_out].cell[st_n_AP_i[AP_n_out]].M[0][i];	
//20101213	}
//20101213      }
//20101213      else{
//20101213	AP_i=obtain_AP_i(AP_z,AP_y,net,0,AP_NC);//??hajime
//20101213      }
//20101213    }//if(ensemble==0)
//20101213    else{//if(ensemble!=0)
//20101213      bag_i=1;
//20101213      for(i=1;i<=net_num;i++){
//20101213	st_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,bag_i+f_AP_NC-1);
//20101213	if((i%(resample_num*num_boosts))==0) bag_i++;
//20101213      }
//20101213      AP_i=0;//ユニット1のため
//20101213      //***連想行列の平均を取る***
//20101213      for(i=0;i<AP_NN;i++){
//20101213	//ネットの初期化
//20101213	net[0].cell[AP_i].M[0][i]=0;
//20101213	for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){
//20101213	  net[net_num+m].cell[AP_i].M[0][i]=0;
//20101213	}
//20101213	//Mの計算
//20101213	bag_i=1;
//20101213	for(m=1;m<=net_num;m++){//Bagging
//20101213	  net[net_num+bag_i].cell[AP_i].M[0][i]+=net[m].cell[st_AP_i[m]].M[0][i];
//20101213	  if((m%resample_num)==0){
//20101213	    net[net_num+bag_i].cell[AP_i].M[0][i]/=resample_num;
//20101213	    bag_i++;
//20101213	  }
//20101213	}  
//20101213	boost_i=1;	
//20101213	for(m=1;m<=(num_boosts*n_AP_NC);m++){//Boosting
//20101213	  net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].M[0][i]);
//20101213	  if((m%num_boosts)==0){
//20101213	    net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i]/=c_t_sum;
//20101213	    net[0].cell[AP_i].M[0][i] += net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].M[0][i];
//20101213	    boost_i++;
//20101213	  }
//20101213	}	  
//20101213	net[0].cell[AP_i].M[0][i]=net[0].cell[AP_i].M[0][i]/n_AP_NC;		  
//20101213	for(j=0;j<AP_NN;j++){
//20101213	  //ネットの初期化
//20101213	  net[0].cell[AP_i].Q[i][j]=0;
//20101213	  for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){
//20101213	    net[net_num+m].cell[AP_i].Q[i][j]=0;
//20101213	  }	  
//20101213	  //Qの計算
//20101213	  bag_i=1;
//20101213	  for(m=1;m<=(num_boosts*n_AP_NC+n_AP_NC);m++){//Bagging
//20101213	    net[net_num+bag_i].cell[AP_i].Q[i][j]+=net[m].cell[st_AP_i[m]].Q[i][j];
//20101213	    if((m%resample_num)==0){
//20101213	      net[net_num+bag_i].cell[AP_i].Q[i][j]/=resample_num;
//20101213	      bag_i++;
//20101213	    }
//20101213	  }	    
//20101213	  boost_i=1;	
//20101213	  for(m=1;m<=(num_boosts*n_AP_NC);m++){//Boosting
//20101213	    net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].Q[i][j]);
//20101213	    if((m%num_boosts)==0){
//20101213	      net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]/=c_t_sum;
//20101213	      net[0].cell[AP_i].Q[i][j] += net[net_num+(num_boosts*n_AP_NC)+boost_i].cell[AP_i].Q[i][j];
//20101213	      boost_i++;
//20101213	    }
//20101213	  } 	    
//20101213	  net[0].cell[AP_i].Q[i][j]=net[0].cell[AP_i].Q[i][j]/n_AP_NC;
//20101213	}	  
//20101213      }
//20101213      //***平均取り終わり*********
//20101213    }//    else{//if(ensemble!=0)
//20101213    /*net[0].cell[AP_i].v++;/*774s以前に発火したセルの価値を高める*/
//20101213    /*        AP_kk++;/*エネルギ計算のため*/  
//20101213    /*        energy1=-AP_y+net[0].cell[AP_i].M[0][0]*AP_z[0];  */
//20101213    /*        for(i=1;i<=AP_nu;i++) energy1 += net[0].cell[AP_i].M[0][i]*AP_uu[i];  */
//20101213    /*        for(i=1;i<=AP_ny;i++) energy1 += net[0].cell[AP_i].M[0][i+AP_nu]*AP_yy[i];  */
//20101213    /*        energy_sum+=(energy1*energy1);  */
//20101213    /*        energy=energy_sum/AP_kk;/*エネルギEの計算*/ 
//20101213    /*        energy_mean+=energy;/*エネルギの平均の計算*/ 
//20101213    /*energy=energy_sum;/*自乗誤差総和の計算*/
//20101213    AP_yyy=0;
//20101213    //090622 yuno
//20101213    AP_yyy+=net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_yy[1];
//20101213    for(i=1;i<=AP_nu;i++) AP_yyy += net[0].cell[AP_i].M[0][i]*(AP_uu[i]-AP_uu[i+1]);
//20101213    for(i=1;i<=AP_ny;i++) AP_yyy += net[0].cell[AP_i].M[0][i+AP_nu]*(AP_yy[i]-AP_yy[i+1]);
//20101213    SMV=AP_u=predict_search_AP(AP_i);  /*操作量決定*/
//20101213    //#else//#ifdef MSPC
//20101213    //      SMV=AP_u=predict_search_AP(); /*操作量決定*/
//20101213#endif//#ifdef MSPC
#else//#ifdef HEN
    SMV=AP_u=AP_u_max;
#endif//#else of #ifdef HEN
  }//end of else of if (AP_k_hajime<AP_kS1*(AP_NN+AP_IS-1) 
  //  if(time<30) fprintf(stderr,"%d,%g) check AP_u=%g\n",it,time,AP_u);
  if(++AP_k>=AP_kS1) AP_k=0;//?
  /*AP_kk++;/*エネルギ計算のため*/
  //if(AP_y>AP_r+0.5) AP_u=0;/*2000/05/15*/
//#ifdef EMULATE
//  SMV=AP_u=(AP_u_max/200.)*(int)(AP_u/(AP_u_max/200.)+0.5);
//#endif
  /*  モニタ通信用の適応予測制御のSV値の算出			*/
#ifdef MSPC
  AP_SV_M=(WORD)((AP_r));
  //  AP_SV_M=(WORD)((AP_r)*YB);
  //  AP_SV_M=(WORD)((AP_r)*100.);
  //#else//#ifdef MSPC
  //  AP_SV_M=(WORD)((AP_r-AP_y_smooth-AP_y_under-AP_y_under2)*100.);
#endif
  //  return(SMV);
}//calc_AP
//#ifndef MSPC
///*======================================================*/
//void     calc_AP_tau(void)   /* 新しいAT実行後のtauの計算*/
///*======================================================*/
//{
//  /* 99/11/16 by Tako*/
//  FLOAT t100;
//  t100=(AP_AT_j[3]-AP_AT_j[2])*20/(80-50)+AP_AT_j[3];
//  AP_tau=hokan((LONG)(100*(AP_AT_y[4]-AP_AT_y[3])),
//	       (LONG *)&AP_AT_TBL[0][0], AP_AT_TBL_N )+t100;/**/ 
//  if(AP_tau<1000)	/* AP_tauは1000以上とする */
//    AP_tau = 1000;
//  AP_0=1000;
//  AP_RESET_T=(WORD)(_AP_RESET_T*100.+.5);
//  AP_THHS=_AP_THHS;
//  /* モニタ通信用の為、値を設定する */
//  AP_0_M=AP_0;
//  AP_tau_M=AP_tau;/**/
//  /* AT完了フラグをON */
//  AT_END = 1;
//  /* AT完了時、ATF,ATTUのOff*/
//  rst_at();/*E2PROMにストア*/
//  init_AP();/*reinit_AP(); 99/11/24*/
//}
///*======================================================*/
//void     exec_AT_APC(void)          /* 適応予測制御演算*/
///*======================================================*/
//{
//  /*AP_y=0.5*AP_y +0.5*PV1/YB;/*雑音が大きいため平均化 99/10/08S.Kurogi*/
//  AP_y=PV1/YB;/*雑音が大きいため平均化 99/10/08S.Kurogi*/
//  AP_AT_jikan+=AP_tS;
//#ifndef MSPC
//  AP_y_smooth *= AP_y_smooth_r;/**/
//#endif
//#ifdef SPM_REINIT_BY_KASO
//  spm_reinit_AP();
//#endif
//  if(AP_AT_cycle==1){/*最小温度を求める*/
//#ifdef EMULATE
//	if(AP_AT_jikan==AP_tS) AP_AT_kaishijikan=time;
//#endif	
//    SMV=AP_u=AP_u_max;
//    if(AP_y<AP_AT_y[0]) {
//      AP_AT_y[0]=AP_y;
//      AP_AT_j[0]=AP_AT_jikan;/*最小温度の時刻を代入*/
//    }
//    if(AP_y>=AP_AT_y[AP_AT_cycle]){
//      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*10%温度以上に入った時刻を代入*/
//      AP_AT_cycle++;
//    }
//  }
//  else if(AP_AT_cycle==2){
//    SMV=AP_u=AP_u_max;
//    if(AP_y>=AP_AT_y[AP_AT_cycle]){
//      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*50%温度以上に入った時刻を代入*/
//      AP_AT_cycle++;
//    }
//  }
//  else if(AP_AT_cycle==3){
//    SMV=AP_u=AP_u_max;
//    if(AP_y>=AP_AT_y[AP_AT_cycle]){
//      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*80%温度以上に入った時刻を代入*/
//      AP_AT_cycle++;
//    } 
//  }
//  else if(AP_AT_cycle==4){/*80%以上に上昇した温度を求める*/
//    SMV=AP_u=AP_u_min;
//    if(AP_y>AP_AT_y[AP_AT_cycle]) {/*最大温度の時刻を求める*/
//      AP_AT_y[AP_AT_cycle]=AP_y;/*最大温度の時刻を代入*/
//      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*最大温度を代入*/
//    }
//    /*    if(AP_y<=AP_AT_y[2]-10.0){/*SPC*/
//    if(AP_y<=AP_AT_y[3]-1.0){/*SPC*/
//      AP_AT_j[5]=AP_AT_jikan;/*80%温度-1℃の時刻を代入*/
//      AP_AT_y[5]=AP_y;
//#ifndef EMULATE
//      calc_AP_tau();
//#else 
//      /*      ATF.b.AT_APC_F=0;*/
//      calc_AP_tau();
//      AP_AT_cycle=-11;
///*	  ATF.b.AT_APC_F=0;calc_AP_tau();ATF.b.AT_APC_F=1;
///*	  AP_AT_cycle=5;
///*	  AP_AT_Np_opt=AP_Np=1;/*dummy*/
///*	  AP_AT_seiteijikan_saitan=AP_tau;
///**/
//#endif
//    }
//  }
//#ifdef EMULATE
//  else if(AP_AT_cycle==5){/*一旦AP_rの4℃以上に上昇させる*/
//    SMV=AP_u=AP_u_max;
//    if(AP_y>=AP_r-4.){
//      AP_AT_cycle=-10;
//    }
//  }
//  else if(AP_AT_cycle==-10){
//    if(AP_y<=AP_r-5.){/*目標より5℃温度以下に下降させる*/
//      AP_AT_cycle=10;
//      AP_AT_jikan=0;
//      if(AP_Np==1) AP_Np=5;
///*      else if(AP_Np==3) AP_Np=5;*/
//      else if(AP_Np==5) {
//	AP_AT_cycle=-11;/*owari*/
//	AP_AT_shuryojikan=time;
//      }/**/
//#ifdef EMULATE
//#endif
//      ATF.b.AT_APC_F=0;
//      init_AP();
//      ATF.b.AT_APC_F=1;
//      AP_AT_seitei=0;
//      AP_AT_seiteijikan=AP_tau;
//    }
//    else SMV=AP_u=AP_u_min;
//  }
//  else if(AP_AT_cycle==10){
//    if(fabs(AP_r-AP_y)<=AP_KyoyouOndoGosa){
//      if(AP_AT_seiteijikan>=AP_tau){/*許容範囲に入る*/
//	AP_AT_seiteijikan=AP_AT_jikan;
//      }
///*      if(AP_AT_jikan>=AP_AT_seiteijikan+900){/*15分以上で終わり*/
//      if(AP_AT_jikan>=AP_AT_seiteijikan+60000){/*60000秒で終わり*/
//      /*if(AP_AT_jikan>=AP_AT_seiteijikan+0.5*AP_tau){/*以上で終わり*/
//      /*if(AP_AT_jikan>=AP_AT_seiteijikan+AP_tau){/*以上で終わり*/
//	AP_AT_cycle=-10;
//	/*	printf("AP_AT_Np_ok=%d(%f),Now=%f\n",AP_Np,AP_AT_seiteijikan,time);*/
//	if(AP_AT_seiteijikan<AP_AT_seiteijikan_saitan){
//	  AP_AT_seiteijikan_saitan=AP_AT_seiteijikan;
//	  AP_AT_Np_opt=AP_Np;
//#ifdef EMULATE
//	  //hi printf("AP_AT_Np_opt=%d(%f),AP_tau=%d,Now=%f\n",
//		 AP_AT_Np_opt,AP_AT_seiteijikan_saitan,AP_tau,time);/**/
//#endif
//	}
//      }
//    }
//    else if(fabs(AP_r-AP_y)>AP_KyoyouOndoGosa+0.3){/*誤差以上*/
//      if(AP_AT_seiteijikan<AP_tau){/*一旦出ると終わり*/
//#ifdef EMULATE
//	//hi printf("AP_AT_Np_ng=%d(%f),AP_tau=%d,Now=%f\n",AP_Np,AP_AT_seiteijikan,AP_tau,time);/**/
//#endif
//	AP_AT_cycle=-10;
//      }
//    }
//  }
//  if(AP_AT_cycle==-11){
//    SMV=AP_u=AP_u_min;
//  }
//#endif /*#ifdef AT_FOR_NP*/
//}
//#endif//#ifndef MSPC
// 050713 tomisaki
// .net -> 1 .dat -> 2 others -> 0
int hantei(char *h_len)
{
  while(*h_len++){
    if(*h_len=='.'){ 
      if(strcmp(h_len,".net")==0) return 1;
      if(strcmp(h_len,".dat")==0) return 2;
    }
  }
  return 0;
}
void multiply(double x_m[N_matrix][N_matrix],int m_m, int n_m,double y_m[N_matrix][N_matrix],int l_m,double z_m[N_matrix][N_matrix]){
  int i_m,j_m,k_m;
  for(i_m=0;i_m<m_m;i_m++){
    for(j_m=0;j_m<l_m;j_m++){
      z_m[i_m][j_m] = 0.;
      for(k_m=0;k_m<n_m;k_m++){
	z_m[i_m][j_m]+=x_m[i_m][k_m]*y_m[k_m][j_m];
      }
    }
  }
}
void tenti(double x_m[N_matrix][N_matrix],int m_m,int n_m,double y_m[N_matrix][N_matrix]){
  int i_m,j_m;
  for(i_m=0;i_m<n_m;i_m++){
    for(j_m=0;j_m<m_m;j_m++){
      y_m[i_m][j_m]=x_m[j_m][i_m];
    }
  }
}
void inv_matrix(double inv_a[N_matrix][N_matrix],double inv_c[N_matrix][N_matrix]){
int i_m,j_m,k_m;
   for( i_m = 0; i_m < N_matrix; i_m++ ){
        for( j_m = i_m+1; j_m < N_matrix; j_m++ ){
            inv_a[j_m][i_m] /= inv_a[i_m][i_m];
            for( k_m = i_m+1; k_m < N_matrix; k_m++ ){
                inv_a[j_m][k_m] -= inv_a[i_m][k_m] * inv_a[j_m][i_m];
            }
        }
    }
    /* 逆行列を求める */
    for( k_m = 0; k_m < N_matrix; k_m++ ){
        /* 初期化 */
        for( i_m = 0; i_m < N_matrix; i_m++ ){
            if( i_m == k_m ){ inv_c[i_m][k_m] = 1; }
            else{ inv_c[i_m][k_m] = 0; }
        }
        /* 解を求める */
        for( i_m = 0; i_m < N_matrix; i_m++ ){
            for( j_m = i_m+1; j_m < N_matrix; j_m++ ){
                inv_c[j_m][k_m] -= inv_c[i_m][k_m] * inv_a[j_m][i_m];
            }
        }
        for( i_m = N_matrix-1; i_m >= 0; i_m-- ){
            for( j_m = i_m+1; j_m<N_matrix; j_m++ ){
                inv_c[i_m][k_m] -= inv_a[i_m][j_m] * inv_c[j_m][k_m];
            }
            inv_c[i_m][k_m] /= inv_a[i_m][i_m];
        }
    }
    /* 出力 */
    //for( i = 0; i < N_matrix; i++ ){
//   for( j = 0; j < N_matrix; j++ ){
//        printf( "%10lf ", inv_c[i][j] );
//     }
//      putchar( '\n' );
//  }
}
/************************************************************************/
#ifdef EMULATE
//int	main(void)		/*  MAIN 				*/
int	main(int argc, char *argv[])		/*  MAIN 	      	*/
//#else
//void	main(void)		/*  MAIN 				*/
#endif
/************************************************************************/
{
  BYTE	calc_start;
  /* 適応予測制御の演算間隔を500msに変更	99/11/08 T.Arita*/
  BYTE	apc_calc_start;
  char buff[buffsize];
  int hi;//080131yuno
  {
    int i;
    for(i=1;i<argc;i++){
      if(strncmp(argv[i],"it:",3)==0){
	sscanf(&argv[i][3],"%d:%d",&iteration,&_itblock);
      }
      else if(strncmp(argv[i],"LAMBDA:",7)==0){
	sscanf(&argv[i][7],"%lf",&AP_LAMBDA);
	//        fprintf(stdout,"#check param0:lambda=%g=LAMBDA(%g)*N2(%d)/NU(%d),AP_TS1=%g,AP_tS=%g\n",lambda,AP_LAMBDA,AP_N2,AP_NU,AP_TS1,AP_tS);
      }
      else if(strncmp(argv[i],"tS:",3)==0){
	sscanf(&argv[i][3],"%lf",&AP_tS);
      }
      else if(strncmp(argv[i],"RI:",3)==0){
	sscanf(&argv[i][3],"%d:%lf",&randominit,&randominitMag);
      }
      else if(strncmp(argv[i],"listSS:",7)==0){
	listSS=&argv[i][7];
      }
      else if(strncmp(argv[i],"T:",2)==0){
	sscanf(&argv[i][2],"%d",&CAN2_T);
      }
      else if(strncmp(argv[i],"tt:",3)==0){
	sscanf(&argv[i][3],"%lf",&totaltime);
	//	u4it0->totaltime=totaltime;
      }
      else if(strncmp(argv[i],"tr0:",4)==0){
	fntrain0=&argv[i][4];
      }
      else if(strncmp(argv[i],"N2s:",4)==0){
	double AP_N2s=10;
	sscanf(&argv[i][4],"%lf",&AP_N2s);
	AP_N2=AP_N2s/AP_TS1;
      }
      else if(strncmp(argv[i],"r:",2)==0){
	sscanf(&argv[i][2],"%lf",&_AP_r);
      }
      else if(strncmp(argv[i],"cm:",3)==0){
	sscanf(&argv[i][3],"%lf",&_crane_m);
      }
      else if(strncmp(argv[i],"cr:",3)==0){
	sscanf(&argv[i][3],"%lf",&_crane_r);
      }
      else if(strncmp(argv[i],"cdXmax:",7)==0){
	sscanf(&argv[i][7],"%lf",&_crane_dXmax);
      }
      else if(strncmp(argv[i],"cC:",3)==0){
	sscanf(&argv[i][3],"%lf",&_crane_C);
	//	_crane_k=_crane_C;
      }
      else if(strncmp(argv[i],"ck:",3)==0){//spring constant
	sscanf(&argv[i][3],"%lf",&_crane_k);
	//	_crane_C=_crane_k;
      }
//      else if(strncmp(argv[i],"cFmax:",6)==0){
//	sscanf(&argv[i][6],"%lf",&_crane_Fmax);
//      }
      else if(strncmp(argv[i],"ky:",3)==0){
	sscanf(&argv[i][3],"%lf",&_rr_kyoyou);//subst to rr_kyoyou in crane2sub.c 
      }
      else if(strncmp(argv[i],"umax:",5)==0){
	sscanf(&argv[i][5],"%lf:%d",&_AP_umax,&info_xdX);//see crane4sub.c for _AP_umax, emulate_crane.c for xdX
      }
      else if(strncmp(argv[i],"uI:",3)==0){//spring constant
	sscanf(&argv[i][3],"%d:%lf:%d",&u4it0->method,&u4it0->Ru,&u4it0->Tu);
      }
      else if(strncmp(argv[i],"ur:",3)==0){//spring constant
	sscanf(&argv[i][3],"%lf",&u4it0->Ru);
      }
      else if(strncmp(argv[i],"uT:",3)==0){//spring constant
	sscanf(&argv[i][3],"%d",&u4it0->Tu);
      }
//      else if(strncmp(argv[i],"ur:",3)==0){//spring constant
//	sscanf(&argv[i][3],"%lf",&AP_ur0);
//      }
//      else if(strncmp(argv[i],"ur0:",4)==0){//spring constant
//	sscanf(&argv[i][4],"%lf",&AP_ur0);
//      }
//      else if(strncmp(argv[i],"uT:",3)==0){//spring constant
//	sscanf(&argv[i][3],"%lf",&AP_uT0);
//      }
      else if(strncmp(argv[i],"kxt:",4)==0){
	int kxt=0;
	sscanf(&argv[i][4],"%d",&kxt);
	if(kxt){
	  char cmd[256];
	  sprintf(cmd,"ID=`ps aux|grep xterm|sed -e /\"ps aux\"/d -e /grep/d -e /killn/d|awk '{print $2}'`;if [ \"$ID\" != \"\" ];then kill -9 $ID;fi");
	  //	  sprintf(cmd,"kill -9 `ps aux|grep xterm|sed -e /\"ps aux\"/d -e /grep/d -e /killn/d|awk '{print $2}'`");
	  fprintf(stderr,"#apc_crane.c:L3548 Executing '%s'.\n",cmd);
	  system(cmd);
	  //	  system("kill -9 `ps aux|grep xterm|sed -e /\"ps aux\"/d -e /grep/d -e /killn/d|awk '{print $2}'`");
	}
      }
      else if(strncmp(argv[i],"DISP:",5)==0){
	sscanf(&argv[i][5],"%d",&DISP);
      }
      else if(strncmp(argv[i],"stab:",5)==0){
        sscanf(&argv[i][5],"%d:%d:%d:%lf",&stab1,&stab2,&stab3,&stab4);
      }
      else if(strncmp(argv[i],"N:",2)==0){
	if(num_tems<1){
	  fprintf(stderr,"#Set N:.. just after setting method:..\n");
	  exit (-1);
	}
	char *p0=&argv[i][2];
	char *p=p0;
	int n;
	for(n=1;;n++){//for(n=0;n<num_tems;){
	  for(;;p++) if(*p==':'|| *p==0) break;
	  sscanf(p0,"%d",&AP_NC[n]);
	  if(*p==0) break;
	  else p0=++p;
	}
	AP_NC[0]=AP_NC[1];
	for(n=1;n<=num_tems;n++) if(AP_NC[0]<AP_NC[n]) AP_NC[0]=AP_NC[n];
	fprintf(stderr,"Nmax=%d:",AP_NC[0]);
	for(n=1;n<=num_tems;n++) fprintf(stderr,"N[%d]=%d,",n,AP_NC[n]);
	fprintf(stderr,"\n");
      }
      else if(strncmp(argv[i],"method:",7)==0){
	sscanf(&argv[i][7],"%d",&method);
	char *p=&argv[i][7];
	int nc=1;
	if(method==1){//single CAN2
	  for(;;) if(*(p++)==':') {nc++;break;}
	  sscanf(p,"%d",&AP_NC[0]);
	  //	  fprintf(stdout,"N=%d ",N);
	  ensemble=0;num_nets=0;
	  uni_flag=nuse_flag=0;//??default?
	}
	else if(method==2){//switching CAN2
	  uni_flag=nuse_flag=1; //unify1 and select1
	  for(;;) if(*p++==':') {nc++;break;}
	  sscanf(p,"%d",&AP_NC[0]);
	  for(;;) if(*p++==':') {nc++;break;}
	  char *p0=p;
	  int n;
	  for(n=0;;){
	    for(;;p++) if(*p==':'|| *p==0) break;
	    if(*p==0) {
	      sscanf(p0,"%s",net_n[++n]);
	      uni_AP_NC[n]=AP_NC[0];
	      num_nets=n;//number of CAN2s
	      //	      fprintf(stderr,"check num_nets=%d\n",num_nets);
	      break;
	    }
	    *p=0;
	    sscanf(p0,"%s",net_n[++n]);
	    uni_AP_NC[n]=AP_NC[0];
	    nc++;
	    p0=++p;
	  }
	}
	else if(method==11){//bagging CAN2
	  for(;;) if(*(p++)==':') break;
	  sscanf(p,"%d:%d:%lf:%d",&AP_NC[0],&num_bags,&bag_alpha,&bag_seed);//rsa:$a:$bs:$b
	  bagging_flag201204=1;
	  ensemble=1;//??void for bagging_flag201204=1
	  uni_flag=nuse_flag=1;//? unify and select for num_nets>=2 ??void for bagging_flag201204=1
	  boosting_flag=0;//??void for bagging_flag201204=1
	  num_tems=0;//tem[0] is for current ensembel machine involving bagging nets;
	  tem=(TEM*)malloc(sizeof(TEM)*(num_tems+1));
	  //tems>=1 for trained ensemble machines
	  //	  num_nets=(num_tems+1)*num_bags;
	  num_nets=(num_tems+1)*(num_bags+1);	    //	    num_nets=(num_tems+1)*num_bags;
//	  n_AP_NC=?;
//	  resample_num=;
//	  num_boosts=1;
//	  net_num=;
//	  //net_num=num_boosts*resample_num*n_AP_NC;
//	  num_nets=;//number of CAN2s
	}
	else if(method==12){//bagging CAN2,num_tems>0
	  bagging_flag201204=1;
	  for(;;) if(*p++==':') {break;}
	  //	  sscanf(p,"%d:%d",&AP_NC,&num_bags);
	  sscanf(p,"%d:%d:%lf:%d",&AP_NC[0],&num_bags,&bag_alpha,&bag_seed);//rsa:$a:$bs:$b
	  for(;;) if(*p++==':'){break;}
	  for(;;) if(*p++==':'){break;}
	  for(;;) if(*p++==':'){break;}
	  for(;;) if(*p++==':'||*p==0){break;}
	  if(*p==0){
	    num_tems=0;
	    tem=(TEM*)malloc(sizeof(TEM)*(num_tems+1));
	    num_nets=(num_tems+1)*(num_bags+1);	    //	    num_nets=(num_tems+1)*num_bags;
	  }
	  else{
	    char *p0=p; 
	    for(num_tems=0;;){
	      for(;;) if(*p++==':'|| *p==0) {break;}
	      num_tems++;
	      if(*p==0) break;
	    }
	    tem=(TEM*)malloc(sizeof(TEM)*(num_tems+1));
	    num_nets=(num_tems+1)*(num_bags+1);	    //	    num_nets=(num_tems+1)*num_bags;
	    int n=1;tem[n++].dname=p=p0;
	    for(;;){
	      for(;;p++) if(*p==':'|| *p==0) break;
	      if(*p==0) break;
	      else{
		*p=0;
		tem[n++].dname=++p;
	      }
	    }
	  }
	  ensemble=1;//??void for bagging_flag201204=1
	  uni_flag=nuse_flag=1;//?void unify and select for num_nets>=2 ??void for bagging_flag201204=1
	  boosting_flag=0;//??void for bagging_flag201204=1
	}//	else if(method==12){//bagging CAN2,num_tems>0
      }//      else if(strncmp(argv[i],"method:",7)==0){
      else if(strncmp(argv[i],"M00:",4)==0){
	int j=0;
	char *p=&argv[i][3];
	for(;;){
	  if(*p==0) break;
	  if(*p==':'){
	    sscanf(++p,"%lf",&M00[j++]);
	  }
	  p++;
	}
      }
    }//    for(i=1;i<argc;i++){
  }
  int tomisaki=0;//?
  if(tomisaki){
    int i_main;
    if(argc>1){//050713 tomisaki
      add_data_N=0;
      for(i_main = 1; i_main < argc; i_main++){
	if(hantei(argv[i_main])==1) net0=argv[i_main];
	if(hantei(argv[i_main])==2){
	  add_dat[add_data_N]=i_main;
	  add_data_N++;
	}
      }
      dat_file = argv;
      if(net0)printf("%s\n",net0);
      for(i_main = 0; i_main <add_data_N; i_main++){
	printf("%s\n",*(dat_file+add_dat[i_main]));
      }
    }
  }//if(tomisaki)
  // 050704 tomisaki
  //  system("cp /dev/null train.dat");
  //ens:ensemble(0):AP_NC
  //ens:ensemble(1):bagging_flag:boosting_flag:f_AP_NC:e_AP_NC
  //ens:ensemble(1):bagging_flag(1):boosting_flag(?):f_AP_NC:e_AP_NC:resample_num:bag_alph
  //ens:ensemble(1):bagging_flag(?):boosting_flag(1):num_boosts
  //num_nets(1):net_f
  //num_nets(>1):uni_flag(1):nuse_flag
  //num_nets(>1):net_n[i]
  //nni_flag(1):uuse_flag(0)->uni_AP_NC[]
  stable_time=0;
  obtain_new=1;//select_by_w
  u_limit=0;
  matrix_0=0;
  //  gakusyu=0;
  penalty=3;  
  if(method==0){//original Question&Answer sequence.
    printf("************ CAN2 for MSPC ***************\n");
    //printf("Use ensemble learning(y/n), iteration(>0):");//2005/11/9
    //fgets(buff,buffsize,stdin);sscanf(buff,"%s %d",yesno,&_iteration);
    printf("Use ensemble learning(y/n):");//2005/11/9
    fgets(buff,buffsize,stdin);sscanf(buff,"%s",yesno);
    //  fprintf(stdout,"#######buff=%s,",buff);
    ensemble=(yesno[0]=='y'||yesno[0]=='1')?1:0;
    //  fprintf(stdout,"ensemble=%d,_iteration=%d,DISP=%d\n",ensemble,_iteration,DISP);
    if(ensemble==1){
      printf("Use bagging learning (y/n)?");//2005/11/9
      fgets(buff,buffsize,stdin);sscanf(buff,"%s",yesno);
      bagging_flag=(yesno[0]=='y'||yesno[0]=='1')?1:0;
      //    scanf("%d",&bagging_flag);
      printf("Use boosting learning(y/n)?");//2005/11/9
      fgets(buff,buffsize,stdin);sscanf(buff,"%s",yesno);
      boosting_flag=(yesno[0]=='y'||yesno[0]=='1')?1:0;
      //    scanf("%d",&boosting_flag);
    }
    if(ensemble==0){
      printf("The number of cell:");
      fgets(buff,buffsize,stdin);sscanf(buff,"%d",&AP_NC[0]);
      //    scanf("%d",&AP_NC);
      if(AP_NC[0]<1) AP_NC[0] = 1;
    }
    else{//ensemble==1
      printf("ID number of the first cell:");
      fgets(buff,buffsize,stdin);sscanf(buff,"%d",&f_AP_NC);
      //    scanf("%d",&f_AP_NC);
      if(f_AP_NC<1) f_AP_NC = 1;
      
      printf("ID number of the last cell:");/*kuwa060223*/
      fgets(buff,buffsize,stdin);sscanf(buff,"%d",&e_AP_NC);
      //    scanf("%d",&e_AP_NC);
      if(f_AP_NC>e_AP_NC){
	ensemble=0;
	AP_NC[0]=f_AP_NC;
      }
      n_AP_NC=e_AP_NC-f_AP_NC+1; /*kuwa060223 アンサンブルの数n_AP_NC<100*/
      AP_NC[0]=f_AP_NC;   
      if(bagging_flag==1){
	printf("The number of the resampling datasets:");//resample_num=bagging_b?
	fgets(buff,buffsize,stdin);sscanf(buff,"%d",&resample_num);
	//scanf("%d",&resample_num);
	if(resample_num<1) resample_num = 1;     
	printf("The alpha:");/*kuwa061023*/
	fgets(buff,buffsize,stdin);sscanf(buff,"%lf",&bag_alpha);
	//scanf("%f",&bag_alpha);
	if(bag_alpha<=0 || bag_alpha>1){
	  bag_alpha=1;
	}
      }
      if(boosting_flag==1){
	printf("The number of boosting times (less than 100):");
	fgets(buff,buffsize,stdin);sscanf(buff,"%d",&num_boosts);
	//scanf("%d",&num_boosts);
	if(num_boosts<1) num_boosts = 1;
      }
    }
    net_num=num_boosts*resample_num*n_AP_NC;
    //yuno071203
    printf("Number of netfiles:");
    fgets(buff,buffsize,stdin);sscanf(buff,"%d",&num_nets);
    //  scanf("%d",&num_nets);//number of netfiles?kuro
    if(num_nets==1){
      printf("The name of the netfile(****.net):");
      fgets(buff,buffsize,stdin);sscanf(buff,"%s",net_n[1]);//
      //fgets(buff,buffsize,stdin);sscanf(buff,"%s",net_f);//??
      //scanf("%s",&net_f);
    }
    //090622 yuno
    //080311koshi
    else if(num_nets>=2){
      printf("Unify the netfiles(y/n)?");//what does unify mean?
      fgets(buff,buffsize,stdin);sscanf(buff,"%s",yesno);
      uni_flag=(yesno[0]=='y'||yesno[0]=='1')?1:0;
      //    fgets(buff,buffsize,stdin);sscanf(buff,"%d",&uni_flag);
      //scanf("%d",&uni_flag);
      //  }
      if(uni_flag==1){
	printf("Merge(0) or Select(1) the netfiles?");//nuse_flag=0 is not used
	fgets(buff,buffsize,stdin);sscanf(buff,"%d",&nuse_flag);
	//scanf("%d",&nuse_flag);
      }
      //  if(num_nets>=2){
      //    printf("Enter the name of the netfiles(****.net)");
      for(hi=1;hi<=num_nets;hi++){
	printf("The name of the net#%d:",hi);
	fgets(buff,buffsize,stdin);sscanf(buff,"%s",net_n[hi]);//
	//fgets(buff,buffsize,stdin);sscanf(buff,"%s",&net_n[hi]);//?
	//    scanf("%s",&net_n[hi]);
      }
      //080318 koshi
      if((uni_flag==1)&&(nuse_flag==0)){//nets with different N, unify1 and mearge0?
	AP_NC[0]=0;
	for(uni=1;uni<=num_nets;uni++){
	  printf("Number of the cells of the %dth netfile\n",uni);
	  fgets(buff,buffsize,stdin);sscanf(buff,"%d",&uni_AP_NC[uni]);
	  //scanf("%d",&uni_AP_NC[uni]);
	  AP_NC[0]+=uni_AP_NC[uni];
	}
	//	AP_NC=cell_num;
	if(AP_NC[0]<1) AP_NC[0]=1;
      }
      else{//nets with the same N
	for(uni=1;uni<=num_nets;uni++){
	  uni_AP_NC[uni]=AP_NC[0];
	}
      }
    }
  }//endof if(method==0)
  ////////////////////////////////////////////////////////////
  int num_nets1=num_nets+1;//L3593 num_nets=(num_tems+1)*num_bags;
  net=(NET*)malloc(sizeof(NET)*num_nets1);
  err=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);
  energy_sum_n=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);//void for bagging_flag201204
  energy_n1=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);//void for bagging_flag201204
  energy_n=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);//void for bagging_flag201204
  energy_mean_n=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);//void for bagging_flag201204
  mse=(FLOAT**)malloc(sizeof(FLOAT*)*num_nets1);
  //  uni_AP_NC=(int*)malloc(sizeof(int)*num_nets1);
  SMV_n=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);//void for bagging_flag201204
  AP_yn=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);//void for bagging_flag201204
  AP_z=(FLOAT*)malloc(sizeof(FLOAT)*(AP_NN+2));
  AP_d=(FLOAT*)malloc(sizeof(FLOAT)*(AP_NN));
  AP_du=(FLOAT*)malloc(sizeof(FLOAT)*(AP_NN));
  AP_dy=(FLOAT*)malloc(sizeof(FLOAT)*(AP_NN));
  n_err=(FLOAT*)malloc(sizeof(FLOAT)*num_nets1);
  int i;
  if(bagging_flag201204==1) for(i=0;i<=num_tems;i++) tem[i].se=(FLOAT*)malloc(sizeof(FLOAT)*Ne);
  for(i=0;i<=num_nets;i++){
//    if(i>=18){//check memory allocation
//      double *dum=(double*)malloc(sizeof(double)*10000);
//      fprintf(stderr,"#memory-check dum=%p i%d listSS=%p\n",dum,i,listSS);
//      free(dum);
//    }
    net[i].cell=(CELL*)malloc(sizeof(CELL)*AP_NC[0]);
    mse[i]=(FLOAT*)malloc(sizeof(FLOAT)*Ne);//void for bagging_flag201204
    energy_sum_n[i]=energy_n1[i]=energy_n[i]=energy_mean_n[i]=0;//void for bagging_flag201204
    //    energy_sum_n[i]=energy_n1[i]=energy_n[i]=energy_mean_n[i]=uni_AP_NC[i]=0;//void for bagging_flag201204
    int j;
    for(j=0;j<AP_NC[0];j++){
      net[i].cell[j].w=(FLOAT*)malloc(sizeof(FLOAT)*(AP_nu+AP_ny));
      net[i].cell[j]._M=(FLOAT*)malloc(sizeof(FLOAT)*AP_NN);
      net[i].cell[j].M=(FLOAT**)malloc(sizeof(FLOAT*)*1);
      net[i].cell[j].M[0]=&(net[i].cell[j]._M[0]);
      net[i].cell[j]._Q=(FLOAT*)malloc(sizeof(FLOAT)*AP_NN*AP_NN);
      net[i].cell[j].Q=(FLOAT**)malloc(sizeof(FLOAT*)*AP_NN);
      net[i].cell[j].v=0;
      //      fprintf(stderr,"sizeofw=%d,sizeofFLOAT=%d\n",sizeof(net[i].cell[j].w),sizeof(FLOAT));
      //      fprintf(stderr,"sizeofQ=%d/%d,%d,AP_NN=%d\n",sizeof(net[i].cell[j]._Q),sizeof(FLOAT),sizeof(net[i].cell[j].Q),AP_NN);
      int k;
      for(k=0;k<AP_NN;k++){
	net[i].cell[j].Q[k]=&(net[i].cell[j]._Q[k*AP_NN]);
	//net[i].cell[j].Q[k]=(FLOAT*)malloc(sizeof(FLOAT)*AP_NN);
      }
      //int k;for(k=0;k<AP_NN;k++) net[i].cell[j].Q[k]=(FLOAT*)malloc(sizeof(FLOAT)*AP_NN);
    }
  }
  if(bagging_flag201204){
    for(i=0;i<=num_tems;i++){
      tem[i].net=&(net[i*(num_bags+1)]);//tem[i].net[0] for copy from tem[i].net[j](j=1,2...)
      //tem[i].net=&(net[i*num_bags]);
      //      int j;for(j=0;j<num_bags;j++) tem[i].net[j].n_cells=AP_NC;
    }
  }
  int max_size_st_AP_i=(num_boosts+1)*(resample_num+1)*n_AP_NC+1;//?
  st_AP_i=(int*)malloc(sizeof(int)*max_size_st_AP_i);
  for(i=0;i<max_size_st_AP_i;i++) st_AP_i[i]=0;
  AP_n_kk=0;
  //  int iii; for(iii=0;iii<=n_AP_NC;iii++) st_AP_i[iii]=0;/*st_AP_i[]の初期化*/
  //090622 yuno
  st_n_AP_i=(int*)malloc(sizeof(int)*(num_nets1));
  for(i=0;i<=num_nets;i++) st_n_AP_i[i]=0;//st_n_AP_i[]の初期化
  //  boosting_c_t=(double*)malloc((num_boosts*n_AP_NC+1)*sizeof(double));//?
  boosting_c_t=(double*)malloc(sizeof(double)*max_size_st_AP_i);//?
  for(i=0;i<max_size_st_AP_i;i++) boosting_c_t[i]=1; //netの重み初期化
  c_t_sum=num_boosts;   
  //  printf("f_AP_NC=%d,e_AP_NC=%d,n_AP_NC=%d,AP_NC=%d,ensemble=%d,resample_num=%d,bag_alpha=%f,num_boosts=%d,net_num=%d\n",f_AP_NC,e_AP_NC,n_AP_NC,AP_NC,ensemble,resample_num,bag_alpha,num_boosts,net_num);/*060322kuwa*/ 
  net->firstcall=1;
  //if(argc>1) net0=argv[1];//050621 modified by kuro
  init_AP();/* 適応制御初期化:初めにこれが呼ばれるべし*/
  if(net0){
    net_load(net,net0,0,AP_NC[0]);//050621 modified by kuro
    sprintf(buff,"cp %s can2b.net\n",net0);
    system(buff);  
    net->firstcall=1;
  }
//  else {//kuro20100125
//    //    it=1;
//    int i;
//    for(i=1;i<=num_nets;i++){
//      net_load(net,net_n[i],hi,uni_AP_NC[i]);
//    }
//    net->firstcall=1;
//  }
  while(1){
#ifdef EMULATE
    /*C_MODE=5;/*オートチューニングによるパラメタ計算のための制御*/
    /*C_MODE=4;/*マニュアルまたはオートチューニングによるパラメタによる制御*/
    /*C_MODE=3;/*自己発熱有りの自動設定*/
    /*C_MODE=2;/*自己発熱無しの自動設定*/
    outer_world(); /*********/
#endif /*#ifdef EMULATE*/
    /*------------------------------------------------------*/
    C_WDT = 0;			/*  ウォッチドックタイマカウンタクリア	*/
    /*------------------------------------------------------*/
    if( MODE_TYPE !=  STD_MODE ){	continue;	}
    /*------------------------------------------------------*/
    chk_ad_data();			/*  ADデータの正規化	*/
    /*------------------------------------------------------*/
    ad_hokan();			        /*  ADデータの補間	*/
    /*------------------------------------------------------*/
    chk_at_calc();			/*  AT 計算タイミングチェック	*/
    /*------------------------------------------------------*/
    if(!RUN){			        /*　制御状態チェック	*/
      MV = 0;			        /*  操作量 reset	*/
      MV_N = 0;
      SMV = 0.0;
      reinit_AP();     /* 適応制御最初期化:行列は初期化しない*/
      rst_pid();
      continue;
      /*------------------------------------------------------*/
    }else{
      if(CHG.b.SV){	/* CHANGE SET TEMP */
	rst_ctrl();   
	set_AP_r(); /* 適応制御の目標温度が変わったとき99/06/25*/
      }
      /*------------------------------------------------------*/
      /* A-Rom制御の追加				99/07/29 T.Arita*/
      /*    if(C_250MS == 0){*/
      calc_start=OFF;
      if(C_MODE==NORM_PID){	/* PID制御(従来)のみカウンタを使用 */
        if(C_250MS==0)
          calc_start=ON;
      }else{
        if(GET_PV_DATA){
          GET_PV_DATA = OFF;
	  calc_start=ON;
        }
      }
      if(calc_start){
	/* 適応予測制御の組込				99/07/29 T.Arita*/
	/* 適応予測のATは、適応予測制御を行いながら、オーバーシュート量で	*/
	/* ATを行う							*/
	/*	if(!ATF.b.AT_RUN_F){		/*PID制御モード*/
	if(ATF.b.AT_APC_F || !ATF.b.AT_RUN_F){	/* PID制御モードor適応予測制御のAT実施中*/
	  /* 適応予測制御の組込				99/07/29 T.Arita*/
	  /* 適応予測によるOn/Off制御は、削除する			*/
	  /* 制御モードの見直し						*/
	  /*	  if(PP != 0){*/
	  /*	    /* 適応予測制御の追加                       99/05/17 S.Kurogi*/
	  /*	    /* スーパー2自由度PID制御の追加		99/03/17 T.Arita*/
	  /*	    /*						calc_pid();*/
	  /*	    switch(C_MODE){
		    /*	    case 7:                     /* 適応予測制御 */
	  /*	    case 6:                     /* 適応予測制御 */
	  /*	    case 5:                     /* 適応予測制御 */
	  /*	    case 4:                     /* 適応予測制御 */
	  /*	    case 3:                     /* 適応予測制御 */
	  /*	    case 2:                     /* 適応予測制御 */
	  /*	      calc_AP();*/
	  /*	      break;*/
	  /*	    case 1:			/* スーパー2自由度PID制御 */
	  /*	      calc_s2dof_pid();*/
	  /*	      break;*/
	  /*	    case 0:*/
	  /*	    default:		       /* 従来のPID制御 */
	  /*	      calc_pid();*/
	  /*	      break;*/
	  /*	    }*/
	  /*	  }*/
	  /*	  else{			/*ON/OFF制御モード*/
	  /*	    switch(C_MODE){*/
	  /*	    case 2:*/
	  /*	      AP_u_res=1;  /*適応によるON/OFF制御*/
	  /*	      calc_AP();*/
	  /*	      break;*/
	  /*	    default:	/* 従来のPID制御 */
	  /*	      calc_onoff();*/
	  /*	      rst_pid();*/
	  /*	    }*/
	  /*	  }*/
	  switch(C_MODE){
#ifdef EMULATE
	  case AT_APC:               /* 適応予測制御 */
#endif
	  case DEF_APC:               /* 適応予測制御 */
	  case SPM_APC:               /* 適応予測制御 */
	  case SC2_APC:               /* 適応予測制御 */
	    calc_AP();
	    break;
	    /* ATモードを廃止し、ATFフラグを使用する	99/11/12 T.Arita*/
	    /* 新しいAT機能を使用する					*/
	    /*	    case AT_APC:               /* 適応予測制御 */
	    /*	      exec_AT_APC();
		      /*	      break;*/
	  case AROM_PID:	       /* A-Rom制御 */
	  case NORM_PID:	       /* 従来のPID制御 */
	  default:
	    if(PP != 0)
	      calc_pid();
	    else{			/*ON/OFF制御モード*/
	      calc_onoff();
	      rst_pid();
	    }
	    break;
	  }
	  MV_N = (UBYTE)SMV;
	}
      } 
    }
  }
}

