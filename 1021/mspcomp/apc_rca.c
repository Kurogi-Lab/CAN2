/********************************************************
multiple models
次の4つの定義文のうち，ひとつだけコメントをはずして使用すること．
gcc -E -DEMULATE emulate.c >emulate.cccとするとプリプロセッサ結果
********************************************************/
/*#define GPC2/**/
/*#define APC2/**/
/*#define APC1/**/
/*#define GPC1/**/
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
int AP_KyoyouOndoGosa; /*許容温度誤差：外乱復帰高速化99/11/22 S.Kurogi*/
FLOAT AP_HoseiKaisiOndo; /* 定常偏差補正開始温度99/11/22 S.Kurogi*/
#ifdef EMULATE
#define AP_TS1 27/**/
GLOBAL	WORD AP_N2=11; /* 予測ステップ数:1/bit */
//GLOBAL	WORD AP_NU;		/* ???:1/bit */
//GLOBAL	double AP_LAMBDA=0.1;//NG
GLOBAL	double AP_LAMBDA=200; /* ???:1/bit */
#else
#define AP_LAMBDA 150
#endif
#define AP_NP AP_N2       /*Npが大だとハンチングを抑える*/
#define AP_Np AP_N2       /*Npが大だとハンチングを抑える*/
//#define AP_NU AP_N2      /*Nuが小かつNpが大だと自己発熱がでる*/
int AP_NU=1;      /*Nuが小かつNpが大だと自己発熱がでる*/

#ifdef APC1
#define AP_NN3
#define AP_nu 2
#define AP_ny 1
#define APC
#endif

#ifdef APC2
#define AP_NN4
#define AP_nu 2
#define AP_ny 2
#define APC
#endif

#ifdef GPC1
#define AP_NN3
#define AP_nu 2
#define AP_ny 1
#define GPC
#endif

#ifdef GPC2
#define AP_NN4
#define AP_nu 2
#define AP_ny 2
#define GPC
#endif

#ifdef MSPC
//#define AP_nu 4//071207yuno
//#define AP_ny 4/*2007/02/18/koshi*/ //071207yuno
#define AP_nu 3 //071207yuno
#define AP_ny 3 /*2007/02/18/koshi*/ //071207yuno
#undef SPM_REINIT_BY_KASO
#endif

#define AP_NN (AP_nu+AP_ny+1) /**/
/*MSPC********************************************************/
// replace define AP_NC to emulate.c for cross-validation 
int AP_NC=1; /*Number Of Cells*/
#define theta_e 0.1 /*Error Limit 水の即応性には0.4以下*/
#define theta_v 100
#define AP_IS 2 /*同定ステップ数*/
int it;
char *net0;//050621 modified by kuro
char net_1[100]; //071203yuno .netファイルのファイル名を保存する配列 
char net_2[100]; //071203yuno .netファイルのファイル名を保存する配列
char net_n[20][100];//080129yuno .netファイルのファイル名を保存する配列
char *net_f=&net_n[0][0];
//char net_f[100]; /*060224kuwa .netファイルのファイル名を保存する配列*/
int rise_time,stable_time=0;//050704 tomisaki
#define file_data_N 100
int add_data_N=0; /*tomisaki*/
double result_data[file_data_N];
int result_it[file_data_N];
int add_dat[5]={0,0,0,0,0};//tomisaki argv[i] に入っている.datファイルのiの番号
char **dat_file;
//modified tomisaki 2005/11/9
GLOBAL int st_AP_i[100];//tomisaki 複数のCAN2を用いたときにAP_iを格納
GLOBAL int ensemble=0;//アンサンブル学習を使うのか?
//GLOBAL int useensrs=1;//ensrsを使うのか?
GLOBAL int useensrs=1;//ensrsを使うのか?
GLOBAL int f_AP_NC=1;
GLOBAL int e_AP_NC=1; //kuwa060223 
GLOBAL int n_AP_NC=1; //kuwa060224 アンサンブルユニットの数
//modified tomisaki 2005/11/31
int obtain_new=0;//sellect unit by weight vector
int matrix_0=0;//Matrix initial value = 0
int num_nets=0;
int u_limit=0;
double error_hyouka=0;
double y_pre[100];
double y_pre[100];
double F_err[100];
double y_pre1;
double u_old;
double u_old1;
int penalty=0;
int code;
int gakusyu=0;

/*bagboostの導入に用いた変数 2006kuwa*/
GLOBAL int bagging_flag=0;
GLOBAL float bag_alpha=1;
GLOBAL int resample_num=1;
GLOBAL int boosting_flag=0;
GLOBAL int boosting_times=1;
GLOBAL double boosting_c_t[100],c_t_sum;
int net_num;

//090622 yuno
/*080311koshi ネットの統合に用いた変数*/
GLOBAL int ave_flag=0;
GLOBAL int uni_flag=0;
GLOBAL int uni=0;
GLOBAL int cell_num=0;
GLOBAL int uni_AP_NC[10]={0,0,0,0,0,0,0,0,0,0};

//081010koshi 変数
GLOBAL int nuse_flag=0;
GLOBAL int st_n_AP_i[100];// 複数のCAN2を用いたときにAP_iを格納
GLOBAL int AP_n_out=0;//081013 koshi 
GLOBAL FLOAT n_err[100];
GLOBAL FLOAT ndy=0;
GLOBAL FLOAT ndy2=0;
GLOBAL FLOAT AP_n_err=0;

GLOBAL int   AP_n_kk;/*制御開始からの時刻カウンタ,エネルギ計算のため*/
GLOBAL FLOAT energy_sum_n[10]={0,0,0,0,0,0,0,0,0,0}; /*自乗誤差の合計*/
GLOBAL FLOAT energy_n1[10]={0,0,0,0,0,0,0,0,0,0}; /*1ステップ分の自乗誤差*/
GLOBAL FLOAT energy_n[10]={0,0,0,0,0,0,0,0,0,0}; /*エネルギ*/
GLOBAL FLOAT energy_mean_n[10]={0,0,0,0,0,0,0,0,0,0}; /*エネルギの平均*/
GLOBAL FLOAT mse[10][32000];

#define save_time 180//mseの保存時間

GLOBAL FLOAT SMV_nn;
GLOBAL FLOAT SMV_n[10];
GLOBAL int p_net=0;
GLOBAL FLOAT p_nerr,perr;
GLOBAL FLOAT p_err[10];
GLOBAL int flag=1;
GLOBAL FLOAT AP_yyn;
GLOBAL FLOAT AP_yn[10];

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

extern void bpmpd(int *, int *, int *, int *, int *, int *, int *,
       double *, int *, int *, double *, double *, double *, double *,
       double *, double *, double *, int *, double *, int *, double *, int *);

/*********************************************************/
void init_MQ_AP(void);          /* 行列の初期化    */
/*void AM_AP(FLOAT *,FLOAT);    /* 最小２乗記憶法  */
/*FLOAT predict_search_AP(void); /* 予測入力探索    */
void set_AP_r(void);            /* 目標温度が変わったとき !!! 99/06/25*/
void reinit_AP(void);           /* 適応制御変数の再初期化 */
void init_AP(void);             /* 適応制御変数の初期化*/
void calc_AP(void);             /* 適応予測制御演算 */

#ifndef MSPC
void calc_AP_tau(void);          /* 新しいAT実行後のtauの計算*/
void exec_AT_APC(void);          /* 新しいATの実行モード*/
#endif

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
//double AP_r=(SV/YB);         /*=SV/100.;SV:水などの場合可変:制御用目標値:0.01℃/bit*/
#define AP_r (SV/YB)         /*=SV/100.;SV:水などの場合可変:制御用目標値:0.01℃/bit*/
/*********************************************************/
/*新AT用*/

#ifndef MSPC
FLOAT AP_AT_y[7];
FLOAT AP_AT_j[6];
int AP_AT_cycle;
FLOAT AP_AT_jikan;
FLOAT AP_AT_seitei;
FLOAT AP_AT_seiteijikan;
FLOAT AP_AT_seiteijikan_saitan;
int AP_AT_Np_opt;
FLOAT      AP_Q[AP_NN][AP_NN];
FLOAT      AP_M[1][AP_NN];
#endif

/*MSPC********************************************************/
#ifdef MSPC
typedef struct {
  int v;/*価値（発火回数、アクセス頻度）*/
  FLOAT Q[AP_NN][AP_NN];
  FLOAT M[1][AP_NN];
  FLOAT w[AP_nu+AP_ny];
} CELL;
typedef struct {
  CELL cell[100];//配列の中身はAP_NC_MAX(50)だった
  int firstcall;
} NET;
NET net[500];//modify tomisaki 2005/11/9
int AP_i=0;
int AP_i1=0;//081022yuno学習後の連想行列を平均化するときにAP_iを格納
int AP_i2=0;
int net_yu =AP_nu+AP_ny,yu,l;//yuno081022
#endif
/*********************************************************/
FLOAT AP_y;             /*=PV1/100.; PV1 入力：センサ温度 PV1温度 0.01℃/bit*/
FLOAT AP_u;               /* 操作量 0-200    */
FLOAT AP_u_max;           /* 操作量上限:200 */
FLOAT AP_u_min;           /* 操作量下限:0   */
/*************************************************************/
#define AP_TO 25.  /*  外部温度（仮想でよい）*/
#define AP_tS 0.25 /*サンプリング周期(秒)*/
#define Gensui(tau) (1.-4.*AP_tS/(tau)) /*理想はGensui(tau)=exp(-4*AP_tS/tau);/**/
#ifndef MSPC
FLOAT      AP_u_res;/*入力解像度;大きいと早い．振れは大きい．*/
#endif
FLOAT      AP_y_k;
FLOAT      AP_y_k_minus_1;
FLOAT      AP_u_k;
FLOAT      AP_u_k_minus_1;
FLOAT      AP_z[AP_NN+2];/*2007/02/18/koshi*/
FLOAT      AP_overshoot;/*OverShoot*/
//090622 yuno
/*****************080508 koshi 一次差分信号を保存するため************/
FLOAT      AP_d[AP_NN];
FLOAT      AP_du[AP_NN]; 
FLOAT      AP_dy[AP_NN];
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
#ifndef EMULATE
/* 適応予測制御の機能追加			99/11/08 T.Arita*/
/* 機能追加分の変数をAPC.cで参照すると				*/
/* TOO MANY EXTERNAL IDENTIFIERSエラーとなる為、			*/
/* APC.cで使用するインクルードファイルを別ファイルにする			*/
/*#include "CS.H"  */
#define	APC_KELK
#include "CS_APC.H"
extern LONG hokan(LONG,LONG *,WORD);
#endif
#ifndef MSPC
#define AP_AT_TBL_N 11
const	LONG	AP_AT_TBL[2][AP_AT_TBL_N] = {
   121, 223, 276, 319, 333, 351, 369, 390, 409, 726, 1420,/*487, 520, 1270,*/
  -796,-272,-147,   0,  53, 125, 199, 215,1242,1796, 2234/*814, 802, 1060*/
}; /**/
#endif
#ifdef AP_NN3
/*********************************************************/
void init_MQ_AP(void)                 /* 行列の初期化    */
/*********************************************************/
{
  AP_M[0][0]=+1.019383e-02;
  AP_M[0][1]=+9.295959e-03;
  AP_M[0][2]=+9.939551e-01;
  AP_Q[0][0]=+1.000000e+04;
  AP_Q[0][1]=-1.197140e-09;
  AP_Q[0][2]=-6.794222e-09;
  AP_Q[1][0]=-1.197140e-09;
  AP_Q[1][1]=+8.400848e-10;
  AP_Q[1][2]=-6.164823e-10;
  AP_Q[2][0]=-6.794222e-09;
  AP_Q[2][1]=-6.163944e-10;
  AP_Q[2][2]=+6.748715e-10;
}
#endif
#ifdef AP_NN4
/*********************************************************/
void init_MQ_AP(void)                 /* 行列の初期化    */
/*********************************************************/
{
  AP_M[0][0]=-4.500449e-02;
  AP_M[0][1]=+2.173344e-02;
  AP_M[0][2]=+9.913619e-01;
  AP_M[0][3]=+2.480479e-03;
  AP_Q[0][0]=+9.999940e+03;
  AP_Q[0][1]=-1.758429e-04;
  AP_Q[0][2]=-8.640277e-04;
  AP_Q[0][3]=+5.228297e-06;
  AP_Q[1][0]=-1.758429e-04;
  AP_Q[1][1]=+1.017217e-07;
  AP_Q[1][2]=-2.661719e-07;
  AP_Q[1][3]=+2.308460e-07;
  AP_Q[2][0]=-8.640277e-04;
  AP_Q[2][1]=-2.661719e-07;
  AP_Q[2][2]=+1.096935e-05;
  AP_Q[2][3]=-1.088859e-05;
  AP_Q[3][0]=+5.228297e-06;
  AP_Q[3][1]=+2.308451e-07;
  AP_Q[3][2]=-1.088859e-05;
  AP_Q[3][3]=+1.082415e-05;
}
#endif

