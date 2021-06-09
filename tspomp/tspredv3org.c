#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include "my_misc.c"
#include "calcAinvb.c"
static char pr[128];//for fnbody
#define PI 3.141592653589793
int usage(int argc,char **argv){
  fprintf(stderr,"Differential version.\n");
  fprintf(stderr,"Usage:%s <file-name-timeseries> <ttrainfrom>:<ttrainto>:<tpredfrom>:<tpredto> [Dy:0|1] [mp:<mp>] <ens2ge options from 3rd ones>\n",argv[0]);
  fprintf(stderr,
          "      y[0],y[1],... are the data in <file-name-timeseries>. \n"
	  "      y[<ttrainfrom>],...,y[<ttrainto>-1] are used for training, and\n"
	  "      y[<tpredfrom>] ,...,y[<tpredto>-1] are going to be predicted. \n"
	  "      mp:<mpn>:<mpd>:<tau_c> <mpd>*i for i=1,2,<nmp> is the number of average for prediction. \n"
	  "      DiffMode:<DiffMode>    <DiffMode>==1 for differential learning, 0 for direct learning. \n"
	  "      r:r1:r2\n"
	  "      Hosei:<Hosei> <Hosei>=1,2,3,..\n"
	  //	  "      ymodify:<ymodify> <ymodify> == 1 for use y[t]=log(y~[t]), ==0 for direct y[t]\n"
	  "      ycode:<ycode> <ycode> == 1 for use y[t]=log(y~[t]), ==0 for direct y[t]\n"
	  );
  return(0);
}
#define BAG 0
#define BOOST 1

#define square(x) ((x)*(x))
int main(int argc,char **argv)
{
  int i,j;
  int rs_method,rs_seed,rs_ens;double rs_alpha=-1;
  //  int BagBoost=BAG;//activate 2011.11.02
  int BagBoost=BOOST;//
  int mpn=1,mpd=1,m;
  double tau_c=1;
  int *rsmo=(int *)malloc(sizeof(int)*argc);
  char *pupdate="1";
  for(i=3;i<argc;i++) rsmo[i]=1;
  
  if(argc < 5){
    usage(argc,argv);
    return(1);
  }
  int ttrainfrom,ttrainto,tpredfrom,tpredto,k=1;
  FILE *fp;
  char fntrain[256];
  char fnpred[256]; 
  char fnresult0[256],*fnresult; 
  double ymin=1e20,ymax=-1e20;
  int ynormalize=0,xnormalize=0;
  int dynormalize=0,dxnormalize=0;
  double ymin1=0,ymax1=1,y0m=0.,y1m=0.,y0M=0,y1M=0.;
  //  int DiffMode=1;
  int DiffMode=0;
#define DirectMODE 0
#define DiffMODE 1
  int r1=0,r2=0;double r12;
  int Hosei=1;
  int Tbst=1;//1 for Bagging
  int ycode=0;
  int N;
#define SSP 1
#define MSP 0
  int ssp=0;
  int DISP=1;
  int T=100;
  int _N,_DN=1,_nN,*NN,_N1,_N2;
  int n_tspredv3=0;
  sscanf(argv[2],"%d-%d:%d-%d",&ttrainfrom,&ttrainto,&tpredfrom,&tpredto);
  
  if((fp=fopen(argv[1],"r"))==NULL){
    fprintf(stderr,"'%s' could not be opened.",argv[1]);
    return(-1);
  }
  for(i=3;i<argc;i++){
    if(strncmp(argv[i],"k:",2)==0) sscanf(&argv[i][2],"%d",&k);
    else if(strncmp(argv[i],"T:",2)==0) sscanf(&argv[i][2],"%d",&T);
    else if(strncmp(argv[i],"mp:",3)==0){
      sscanf(&argv[i][3],"%d:%d:%lf",&mpn,&mpd,&tau_c);
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"DISP:",5)==0){sscanf(&argv[i][5],"%d",&DISP);}
    else if(strncmp(argv[i],"dy:",3)==0){dynormalize=i;rsmo[i]=0;}
    else if(strncmp(argv[i],"dx:",3)==0){dxnormalize=i;rsmo[i]=0;}
    else if(strncmp(argv[i],"y:",2)==0){ynormalize=i;}
    else if(strncmp(argv[i],"x:",2)==0){xnormalize=i;}
    else if(strncmp(argv[i],"r:",2)==0){
      sscanf(&argv[i][2],"%d:%d",&r1,&r2);
      r12=(double)r1/r2;
    }
    else if(strncmp(argv[i],"ycode:",6)==0){
      sscanf(&argv[i][6],"%d",&ycode);
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"DiffMode:",9)==0){
      sscanf(&argv[i][9],"%d",&DiffMode);
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"Hosei:",6)==0){
      sscanf(&argv[i][6],"%d",&Hosei);
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"N:",2)==0){
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
      int jj;
      for(jj=0;jj<_nN;jj++) NN[jj]=_N1+_DN*jj;
      NN[_nN]=0;
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"NRn:",4)==0){
      char *p0=&argv[i][4];
      char *p;
      int _n;
      sscanf(p0,"%d-%d:%d",&_N1,&_N2,&_n);
      double _r=exp(log(_N2/_N1)/(_n-1));
      _nN=_n;
      NN=(int *)malloc(sizeof(int)*(_nN+1));
      int jj;
      for(jj=0;jj<_nN;jj++) NN[jj]=_N1*pow(_r,jj)+0.5;
      fprintf(stderr,"###N:");
      for(jj=0;jj<_nN;jj++){
	fprintf(stderr,"%d ",NN[jj]);
      }
      fprintf(stderr,"\n");
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
 
    else if(strncmp(argv[i],"N:",2)==0){
      sscanf(&argv[i][2],"%d",&N);
    }
    else if(strncmp(argv[i],"Tbst:",5)==0) {
      sscanf(&argv[i][5],"%d",&Tbst);
      BagBoost=BOOST;//
      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"rsa:",4)==0){
      int ncol=0;
      char *p=&argv[i][4];
      for(;*p!=0;p++) if(*p==':') ncol++;
      char *rsa=&argv[i][4];
      if(ncol==2) {sscanf(rsa,"%d:%lf:%d",&rs_method,&rs_alpha,&rs_seed);rs_ens=1;}
      else if(ncol==3) sscanf(rsa,"%d:%lf:%d:%d",&rs_method,&rs_alpha,&rs_seed,&rs_ens);
      //      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"ssp:",4)==0) {
      sscanf(&argv[i][4],"%d",&ssp);
      rsmo[i]=1;      //      rsmo[i]=0;
    }
    else if(strncmp(argv[i],"pupdate:",8)==0) pupdate=&argv[i][8];
  }
  if(tpredfrom<k) tpredfrom=k;
  int num0=tpredto-tpredfrom;

