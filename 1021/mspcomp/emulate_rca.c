#include <stdio.h>
#include <stdlib.h> //090624yuno疑似乱数をzmtrand.c使うため
#include <math.h>
#include "cs_emu.h"

//090624yuno
#include "myrandom.c" 
#define usezmtrand
#ifdef usezmtrand
#include  "share/zmtrand.c"
#endif
#define USEMALLOC

double AP_AT_shuryojikan=0;
double AP_AT_kaishijikan=0;
int debug=0; /* 実際のコンパイルでは必要ない*/
FILE *fptrain,*fptest;
char *fntrain="mspctrain.dat";
char *fntest="mspctest.dat";

//090604yuno
int _iteration=0;
int DISP=0;
int iteration,it=0;
FILE *fpresult;
char *fnresult="mspcresult.dat";
#define NEWenergy
#define cmdsize 256
#define buffsize 256
#define fnsize 256

#include "apc_rca.c"
int checkmode=0;
#undef PI
#define PI 3.14159265358979323846
double AP_u_ave;

int k,k_plus_1,k_minus_1,k_minus_kT,k_minus_kH,k_minus_kB;
int k_minus_kD,kD;

//RCA plant
double TK=273.15;
double *buff_TH,*buff_TB,*buff_P,*buff_VA;
double *TH;/*ヒータ温度*/
double *TB,*TB0,yyy;/*水槽温度*/
double TC;/*140;/*自己発火開始温度*/
double TO=25;/*外気温度*/
double Pinf,TBinf;/*定常状態になったときのPとTB*/
double MA=0,dMA,dMB,dH,n_ALPHA,R=8.31;/*自己発火モル数*/
double MAT;/*自己発火総体積*/
double *p;/*入力ワット*/
double Pmax=6000;/*入力ワット*/
double LH0,LB0,LH,LB,LT,R2;
double tH,tB,tT;
int kH,kB,kT;
double v;//volume?
int stocksize;

double tD,tauD,etauD;
double aHH,aHB,aHP;
double aBB,aBH,aB0,aBP;
double VB=0.030,VH=0.0024,VT;
double S=0.0002;
double rV;
double vS=0.00023;
double tauB;
double alphaO=0.00024,alpha;
double beta0=0.00103,beta;
double T_ini=85;
int plantmode=0;
double a0,a1,b,c,bH;
double rho0=1000,C0=4200;
double r1,rho1,rho_01,C1,C_01;
double r2,rho2,rho_02,C2,C_02;
double rho_r,C_r,rho_0r,C_0r;
double zatuon_rho_r,zatuon_C_r,_rho_r,_C_r;
double *TH0,*TH1,*TB0,TB1;
double *u_PID,*e_PID;
int k_PID,k_PID_minus_1,k_PID_minus_2,buffsize_PID=5;
double e_PID_k_minus_2,e_PID_k_minus_1,e_PID_k;
double u_PID_k_minus_1,u_PID_k;

int cntl_phase=0;
double ur[5]={1.0,0.4,0.5},TBC[5]={120,-1,};
double zatuon_keisoku=0.05,zatuon_alpha,zatuon_TO,zatuon_vS;
double _alpha,_TO,_vS;
double kp,ki,kd,TI,TD;
int Np=10;
double *y,yy=0,*u,uu=0,uuu,*buff_y,*buff_u;
double *us;
double *ys;
int kk,i,j,kk1;
double starttime,totaltime,tS1=100,gamma1=0.1,Ea,Ko,lnKo;
double alpha2_forget=1.0;
double *z;
double u_res,u_max;
int dim=0;
int kS1;
int zmode=51;
int imode1,imode2;
double rr,rr_kyoyou,rr_smooth_r,rr_smooth,rr_over,rr_under,rr_smooth_n=0,t_smooth;
double overshoot=0,undershoot=0,maxTB=0;
double seiteijikoku=-1,dis_seitei=-1;

/*bagboostの導入に用いた変数 2006kuwa*/
#define tau 1000
#define	RAND_MAX	2147483647

/* 指数変換でも使用する為、戻り値をLONG型にする			*/
/* 呼び出し元では、キャストするように変更した			*/
/*--------------------------------------------------------------*/
LONG	hokan(LONG x,LONG *ptr,WORD cnt)	/*  補間	*/
     /*--------------------------------------------------------------*/
{
  WORD	i;
  LONG	temp;
  LONG	temp_mod;
  LONG	ltemp;
  LONG	*ptr1;
  
  ptr1 = ptr+cnt;
  for( i=0;i<cnt;i++ ){
    if( x < *ptr )	break;
    ptr++;
    ptr1++;
  }
  if( i<=0 ){
    temp = *ptr1;
  }else if( i>=cnt ){
    temp = *(ptr1-1);
  }else{
    if( *ptr == *(ptr-1) ){			/*  x1 == x2	*/
      temp = *(ptr1-1);		/*   ans = y1	*/
    }else{					/*  x1 != x2	*/
      if( *ptr1 > *(ptr1-1) ){	/*   y2 > y1	*/
	ltemp = *ptr1-(*(ptr1-1));
	ltemp *= (x-(*(ptr-1)));
	*ptr1--;
      }else{				/*   y2 < y1	*/
	ltemp = *(ptr1-1)-(*ptr1);
	ltemp *= ((*ptr)-x);
      }
      if( ltemp == 0 ){		/*   (y2-y1)*(x-x1) == 0 */
	temp = *ptr1;		/*    ans = y1	*/
      }else{
	temp_mod = ltemp%(*ptr-(*(ptr-1)));
	ltemp = ltemp/(*ptr-(*(ptr-1)));
	if( ltemp > 32767 ){	/*   (y2-y1)*(x-x1)/(x2-x1) > 32767 */
	  temp = *ptr1;	/*    ans = y1	*/
	}else{
	  temp = ltemp + *ptr1;
	  if( temp_mod*2 < (*ptr)-(*(ptr-1)) ){
	    temp += 1;
	  }
	}
      }
    }
  }
  return temp;
}
initialize()
{
  int i;
  char buff[buffsize];
  FILE *fp;
  /**************/
  if((fp=fopen("emulate_rca.ini","r"))==NULL){
    printf("File (emulate_rca.ini) Open Error\n");
    fclose(fp);
    if((fp=fopen("emulate.dat","r"))==NULL){
      printf("File (emulate.dat) Open Error\n");
      fclose(fp);
      return;
    }
  }
  for(;;){fgets(buff,buffsize,fp); if(buff[0]!='#') break;}
  sscanf(buff,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
	 &vS,&LH0,&LB0,&VH,&VB,&R2,&TO,&Pinf,&TBinf,&tD,&tauD);
  vS=vS/60./1000.;/*l/min==> m^3/s*/
  
  for(;;){fgets(buff,buffsize,fp); if(buff[0]!='#') break;}
  sscanf(buff,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
	 &r1,&rho_01,&C_01,&r2,&rho_02,&C_02,&Ea,&lnKo,&dH,&n_ALPHA);
  for(;;){fgets(buff,buffsize,fp); if(buff[0]!='#') break;}
  sscanf(buff,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%d",
	 &starttime,&totaltime,&T_ini,&rr,&rr_kyoyou,&zatuon_keisoku,&zatuon_alpha,&zatuon_TO,&zatuon_vS,&zatuon_rho_r,&zatuon_C_r,&iteration);
  //090604yuno
  if(_iteration>0) iteration=_iteration;
  SV=rr*YB;
  AP_KyoyouOndoGosa=rr_kyoyou;
  printf("***starttime=%lf,totaltime=%lf,rr=%lf,T_ini=%lf,zatuon=%lf,%lf,%lf,%lf",
	 starttime,totaltime,T_ini,rr,zatuon_keisoku,zatuon_alpha,zatuon_TO,zatuon_vS);
  for(;;){fgets(buff,buffsize,fp); if(buff[0]!='#') break;}
  sscanf(buff,"%d%d%d%d%d",&C_MODE,&PP,&II,&DD,&checkmode);
  CHG.b.P=1;  CHG.b.I=1;  CHG.b.D=1;/* for AROM_PID*/
  kp=100.0/PP;ki=kp/(double)(II<<SHIFT);kd = kp*(double)(DD<<SHIFT)/(1+(DD<<SHIFT));/* for NORM_PID*/
  if(C_MODE==AT_APC) ATF.b.AT_APC_F=1;
  else ATF.b.AT_APC_F=0;
  fclose(fp);
  /************************/
  S=PI*(R2/2.)*(R2/2.);
  v=vS/S;
  LT=(VH+VB)/S+LH0+LB0;
  VT=LT*S;
  LB=VB/S;
  LH=VH/S;
  tH=LH0/v;
  tB=LB0/v;
  tT=LT/v;
  kH=tH/AP_tS;
  kB=tB/AP_tS;
  kT=tT/AP_tS;
  kD=tD/AP_tS;
  if(tauD<AP_ZERO) etauD=1;
  else etauD=exp(-AP_tS/tauD);
  printf("LB=%f,%f,%f\n",LB,LH,VB);
  printf("LT=%f,LH=%f,tH=%f,tB=%f,tT=%f,kH=%d,kB=%d,kT=%d\n",LT,LH,tH,tB,tT,kH,kB,kT);

  int stocksize=2*(double)tT/(double)AP_tS;
  TH0=(double *)malloc(stocksize*sizeof(double));
  TH1=(double *)malloc(stocksize*sizeof(double));
  TB0=(double *)malloc(stocksize*sizeof(double));
  TB=(double *)malloc(stocksize*sizeof(double));
  TH=(double *)malloc(stocksize*sizeof(double));
  p=(double *)malloc(stocksize*sizeof(double));
}