#ifdef MSPC
int net_load(NET *net,char *fname,int a_n,int units){
  int i, k, l;
  FILE *fp;
  char buff[128];
  FLOAT dummy;
  int idummy,net_k;
  double ddummy;

  if(fname==NULL){
    printf("Name of the Net File:");
    buff[0]=0;scanf("%s",buff);
    if(buff[0]==0) return(0);
    if((fp = fopen(buff, "r"))==NULL) return(1);
  }
  else{
    if((fp = fopen(fname, "r"))==NULL) return(1);
  }
  
  net_k=AP_nu+AP_ny;
  fread(&(idummy),sizeof(int),1,fp);//net->n_cells
  fread(&(idummy),sizeof(int),1,fp);//net->winit  
  fread(&(idummy),sizeof(int),1,fp);//GlobalTime
  fread(&(idummy),sizeof(int),1,fp);//ReinitTime
  //2006/2/2 tomisaki
  fread(&(idummy),sizeof(int),1,fp);//net->k
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
    for(k=0; k<net_k; k++) fread(&(net[a_n].cell[i].w[k]),sizeof(FLOAT),1,fp);
    for(k=1; k<=net_k; k++) fread(&(net[a_n].cell[i].M[0][k]),sizeof(FLOAT),1,fp);
    k=0;fread(&(net[a_n].cell[i].M[0][k]),sizeof(FLOAT),1,fp);

    for(k=1; k<=net_k; k++){
      for(l=1; l<=net_k; l++)fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
      l=0; fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
    }
    k=0;
    for(l=1; l<=net_k; l++) fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
    l=0; fread(&(net[a_n].cell[i].Q[k][l]),sizeof(FLOAT),1,fp);
    fread(&(net[a_n].cell[i].v),sizeof(FLOAT),1,fp);
    fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].S
    fread(&(dummy),sizeof(FLOAT),1,fp);//net->cell[i].E
  }
  for(i=0;i<units;i++){
    printf("\nM[%d]=",i);
    for(k=0; k<=net_k; k++) printf("%f ",net[a_n].cell[i].M[0][k]);
  }
  fclose(fp);
  return(1);
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
    else{
	//2005/11/9 tomisaki
	if(n>=0){//初めはこの設定
	  for(i=0;i<AP_NN;i++){
	    net[a_n].cell[n].M[0][i]=0;
	    net[a_n].cell[n].v=0;
	    for(j=0;j<AP_NN;j++){
	      if(i==j) net[a_n].cell[n].Q[i][j]=1e0;
	      else  net[a_n].cell[n].Q[i][j]=0;
	    }
	  }
	  //070130kuwa unit1でdeltaを用いたときの値 
	  net[a_n].cell[n].M[0][0]=-3.0433671e-03;
	  net[a_n].cell[n].M[0][1]=3.4363725e-03;
	  net[a_n].cell[n].M[0][2]=3.8970019e-03;
	  net[a_n].cell[n].M[0][3]=8.8743849e-04;  
	  net[a_n].cell[n].M[0][4]=1.6971479e+00;
	  net[a_n].cell[n].M[0][5]=-7.7143775e-01;
	  net[a_n].cell[n].M[0][6]=9.0087558e-02;  
	}
#ifdef delta_cell_10_200_120
      }
#endif
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
      for(i=0;i<AP_NC;i++){
	init_MQ_APi(i,0,0);
      }
  }
  else{//2005/11/10 tomisaki
    init_MQ_APi(0,0,0);//net[a_n]にMの平均を格納する。
    for(j=1;j<=net_num;j++){//アンサンブル学習に必要なネットの用意
      for(i=0;i<AP_NC;i++){
	init_MQ_APi(i,0,j);
      }
    }
  }
}
FLOAT err[100];//配列の中身はAP_NC
FLOAT init_err=0;
/***********************************************************************/
int obtain_AP_i(FLOAT *x,FLOAT y,NET *net, int a_n, int u_n)/*AP_iを１ステップだけで計算 cを求める計算*/
/***********************************************************************/
{//modify tomisaki 2005/11/9
  int i,j,k,AP_out,flag_ob=0;
  FLOAT dy,dy2,AP_err;

  if(obtain_new==0){
    for(i=0;i<u_n;i++){
      if(it==0 || net[a_n].cell[i].w[0]!=0. || net[a_n].cell[i].w[1]!=0. || net[a_n].cell[i].w[2]!=0.)
	{
	  dy2=0;
	  for(k=0;k<AP_IS;k++){
	    dy = -AP_yy[k]+net[a_n].cell[i].M[0][0]*AP_z[0];
	    for(j=1;j<=AP_nu;j++) dy += net[a_n].cell[i].M[0][j]*AP_uu[k+j];
	    for(j=1;j<=AP_ny;j++) dy += net[a_n].cell[i].M[0][j+AP_nu]*AP_yy[k+j];
	    dy2+=fabs(dy);
	  }
	  dy2/=AP_IS;
	  err[i]=dy2;
	  if(i==0||dy2<AP_err){
	    AP_err=dy2;
	    AP_out=i;
	  }
	}
    }/**/
    
    return(AP_out);
  }
  else{/*2007/02/18/koshi*/
    for(i=0;i<u_n;i++){
      if(it==0 || net[a_n].cell[i].w[0]!=0. || net[a_n].cell[i].w[1]!=0. || net[a_n].cell[i].w[2]!=0. || net[a_n].cell[i].w[3]!=0. || net[a_n].cell[i].w[4]!=0. || net[a_n].cell[i].w[5]!=0.)
	{
	  dy=0;
	  for(j=0;j<(AP_nu+AP_ny);j++){
	    if(j<AP_nu) dy+=pow((AP_z[j+1]-AP_z[j+2])-net[a_n].cell[i].w[j] , 2);
	    if(j>=AP_nu) dy+=pow((AP_z[j+2]-AP_z[j+3])-net[a_n].cell[i].w[j] , 2);
	  }
	  err[i]=dy;
	  if(i==0 || dy<AP_err){
	    AP_err=dy;
	    AP_out=i;
	  }
	}
    }
    return(AP_out);
  }
}
#define AP_hoji 1.0
/*======================================================*/
void AM_AP(FLOAT x[],FLOAT y,int APi,NET *net) /*  最小２乗法  */
/*======================================================*/
/*	入力ベクトル x[4]                               */
/*	出力値       y                                  */
/*======================================================*/
{
  int i,j,k;
  FLOAT hth=0,gtx1;
  FLOAT h[AP_NN],g[AP_NN],p[AP_NN];
  FLOAT yhat;

  for(i=0;i<AP_NN;i++) 
    for(g[i]=0,j=0;j<AP_NN;j++) g[i] += net[0].cell[APi].Q[i][j]*x[j];
  for(gtx1=AP_hoji,i=0;i<AP_NN;i++) gtx1 += g[i]*x[i];
  for(i=0;i<AP_NN;i++) p[i] = g[i]/gtx1;/**/
  for(i=0;i<AP_NN;i++){
    for(j=0;j<AP_NN;j++){
      net[0].cell[APi].Q[i][j] = (net[0].cell[APi].Q[i][j] - g[i]*p[j])/AP_hoji;
    }
  }
  for(yhat=0,i=0;i<AP_NN;i++) yhat += net[0].cell[APi].M[0][i]*x[i];
  for(i=0;i<AP_NN;i++) net[0].cell[APi].M[0][i] += (y-yhat)*p[i];/**/
}
int s00=0,s01;
FLOAT ste_allerr=0;
FLOAT tra_allerr=0;
FLOAT mid_allerr=0;
FLOAT allerr=0;
int n_of_saishokika=0;
/*********************************************************/
void store_vector_AP(FLOAT *AP_z,FLOAT AP_y,NET *net)  /*traindate testdataを作成*/
/*********************************************************/
{
  int k,nn;
  int i,j,iii,vsum,vave,nmax=0,modified=-1;
  FLOAT yi; 
  FLOAT temp;
  FLOAT errmin=0;
  int *s,ss[100];//配列の中身はAP_NCだった
  FLOAT *z;

  /*2007/02/18/koshi*/
  for(i=1;i<=AP_nu;i++) fprintf(fptrain,"%e ",AP_z[i]-AP_z[i+1]); 
  for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptrain,"%e ",AP_z[i]-AP_z[i+1]);
  fprintf(fptrain,"%e %f\n",AP_y-AP_z[AP_nu+2],time);
  if(((long int)(time/AP_tS))%8==0){//2秒おき ??necessary?
    for(i=1;i<=AP_nu;i++) fprintf(fptest,"%e ",AP_z[i]-AP_z[i+1]);
    for(i=AP_nu+2;i<=AP_NN;i++) fprintf(fptest,"%e ",AP_z[i]-AP_z[i+1]);
    fprintf(fptest,"%e %f\n",AP_y-AP_z[AP_nu+2],time);
  }
  return;
  
  nmax=AP_NC;

  for(i=0;i<AP_NC;i++) ss[i]=i;
  for(i=0;i<AP_NC;i++){
    for(j=i;j<AP_NC;j++){
      if(err[(int)ss[i]]>err[(int)ss[j]]){
	temp=(int)ss[i];
	ss[i]=ss[j];
	ss[j]=temp;
      }
    }
  }
  errmin=err[(int)ss[0]];
  if(AP_r-AP_y>0 && mid_allerr==0) tra_allerr+=errmin;
  else mid_allerr+=errmin;
  allerr+=errmin;
  s01=s00;
  s00=ss[0];
  if(errmin>theta_e) {
    if(net[0].cell[s00].v<=theta_v){
      net[0].cell[s00].v++;
      AM_AP(AP_z,AP_y,s00,net);
      modified=s00;
#ifdef EMULATE
      if(debug==10){
      }
#endif
    }
    else {/*if(net[0].cell[s00].v>theta_v){*/
      int minvalcell=0;
      int n_of_memorized_cells=0;
      FLOAT meanvalue=0;
      if(AP_NC>1 && s00==0) minvalcell=1;
      for(i=0;i<AP_NC;i++){
	if(net[0].cell[i].v<net[0].cell[minvalcell].v && i!=s00) minvalcell=i;
	if(net[0].cell[i].v>0) {
	  meanvalue+=net[0].cell[i].v;
	  n_of_memorized_cells++;
	}
      }
      if(n_of_memorized_cells!=0) meanvalue/= n_of_memorized_cells;
       if (errmin>theta_e){
      }
      if(minvalcell!=s00) {
	CELL *c0,*c1;
#ifdef EMULATE

#endif
	c0=&net[0].cell[s00];
	c1=&net[0].cell[minvalcell];
	c1->v=c0->v=theta_v/2.;/*OS=0.91(NC=10),OS=1.8(NC=5)*/
	for(i=0;i<AP_NN;i++){
	  c1->M[0][i]=c0->M[0][i];
	  for(j=0;j<AP_NN;j++){
	    c1->Q[i][j]=c0->Q[i][j];
	  }
	}
	n_of_saishokika++;
      }
      AM_AP(AP_z,AP_y,minvalcell,net);
      modified=minvalcell;
    }
  }
  else{/*err=<theta_eのとき*/
    net[0].cell[s00].v++;
    AM_AP(AP_z,AP_y,s00,net);/**/
    modified=s00;
#ifdef EMULATE
    if(debug==10){
      printf("sv3:cell_i=%d,err=%f<%f,v=%f\n",modified,errmin,theta_e,net[0].cell[s00].v);/**/
      printf("AP_z=%e,%e,%e,%e,y=%e\n",AP_y,AP_z[0],AP_z[1],AP_z[2],AP_z[3],AP_y);
      printf("   M=%e,%e,%e,%e\n",
	     net[0].cell[s00].M[0][0],
	     net[0].cell[s00].M[0][1],
	     net[0].cell[s00].M[0][2],
	     net[0].cell[s00].M[0][3]);
    }
#endif
  }/**/
  if(net[0].cell[modified].M[0][1]<0){
    init_MQ_APi(modified,1,0);/**/
#ifdef EMULATE
#endif
  }/**/
}	
#endif
#ifndef MSPC
#define AP_hoji 1.0
/*======================================================*/
void AM_AP(x,y)                         /*  最小２乗法  */
/*======================================================*/
/*	入力ベクトル x[AP_NN]                               */
/*	出力値       y                                  */
/*======================================================*/
FLOAT x[],y;
{
  int i,j,k;
  FLOAT hth=0,gtx1;
  FLOAT h[AP_NN],g[AP_NN],p[AP_NN];
  FLOAT yhat;

  for(i=0;i<AP_NN;i++) for(g[i]=0,j=0;j<AP_NN;j++) g[i] += AP_Q[i][j]*x[j];
  for(gtx1=AP_hoji,i=0;i<AP_NN;i++) gtx1 += g[i]*x[i];
  for(i=0;i<AP_NN;i++) p[i] = g[i]/gtx1;/**/
  for(i=0;i<AP_NN;i++){
    for(j=0;j<AP_NN;j++){
      AP_Q[i][j] = (AP_Q[i][j] - g[i]*p[j])/AP_hoji;
    }
  }
  for(yhat=0,i=0;i<AP_NN;i++) yhat += AP_M[0][i]*x[i];
  yhat=AP_M[0][0]*x[0]+AP_M[0][1]*x[1]+AP_M[0][2]*x[2]+AP_M[0][3]*x[3];
  for(i=0;i<AP_NN;i++) AP_M[0][i] += (y-yhat)*p[i];/**/
}
#endif
#ifdef APC
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
#endif