#define buffsize 512
#define cmdsize 10240
  //#define buffsize 1024
  char buff[buffsize];
  for(i=0;;){
    fgets(buff,buffsize,fp);
    if(feof(fp)) break;
    if(buff[0]=='#') continue;
    i++;
  }
  int ndata=i,ndata1=i-1;
  if(ttrainto>ndata) ttrainto=ndata;
  rewind(fp);
  double *y0;
  double *y00=(double *)malloc(sizeof(double)*(ndata));
  double *y0l; 
  //  i=0;fgets(buff,buffsize,fp);sscanf(buff,"%lf",&y0[i]);
  for(i=0;i<ndata;){
    fgets(buff,buffsize,fp);
    if(feof(fp)) break;
    if(buff[0]=='#') continue;
    sscanf(buff,"%lf",&y00[i]);
    i++;
  }
  fclose(fp);
  if(ycode==1){
    y0l=(double *)malloc(sizeof(double)*(ndata));
    for(i=0;i<ndata;i++) y0l[i]=log(y00[i]);
    y0=y0l;
  }
  else{
    y0=y00;
  }
  //
  {
    DIR *pdir;
    if((pdir=opendir("./tmp"))==NULL) system("mkdir ./tmp"); else closedir(pdir);
    if((pdir=opendir("./result-ensrs"))==NULL) system("mkdir ./result-ensrs"); else closedir(pdir);
    if((pdir=opendir("./result-ensrs/tmp"))==NULL) system("mkdir ./result-ensrs/tmp"); else closedir(pdir);
  }
  ///
  double mse0=0,mean0=0;
  int tevalto=tpredto;
  if(ndata<tevalto) tevalto=ndata;
  int neval=tevalto-tpredfrom;
  if(neval>=1){
    for(i=tpredfrom;i<tevalto;i++) mean0+=y00[i];
    mean0/=neval;
    for(i=tpredfrom;i<tevalto;i++) mse0+=square(y00[i]-mean0);
    mse0/=neval;
  }
  else mse0=(y00[ndata-1]+y00[ndata-2])/2;
  char cmd[cmdsize];
  double *ypm=(double *)malloc(sizeof(double)*(tpredto)*(mpn+1));
  double *yp=&ypm[tpredto*mpn];