int myindex(int k,int stocksize)//090604yuno indexをmyindexに変更
{
  return((k+stocksize)%stocksize);
}

next_k()
{
  k++;
  k = myindex(k,buffsize);
  k_plus_1 = myindex(k+1,buffsize);
  k_minus_kT = myindex(k-kT,buffsize);
  k_minus_kH = myindex(k-kH,buffsize);
  k_minus_kB = myindex(k-kB,buffsize);
  k_minus_kD = myindex(k-kD,buffsize);
}

//next_k_orig()
//{
//  k++;
//  k = (k+buffsize)%buffsize;
//  k_plus_1 = (k+1+buffsize)%buffsize;
//  k_minus_1 = (k-1+buffsize)%buffsize;
//  k_minus_kT = (k-kT+buffsize)%buffsize;
//  k_minus_kH = (k-kH+buffsize)%buffsize;
//  k_minus_kB = (k-kB+buffsize)%buffsize;
//}

int iiiii=0;  
double ppk=0,aaa=0.999;
double ppkH=0,bbb=0.999,uuH;
double ppkB=0,ccc=0.999,uuB,aB04;
double ALPHAH=1,ALPHAB=1;
double plant(double uu)//  double uu;
{
  double aBP;
  if(iiiii==0){
    iiiii=1;
    rho1=rho0*rho_01;
    C1=C0*C_01;
    rho2=rho0*rho_02;
    C2=C0*C_02;
    rho_r=(r1*rho1+r2*rho2)/(r1+r2);
    C_r=(r1*C1+r2*C2)/(r1+r2);
    rho_0r=rho_r/rho0;
    C_0r=C_r/C0;
    alphaO=Pinf/(rho_r*C_r*VB*(TBinf-TO));    /*    alphaO=3.382581e-04;*/
    ppk=ppkH=ppkB=0;/*入力パワー初期値*/
    MA=MAT=rho_r*VT;/*総質量*/
    printf("alphaO=%e,%e,===%e\n",alphaO,alphaO*rho_r*C_r,Pinf/(rho_r*C_r*TBinf));
    ALPHAH=ALPHAB=1;
  }
  _alpha=alphaO*(1.+zatuon_alpha);/**/
  _vS=vS*(1.+zatuon_vS*sin(2.*PI*time));/*1秒おきに脈動*/
  _rho_r=rho_r;
  _C_r=C_r;
  aHH=exp(-AP_tS*_vS/VH);
  aHB=(1-aHH);
  aHP=(1-aHH)/(_vS*_rho_r*(1.+zatuon_rho_r*TH[k])*_C_r);
  aBB=exp(-AP_tS*(_alpha+_vS/VB));
  aBH=(1-aBB)*(_vS/VB)/((_vS/VB)+_alpha);
  aB0=(1-aBB)*_alpha/((_vS/VB)+_alpha);
  aBP=(1-aBB)*(1./(VB*_rho_r*(1.+zatuon_rho_r*TB0[k])*_C_r))/((_vS/VB)+_alpha);
  /*自己発熱*/
  if(lnKo>0 && (ALPHAH>0 || ALPHAB>0)){
    double dALPHAH,dALPHAB,B_H;
#ifdef ORIG
    dALPHAH=exp(lnKo-Ea/R/(TH[k] +TK))*pow(ALPHAH,n_ALPHA)*AP_tS;
    dALPHAB=exp(lnKo-Ea/R/(TB0[k]+TK))*pow(ALPHAB,n_ALPHA)*AP_tS;
    dALPHAH =(dALPHAH*(VH+LH0*S)+(dALPHAB-dALPHAH)*_vS*AP_tS)/(VH+LH0*S);
    dALPHAB =(dALPHAB*(VB+LB0*S)+(dALPHAH-dALPHAB)*_vS*AP_tS)/(VB+LB0*S);
    if(ALPHAH-dALPHAH<=0) {dALPHAH=ALPHAH;}
    if(ALPHAB-dALPHAB<=0) {dALPHAB=ALPHAB;}
    ALPHAH -=dALPHAH;
    ALPHAB -=dALPHAB;
    uuH = dH*dALPHAH*_rho_r*(1.+zatuon_rho_r*TH[k])*(VH+LH0*S)/AP_tS;
    uuB = dH*dALPHAB*_rho_r*(1.+zatuon_rho_r*TB0[k])*(VB+LB0*S)/AP_tS;
#else
    dALPHAH=exp(lnKo-Ea/R/(TH[k] +TK))*pow(ALPHAH,n_ALPHA)*AP_tS;
    dALPHAB=exp(lnKo-Ea/R/(TB0[k]+TK))*pow(ALPHAB,n_ALPHA)*AP_tS;
    uuH = dH*dALPHAH*_rho_r*(1.+zatuon_rho_r*TH[k])*(VH+LH0*S)/AP_tS;
    uuB = dH*dALPHAB*_rho_r*(1.+zatuon_rho_r*TB0[k])*(VB+LB0*S)/AP_tS;
    B_H=ALPHAB-ALPHAH;
    dALPHAH = -dALPHAH +B_H*_vS*AP_tS/(VH+LH0*S);
    dALPHAB = -dALPHAB -B_H*_vS*AP_tS/(VB+LB0*S);
    if(ALPHAH+dALPHAH<=0) ALPHAH=0; else ALPHAH +=dALPHAH;
    if(ALPHAB+dALPHAB<=0) ALPHAB=0; else ALPHAB +=dALPHAB;
#endif
  }
  else {
    uuH=uuB=0;
  }
  aaa=bbb=ccc=0.9917;/**/
  aaa=bbb=ccc=0.0;/**/
  ppkH=bbb*ppkH+(1.-bbb)*(uuH);
  ppkB=ccc*ppkB+(1.-ccc)*(uuB);
  ppk=aaa*ppk+(1.-aaa)*uu;
  /*自己発熱は以上*/
  
  TH[k_plus_1]=aHH*TH[k]+aHB*TB0[k_minus_kB]+aHP*(ppk+ppkH);
  TB0[k_plus_1]=aBB*TB0[k]+aBH*TH[k_minus_kH]+aB0*_TO+aBP*ppkB;
  TB[k_plus_1]=TB0[k_minus_kD];
  return(TB[k_plus_1]);
}
#define AROMPID/**/
#ifdef AROMPID
/*== for calc_pid() original============================*/
void rst_pid()
{
  U1K = 0.0;
  U2K = 0.0;
  U2K_1 = 0.0;
  SM0 = 0.0;
  SMN = 0.0;
  UM0 = 0.0;
  UMN = 0.0;
  SEK0 = 0;
  SEK1 = 0;
}
/*======================================================*/
void	calc_pid(void)		/*  ＰＩＤ演算		*/
     /*======================================================*/
     /*	入力  ：  センサ温度 	PV1			*/
     /*	出力  ：  操作量	SMV			*/
     /*======================================================*/
{
  WORD 	err;		/* 偏差 			*/
  double 	ek0,ek1;
  double kuro;
  
  SEK1 = SEK0;		/* 1サイクル前の偏差 */
  SEK0 = err = SSV - PV1;	/* 現在の偏差 */
  /*---------------------------------------------------*/
  ek0 = (double)SEK0;
  ek1 = (double)SEK1;
  /*---------------------------------------------------*/
  if(CHG.b.P){		/* 比例ゲイン */
    CHG.b.P = 0;
    KK = 100.0/(double)PP;
  }
  /*---------------------------------------------------*/
  if(CHG.b.I){
    CHG.b.I = 0;
    if(II == 0){
      KI = 0.0;
      U2K = U2K_1 =0.0;
    }else{
      KI = 1/(double)(II<<SHIFT);
      UM0 = UMN = 0.0;
    }
  }
  /*----------------------------------------------*/
  if(CHG.b.D){
    CHG.b.D = 0;
    KD = (double)(DD<<SHIFT)/(1+(DD<<SHIFT));
  }
  if(abs(err) > PP){		/* バンドチェック */
    SM0 = (err>0) ? M_MAX : M_MIN;
    UM0 = 0.0;
    U1K = U2K = U2K_1 =0.0;
  }else{
    /*  不完全微分のゲイン n = 1.0 */
    /*  sampling time T = 0.25 */
    U1K = KK * ek0;		/* 比例 */
    U2K = U2K_1 + (KK * KI * ek0);	/* 積分項 */
    
    /*-------------  不完全微分 --------------*/
    UM0 = KD * (UMN + KK * 1 * (ek0 - ek1));
    
    if(U1K > M_MAX){		
      U1K=M_MAX;	/* 比例項リミット */
    }
    else if(U1K < M_MIN)
      U1K=M_MIN;
    
    if(U2K > M_MAX)
      U2K=M_MAX;	/* 積分項リミット */
    else if(U2K < -200)
      U2K=-200;
    U2K_1 = U2K;
    
    if(UM0 > M_MAX)
      UM0=M_MAX;	/* 微分項リミット */
    else if(UM0 < -200)
      UM0=-200;
    UMN = UM0;
    
    SM0 = U1K + U2K + UM0;
  }
  /*------------------------------------------------*/
  if(SM0 > M_MAX){	/* 操作量 の Limit Check */
    SM0 = M_MAX;	/* 操作量をクランプする */
  }else if(SM0 < M_MIN){
    SM0 = M_MIN;	/* 操作量をクランプする */
  }
  SMN = SM0;		/* 内部状態の保存 */
  SMV = SM0;		/* 操作量 */
}
#endif/*#ifdef AROMPID*/
#ifdef NORMPID
void rst_pid()
{
  e_PID_k_minus_2=0;
  e_PID_k_minus_1=0;
  e_PID_k=0;
  u_PID_k_minus_1=0;
  u_PID_k=0;
}
void calc_pid() 
     /*======================================================*/
     /*	入力  ：  センサ温度 	PV1			*/
     /*	出力  ：  操作量	SMV			*/
     /*======================================================*/
{
  
  e_PID_k_minus_2=  e_PID_k_minus_1;
  e_PID_k_minus_1=  e_PID_k;
  u_PID_k_minus_1= u_PID_k;
  
  e_PID_k= rr-PV1/YB;/**/
  u_PID_k=u_PID_k_minus_1
    + kp*(e_PID_k-e_PID_k_minus_1)
    + ki*e_PID_k 
    + kd*(e_PID_k-2.*e_PID_k_minus_1+e_PID_k_minus_2);
  if(u_PID_k>AP_u_max) u_PID_k=AP_u_max;
  else if(u_PID_k<0) u_PID_k=0;
  SMV=u_PID_k;
}
#endif