/***********************MSPC******************************/
#ifdef MSPC
FLOAT *g_buf,*p_buf,*P_buf,*r_buf,*z_buf,*Pr_buf,*rP_buf;
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
#define lambda (AP_N2*(AP_LAMBDA)*1.0e-5/AP_NU)/**/
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
  int    m_2, n_2, nz_2, qn_2, qnz_2, acolcnt[maxn+1], acolidx[maxnz], qcolcnt[maxn+1], qcolidx[maxqnz],
    status[maxn+maxm],  memsiz;
  double acolnzs[maxnz], qcolnzs[maxqnz], rhs[maxm], obj[maxn], lbound[maxn+maxm],
    ubound[maxn+maxm], primal[maxn+maxm], dual[maxn+maxm], big, opt;
  //090622 yuno
  int cons_qp=0; //080519koshi 場合分けのための定数
  /*2007/02/16/koshi*/
  b=(FLOAT *)&(net[0].cell[m].M[0][1]);/*b[0..k_u-1]*/
  a=(FLOAT *)&(net[0].cell[m].M[0][AP_nu+1]);/*a[0..k_y-1]*/
  c=net[0].cell[m].M[0][0];//net[0].cell[m].M[0][0]*AP_z[0];//AP_z[0]=1;
  //c=0; for the CAN2 with BIAS:0
  double g_buf[AP_N2];
  double p_buf[AP_N2];
  double P_buf[AP_NU*AP_NU];
  double r_buf[AP_NU];
  double z_buf[AP_NU];
  double Pr_buf[AP_NU];
  double rP_buf[AP_NU];
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
#endif //#ifdef BPMPD
    //printf("primal:%f code:%d dual %f\n",primal[0],code,dual[0]);
    //if(code == 3 )umin=AP_z[1]+dual[0];
    //else umin=AP_z[1]+primal[0];
    umin = AP_z[1]+primal[0];
    //printf("mcode %d %f %f %f %f %f\n",code,primal[0],primal[1],primal[2],primal[3],primal[4]);
    if(code != 2) umin = 0.;
  }
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
  else if(penalty==2){
    /*step 1: ステップ応答を求める*/
#define GPC_KURO
#ifdef GPC_KURO /*GPCの原著ではΔuに対するステップ応答*/
    for(j=0;j<AP_N2;j++){
      g(j)=0;
      for(i=0;i<AP_nu;i++) if(i<=j) g(j)+=b[i];
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#else /*インパルス応答*/
    for(j=0;j<AP_N2;j++){
      if(j<AP_nu) g(j)=b[j];
      else g(j)=0;
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#endif
    /*step 2*//*pの計算*/
    /**/
    for(j=0;j<AP_N2;j++){
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
    if(check){//check100123
      for(i=0;i<AP_ny;i++) a[i]=0;
      for(i=0;i<AP_nu;i++) b[i]=0;
      a[0]=0.9;
      b[0]=1;
      for(i=0;i<=AP_ny+2;i++) AP_yy[i]=0;
      for(i=0;i<=AP_nu+2;i++) AP_uu[i]=0;
      AP_yy[0]=0;
      //      AP_r=10;
      AP_LAMBDA=1;
    }
#define GPC_STEP 1
#define GPC_IMPULSE 2
#define GPC_g GPC_IMPULSE //一次差分ではインパルス応答
#if GPC_g == GPC_STEP/*GPCの原著ではΔu=1に対するステップ応答*/
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
#undef original
#define original
#ifndef original
    //Matrix inverse using SVD 
    double GGI[AP_NU*AP_NU];
#define GGI(i,j) GGI[(i)*AP_NU+(j)]
#define G(i,j) ((i<j)?0:g(i-j))
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

#else 
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
    for(umin=AP_uu[1],i=0;i<AP_NU;i++) umin+=P(0,i)*z(i);
    if(check){//check100123
      fprintf(stderr,"\nAP_y=%g,u[0]=%g,u[-1]=%g,lambda=%g\n",AP_yy[0],AP_uu[0],AP_uu[1],lambda);
      fprintf(stderr,"\ndp:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",dp[i]);
      fprintf(stderr,"\n p:");for(i=0;i<AP_N2;i++) fprintf(stderr,"%g,",p(i));
      fprintf(stderr,"\n p:");
      for(j=0;j<AP_NU;j++){
	fprintf(stderr,"\n p(j%d,*):",j);
	for(i=0;i<AP_NU;i++){
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
  if(it==0&&matrix_0==1){
    umin=AP_u_max*0.10;
  }
  if(time<160) umin=AP_u_max; 
  return(umin);
}//endof predict_search_AP(int m)

/*********************************************************/
FLOAT predict_search_AP1(int m)
/*********************************************************/
{
  int i,j,k,l;
  FLOAT umin;
  FLOAT *a,*b,c;
  FLOAT rPr_plus_1;
  //tomisaki
  double G[N_matrix][N_matrix];
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
  int    m_2, n_2, nz_2, qn_2, qnz_2, acolcnt[maxn+1], acolidx[maxnz], qcolcnt[maxn+1], qcolidx[maxqnz],
    status[maxn+maxm],  memsiz;
  double acolnzs[maxnz], qcolnzs[maxqnz], rhs[maxm], obj[maxn], lbound[maxn+maxm],
    ubound[maxn+maxm], primal[maxn+maxm], dual[maxn+maxm], big, opt;
  //090622 yuno
  int cons_qp=0; //080519koshi 場合分けのための定数
  double g_buf[AP_N2];
  double p_buf[AP_N2];
  double P_buf[AP_NU*AP_NU];
  double r_buf[AP_NU];
  double z_buf[AP_NU];
  double Pr_buf[AP_NU];
  double rP_buf[AP_NU];
  /*2007/02/16/koshi*/
  c=net[0].cell[m].M[0][0]*AP_z[0];
  b=(FLOAT *)&(net[0].cell[m].M[0][1]);/*b[0..k_u-1]*/
  a=(FLOAT *)&(net[0].cell[m].M[0][AP_nu+1]);/*a[0..k_y-1]*/
  
  //penalty = 0;
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
      else if(i<2*N_matrix){//uの範囲 0<u<pmax
	ubound[i]=AP_u_max;
	lbound[i]=0;
	rhs[i-N_matrix]=-AP_z[1];
      }
      else{//yの範囲 r-2<y<r+2-y_0
	ubound[i]=0;
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
#endif //#ifdef BPMPD
    //printf("primal:%f code:%d dual %f\n",primal[0],code,dual[0]);
    //if(code == 3 )umin=AP_z[1]+dual[0];
    //else umin=AP_z[1]+primal[0];
    umin = AP_z[1]+primal[0];
    //printf("mcode %d %f %f %f %f %f\n",code,primal[0],primal[1],primal[2],primal[3],primal[4]);
    if(code != 2) umin = 0.;
  }
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
  else if(penalty==2){
    
    /*step 1: ステップ応答を求める*/
#ifdef GPC_KURO/*GPCの原著ではΔuに対するステップ応答*/
    for(j=0;j<AP_N2;j++){
      g(j)=0;
      for(i=0;i<AP_nu;i++) if(i<=j) g(j)+=b[i];
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#else /*インパルス応答*/
    for(j=0;j<AP_N2;j++){
      if(j<AP_nu) g(j)=b[j];
      else g(j)=0;
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#endif
    /*step 2*//*pの計算*/
    /**/
    for(j=0;j<AP_N2;j++){
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
  }

  else{/*2006/12/26/koshi*///penalty==3
    /*step 1: ステップ応答を求める*/
    //#define GPC_KURO ////2010.01.19 by kuro
#ifdef GPC_KURO/*GPCの原著ではΔuに対するステップ応答*/
    for(j=0;j<AP_N2;j++){
      g(j)=0;
      for(i=0;i<AP_nu;i++) if(i<=j) g(j)+=b[i];
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#else /*インパルス応答*/
    for(j=0;j<AP_N2;j++){
      if(j<AP_nu) g(j)=b[j];
      else g(j)=0;
      for(i=0;i<AP_ny;i++) if(i<j) g(j)+=a[i]*g(j-i-1);
    }
#endif
    /*step 2: u(t+i)=u(t-1)とした応答pの計算;*/
    /**/
    for(j=0;j<AP_N2;j++){
      p(j)=c;
      //#define useoriginal //2010.01.19 by kuro
#ifdef useoriginal      //compensated by kuro because some one omit below from can2b050205.tgz
      for(i=0;i<AP_nu;i++){
	if(j<i) p(j)+=b[i]*AP_uu[(i-j+1)];
	else p(j)+=b[i]*AP_uu[1];
      }
#endif
      for(i=0;i<AP_ny;i++){
#ifdef nouseoriginal
	if(j<=i) p(j)+=a[i]*(AP_yy[(i-j)]);//original use this!!
#else
	if(j<=i) p(j)+=a[i]*(AP_yy[(i-j+1)]-AP_yy[(i-j+2)]);//not this even if 1st order difference
	//	if(j<=i) p(j)+=a[i]*(AP_yy[(i-j)]-AP_yy[(i-j+1)]);//not this even if 1st order difference
#endif
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
      if(j>0) p(j) += p(j-1);
      for(i=0;i<AP_NU;i++){/**/
#ifdef MSPC
	z(i) += r(i)*(AP_r-(AP_yy[0]+p(j)));/**/
#else
	z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-AP_y_under2-p(j));/**/
#endif
	for(k=0;k<AP_NU;k++){
	  P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
	}
      }
    }//for(j=0;j<AP_N2;j++)   
    for(umin=AP_z[1],j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
  }
  if(u_limit==0){
    if(umin>AP_u_max) umin=AP_u_max;
    else if(umin<AP_u_min) umin=AP_u_min;
  }
  if(it==0&&matrix_0==1){
    umin=AP_u_max*0.10;
  }
  if(time<160) umin=AP_u_max; 
  return(umin);
}////endof predict_search_AP(int m)
#endif
/******************EndOfMSPC******************/
#ifdef GPC
/* mallocが使用できない為、固定にする	99/11/09 S.Kurogi*/
FLOAT *g_buf,*p_buf,*P_buf,*r_buf,*z_buf,*Pr_buf,*rP_buf;
/* mallocが使用できない為、バッファに変更	99/11/08 T.Arita*/
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
#define lambda (AP_N2*5e-3/AP_NU)
#endif
#ifdef GPC1
/*********************************************************/
FLOAT predict_search_AP()
/**********************************************************/
{
  int i,j,k,l;
  FLOAT umin;
  FLOAT c;
  FLOAT rPr_plus_1;
/****/
  c=AP_M[0][0]*AP_z[0];
  g(0)=AP_M[0][1];
  if(AP_NP>1) g(1)=AP_M[0][2]*g(0);
  for(j=2;j<AP_N2;j++){
    g(j)=AP_M[0][2]*g(j-1)+AP_M[0][3]*g(j-2);
  }/**/
  /*step 2*/
  for(j=0;j<AP_N2;j++){/*pの計算*/
    if(j==0) p(0)=AP_M[0][2]*AP_y+AP_M[0][1]*AP_z[1]+c;
    else if(j>=1) p(j)=AP_M[0][2]*p(j-1)+AP_M[0][1]*AP_z[1]+c;
  }
  for(i=0;i<AP_NU;i++){
    z(i)=0;
    for(j=0;j<AP_NU;j++){
      if(i==j) P(i,j)=1./lambda;/**/
      else P(i,j)=0;
    }
  }
  /*step 3*/
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
      z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-AP_y_under_2-p(j));/**/
#endif
      for(k=0;k<AP_NU;k++){
	P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
      }
    }
  }
  for(umin=0,j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
  if(umin>AP_u_max) umin=AP_u_max;
  else if(umin<AP_u_min) umin=AP_u_min;
  return(umin);
}
#endif

#ifdef GPC2
/*********************************************************/
FLOAT predict_search_AP()
/*********************************************************/
{
  int i,j,k,l;
  FLOAT umin;
  FLOAT c;
  FLOAT rPr_plus_1;
/****/
  c=AP_M[0][0]*AP_z[0];
  g(0)=AP_M[0][1];
  if(AP_NP>1) g(1)=AP_M[0][2]*g(0);
  for(j=2;j<AP_N2;j++){
    g(j)=AP_M[0][2]*g(j-1)+AP_M[0][3]*g(j-2);
  }/**/
  /*step 2*/
  for(j=0;j<AP_N2;j++){/*pの計算*/
    if(j==0) p(0)=AP_M[0][2]*AP_y+AP_M[0][3]*AP_z[2]+AP_M[0][1]*AP_z[1]+c;
    else if(j==1) p(1)=AP_M[0][2]*p(0)+AP_M[0][3]*AP_y+AP_M[0][1]*AP_z[1]+c;
    else if(j>=2) p(j)=AP_M[0][2]*p(j-1)+AP_M[0][3]*p(j-2)+AP_M[0][1]*AP_z[1]+c;
  }
  for(i=0;i<AP_NU;i++){
    z(i)=0;
    for(j=0;j<AP_NU;j++){
      if(i==j) P(i,j)=1./lambda;/**/
      else P(i,j)=0;
    }
  }
  /*step 3*/
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
      z(i) += r(i)*(AP_r-AP_y_smooth-AP_y_under-p(j));/**/
#else
      z(i) += r(i)*(AP_r-p(j));/**/
#endif
      for(k=0;k<AP_NU;k++){
	P(i,k) -= Pr(i)*rP(k)/rPr_plus_1;
      }
    }
  }
  for(umin=AP_z[1],j=0;j<AP_NU;j++) umin+=P(0,j)*z(j);
  if(umin>AP_u_max) umin=AP_u_max;
  else if(umin<AP_u_min) umin=AP_u_min;
  /*printf("umin=%f\n",umin); /**/
  return(umin);
}
#endif
#define BWF
#undef BWF
#ifdef BWF /*バタワースフィルタ*/
FLOAT AP_y0,AP_y1,AP_y2,AP_yy1;
/*BWF#3ダメ,4.000000 [Hz],
パスバンド周波数 : 0.005000 [Hz]
ストップバンド周波数 : 0.010000 [Hz]
パスバンド端減衰量 : 3.000000 [dB]
ストップバンド端減衰量 : 10.000000 [dB]
#define BWF_k   2.48613807057856018e-01
#define BWF_b1 -1.98887971173257294e+00
#define BWF_b2  9.88941201193123343e-01
#define BWF_a0  6.18323065783157942e-05
#define BWF_a1  1.23664613156631588e-04
#define BWF_a2  6.18323065783157942e-05
/**/
/*BWF#1サンプリング周波数 : 20.000000 [Hz]
パスバンド周波数 : 1.500000 [Hz]
ストップバンド周波数 : 3.000000 [Hz]
パスバンド端減衰量 : 3.000000 [dB]
ストップバンド端減衰量 : 10.000000 [dB]
#define BWF_k  1.78865175977607815e-01
#define BWF_b1 -1.34825016312690305e+00
#define BWF_b2 5.13592652514821890e-01
#define BWF_a0 2.31099330101878137e-01
#define BWF_a1 4.62198660203756273e-01
#define BWF_a2 2.31099330101878137e-01
/**/
/*BWF#2フィルタの次数 : 2
セクション数 : 1
種類 : LPF
サンプリング周波数 : 4.000000 [Hz]
パスバンド周波数 : 0.050000 [Hz]
ストップバンド周波数 : 0.100000 [Hz]
パスバンド端減衰量 : 3.000000 [dB]
ストップバンド端減衰量 : 10.000000 [dB]*/

/* コンパイラの制限により有効桁数を17桁にする	99/11/12 T.Arita*/
/*#define BWF_k   2.36478626953582627e-01
/*#define BWF_b1 -1.88890163277109613e+00
/*#define BWF_b2  8.94756398486225901e-01
/*#define BWF_a0  6.18952946250698934e-03
/*#define BWF_a1  1.23790589250139787e-02
/*#define BWF_a2  6.18952946250698934e-03*/
#define BWF_k   2.3647862695358263e-01
#define BWF_b1 -1.8889016327710961e+00
#define BWF_b2  8.9475639848622590e-01
#define BWF_a0  6.1895294625069893e-03
#define BWF_a1  1.2379058925013979e-02
#define BWF_a2  6.1895294625069893e-03
/**/
#endif
/*======================================================*/
void set_AP_r(void) /* 目標温度の設定，変更のとき99/06/25*/
/*======================================================*/
{
  FLOAT tmp;
  CHG.b.SV = 0;
  AP_y=PV1/YB;
#ifndef MSPC
#ifdef BWF
  AP_y0=AP_y1=AP_y2=AP_y;/*BWF*/
#endif
  if(ATF.b.AT_APC_F){ 
    /* ATモードを廃止し、ATFフラグを使用する	99/11/08 T.Arita*/
    /* 新しいAT機能を使用する					*/
#ifndef MSPC
    AP_AT_y[0]=AP_y;
    AP_AT_y[1]=AP_y+0.10*(AP_r-AP_y);
    AP_AT_y[2]=AP_y+0.50*(AP_r-AP_y);
    AP_AT_y[3]=AP_y+0.80*(AP_r-AP_y);
    AP_AT_j[0]=0;/*requested by Mimata ???*/
    AP_AT_y[6]=AP_y+0.90*(AP_r-AP_y);
    AP_AT_cycle=1;
    AP_AT_jikan=0;
    AP_y_smooth_tau=1000.;
    AP_y_smooth=(AP_r-AP_y);
    AP_y_smooth_r=Gensui(AP_y_smooth_tau);/**/
#endif
  }
  else{
    if(AP_tau==0 && AP_0==0 && AP_RESET_T==0 && AP_THHS==0){/* 自動設定モード */
      /*if(AP_tau==0 && AP_0==0 && AP_RESET_T==0){/* 自動設定モード */
      if(C_MODE==DEF_APC){/* 自己発熱がない（水，リン酸など）場合のモード */
        tmp = 0.8;
#ifndef MSPC
        AP_y_smooth=(AP_r-AP_y)*tmp;/**/
        AP_y_smooth_tau=1000.;
#endif
        _AP_RESET_T=0.;
      }
      else if(C_MODE==SPM_APC){/*自己発熱がある（硫酸過水）の場合の自動設定モード*/
	tmp = 1.0;/**/
#ifndef MSPC
        AP_y_smooth=(AP_r-AP_y)*tmp;
        AP_y_smooth_tau=AP_approx(AP_r,2300.,135.,1000.,110.);/*apc-spm990711a.cs*/
#endif
#ifndef MSPC
#ifdef EMULATE
	/*AP_y_smooth_tau = 1158;/**/
	AP_y_smooth_tau = 100;/**/
#endif
#ifdef APC1
        AP_y_smooth_tau *= AP_approx(AP_Np,1.3,4.,1.,2.);
#endif
#ifdef APC2
/*        AP_y_smooth_tau *= AP_approx(AP_Np,1.1,4.,1.,2.);/**/
        AP_y_smooth_tau *= AP_approx(AP_Np,1.2,4.,1.,2.);
#endif
#ifdef GPC
        /*AP_y_smooth_tau *= AP_approx(AP_Np,1.05,4.,1.,2.);*/
#endif
#endif
      }
      else if(C_MODE==SC2_APC){/*自己発熱がある（塩酸過水）の場合の自動設定モード*/
        tmp = 1.0;
#ifndef MSPC
        AP_y_smooth=(AP_r-AP_y)*tmp;
        /* 塩酸過水の自動設定モードでのAP_y_smooth_tauの補間値変更 */
        AP_y_smooth_tau=AP_approx(AP_r,1800.,80.,1000.,50.);
        /*_AP_RESET_T=0.;/*コメントアウト by 99/11/12/ Kurogi*/
#endif
      }
      /* 自動設定モードでのAP_y_smooth_tauのリミッタ追加 */
      /*if(AP_y_smooth_tau<1000.)	AP_y_smooth_tau=1000.;/* AP_y_smooth_tauは1000以上とする */
      /*if(AP_y_smooth_tau<500.)	AP_y_smooth_tau=500.;/* AP_y_smooth_tauは1000以上とする */
      _AP_THHS=100;/*99/11/24*/
      _AP_RESET_T=0;/*by 99/11/12/ Kurogi*/
      /* 自動設定モードでの設定値表示の為、値を設定する */
      AP_0_D=(WORD)(tmp*1000.+.5);
#ifndef MSPC
      AP_tau_D=(WORD)(AP_y_smooth_tau+.5);/**/
#endif
      AP_RESET_T_D=(WORD)(_AP_RESET_T*100.+.5);
      AP_THHS_D=_AP_THHS;/*？？有田さんチェックお願い99/11/22*/
    }
    else{/* マニュアルモード */
#ifndef  MSPC
      tmp = (FLOAT)AP_0/1000.;
      AP_y_smooth=(AP_r-AP_y)*tmp;/**/
      AP_y_smooth_tau=(FLOAT)AP_tau;/**/
      _AP_RESET_T=(FLOAT)AP_RESET_T/100.;
      _AP_THHS=AP_THHS;/*99/11/24*/
#endif
    }
  }
  /* もにた通信用の為、値を設定する */
  AP_0_M=(WORD)(tmp*1000.+.5);
#ifndef MSPC
  AP_tau_M=(WORD)(AP_y_smooth_tau+.5);/**/
#endif
  /*理想はAP_y_smooth_r=exp(-4*AP_tS/AP_y_smooth_tau);/**/
  /*  AP_y_smooth_r=1.-AP_tS*4./AP_y_smooth_tau;/**/
#ifndef MSPC
  AP_y_smooth_r=Gensui(AP_y_smooth_tau);/**/
  AP_y_under=0;/**/
  AP_y_under2=0;/**/
  AP_y_reach=-1;/**/
#endif
#ifdef SPM_REINIT_BY_KASO
  AP_y_reach1=0;/**/
#endif
#endif
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
  AP_u_max=M_MAX;  /*入力最大値の設定 */
  AP_u_min=M_MIN;  /*入力最大値の設定 */ //061227kuwa
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
    AP_HoseiKaisiOndo=AP_approx(AP_r,3.0,80.,0.5,30.);
    if(AP_HoseiKaisiOndo>6) AP_HoseiKaisiOndo=6;/*135℃では5.75*/
}
/*======================================================*/
void init_AP(void)          /* 適応制御の準備と初期化 */
/*======================================================*/
{
  AP_KyoyouOndoGosa=2;
  init_MQ_AP();
  reinit_AP();
#ifdef MSPC
  if( AP_NP > 11 ) AP_NP=11;
  if( AP_NP >= 7 ){
    AP_NU = 1;
  }else if( AP_NP > 3 ){
    AP_NU = 2;
  }else {
    AP_NU = AP_NP;
  }
  /*AP_N2=AP_NU=4;/**/
  /*AP_N2=AP_NU=4;/**/
/*  AP_N2=AP_NU=3;/**/
  p_buf=&APC_BUF[0];
  g_buf=&p_buf[AP_N2];
  P_buf=&g_buf[AP_N2];
  r_buf=&P_buf[AP_NU*AP_NU];
  z_buf=&r_buf[AP_NU];
  Pr_buf=&z_buf[AP_NU];
  rP_buf=&Pr_buf[AP_NU];
#endif
#ifdef GPC
  /* AP_NUの追加				99/11/12 T.Arita*/
  /* AP_NP<=11, AP_NU<=AP_NP,N2*2+Nu*(Nu+4)<=27 の追加	99/11/14 Kurogi*/
  if( AP_NP > 11 ) AP_NP=11;
  if( AP_NP >= 7 ){
    AP_NU = 1;
  }else if( AP_NP > 3 ){
    AP_NU = 2;
  }else {
    AP_NU = AP_NP;
  }
  p_buf=&APC_BUF[0];
  g_buf=&p_buf[AP_N2];
  P_buf=&g_buf[AP_N2];
  r_buf=&P_buf[AP_NU*AP_NU];
  z_buf=&r_buf[AP_NU];
  Pr_buf=&z_buf[AP_NU];
  rP_buf=&Pr_buf[AP_NU];
#endif
}
#ifdef SPM_REINIT_BY_KASO
void spm_reinit_AP()
{
  if(_AP_RESET_T!=0.0){/*SPM_REINIT_BY_SETTEI/**/
    if(AP_y>=_AP_RESET_T && AP_y_reach1==0) {
      /*制御パラメータリセット温度が設定されていて、その温度になったら軌道再設定*/
        reinit_AP();
        AP_y_reach1=1;
    }
  }
  else{ /*SPM_REINIT_BY_KASO/**/
/*実温が100℃以下で仮想目標温度より5℃以上高いと再初期化：
　実際の制御と同じにしないといけない：上の行参照*/
    if(AP_y<100.0 &&
       ((AP_y-(AP_r-AP_y_smooth)>+5.0 && AP_r-AP_y>0)||
	(AP_y-(AP_r-AP_y_smooth)<-5.0 && AP_r-AP_y<0)))
      reinit_AP();
  }
}
#endif
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
  /* ATモードを廃止し、ATFフラグを使用する	99/11/12 T.Arita*/
  /* 新しいAT機能を使用する				*/
/*  if(time<1000) printf("ATF.b.AT_APC_F=%d\n",ATF.b.AT_APC_F);*/
#ifndef MSPC
  if(ATF.b.AT_APC_F){
    exec_AT_APC();
    if(AP_AT_cycle<10) return;
  }
#endif
#ifdef BWF
  /*バタワースフィルタ#2*/
  AP_y0=BWF_k*PV1/YB-BWF_b1*AP_y1-BWF_b2*AP_y2;
  AP_y=BWF_a0*AP_y0+BWF_a1*AP_y1+BWF_a2*AP_y2;
  AP_y2=AP_y1;
  AP_y1=AP_y0;
  /*バタワースフィルタ#1
  AP_y0=PV1/YB;
  AP_y=1.2813*AP_y-0.47844*AP_yy1+0.049283*(AP_y0+2.*AP_y1+AP_y2);
  AP_yy1=AP_y;
  AP_y2=AP_y1;
  AP_y1=AP_y0;/**/
#else 
  AP_y=PV1/YB;/**/
/*  AP_y=(PV1+((2.*random()-1.)*0.7)*YB)/YB;/**/
/*  AP_y=0.9*AP_y +0.1*PV1/YB+((2.*random()-1.)*0.07);*/
#endif
  /*AP_y=0.5*AP_y +0.5*PV1/YB;/*雑音が大きいため平均化 99/10/08S.Kurogi*/
  /*AP_y=0.95*AP_y +0.05*PV1/YB;/*雑音が大きいため平均化 99/10/08S.Kurogi*/
  /*AP_y=0.999*AP_y+0.001*PV1/YB;/*測定雑音が大きいとき*/
  /*AP_y=(1.+1./500.)*(PV1/YB)-(1./500.)*AP_y;/*ハンチングが出る*/
  /* 適応予測制御の組込		99/07/29〜08/17  T.Arita*/
  /* 制御モードの見直し					*/
/*if(C_MODE==SPM_APC && AP_y>=85 && AP_y_reach1==0) {
/*if(C_MODE>=3 && AP_y>=85 && AP_y_reach1==0) {*/
/*  /*硫酸過水のとき85℃になったら軌道再設定*/
/*    reinit_AP();
/*    AP_y_reach1=1;
/*}*/
/*  spm_reinit_AP();/*000514*/
  if(AP_y-AP_r>AP_overshoot) AP_overshoot=AP_y-AP_r;
#ifndef MSPC
  AP_y_smooth *= AP_y_smooth_r;/**/
  AP_y_ave=Gensui(100)*AP_y_ave +(1.-Gensui(100))*AP_y; /*  AP_y_ave=AP_y;*/
#endif
/**  if(AP_y_reach<=0){
/**    AP_y_under=0.0;
/**    /*    if((AP_y-AP_r>-3.0 && AP_y-AP_r<0.0) || 
/**	  (C_MODE==SPM_APC && AP_y_smooth<1) ){/**/
/**    AP_HoseiKaisiOndo=AP_approx(AP_r,3.0,80.,0.5,30.);
/**    if(AP_HoseiKaisiOndo>6) AP_HoseiKaisiOndo=6;/*135℃では5.75*/
/**    if(AP_y-AP_r>-AP_HoseiKaisiOndo && AP_y-AP_r<0.0){
/**	 /*目標温度の2.0℃以内に入ったら平均値の初期化*/
/**	 AP_y_ave=AP_y;
/**	 /*AP_y_smooth_r*=AP_y_smooth_r;/*??*/
/**	 AP_y_reach=AP_tS;
/**    }
/**  }
/**  else{
/**    /*AP_y_ave=0.99*AP_y_ave +0.01*AP_y; /*  AP_y_ave=AP_y;*/
/**    /*AP_y_under=AP_y_under+0.0004*(AP_y_ave-AP_r); /* 定常偏差を吸収*/
/**    /*AP_y_under=AP_y_under+AP_y_under_step*(AP_y_ave-AP_r); /**/
/**    /*AP_y_under=AP_y_under+(0.00016*AP_tS)*(AP_y_ave-AP_r); /**/
/**    /*AP_y_under=AP_y_under+(1.-AP_y_reach*0.9/600.)*(1.-Gensui(AP_THHS))*(AP_y_ave-AP_r); /**/
/**    /*   AP_y_under+=(1.-Gensui(AP_THHS))*(AP_y_ave-AP_r); /**/
/**    /*  _AP_THHS=100;*/
/**#ifdef FILTER
/**    AP_y_under+=(1.-Gensui(_AP_THHS*60.))*(AP_y-AP_r); /**/
/**#endif
/**    /*AP_y_under+=(1.-Gensui(6000))*(AP_y-AP_r); /**/
/**#ifdef GAIRANGO_SHOKIKA
/**    if(AP_y_reach>=300){/*5分以上して外乱チェック*/
/**	 if(AP_y<AP_r-AP_KyoyouOndoGosa || AP_y>AP_r+AP_KyoyouOndoGosa){
/**	   AP_y_under=0.0;
/**	   AP_y_reach=AP_tS;
/**	   /*	init_MQ_AP();/**/
/**	 }
/**    }
/**    else{/*時間計測*/
/**	 AP_y_reach+=AP_tS;
/**    }
/**#endif
/**  }
*/
//090622 yuno
  //ファイルに書き込み//koshi090204
  if(flag==1){
    if((nuse_flag==1)&&(uni_flag==1)&&(it>=1)){
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
    }
    else if((num_nets==1)&&(it>=1)){
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
    }
    else{
    }
  }
  /*00/10/05に変更*/
  if(AP_k==0){
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
  double AP_k_start=AP_kS1*(AP_ny+AP_IS);/*090331kuro*/
  //  if(AP_k_start<660) AP_k_start=660;/*090331kuro*/
  //  if(AP_k_start<650) AP_k_start=650;/*090331kuro*/
  if(AP_k_start<630) AP_k_start=605;/*090331kuro*/
  if(AP_k_hajime>=AP_k_start){/*090331kuro*/
    FLOAT aaaa;
    aaa=0.5-(FLOAT)AP_k/(FLOAT)AP_kS1;
    for(i=1;i<AP_IS+AP_ny;i++){
      AP_uu[i]=AP_u_sum[i]-(AP_u_sum[i]-AP_u_sum[i+1])*aaa;
    }
    for(i=1;i<AP_IS+AP_ny;i++){
      AP_yy[i]=AP_y_sum[i]-(AP_y_sum[i]-AP_y_sum[i+1])*aaa;
    }
    AP_yy[0]=AP_y;//AP_z[0]=1;
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
    if(ensemble==0){
      if((it>=1)&&(uni_flag==1)&&(nuse_flag==1)){
	//各ネットでユニットを選択する
	for(i=1;i<=num_nets;i++){
	    st_n_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,uni_AP_NC[i]);
	}
	AP_n_kk++;
	//エネルギから選択
	for(i=1;i<=num_nets;i++){
	  ndy2=0;
	  energy_n1[i]=-AP_y+net[i].cell[st_n_AP_i[i]].M[0][0]*AP_z[0]+AP_yy[1];
	  for(hi=1;hi<=AP_nu;hi++){
	    energy_n1[i] += net[i].cell[st_n_AP_i[i]].M[0][hi]*AP_du[hi];
	  }
	  for(hi=1;hi<=AP_ny;hi++){ 
	    energy_n1[i] += net[i].cell[st_n_AP_i[i]].M[0][hi+AP_nu]*AP_dy[hi];
	  }
	  energy_sum_n[i]+=(energy_n1[i]*energy_n1[i]);
	  energy_n[i]=energy_sum_n[i]/AP_n_kk;
	  energy_mean_n[i]+=energy_n[i];
	  //ndy2=energy_n[i];
	  mse[i][AP_n_kk]=(energy_n1[i]*energy_n1[i]);
	  if(AP_n_kk<save_time){
	    for(hi=1;hi<=AP_n_kk;hi++){
	      ndy2+=mse[i][hi];
	    }
	    n_err[i]=ndy2;
	  }	  
	  else{
	    for(hi=AP_n_kk-save_time;hi<=AP_n_kk;hi++){
	      ndy2+=mse[i][hi];
	    }
	    n_err[i]=ndy2;
	  }
	  if(i==1||ndy2<AP_n_err){
	    AP_n_err=ndy2;
	    AP_n_out=i;
	  }
	} 
	AP_i=st_n_AP_i[AP_n_out];
	for(i=0;i<=AP_nu+AP_ny;i++){
	  net[0].cell[AP_i].M[0][i]=net[AP_n_out].cell[st_n_AP_i[AP_n_out]].M[0][i];
	}
      }//end of if((it>=1)&&(uni_flag==1)&&(nuse_flag==1))
      else{
	AP_i=obtain_AP_i(AP_z,AP_y,net,0,AP_NC);
	AP_n_kk++;	
	ndy2=0;
	energy_n1[0]=-AP_y+net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_yy[1];
	for(hi=1;hi<=AP_nu;hi++){
	  energy_n1[0] += net[0].cell[AP_i].M[0][hi]*AP_du[hi];
	}
	for(hi=1;hi<=AP_ny;hi++){ 
	  energy_n1[0] += net[0].cell[AP_i].M[0][hi+AP_nu]*AP_dy[hi];
	}
	energy_sum_n[0]+=(energy_n1[0]*energy_n1[0]);
	energy_n[0]=energy_sum_n[0]/AP_n_kk;
	energy_mean_n[0]+=energy_n[0];
      }
    }//end of if(ensemble==0)
    else{ //else of if(ensemble==0)
      bag_i=1;
      for(i=1;i<=net_num;i++){
      	st_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,bag_i+f_AP_NC-1);//unitの選択
	if((i%(resample_num*boosting_times))==0) bag_i++;
      }     
      AP_i=0;//ユニット1のため
      //連想行列の平均を取る
      for(i=0;i<AP_NN;i++){
	//ネットの初期化
	net[0].cell[AP_i].M[0][i]=0;
	for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){
	  net[net_num+m].cell[AP_i].M[0][i]=0;
	}
	//Mの計算
	bag_i=1;
	for(m=1;m<=net_num;m++){//Bagging
	  net[net_num+bag_i].cell[AP_i].M[0][i]+=net[m].cell[st_AP_i[m]].M[0][i];
	  if((m%resample_num)==0){
	    net[net_num+bag_i].cell[AP_i].M[0][i]/=resample_num;
	    bag_i++;
	  }
	}
	boost_i=1;	
	for(m=1;m<=(boosting_times*n_AP_NC);m++){//Boosting??
	  net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].M[0][i]);
	  if((m%boosting_times)==0){
	    net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i]/=c_t_sum;
	    net[0].cell[AP_i].M[0][i] += net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i];
	    boost_i++;
	  }
	}
	net[0].cell[AP_i].M[0][i] = net[0].cell[AP_i].M[0][i]/n_AP_NC;
	for(j=0;j<AP_NN;j++){
	  //ネットの初期化
	  net[0].cell[AP_i].Q[i][j]=0;
	  for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){
	    net[net_num+m].cell[AP_i].Q[i][j]=0;
	  }	  
	  //Qの計算
	  bag_i=1;
	  for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){//Bagging
	    net[net_num+bag_i].cell[AP_i].Q[i][j]+=net[m].cell[st_AP_i[m]].Q[i][j];
	    if((m%resample_num)==0){
	      net[net_num+bag_i].cell[AP_i].Q[i][j]/=resample_num;
	      bag_i++;
	    }
	  }
	  boost_i=1;	
	  for(m=1;m<=(boosting_times*n_AP_NC);m++){//Boosting
	    net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].Q[i][j]);
	    if((m%boosting_times)==0){
	      net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]/=c_t_sum;
	      net[0].cell[AP_i].Q[i][j] += net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j];
	      boost_i++;
	    }
	  } 
	  net[0].cell[AP_i].Q[i][j]=net[0].cell[AP_i].Q[i][j]/n_AP_NC;
	}
      }
      //***平均取り終わり*********
    }//end of else{ //else of if(ensemble==0)