//  double **ypN=(double **)malloc(sizeof(double*)*(_nN+1));
//  for(i=0;i<=_nN;i++) ypN[i]=(double*)malloc(sizeof(double)*(tpredto-tpredfrom));
//  double *ypNmean=ypN[_nN];
//  double *skwN=(double *)malloc(sizeof(double)*(_nN));

  //  double *ypN=(double *)malloc(sizeof(double)*(_nN)*(tpredto-tpredfrom+1));
  //  double *skwN=(double *)malloc(sizeof(double)*(_nN));
  /////////////////////////////////  
  char *fn_predall="tspall.dat";
  //  char *fn_predall="predict+all.dat";
  int n_predall=0;
  char *fn_lossall="loss+all.dat";
  //////////////////
  if(DiffMode==1){//             dy
    double *ydpm=(double *)malloc(sizeof(double)*(tpredto)*(mpn+1));
    double *ydp=&ydpm[tpredto*mpn];
    int i0m;
    char fnpredlong[128];
    double *yd=(double *)malloc(sizeof(double)*(ndata));
    if(ynormalize>1) rsmo[ynormalize]=0;
    if(xnormalize>1) rsmo[xnormalize]=0;
    {
      for(i=1;i<ndata;i++) {
	yd[i]=y0[i]-y0[i-1];
	if(ymin>yd[i]) ymin=yd[i];
	else if(ymax<yd[i]) ymax=yd[i];
      }
      fprintf(stderr,"\nThe range of dy:%f:%f\n",ymin,ymax);
    }
    double meand0=0,msed0=0;
    if(neval>0){
      for(i=tpredfrom;i<tevalto;i++) meand0+=yd[i];
      meand0/=neval;
      for(i=tpredfrom;i<tevalto;i++) msed0+=square(yd[i]-meand0);
      msed0/=neval;
    }
    else msed0=1e20;
    int iN;
    for(iN=0;iN<_nN;iN++){
      N=NN[iN];
      for(m=0;m<mpn;m++){
	//      i0m=m*ttrainto;
	i0m=m*tpredto;
	int tmtrainto=ttrainto-m*mpd;//
	int tmpredfrom=tpredfrom-m*mpd;
	for(i=0;;i++){
	  ydpm[i+i0m]=yd[i];
	  //      fprintf(stderr,"%d)%e=%e\n",i,ydpm[i],yd[i]);
	  //	if(i>=tmtrainto-1) break;
	  if(i>=tmpredfrom-1) break;
	}
	//      ypm[i+i0m]=y0[(i)];//i==tmtrainto-1
	ypm[tmpredfrom-1+i0m]=y0[(i)];//i==tmtrainto-1
	//
	//      sprintf(fnpredlong,"result-ensrs/tmp/%s+%d-%d:%d-%dk%d-dy-predict+.dat",fnbody(argv[1],pr),ttrainfrom,ttrainto-m*mpd,tpredfrom-m*mpd,tpredto,k);
	sprintf(fnpredlong,"result-ensrs/tmp/%s+%d-%d:%d-%dk%dN%da%gb%d-dy-predict+.dat",fnbody(argv[1],pr),ttrainfrom,tmtrainto,tmpredfrom,tpredto,k,N,rs_alpha,rs_ens);
	if((fp=fopen(fnpredlong,"r"))!=NULL && *pupdate=='0'){
	  fprintf(stderr,"#Read from '%s'\n",fnpredlong);
	  for(i=tmpredfrom;i<tpredto;i++){
	    fgets(buff,buffsize,fp);
	    if(feof(fp)) break;
	    sscanf(buff,"%lf%lf",&ypm[i+i0m],&ydpm[i+i0m]);
	  }
	  fclose(fp);
	}
	else{
	  if(rs_method==-1){
	    //	if(rs_method==-1 && rs_alpha<0){
	    sprintf(fntrain,"tmp/%s:dy%d-%d.dat",fnbody(argv[1],pr),ttrainfrom+1,tmtrainto);//sprintf(fntrain,"tmp/%strain:dy1-%d.dat",fnbody(argv[1],pr),tmtrainto-1);
	    fp=fopen(fntrain,"w+");
	    //	  for(i=1;i<ndata;i++) fprintf(fp,"%.7e\n",yd[i]);//train
	    for(i=0;i<ndata;i++) fprintf(fp,"%.7e\n",yd[i]);//train
	    fclose(fp);

            //sprintf(cmd,"./ensrs %s 2:%d:%g:%d %d-%d:1 bg:/dev/null Tsk:0:%d-%d:%d-%d",fntrain,rs_ens,rs_alpha,rs_seed, N, N, ttrainfrom+1,tmtrainto,tmpredfrom,tpredto);
	    sprintf(cmd,"./ens2ge %s /dev/null Tsk:0:%d-%d:%d-%d",fntrain,ttrainfrom+1,tmtrainto,tmpredfrom,tpredto);
	    for(j=3;j<argc;j++) { if(rsmo[j]==1) sprintf(&cmd[strlen(cmd)]," %s",argv[j]);}
	    sprintf(&cmd[strlen(cmd)]," dsp:0 N:%d-%d:1",N,N);
	    if(dynormalize==0) sprintf(&cmd[strlen(cmd)]," y:%e:%e:%e:%e:%e:%e:%e:%e",ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
	    else sprintf(&cmd[strlen(cmd)]," y:%s",&argv[dynormalize][3]);
	    fprintf(stderr,"Executing1 '%s'\n",cmd);
	    system(cmd);
	    fp=fopen("predict+.dat","r");
	    for(i=tmpredfrom;i<tpredto;i++){	    //	  for(i=tmtrainto;i<tpredto;i++){
	      fgets(buff,buffsize,fp);
	      if(feof(fp)) break;
	      sscanf(buff,"%lf",&ydpm[i+i0m]);
	      ypm[i+i0m]=ypm[(i-1)+i0m]+ydpm[i+i0m];
	    }
	    fclose(fp);
	    {
	      fprintf(stdout,"#exec0n");
	      FILE *fp;
	      int initpredall=0;
	      if((fp=fopen(fn_predall,"r"))==NULL){
		initpredall=1;
	      }
	      else fclose(fp);
	      if(n_predall==0 && initpredall==1){
		//		s;printf(cmd,"cat predict+.dat|awk '{printf(\"%d %.7e %.7e\",($2+%d),$3,$1);}'> %s",tpredfrom,fn_predall);
		sprintf(cmd,"cat predict+.dat|awk '{print ($2+%d),$3,$1;}'> %s",tpredfrom,fn_predall);
		fprintf(stdout,"#executing %s\n",cmd);
		system(cmd);
		sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' > %s",N,fn_lossall);system(cmd);
		system(cmd);

	      }
	      else{
		sprintf(cmd,"cp %s p1.dat;cat predict+.dat |awk '{print $1}'| paste p1.dat - > %s",fn_predall,fn_predall);
		//printf(cmd,"cp %s p1.dat;cat predict+.dat |awk '{print $1}'| paste p1.dat - > %s",fn_predall,fn_predall);
		fprintf(stderr,"#executing %s\n",cmd);
		system(cmd);
		sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' >> %s",N,fn_lossall);system(cmd);
	      }
	      n_predall++;
	    }

	  }
	  else if(BagBoost==BOOST){
	    sprintf(fntrain,"tmp/%s:dy%d-%d.dat",fnbody(argv[1],pr),ttrainfrom+1,tmtrainto);
	    fp=fopen(fntrain,"w+");
	    for(i=k+ttrainfrom+1;i<tmtrainto;i++){
	      for(j=0;j<k;j++) fprintf(fp,"%.7e ",yd[i-j-1]);
	      fprintf(fp,"%.7e\n",yd[i]);
	    }
	    fclose(fp);
	    int B=0,t;//B=0:NoBoost//	  int B=2,t;//B=2:GbBoost??
	    for(t=Tbst;t<=Tbst;t++){
	      sprintf(cmd,"./ens2ge %s %s ",fntrain,"/dev/null");
	      for(j=3;j<argc;j++) { if(rsmo[j]==1) sprintf(&cmd[strlen(cmd)]," %s",argv[j]);}
	      sprintf(&cmd[strlen(cmd)]," bst:%d:%d dsp:0 N:%d-%d:1",t,B,N,N);
	      //	    sprintf(&cmd[strlen(cmd)]," bayes:3:0:0:1:0");
	      if(dynormalize==0){
		sprintf(&cmd[strlen(cmd)]," y:%e:%e:%e:%e:%e:%e:%e:%e",ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
		for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%e:%e:%e:%e:%e:%e:%e:%e",j,ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
	      }
	      else{
		sprintf(&cmd[strlen(cmd)]," y:%s",&argv[dynormalize][3]);
		if(dxnormalize>0)for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[dxnormalize][3]);
		else for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[dynormalize][3]);
	      }
	      fprintf(stderr,"Executing2 '%s'\n",cmd);
	      system(cmd);
	    }
	    //
	    //	  for(i=tmtrainto;i<tpredto;i++){
	    for(i=tmpredfrom;i<tpredto;i++){
	      sprintf(fnpred,"tmp/dy-pred%dk%d.input",i,k);
	      fp=fopen(fnpred,"w+");
	      if(ssp==0) {for(j=0;j<k;j++) fprintf(fp,"%.7e ",ydpm[i-j-1+i0m]);}
	      //	    else {for(j=0;j<k;j++) fprintf(fp,"%.7e ",yd[i-j-1+i0m]);}
	      else {for(j=0;j<k;j++) fprintf(fp,"%.7e ",yd[i-j-1]);}
	      if(i<ndata) fprintf(fp,"%.7e\n",yd[i]);//for compare
	      else fprintf(fp,"%.7e\n",ydpm[i-1+i0m]);//for compare 
	      fclose(fp);
	      
	      for(t=Tbst;t<=Tbst;t++){
		sprintf(cmd,"./ens2ge %s %s ",fntrain,fnpred);
		for(j=3;j<argc;j++) { if(rsmo[j]==1) sprintf(&cmd[strlen(cmd)]," %s",argv[j]);}
		//	      B=0;//??noboost?
		sprintf(&cmd[strlen(cmd)]," bst:%d:%d dsp:0 N:%d-%d:1",t,B,N,N);
		//	      sprintf(&cmd[strlen(cmd)]," bayes:3:0:0:1:0");
		//	      sprintf(&cmd[strlen(cmd)]," r:0:0");//061201
		if(dynormalize==0){
		  sprintf(&cmd[strlen(cmd)]," y:%e:%e:%e:%e:%e:%e:%e:%e",ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
		  for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%e:%e:%e:%e:%e:%e:%e:%e",j,ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
		}
		else{
		  sprintf(&cmd[strlen(cmd)]," y:%s",&argv[dynormalize][3]);
		  if(dxnormalize>0) for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[dxnormalize][3]);
		  else for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[dynormalize][3]);
		}
		fprintf(stderr,"Executing3 '%s'\n",cmd);
		system(cmd);
	      }
	      fp=fopen("predict+.dat","r");
	      fgets(buff,buffsize,fp);
	      sscanf(buff,"%lf",&ydpm[i+i0m]);
	      ypm[i+i0m]=ypm[(i-1)+i0m]+ydpm[i+i0m];
	      fclose(fp);
	      {
		fprintf(stdout,"#exec0\n");
		FILE *fp;
		int initpredall=0;
		if((fp=fopen(fn_predall,"r"))==NULL){
		  initpredall=1;
		}
		else fclose(fp);
		if(n_predall==0 && initpredall==1){
		  sprintf(cmd,"cat predict+.dat|awk '{print ($2+%d),$3,$1;}'> %s",tpredfrom,fn_predall);
		  fprintf(stdout,"#executing1 %s\n",cmd);
		  system(cmd);
		  sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' > %s",N,fn_lossall);system(cmd);
		}
		else{
		  sprintf(cmd,"cp %s p1.dat;cat predict+.dat |awk '{print $1}'| paste p1.dat - > %s",fn_predall,fn_predall);
		  fprintf(stderr,"#executing %s\n",cmd);
		  system(cmd);
		  sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' >> %s",N,fn_lossall);system(cmd);
		}
		n_predall++;
	      }

	    }
	  }
	  fp=fopen(fnpredlong,"w");
	  for(i=tmpredfrom;i<tpredto;i++) fprintf(fp,"%.7e %.7e\n",ypm[i+i0m],ydpm[i+i0m]);
	  fclose(fp);
	}
      }
      for(i=tpredfrom;i<tpredto;i++){
	ydp[i]=0;
	for(m=0;m<mpn;m++) ydp[i]+=ydpm[i+m*tpredto];
	ydp[i]/=(double)mpn;
      }
      //double *c=(double *)malloc(m*sizeof(double));
      //double tau_c=20.;
      //#define Hosei 2
      //#define Hosei 1
      //#if Hosei == 1
      if(Hosei>4){Hosei=2;}
      if(Hosei==1){
	double ct;
	double ctsum=0;
	for(i=tpredfrom;i<tpredto;i++){
	  yp[i]=0;
	  ctsum=0;
	  for(m=0;m<mpn;m++){
	    //	  ct=exp((double)(i-(tpredfrom-m*mpd))/tau_c);
	    ct=exp((double)(-m*mpd)/tau_c);
	    //	  ct=1;
	    ctsum+=ct;
	    yp[i]+=(ct*ypm[i+m*tpredto]);
	  }
	  yp[i]/=ctsum;
	}
      }
      else if(Hosei==2){
	double Deltay=0;
	i=tpredto-1; for(m=0;m<mpn;m++) Deltay+=ypm[i+m*tpredto];
	Deltay/=(double)mpn;
	Deltay-=ypm[tpredto-1];
	for(i=tpredfrom;i<tpredto;i++){
	  yp[i]=ypm[i]+(i-tpredfrom)*Deltay/num0;
	}
      }
      else if(Hosei==3){
	i=tpredfrom-1;
	yp[i]=y0[i];
	for(i=tpredfrom;i<tpredto;i++) yp[i]=yp[i-1]+ydp[i];
	double Deltay=0;
	i=tpredto-1; for(m=0;m<mpn;m++) Deltay+=ypm[i+m*tpredto];
	Deltay/=(double)mpn;
	Deltay-=yp[tpredto-1];
	for(i=tpredfrom;i<tpredto;i++){
	  yp[i]=yp[i]+(i-tpredfrom)*Deltay/num0;
	}
      }
      else if(Hosei==4){//combination of 1 and 2
	double ct;
	double ctsum=0;
	for(i=tpredfrom;i<tpredto;i++){
	  yp[i]=0;
	  ctsum=0;
	  for(m=0;m<mpn;m++){
	    ct=exp((double)(-m*mpd)/tau_c);
	    ctsum+=ct;
	    yp[i]+=(ct*ypm[i+m*tpredto]);
	  }
	  yp[i]/=ctsum;
	}
	for(i=tpredfrom;i<tpredto;i++){
	  double a=(double)(i-tpredfrom)/num0;
	  yp[i]=(1.-a)*ypm[i]+a*yp[i];
	}
      }
      
      if(ycode==1){//decode ;y -> (log encode) -> y:=log(y) -> learning -> (decoding) 
	for(i=tpredfrom;i<tpredto;i++){
	  yp[i]=exp(yp[i]);
	  for(m=0;m<mpn;m++){
	    ypm[i+m*tpredto]=exp(ypm[i+m*tpredto]);
	  }
	}
	y0=y00;
      }
      {
	double mse=0;
	int nmse=0;
	double msed=0;
	char *dir="result-ensrs";
	//      sprintf(fnresult0,"%s/predictDM%d:%d-%d:%d-%d.dat",dir,DiffMode,ttrainfrom,ttrainto,tpredfrom,tpredto);
	sprintf(fnresult0,"%s/predictDM%d:%d-%d.dat",dir,DiffMode,tpredfrom,tpredto);
	fnresult=&fnresult0[strlen(dir)+1];
	fp=fopen(fnresult0,"w+");
	for(i=tpredfrom;i<tpredto;i++){
	  if(r1!=0){
	    yp[i]=(double)(((int)((yp[i]/r12)+.5))*r12);//precision
	    //	_yp=(double)(((int)((yp[i]*10.)+.5))/10.);//precision
	  }
	  if(i<ndata){
	    //	fprintf(fp,"%.7e %d %.7e %.7e %.7e %.7e \n",_yp,i+1,y0[i],yp[i],ydpm[i],yd[i]);
	    //	fprintf(fp,"%.7e %d %.7e %.7e %.7e",_yp,i+1,y0[i],yp[i],yd[i]);
	    fprintf(fp,"%.7e %d %.7e %.7e %.7e %.7e",yp[i],i,y0[i],yd[i],yp[i],ydp[i]);
	    for(m=0;m<mpn;m++) fprintf(fp," %.7e %.7e",ypm[i+m*tpredto],ydpm[i+m*tpredto]); fprintf(fp,"\n");
	    nmse++;
	    mse+=square(yp[i]-y0[i]);
	    //mse+=square(mean0-y0[i]);
	    //mse+=square(_yp-y0[i]);
	    msed+=square(ydpm[i]-yd[i]);
	  }
	  //    else fprintf(fp,"%.7e %d %.7e %.7e %.7e %.7e #\n",_yp,i+1,0.,yp[i],ydpm[i]);
	  else{
	    fprintf(fp,"%.7e %d %.7e %.7e %.7e %.7e",yp[i],i,y0[ndata1],yd[ndata1],yp[i],ydp[i]);
	    for(m=0;m<mpn;m++) fprintf(fp," %.7e %.7e",ypm[i+m*tpredto],ydpm[i+m*tpredto]); fprintf(fp,"\n");
	  }
	  //	  ypN[iN][i]=yp[i];
	}
	mse/=nmse;
	msed/=nmse;
	fclose(fp);
//	{
//	  fp=fopen("loss.dat","r");
//	  fgets(buff,buffsize,fp);
//	  double _Ltst,_Lvar;
//	  sscanf(buff,"%lf%lf%lf",&_Ltst,&_Lvar,&skwN[iN]);
//	  fclose(fp);
//	}
	// b=Ax 
	//      double *A=(double *)malloc(2*num0*sizeof(double));
	//      //    double *b=(double *)malloc(num0*sizeof(double));
	//      double Myp[2],My0[2];
	//      for(i=0;i<num0;i++){A[i*2]=i; A[i*2+1]=1.;}//      A[i*2+1]=i+tpredfrom; A[i*2]=1.;      //      A[num0+i]=i+tpredfrom; A[i]=1.;
	//      calc_Ainvb(Myp,A,&(yp[tpredfrom]),2,num0,2);
	//      for(i=0;i<num0;i++){A[i*2]=i; A[i*2+1]=1.;}//      A[i*2+1]=i+tpredfrom; A[i*2]=1.;      //      A[num0+i]=i+tpredfrom; A[i]=1.;
	//      calc_Ainvb(My0,A,&(y0[tpredfrom]),2,num0,2);
	//      fprintf(stderr,"(a,b)=(%e,%e) for yp=a*t+b; (%e,%e) for y=a*t+b\n",Myp[0],Myp[1],My0[0],My0[1]);
	
	if((DISP&0x01)==0x01){
	  char *fnplt="dispy.plt";
	  char *fnobj="y.obj";
	  char fnpltdir[64];
	  sprintf(fnpltdir,"%s/%s",dir,fnplt);
	  fp=fopen(fnpltdir,"w+");
	  fprintf(fp,"set title \"DiffMode y, y^, and ymean(%g)\"\n",mean0);
	  fprintf(fp,"set style data lines\n");
	  fprintf(fp,"plot \"%s\" using 2:3 t \"y 2:3\"",fnresult);
	  for(m=0;m<mpn;m++) fprintf(fp,", \"%s\" using 2:%d t \"y^%d 2:%d\"",fnresult,7+m*2,m,7+m*2);
	  fprintf(fp,", \"%s\" using 2:1 t \"y^ 2:1\"",fnresult);
	  fprintf(fp,", %f",mean0);
	  fprintf(fp,"\npause -1 \"%s: hit return to save in '%s/%s'.\"\n",fnplt,dir,fnobj);
	  fprintf(fp,"set terminal tgif; set output \"%s\";replot\n",fnobj);
	  fclose(fp);
	  sprintf(cmd,"cd %s;xterm -geometry 50x5-0+0 -e gnuplot -geometry 420x280 %s",dir,fnplt);
	  fprintf(stderr,"Execute '%s'.\n",cmd);
	  sprintf(&cmd[strlen(cmd)],"&");
	  system(cmd);
	}
	if((DISP&0x01)==0x01){//??diffmode??
	  char *fnplt="dispdy.plt";
	  char *fnobj="dy.obj";
	  char fnpltdir[64];
	  sprintf(fnpltdir,"%s/%s",dir,fnplt);
	  fp=fopen(fnpltdir,"w+");
	  fprintf(fp,"set title \"DiffMode dy, dy^_i, dy^ and ymean(%g)\"\n",mean0);
	  fprintf(fp,"set style data lines\n");
	  fprintf(fp,"plot \"%s\" using 2:4 t \"dy 2:4\"",fnresult);
	  for(m=0;m<mpn;m++) fprintf(fp,", \"%s\" using 2:%d t \"dy^%d 2:%d\"",fnresult,8+m*2,m,8+m*2);
	  fprintf(fp,", \"%s\" using 2:6 t \"dy^ 2:6\"",fnresult);
	  fprintf(fp,", %f",meand0);
	  fprintf(fp,"\npause -1 \"%s:hit return to save in '%s/%s'.\"\n",fnplt,dir,fnobj);
	  fprintf(fp,"set terminal tgif; set output \"%s\";replot;quit\n",fnobj);
	  fclose(fp);
	  sprintf(cmd,"cd %s;xterm -geometry 50x5-0+0 -e gnuplot -geometry 420x280 %s",dir,fnplt);
	  //      sprintf(cmd,"cd %s;xterm -geometry 80x5-0+0 -e gnuplot -geometry 500x320 %s",dir,fnplt);
	  fprintf(stderr,"Execute '%s'.\n",cmd);
	  sprintf(&cmd[strlen(cmd)],"&");
	  system(cmd);
	}
	fprintf(stderr,"#MSE=%e(NMSE%e) MSEdy=%e(NMSEdy%e)(n%d) %d-%d:%d-%dk%dN%dT%dmp%d:%d:%gH%d-dy\n",
		mse,mse/mse0,msed,msed/msed0,nmse,ttrainfrom,ttrainto,tpredfrom,tpredto,k,N,T,mpn,mpd,tau_c,Hosei);
	{
	  FILE *fp=fopen("lossall.dat","a+");
	  fprintf(fp,"#tspredv3 %e %e %e %d %d %d %d %d %d %d %d %d %d %g %d #mse,mse0,msed,nmse,ttrainfrom,ttrainto,tpredfrom,tpredto,k,N,T,mpn,mpd,tau_c,Hosei it%d\n",
		  mse,mse0,msed,nmse,ttrainfrom,ttrainto,tpredfrom,tpredto,k,N,T,mpn,mpd,tau_c,Hosei,n_tspredv3++);
	  fclose(fp);
	}
	fprintf(stderr,"#The prediction is saved in %s.\n",fnresult0);
      }
    }
  }// endof if(DiffMode==1)
  else{//if(DiffMode==DirectMode){ 
    int i0m;
    char fnpredlong[128];
    if(dynormalize>1) rsmo[dynormalize]=0;
    if(dxnormalize>1) rsmo[dxnormalize]=0;
    for(i=0;i<ndata;i++){
      if(ymin>y0[i]) ymin=y0[i];
      else if(ymax<y0[i]) ymax=y0[i];
    }
    fprintf(stderr,"\nThe range of y:%f:%f\n",ymin,ymax);
    int iN;
    for(iN=0;iN<_nN;iN++){
      N=NN[iN];
      for(m=0;m<mpn;m++){
	i0m=m*tpredto;
	int tmtrainto=ttrainto-m*mpd;	//
	int tmpredfrom=tpredfrom-m*mpd;	//
	for(i=0;;i++){
	  ypm[i+i0m]=y0[i];//ypm[i]=y0[(i)];//??
	  //	if(i>=tmtrainto-1) break;
	  if(i>=tmpredfrom-1) break;
	}
	sprintf(fnpredlong,"result-ensrs/tmp/%s+%d-%d:%d-%dk%dN%da%gb%dT%d-y-predict+.dat",fnbody(argv[1],pr),ttrainfrom,ttrainto-m*mpd,tpredfrom-m*mpd,tpredto,k,N,rs_alpha,rs_ens,T);
	if((fp=fopen(fnpredlong,"r"))!=NULL && *pupdate=='0'){
	  fprintf(stderr,"#Read from '%s'\n",fnpredlong);
	  for(i=tmpredfrom;i<tpredto;i++){
	    fgets(buff,buffsize,fp);
	    if(feof(fp)) break;
	    sscanf(buff,"%lf",&ypm[i+i0m]);
	  }
	  fclose(fp);
	}//closing if((fp=fopen(fnpredlong,"r"))!=NULL){
	else{//if((fp=fopen(fnpredlong,"r"))!=NULL){
	  if(rs_method==-1){//single CAN2
	    sprintf(fntrain,"tmp/%s:y%d-%d.dat",fnbody(argv[1],pr),ttrainfrom,tmtrainto);
	    fp=fopen(fntrain,"w+");
	    for(i=0;i<ndata;i++) fprintf(fp,"%.7e\n",y0[i]);
	    fclose(fp);
	    //	  sprintf(cmd,"./ens2ge %s /dev/null Tsk:0:%d:%d:-%d",fntrain,tmtrainto,tpredto,ttrainfrom);
	    sprintf(cmd,"./ens2ge %s /dev/null Tsk:0:%d-%d:%d-%d",fntrain,ttrainfrom,tmtrainto,tmpredfrom,tpredto);
	    for(j=3;j<argc;j++) { if(rsmo[j]==1) sprintf(&cmd[strlen(cmd)]," %s",argv[j]);}
	    sprintf(&cmd[strlen(cmd)]," dsp:0 N:%d-%d:1",N,N);
	    if(ynormalize==0){
	      sprintf(&cmd[strlen(cmd)]," y:%e:%e:%e:%e:%e:%e:%e:%e",ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
	    }
	    else{
	      sprintf(&cmd[strlen(cmd)]," y:%s",&argv[ynormalize][2]);
	    }
	    fprintf(stderr,"Executing4 '%s'\n",cmd);
	    system(cmd);
	    {//
	      if(n_predall==0){
		sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' > %s",N,fn_lossall);system(cmd);
	      }
	      else{
		sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' >> %s",N,fn_lossall);system(cmd);
		fprintf(stderr,"#exec %s\n",cmd);
	      }
	    }

	    fp=fopen("predict+.dat","r");
	    //	  for(i=tmtrainto;i<tpredto;i++){
	    for(i=tmpredfrom;i<tpredto;i++){
	      fgets(buff,buffsize,fp);
	      if(feof(fp)) break;
	      sscanf(buff,"%lf",&ypm[i+i0m]);
	    }
	    fclose(fp);
	  }//if(rs_method==-1){
	  else if(BagBoost==BOOST){
	    sprintf(fntrain,"tmp/%s:y%d-%d.dat",fnbody(argv[1],pr),ttrainfrom,tmtrainto);
	    fp=fopen(fntrain,"w+");
	    for(i=k+ttrainfrom;i<tmtrainto;i++){//for(i=k+ttrainfrom+1;i<tmtrainto;i++){//2011.11.02
	      for(j=0;j<k;j++) fprintf(fp,"%.7e ",y0[i-j-1]);
	      fprintf(fp,"%.7e\n",y0[i]);
	    }
	    fclose(fp);
	    //
	    int B=0,t;	  //noboost	  	  int B=2,t;//GbBoost==2
	    for(t=Tbst;t<=Tbst;t++){
	      sprintf(cmd,"./ens2ge %s %s ",fntrain,"/dev/null");
	      for(j=3;j<argc;j++) { if(rsmo[j]==1) sprintf(&cmd[strlen(cmd)]," %s",argv[j]);}
	      sprintf(&cmd[strlen(cmd)]," bst:%d:%d dsp:0 N:%d-%d:1",t,B,N,N);
	      //	    sprintf(&cmd[strlen(cmd)]," bayes:3:0:0:1:0");
	      if(ynormalize==0){
		sprintf(&cmd[strlen(cmd)]," y:%e:%e:%e:%e:%e:%e:%e:%e",ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
		for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%e:%e:%e:%e:%e:%e:%e:%e",j,ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
	      }
	      else{
		sprintf(&cmd[strlen(cmd)]," y:%s",&argv[ynormalize][2]);
		if(xnormalize>0)for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[xnormalize][2]);
		else for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[ynormalize][2]);
	      }
	      //check here 
	      fprintf(stderr,"Executing5 '%s'\n",cmd);//learning
	      system(cmd);
	      {//
		FILE *fp;
		int initpredall=0;
		if((fp=fopen(fn_predall,"r"))==NULL){
		  initpredall=1;
		}
		else fclose(fp);
		if(n_predall==0 && initpredall==1){
		  //		if(n_predall==0){
		  sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' > %s",N,fn_lossall);system(cmd);
		}
		else{
		  sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' >> %s",N,fn_lossall);system(cmd);
		  fprintf(stderr,"#exec5 %s\n",cmd);
		}
	      }
	    }//closing 	  for(t=Tbst;t<=Tbst;t++){
	    for(i=tmpredfrom;i<tpredto;i++){
	      sprintf(fnpred,"tmp/y-pred%dk%d.input",i,k);
	      fp=fopen(fnpred,"w+");
	      if(ssp==0){ for(j=0;j<k;j++) fprintf(fp,"%.7e ",ypm[i-j-1+i0m]);}
	      else { for(j=0;j<k;j++) fprintf(fp,"%.7e ",y0[i-j-1]);}
	      //	    else { for(j=0;j<k;j++) fprintf(fp,"%.7e ",y0[i-j-1+i0m]);}
	      if(i<ndata) fprintf(fp,"%.7e\n",y0[i]);//for compare
	      else fprintf(fp,"%.7e\n",ypm[i-1+i0m]);//for compare 
	      fclose(fp);
	      
	      for(t=Tbst;t<=Tbst;t++){
		sprintf(cmd,"./ens2ge %s %s ",fntrain,fnpred);
		for(j=3;j<argc;j++) { if(rsmo[j]==1) sprintf(&cmd[strlen(cmd)]," %s",argv[j]);}
		sprintf(&cmd[strlen(cmd)]," bst:%d:%d dsp:0 N:%d-%d:1",t,B,N,N);//sprintf(&cmd[strlen(cmd)]," bayes:3:0:0:1:0");
		sprintf(&cmd[strlen(cmd)]," fupdate:0");//modified by kuro for faster
		//	      sprintf(&cmd[strlen(cmd)]," r:0:0");//061201
		if(ynormalize==0){
		  sprintf(&cmd[strlen(cmd)]," y:%e:%e:%e:%e:%e:%e:%e:%e",ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
		  for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%e:%e:%e:%e:%e:%e:%e:%e",j,ymin,ymax,ymin1,ymax1,y0m,y1m,y0M,y1M);
		}
		else{
		  sprintf(&cmd[strlen(cmd)]," y:%s",&argv[ynormalize][2]);
		  if(xnormalize>0)for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[xnormalize][2]);
		  else for(j=0;j<k;j++) sprintf(&cmd[strlen(cmd)]," x%d:%s",j,&argv[ynormalize][2]);
		}
		fprintf(stderr,"Executing6 '%s'\n",cmd);
		system(cmd);//check here for parallel processing
	      }
	      fp=fopen("predict+.dat","r");
	      fgets(buff,buffsize,fp);
	      sscanf(buff,"%lf",&ypm[i+i0m]);
	      fclose(fp);
	    }//for(i=tmpredfrom;i<tpredto;i++){
	    fp=fopen(fnpredlong,"w");
	    for(i=tmpredfrom;i<tpredto;i++) fprintf(fp,"%.7e\n",ypm[i+i0m]);
	    fclose(fp);
	  }//	  else if(BagBoost==BOOST){
	}//else{//if((fp=fopen(fnpredlong,"r"))!=NULL){
	if(ycode==1){//decode ;y -> (log encode) -> y:=log(y) -> learning -> (decoding) 
	  int m;
	  for(i=tpredfrom;i<tpredto;i++){
	    yp[i]=exp(yp[i]);
	    for(m=0;m<mpn;m++){
	      ypm[i+m*tpredto]=exp(ypm[i+m*tpredto]);
	    }
	  }
	  y0=y00;
	}
	if(Hosei>1){Hosei=1;}
	if(Hosei==0){
	  int m;
	  for(i=tpredfrom;i<tpredto;i++){
	    yp[i]=0;
	    for(m=0;m<mpn;m++){
	      yp[i]+=ypm[i+m*tpredto];
	    }
	    yp[i]/=(double)mpn;
	  }
	}
	else if(Hosei==1){
	  double ct,ctsum;
	  int m;
	  for(i=tpredfrom;i<tpredto;i++){
	    yp[i]=0;
	    ctsum=0;
	    for(m=0;m<mpn;m++){
	      ct=exp((double)(-m*mpd)/tau_c);
	      ctsum+=ct;
	      yp[i]+=(ct*ypm[i+m*tpredto]);
	    }
	    yp[i]/=ctsum;
	  }
	}
	{//save result
	  double mse=0;
	  int nmse=0;
	  int m;
	  char *dir="result-ensrs";
	  sprintf(fnresult0,"%s/predictDM%d:%d-%d.dat",dir,DiffMode,tpredfrom,tpredto);
	  fnresult=&fnresult0[strlen(dir)+1];
	  fp=fopen(fnresult0,"w+");
	  for(i=tpredfrom;i<tpredto;i++){
	    if(r1!=0){
	      yp[i]=(double)(((int)((yp[i]/r12)+.5))*r12);//precision
	    }
	    if(i<ndata){
	      fprintf(fp,"%.7e %d %.7e",yp[i],i,y0[i]);
	      for(m=0;m<mpn;m++) fprintf(fp," %.7e",ypm[i+m*tpredto]); fprintf(fp,"\n");
	      nmse++;
	      mse+=square(yp[i]-y0[i]);
	      //	      yp[N][i-tpredfrom]=ypt[i];//????
	    }
	    else{
	      fprintf(fp,"%.7e %d %.7e",yp[i],i,y0[ndata1]);
	      for(m=0;m<mpn;m++) fprintf(fp," %.7e",ypm[i+m*tpredto]); fprintf(fp,"\n");
	    }
	    //	    ypN[iN][i]=yp[i];
	  }
	  mse/=nmse;
	  fclose(fp);
//	  {
//	    fp=fopen("loss.dat","r");
//	    fgets(buff,buffsize,fp);
//	    double _Ltst,_Lvar;
//	    sscanf(buff,"%lf%lf%lf",&_Ltst,&_Lvar,&skwN[iN]);
//	    fclose(fp);
//	  }
	  
	  {//????

	    FILE *fp;
	    int initpredall=0;
	    if((fp=fopen(fn_predall,"r"))==NULL){
	      initpredall=1;
	    }
	    else fclose(fp);
	    if(n_predall==0 && initpredall==1){
	      //	    if(n_predall==0){
	      sprintf(cmd,"cat %s|awk '{print $2,$3,$1;}'> %s",fnresult0,fn_predall);system(cmd);
	      fprintf(stderr,"#exec6 %s\n",cmd);
	      //	      sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' > %s",N,fn_lossall);system(cmd);
	    }
	    else{
	      sprintf(cmd,"cp %s p1.dat;cat %s |awk '{print $1}'| paste p1.dat - > %s",fn_predall,fnresult0,fn_predall);system(cmd);
	      fprintf(stderr,"#exec6 %s\n",cmd);
	      //	      sprintf(cmd,"cat loss+.dat|awk '{print $0,\"N%d\";}' >> %s",N,fn_lossall);system(cmd);
	    }
	    n_predall++;
	  }
	  if((DISP&0x01)==0x01){
	    char *fnplt="dispy.plt";
	    char *fnobj="y.obj";
	    char fnpltdir[64];
	    sprintf(fnpltdir,"%s/%s",dir,fnplt);
	    fp=fopen(fnpltdir,"w+");
	    fprintf(fp,"set title \"DirectMode y, y^_i(shift prediction), y^ and ymean(%g)\"\n",mean0);
	    fprintf(fp,"set style data lines\n");
	    fprintf(fp,"plot \"%s\" using 2:3 t \"y 2:3\"",fnresult);
	    for(m=0;m<mpn;m++) fprintf(fp,", \"%s\" using 2:%d t \"y^%d 2:%d\"",fnresult,4+m,m,4+m);
	    fprintf(fp,", \"%s\" using 2:1 t \"y^ 2:1\"",fnresult);
	    fprintf(fp,", %g",mean0);
	    fprintf(fp,"\npause -1 \"hit return to save in '%s/%s'.\"\n",dir,fnobj);
	    fclose(fp);
	    sprintf(cmd,"cd %s;xterm -geometry 50x5-0+0 -e gnuplot -geometry 420x280 %s",dir,fnplt);
	    fprintf(stderr,"Execute '%s'.\n",cmd);
	    sprintf(&cmd[strlen(cmd)],"&");
	    system(cmd);
	  }
	  fprintf(stderr,"#MSE=%e(NMSE%e)(n%d) %d-%d:%d-%dk%dN%da%gb%dT%dmp%d:%d:%gH%d-y\n",mse,mse/mse0,nmse,ttrainfrom,ttrainto,tpredfrom,tpredto,k,N,rs_alpha,rs_ens,T,mpn,mpd,tau_c,Hosei);
	  {
	    FILE *fp=fopen("lossall.dat","a+");

	    fprintf(fp,"#tspredv3 %e %e %d %d %d %d %d %d %d %g %d %d %d %d %g %d #mse,mse0,nmse,ttrainfrom,ttrainto,tpredfrom,tpredto,k,N,rs_alpha,rs_ens,T,mpn,mpd,tau_c,Hosei,it%d\n",
		    mse,mse0,nmse,ttrainfrom,ttrainto,tpredfrom,tpredto,k,N,rs_alpha,rs_ens,T,mpn,mpd,tau_c,Hosei,n_tspredv3++);
	    fclose(fp);
	  }
	  fprintf(stderr,"#The prediction is saved in %s.\n",fnresult0);
	}////save result
      }//for(m=0;m<mpn;m++){
    }//for(iN=0;iN<_nN;iN++){
    //////////////////////////////////////////////////
    if((DISP&0x02)==0x02){
      //      char *fnplt="dispypall.plt";
      //      char *fnplt="predict+all.plt";
      char *fnplt="tspall.plt";
      fp=fopen(fnplt,"w");
      fprintf(fp,"set nokey;set style data lines\n");
      //      fprintf(fp,"plot \"%s\" using ($1):2 w lp t \"y\"",fn_predall);
      int m;
      for(m=0;m<n_predall;m++){
        if(m==0) fprintf(fp,"plot \"%s\" using ($1):%d lt 1 lc rgb \"black\" t \"y^N%d\"",fn_predall,3+m,NN[m]);
        else fprintf(fp,", \"\" using 1:%d lt 1 lc rgb \"black\" t \"y^N%d\"\\\n",3+m,NN[m]);
      }
      fprintf(fp,"\npause -1 \"hit return to quit.\"\n");
      fprintf(fp,"\nset term tgif;set output \"tspall.obj\";replot\n");
      fclose(fp);
      sprintf(cmd,"xterm -geometry 50x5+0-0 -e gnuplot -geometry 320x180+0+0 %s",fnplt);
      fprintf(stderr,"Execute '%s'.\n",cmd);
      sprintf(&cmd[strlen(cmd)],"&");
      system(cmd);
      sprintf(cmd,"cat %s",fn_lossall);
      fprintf(stderr,"#%s\n",cmd);
      system(cmd);
    }
  }//  else{//if(DiffMode==DirectMode){ 
  return(0);
}