int jjjjj=0;
FILE *fp;
char buff[buffsize];


// ***************  050704 tomisaki ******************************
//学習データの範囲を変更する関数 :ms_train.dat->rs_train.dat
void make_rs(void)
{
  FILE *fp1,*fp2,*fp3,*fp4;
  double data_time;
  int endloop,loop_c;
  char buff2[buffsize];


  data_time = stable_time;
  if(data_time >= totaltime)data_time=totaltime;
  if(seiteijikoku == -1) data_time=totaltime;
  printf("data_time : %f\n",data_time);

    if((fp1=fopen(fntrain,"r"))==NULL){
      printf("error when open the file (%s).\n",fntrain);
      fclose(fp1);
      exit(1);
    }
    if((fp3=fopen("rs_train.dat","w+"))==NULL){
      printf("error when open the file rs_train.dat.\n");
      fclose(fp3);
      exit(1);
    }
    if((fp4=fopen("rs_test.dat","w+"))==NULL){
      printf("error when open the file rs_test.dat.\n");
      fclose(fp4);
      exit(1);
    }

    for(endloop=160; endloop<=data_time; endloop++){
      for(loop_c=0; loop_c<4; loop_c++){//4回で1秒
	if((fgets(buff2,buffsize,fp1))!=NULL){
	  fputs(buff2,fp3);
	}
      }
      fputs(buff2,fp4);
    }
  
 fclose(fp1);
 fclose(fp3); 
 fclose(fp4);

}

// 050713 tomisaki
// .datファイルを合成しトレーニングデータも同時に作成する。
void make_file_dat(char **file)
{
  int i_file,count8=0;
  FILE *fp1,*fp2,*fp3;
  char ma_file_name[]="file_add.dat";
  char buff2[buffsize];

  //学習データを追加記入でオープン
  if((fp2=fopen(fntrain,"a+"))==NULL){
    printf("error : cannot open %s\n",fntrain);
    exit(1);
  }
  if((fp3=fopen(fntest,"a+"))==NULL){
    printf("error : cannot open rs_test.dat\n");
    exit(1);
  }

  //fileの中のデータをあわせる
  for(i_file=0;i_file<add_data_N;i_file++){
    if((fp1=fopen(*(file+add_dat[i_file]),"r"))==NULL){
      printf("error : cannot open %s\n",*(file+add_dat[i_file]));
      exit(1);
    }
    
    while((fgets(buff2,buffsize,fp1))!=NULL){
      fputs(buff2,fp2);
      if(count8==0 || count8==9){
	fputs(buff2,fp3);
	count8=0;
      }
      count8++;
    }
    fclose(fp1);
  }//for(i=1;...)

  fclose(fp2);
  fclose(fp3);
}


/*************************************************/