#ifdef FILTER2
    {
      int i;FLOAT yy=0;
      for(i=0;i<AP_NN;i++) yy+=net[0].cell[AP_i].M[0][i]*AP_z[i];
#ifndef MSPC
      AP_y_under2= AP_y_under2*(1.-Gensui(_AP_THHS*60.0))+Gensui(_AP_THHS*60.0)*(AP_y-yy); /**/
#endif
    }/**/
#endif
    store_vector_AP(AP_z,AP_y,net);
#else 
    /*AM_AP(AP_z,AP_y+2e-10*(2.*rand()-1.));/*データを記憶*/
    AM_AP(AP_z,AP_y);/*データを記憶*/
    /*相関行列が変な場合は初期化*/
    /*    if(AP_M[0][1]<0.01 || AP_M[0][1]>0.05){/**/
    /*if(AP_M[0][1]<0||(AP_M[0][2]>1)){/**/
    /*if(AP_M[0][2]>1 || AP_M[0][3]<0){/**/
    if(AP_M[0][2]>1){/**/
      /*init_MQ_AP();/*printf("Hatsunetu1\n");/**/
    }
#endif
#ifdef MSPC
    //090622 yuno 
    if(ensemble==0){
      if((it>=1)&&(uni_flag==1)&&(nuse_flag==1)){	
	//各ネットでユニットを選択する
	for(i=1;i<=num_nets;i++){
	    st_n_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,uni_AP_NC[i]);
	}
      }  
      else if((uni_flag==1)&&(nuse_flag==0)){
	AP_i=obtain_AP_i(AP_z,AP_y,net,0,AP_NC);
	for(i=1;i<=num_nets;i++){
	  if((uni_AP_NC[i-1]<=AP_i)&&(AP_i<AP_NC)){
	    AP_n_out=i;
	  }
	}
      }  
      else{
	// 荷重ベクトルによるユニットの選択
	AP_i=obtain_AP_i(AP_z,AP_y,net,0,AP_NC);
      }
    }
    else{
      bag_i=1;
      for(i=1;i<=net_num;i++){
	st_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,bag_i+f_AP_NC-1);
	if((i%(resample_num*boosting_times))==0) bag_i++;
      }
      AP_i=0;//ユニット1のため
      //***連想行列の平均を取る***
      for(i=0;i<AP_NN;i++){
	//ネットの初期化
      net[0].cell[AP_i].M[0][i]=0;
      for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){
	net[net_num+m].cell[AP_i].M[0][i]=0;
      }	    
      //Mの計算
      bag_i=1;
      for(m=1;m<=net_num;m++){//Bagging
	net[net_num+bag_i].cell[AP_i].M[0][i]+=net[m].cell[st_AP_i[m]].M[0][i];
	if((m%resample_num)==0){
	  net[net_num+bag_i].cell[AP_i].M[0][i]/=resample_num;
	  bag_i++;
	}
      }      
      boost_i=1;	
      for(m=1;m<=(boosting_times*n_AP_NC);m++){//Boosting
	net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].M[0][i]);
	if((m%boosting_times)==0){
	  net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i]/=c_t_sum;
	  net[0].cell[AP_i].M[0][i] += net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i];
	  boost_i++;
	}
      }      
      net[0].cell[AP_i].M[0][i]=net[0].cell[AP_i].M[0][i]/n_AP_NC;	      
      for(j=0;j<AP_NN;j++){
	//ネットの初期化
	net[0].cell[AP_i].Q[i][j]=0;
	for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){
	  net[net_num+m].cell[AP_i].Q[i][j]=0;
	}	  
	//Qの計算
	bag_i=1;
	for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){//Bagging
	  net[net_num+bag_i].cell[AP_i].Q[i][j]+=net[m].cell[st_AP_i[m]].Q[i][j];
	  if((m%resample_num)==0){
	    net[net_num+bag_i].cell[AP_i].Q[i][j]/=resample_num;
	    bag_i++;
	  }
	}
	boost_i=1;	
	for(m=1;m<=(boosting_times*n_AP_NC);m++){//Boosting
	  net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].Q[i][j]);
	  if((m%boosting_times)==0){
	    net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]/=c_t_sum;
	    net[0].cell[AP_i].Q[i][j] += net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j];
	    boost_i++;
	  }
	} 	
	net[0].cell[AP_i].Q[i][j]=net[0].cell[AP_i].Q[i][j]/n_AP_NC;
      }     
      }
      //***平均取り終わり*********
    }
    /*エネルギのE計算*/
    AP_kk++;/*エネルギ計算のため*//*2007/02/18/koshi*/
    energy1=-AP_y+net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_z[AP_nu+2];
    for(i=1;i<=AP_nu;i++)
      energy1 += net[0].cell[AP_i].M[0][i]*AP_du[i];
    for(i=1;i<=AP_ny;i++) 
      energy1 += net[0].cell[AP_i].M[0][i+AP_nu]*AP_dy[i];
    energy_sum+=(energy1*energy1);
    energy=energy_sum/AP_kk;/*エネルギEの計算*/
    energy_mean+=energy;/*エネルギの平均の計算*/
    /*energy=energy_sum;/*自乗誤差総和の計算*/
    /*printf("%f,AP_kk=%f\n",time,AP_kk);/**/
    AP_yyy=0;
    AP_yyy+=net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_z[3];
    for(i=1;i<=AP_nu;i++)
      AP_yyy += net[0].cell[AP_i].M[0][i]*(AP_uu[i]-AP_uu[i+1]);
    for(i=1;i<=AP_ny;i++)
      AP_yyy += net[0].cell[AP_i].M[0][i+AP_nu]*(AP_yy[i]-AP_yy[i+1]);
    SMV=AP_u=predict_search_AP(AP_i);  /*操作量決定*/
    //090622 yuno
      if((nuse_flag==1)&&(uni_flag==1)&&(it>=1)){//090126koshi     
	for(hi=1;hi<=num_nets;hi++){
	  p_err[hi]=0;
	}
	for(hi=1;hi<=num_nets;hi++){
	  AP_yyn=0;
	  AP_yyn+=net[hi].cell[st_n_AP_i[hi]].M[0][0]*AP_z[0]+AP_yy[1];
	  for(i=1;i<=AP_nu;i++)
	    AP_yyn += net[hi].cell[st_n_AP_i[hi]].M[0][i]*AP_du[i];
	  for(i=1;i<=AP_ny;i++)
	    AP_yyn += net[hi].cell[st_n_AP_i[hi]].M[0][i+AP_nu]*AP_dy[i];
	  for(i=0;i<AP_NN;i++){
	    net[0].cell[AP_i].M[0][i]=net[hi].cell[st_n_AP_i[hi]].M[0][i];
	  }
	  AP_yn[hi]=AP_y-AP_yyn;//予測誤差
	  SMV_n[hi]=predict_search_AP(AP_i);
	}
	//ファイルに書き込み
	if((fpi=fopen("input.dat","a+"))==NULL){
	  exit(1);
	}
	fprintf(fpi,"%f ",time);
	for(hi=1;hi<=num_nets;hi++){
	  fprintf(fpi,"%f ",SMV_n[hi]);
	}
	fprintf(fpi,"%d ",AP_n_out);
	fprintf(fpi,"%f ",AP_y);
	for(hi=1;hi<=num_nets;hi++){
	  fprintf(fpi,"%f ",AP_yn[hi]);
	}
	fprintf(fpi,"%f ",AP_y-AP_yyy);
	fprintf(fpi,"\n");
	fclose(fpi);	
      }
      else if((num_nets==1)&&(it>=1)){
	if((fpi=fopen("input.dat","a+"))==NULL){
	  exit(1);
	}
	fprintf(fpi,"%f ",time);
	fprintf(fpi,"%f ",SMV-AP_uu[1]);
	fprintf(fpi,"%f ",AP_y);
	fprintf(fpi,"%f ",AP_y-AP_yyy);
	fprintf(fpi,"\n");
	fclose(fpi);
      }
      else{
      }
