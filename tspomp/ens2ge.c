/* Generalization Error with Resampling method.
 */
//gcc -Wall -g  -lm  -lgsl -lgslcblas rsm4ge.c   -o rsm4ge
//make rsm4ge
//Usage:rsm4ge data/11train1e3.dat 10 1 data/11test101x101.dat
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
//#define nNmax 100
#define square(x) ((x)*(x))
#define buffsize 1024
#define linesize 10000
#define nRSmax 2
#define NORS2 -1
#define DIRECT -1
#define LEAVEMANYOUT 0
#define MULTIFOLD 1
#define BOOTSTRAP 2
char *methodname1[4]={"Direct","LeaveManyOut","MultiFold","BootStrap"};
//int *NN;
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix_double.h>
#include "my_misc.c"

void usage(int argc,char **argv){
  //  fprintf(stderr,"Usage: %s <fn_given> <fn_valid> N:<N>:<nD>:<nN> m:<m>:<d>:<nm> [<options>]\n",argv[0]);
  fprintf(stderr,"Usage: %s <fn_given> <fn_valid> <N:<N1>:<NN>:<Nd> | N:<N1>-<N2>:<NStep>> <m:<m1>:<nm>:<md>|m:<m1>-<m2>:<md>> [<options>]\n",argv[0]);
  fprintf(stderr,
	  "fn_given              : file name of given data\n"
	  "<fn_valid>            : the file name of validation data if exist (default /dev/null).\n"
	  "N:<N1>[:<NN>[:<ND>]]  : number of cells N=N1+ND*i for i=0,1,..,NN-1 .\n"
	  "N:<N1>-<N2>[:<ND>]]   : number of cells N=N1+ND*i for i=0,1,... until N<=N2.\n"
	  "m:<m1>:<md>:<nm>      : number of ensenble m=m1+nd*i for i=0,1,2,...,nm-1.\n"
	  "m:<m1>-<m2>:<md>      : number of ensenble m=m1+nd*i for i=0,1,2,... until m<=nd.\n"
	  "k:<k>                 : dimension of the input vector (defalut:2).\n"
	  "rs:<rsprog>           : executable program for resampling method(defalut:rs4irem).\n"
	  "<other options>       : see ensrs.c\n"
	  );
}
static char pr[buffsize];
int main(int argc,char **argv)
{
  char cmd[30000];
  char rdir[buffsize];
  char fngiven[1024];
  char fnvalid[1024];
  char fnplt[1024];
  char fnloss[1024];
  FILE *fp,*fploss;
  char *rdir0="./result-ensrs";
  //  char *rdir1="./result-ensrs/rsresults";
  int i,j,jj,ij;
  int K=2;        //dimension
  int *rsmo;
  char ensrsprog[256];
  int _N,_DN=1,_nN,*NN,_N1,_N2;
  int Ngs1=0,Ngs2=0;
  int _m,_dm,_nm,*mm=NULL,_m1,_m2;
  //  int _e,_de,_ne,*ee,_e1,_e2;
  double *LD,*Ltst,*Lvar,*Lvarval,*Lvar0;
  double *Lib,Libmin5,*Lemp,*H0,*L0,*L0v,*Ltr;
  int ij_LDmin=0;
  int ij_Ltstmin=0;
  int ij_Lvarmin=0;
  int ij_Lvarvalmin=0;
  DIR *pdir;
  //  int _N1,_N2,_m1,_m2;
  int intmode,bayesmode;
  double bayesopt1=0,bayesopt2=0,bayesopt3=0,bayesopt4=0;
  int m_LD=0;
  //  char bagalpha[10]={0,};
  int BAGGING=0,rs_method=-1,rs_seed=10,rs_ens=1;
  //  double rs_alpha=0,kc=2;//kc=2:coverage factor for 95% extended uncertainty 
  double rs_alpha=0;//kc=2:coverage factor for 95% extended uncertainty 
  double rs_beta=0;
  double *rs_Alpha=NULL;
  char *rsa;
  //  sprintf(ensrsprog,"rs4irem");
  int t_boost=-1;
  //  double rethresh_boost=12.0;
  int dsp=1;
  int DISP=1;
#define NoBoost 0
#define EmBoost 1
#define GbBoost 2
  int Boost=NoBoost;
  sprintf(ensrsprog,"ensrs");
  
  if(argc<5){
    usage(argc,argv);
    return(-1);
  }

  sprintf(fngiven,"%s",argv[1]);
  sprintf(fnvalid,"%s",argv[2]);
  
  rsmo=(int *)malloc(sizeof(int)*argc);
  for(i=3;i<argc;i++) rsmo[i]=1;
  
  for(i=3;i<argc;i++){
    if(strncmp(argv[i],"ib:",3)==0){
      sscanf(&(argv[i][3]),"%d:%d:%lf:%lf:%lf:%lf",&intmode,&bayesmode,&bayesopt1,&bayesopt2,&bayesopt3,&bayesopt4);
      rsmo[i]=1;
      m_LD=bayesopt2;
    }
  }
  for(i=3;i<argc;i++){
    if(strncmp(argv[i],"N:",2)==0){
      char *p;
      int ptn=0;
      for(p=&argv[i][2];;){
	if(*p==0) break;
	if(ptn==0){//unknown pattern
	  if(*p==':') {ptn=1;break;}
	  if(*p=='-') {ptn=2;break;}
	}
	p++;
      }
      if(ptn==1) {sscanf(&argv[i][2],"%d:%d:%d",&_N1,&_DN,&_nN);_N2=_N1+(_nN-1)*_DN;}
      else if(ptn==2) sscanf(&argv[i][2],"%d-%d:%d",&_N1,&_N2,&_DN);
      else _N1=_N2=_DN=1;
      if(_DN<=0) _DN=1;
      for(_nN=0,_N=_N1;_N<=_N2;_N+=_DN) _nN++;
      if(_nN<1) _nN=1;
      NN=(int *)malloc(sizeof(int)*(_nN+1));
      for(jj=0;jj<_nN;jj++) NN[jj]=_N1+_DN*jj;
      NN[_nN]=0;
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"NN:",3)==0){
      char *p;
      _nN=0;
      for(p=&argv[i][3];;){
	if(*p==0) break;
	if(*p==':') _nN++;
	p++;
      }
      _nN++;
      NN=(int *)malloc(sizeof(int)*(_nN+1));
      for(p=&argv[i][3],_nN=0;;){
	sscanf(p,"%d",&NN[_nN++]);
	for(;;) if(*p==':'|| *p=='-' || *p==0) break; else p++;
	if(*p==0) break;
	if(*p=='-'){
	  int _n,j;
	  sscanf(++p,"%d",&_n);
	  for(j=NN[_nN-1]+1;j<=_n;j++) NN[_nN++]=j;
	  for(;;) if(*p==':'|| *p=='-' || *p==0) break; else p++;
	  if(*p==0) break;
	}
	p++;
      }
      NN[_nN]=0;
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"Ngs:",4)==0){
      sscanf(&argv[i][4],"%d-%d",&Ngs1,&Ngs2);
      _nN=Ngs2-Ngs1;
      NN=(int *)malloc(sizeof(int)*(_nN+1));
      NN[0]=Ngs1;
      NN[1]=Ngs2;
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"m:",2)==0){
      char *p;
      int ptn=0;
      for(p=&argv[i][2];;){
	if(*p==0) break;
	if(ptn==0){//unknown pattern
	  if(*p==':') {ptn=1;break;}
	  if(*p=='-') {ptn=2;break;}
	}
	p++;
      }
      if(ptn==1) {sscanf(&argv[i][2],"%d:%d:%d",&_m1,&_dm,&_nm);_m2=_m1+(_nm-1)*_dm;}
      else if(ptn==2) sscanf(&argv[i][2],"%d-%d:%d",&_m1,&_m2,&_dm);
      else _m1=_m2=_nm=1;
      //      sscanf(&argv[i][2],"%d:%d:%d",&_m1,&_m2,&_dm);
      //if(_m1<3) _m1=3;
      if(_dm<1) _dm=1;
      if(_m1<m_LD*2+1) _m1=m_LD*2+1;
      for(_nm=0,_m=_m1;_m<=_m2;_m++) _nm++;
      mm=(int *)malloc(sizeof(int)*(_nm+1));
      for(jj=0;jj<_nm;jj++) mm[jj]=_m1+_dm*jj;
      mm[_nm]=0;
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"M:",2)==0){
      char *p;
      int ptn=0;
      for(p=&argv[i][2];;){
	if(*p==0) break;
	if(ptn==0){//unknown pattern
	  if(*p==':') {ptn=1;break;}
	  if(*p=='-') {ptn=2;break;}
	}
	p++;
      }
      if(ptn==1) {sscanf(&argv[i][2],"%d:%d:%d",&_m1,&_dm,&_nm);_m2=_m1+(_nm-1)*_dm;}
      else if(ptn==2) sscanf(&argv[i][2],"%d-%d:%d",&_m1,&_m2,&_dm);
      else _m1=_m2=_nm=1;
      if(_m1<1) _m1=1;
      if(_dm<1) _dm=1;
      for(_nm=0,_m=_m1;_m<=_m2;_m+=_dm) _nm++;
      mm=(int *)malloc(sizeof(int)*(_nm+1));
      for(jj=0;jj<_nm;jj++) mm[jj]=_m1+_dm*jj;
      mm[_nm]=0;
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"k:",2)==0) sscanf(&argv[i][2],"%d",&K);
    else if(strncmp(argv[i],"rs:",3)==0) {sprintf(ensrsprog,"%s",&argv[i][3]);rsmo[i]=0;}
    else if(strncmp(argv[i],"bga:",4)==0){
      //      sprintf(bagalpha,"%s",&argv[i][4]);rsmo[i]=0;
      sscanf(&argv[i][4],"%lf",&rs_alpha);
      rs_method=2;
      rsmo[i]=0;
      rs_seed=10;
      rs_ens=1;
    }//bootstrap aggregation 
    else if(strncmp(argv[i],"rsa:",4)==0){
      //      sscanf(&argv[i][4],"%d:%lf:%d",&rs_method,&rs_alpha,&rs_seed);
      int ncol=0;
      char *p=&argv[i][4];
      for(;*p!=0;p++) if(*p==':') ncol++;
      rsa=&argv[i][4];
      if(ncol==2) {sscanf(rsa,"%d:%lf:%d",&rs_method,&rs_alpha,&rs_seed);rs_ens=1;}
      else if(ncol==3) sscanf(rsa,"%d:%lf:%d:%d",&rs_method,&rs_alpha,&rs_seed,&rs_ens);
      else if(ncol==4) sscanf(rsa,"%d:%lf:%d:%d:%lf",&rs_method,&rs_alpha,&rs_seed,&rs_ens,&rs_beta);
      BAGGING=1;//bagging with validfile
      rsmo[i]=0;
    }//resampling aggregation
    else if(strncmp(argv[i],"dsp:",4)==0){
      sscanf(&argv[i][4],"%d",&dsp);
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"DISP:",5)==0){
      sscanf(&argv[i][5],"%d",&DISP);
      //      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"bst:",4)==0){
      char *p;
      p=&argv[i][4];
      for(j=0;;p++) {
	if(*p==0) break;
	if(*p==':') if(++j>=1) break;
      }
      //      if(j>=1) {sscanf(&argv[i][4],"%d:%lf",&t_boost,&rethresh_boost);}
      if(j>=1) {sscanf(&argv[i][4],"%d:%d",&t_boost,&Boost);}
      else {sscanf(&argv[i][4],"%d",&t_boost);}
      //      sscanf(&argv[i][4],"%d",&t_boost);
      rsmo[i]=0;
    }
  }

  if(rs_method>=0 && strncmp(fnvalid,"/dev/null",9)==0) BAGGING=2;//bagging without validfile
  if(mm==NULL){mm=(int *)malloc(sizeof(int)*(2)); mm[0]=1; mm[1]=0; _nm=1;}//??
  LD   =(double *)malloc(sizeof(double)*_nN*_nm);
  Ltst   =(double *)malloc(sizeof(double)*_nN*_nm);
  Lvar   =(double *)malloc(sizeof(double)*_nN*_nm);
  Lvar0  =(double *)malloc(sizeof(double)*_nN*_nm);
  Lvarval=(double *)malloc(sizeof(double)*_nN*_nm);
  Lib =(double *)malloc(sizeof(double)*_nN*_nm);
  Lemp=(double *)malloc(sizeof(double)*_nN*_nm);
  H0     =(double *)malloc(sizeof(double)*_nN*_nm);//Entropy
  int *s_Ltstmin=(int*)malloc(sizeof(int)*_nN*_nm);
  int smax_Ltstmin=_nN*_nm;
  //  if(smax_Ltstmin>50) smax_Ltstmin=50;
  if(smax_Ltstmin>5) smax_Ltstmin=5;
  L0     =(double *)malloc(sizeof(double)*_nN*_nm);//OriginalLoss
  L0v    =(double *)malloc(sizeof(double)*_nN*_nm);//OriginalLoss - Lob
  Ltr    =(double *)malloc(sizeof(double)*_nN*_nm);//OriginalLoss - Ltr
  int *s_L0vmin=(int*)malloc(sizeof(int)*_nN*_nm);
  int smax_L0vmin=1;
  sprintf(rdir,"%s",rdir0);
  if((pdir=opendir(rdir))==NULL) {sprintf(cmd,"mkdir %s",rdir);system(cmd);}  else closedir(pdir);
  sprintf(rdir,"%s/tmp",rdir0);
  if((pdir=opendir(rdir))==NULL) {sprintf(cmd,"mkdir %s",rdir);system(cmd);} else closedir(pdir);
  { //dir to store the result
    sprintf(rdir,"%s",rdir0);
    if((pdir=opendir(rdir))==NULL) {sprintf(cmd,"mkdir %s",rdir);system(cmd);}  else closedir(pdir);
    sprintf(&rdir[strlen(rdir)],"/%s",fnbody(fngiven,pr));//
    sprintf(&rdir[strlen(rdir)],"+%s",fnbody(fnvalid,pr));//
    for(i=2;i<argc;i++){
      sprintf(&rdir[strlen(rdir)],"%s",argv[i]);
    }
    for(i=strlen(rdir0)+1;rdir[i]!=0;i++) if(rdir[i]=='/') rdir[i]='@';
    rdir[240]=0;
    if((pdir=opendir(rdir))==NULL) {sprintf(cmd,"mkdir %s",rdir);system(cmd);}
    else closedir(pdir);
  }
  sprintf(fnloss,"%s/loss.dat",rdir);
  sprintf(fnplt ,"%s/loss.plt",rdir);
  int nGivenData;
  ///////////For Golden Section Method
  const double r = 2. / (3. + sqrt(5.));//0.381966
  double c, d, fc, fd, t,*pfcd;
  double a, b, fa, fb;
  char *fn_predall="predict+all.dat";
  int n_predall=0;
  //  if((fploss=fopen(fnloss,"r"))==NULL){
  if(1==1 || (fploss=fopen(fnloss,"r"))==NULL){
    for(i=0;i<_nN;i++){
      for(j=0;j<_nm;j++){
	ij=i*_nm+j;
	if(rs_method<0){//for specified valid-file
	  sprintf(cmd,"%s %s -1:%s %d-%d:%d ",ensrsprog,fngiven,fnvalid,NN[i]-m_LD*_DN,NN[i]+(mm[j]-1+m_LD)*_DN,_DN);
	}
	else{//for bagging or unspecified valid-file
	  if(rs_beta>1){
	    if(rs_Alpha==NULL){
	      rs_Alpha=(double *)malloc(sizeof(double)*(_nN+1));
	      FILE *fp=fopen(fngiven,"r");
	      char line[10240];
	      for(nGivenData=0;;nGivenData++){
		fgets(line,10240,fp);
		if(feof(fp)) break;
	      }
	      fclose(fp);
	    }
	    rs_Alpha[i]=-log(NN[i]*(K+1)*rs_beta/nGivenData);
	    if(rs_Alpha[i]>2.3) rs_Alpha[i]=2.3;
	    rs_alpha=rs_Alpha[i];
	  }
	    
	  if(t_boost==-1 || Boost==NoBoost){//default for resampling = Bagging-Only
	    //	    sprintf(cmd,"%s %s %d:%d:%.2f:%d %d-%d:%d bg:%s ",ensrsprog,fngiven,rs_method,rs_ens,rs_Alpha[i],rs_seed,NN[i],NN[i]+(mm[j]-1)*_DN,1,fnvalid);//for ensrs060609.c
	    sprintf(cmd,"%s %s %d:%d:%g:%d %d-%d:%d bg:%s ",ensrsprog,fngiven,rs_method,rs_ens,rs_alpha,rs_seed,NN[i],NN[i]+(mm[j]-1)*_DN,1,fnvalid);//for ensrs060609.c
	    //sprintf(cmd,"%s %s %d:%d:%.2f:%d %d-%d:%d bg:%s ",ensrsprog,fngiven,rs_method,rs_ens,rs_alpha,rs_seed,NN[i]-m_LD*_DN,NN[i]+(mm[j]-1+m_LD)*_DN,1,fnvalid);
	    //sprintf(cmd,"%s %s %d:%d:%.2f:%d %d-%d:%d bg:%s ",ensrsprog,fngiven,rs_method,mm[j],rs_alpha,rs_seed,NN[i],NN[i],1,fnvalid);//for ensrs060608.c
	  }
	  else if(Boost==GbBoost){//Gradient-based boosting
	    int t; 
	    for(t=1;t<=t_boost;t++){
	      //	      sprintf(cmd,"%s %s %d:%d:%.2f:%d %d-%d:%d bg:%s bst:%d:%d ",ensrsprog,fngiven,rs_method,rs_ens,rs_Alpha[i],rs_seed,NN[i],NN[i]+(mm[j]-1)*_DN,1,fnvalid,t,Boost);//for ensrs060907.c
	      sprintf(cmd,"%s %s %d:%d:%g:%d %d-%d:%d bg:%s bst:%d:%d ",ensrsprog,fngiven,rs_method,rs_ens,rs_alpha,rs_seed,NN[i],NN[i]+(mm[j]-1)*_DN,1,fnvalid,t,Boost);//for ensrs060907.c
	      if(t==t_boost) break;
	      for(jj=3;jj<argc;jj++) if(rsmo[jj]) sprintf(&cmd[strlen(cmd)],"%s ",argv[jj]);
	      sprintf(&cmd[strlen(cmd)],"> /dev/null");
	      fprintf(stderr,"! Executing '%s'.\n",cmd);
	      system(cmd);
	    }
	  }
	  else if(Boost==EmBoost){
	    //	    sprintf(cmd,"%s %s %d:%d:%.2f:%d %d-%d:%d bg:%s bst:%d:%d ",ensrsprog,fngiven,rs_method,rs_ens,rs_Alpha[i],rs_seed,NN[i],NN[i]+(mm[j]-1)*_DN,1,fnvalid,t_boost,Boost);//for ensrs060907.c
	    sprintf(cmd,"%s %s %d:%d:%g:%d %d-%d:%d bg:%s bst:%d:%d ",ensrsprog,fngiven,rs_method,rs_ens,rs_alpha,rs_seed,NN[i],NN[i]+(mm[j]-1)*_DN,1,fnvalid,t_boost,Boost);//for ensrs060907.c
	  }
	}//elsee{//for bagging or unspecified valid-file
	//	sprintf(cmd,"%s %s -1:%s %d-%d:%d ",ensrsprog,fngiven,fnvalid,NN[i]-mm[j],NN[i]+mm[j],_d);
	//	sprintf(cmd,"%s %s -1:%s %d-%d:%d ",ensrsprog,fngiven,fnvalid,NN[i],NN[i]+mm[j]+2*m_LD,_dm);
	//	sprintf(cmd,"%s %s -1:%s %d-%d:%d ",ensrsprog,fngiven,fnvalid,NN[i],NN[i]+mm[j]*_DN,_DN);
	//	sprintf(cmd,"%s %s -1:%s %d-%d:%d ",ensrsprog,fngiven,fnvalid,NN[i],NN[i]+mm[j],_dm);
	//	sprintf(cmd,"%s %s -1:%s %d:%d:%d ",ensrsprog,fngiven,fnvalid,NN[i],mm[j],_dm);
	//	sprintf(cmd,"%s %s -1:%s %d-%d ",ensrsprog,fngiven,fnvalid,NN[i],NN[i]+mm[j]-1);
	for(jj=3;jj<argc;jj++) if(rsmo[jj]) sprintf(&cmd[strlen(cmd)],"%s ",argv[jj]);
	sprintf(&cmd[strlen(cmd)],"> /dev/null");
	fprintf(stderr,"Executing '%s'.\n",cmd);
	if(system(cmd)==-1){
	  fprintf(stderr,"Error when executing '%s'.\n",cmd);
	  return(-1);
	}
#ifdef PREDALL
	{
	  if(n_predall==0){
	    sprintf(cmd,"cat predict+.dat|awk '{print $2,$3,$1;}'> %s",fn_predall);
	    fprintf(stderr,"#executing %s\n",cmd);
	    system(cmd);
	  }
	  else{
	    sprintf(cmd,"cp %s p1.dat;cat predict+.dat |awk '{print $1}'| paste p1.dat - > %s",fn_predall,fn_predall);
	    fprintf(stderr,"#executing %s\n",cmd);
	    system(cmd);
	  }
	  n_predall++;
	}
#endif//#ifdef PREDALL
	double *func=Ltst;
	//double *func=LD;//check LD/N for estimating bias
	{
	  int _nfiles,_num;
	  fp=fopen("./loss+.dat","r");
	  fscanf(fp,"%lf %lf %lf %lf %lf %d %d %lf %lf %lf %lf %lf",&LD[ij],&Ltst[ij],&Lvar[ij],&Lvarval[ij],&Lvar0[ij],&_nfiles,&_num,&Lib[ij],&Lemp[ij],&H0[ij],&L0[ij],&Ltr[ij]);
	  L0v[ij]=L0[ij]-Lvar[ij];
	  //double tmp=Ltst[ij]; Ltst[ij]=LD[ij];LD[ij]=tmp;//check LD/N for estimating bias
	  //double tmp=Ltst[ij]; Ltst[ij]=LD[ij]/(NN[i]);LD[ij]=tmp;//check LD/N for estimating bias
	  //	  double tmp=Ltst[ij]; Ltst[ij]=LD[ij]/(NN[i]*NN[i]);LD[ij]=tmp;//check LD/N for estimating bias
	  //	  LD[ij]/=(NN[i]*NN[i]);//checkLD/N//check LD/N for estimating bias
	  //	  LD[ij]/=NN[i];//checkLD/N//check LD/N for estimating bias
	  //	  double tmp=Ltst[ij]; Ltst[ij]=LD[ij]/NN[i];LD[ij]=tmp;//check LD/N for estimating bias
	  //	  double tmp=Ltst[ij]; Ltst[ij]=-LD[ij]/NN[i];LD[ij]=tmp;//check LD/N for estimating bias
	  fclose(fp);
	}
	if(Ngs1!=0){//golden section method searches Ltst
	  if(i==0){a=NN[i];fa=func[ij];}	  //	  if(i==0){a=NN[i];fa=Ltst[ij];}
	  else if(i==1){
	    b=NN[i];
	    fb=func[ij]; // fb=Ltst[ij];
	    t = r * (b - a);
	    c=a+t;
	    d=b-t;
	    NN[i+1]=(int)(c+.5);
	    NN[i+2]=(int)(d+.5);
	  }
	  else if(i==2){
	    fc=func[ij];//	    fc=Ltst[ij];
	    pfcd=&fd;
	    if((fa>=fc && fc>=fb) || (fa<=fc && fc<=fb)){
	      fprintf(stderr,"#(i%d)Ltst(%d)%g,Ltst(%d)%g,Ltst(%d)%g\n",i,(int)(a+.5),fa,(int)(c+.5),fc,(int)(b+.5),fb);
	      fprintf(stderr,"# Minimum of L may not be in the range Ngs:%d:%d !!!\n",Ngs1,Ngs2);
	      //	      exit(-1);
	    }
	  }
	  else if(i>=3){
	    *pfcd=func[ij];//	    *pfcd=Ltst[ij];
	    fprintf(stderr,"#(i%d)Ltst(%d)%g,Ltst(%d)%g,Ltst(%d)%g,Ltst(%d)%g \n",i,(int)(a+.5),fa,(int)(c+.5),fc,(int)(d+.5),fd,(int)(b+.5),fb);
	    if(i>=10 && (fc>func[1] &&(fd>func[1]))){      //	    if(i>=10 && (fc> Ltst[1]) &&(fd>Ltst[1])){
	      fprintf(stderr,"#(i%d)Ltst(%d)%g,Ltst(%d)%g,Ltst(%d)%g\n",i,(int)(c+.5),fc,(int)(b+.5),fb,NN[1],Ltst[1]);
	      fprintf(stderr,"# Minimum of L may not be in the range Ngs:%d:%d !!!\n",Ngs1,Ngs2);
	      //	      exit(-1);
	    }
	    if(fc>fd){
	      a = c;  c = d;  fc = fd;  d = b - r * (b - a);
	      if (d - c < 0.5) {
		_nN=i+1;
		break;
	      }
	      NN[i+1]=(int)(d+.5);
	      pfcd=&fd;
	      //	      fd = f(d,par);
	    } else {
	      b = d;  d = c;  fd = fc;  c = a + r * (b - a);
	      if (d - c < 0.5) {
		_nN=i+1;
		break;
	      }
	      NN[i+1]=(int)(c+.5);
	      pfcd=&fc;
	      //	      fc = f(c,par);
	    }
	  }
	}
	//	{//060517
	//	  double _msemean,_msestdp,_msestdm;
	//	  fp=fopen("./tmp/rsresult.dat","r");
	//	  fscanf(fp,"%lf %lf %lf %lf",&_msemean,&_msestdp,&_msestdm,&Lib[ij]);
	//	  fclose(fp);
	//	}
      }
    }
    fploss=fopen(fnloss,"w");
    for(i=0;i<_nN;i++){
      for(j=0;j<_nm;j++){
	ij=i*_nm+j;
	fprintf(fploss,"%d %d %13.7e %13.7e %13.7e %13.7e %13.7e %13.7e %.7e %.7e %.7e#N m LD Ltst Lvar Lvarval Lvar0\n",
		NN[i],mm[j],LD[ij],Ltst[ij],Lvar[ij],Lvarval[ij],Lvar0[ij],Lib[ij],Lemp[ij],H0[ij],L0[ij]);
      }
      fprintf(fploss,"\n");
    }
    fclose(fploss);
    if(Ngs1!=0){
      sprintf(cmd,"sort -g %s >tmploss.dat; mv tmploss.dat %s",fnloss,fnloss);
      system(cmd);
    }
    fploss=fopen(fnloss,"r");
  }//closing  if((fploss=fopen(fnloss,"r"))==NULL){