outer_world()
{
  double min_MSE;
  int min_cell;
  float MSE[100];
  int cell[100];
  FILE *fp1;
  FILE *fp2;
  FILE *fp3;
  FILE *fp4;
  FILE *fp5;
  FILE *fp6;  
  FILE *fp7;
  FILE *fpy;
  //090622 yuno
  FILE *fpym; //2007/10/09 koshi
  FILE *fpsn;  //081023 koshi

  int net_yu =AP_nu+AP_ny,yu,l;//yuno071203
  int hi;//080131yuno 
  int net_s,net_i;//080305koshi   //090622 yuno
  int m,bag_m,boost_m,net_m;

  char cmd[cmdsize];
  char fn[fnsize];

  GET_PV_DATA=1;
  if(jjjjj==0){/*初めにready_AP()を呼ぶ*/
    jjjjj=1;
    MODE_TYPE=STD_MODE;
    RUN=0;/*初めにready_AP()を呼ぶため*/
    AP_tau=0;AP_0=0;AP_RESET_T=0;AP_THHS=0;/*非マニュアル??*/
    PP=1;/*mainルーティンでAPCを呼ぶため*/
    AP_u_ave=0;
    return;
  }
  if(jjjjj==1){
    jjjjj=2;

    initialize();
    C_250MS=0;
    MODE_TYPE=STD_MODE;/*???*/
    RUN=0;
    /*PP=1;/*mainルーティンでAPCを呼ぶため*/

    kk1=(AP_tS1+starttime+1)/AP_tS;
    k=0;
    kS1=AP_tS1/AP_tS;/*300s=5min*/
    buff_y=(double *)malloc((int)((totaltime/AP_tS+kS1*(AP_NN-2)+Np+1)*sizeof(double)));
    buff_u=(double *)malloc((int)((totaltime/AP_tS+kS1*(AP_NN-2)+Np+1)*sizeof(double)));
    y=&buff_y[kS1*(AP_NN-2)];
    u=&buff_u[kS1*(AP_NN-2)];
    for(kk=0;kk<kk1;kk++){
      buff_y[kk]=T_ini;               /*初期温度*/
      buff_u[kk]=0;
    }
    for(k=0;k<buffsize;k++){
      TH[k]=TH[k]=TB0[k]=TB[k]=TB1=T_ini;/*初期温度*/
      p[k]=0.0;
    }
    overshoot=undershoot=maxTB=0;
    seiteijikoku=-1;
    /****/

    time=0;

    if((fpy=fopen("y.dat","w+"))==NULL){
      exit(1);
    }
    fprintf(fpy,"#time TB TH yy  TH-TB TH0 TH1 TB0 \n");
    fprintf(fpy,"%f %f %f %f %f %f %f %f %f %f\n",
    		     time,TO,TO,0,0,0,0,0,0,0);
    fclose(fpy);

    //090622 yuno
     /* ***連想行列をファイル書き込む 2007/10/09 koshi ****/
    if((fpym=fopen("./y_matrix.dat","w+"))==NULL){
      exit(1);
    }
    if((uni_flag==1)&&(nuse_flag==1)){
      fprintf(fpym,"#time M[0][0] M[0][1] M[0][2] M[0][3] M[0][4] M[0][5] M[0][6] # ");
      for(hi=1;hi<=num_nets;hi++){
	fprintf(fpym,",st_n_AP_i[%d]",hi);
      }
      for(hi=1;hi<=num_nets;hi++){
	fprintf(fpym,",mse[%d]",hi);
      }
      fprintf(fpym,",sellected_net");
      for(hi=1;hi<=num_nets;hi++){
	fprintf(fpym,", err in time[%d]",hi);
      }
      for(hi=1;hi<=num_nets;hi++){
	fprintf(fpym,", err in save_time[%d]",hi);
      }
      fprintf(fpym,", save_time");
      fprintf(fpym,"\n");
    }
    

    else if((uni_flag==1)&&(nuse_flag==0)){
      fprintf(fpym,"#time M[0][0] M[0][1] M[0][2] M[0][3] M[0][4] M[0][5] M[0][6] # ");
      
      fprintf(fpym,",sellect_net");
      fprintf(fpym,"\n");
    }


    else{
      fprintf(fpym,"#time M[0][0] M[0][1] M[0][2] M[0][3] M[0][4] M[0][5] M[0][6] #");
      fprintf(fpym," sellected_net");
      fprintf(fpym," error in time");
      fprintf(fpym,"\n");
    }

    fclose(fpym);

    kk=0;
    //040120kuro
    if((fptrain=fopen(fntrain,"w+"))==NULL){
      printf("error when open the file (%s).\n",fntrain);
      exit(1);
    }
    if((fptest=fopen(fntest,"w"))==NULL){
      printf("error when open the file (%s).\n",fntest);
      exit(1);
    }
  }
  kk++;
  time=kk*AP_tS;
  next_k();
  if(RUN==0 && kk>=starttime/AP_tS){
    RUN=1;

    PV1=25*YB;
    SV=rr*YB;
    if(C_MODE==NORM_PID){/*PID*/
      rst_pid();
    }
    else if(AT_FLAG==2){/*APC*/
      
#ifndef MSPC
      AP_y_under=rr_under;
      AP_u_res=u_res;
#endif
      reinit_AP();/**/
    }
    else if(C_MODE==DEF_APC||C_MODE==SPM_APC||C_MODE==SC2_APC){
      reinit_AP();/**/
    }
    else if(C_MODE==AT_APC){/*New ATモード */
      AP_tau=2500;
      AP_0=1000.0;
      AP_RESET_T=8500;
      AP_THHS=0.0001*100000/AP_tS;
      AP_THHS=0.001*100000/AP_tS;
      reinit_AP();/**/
    }
  }
  if(checkmode==2){/*time<1500で30℃ time>1500から80℃，time>4500から75℃に*/
    if(time>0){
      if(jjjjj==2){
	jjjjj=3;
	rr=30;
	SV=rr*YB;/*目標値変化*/
	CHG.b.SV=1;/*on_change_AP_r()を呼ぶため*/
      }
      else if(jjjjj==3){
	jjjjj=4;
	CHG.b.SV=0;/*on_change_AP_r()をもう呼ばない*/
      }
    }
    if(time>2000){
      if(jjjjj==4){
	jjjjj=5;
	rr=80;
	SV=rr*YB;/*目標値変化*/
	CHG.b.SV=1;/*on_change_AP_r()を呼ぶため*/
      }
      else if(jjjjj==5){
	jjjjj=6;
	CHG.b.SV=0;/*on_change_AP_r()をもう呼ばない*/
      }
    }
    if(time>5000){
      if(jjjjj==6){
	jjjjj=7;
	rr=75;
	SV=rr*YB;/*目標値変化*/
	CHG.b.SV=1;/*on_change_AP_r()を呼ぶため*/
      }
      else if(jjjjj==7){
	jjjjj=8;
	CHG.b.SV=0;/*on_change_AP_r()をもう呼ばない*/
      }
    }
  }
  /*********/
  if(RUN==0) p[k]=0;
  else p[k]=(double)Pmax*SMV/M_MAX;
  {
    double t0=500,t00=400;
    if(time<1)TH[k_plus_1]=TB[k_plus_1]=TB0[k_plus_1]=T_ini;/*初期温度*/
    else{
      plant(p[k]);
      /* TB1は遅れ有り温度センサ出力？*/
      TB1=etauD*TB1+(1.-etauD)*TB0[k_minus_kD]
	+((2.*myrandom()-1.)*0.00)/*測定雑音:不思議な現象0.003以上にすると操作量振動が小さくなる*/
	+zatuon_keisoku*sin(2.*PI*time/50.);/**/
      TB1=(int)(TB1/0.0001)*0.0001;/*bit落ち？温度計出力の精度*/
      PV1 = 0.0*PV1+1.0*(double)YB*((int)(TB1/0.01)*0.01)+YB*((2.*myrandom()-1.)*0.02);/**/
    }
  }
  AP_u_ave=0.9999*AP_u_ave +0.0001*AP_u; 
  if(checkmode==1){/*time>4000で水槽温度を4℃低くする*/
    if(time>=5000){
      if(jjjjj==2){
	jjjjj=3;
	TB0[k_plus_1]=TB0[k_plus_1]-4.0;
	TH[k_plus_1]=TB0[k_plus_1];/**/
	rho_01 *= 0.9;
	rho_02 *= 0.9;
	C_01 *=1.9;
	C_02 *=1.9;
	VB +=0.00055;

	LT=(VH+VB)/S+LH0+LB0;
	VT=LT*S;
	LB=VB/S;
	LH=VH/S;
	tH=LH0/v;
	tB=LB0/v;
	tT=LT/v;
	kH=tH/AP_tS;
	kB=tB/AP_tS;
	kT=tT/AP_tS;
	rho1=rho0*rho_01;
	C1=C0*C_01;
	rho2=rho0*rho_02;
	C2=C0*C_02;
	rho_r=(r1*rho1+r2*rho2)/(r1+r2);
	C_r=(r1*C1+r2*C2)/(r1+r2);
	rho_0r=rho_r/rho0;
	C_0r=C_r/C0;
	alphaO=Pinf/(rho_r*C_r*VB*(TBinf-TO));
      }
    }
  }
  /**/
  /*********/
  yyy=PV1/YB;
  if(time <5000){
    if(seiteijikoku<0 && fabs(yyy-rr)<=rr_kyoyou) seiteijikoku=time;
    else if(seiteijikoku>0 && fabs(yyy-rr)>rr_kyoyou) seiteijikoku=-1;
    if(yyy>maxTB) maxTB=yyy;
    if(yyy-rr>overshoot) overshoot=yyy-rr;
    if(overshoot>0&&rr-yyy>undershoot) undershoot=rr-yyy;/**/
  }
  if(checkmode==1){  
    if(time>5000){
      if(dis_seitei<0 && fabs(yyy-rr)<=2) dis_seitei=time;/*外乱速応性*/
      else if(dis_seitei>0 && fabs(yyy-rr)>2) dis_seitei=-1;
    }
  }
  {
    double yy=0;
    if(difference_flag==1){//2007/10/07 koshi 
      yy+=net[0].cell[AP_i].M[0][0]*AP_z[0]+AP_z[AP_nu+2];
      for(i=1;i<=AP_nu;i++) yy+=net[0].cell[AP_i].M[0][i]*(AP_uu[i]-AP_uu[i+1]);
      for(i=1;i<=AP_ny;i++) yy+=net[0].cell[AP_i].M[0][i+AP_nu]*(AP_yy[i]-AP_yy[i+1]);
    }
    else{
      for(i=0;i<AP_NN;i++) yy+=net[0].cell[AP_i].M[0][i]*AP_z[i];
    }
    if(debug==1){/*for debug*/
    }
    if(kk==290){
    }

    if(debug==1 ||kk%(int)(1./AP_tS)==0){/**/
      if(kk==0){error_hyouka=0.0;}
      error_hyouka+=pow((AP_r - AP_y)*0.25, 2);

      if((fpy=fopen("y.dat","a+"))==NULL){//2006/11/30kuwa
	exit(1);
      }
      if(ensemble==0){
	fprintf(fpy,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %f %f %d %f | %f %f %f %f\n",
		time,
		PV1/YB,
		TH[k_plus_1],
		p[k]/Pmax*100,/**/
		yy,//5
		TH[k_plus_1]-TB[k_plus_1],
		AP_r,
		AP_y,//8
		(1.+AP_i)*100/AP_NC,/*774s以前のセルも表示できる*/
		(1.-ALPHAB)*100.,
		AP_r+2, //11 
//090608 yuno
#ifdef NEWenergy
		energy_sum*10000/AP_kk,/*energy=energy_sum/AP_kk*/
#else
		energy*50*100,//energy=energy_sum/AP_kk
#endif
		AP_yyy, 
		dis_seitei,
		AP_i,
		error_hyouka,//16
		pow((AP_r - AP_y),2),
		code,//18
		u_old/M_MAX*100,
		net[0].cell[AP_i].M[0][0], 
		net[0].cell[AP_i].M[0][1], 
		net[0].cell[AP_i].M[0][2], 
		net[0].cell[AP_i].M[0][3]
		);
      }//end of if(ensemble==0)
      fclose(fpy);
    
      /***********************************************************************///090622 yuno
      if((fpym=fopen("y_matrix.dat","a+"))==NULL){//2007/10/09 koshi
	exit(1);
      }

      if(ensemble==0){
	if((uni_flag==1)&&(nuse_flag==1)){
	  fprintf(fpym,"%f ",time);
	  for(hi=0;hi<AP_NN;hi++){
	    fprintf(fpym,"%f ",net[0].cell[AP_i].M[0][hi]);
	      }
	  for(hi=1;hi<=num_nets;hi++){
	    fprintf(fpym,"%d ",st_n_AP_i[hi]);
	  }
	  for(hi=1;hi<=num_nets;hi++){
	    fprintf(fpym,"%e ",energy_n[hi]*5000);
	  }
	  fprintf(fpym,"%d ",AP_n_out);
	  for(hi=1;hi<=num_nets;hi++){
	    fprintf(fpym,"%e ",mse[hi][AP_n_kk]);
	  }
	  for(hi=1;hi<=num_nets;hi++){
	    fprintf(fpym,"%e ",n_err[hi]);
	  }
	  fprintf(fpym,"%d ",save_time);
	  
	  fprintf(fpym,"\n");
	}//end of if((uni_flag==1)&&(nuse_flag==1))
	else if((uni_flag==1)&&(nuse_flag==0)){
	  fprintf(fpym,"%f ",time);
	  for(hi=0;hi<AP_NN;hi++){
	    fprintf(fpym,"%f ",net[0].cell[AP_i].M[0][hi]);
	      }
	  fprintf(fpym,"# ");
	  fprintf(fpym,"%d ",AP_n_out);
	  fprintf(fpym,"\n");
	}//end of else if((uni_flag==1)&&(nuse_flag==0))
	else{
	  fprintf(fpym,"%f ",time);
	  for(hi=0;hi<AP_NN;hi++){
	    fprintf(fpym,"%f ",net[0].cell[AP_i].M[0][hi]);
	  }
	  fprintf(fpym,"%d ",AP_i);
	  fprintf(fpym,"%e ",energy_n1[0]*energy_n1[0]);
	  fprintf(fpym,"\n");
	}
      }//end of if(ensemble==0)
      fclose(fpym);
    }//end of if(debug==1 ||kk%(int)(1./AP_tS)==0)
  }
  
  if(kk>=totaltime/AP_tS){
    if(1==0){  
      int n,i,j;  
      for(n=0;n<AP_NC;n++) {  
       i=0;    printf("%+9.3f&",net[0].cell[n].M[0][i]*AP_z[0]);  
       for(j=1;j<=AP_ny;j++) printf("%+9.3f&",net[0].cell[n].M[0][j+AP_nu]);      
       for(j=1;j<AP_nu;j++) printf("%+9.3f&",net[0].cell[n].M[0][j]); 
       j=AP_nu;printf("%+9.3f\\\\\n",net[0].cell[n].M[0][j]);  
     }  
     for(n=0;n<AP_NC;n++){  
       if(n==0) printf("if(n==%d){\n",n);  
       else printf("}else if(n==%d){\n",n);  
       printf("net[0].cell[n].v=%d;\n",net[0].cell[n].v);  
       for(i=0;i<AP_NN;i++) printf("net[0].cell[n].M[0][%d]=%+e;\n",i,net[0].cell[n].M[0][i]);  
       for(i=0;i<AP_NN;i++){  
	 for(j=0;j<AP_NN;j++) printf("net[0].cell[n].Q[%d][%d]=%+e;\n",i,j,net[0].cell[n].Q[i][j]);  
       }  
     } 
     printf("}\n",n);  
     printf("else \n"); 
     printf("#endif\n");
     
     printf("}\n",n);
     for(n=0;n<AP_NC;n++){
       printf("%d\n",net[0].cell[n].v);
       for(i=0;i<AP_NN;i++){
	 for(j=0;j<AP_NN;j++) printf("% e",net[0].cell[n].Q[i][j]);
	 printf("\n");
       }
       for(i=0;i<AP_NN;i++) printf("% e",net[0].cell[n].M[0][i]);
       printf("\n");
     }
   }
   
//090608 yuno
#ifdef MSPC
    fprintf(stdout,"lambda=%g= %g*%g*1e-5/%g\n",lambda,(double)AP_N2,(double)AP_LAMBDA,(double)AP_NU);
#ifdef NEWenergy
    printf("%d %f %f %f %f it,TS,OS,Em,Um\n",
	   it,seiteijikoku-starttime,overshoot,energy_sum/AP_kk*10000.,energy_sum/AP_kk*10000.);
    printf("%d)SeiteiJikan=%f,OS=%f,US=%f,max=%f,init_err=%f,tra_allerr=%f,mid_allerr=%f,ste_allerr=%f,allerr=%f,saishokika=%d,E_mean=%f,dis_seitei=%f\n",it,
	   seiteijikoku-starttime,overshoot,undershoot,AP_u_max,init_err,tra_allerr,mid_allerr,ste_allerr,allerr,n_of_saishokika,energy_sum/AP_kk*10000.,dis_seitei-5000);
#else
    printf("%d %f %f %f it,TS,OS,Em\n",
	   it,seiteijikoku-starttime,overshoot,energy_mean/AP_kk*50*100);
    printf("%d)SeiteiJikan=%f,OS=%f,US=%f,max=%f,init_err=%f,tra_allerr=%f,mid_allerr=%f,ste_allerr=%f,allerr=%f,saishokika=%d,E_mean=%f,dis_seitei=%f\n",it,
	   seiteijikoku-starttime,overshoot,undershoot,AP_u_max,init_err,tra_allerr,mid_allerr,ste_allerr,allerr,n_of_saishokika,energy_mean/AP_kk*50*100,dis_seitei-5000);
#endif
#else
   printf("SeiteiJikan=%f,OS=%f,US=%f,tau=%f(%f),max=%f,under=%f\n",
	  seiteijikoku-starttime,overshoot,undershoot,AP_y_smooth_tau,AP_y_smooth_r,AP_u_max,0);
#endif


#ifndef MSPC
   if(C_MODE==AT_APC){
     double tau2, P2,t100;
     printf(" ymin=y(%4.0f)=%f\n  y10=y(%4.0f)=%f\n  y50=y(%4.0f)=%f\n  y80=y(%4.0f)=%f\n ymax=y(%4.0f)=%f\ny80-1=y(%4.0f)=%f\n",
	    AP_AT_j[0],AP_AT_y[0],
	    AP_AT_j[1],AP_AT_y[1],
	    AP_AT_j[2],AP_AT_y[2],
	    AP_AT_j[3],AP_AT_y[3],
	    AP_AT_j[4],AP_AT_y[4],
	    AP_AT_j[5],AP_AT_y[5]);
     t100=(AP_AT_j[3]-AP_AT_j[2])*20/(80-50)+AP_AT_j[3];
     printf("t100=%f,(ymax-y80)=%f,hokan=%ld\n",t100,(AP_AT_y[4]-AP_AT_y[3]),
	     AP_tau,AP_AT_Np_opt,hokan((LONG)(100*(AP_AT_y[4]-AP_AT_y[3])),
				       (LONG *)&AP_AT_TBL[0][0], AP_AT_TBL_N ));
     calc_AP_tau();
     printf("Calculated AP_tau=%d,AP_Np=%d,KyoyoOndo=%d,SyoYoJikan=%5.0f(%5.0f-%5.0f),Seitei5-3=%5.0f<%d?\n",
	    AP_tau,AP_AT_Np_opt,AP_KyoyouOndoGosa,
	    AP_AT_shuryojikan-AP_AT_kaishijikan,
	    AP_AT_shuryojikan,AP_AT_kaishijikan,
	    AP_AT_seiteijikan_saitan,AP_tau);
     overshoot=(AP_AT_y[4]-AP_AT_y[3]);
   }
#endif //#ifndef MSPC
   /******/    
   if((fp=fopen("y.plt","wt+"))==NULL){
     printf("File(y.plt) Open Eoor\n");
     fclose(fp);
     return;
   }

   //090622 yuno
  //081023 koshi
   if(uni_flag==1){
     if((fpsn=fopen("selected_net.plt","wt+" ))==NULL){
       printf("File(selected_net) Open Error\n");
       fclose(fpsn);
       return;
     }
   }



#ifdef LINUX
   if((it==iteration-1)||DISP){
     //   if((it==iteration-1)|| (it%DISP==1)){
   //   if(it==iteration-1){
     system("cp y.dat _y.dat");
     fprintf(fp,"set terminal x11\n");
     fprintf(fp,
	     "set title \"it%d: Mokuhyo=%4.1f,RyuSoku=%4.1f,O.S.=%4.1f,U.S.=%4.1f,Seite iJikan=%5.0f,HiJu=%4.1f,Hinetu=%4.1f\"\n",it,rr,vS*60000,overshoot,undershoot,seiteijikoku-starttime,rho_0r,C_0r);
     fprintf(fp,"set xlabel \"t[s]\"\n");
     fprintf(fp,"set ylabel \"Temperature[deg]/Power Rate[%s]\"\n","%");
     fprintf(fp,"set data style linespoints\n");
     fprintf(fp,"set data style lines\n");
     fprintf(fp,"#set grid\n");
     fprintf(fp,"set parametric\n");
     fprintf(fp,"set yrange [0:140]\n");
     fprintf(fp,"#set yrange [132:138]\n");
     fprintf(fp,"#set yrange [115:140]\n");
     fprintf(fp,"set ytics (0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200)\n");
     fprintf(fp,"#\n");
     fprintf(fp,"plot \"_y.dat\" using 1:4 title \"P/Pmax[%s]\", \"_y.dat\" using 1:7 title \"Tr^\", \"_y.dat\" using 1:2 title \"T_B[deg]\",\"_y.dat\" using 1:12 title \"Energy\"\n","%");
     fprintf(fp,"#\n");
     fprintf(fp,"pause -1 \"it%d: Hit 'return' to continue. Type C-c C-z, 'kill %1' on emacs shell to quit.\"\n",it);
     fprintf(fp,"set terminal tgif;set output \"y.obj\";replot\n");
     //     fprintf(fp, "#\n");
     //     fprintf(fp,"plot \"_y.dat\" using 1:4 title \"P/Pmax[%s]\", \"_y.dat\" using 1:7 title \"Tr^\", \"_y.dat\" using 1:2 title \"T_B[deg]\",\"_y.dat\" using 1:12 title \"Energy\"\n","%");
     fclose(fp);
     system("xterm -geometry 40x5+0+0 -e gnuplot -geometry 300x240-0+0 y.plt&");
    //090622 yuno
     if(uni_flag==1){
       system("cp y_matrix.dat _y_matrix.dat");
       /*****選択されたネットの表示 081023koshi******/
       fprintf(fpsn,"set terminal x11\n");
       fprintf(fpsn,"set xlabel \"t[s]\"\n");
       fprintf(fpsn,"set ylabel \"Sellected net\"\n");
       fprintf(fpsn,"set data style points\n");
       fprintf(fpsn,"set parametric\n");
       fprintf(fpsn,"set yrange [0:%d]\n",num_nets+1);
       fprintf(fpsn,"set ytics 1\n");
       fprintf(fpsn,"plot \"_y_matrix.dat\" using 1:%d title \"selected_net\"",AP_NN+2*num_nets+2);
       fprintf(fpsn,"#\n");
       fprintf(fpsn,"pause -1 \"Hit 'return' to continue. Type C-c C-z, 'kill %1' on emacs shell to quit.\"\n");
       fprintf(fpsn,"set terminal tgif\n");
       fprintf(fpsn,"set output \"selected_net.obj\"\n");
       fprintf(fpsn, "#\n");
       fprintf(fpsn,"plot \"_y_matrix.dat\" using 1:%d title \"selected_net\"",AP_NN+2*num_nets+2);
       fclose(fpsn);
       
       //090608 yuno 
       system("xterm -geometry 40x5-0+0 -e gnuplot -geometry 300x240-0+0 selected_net.plt&"); 
     /***************************************************/
     }
   }
   
#else //end of #ifdef LINUX
#ifdef OLD1
   fprintf(fp,
	   "set title \"Mokuhyo=%4.1f RyuSoku=%4.1f OS=%3.1f US=%3.1f SeiteiJikan=%4.0f HiJu=%3.1f Hinetu=%3.1f\"\n"
	   "set data style linespoints\n"
	   "set data style lines\n"
	   "#set grid\n"
	   "set parametric\n"
	   "#set yrange [0:140]\n"
	   "set ytics (0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200)\n"
	   "#set xtics (%3.0f,500,1000,1500,2000,2500,3000,3500,4000,4500,5000)\n"
	   "set xlabel \"t[s]\"\n"
	   "set ylabel \"Temperature[deg]/Power Rate[%s]\"\n"
	   "plot \"y.dat\" using 1:2 title \"T_B[deg]\", \"y.dat\" using 1:4 title \"P/Pmax[%s]\", \"y.dat\" using 1:7 title \"Tr^\", \"y.dat\" using 1":9 title \"Cell\", \"y.dat\" using 1:10 title \"AlphaB\"\n"
#plot \"y.dat\" using 1:2 title \"TB[deg]\", \"y.dat\" using 1:3 title \"TH[deg]\", \"y.dat\" using 1:4 title \"P/Pmax[%s]\", \"y.dat\" using 1:5 title \"^TB[deg]\", \"y.dat\" using 1:6 title \"TH-TB[deg]\", \"y.dat\" using 1:7 title \"Tr^\", \"y.dat\" using 1:10 title \"AlphaB\"\n"
	   "pause 1 \"Hit return to quit\"\n"
	   "set terminal gif medium size 600,400 xffffff x000000 x404040 xff0000 x00ff00 x0000ff x66cdaa xcdb5cd xadd8e6 xdda0dd x9500d3\n"
	   "#set terminal gif small size 600,400 xffffff x000000 x404040 xff0000 xffa500 x66cdaa xcdb5cd xadd8e6 x0000ff xdda0dd x9500d3\n"
	   "set output \"y.gif\"\n"
	   "plot \"y.dat\" using 1:2 title \"T_B[deg]\", \"y.dat\" using 1:4 title \"P/Pmax[%s]\", \"y.dat\" using 1:7 title \"Tr^\", \"y.dat\" using 1:9 title \"Cell\", \"y.dat\" using 1:10 title \"AlphaB\"\n"
	   "#plot \"y.dat\" using 1:2 title \"T_B[deg]\", \"y.dat\" using 1:3 title \"T_H[deg]\", \"y.dat\" using 1:4 title \"P/Pmax[%s]\", \"y.dat\" using 1:10 title \"AlphaB\"\n"
	   ,rr,vS*60000,overshoot,undershoot,seiteijikoku-starttime,rho_0r,C_0r,starttime,"%","%","%","%","%");
   fclose(fp);
   system("wgnuplot y.plt;wait&");/**/
#endif //end of #ifdef OLD1
   fprintf(fp,
	   "set title \"Mokuhyo=%4.1f RyuSoku=%4.1f OS=%3.1f US=%3.1f SeiteiJikan=%4.0f HiJu=%3.1f Hinetu=%3.1f\"\n"
	   "set data style linespoints\n"
	   "set data style lines\n"
	   "set grid\n"
	   "set parametric\n"
	   "#set yrange [0:140]\n"
	   "set ytics (0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200)\n"
	   "//#set xtics (%3.0f,500,1000,1500,2000,2500,3000,3500,4000,4500,5000)\n"
	   "set xtics (%3.0f,500,1000,1500,2000,2500,3000,3500,4000,4500,5000)\n"
	   "set xlabel \"t[s]\"\n"
	   "set ylabel \"Temperature[deg]/Power Rate[%s]\"\n"
	   "plot \"y.dat\" using 1:2 title \"TB[deg]\", \"y.dat\" using 1:3 title \"TH[deg]\", \"y.dat\" using 1:4 title \"P/Pmax[%s]\", \"y.dat\" using 1:5 title \"^TB[deg]\", \"y.dat\" using 1:6 title \"TH-TB[deg]\", \"y.dat\" using 1:7 title \"Tr^\","
	   "pause 1 \"Hit return to quit\"\n"
	   "set terminal gif medium size 600,400 xffffff x000000 x404040 xff0000 x00ff00 x0000ff x66cdaa xcdb5cd xadd8e6 xdda0dd x9500d3\n"
	   "#set terminal gif small size 600,400 xffffff x000000 x404040 xff0000 xffa500 x66cdaa xcdb5cd xadd8e6 x0000ff xdda0dd x9500d3\n"
	   "set output \"y.gif\"\n"
	   "plot \"y.dat\" using 1:2 title \"T_B[deg]\", "
	   "\"y.dat\" using 1:3 title \"T_H[deg]\","
	   " \"y.dat\" using 1:4 title \"P/Pmax[%s]\"\n"
	   ,rr,vS*60000,overshoot,undershoot,seiteijikoku-starttime,rho_0r,C_0r,starttime,"%","%","%","%","%");
   fclose(fp);
   
#endif
   
   //050711 tomisaki
   int i_data;
   int i_cell;
   FILE *matrix_file;
   if(it==0){
     fp6=fopen("result.dat","w+");
     fprintf(fp6,"#it overshoot,undershoot,seiteijikoku-starttime,energy_mean/AP_kk*50*100,AP_NC,lambda # ");
     for(i_data=0;i_data<AP_NN;i_data++){
       fprintf(fp6,",M[0][%d]",i_data);
     }
     fprintf(fp6,"\n");
     fclose(fp6);  
   }
   
   //2005/11/10 tomisaki
   if(stable_time!=0){
     // 050704 tomisaki
     printf("seiteijikoku : %f\n",seiteijikoku);
     make_rs();    
   }
   
   if(add_dat[0]!=0){
     make_file_dat(dat_file);
   }
   
   if(it==0){
     matrix_file=fopen("result_matrix.dat","w");
   }
   else{
     matrix_file=fopen("result_matrix.dat","a+");
   }
   fprintf(matrix_file,"it : %d\n",it);
   if(ensemble==0){
     for(i_cell=0;i_cell<AP_NC;i_cell++){
       fprintf(matrix_file,"M[%d] ",i_cell);
       for(i_data=0;i_data<AP_NN;i_data++){
	 fprintf(matrix_file,"%15.7e ",net[0].cell[i_cell].M[0][i_data]);
       }
       fprintf(matrix_file,"w[%d] ",i_cell);//080305koshi i_data<3をi_data<AP_ny+AP_nuに修正
       for(i_data=0;i_data<3;i_data++){
	 fprintf(matrix_file,"%15.7e ",net[0].cell[i_cell].w[i_data]);
       }
       fprintf(matrix_file,"v[%d]: %d ",i_cell,net[0].cell[i_cell].v);
       fprintf(matrix_file,"\n");
     }
   }
   fp6=fopen("result.dat","a+");
#ifdef NEWenergy
    fprintf(fp6,"%d %f %f %f %f %d %f %f # ",it,overshoot,undershoot,seiteijikoku-starttime,10000.*energy_sum/AP_kk,AP_NC,lambda,10000.*energy_sum/AP_kk);
#else 
    fprintf(fp6,"%d %f %f %f %f %d %f # ",it,overshoot,undershoot,seiteijikoku-starttime,energy_mean/AP_kk*50*100,AP_NC,lambda);
#endif
   for(i_data=0;i_data<AP_NN;i_data++){
     fprintf(fp6," %f",net[0].cell[AP_i].M[0][i_data]);
   }
   for(i_data=0;i_data<=n_AP_NC;i_data++){
     fprintf(fp6," %d",st_AP_i[i_data]);
   }

   fprintf(fp6,"\n");
   fclose(fp6);  
   fclose(matrix_file);
   
#ifdef kuwakoshi//090608 yuno
   sprintf(cmd,"cp y.dat ./y_data/y_%d.dat",it);//061130kuwa
   system(cmd); 

   sprintf(cmd,"cp y_matrix.dat ./y_matrix_data/matrix_%d.dat",it); //2007/10/11 koshi
   system(cmd);
#endif //#ifdef kuwakoshi


   if(++it>=iteration){
     sprintf(cmd,"kill -9 `ps aux|grep xterm|sed -e /\"ps aux\"/d -e /grep/d -e /killn/d|awk '{print $2}'`");
     fprintf(stdout,"To kill all plot windows, do:\n%s\n",cmd);
     fprintf(stdout,"Done emulate!(Push return-key)\n");
     exit(0);
   }
   /****/
   for(kk=0;kk<kk1;kk++){
     buff_y[kk]=25;
     buff_u[kk]=0;
   }
   for(k=0;k<buffsize;k++){
     TH[k]=TH[k]=TB0[k]=TB[k]=25;
     p[k]=0.0;
   }
   overshoot=undershoot=maxTB=0;
   seiteijikoku=-1;


   time=0; 
   k=0;
   iiiii=0;/*プラント初期化*/
   kk=0;
   PV1=YB*25;
   reinit_AP();
   RUN=0;
   jjjjj=0;/**/
   fclose(fptrain);
   fclose(fptest);
   
   //yuno090622
   //080318 koshi
   int tnet=0;
   int tweight=0;
   int tcell=0;
   int uni;
   net_i=1;
   // unnecessary for ensrs, from here

   //2005/11/10 tomisaki
   if(ensemble==0){//
     if(useensrs){//kuro
       int T=20;//number of training iterations
       char *fnnet="can2b.net";
       int k=AP_nu+AP_ny;
       system("rm -rf result-ensrs2ge/");
       sprintf(cmd,"can2b/ensrs %s -1:/dev/null %d-%d:1 Lstd:0:2 ib:0:0:0:0 k:%d vm2:-1 T:%d BIAS:0 DISP:0 > /dev/null 2>&1;cp last.net %s",
       //sprintf(cmd,"can2b/ensrs %s -1:/dev/null %d-%d:1 Lstd:0:2 ib:0:0:0:0 k:%d NC:10 vt:0.5 vm:4 vm2:-1 vr:0.5 w:0.1 T:%d DISP:0 > /dev/null 2>&1;cp last.net %s",
	       fntrain,AP_NC,AP_NC,k,T,fnnet);
       system(cmd);
     }
     if((num_nets==1)&&(net->firstcall==1)){
       //sprintf(cmd,"%s",net_f);net_load(net,cmd,0,AP_NC);
       net_load(net,net_f,0,AP_NC);
     }
     else if((num_nets>=2)&&(net->firstcall==1)){//090622 yuno
       if((uni_flag==1)&&(nuse_flag==0)){
	 //ネットの初期化
	 for(tnet=0;tnet<=num_nets;tnet++){
	   for(i=0;i<AP_NC;i++){
	     for(yu=0;yu<=net_yu;yu++){
	       net[tnet].cell[i].M[0][yu]=0;
	     }
	   }
	 }
	 //ネットの読み込み
	 for(hi=1;hi<=num_nets;hi++){
	   sprintf(cmd,"%s",net_n[hi]);
	   net_load(net,cmd,hi,uni_AP_NC[hi]);
	 }
	 //ネットの統合
	 for(i=0;i<uni_AP_NC[1];i++){
	   for(yu=0;yu<=net_yu;yu++){
	     net[0].cell[i].M[0][yu]=net[1].cell[i].M[0][yu];
	   }
	 }
	 tcell=uni_AP_NC[1];
	 for(uni=1;uni<num_nets;uni++){
	   for(i=0;i<uni_AP_NC[uni+1];i++){
	     for(yu=0;yu<=net_yu;yu++){
		 net[0].cell[i+tcell].M[0][yu]=net[uni+1].cell[i].M[0][yu];
	     }
	   }
	   tcell+=uni_AP_NC[uni+1];
	 }
	 //重みの統合
	 for(i=0;i<uni_AP_NC[1];i++){
	   for(yu=0;yu<=net_yu;yu++){
	     net[0].cell[i].w[yu]=net[1].cell[i].w[yu];
	   }
	 }
	 tweight=uni_AP_NC[1];
	 for(uni=1;uni<num_nets;uni++){
	   for(i=0;i<uni_AP_NC[uni+1];i++){
	     for(yu=0;yu<=net_yu;yu++){
	       net[0].cell[i+tweight].w[yu]=net[uni+1].cell[i].w[yu];
	     }
	   }
	   tweight+=uni_AP_NC[uni+1];
	 }
       }//end of if((uni_flag==1)&&(nuse_flag==0))
       
       //統合されたネットを初期条件により選択する? 081010koshi
       else if((uni_flag==1)&&(nuse_flag==1)){
	 //ネットの初期化
	 for(tnet=1;tnet<=num_nets;tnet++){
	   for(i=0;i<AP_NC;i++){
	     for(yu=0;yu<=net_yu;yu++){
	       net[tnet].cell[i].M[0][yu]=0;
	     }
	   }
	 }
	 //ネットの読み込み
	 for(hi=1;hi<=num_nets;hi++){
	   sprintf(cmd,"%s",net_n[hi]);
	   net_load(net,cmd,hi,uni_AP_NC[hi]);
	 }
       }

       else if(ave_flag==1){
	 for(i=0;i<AP_NC;i++){
	   for(yu=0;yu<=net_yu;yu++){
	     net[0].cell[i].M[0][yu]=0;
	     net[num_nets+net_i].cell[i].M[0][yu]=0;
	   }
	 }
	 for(hi=1;hi<=num_nets;hi++){
	   sprintf(cmd,"%s",net_n[hi]);
	   net_load(net,cmd,hi,AP_NC);
	 }
	 for(i=0;i<AP_NC;i++){
	   for(yu=0;yu<=net_yu;yu++){
	     net[0].cell[i].M[0][yu]=0;
	     net[num_nets+net_i].cell[i].M[0][yu]=0;
	   }
	 }
	 //連想行列の平均
	 for(i=0;i<AP_NC;i++){
	   //Mの計算
	   for(yu=0;yu<=net_yu;yu++){
	     for(net_s=1;net_s<=num_nets;net_s++){
	       net[num_nets+net_i].cell[i].M[0][yu]+=net[net_s].cell[i].M[0][yu];
	       if((net_s%num_nets)==0){
		 net[num_nets+net_i].cell[i].M[0][yu]/=num_nets;
		 net[0].cell[i].M[0][yu]=net[num_nets+net_i].cell[i].M[0][yu];
	       }
	     } 
	   } 
	 }
       }
     }//end of else if((num_nets>=2)&&(net->firstcall==1)){//090622 yuno
     else{
       net_load(net,"can2b.net",0,AP_NC);
     }
   }//end of if(ensemble==0)
   net->firstcall=0;
  }
}