#else
    SMV=AP_u=predict_search_AP(); /*操作量決定*/
#endif
#ifdef EMULATE
    SMV=AP_u=(AP_u_max/200.)*(int)(AP_u/(AP_u_max/200.)+0.5);
#endif
    /*    if(time<1000) printf("***%5.2f %f\n",time, SMV);*/
  }
  else {/*if (AP_k_hajime<AP_kS1*(AP_NN+AP_IS-1)*/
    AP_k_hajime++;
/*制御開始時にもAPCで実行するように変更．99/11/15 Kurogi*/
/*KELKでのSPM に対応ため上を元に戻す．99/11/17 Kurogi*/
/*    if(C_MODE==SPM_APC){/*SPM 許容範囲2℃以内but自己発熱がある*/
#define ICONIP2001 1
    /*if(C_MODE==DEF_APC){/*SPM 許容範囲2℃以内but自己発熱がある*/
    /*if(1){/*SPM 許容範囲2℃以内but自己発熱がある*/
      /*if(AP_r>AP_y+10) SMV=AP_u=AP_u_max; /*操作量決定*/
      /*else if(AP_r>AP_y) SMV=AP_u=0.15*(AP_u_max-AP_u_min)+AP_u_min;
	/*else SMV=AP_u=0.0; /*操作量決定*/
      /* }*/
      /*else{/*許容範囲1℃以内*/
      AP_yy[0]=AP_y;
      /*for(i=1;i<=AP_nu;i++) AP_z[i]=AP_uu[i]=0.1*AP_u_max;/*80℃スタートの場合*/
      /*for(i=1;i<=AP_ny;i++) AP_z[i+AP_nu]=AP_yy[i]=AP_y;/*80℃スタートの場合*/
      for(i=1;i<=AP_nu;i++) AP_z[i]=AP_uu[i]=0.2*AP_u_max;/*エネルギがOSに良く反映するが,入力の変化に問題ありかも*/
      for(i=1;i<=AP_ny;i++) AP_z[i+AP_nu]=AP_yy[i]=AP_y-3.0*i;/*エネルギがOSに良く反映するが,入力の変化に問題ありかも*/
#ifdef MSPC
      if(ensemble==0){
	if((it>=1)&&(uni_flag==1)&&(nuse_flag==1)){
	  //各ネットでユニットを選択する
	  for(i=1;i<=num_nets;i++){
	    st_n_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,uni_AP_NC[i]);
	  }  
	  //各ネットで選択されたユニットに対して,さらに観測値との誤差により選択
	  for(i=1;i<=num_nets;i++){
	    ndy2=0;
	    for(k=0;k<1;k++){
	      ndy = -AP_yy[k]+AP_yy[k+1]+net[i].cell[st_n_AP_i[i]].M[0][0]*AP_z[0];
	      for(j=1;j<=AP_nu;j++) ndy += net[i].cell[st_n_AP_i[i]].M[0][j]*(AP_uu[k+j]-AP_uu[k+j+1]);
	      for(j=1;j<=AP_ny;j++) ndy += net[i].cell[st_n_AP_i[i]].M[0][j+AP_nu]*(AP_yy[k+j]-AP_yy[k+j+1]);
	      ndy2+=fabs(ndy);
	    }
	    //ndy2/=AP_IS;
	    n_err[i]=ndy2;
	    if(i==1||ndy2<AP_n_err){
	      AP_n_err=ndy2;
	      AP_n_out=i;
	    }
	  }
	  AP_i=st_n_AP_i[AP_n_out];	  
	  for(i=0;i<=AP_nu+AP_ny;i++){
	    net[0].cell[AP_i].M[0][i]=net[AP_n_out].cell[st_n_AP_i[AP_n_out]].M[0][i];	
	  }
	}
	else{
	  AP_i=obtain_AP_i(AP_z,AP_y,net,0,AP_NC);
	}
      }
      else{
	bag_i=1;
	for(i=1;i<=net_num;i++){
	  st_AP_i[i]=obtain_AP_i(AP_z,AP_y,net,i,bag_i+f_AP_NC-1);
	  if((i%(resample_num*boosting_times))==0) bag_i++;
	}
	AP_i=0;//ユニット1のため
	//***連想行列の平均を取る***
	for(i=0;i<AP_NN;i++){
	  //ネットの初期化
	  net[0].cell[AP_i].M[0][i]=0;
	  for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){
	    net[net_num+m].cell[AP_i].M[0][i]=0;
	  }
	  //Mの計算
	  bag_i=1;
	  for(m=1;m<=net_num;m++){//Bagging
	    net[net_num+bag_i].cell[AP_i].M[0][i]+=net[m].cell[st_AP_i[m]].M[0][i];
	    if((m%resample_num)==0){
	      net[net_num+bag_i].cell[AP_i].M[0][i]/=resample_num;
	      bag_i++;
	    }
	  }  
	  boost_i=1;	
	  for(m=1;m<=(boosting_times*n_AP_NC);m++){//Boosting
	    net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].M[0][i]);
	    if((m%boosting_times)==0){
	      net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i]/=c_t_sum;
	      net[0].cell[AP_i].M[0][i] += net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].M[0][i];
	      boost_i++;
	    }
	  }	  
	  net[0].cell[AP_i].M[0][i]=net[0].cell[AP_i].M[0][i]/n_AP_NC;		  
	  for(j=0;j<AP_NN;j++){
	    //ネットの初期化
	    net[0].cell[AP_i].Q[i][j]=0;
	    for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){
	      net[net_num+m].cell[AP_i].Q[i][j]=0;
	    }	  
	    //Qの計算
	    bag_i=1;
	    for(m=1;m<=(boosting_times*n_AP_NC+n_AP_NC);m++){//Bagging
	      net[net_num+bag_i].cell[AP_i].Q[i][j]+=net[m].cell[st_AP_i[m]].Q[i][j];
	      if((m%resample_num)==0){
		net[net_num+bag_i].cell[AP_i].Q[i][j]/=resample_num;
		bag_i++;
	      }
	    }	    
	    boost_i=1;	
	    for(m=1;m<=(boosting_times*n_AP_NC);m++){//Boosting
	      net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]+=(boosting_c_t[m]*net[net_num+m].cell[AP_i].Q[i][j]);
	      if((m%boosting_times)==0){
		net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j]/=c_t_sum;
		net[0].cell[AP_i].Q[i][j] += net[net_num+(boosting_times*n_AP_NC)+boost_i].cell[AP_i].Q[i][j];
		boost_i++;
	      }
	    } 	    
	    net[0].cell[AP_i].Q[i][j]=net[0].cell[AP_i].Q[i][j]/n_AP_NC;
	  }	  
	}
	//***平均取り終わり*********
      }      
      /*net[0].cell[AP_i].v++;/*774s以前に発火したセルの価値を高める*/