#define FINISH
#ifdef FINISH
#ifdef PREDALL
  if((DISP&0x02)==0x02){
    sprintf(fnplt ,"dispypall.plt");
    fp=fopen(fnplt,"w");
    fprintf(fp,"set style data lines\n");
    fprintf(fp,"plot \"%s\" using 1:2 w lp t \"y\"",fn_predall);
    int m;
    for(m=0;m<n_predall;m++) fprintf(fp,", \"\" using 1:%d t \"y^N%d\"",3+m,NN[m/_nm]);
    fprintf(fp,"\npause -1 \"hit return to quit.\"\n");
    fclose(fp);
    sprintf(cmd,"xterm -geometry 50x5+0-0 -e gnuplot -geometry 320x180+0+0 %s",fnplt);
    fprintf(stderr,"Execute '%s'.\n",cmd);
    sprintf(&cmd[strlen(cmd)],"&");
    system(cmd);
  }
#endif//#ifdef PREDALL
  return(0);
}
#else

  {
    char buff[buffsize];
    //    int _NN,_mm;
    int _mm;
    ij_LDmin=ij_Ltstmin=ij_Lvarmin=ij_Lvarvalmin=0;
    for(i=0;i<_nN;i++){
      for(j=0;j<_nm;j++){
	ij=i*_nm+j;
	for(;;){
	  fgets(buff,buffsize,fploss);
	  if(feof(fploss)) break;
	  if(strlen(buff)>1) break;
	}
	sscanf(buff,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
	       &NN[i],&_mm,&LD[ij],&Ltst[ij],&Lvar[ij],&Lvarval[ij],&Lvar0[ij],&Lib[ij],&Lemp[ij],&H0[ij],&L0[ij],&Ltr[ij]);
	L0v[ij]=L0[ij]-Lvar[ij];
	//	       &_NN,&_mm,&LD[ij],&Ltst[ij],&Lvar[ij],&Lvarval[ij],&Lvar0[ij],&Lib[ij],&Lemp[ij],&H0[ij]);
	//	Lvar[ij]*=(mm[j]/(mm[j]-1+1e-3));
	//	Lvar0[ij]*=(mm[j]/(mm[j]-1+1e-3));
	//		 &NN[i],&mm[j],&LD[ij],&Ltst[ij],&Lvar[ij],&Lvarval[ij]);
	//	if(_mm!=mm[j]){
	//	  fprintf(stderr,"m=%d,%dhen\n",mm[j],_mm);
	//	}
	//	if(_NN!=NN[i]){
	//	  fprintf(stderr,"N=%d,%dhen\n",NN[i],_NN);
	//	}
	{
	  //	  if(LD[ij]<1e-20){  fprintf(stderr,"hen\n");	  }
	  if(LD[ij]<LD[ij_LDmin]) ij_LDmin=ij;
	  if(Ltst[ij]<Ltst[ij_Ltstmin]) ij_Ltstmin=ij;
	  if(Lvar[ij]<Lvar[ij_Lvarmin]) ij_Lvarmin=ij;
	  if(Lvarval[ij]<Lvarval[ij_Lvarmin]) ij_Lvarvalmin=ij;
	  //	    if(LD[ij]>1e-20    && LD[ij]<LD[ij_LDmin]) ij_LDmin=ij;
	  //	    if(Ltst[ij]>1e-20    && Ltst[ij]<Ltst[ij_Ltstmin]) ij_Ltstmin=ij;
	  //	    if(Lvar[ij]>1e-20    && Lvar[ij]<Lvar[ij_Lvarmin]) ij_Lvarmin=ij;
	  //	    if(Lvarval[ij]>1e-20 && Lvarval[ij]<Lvarval[ij_Lvarmin]) ij_Lvarvalmin=ij;
	}
      }
    }
    fclose(fploss);
  }
  double Libr=2.0;
  Libmin5=1e30;
  for(i=0;i<_nN*_nm;i++) {
    s_Ltstmin[i]=i;
    //    if(Libmin5>Lib[i]) Libmin5=Lib[i];
  }
  {
    //    Libmin5*=2.;
    for(i=0;i<smax_Ltstmin;i++){
      for(j=i+1;j<_nN*_nm;j++){
	if(Ltst[s_Ltstmin[j]]<Ltst[s_Ltstmin[i]]){
	  int itmp=s_Ltstmin[i];
	  s_Ltstmin[i]=s_Ltstmin[j];
	  s_Ltstmin[j]=itmp;
	}
      }
    }
  }
  {
    //    Libmin5*=2.;
    for(i=0;i<smax_L0vmin;i++){
      for(j=i+1;j<_nN*_nm;j++){
	if(L0v[s_L0vmin[j]]<L0v[s_L0vmin[i]]){
	  int itmp=s_L0vmin[i];
	  s_L0vmin[i]=s_L0vmin[j];
	  s_L0vmin[j]=itmp;
	}
      }
    }
  }
  
  {
    //for local min
    int *ss,itmp,n=_nN*_nm,ns=10,is;
    int n0,m0,n1,n2,i0,j0,ii,jj;
    int localmin;
    ss=(int *)malloc(sizeof(int)*n);
    //Local min of LD
    {
      fprintf(stderr,"##Increasing Lib (Check Overfitting)\n");
      ns=3;
      for(i=0;i<n;i++) ss[i]=i;
      is=0;
      for(i=0;i<n;i++){
	for(j=i+1;j<n;j++){
	  if(Lib[ss[i]]>Lib[ss[j]]){//Increasing
	    //	  if(LD[ss[i]]<LD[ss[j]]){//Decreasing
	    itmp=ss[i];
	    ss[i]=ss[j];
	    ss[j]=itmp;
	  }
	}
	//	if(Lib[ss[i]]>Libmin5) continue;
	//	if(Lvar[ss[i]]<1e-20) continue;
	//	i0=ss[i]/_nm;j0=ss[i]%_nm;
	localmin=1;
	//	for(ii=i0-1;ii<=i0+1;ii++){
	//	  for(jj=j0-1;jj<=j0+1;jj++){
	//	    if(ii<0) continue;
	//	    if(ii>_nN-1) continue;
	//	    if(jj<0) continue;
	//	    if(jj>_nm-1) continue;
	//	    if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	//	  }
	//	}
	if(localmin==1){
	  is++;
	  if(is<=ns){
	    //	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	    //	    fprintf(stderr,"%3d:%3d(N:%3d-%3d)LD=%.3e Lvar=%.3e Lvar0=%.3e Ltst=%.3e Lib%d=%.3e",n0,m0,n1,n2,LD[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],i,Lib[ss[i]]);
	    //	    //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	    //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n0+m0-1-_DN*m_LD));
	    
	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	    fprintf(stderr,"LD=%.3e Lvar=%.3e Lvar0=%.3e Lib%d=%.3e Ltst=%.3e N:%d-:%d M:%d\n",LD[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],i,Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	    
	    //	    fprintf(stderr,"%3d:%3d(N:%3d-%3d)LD=%.3e Lvar=%.3e Lvar0=%.3e Ltst=%.3e Lib%d=%.3e\n",n0,m0,n1,n2,LD[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],i,Lib[ss[i]]);
	    //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n0+m0-1-_DN*m_LD));
	  }
	}
	//	if(is>=ns) break;
      }
    }
    if(!BAGGING){
      Libmin5=Lib[ss[0]];
      fprintf(stderr,"#Below, ignore Lib>(Libmin=%.3e)*%.2f=",Libmin5,Libr);
      Libmin5*=Libr;fprintf(stderr,"%e\n",Libmin5);
      {
	fprintf(stderr,"##Increasing LD with local min of LD\n");
	//      fprintf(stderr,"##Decreasing LD with local min of LD\n");
	ns=3;
	for(i=0;i<n;i++) ss[i]=i;
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    if(LD[ss[i]]>LD[ss[j]]){//Increasing
	      //	  if(LD[ss[i]]<LD[ss[j]]){//Decreasing
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  for(ii=i0-1;ii<=i0+1;ii++){
	    for(jj=j0-1;jj<=j0+1;jj++){
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      //	    if(ii<NN[0]) continue;
	      //	    if(ii>NN[_nN-1]) continue;
	      //	    if(jj<mm[0]) continue;
	      //	    if(jj>mm[_nm-1]) continue;
	      //
	      if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	    }
	  }
	  if(localmin==1){
	    is++;
	    if(is<=ns){
	      //	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	      n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	      fprintf(stderr,"LDmin%3d=%.3e Lvar=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",i,LD[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	      //	    fprintf(stderr,"%3d:%3d(N:%3d-%3d)LDmin%3d=%.3e Lvar=%.3e Lvar0=%.3e Ltst=%.3e Lib=%.3e\n",n0,m0,n1,n2,i,LD[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	      //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LDmin%3d=%e Lvar=%e Ltst=%e\n",n0,m0,n1,n2,i,LD[ss[i]],Lvar[ss[i]],Ltst[ss[i]]);
	      //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LDmin%3d=%e Lvar=%e Ltst=%e LD*Lvar=%e\n",n0,m0,n1,n2,i,LD[ss[i]],Lvar[ss[i]],Ltst[ss[i]],LD[ss[i]]*Lvar[ss[i]]);
	      //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	      //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
	    }
	  }
	  //	if(is>=ns) break;
	}
	fprintf(stderr,"#TotalLocalmins of LD=%d(<%d)\n",is,n);
      }
      {
	double *_L  =(double *)malloc(sizeof(double)*_nN*_nm);
	fprintf(stderr,"##Increasing _L=(Lvar/Lvar0) with local min of LD\n");
	ns=3;
	for(i=0;i<n;i++){
	  //	_L[i]=Lemp[i]-Lvar0[i];
	  //_L[i]=Lib[i]-Lvar0[i];
	  //	_L[i]=Lib[i]+Lvar0[i];//bad
	  //	_L[i]=Lvar0[i];//bad
	  //	_L[i]=Lvar[i];//good
	  _L[i]=Lvar[i]/Lvar0[i];//NG for 2e3
	  //	_L[i]=Lvar[i]-Lvar0[i];//Good
	}
	
	for(i=0;i<n;i++) ss[i]=i;
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    //	  if(_L[ss[i]]<_L[ss[j]]){
	    if(_L[ss[i]]>_L[ss[j]]){
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  for(ii=i0-1;ii<=i0+1;ii++){
	    for(jj=j0-1;jj<=j0+1;jj++){
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	    }
	  }
	  //	localmin=1;
	  if(localmin==1){
	    is++;
	    if(is<=ns){
	      //	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	      n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	      fprintf(stderr,"_L%3d=%.3e Lvar=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",i,_L[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	      //	    fprintf(stderr,"%3d:%3d(N:%3d-%3d)_L%3d=%.3e Lvar=%.3e Lvar0=%.3e Ltst=%.3e Lib=%.3e",n0,m0,n1,n2,i,_L[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	      //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	      //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
	    }
	  }
	}
	free(_L);
      }
      {
	double *_LD2  =(double *)malloc(sizeof(double)*_nN*_nm);
	//      fprintf(stderr,"##Increasing LD with local min of LD\n");
	fprintf(stderr,"##Decreasing LD2 with local min of LD\n");
	ns=3;
	for(i=0;i<n;i++){
	  i0=i/_nm;j0=i%_nm;
	  ii=i0-1;if(ii<0) ii=0;
	  //	_LD2[i]=Lib[ii*_nm+j0]-Lib[i];//060529
	  //_LD2[i]=-Lib[ii*_nm+j0];//060529
	  //_LD2[i]=LD[i]-LD[ii*_nm+j0];//060529
	  //	_LD2[i]=LD[ii*_nm+j0]-LD[i];ii=i0+1;if(ii>=_nN) ii=_nN-1;_LD2[i] = (LD[ii*_nm+j0]-LD[i])/_LD2[i];//060529
	  _LD2[i]=LD[ii*_nm+j0]-LD[i];_LD2[i] = 1./_LD2[i];//060529
	}
	
	for(i=0;i<n;i++) ss[i]=i;
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    if(_LD2[ss[i]]<_LD2[ss[j]]){
	      //	  if(_LD2[ss[i]]>_LD2[ss[j]]){
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  for(ii=i0-1;ii<=i0+1;ii++){
	    for(jj=j0-1;jj<=j0+1;jj++){
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      //	    if(ii<NN[0]) continue;
	      //	    if(ii>NN[_nN-1]) continue;
	      //	    if(jj<mm[0]) continue;
	      //	    if(jj>mm[_nm-1]) continue;
	      //
	      if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	    }
	  }
	  if(localmin==1){
	    is++;
	    if(is<=ns){
	      n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	      fprintf(stderr,"LD2max%3d=%.3e Lvar=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",i,_LD2[ss[i]],Lvar[ss[i]],Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	      //	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	      //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD2:%3d=%e Lvar=%e Ltst=%e\n",n0,m0,n1,n2,i,LD[ss[i]],Lvar[ss[i]],Ltst[ss[i]]);
	      //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD2:%3d=%e Lvar=%e Ltst=%e LD*Lvar=%e\n",n0,m0,n1,n2,i,LD[ss[i]],Lvar[ss[i]],Ltst[ss[i]],LD[ss[i]]*Lvar[ss[i]]);
	      //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	      //	    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
	    }
	    if(is>=ns) break;
	  }
	}
	//      fprintf(stderr,"#TotalLocalmins of LD=%d(<%d)\n",is,n);
	free(_LD2);
      }
      //local min of Lvar 
      {
	fprintf(stderr,"##Increasing Lvar with local min of Lvar\n");
	ns=3;
	for(i=0;i<n;i++) ss[i]=i;
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    if(Lvar[ss[i]]>Lvar[ss[j]]){
	      //	  if(Lvar[ss[i]]<Lvar[ss[j]]){
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  for(ii=i0-1;ii<=i0+1;ii++){
	    for(jj=j0-1;jj<=j0+1;jj++){
	      //	  fprintf(stderr,"ii,jj=%d:%d\n",ii,jj);
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      if(Lvar[ii*_nm+jj]<Lvar[ss[i]]) {localmin=0;break;}
	    }
	  }
	  if(localmin==1){
	    is++;
	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	    fprintf(stderr,"LD=%.3e Lvarmin%3d=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%.3e Lvarmin%3d=%.3e Lvar0=%.3e Ltst=%.3e Lib=%.3e",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	    //	  n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%e Lvarmin%3d=%e Ltst=%e\n",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Ltst[ss[i]]);
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
	    if(is>=ns) break;
	  }
	}
      }
      {
	//      fprintf(stderr,"##global Lvar max with local min\n");
	fprintf(stderr,"##Decreasing Lvar with local min of LD\n");
	ns=3;
	for(i=0;i<n;i++) ss[i]=i;
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    //	  if(Lvar[ss[i]]>Lvar[ss[j]]){
	    if(Lvar[ss[i]]<Lvar[ss[j]]){
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  if(Lib[ss[i]]>Libmin5) continue;
	  for(ii=i0-1;ii<=i0+1;ii++){
	    for(jj=j0-1;jj<=j0+1;jj++){
	      //	  fprintf(stderr,"ii,jj=%d:%d\n",ii,jj);
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      if(Lvar[ii*_nm+jj]<Lvar[ss[i]]) {localmin=0;break;}
	    }
	  }
	  if(localmin==1){
	    is++;
	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	    fprintf(stderr,"LD=%.3e Lvarmax%3d=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%.3e Lvarmax%3d=%.3e Lvar0=%.3e Ltst=%.3e Lib=%.3e",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	  n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%e Lvarmin%3d=%e Ltst=%e\n",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Ltst[ss[i]]);
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    if(is>=ns) break;
	  }
	}
      }
      //global Lvar min and local LDmin
      {
	fprintf(stderr,"##Increasing Lvar with local min of LD (9neighbour of (l1,ld) **Use this or the next)** \n");
	//      fprintf(stderr,"##global min of Lvar with local min of LD\n");
	ns=3;
	for(i=0;i<n;i++) ss[i]=i;
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    if(Lvar[ss[i]]>Lvar[ss[j]]){
	      //if(Lvar[ss[i]]<Lvar[ss[j]]){//060517
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  for(ii=i0-1;ii<=i0+1;ii++){
	    for(jj=j0-1;jj<=j0+1;jj++){
	      //	  fprintf(stderr,"ii,jj=%d:%d\n",ii,jj);
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	    }
	  }
	  
	  if(localmin==1){
	    is++;
	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	    fprintf(stderr,"LD=%.3e Lvarmin%2d=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	    //	  n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	    //	  fprintf(stderr,"#%2d:%2d(N:%2d-%2d) LD=%.3e Lvarmin%2d=%.3e Lvar0=%.3e Ltst=%.3e Lib=%.3e",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%e Lvarmin%3d=%e Ltst=%e\n",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Ltst[ss[i]]);
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    if(is>=ns) break;
	  }
	}
      }
      
      {
	fprintf(stderr,"##Increasing Lvar with local min of LD (9neighbour of (l1,l2)**Use this or the above)**) \n");
	ns=3;
	for(i=0;i<n;i++) ss[i]=i;
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    if(Lvar[ss[i]]>Lvar[ss[j]]){
	      //	  if(Lvar[ss[i]]<Lvar[ss[j]]){//060517
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  {
	    int iii;
	    for(iii=0;iii<9;iii++){
	      if(iii==0){ii=i0-1;jj=j0  ;}//l1-1,l2-1
	      if(iii==1){ii=i0-1;jj=j0+1;}//l1-1,l2
	      if(iii==2){ii=i0-1;jj=j0+2;}//l1-1,l2+1
	      if(iii==3){ii=i0  ;jj=j0-1;}//l1-1,l2-1
	      if(iii==4){ii=i0  ;jj=j0  ;}//l1-1,l2
	      if(iii==5){ii=i0  ;jj=j0+1;}//l1-1,l2+1
	      if(iii==6){ii=i0+1;jj=j0-2;}//l1-1,l2-1
	      if(iii==7){ii=i0+1;jj=j0-1;}//l1-1,l2
	      if(iii==8){ii=i0+1;jj=j0  ;}//l1-1,l2+1
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	    }
	  }
	  
	  if(localmin==1){
	    is++;
	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	    fprintf(stderr,"LD=%.3e Lvarmin%3d=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d D:%d m:%d\n",LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	    //	  n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	    //	  //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%e Lvarmin%3d=%e Ltst=%e\n",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Ltst[ss[i]]);
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%.3e Lvarmin%3d=%.3e Lvar0=%.3e Ltst=%.3e Lib=%.3e",n0,m0,n1,n2,LD[ss[i]],i,Lvar[ss[i]],Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	    //	  //	  fprintf(stderr,"**N:%d-%d\n",n0+_DN,n2=n0+m0-2);
	    //	  //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
	    if(is>=ns) break;
	  }
	}
      }
      
      {
	double *_Lvar  =(double *)malloc(sizeof(double)*_nN*_nm);
	
	fprintf(stderr,"##Increasing |Lvar-Lvar0|\n");
	ns=3;
	for(i=0;i<n;i++){
	  ss[i]=i;
	  _Lvar[i]=Lvar[i]-Lvar0[i];//060529
	  //	_Lvar[i]=fabs(Lvar[i]/Lvar0[i]-1.2);//060529
	  //	_Lvar[i]=fabs((Lvar[i]-Lvar0[i])/Lib[i]);//060518??
	  //	_Lvar[i]=Lvar[i]/Lvar0[i];
	  //	_Lvar[i]=fabs(Lvar[i]-Lvar0[i]);//good one
	  //	_Lvar[i]=fabs((Lvar[i]-Lvar0[i])/Lvar0[i]);//060518??
	  //	_Lvar[i]=fabs((Lvar[i]-Lvar0[i])/sqrt(Lib[i]));//060518??
	  //	_Lvar[i]=fabs(Lvar[i]-Lvar0[i])/Lvar[i];
	  //	_Lvar[i]=fabs(Lvar[i]-Lvar0[i])/Lvar0[i];
	}
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    if(_Lvar[ss[i]]>_Lvar[ss[j]]){
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  //	for(ii=i0-1;ii<=i0+1;ii++){
	  //	  for(jj=j0-1;jj<=j0+1;jj++){
	  //	    //	  fprintf(stderr,"ii,jj=%d:%d\n",ii,jj);
	  //	    if(ii<0) continue;
	  //	    if(ii>_nN-1) continue;
	  //	    if(jj<0) continue;
	  //	    if(jj>_nm-1) continue;
	  //	    if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	  //	  }
	  //	}
	  if(localmin==1){
	    is++;
	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	    fprintf(stderr,"LD=%.3e Lvar=%.3e Lvar0min%3d=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",LD[ss[i]],Lvar[ss[i]],i,Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	    //	  n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%.3e Lvar=%.3e Lvar0min%3d=%.3e Ltst=%.3e Lib=%.3e",n0,m0,n1,n2,LD[ss[i]],Lvar[ss[i]],i,Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	    //	  //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
	    if(is>=ns) break;
	  }
	}
      }
      {
	double *_Lvar  =(double *)malloc(sizeof(double)*_nN*_nm);
	
	fprintf(stderr,"##Increasing |Lvar-Lvar0| with local min of LD(9neighbour of (l1,ld)\n");
	ns=3;
	for(i=0;i<n;i++){
	  ss[i]=i;
	  _Lvar[i]=Lvar[i]-Lvar0[i];//060529
	  //	_Lvar[i]=fabs(Lvar[i]/Lvar0[i]-1.2);//060529??
	  //	_Lvar[i]=fabs((Lvar[i]-Lvar0[i])/Lib[i]);//060518??
	  //	_Lvar[i]=Lvar[i]/Lvar0[i];
	  //	_Lvar[i]=fabs(Lvar[i]-Lvar0[i]);//good one
	  //	_Lvar[i]=fabs((Lvar[i]-Lvar0[i])/Lvar0[i]);//060518??
	  //	_Lvar[i]=fabs((Lvar[i]-Lvar0[i])/sqrt(Lib[i]));//060518??
	  //	_Lvar[i]=fabs(Lvar[i]-Lvar0[i])/Lvar[i];
	  //	_Lvar[i]=fabs(Lvar[i]-Lvar0[i])/Lvar0[i];
	}
	is=0;
	for(i=0;i<n;i++){
	  for(j=i+1;j<n;j++){
	    if(_Lvar[ss[i]]>_Lvar[ss[j]]){
	      itmp=ss[i];
	      ss[i]=ss[j];
	      ss[j]=itmp;
	    }
	  }
	  if(Lib[ss[i]]>Libmin5) continue;
	  if(Lvar[ss[i]]<1e-20) continue;
	  if(Lvar[ss[i]]<Lvar0[ss[i]]) continue;
	  i0=ss[i]/_nm;j0=ss[i]%_nm;
	  localmin=1;
	  for(ii=i0-1;ii<=i0+1;ii++){
	    for(jj=j0-1;jj<=j0+1;jj++){
	      //	  fprintf(stderr,"ii,jj=%d:%d\n",ii,jj);
	      if(ii<0) continue;
	      if(ii>_nN-1) continue;
	      if(jj<0) continue;
	      if(jj>_nm-1) continue;
	      if(LD[ii*_nm+jj]<LD[ss[i]]) {localmin=0;break;}
	    }
	  }
	  if(localmin==1){
	    is++;
	    n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;
	    fprintf(stderr,"LD=%.3e Lvar=%.3e Lvar0min%3d=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",LD[ss[i]],Lvar[ss[i]],i,Lvar0[ss[i]],Lib[ss[i]],Ltst[ss[i]],n1,_DN,m0);
	    //	  n0=NN[ss[i]/_nm];m0=mm[ss[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
	    //	  fprintf(stderr,"%3d:%3d(N:%3d-%3d) LD=%.3e Lvar=%.3e Lvar0min%3d=%.3e Ltst=%.3e Lib=%.3e",n0,m0,n1,n2,LD[ss[i]],Lvar[ss[i]],i,Lvar0[ss[i]],Ltst[ss[i]],Lib[ss[i]]);
	    //	  //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    //	  fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
	    if(is>=ns) break;
	  }
	}
      }
    }
    static char pr1[buffsize];
    fp=fopen(fnplt,"w+");
    for(i=0;i<smax_Ltstmin;i++){
      n0=NN[s_Ltstmin[i]/_nm];m0=mm[s_Ltstmin[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;//n1=n0+1;n2=n0+m0-2;
      //      fprintf(stderr,"t:%s v:%s LD%.2eLvar%.2eLvar0%.2eLib%.3eLtst%d=%.3eOvf%.3eLb'%.3eN:%d-:%dM:%drsa:%s\n",
      //	      fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[s_Ltstmin[i]],Lvar[s_Ltstmin[i]],Lvar0[s_Ltstmin[i]],Lib[s_Ltstmin[i]],i,Ltst[s_Ltstmin[i]],
      //	      //	      Ltst[s_Ltstmin[i]]-Lib[s_Ltstmin[i]],//overfit
      //	      Ltst[s_Ltstmin[i]]+Lvar0[s_Ltstmin[i]]-Lib[s_Ltstmin[i]],//overfit
      //	      (Lib[s_Ltstmin[i]]-Lvar0[s_Ltstmin[i]])/Ltst[s_Ltstmin[i]],//Lbias-Ovrfit
      //	      n1,_DN,m0,rsa);
      if(BAGGING==2){
	//	fprintf(stderr,"t:%s v:%s Ltst%d=%.3e(LvarPop%.3e)LbiasPop%.3e,LbiasPopB%.3eLib%.3eN:%d-:%dM:%drsa:%sbst:%d:%d\n",
	fprintf(stderr,"t:%s v:%s Lob%d=%.3e(uc%.3e)Lbias%.3e,LbiasPopB%.3eLib%.3eLemp%.3eH%.4fN:%d-:%dM:%drsa:%sbst:%d:%d\n",
		fnbody(fngiven,pr),fnbody(fnvalid,pr1),
		i,Ltst[s_Ltstmin[i]],
		LD[s_Ltstmin[i]],
		Ltst[s_Ltstmin[i]]-LD[s_Ltstmin[i]],//Ltst-Lvar=Lbias+Lnoise
		Ltst[s_Ltstmin[i]]+(1.-rs_alpha)*LD[s_Ltstmin[i]],//kc=2:coverage factor for 95% extended uncertainty 
		//		Ltst[s_Ltstmin[i]]-(rs_alpha-1.)*LD[s_Ltstmin[i]],//kc=2:coverage factor for 95% extended uncertainty 
		//Ltst[s_Ltstmin[i]]-5.*LD[s_Ltstmin[i]]-4.*sqrt((LD[s_Ltstmin[i]])*(Ltst[s_Ltstmin[i]]-LD[s_Ltstmin[i]])),//kc=2:coverage factor for 95% extended uncertainty 
		//Ltst[s_Ltstmin[i]]+3.*LD[s_Ltstmin[i]]+4.*sqrt((LD[s_Ltstmin[i]])*(Ltst[s_Ltstmin[i]]-LD[s_Ltstmin[i]])),
		//		Ltst[s_Ltstmin[i]]-5.*LD[s_Ltstmin[i]],//kc=2:coverage factor for 95% extended uncertainty 
		//		Ltst[s_Ltstmin[i]]+3.*LD[s_Ltstmin[i]],
		Lib[s_Ltstmin[i]],
		Lemp[s_Ltstmin[i]],
		H0[s_Ltstmin[i]],
		n1,_DN,m0,rsa,t_boost,Boost);
      }
      else{
	fprintf(stderr,"t:%s v:%s LD%.2eLvar%.2eLvar0%.2eLib%.3eH%.4fLtst%d=%.3eN:%d-:%dM:%drsa:%sbst:%d:%d\n",
		fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[s_Ltstmin[i]],Lvar[s_Ltstmin[i]],Lvar0[s_Ltstmin[i]],Lib[s_Ltstmin[i]],
		//      fprintf(stderr,"t:%s v:%s LD%.2eLvar%.2eLvar0%.2eLemp%.3eH%.4fLtst%d=%.3eN:%d-:%dM:%drsa:%sbst:%d:%d\n",
		//	      fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[s_Ltstmin[i]],Lvar[s_Ltstmin[i]],Lvar0[s_Ltstmin[i]],Lemp[s_Ltstmin[i]],
		//fprintf(stderr,"t:%s v:%s LD%.2eLvar%.2eLvar0%.2eLib%.3eH%.4fLtst%d=%.3eN:%d-:%dM:%drsa:%sbst:%d:%d\n",
		//fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[s_Ltstmin[i]],Lvar[s_Ltstmin[i]],Lvar0[s_Ltstmin[i]],Lib[s_Ltstmin[i]],
		H0[s_Ltstmin[i]],
		i,Ltst[s_Ltstmin[i]],
		n1,_DN,m0,rsa,t_boost,Boost);
	
	//	fprintf(stderr,"t:%s v:%s LD%.2eLvar%.2eLvar0%.2eLib%.3eLtst%d=%.3eLtr+Lvl%.3eN:%d-:%dM:%drsa:%sbst:%d\n",
	//		fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[s_Ltstmin[i]],Lvar[s_Ltstmin[i]],Lvar0[s_Ltstmin[i]],Lib[s_Ltstmin[i]],i,Ltst[s_Ltstmin[i]],
	//		Ltst[s_Ltstmin[i]]+Lib[s_Ltstmin[i]],n1,_DN,m0,rsa,t_boost);
      }
      ////      fprintf(stderr,"t:%s v:%s LD%.2eLvar%.2eLvar0%.2eLib%.3eLtst%d=%.3eLtr/Lvl%.3fN:%d-:%dM:%drsa:%s\n",
      ////	      fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[s_Ltstmin[i]],Lvar[s_Ltstmin[i]],Lvar0[s_Ltstmin[i]],Lib[s_Ltstmin[i]],i,Ltst[s_Ltstmin[i]],Lib[s_Ltstmin[i]]/Ltst[s_Ltstmin[i]],n1,_DN,m0,rsa);
      //      n0=NN[s_Ltstmin[i]/_nm];m0=mm[s_Ltstmin[i]%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
      //      fprintf(stderr,"t:%s v:%s %d:%d(N:%d-%d) LD   =%.3e Ltst%d=%.3e Lvar=%.3e Lvar0=%.3e Lib=%.3e",
      //	      fnbody(fngiven,pr),fnbody(fnvalid,pr1),n0,m0,n1,n2,LD[s_Ltstmin[i]],i,Ltst[s_Ltstmin[i]],Lvar[s_Ltstmin[i]],Lvar0[s_Ltstmin[i]],Lib[s_Ltstmin[i]]);
      //      //    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_DN*m_LD),(int)(n2=n0+m0-1-_DN*m_LD));
      //      fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
    }
    for(i=0;i<smax_L0vmin;i++){
      n0=NN[s_Ltstmin[i]/_nm];m0=mm[s_Ltstmin[i]%_nm];n1=n0;n2=n0+(m0-1)*_DN;//n1=n0+1;n2=n0+m0-2;
      //    if(BAGGING==2){
      fprintf(stderr,"t:%s v:%s L0v%d=%.3e=%.3e-%.3eLtst(Lob)%.3eLib%.3eLtr%.3eN:%d-:%dM:%drsa:%sbst:%d:%d\n",
	      fnbody(fngiven,pr),fnbody(fnvalid,pr1),
	      i,
	      L0v[s_L0vmin[i]],
	      L0[s_L0vmin[i]],
	      Lvar[s_L0vmin[i]],
	      Ltst[s_L0vmin[i]],
	      Lib[s_L0vmin[i]],
	      Ltr[s_L0vmin[i]],
	      n1,_DN,m0,rsa,t_boost,Boost);
      //    }
    }
    
    
    n0=NN[ij_LDmin/_nm];m0=mm[ij_LDmin%_nm];n1=n0;n2=n0+(m0-1)*_DN;//n1=n0+1;n2=n0+m0-2;
    fprintf(stderr,"t:%s v:%s LDmin=%.3e Lvar=%.3e Lvar0=%.3e Lib=%.3e Ltst=%.3e N:%d-:%d M:%d\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[ij_LDmin],Lvar[ij_LDmin],Lvar0[ij_LDmin],Lib[ij_LDmin],Ltst[ij_LDmin],n1,_DN,m0);
    //    n0=NN[ij_LDmin/_nm];m0=mm[ij_LDmin%_nm];n1=n0;n2=n0+m0-1;//n1=n0+1;n2=n0+m0-2;
    //    fprintf(stderr,"t:%s v:%s %d:%d(N:%d-%d) LDmin=%.3e Ltst=%.3e Lvar=%.3e Lvar0=%.3e Lib=%.3e",
    //	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),n0,m0,n1,n2,LD[ij_LDmin],Ltst[ij_LDmin],Lvar[ij_LDmin],Lvar0[ij_LDmin],Lib[ij_LDmin]);
    //    fprintf(stderr,"**N:%d-%d\n",(int)(n0+_dm*m_LD),(int)(n2=n0+m0-1-_dm*m_LD));
    //    fprintf(stderr,"test=%d %d %d\n", 1/10,8/10,11/10);
    //    fprintf(stderr,"t:%s v:%s ij%d(i%d,j%d) N:%d:%d LDmin=%e Ltst=%e\n",
    //	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),NN[ij_LDmin/_nm],mm[ij_LDmin%_nm],LD[ij_LDmin],Ltst[ij_LDmin]);
  
    fprintf(fp,"set style data linespoints\n");
    fprintf(fp,"set logscale z\n");
    fprintf(fp,"set title \"%s %s N:%d-:%d M:%d LDmin=%e Ltst=%e rsa:%s\"\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),n1,_DN,m0,LD[ij_LDmin],Ltst[ij_LDmin],rsa);
    fprintf(fp,"set xlabel \"l1\";set ylabel \"ld\";set zlabel \"LD\"\n");
    if(BAGGING==2){
      fprintf(fp,"splot \"%s.dat\" using 1:2:4, \"%s.dat\" using 1:2:($4-5*$3), \"%s.dat\" using 1:2:($4+3*$3)\n",fnbody(fnloss,pr),fnbody(fnloss,pr),fnbody(fnloss,pr));
    }
    else{
      //    fprintf(fp,"splot \"%s.dat\" using 1:2:3\n",fnbody(fnloss,pr));
      fprintf(fp,"splot \"%s.dat\" using 1:2:4\n",fnbody(fnloss,pr));
    }
    fprintf(fp,"pause -1 \"hit return for save!\"\n");
    fprintf(fp,"set terminal tgif\n");
    fprintf(fp,"set output \"./lhat.obj\"\n");
    fprintf(fp,"replot\n");
    //
    n0=NN[ij_Ltstmin/_nm];m0=mm[ij_Ltstmin%_nm];n1=n0;n2=n0+(m0-1)*_DN;//n1=n0+1;n2=n0+m0-2;
    fprintf(fp,"set terminal x11\n");
    fprintf(fp,"set title \"%s %s Ltst=%e Ltstmin=%e Lib=%e N:%d-:%d M:%d\"\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),LD[ij_Ltstmin],Ltst[ij_Ltstmin],Lib[ij_Ltstmin],n1,_DN,m0);
    //    fprintf(fp,"splot \"%s.dat\" using 1:2:4\n",fnbody(fnloss,pr));
    fprintf(fp,"set xlabel \"l1\";set ylabel \"ld\";set zlabel \"4Ltst,8Lib\"\n");
    fprintf(fp,"splot \"%s.dat\" using 1:2:4, \"%s.dat\" using 1:2:8\n",fnbody(fnloss,pr),fnbody(fnloss,pr));
    fprintf(fp,"pause -1 \"hit return for save !\"\n");
    fprintf(fp,"set terminal tgif\n");
    fprintf(fp,"set output \"./lhat.obj\"\n");
    fprintf(fp,"replot\n");
    //
    n0=NN[ij_Lvarmin/_nm];m0=mm[ij_Lvarmin%_nm];n1=n0;n2=n0+(m0-1)*_DN;//n1=n0+1;n2=n0+m0-2;
    fprintf(fp,"set terminal x11\n");
    fprintf(stderr,"t:%s v:%s Lvarmin=%e Lvarval=%e N:%d-:%d M:%d\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),Lvar[ij_Lvarmin],Lvarval[ij_Lvarmin],n1,_DN,m0);
    fprintf(fp,"set title \"Lvar %s %s Lvarmin=%e Lvarval=%e N:%d-:%d M:%d\"\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),Lvar[ij_Lvarmin],Lvarval[ij_Lvarmin],n1,_DN,m0);
    fprintf(fp,"set xlabel \"l1\";set ylabel \"ld\";set zlabel \"5Lvar,7Lvar0\"\n");
    //    fprintf(fp,"splot \"%s.dat\" using 1:2:5\n",fnbody(fnloss,pr));
    fprintf(fp,"splot \"%s.dat\" using 1:2:5, \"%s.dat\" using 1:2:7\n",fnbody(fnloss,pr),fnbody(fnloss,pr));
    fprintf(fp,"pause -1 \"hit return for save !\"\n");
    fprintf(fp,"set terminal tgif\n");
    fprintf(fp,"set output \"./lhat.obj\"\n");
    fprintf(fp,"replot\n");
    //
    n0=NN[ij_Lvarvalmin/_nm];m0=mm[ij_Lvarvalmin%_nm];n1=n0;n2=n0+(m0-1)*_DN;//n1=n0+1;n2=n0+m0-2;
    fprintf(fp,"set terminal x11\n");
    fprintf(stderr,"t:%s v:%s Lvar=%e Lvarvalmin=%e N:%d-:%d M:%d\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),Lvar[ij_Lvarvalmin],Lvarval[ij_Lvarvalmin],n1,_DN,m0);
    fprintf(fp,"set title \"%s %s Lvar=%e Lvarvalmin=%e N:%d-:%d M:%d\"\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),Lvar[ij_Lvarvalmin],Lvarval[ij_Lvarvalmin],n1,_DN,m0);
    fprintf(fp,"set xlabel \"l1\";set ylabel \"ld\";set zlabel \"6Lvarval\"\n");
    fprintf(fp,"splot \"%s.dat\" using 1:2:6\n",fnbody(fnloss,pr));//Lvarval
    fprintf(fp,"pause -1 \"hit return for save !\"\n");
    fprintf(fp,"set terminal tgif\n");
    fprintf(fp,"set output \"./lhat.obj\"\n");
    fprintf(fp,"replot\n");
    //
    fprintf(fp,"set terminal x11\n");
    fprintf(stderr,"t:%s v:%s Lvar=%e Lvarvalmin=%e N:%d-:%d M:%d\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),Lvar[ij_Lvarvalmin],Lvarval[ij_Lvarvalmin],n1,_DN,m0);
    fprintf(fp,"set title \"Lvar-Lvar0 %s %s Lvar=%e Lvarvalmin=%e N:%d-:%d M:%d\"\n",
	    fnbody(fngiven,pr),fnbody(fnvalid,pr1),Lvar[ij_Lvarvalmin],Lvarval[ij_Lvarvalmin],n1,_DN,m0);
    //    fprintf(fp,"splot \"%s.dat\" using 1:2:7\n",fnbody(fnloss,pr));//Lvar-Lvar0
    fprintf(fp,"set xlabel \"l1\";set ylabel \"ld\";set zlabel \"5Lvar-7Lvar0\"\n");
    fprintf(fp,"splot [][][0.00001:1] \"%s.dat\" using 1:2:($5-$7)\n",fnbody(fnloss,pr));//Lvar-Lvar0
    //    fprintf(fp,"splot \"%s.dat\" using 1:2:($5/$7)\n",fnbody(fnloss,pr));//Lvar-Lvar0
    //    fprintf(fp,"splot [2:][2:][0.0001:1] \"%s.dat\" using 1:2:5, \"%s.dat\" using 1:2:7 \n",fnbody(fnloss,pr),fnbody(fnloss,pr));//Lvar-Lvar0
    fprintf(fp,"pause -1 \"hit return for save !\"\n");
    fprintf(fp,"set terminal tgif\n");
    fprintf(fp,"set output \"./lhat.obj\"\n");
    fprintf(fp,"replot\n");
    //
    fprintf(fp,"quit\n");
    fclose(fp);
    if(dsp==1 && DISP==1){
      sprintf(cmd,"cd %s;xterm -geometry 40x5-0+0 -e gnuplot %s.plt",rdir,fnbody(fnplt,pr));
      fprintf(stderr,"#Executing '%s'.\n",cmd);
      sprintf(&cmd[strlen(cmd)],"&");
      system(cmd);
    }
  }
  return(0);
}
#endif