/*        AP_kk++;/*エネルギ計算のため*/  
/*        energy1=-AP_y+net[0].cell[AP_i].M[0][0]*AP_z[0];  */
/*        for(i=1;i<=AP_nu;i++) energy1 += net[0].cell[AP_i].M[0][i]*AP_uu[i];  */
/*        for(i=1;i<=AP_ny;i++) energy1 += net[0].cell[AP_i].M[0][i+AP_nu]*AP_yy[i];  */
/*        energy_sum+=(energy1*energy1);  */
/*        energy=energy_sum/AP_kk;/*エネルギEの計算*/ 
/*        energy_mean+=energy;/*エネルギの平均の計算*/ 
      /*energy=energy_sum;/*自乗誤差総和の計算*/
      AP_yyy=0;
      //090622 yuno
      AP_yyy+=net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_yy[1];
      for(i=1;i<=AP_nu;i++)
	AP_yyy += net[0].cell[AP_i].M[0][i]*(AP_uu[i]-AP_uu[i+1]);
      for(i=1;i<=AP_ny;i++) 
	AP_yyy += net[0].cell[AP_i].M[0][i+AP_nu]*(AP_yy[i]-AP_yy[i+1]);
      SMV=AP_u=predict_search_AP(AP_i);  /*操作量決定*/
#else
      SMV=AP_u=predict_search_AP(); /*操作量決定*/
#endif
    }
  if(++AP_k>=AP_kS1) AP_k=0;/**/
  /*AP_kk++;/*エネルギ計算のため*/
  //if(AP_y>AP_r+0.5) AP_u=0;/*2000/05/15*/
#ifdef EMULATE
  SMV=AP_u=(AP_u_max/200.)*(int)(AP_u/(AP_u_max/200.)+0.5);
#endif
  /*  モニタ通信用の適応予測制御のSV値の算出			*/
#ifdef MSPC
  AP_SV_M=(WORD)((AP_r)*100.);
#else
  AP_SV_M=(WORD)((AP_r-AP_y_smooth-AP_y_under-AP_y_under2)*100.);
#endif
}
#ifndef MSPC
/*======================================================*/
void     calc_AP_tau(void)   /* 新しいAT実行後のtauの計算*/
/*======================================================*/
{
  /* 99/11/16 by Tako*/
  FLOAT t100;
  t100=(AP_AT_j[3]-AP_AT_j[2])*20/(80-50)+AP_AT_j[3];
  AP_tau=hokan((LONG)(100*(AP_AT_y[4]-AP_AT_y[3])),
	       (LONG *)&AP_AT_TBL[0][0], AP_AT_TBL_N )+t100;/**/ 
  if(AP_tau<1000)	/* AP_tauは1000以上とする */
    AP_tau = 1000;
  AP_0=1000;
  AP_RESET_T=(WORD)(_AP_RESET_T*100.+.5);
  AP_THHS=_AP_THHS;
  /* モニタ通信用の為、値を設定する */
  AP_0_M=AP_0;
  AP_tau_M=AP_tau;/**/
  /* AT完了フラグをON */
  AT_END = 1;
  /* AT完了時、ATF,ATTUのOff*/
  rst_at();/*E2PROMにストア*/
  init_AP();/*reinit_AP(); 99/11/24*/
}
/*======================================================*/
void     exec_AT_APC(void)          /* 適応予測制御演算*/
/*======================================================*/
{
  /*AP_y=0.5*AP_y +0.5*PV1/YB;/*雑音が大きいため平均化 99/10/08S.Kurogi*/
  AP_y=PV1/YB;/*雑音が大きいため平均化 99/10/08S.Kurogi*/
  AP_AT_jikan+=AP_tS;
#ifndef MSPC
  AP_y_smooth *= AP_y_smooth_r;/**/
#endif
#ifdef SPM_REINIT_BY_KASO
  spm_reinit_AP();
#endif
  if(AP_AT_cycle==1){/*最小温度を求める*/
#ifdef EMULATE
	if(AP_AT_jikan==AP_tS) AP_AT_kaishijikan=time;
#endif	
    SMV=AP_u=AP_u_max;
    if(AP_y<AP_AT_y[0]) {
      AP_AT_y[0]=AP_y;
      AP_AT_j[0]=AP_AT_jikan;/*最小温度の時刻を代入*/
    }
    if(AP_y>=AP_AT_y[AP_AT_cycle]){
      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*10%温度以上に入った時刻を代入*/
      AP_AT_cycle++;
    }
  }
  else if(AP_AT_cycle==2){
    SMV=AP_u=AP_u_max;
    if(AP_y>=AP_AT_y[AP_AT_cycle]){
      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*50%温度以上に入った時刻を代入*/
      AP_AT_cycle++;
    }
  }
  else if(AP_AT_cycle==3){
    SMV=AP_u=AP_u_max;
    if(AP_y>=AP_AT_y[AP_AT_cycle]){
      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*80%温度以上に入った時刻を代入*/
      AP_AT_cycle++;
    } 
  }
  else if(AP_AT_cycle==4){/*80%以上に上昇した温度を求める*/
    SMV=AP_u=AP_u_min;
    if(AP_y>AP_AT_y[AP_AT_cycle]) {/*最大温度の時刻を求める*/
      AP_AT_y[AP_AT_cycle]=AP_y;/*最大温度の時刻を代入*/
      AP_AT_j[AP_AT_cycle]=AP_AT_jikan;/*最大温度を代入*/
    }
    /*    if(AP_y<=AP_AT_y[2]-10.0){/*SPC*/
    if(AP_y<=AP_AT_y[3]-1.0){/*SPC*/
      AP_AT_j[5]=AP_AT_jikan;/*80%温度-1℃の時刻を代入*/
      AP_AT_y[5]=AP_y;
#ifndef EMULATE
      calc_AP_tau();
#else 
      /*      ATF.b.AT_APC_F=0;*/
      calc_AP_tau();
      AP_AT_cycle=-11;
/*	  ATF.b.AT_APC_F=0;calc_AP_tau();ATF.b.AT_APC_F=1;
/*	  AP_AT_cycle=5;
/*	  AP_AT_Np_opt=AP_Np=1;/*dummy*/
/*	  AP_AT_seiteijikan_saitan=AP_tau;
/**/
#endif
    }
  }
#ifdef EMULATE
  else if(AP_AT_cycle==5){/*一旦AP_rの4℃以上に上昇させる*/
    SMV=AP_u=AP_u_max;
    if(AP_y>=AP_r-4.){
      AP_AT_cycle=-10;
    }
  }
  else if(AP_AT_cycle==-10){
    if(AP_y<=AP_r-5.){/*目標より5℃温度以下に下降させる*/
      AP_AT_cycle=10;
      AP_AT_jikan=0;
      if(AP_Np==1) AP_Np=5;
/*      else if(AP_Np==3) AP_Np=5;*/
      else if(AP_Np==5) {
	AP_AT_cycle=-11;/*owari*/
	AP_AT_shuryojikan=time;
      }/**/
#ifdef EMULATE
#endif
      ATF.b.AT_APC_F=0;
      init_AP();
      ATF.b.AT_APC_F=1;
      AP_AT_seitei=0;
      AP_AT_seiteijikan=AP_tau;
    }
    else SMV=AP_u=AP_u_min;
  }
  else if(AP_AT_cycle==10){
    if(fabs(AP_r-AP_y)<=AP_KyoyouOndoGosa){
      if(AP_AT_seiteijikan>=AP_tau){/*許容範囲に入る*/
	AP_AT_seiteijikan=AP_AT_jikan;
      }
/*      if(AP_AT_jikan>=AP_AT_seiteijikan+900){/*15分以上で終わり*/
      if(AP_AT_jikan>=AP_AT_seiteijikan+60000){/*60000秒で終わり*/
      /*if(AP_AT_jikan>=AP_AT_seiteijikan+0.5*AP_tau){/*以上で終わり*/
      /*if(AP_AT_jikan>=AP_AT_seiteijikan+AP_tau){/*以上で終わり*/
	AP_AT_cycle=-10;
	/*	printf("AP_AT_Np_ok=%d(%f),Now=%f\n",AP_Np,AP_AT_seiteijikan,time);*/
	if(AP_AT_seiteijikan<AP_AT_seiteijikan_saitan){
	  AP_AT_seiteijikan_saitan=AP_AT_seiteijikan;
	  AP_AT_Np_opt=AP_Np;
#ifdef EMULATE
	  //hi printf("AP_AT_Np_opt=%d(%f),AP_tau=%d,Now=%f\n",
		 AP_AT_Np_opt,AP_AT_seiteijikan_saitan,AP_tau,time);/**/
#endif
	}
      }
    }
    else if(fabs(AP_r-AP_y)>AP_KyoyouOndoGosa+0.3){/*誤差以上*/
      if(AP_AT_seiteijikan<AP_tau){/*一旦出ると終わり*/
#ifdef EMULATE
	//hi printf("AP_AT_Np_ng=%d(%f),AP_tau=%d,Now=%f\n",AP_Np,AP_AT_seiteijikan,AP_tau,time);/**/
#endif
	AP_AT_cycle=-10;
      }
    }
  }
  if(AP_AT_cycle==-11){
    SMV=AP_u=AP_u_min;
  }
#endif /*#ifdef AT_FOR_NP*/
}
#endif
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
#else
void	main(void)		/*  MAIN 				*/
#endif
/************************************************************************/
{
  BYTE	calc_start;
  /* 適応予測制御の演算間隔を500msに変更	99/11/08 T.Arita*/
  BYTE	apc_calc_start;
  char buff[buffsize];
  int i_main;
  int hi;//080131yuno
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
  // 050704 tomisaki
  printf("************ CAN2 for MSPC ***************\n");
  /*  printf("use ensemble netfile? yes:1 no:0\n");//2005/11/9
  scanf("%d",&ensemble);
  if(ensemble==1){
    printf("input 5th netfile ****.net \n");
    for(i_main=0;i_main<5;i_main++){
      scanf("%s",net_f[i_main]);
    }
    net->firstcall=1;
    num_nets=1;
  }
  */
  printf("Use ensemble learning(y/n), iteration(>0):");//2005/11/9
  fgets(buff,buffsize,stdin);sscanf(buff,"%s %d %d",yesno,&_iteration,&DISP);
  ensemble=(yesno[0]=='y'||yesno[0]=='1')?1:0;

//  char yesno1[5];
//  printf("Use ensemble learning(y/n), iteration(>0) useensrs(y/n):");//2005/11/9
//  fgets(buff,buffsize,stdin);sscanf(buff,"%s %d %s",yesno,&_iteration,yesno1);
//  ensemble=(yesno[0]=='y'||yesno[0]=='1')?1:0;
//  useensrs=(yesno1[0]=='y'||yesno1[0]=='1')?1:0;
  //  scanf("%d",&ensemble);
  
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
  stable_time=0;
  obtain_new=1;
  u_limit=0;
  matrix_0=0;
  gakusyu=0;
  penalty=3;  
  if(ensemble==0){
    printf("The number of cell:");
    fgets(buff,buffsize,stdin);sscanf(buff,"%d",&AP_NC);
    //    scanf("%d",&AP_NC);
    if(AP_NC<1) AP_NC = 1;
  }
  else{
    printf("The ID number of the first cell:");
    fgets(buff,buffsize,stdin);sscanf(buff,"%d",&f_AP_NC);
    //    scanf("%d",&f_AP_NC);
    if(f_AP_NC<1) f_AP_NC = 1;
    
    printf("The ID number of the last cell:");/*kuwa060223*/
    fgets(buff,buffsize,stdin);sscanf(buff,"%d",&e_AP_NC);
    //    scanf("%d",&e_AP_NC);
    if(f_AP_NC>e_AP_NC){
      ensemble=0;
      AP_NC=f_AP_NC;
    }
    n_AP_NC=e_AP_NC-f_AP_NC+1; /*kuwa060223 アンサンブルの数n_AP_NC<100*/
    AP_NC=f_AP_NC;   
    if(bagging_flag==1){
      printf("The number of the resampling datasets:");
      fgets(buff,buffsize,stdin);sscanf(buff,"%d",&resample_num);
      //scanf("%d",&resample_num);
      if(resample_num<1) resample_num = 1;     
      printf("The alpha:");/*kuwa061023*/
      fgets(buff,buffsize,stdin);sscanf(buff,"%f",&bag_alpha);
      //scanf("%f",&bag_alpha);
      if(bag_alpha<=0 || bag_alpha>1){
	bag_alpha=1;
      }
    }
    if(boosting_flag==1){
      printf("The number of boosting times (less than 100):");
      fgets(buff,buffsize,stdin);sscanf(buff,"%d",&boosting_times);
      //scanf("%d",&boosting_times);
      if(boosting_times<1) boosting_times = 1;
    }
  }
  net_num=boosting_times*resample_num*n_AP_NC;
  //yuno071203
  printf("Number of netfiles:");
  fgets(buff,buffsize,stdin);sscanf(buff,"%d",&num_nets);
  //  scanf("%d",&num_nets);//number of netfiles?kuro
  if(num_nets==1){
    printf("The name of the netfile(****.net):");
    fgets(buff,buffsize,stdin);sscanf(buff,"%s",net_f);//??
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
      printf("Merge(0) or Select(1) the netfiles?");
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
    if((uni_flag==1)&&(nuse_flag==0)){
      for(uni=1;uni<=num_nets;uni++){
      	printf("The number of the cell of the %dth netfile\n",uni);
	fgets(buff,buffsize,stdin);sscanf(buff,"%d",&uni_AP_NC[uni]);
	//scanf("%d",&uni_AP_NC[uni]);
	cell_num+=uni_AP_NC[uni];
      }
      AP_NC=cell_num;
      if(AP_NC<1) AP_NC=1;
    }
    else{
      for(uni=1;uni<=num_nets;uni++){
	uni_AP_NC[uni]=AP_NC;
      }
    }
  }
  int iii;
  for(iii=0;iii<=n_AP_NC;iii++){ /*st_AP_i[]の初期化*/
    st_AP_i[iii]=0;
  }
  //090622 yuno
  for(iii=0;iii<=num_nets;iii++){//st_n_AP_i[]の初期化
    st_n_AP_i[iii]=0;
  }
  for(iii=0;iii<100;iii++){
    boosting_c_t[iii]=1; //netの重み初期化
  }
  c_t_sum=boosting_times;   
  printf("f_AP_NC=%d,e_AP_NC=%d,n_AP_NC=%d,AP_NC=%d,ensemble=%d,resample_num=%d,bag_alpha=%f,boosting_times=%d,net_num=%d\n",f_AP_NC,e_AP_NC,n_AP_NC,AP_NC,ensemble,resample_num,bag_alpha,boosting_times,net_num);/*060322kuwa*/ 
  net->firstcall=1;
  //if(argc>1) net0=argv[1];//050621 modified by kuro
  init_AP();/* 適応制御初期化:初めにこれが呼ばれるべし*/
  if(net0){
    net_load(net,net0,0,AP_NC);//050621 modified by kuro
    sprintf(buff,"cp %s can2b.net\n",net0);
    system(buff);  
    net->firstcall=1;
  }
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
/*	  if(PP != 0){
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
/*	      calc_AP();
/*	      break;
/*	    case 1:			/* スーパー2自由度PID制御 */
/*	      calc_s2dof_pid();
/*	      break;*/
/*	    case 0:
/*	    default:		       /* 従来のPID制御 */
/*	      calc_pid();
/*	      break;
/*	    }
/*	  }
/*	  else{			/*ON/OFF制御モード*/
/*	    switch(C_MODE){
/*	    case 2:
/*	      AP_u_res=1;  /*適応によるON/OFF制御*/
/*	      calc_AP();
/*	      break;
/*	    default:	/* 従来のPID制御 */
/*	      calc_onoff();
/*	      rst_pid();
/*	    }
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

