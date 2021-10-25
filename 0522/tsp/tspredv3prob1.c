#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include "my_misc.c"
#include "calcAinvb.c"
#include "share/zmtrand.c"
#define PI 3.141592653589793
#define INFTY (1e20)
#define INFTYint 999
#define ZERO (1e-20)
#define buffsize 100000
#define square(x) ((x)*(x))
int DISP=1;
double kyori(double *x,double *y,int t)
{
  int d=0,i;
  for(i=0;i<t;i++){
    double e=x[i]-y[i];
    d+=e*e;
  }
  return(sqrt(d));
}

int main(int argc,char **argv)
{

  //  char *fpa;
  //  char *fla;
  int i;
  int _N,_N1,_N2,_DN,_nN=0;
  //  int *NN;
  int rsmo[100];
  double rN=0;
  char cmd[314];
  double e_th=0;
  char fnout[256];
  char fnplt[256];
  double pNth=1;
  double e4t=5;
  double Sth=0.5;//Similarity threshold
  char *ftr="../../2004/ueno/data/lorenz10000_1e-4_p128.dat";
  int tr0=0,tr1=2000;
  int trd=tr1-tr0;
  double Hth=1.0;
  double attr_ym=0,attr_yM=0;
  int attr_n=40;
  double py_ym=-18.5,py_yM=18.5;
  int py_n=50;
  char dir[256]={'.', 0};//null or xxx/
  char *ds[20];
  char *fn_pa[10];
  char *fn_la[10];
  int n_pa=1,n_la=1,n_ds=0;
  //  int n_pa=0,n_la=0,n_ds=0;
  int ms=0; //method of model selection; ms=0 for LtH ms=1 for Lyp
  //  int LtHmin=0,LtHmax=INFTYint;
  int LtHth_min=0,LtHth_max=INFTYint,LtHth_modelselection=0;//modelselection=0 for only calculating the correlation H*LH
  int DNth=0,Nth=5000;//
  //  int ntsim=100;
  printf("#start: %s",argv[0]);
  for(i=1;i<argc;i++){printf(" %s",argv[i]);}
  printf("\n");
  for(i=1;i<argc;i++){
    if(strncmp(argv[i],"ds:",3)==0 ){//predict+all
      char *p;
      int j=0;
      ds[j]=p=&argv[i][3];
      for(;;){
	if(*p==0) break;
	if(*p==' ') {
	  *p=0;
	  j++;p++;
	  ds[j]=p;
	}
	p++;
      }
      n_ds=j+1;
    }
    else if(strncmp(argv[i],"dir:",4)==0){
      sprintf(dir,"%s",&argv[i][4]);
      int sl1=strlen(dir)-1;
      if(dir[sl1]=='/'){
	dir[sl1]=0;
      }
    }
    else if(strncmp(argv[i],"pa:",3)==0 ){//predict+all
      char *p;
      int j=0;
      fn_pa[j]=p=&argv[i][3];
      for(;;){
	if(*p==0) break;
	if(*p==',') {
	  *p=0;
	  j++;p++;
	  fn_pa[j]=p;
	}
	p++;
      }
      n_pa=j+1;
    }
    else if(strncmp(argv[i],"la:",3)==0 ){//lossall
      char *p;
      int j=0;
      fn_la[j]=p=&argv[i][3];
      for(;;){
	if(*p==0) break;
	if(*p==',') {
	  *p=0;
	  j++;p++;
	  fn_la[j]=p;
	}
	p++;
      }
      n_la=j+1;
    }
    else if(strncmp(argv[i],"fpa:",4)==0){//predict+all.dat
      //      fpa=&argv[i][4];
      fn_pa[0]=&argv[i][4];
      n_pa=1;
    }
    else if(strncmp(argv[i],"ms:",3)==0){//predict+all.dat
      sscanf(&argv[i][3],"%d",&ms);
    }
    else if(strncmp(argv[i],"DISP:",5)==0){
      sscanf(&argv[i][5],"%d",&DISP);
    }
    else if(strncmp(argv[i],"fla:",4)==0){//lossall.dat
      //fla=&argv[i][4];
      fn_la[0]=&argv[i][4];
      n_la=1;
    }
    else if(strncmp(argv[i],"ftr:",4)==0){//
      ftr=&argv[i][4];
    }
    else if(strncmp(argv[i],"ttr:",4)==0){//
      sscanf(&argv[i][4],"%d-%d",&tr0,&tr1);
    }
    else if(strncmp(argv[i],"pNth:",5)==0){//
      sscanf(&argv[i][5],"%lf",&pNth);
    }
    else if(strncmp(argv[i],"e4t:",4)==0){//
      sscanf(&argv[i][4],"%lf",&e4t);
    }
    else if(strncmp(argv[i],"e4H:",4)==0){//
      sscanf(&argv[i][4],"%lf,%d,%d",&e4t,&DNth,&Nth);
    }
    else if(strncmp(argv[i],"Hth:",4)==0){//
      int nr=sscanf(&argv[i][4],"%lf,%d,%d,%d",&Hth,&LtHth_min,&LtHth_max,&LtHth_modelselection);
      if(nr<=3) LtHth_modelselection=0;
      if(nr<=2) LtHth_max=INFTYint;
      if(nr<=1) LtHth_min=0;
      //LtHth_max for only obtaining H*LH
      //      sscanf(&argv[i][4],"%lf",&Hth);
    }
    else if(strncmp(argv[i],"e_th:",5)==0){//
      sscanf(&argv[i][5],"%lf",&e_th);
    }
    else if(strncmp(argv[i],"rN:",3)==0){//
      sscanf(&argv[i][3],"%lf",&rN);
    }
    else if(strncmp(argv[i],"Sth:",4)==0){//
      sscanf(&argv[i][4],"%lf",&Sth);
    }
    else if(strncmp(argv[i],"at:",3)==0){//transform
      sscanf(&argv[i][3],"%lf_%lf:%d",&attr_ym,&attr_yM,&attr_n);
    }
    else if(strncmp(argv[i],"py:",3)==0){//transform
      sscanf(&argv[i][3],"%lf,%lf,%d",&py_ym,&py_yM,&py_n);
    }
//    else if(strncmp(argv[i],"nts:",3)==0){//ntsim for clustering
//      sscanf(&argv[i][3],"%d",&ntsim);
//    }
  }
  char buff[buffsize];
  double sa=0, v[25];
  int n=0,iN=0;
  int t,nt=0;
  FILE *fp;
  char fn[257];
  int nN=0;
  int *NN=NULL;
  double *saN=NULL;
  int j;
  int n_fn=(n_ds>0)?n_ds:n_pa ;

  for(j=0;j<n_fn;j++){
    if(n_ds>0) sprintf(fn,"%s/lossall.dat",ds[j]);
    else sprintf(fn,"%s/%s",dir,fn_la[j]);
    fp=fopen(fn,"r");//lossall.dat
    int _nN=0;
    for(;;){
      fgets(buff,buffsize,fp);
      if(feof(fp)) break;
      if(buff[0]=='#'){
	_nN++;
      }
      else nt++;
    }
    nt/=_nN;//nt
    nN+=_nN;
    fclose(fp);
  }
  fprintf(stderr,"###n_fn=%d nN=%d, nt=%d\n",n_fn,nN,nt);
  for(j=0;j<n_fn;j++){
    if(n_ds>0) sprintf(fn,"%s/lossall.dat",ds[j]);
    else sprintf(fn,"%s/%s",dir,fn_la[j]);
    fp=fopen(fn,"r");//lossall.dat
    if(j==0){
      NN=(int *)malloc(sizeof(int)*(nN));//I do not understand why here is OK and the above is NG.
      saN=(double *)malloc(sizeof(double)*(nN));//absolute skew
    }
    rewind(fp);
    //  int t;
    sa=0;
    for(t=0;;t++){
      buff[0]=0;
      fgets(buff,buffsize,fp);
      if(feof(fp)) break;
      if(buff[0]==0) break;
      if(buff[0]!='#'){//24
	char *p=&buff[0];
	//      sscanf(buff,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&v[1],&v[2],&v[3],&v[4],&v[5],&v[6],&v[7],&v[8],&v[9],&v[10],&v[11],&v[12],&v[13],&v[14],&v[15],&v[16]);
	for(i=1;i<=24;i++){
	  if(*p==0) break;
	  sscanf(p,"%lf",&v[i]);
	  for(;;){
	    if(*p==0) break;
	    if(*p==' ' || *p==0x09){
	      p++;
	      break;//tab=0x09,
	    }
	    p++;
	  }
	}
	sa+=v[9];//skewa
	n++;
      }
      else{//if(buff[0]=='#'){%24
	char *p=&buff[10];
	for(i=1;i<=16;i++){
	  if(*p==0) break;
	  sscanf(p,"%lf",&v[i]);
	  for(;;){
	    if(*p==0) break;
	    if(*p==' ' || *p==0x09){
	      p++;
	      break;//tab=0x09,
	    }
	    p++;
	  }
	}
	if(iN>=nN){
	  fprintf(stderr,"#check\n");
	}
	//      sscanf(&buff[10],"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&v[1],&v[2],&v[3],&v[4],&v[5],&v[6],&v[7],&v[8],&v[9],&v[10],&v[11],&v[12],&v[13],&v[14],&v[15],&v[16]);
	//	fprintf(stderr,"#check t=%d i=%d v9=%g\n",t,i,v[9]);
	NN[iN] = v[9];//number of units of the CAN2
	//      fprintf(stderr,"#NN[%d]=%d\n",iN,NN[iN]);
	saN[iN]=(n>0)?sa/n:0;
	//	if(n>0) saN[iN] = sa/n;	else saN[iN] = 0;
	//      _nt=n;
	sa=n=0;
	iN++;
      }
      //      fprintf(stderr,"#check t=%d nN=%d iN=%d\n",t,nN,iN);
      //      double **ypN2=(double **)malloc(sizeof(double*)*(nN+2));free(ypN2);
    }
    fclose(fp);
  }
  ////////
  if(iN!=nN) fprintf(stderr,"#err iN=%d nN=%d\n",iN,nN);
  if(n_pa!=n_la) fprintf(stderr,"#err n_pa%d != n_la%d\n",n_pa,n_la);
  int nN2=nN+2;
  double **ypN=(double **)malloc(sizeof(double*)*(nN2+1));
  int ii=0;
  for(j=0;j<n_fn;j++){
    if(n_ds>0) sprintf(fn,"%s/tspall.dat",ds[j]);
    else sprintf(fn,"%s/%s",dir,fn_pa[j]);
    fp=fopen(fn,"r");//predict+all.dat
    if(j==0){
      for(nt=0;;){
	buff[0]=0;
	fgets(buff,buffsize,fp);
	if(feof(fp)) break;
	if(buff[0]==0) break;
	if(buff[0]=='#') continue;
	nt++;
      }
      fprintf(stderr,"##nN=%d,nt=%d\n",nN,nt);
      for(i=0;i<=nN2;i++) ypN[i]=(double*)malloc(sizeof(double)*nt);
      rewind(fp);
    }
//  {
//    double **yp=(double **)malloc(sizeof(double*)*15);free(yp);//memorycheck
//  }
    //    double *ypNmean=ypN[nN];                          //ypredict
    for(t=0;t<nt;t++){
      buff[0]=0;
      fgets(buff,buffsize,fp);
      if(feof(fp)) break;
      if(buff[0]==0) break;
      char *p=&buff[0];
      for(i=0;;i++){
	if(*p==0) break;
	if(j==0) sscanf(p,"%lf",&ypN[i][t]);
	//	else if(i+ii>=nN2) fprintf(stderr,"#hen i+ii=%d+%d=%d\n",i,ii,i+ii);
	else if(i>=2){
	  sscanf(p,"%lf",&ypN[i+ii-2][t]);
	}
	for(;;){
	  if(*p==0) break;
	  if(*p==' ' || *p==0x09){
	    p++;
	    break;//tab=0x09,
	  }
	  p++;
	}
      }
    }
    if(j==0) ii=i;
    else ii+=i-2;
    fprintf(stderr,"#ii=%d\n",ii);//check number of columns
    fclose(fp);
  }//for(j=0;j<n_fn;j++){
  ///////////////
  int iNsamin=0,iNsamax=nN-1;
  fprintf(stderr,"#skewa:");
  if(1==0){
    for(i=0;i<nN;i++){
      fprintf(stdout,"%g %d #sa N\n",saN[i],NN[i]);
      //    fprintf(stderr,"sa%gN%d\n",saN[i],NN[i]);
    }
  }
  for(i=1;i<nN;i++){
    if(saN[iNsamin]>saN[i]) {
      iNsamin=i;
    }
    //    if(saN[iNsamin]<saN[i]) break;
  }
  //  iNsamax=iNsamin;
  for(i=nN-1;i>iNsamin;i--){
    if(saN[iNsamax]<saN[i]){
      iNsamax=i;
    }
    //    if(saN[iNsamax]>saN[i]) break;
  }
  fprintf(stdout,"#sa: min%g[%d] max%g[%d]\n",saN[iNsamin],NN[iNsamin],saN[iNsamax],NN[iNsamax]);
  //  fprintf(stderr,"#sa[N%d]%g < sa[N%d]%g\n",NN[iNsamin],saN[iNsamin],NN[iNsamax],saN[iNsamax]);
  /////
  double *ypmin=(double*)malloc(sizeof(double)*nt);
  double *ypmax=(double*)malloc(sizeof(double)*nt);
  double **yp=(double **)malloc(sizeof(double*)*nN);
  //
  //  char *fnout="Lyp.dat";//pp: predprob
  //  sprintf(fnout,"Lyp.dat");//pp: predprob
  //  fp=fopen(fnout,"w");
  for(i=0;i<nN;i++) yp[i]=&ypN[2+i][0];

  //attractor similarity
  {  //attractor similarity

    int n12;
    double ymax,ymin;
    double yd;
    fprintf(stderr,"#making attractors");
    if(attr_ym==0 && attr_yM==0){
      n12=40;
      ymax=18.5,ymin=-18.5;
    }
    else{
      n12=attr_n;
      ymax=attr_yM;
      ymin=attr_ym;
    }
    yd=(ymax-ymin)/(n12);
    //    char *fny0="../../2004/ueno/data/lorenz10000_1e-4_p128.dat";
    fp=fopen(ftr,"r");
    //    int tr1=2000;
    double *y0=(double*)malloc(sizeof(double)*tr1);
    int _t;
    for(t=_t=0;_t<tr1;_t++){
      fgets(buff,buffsize,fp);
      if(buff[0]=='#') continue;
      if(_t<tr0) continue;
      sscanf(buff,"%lf",&y0[t++]);
    }
    fclose(fp);
    double **attr0=(double**)malloc(sizeof(double*)*n12);;
    for(i=0;i<n12;i++){
      attr0[i]=(double*)malloc(sizeof(double)*n12);
      for(j=0;j<n12;j++) attr0[i][j]=0;
    }
    for(t=0;t<trd-1;t++){
      i=(y0[t]-ymin)/yd-0.5;
      j=(y0[t+1]-ymin)/yd-0.5;
      if(i<0 || i>=n12) fprintf(stderr,"hen i%d>=%d\n",i,n12);
      else if(j<0 || j>=n12) fprintf(stderr,"hen j%d>%d\n",j,n12);
      else attr0[i][j]++;
    }
    double norma=0;
    for(i=0;i<n12;i++){
      for(j=0;j<n12;j++){
	norma+=attr0[i][j]*attr0[i][j];
      }
    }
    norma=sqrt(norma);
    fprintf(stderr,"#y0:norma=%g n%d\n",norma,n);
    for(i=0;i<n12;i++){
      for(j=0;j<n12;j++){
	attr0[i][j]/=norma;
      }
    }
    {
      sprintf(fnout,"attr_train.dat");
      fp=fopen(fnout,"w");
      for(t=0;t<trd-2;t++){
	fprintf(fp,"%g %g %g\n",y0[t],y0[t+1],y0[t+2]);
      }
      fclose(fp);
      sprintf(fnout,"attr_train-.dat");
      fp=fopen(fnout,"w");
      for(i=0;i<n12;i++){
	for(j=0;j<n12;j++){
	  fprintf(fp,"%d %d %.7e\n",i,j,attr0[i][j]);
	}
	fprintf(fp,"\n");
      }
      fclose(fp);
    }
    //
    double ***attr=(double ***)malloc(sizeof(double**)*(nN));
    int n;
    for(n=0;n<nN;n++){
      attr[n]=(double**)malloc(sizeof(double*)*n12);
      for(i=0;i<n12;i++){
	attr[n][i]=(double*)malloc(sizeof(double)*n12);
	//	for(j=0;j<n12;j++) attr[n][i][j]=0;
      }
    }
    //
    int _ntD=20,_nt,_nti,_nt0,_i,_j;
    double **S=(double**)malloc(sizeof(double)*(nt/_ntD+1));//similarity
    int nSmax=0;
    for(_i=0,_nt=nt;_nt>0;_nt-=_ntD){
	S[_i++]=(double*)malloc(sizeof(double)*nN);
    }
    _nti=_i-1;
    _nt0=nt-_nti*_ntD;
    fprintf(stderr,"#making attractors for %d*%d steps:",_nti+1,_ntD);
    for(_i=0;_i<=_nti;_i++){//check change of corralation
      _nt=_i*_ntD+_nt0;
      fprintf(stderr,"%d ",_nt);
      for(n=0;n<nN;n++){
	for(i=0;i<n12;i++){
	  for(j=0;j<n12;j++) attr[n][i][j]=0;
	}
      }
      
      for(n=0;n<nN;n++){
	for(t=0;t<_nt-1;t++){
	  i=(yp[n][t]-ymin)/yd-0.5;
	  j=(yp[n][t+1]-ymin)/yd-0.5;
	  if(i<0 || i>=n12) fprintf(stderr,"hen i%d>%d\n",i,n12);
	  else if(j<0 || j>=n12) fprintf(stderr,"hen j%d>%d\n",j,n12);
	  else attr[n][i][j]++;
	}
	double norma=0;
	for(i=0;i<n12;i++){
	  for(j=0;j<n12;j++){
	    norma+=attr[n][i][j]*attr[n][i][j];
	  }
	}
	norma=sqrt(norma);
	//      fprintf(stderr,"#norma=%g n%d\n",norma,n);
	for(i=0;i<n12;i++){
	  for(j=0;j<n12;j++){
	    attr[n][i][j]/=norma;
	  }
	}
      }
    ///
      for(n=0;n<nN;n++){
	char fnout[20];
	sprintf(fnout,"attrN%d.dat",NN[n]);
	fp=fopen(fnout,"w");
	for(t=0;t<_nt-2;t++){
	  fprintf(fp,"%g %g %g\n",yp[n][t],yp[n][t+1],yp[n][t+2]);
	}
	fclose(fp);
      }
      for(n=0;n<nN;n++){
	char fnout[20];
	sprintf(fnout,"attrN%d-.dat",NN[n]);
	fp=fopen(fnout,"w");
	for(i=0;i<n12;i++){
	  for(j=0;j<n12;j++){
	    fprintf(fp,"%d %d %.7e\n",i,j,attr[n][i][j]);
	  }
	  fprintf(fp,"\n");
	}
	fclose(fp);
      }

      int m;
      nSmax=0;
      for(n=0;n<nN;n++){
	S[_i][n]=0;
	for(i=0;i<n12;i++){
	  for(j=0;j<n12;j++){
	    S[_i][n]+=attr[n][i][j]*attr0[i][j];
	  }
	}
	if(S[_i][n]>S[_i][nSmax]) nSmax=n;

//	if(S[_i][n]>=Sth) fprintf(stderr,"%d %d %.3f #*i N C\n",n,NN[n],S[_i][n]);
//	else          fprintf(stderr,"%d %d %.3f # i N C\n",n,NN[n],S[_i][n]);
	//      if(S[n]>=Sth) fprintf(stderr,"*%dN%d)%.2f\n",n,NN[n],S[n]);
	//      else fprintf(stderr," %dN%d)%.2f\n",n,NN[n],S[n]);
      }
      //    fprintf(stderr,"\n");
    }//    for(_i=0;_i<=_nti;_i++){//check change of corralation
    fprintf(stderr,"#saving sim.dat");
    int nSmax0=nSmax;
    system("mkdir -p tmp");
    sprintf(fnout,"tmp/sim.dat");//pp: predprob
    fp=fopen(fnout,"w");
    for(_i=0;_i<=_nti;_i++){//check change of corralation
      fprintf(fp,"%d ",_i*_ntD+_nt0);
      for(n=0;n<nN;n++){//	fprintf(fp,"%d ",n);
	fprintf(fp,"%g ",S[_i][n]);
      }
      fprintf(fp,"\n");
    }
    fclose(fp);
    sprintf(fnplt,"tmp/sim.plt");
    fp=fopen(fnplt,"w");
    fprintf(fp,"set style data lines; set nokey\n");
    fprintf(fp,"plot \"%s\" using 1:2 lt 1 lc rgb \"black\" t \"\"",fnout);
    for(n=1;n<nN;n++){
      fprintf(fp,", \"\" using 1:%d lt 1 lc rgb \"black\" t \"\"\\\n",n+1);
    }
    fprintf(fp,", %g\n",Sth);
    fprintf(fp,"\npause -1 \"%s:hit return to quit.\"\n",fnplt);
    fprintf(fp,"set term tgif;set output \"tmp/sim.obj\";replot;set term x11\n");
    fclose(fp);
    sprintf(cmd,"xterm -geometry 50x5+0-0 -e gnuplot -geometry 320x180+0+0 %s",fnplt);
    fprintf(stderr,"Execute '%s'.\n",cmd);
    sprintf(&cmd[strlen(cmd)],"&");
    if(DISP!=0) system(cmd);

    fprintf(stderr,"#similaritys saved in %s\n",fnout);
    //
    int *nS=(int*)malloc(sizeof(int)*nN);
    fprintf(stdout,"#N of Removed predictions with Sth=%g (nN=%d):\n",Sth,nN);
    //20190521
    double Smax=0;
//    for(i=n=0;n<nN;n++){// 20190521
//      if(NN[n]>=NN[iNsamin] && NN[n]<=NN[iNsamax] && S[_nti][n]>Smax) Smax=S[_nti][n];
//    }
    for(_i=0;_i<=_nti;_i++){//check change of corralation
      for(i=n=0;n<nN;n++){// 20191214
        if(S[_i][n]>Smax) Smax=S[_i][n];
      }
    }

    for(_i=0;_i<=_nti;_i++){//check change of corralation
      for(i=n=0;n<nN;n++){//sort
        if(S[_i][n]>=Sth*Smax){//20190521
	//      if(NN[n]>=NN[iNsamin] && NN[n]<=NN[iNsamax] && S[_nti][n]>=Sth){
          nS[i]=n;i++;
          fprintf(stdout,"oN%d(S%g),%d<%d<%d \n",NN[n],S[_i][n],NN[iNsamin],NN[n],NN[iNsamax]);
        }//_nti= terminal time
      //      if(S[_nti][n]>=Sth) {nS[i]=n;i++;}//_nti= terminal time
        else{
          fprintf(stdout,"xN%d(S%g),%d<%d<%d \n",NN[n],S[_i][n],NN[iNsamin],NN[n],NN[iNsamax]);
          //	fprintf(stdout,"N%d(S%g) ",NN[n],S[_nti][n]);
        }
      }
    }
    //    n=(172-10)/2;fprintf(stdout,"\n#S(N%d)=%g is used\n",NN[n],S[_nti][n]);
    int imaxS=i;//
    fprintf(stdout,"imaxS=%d\n",imaxS);//check
    if(imaxS==0){
      fprintf(stdout,"imaxS=0. tune Sth=%f Smax=%f\n",Sth,Smax);
      return(-1);
    }
    double *Lyp=(double *)malloc(sizeof(double)*(nN));//Leave-one-out prediction loss
    int iLypmin;
    iLypmin=0;
    for(_i=0;_i<imaxS;_i++){
      i=nS[_i];
      Lyp[i]=0;
      double ne=0;int _j;
      for(_j=0;_j<imaxS;_j++){
	j=nS[_j];
	if(i==j) continue;
	for(t=0;t<nt;t++){
	  double e=yp[i][t]-yp[j][t];
	  Lyp[i]+=e*e;
	  ne++;
	}
      }
      Lyp[i]=sqrt(Lyp[i]/ne);
      if(iLypmin==0 || Lyp[iLypmin]>Lyp[i]) iLypmin=i;
    }
    nSmax=iLypmin;//replace N=NN[nSmax] for the best prediction by N=NN[iLypmin]
    ////////////////////////////////////
    int iLtHmax=0;
    double *LtH=(double *)malloc(sizeof(double)*(nN));//Leave-one-out prediction horizon LOOCV predictive horizon
    double *LtHij=(double *)malloc(sizeof(double)*(nN)*nN);//Leave-one-out prediction horizon 
    for(_i=0;_i<imaxS;_i++){
      i=nS[_i];
      LtH[i]=0;
      double ne=0;
      for(_j=0;_j<imaxS;_j++){
	j=nS[_j];
	if(i==j) continue;
	for(t=0;t<nt;t++){
	  double e=yp[i][t]-yp[j][t];
	  if(fabs(e)> e4t && fabs(NN[i]-NN[j])>DNth && NN[i]<=Nth){//predictable horizon =t-1
        //if(fabs(e)>=e4t && fabs(NN[i]-NN[j])>DNth && NN[i]<=Nth){//predictable horizon =t-1 iconip2015
	    //	  if(fabs(e)>=e4t && fabs(NN[i]-NN[j])>DNth){
	    //	  if(fabs(e)>=e4t){
	    //LtH[i]+=square(t-1);
	    if(LtHth_modelselection<=1) LtH[i]+=(t-1);//mean for LOOCV
	    else if(LtHth_modelselection==2){
	      if(fabs(_i-_j)>=2 && LtH[i]<t-1) LtH[i]=t-1;//search max  LtH[i]
	      //	      if(LtH[i]==0 || LtH[i]<t-1) LtH[i]=t-1;
	    }
	    LtHij[i*nN+j]=t-1;
	    ne++;
	    break;
	  }
	}
      }
      //      fprintf(stderr,"#check DNth=%d\n",DNth);
      //LtH[i]=sqrt(LtH[i]/ne);//      
      if(LtHth_modelselection<=1) LtH[i]=LtH[i]/ne;//mean for LOOCV

      if(iLtHmax==0) iLtHmax=i;
      else{
	if(LtHth_modelselection==0){
	  if(LtH[iLtHmax]<LtH[i]) iLtHmax=i;
	}
	else if(LtHth_modelselection==1){
	  if(LtH[iLtHmax]<LtH[i] && LtH[i]>=LtHth_min && LtH[i]<=LtHth_max) iLtHmax=i;//this can be done by tuning iLtHmax
	  //	  iLtHmax=nSmax;//?
	}
	else if(LtHth_modelselection==2){
	  if(LtH[iLtHmax]<LtH[i]) iLtHmax=i;
	}
      }
      //      if(LtHth_modelselection==1) iLtHmax=nSmax;//??20151116?????
      //iconip2015 from here tag#1
      //if(iLtHmax==0 ||
      //	 (LtH[iLtHmax]<LtH[i] && 
      //	  (LtHth_modelselection==0 ||
      //	   (LtHth_modelselection!=0 && LtH[i]>=LtHth_min && LtH[i]<=LtHth_max)))) iLtHmax=i;
      //iconip2015 to here tag#1

      //      if(iLtHmax==0 || LtH[iLtHmax]<LtH[i]) iLtHmax=i;
    }
    //
    if(1==1){//check?
      i=iLtHmax;
      //      fprintf(stdout,"LtHij for i=%d \n",i);
      for(_j=0;_j<imaxS;_j++){
	j=nS[_j];
	if(i==j) continue;
	//	fprintf(stdout,"%g %d\n", LtHij[i*nN+j],j);
      }
    }
    //////////////////////////////////
    int nrep;//nrepresentative
    if(ms==0) nrep=iLtHmax;     //replace N=NN[nrep] for the best prediction by N=NN[iLmin]
    else if(ms==1) nrep=iLypmin;//replace N=NN[nrep] for the best prediction by N=NN[iLypmin]
    else if(ms==-1) nrep=nSmax0;
    ////////////////////////////////////
//    if(1==0){//only for check using smaller LtHij
//      sprintf(fnout,"LtH.dat");
//      fp=fopen(fnout,"w");
//      int iLtH2max=0;//chose greater LtHij than the mean LtH[i]/3
//      for(_i=0;_i<imaxS;_i++){
//	i=nS[_i];
//	double LtH2=0;int nLtH2=0;
//	for(_j=0;_j<imaxS;_j++){
//	  j=nS[_j];
//	  fprintf(fp,"%d %d %g %g\n",i,j,LtHij[i*nN+j],LtH[i]);
//	  if(LtHij[i*nN+j]>=LtH[i]/3.){
//	    LtH2+=LtHij[i*nN+j];//sum of LtHij bigger than the mean
//	    nLtH2++;
//	  }
//	}
//	fprintf(fp,"\n");
//	LtH[i]=LtH2/nLtH2;
//	if(iLtH2max==0 || LtH[iLtH2max]<LtH[i]) iLtH2max=i;
//      }
//      fclose(fp);
//      //      nrep=iLtH2max;//replace N=NN[nrep] for the best prediction by N=NN[iLmin]
//    }
    ///////////////////////////////////////////////
    int *sL=(int*)malloc(sizeof(int)*nN);//sort of LtH
    for(i=0;i<imaxS;i++){sL[i]=nS[i];}
    for(i=0;i<imaxS;i++){//sort
      for(j=i+1;j<imaxS;j++){
	if(LtH[sL[i]]<LtH[sL[j]]){
	  //	if(Lyp[sL[i]]>Lyp[sL[j]]){
	  int sLi=sL[i];
	  sL[i]=sL[j];
	  sL[j]=sLi;
	}
      }
    }
    int Hexp=0;
    for(t=0;t<nt;t++){//obtain error range
      ypmin[t]=INFTY;ypmax[t]=-INFTY;
      for(i=0;i<imaxS*Hth;i++){//???
	n=sL[i];
	if(ypmin[t]>yp[n][t]) ypmin[t]=yp[n][t];
	if(ypmax[t]<yp[n][t]) ypmax[t]=yp[n][t];
      }
      if(Hexp==0 &&
	 (fabs(ypmin[t]-yp[iLtHmax][t])>e4t ||
	  fabs(ypmax[t]-yp[iLtHmax][t])>e4t)){
	Hexp=t-1;
      }
    }

    //RMSE:root mean square prediction error
    //    double rmse=0;
    int ne=0;
    int _tH=0;//predictable horizon
    int flag_tH=0;
    for(t=0;t<nt;t++){
      double e=yp[nrep][t]-ypN[1][t];//horizon of representative nrep?
      //      rmse+=e*e;
      ne++;
      if(flag_tH==0 && fabs(e)>=e4t){
	_tH=t-1;
	flag_tH=1;
      }
    }
    //    rmse=sqrt(rmse/ne);
    int tH_nrep=_tH;
    //    fprintf(stderr,"#tH%3dN%3dC%5.3f",tH_nrep,NN[nrep],C[_nti][nrep]);
    //    fprintf(stderr,"#tH%3dN%3dRMSE%5.2f",tH,NN[nrep],rmse);
    //    fprintf(stderr,"#RMSE%5.2ftH%3dN%3d\n",rmse,tH,NN[nrep]);
    //?????evaluation?
    int best_tH=_tH,best_n=nrep;
    for(n=0;n<nN;n++){
      for(t=0;t<nt;t++){
	double e=yp[n][t]-ypN[1][t];//
	if(fabs(e)>=e4t){
	  _tH=t-1;
	  if(_tH>best_tH){
	    best_tH=_tH;
	    best_n=n;
	  }
	  break;
	}
      }
    }
    int iL_best_n=0,iL_nrep=0;
    for(i=0;i<imaxS;i++){
      if(nrep==sL[i]){
	iL_nrep=i;//??nouse??
      }
      if(best_n==sL[i]){
	iL_best_n=i;//
      }
    }
    ////
    sprintf(fnout,"SLH.dat");//pp: predprob //data of Similarity, Loss(Error), Horizon 
    fp=fopen(fnout,"w");
    double normC=0,normLyp=0,normLypy=0,normtH=0,normLtH=0;
    double prodSLyp=0,prodSLypy=0,prodStH=0,prodtHLtH=0;
    double prodLypLypy=0,prodLyptH=0;
    double prodLypytH=0;
    double *Lypy=(double*)malloc(sizeof(double)*nN);
    double *tH=(double*)malloc(sizeof(double)*nN);
    double normLtH0=0,normtH0=0,prodtHLtH0=0;
    double normC0=0,prodStH0=0;
    fprintf(fp,"#C Lyp Lypy LtH tH NN\n");
    for(i=0;i<imaxS;i++){
      n=sL[i];
      //n=nS[i];
      Lypy[n]=0;
      flag_tH=0;
      for(t=0;t<nt;t++){
	double e=yp[n][t]-ypN[1][t];
	Lypy[n]+=(e*e);
	if(flag_tH==0 && fabs(e)>=e4t){
	  tH[n]=t-1;
	  flag_tH=1;
	}
      }
      Lypy[n]=sqrt(Lypy[n]/nt);
      fprintf(fp,"%.7e %.7e %.7e %g %g %d\n",S[_nti][n],Lyp[n],Lypy[n],LtH[n],tH[n],NN[n]);
    }
    double meanS=0,meanLyp=0,meanLypy=0,meantH=0,meanLtH=0;
    //    int neval=0;
    double neval=0+1e-20;
    for(i=0;i<imaxS;i++){
      n=sL[i];
      if(LtH[n]>=LtHth_min && LtH[n]<=LtHth_max){
	meanS   +=S[_nti][n];
	meanLyp +=Lyp[n];
	meanLypy+=Lypy[n];
	meanLtH+=LtH[n]; 
	meantH  +=tH[n];
	neval++;
      }
    }
    meanS/=neval;
    meanLyp/=neval;
    meanLypy/=neval;
    meantH/=neval;
    meanLtH/=neval;
    //    fprintf(stderr,"%d %d \n",LtHth_min,LtHth_max);
    for(i=0;i<imaxS;i++){
      n=sL[i];
      if(LtH[n]>=LtHth_min && LtH[n]<=LtHth_max){
	normC      +=square(S[_nti][n]-meanS);
	normLyp    +=square(Lyp[n]-meanLyp);
	normLypy   +=square(Lypy[n]-meanLypy);
	normLtH    +=square(LtH[n]-meanLtH);
	normtH     +=square(tH[n]-meantH);
	prodSLyp   +=(S[_nti][n]-meanS)*(Lyp[n]-meanLyp);
	prodSLypy  +=(S[_nti][n]-meanS)*(Lypy[n]-meanLypy);
	prodStH    +=(S[_nti][n]-meanS)*(tH[n]-meantH);
	prodLypLypy+=(Lyp[n]-meanLyp)*(Lypy[n]-meanLypy);
	prodLyptH  +=(Lyp[n]-meanLyp)*(tH[n]-meantH);
	prodLypytH +=(Lypy[n]-meanLypy)*(tH[n]-meantH);
	prodtHLtH  +=(tH[n]-meantH)*(LtH[n]-meanLtH);
	fprintf(stderr,"%d %g %g #NN[n], LtH tH\n",NN[n],LtH[n],tH[n]);
	
	normC0      +=square(S[_nti][n]);
	prodStH0    +=(S[_nti][n])*(tH[n]);
	
	normLtH0    +=square(LtH[n]);
	normtH0     +=square(tH[n]);
	prodtHLtH0  +=(tH[n])*(LtH[n]);
      }
    }
    normC=sqrt(normC);
    normLyp=sqrt(normLyp);
    normLypy=sqrt(normLypy);
    normtH=sqrt(normtH);
    normLtH=sqrt(normLtH);

    normLtH0=sqrt(normLtH0);   normtH0=sqrt(normtH0);
    normC0=sqrt(normC0);
    double corSLyp=prodSLyp/(normC*normLyp);
    double corSLypy=prodSLypy/(normC*normLypy);
    double corStH=prodStH/(normC*normtH);
    double corLypLypy=prodLypLypy/(normLyp*normLypy);
    double corLyptH=prodLyptH/(normLyp*normtH);
    double corLypytH=prodLypytH/(normLypy*normtH);
    double cortHLtH=prodtHLtH/(normtH*normLtH+ZERO);

    double simtHLtH=prodtHLtH0/(normtH0*normLtH0+ZERO);
    double simStH  =prodStH0/(normC0*normtH0+ZERO);
    //
    fprintf(stdout,"#H%3d<E%3dL%3d>N%3dS%5.3fL%5.3f_L%5.2f",tH_nrep,Hexp,(int)LtH[iLtHmax],NN[nrep],S[_nti][nrep],Lyp[nrep],Lypy[nrep]);
    fprintf(stdout,"bst[H%3dN%3dS%5.3fL%5.2f(%2d/3%d)_L%5.2f]",best_tH,NN[best_n],S[_nti][best_n],Lyp[best_n],iL_best_n,imaxS,Lypy[best_n]);
    fprintf(stdout,"H*HL%5.2f(s%.3fn%d)S*H%g(s%.3f)N%d-%d\n",cortHLtH,simtHLtH,(int)neval,corStH,simStH,NN[iNsamin],NN[iNsamax]);
    fprintf(stdout,"#S*Lyp%g S*Lypy%g Lyp*Lypy%g Lyp*tH%g Lypy*tH%g #corralation of losses\n",corSLyp,corSLypy,corLypLypy,corLyptH,corLypytH);

    {
      int _j;
      for(_j=0;_j<imaxS;_j++){
	int j=nS[_j];
	fprintf(stdout,"%d %g %d #check LOOCV horizon LtHij\n",j,LtHij[iLtHmax*nN+j],NN[iLtHmax]);
      }
    }
    //    fprintf(stdout,"H*HL%.3f(%d)S*H%g\n#S*Lyp%g S*Lypy%g Lyp*Lypy%g Lyp*tH%g Lypy*tH%g #corralation of losses\n",cortHLtH,(int)neval,corStH,corSLyp,corSLypy,corLypLypy,corLyptH,corLypytH);

    //fprintf(stderr,"#tH%3dN%3dC%5.3fL%5.3f_L%5.3f",tH_nrep,NN[nrep],S[_nti][nrep],Lyp[nrep],Lypy[nrep]);
    //fprintf(stderr,"bst[tH%3dN%3dC%5.3fL%5.3f(%d/%d)_L%5.3f]\n",best_tH,NN[best_n],S[_nti][best_n],Lyp[best_n],iL_best_n,imaxS,Lypy[best_n]);
    //fprintf(stdout,"#tH*LtH%.3f(%d) C*Lyp%g C*Lypy%g C*tH%g Lyp*Lypy%g Lyp*tH%g Lypy*tH%g ## corralation of losses\n",cortHLtH,neval,corSLyp,corSLypy,corStH,corLypLypy,corLyptH,corLypytH);
    //    fprintf(stdout,"#cor CLyp%g CLypy%g CtH%g LypLypy%g LyptH%g LypytH%g tHLtH%g\n",corSLyp,corSLypy,corStH,corLypLypy,corLyptH,corLypytH,cortHLtH);
    fclose(fp);

  ///////////
    sprintf(fnout,"%s/tspALL.dat",ds[0]);
    fp=fopen(fnout,"w");
    for(t=0;t<nt;t++){
      for(i=0;i<nN2;i++) fprintf(fp,"%g ",ypN[i][t]);
      fprintf(fp,"\n");
    }
    fclose(fp);

    sprintf(fnout,"%s/tspSth.dat",ds[0]);
    fp=fopen(fnout,"w");
    for(t=0;t<nt;t++){
      for(i=0;i<imaxS;i++){
	fprintf(fp,"%.7e ",ypN[sL[i]+2][t]);
	//	fprintf(fp,"%.7e ",yp[sL[i]][t]);
      }
      fprintf(fp,"\n");
    }
    fclose(fp);
    //
    {
      sprintf(fnout,"%s/tspSth_id.dat",ds[0]);
      fp=fopen(fnout,"w");
      for(i=0;i<imaxS;i++){
	fprintf(fp,"%d\n",sL[i]);
      }
      fclose(fp);
      printf("#check tspSth_id is saved in %s\n",fnout);
    }
    //
    sprintf(fnout,"%s/yg.dat",ds[0]);
    fp=fopen(fnout,"w");
    for(t=0;t<nt;t++){
	fprintf(fp,"%.7e ",ypN[1][t]);
      fprintf(fp,"\n");
    }
    fclose(fp);

//    sprintf(fnout,"tspsimT.dat");//until ntsim
//    fp=fopen(fnout,"w");
//    fprintf(fp,"#ntsim=%d nN2=%d imaxS=%d\n",ntsim,nN2,imaxS);
//    for(i=0;i<imaxS;i++){//    for(i=0;i<nN2;i++){//    
//      n=sL[i];
//      for(t=0;t<ntsim;t++){
//	fprintf(fp,"%g ",ypN[n][t]);
//      }
//      fprintf(fp,"\n");
//    }
//    fclose(fp);

    sprintf(fnout,"tmp/tspp.dat");//pp: predprob
    fp=fopen(fnout,"w");
    for(t=0;t<nt;t++){
      fprintf(fp,"%g %g %g %g %g\n",ypN[0][t],ypN[1][t],yp[nrep][t],ypmin[t],ypmax[t]);
      //t,y0,yp,ypmin,ypmax
    }
    fclose(fp);
    sprintf(fnplt,"tmp/tspp.plt");
    fp=fopen(fnplt,"w");
    fprintf(fp,"set style data lines;set nokey\n");
    fprintf(fp,"set term postscript eps enhanced color; set output \"tspSth.eps\"\n");
    for(i=0;i<imaxS;i++){//20160516 modified
      n=sL[i];
      if(i==0) fprintf(fp,"plot \"%s/tspALL.dat\" using 1:%d lt 1 lc rgb \"black\" t \"\"\\\n",ds[0],n+3);
      else fprintf(fp,", \"\" using 1:%d lt 1 lc rgb \"black\" t \"\"\\\n",n+3);
    }
    fprintf(fp,", \"%s\" using 1:%d w l lt 1 lw 2 lc rgb \"red\"\n",fnout,2);//yp
    fprintf(fp,"set term postscript eps enhanced color; set output \"tspp.eps\"\n");
    //    fprintf(fp,"\nset term tgif;set output \"tmp/tspSth.obj\";replot;set term x11\n");
    //    fprintf(fp,"\npause -1 \"%s:hit return to quit.\"\n",fnplt);
    ///
    fprintf(fp,"plot \"%s\" using 1:4 lt 3 t \"ypmax\", \"\" using 1:5 lt 4 t \"ypmin\", \"\" using 1:2 w l lt 2 lw 1 t \"y\", \"\" using 1:3 w l lt 1 lw 2 t \"yN%d\"",fnout,NN[nrep]);
    //   fprintf(fp,"\npause -1 \"%s: hit return to see details.\"\n",fnplt);
    //    fprintf(fp,"set term tgif;set output \"tmp/tspp.obj\";replot;set term x11\n");
    fclose(fp);
    sprintf(cmd,"gnuplot %s&",fnplt);
    //    sprintf(&cmd[strlen(cmd)],"&");
    system(cmd);
//    
//    sprintf(cmd,"xterm -geometry 50x5+0-0 -e gnuplot -geometry 320x180+0+0 %s",fnplt);
//    fprintf(stderr,"Execute '%s'.\n",cmd);
//    sprintf(&cmd[strlen(cmd)],"&");
    fprintf(stderr,"Execute gv tspSth.eps& gv tspp.eps& # to see the result.\n");
    if(DISP!=0) {
      sprintf(cmd,"gv tspSth.eps&");
      system(cmd);
      sprintf(cmd,"gv tspp.eps&");
    }

    // probability map
    sprintf(fnout,"tmp/typ.dat");
    fp=fopen(fnout,"w");
    double *py=(double*)malloc(sizeof(double)*py_n);
    double py_dy=(py_yM-py_ym)/py_n;
    for(t=0;t<nt;t++){
      int nn=0;
      for(i=0;i<py_n;i++) py[i]=0;
      for(i=0;i<imaxS*Hth;i++){//
	n=sL[i];
	int ii=(yp[n][t]-py_ym)/py_dy-0.5;
	py[ii]++;
	nn++;
      }
//      for(n=0;n<nN;n++) {
//	if(S[_nti][n]>=Sth){
//	  i=(yp[n][t]-py_ym)/py_dy-0.5;
//	  py[i]++;
//	  nn++;
//	}
//      }
      for(i=0;i<py_n;i++){
	py[i]/=nn;
	fprintf(fp,"%d %g %g %d\n",t,py_ym+i*py_dy,py[i],nn);
      }
      fprintf(fp,"\n");
    }
    fprintf(stdout,"#saved in %s\n",fnout);
    
  }//attractor similarity
  
////#ifdef COMPETITIVE
////  // clustering with competitive nets
////  int nw=5;
////  double **w=(double **)malloc(sizeof(double*)*(nw));
////  for(i=0;i<nw;i++) w[i]=(double*)malloc(sizeof(double)*nt);
////  int *jw=(int*)malloc(sizeof(int)*nN);
////  int *iw=(int*)malloc(sizeof(int*)*(nw));
////  int *iv=(int*)malloc(sizeof(int*)*(nw));
////  {
////    double **v=(double **)malloc(sizeof(double*)*(nw));
////    for(i=0;i<nw;i++) v[i]=(double*)malloc(sizeof(double)*nt);
////    int *nv=(int*)malloc(sizeof(int)*nw);
////    int it=100;
////    double *d=(double*)malloc(sizeof(double)*nw);
////    int *nd=(int*)malloc(sizeof(int)*nw);
////    double *L=(double*)malloc(sizeof(double)*nN);
////    //initialize
////    int seed=1;
////    InitMt((unsigned long)seed);
////    for(j=0;j<nw;j++){
////      int i=NextIntEx(nN);
////      iw[j]=i;
////    }
////    int _it;
////    for(_it=0;_it<it;_it++){
////    //distortion
////      for(j=0;j<nw;j++){//init v and nv
////	d[j]=nd[j]=nv[j]=0;
////      }
////      for(i=0;i<nN;i++){
////	//search nearest w
////	int _jw=0;
////	double dmin=INFTY;
////	for(j=0;j<nw;j++){
////	  double _d=kyori(yp[iw[j]],yp[i],nt);
////	  if(dmin>_d){
////	    _jw=j;
////	    dmin=_d;
////	  }
////	}
////	//	iv[_jw]=i;
////	jw[i]=_jw;
////	nv[_jw]++;
////	d[_jw]+=dmin;
////	nd[_jw]++;
////      }
////      //the center series
////      for(j=0;j<nw;j++){
////	int ii;
////	double Lmin=INFTY;
////	for(i=0;i<nN;i++){
////	  L[i]=0;
////	  if(j!=jw[i]) continue;
////	  for(ii=0;ii<nN;ii++){
////	    if(i==ii) continue;
////	    if(j!=jw[ii]) continue;
////	    for(t=0;t<nt;t++){
////	      double e=yp[i][t]-yp[ii][t];
////	      L[i]+=e*e;
////	    }
////	  }
////	  if(L[i]<Lmin){
////	    Lmin=L[i];
////	    iLmin=i;
////	  }
////	}
////	iv[j]=iLmin;
////      }
////
////      //check convergence
//////      double sumdw=0;
//////      for(j=0;j<nw;j++){
//////	for(t=0;t<nt;t++) sumdw+=fabs(w[j][t]-v[j][t]);
//////      }
//////      if(sumdw<1){
//////	fprintf(stderr,"#converged at it=%d\n",it);
//////	break;//converged
//////      }
////      //replace w by v
////      iw[j]=iv[j];
////
////      //calc distortion
////      for(j=0;j<nw;j++) d[j]=nd[j]=nv[j]=0;
////      for(i=0;i<nN;i++){
////	//search nearest w
////	int _jw=0;
////	double dmin=INFTY;
////	for(j=0;j<nw;j++){
////	  double _d=kyori(yp[iw[j]],yp[i],nt);
////	  if(dmin>_d){
////	    _jw=j;
////	    dmin=_d;
////	    jw[i]=_jw;
////	  }
////	}
////	d[_jw]+=dmin;
////	nv[_jw]++;
////      }
////      //serach dmax and dmin
////      int jdmax=0,jdmin=0;
////      for(j=0;j<nw;j++)	d[j]/=(nv[j]+ZERO);
////      double dmax=d[0],dmin=d[0];
////      for(j=1;j<nw;j++){
////	if(d[j]>dmax) {dmax=d[j];jdmax=j;}
////	if(d[j]<dmin) {dmin=d[j];jdmin=j;}
////      }
//////
//////      for(i=0;i<nN;i++){
//////	//search nearest w
//////	int _jw=0;
//////	double dmin=INFTY;
//////	for(j=0;j<nw;j++) d[j]=nd[j]=0;
//////	for(j=0;j<nw;j++){
//////	  double _d=kyori(yp[iw[j]],yp[i],nt);
//////	  if(dmin>_d){
//////	    _jw=j;
//////	    dmin=_d;
//////	  }
//////	}
//////	jw[i]=_jw;
//////	d[_jw]+=dmin;
//////	nd[_jw]++;
//////      }
//////      //serach dmax and dmin
//////      int jdmax=0,jdmin=0;
//////      double dmax=-1,dmin=INFTY;
//////      for(j=0;j<nw;j++){
//////	d[j]/=(nd[j]+ZERO);
//////	if(d[j]>dmax) {d[j]=dmax;jdmax=j;}
//////	if(d[j]<dmin) {d[j]=dmin;jdmin=j;}
//////      }
////      //asymptotic optimality
////      double renint_th=3;
////      //      fprintf(stderr,"#reinit dmax dmin %d[%g] %d[%g] it%d\n",jdmax,dmax,jdmin,dmin,_it);
////      if(dmax>dmin*3){//reinit jdmin
////	for(i=0;i<nN;i++){
////	  if(jw[i]==jdmax && i!=iw[jdmax]){
////	    iv[jdmin]=i;
////	    break;
////	  }
////	}
////	if(iv[jdmin]!=iw[jdmin]) iw[jdmin]=iv[jdmin];
////      }
////    }
////    fp=fopen("w.dat","w");
////    fprintf(fp,"#dn:");
////    for(j=0;j<nw;j++) fprintf(fp,"[%d]d%gnv%diw%d ",j,d[j],nv[j],iw[j]);
////    fprintf(fp,"\n");
////    for(t=0;t<nt;t++){
////      fprintf(fp,"%d ",t);
////      for(j=0;j<nw;j++){
////	fprintf(fp,"%.7e ",yp[iw[j]][t]);
////      }
////      fprintf(fp,"\n");
////    }
////    fclose(fp);
////  }
////#endif //#ifdef COMPETITIVE

////#ifdef Lyp
////  for(i=0;i<nN;i++) Lyp[i]=0;
////  int _i0=-1,_i1=-1;
////  for(i=i0;i<=i1;i++){
////    //    Lyp[i]=0;
////    double ne=0;
////    for(j=i0;j<=i1;j++){
////      if(i==j) continue;
////      for(t=0;t<nt;t++){
////	double e=yp[i][t]-yp[j][t];
////	if(fabs(e)>=e4t) break;
////	Lyp[i]+=e*e;
////	ne++;
////      }
////    }
////    Lyp[i]=sqrt(Lyp[i]/ne);
////    if(Lyp[iLmin]>Lyp[i]) iLmin=i;
////    if(Lyp[iLmax]<Lyp[i]) iLmax=i;
////    if(Lyp[i]<e_th){//??
////      if(_i0<0) _i0=i;//imin
////      _i1=i;//imax
////    }
////    //    fprintf(fp,"%d %g %g #N LOOMSE saN\n",NN[i],Lyp[i],saN[i]);
////  }
////  //  fclose(fp);
////
////  //for the probability of NN
////  double *NNx=(double *)malloc(sizeof(double)*(nN));
////  NNx[i0]=NN[i0]/2;NNx[i0-1]=NN[i0-1]/2;
////  for(i=i0;i<i1-1;i++) NNx[i]=(NN[i+1]-NN[i-1])/2;
////  double sumN=0;
////  for(i=i0;i<i1;i++) sumN+=NNx[i];
////  for(i=i0;i<i1;i++) NNx[i]/=sumN;
////  ///////////////////////sort Lyp
////  int *s=(int*)malloc(sizeof(int)*nN);
////  for(i=i0;i<i1;i++) s[i]=i;
////  for(i=i0;i<i1-1;i++){
////    for(j=i+1;j<i1;j++){
////      if(Lyp[s[i]]>Lyp[s[j]]){
////	int si=s[i];
////	s[i]=s[j];
////	s[j]=si;
////      }
////    }
////  }
////  ///search yp_theta at cumulative prob of NN
////  double _pNth=1;
////  for(i=i1-1;i>=i0;i--){
////    _pNth-=NNx[s[i]];
////    if(_pNth<pNth) break;//greatest less than pNth
////  }
////  //  fprintf(stderr,"#pth=%g-1\n",cNNxs);
////  int ith=i;
////
////  double *Lyp1=(double *)malloc(sizeof(double)*(nN));//distance
////  int iL1min=-1,iL1max=-1;
////  for(i=0;i<nN;i++) Lyp1[i]=0;
////  for(i=i0;i<=ith;i++){
////    //   Lyp1[s[i]]=0;
////    int ne=0;
////    for(j=i0;j<=ith;j++){
////      if(i==j) continue;
////      for(t=0;t<nt;t++){
////	double e=yp[s[i]][t]-yp[s[j]][t];
////	if(fabs(e)>=e4t) break;
////	Lyp1[s[i]]+=e*e;
////	ne++;
////      }
////    }
////    Lyp1[s[i]]=sqrt(Lyp1[s[i]]/ne);
////    if(iL1min<0 || Lyp1[iL1min]>Lyp1[s[i]]) iL1min=s[i];
////    if(iL1max<0 || Lyp1[iL1max]<Lyp1[s[i]]) iL1max=s[i];
////  }
////  sprintf(fnout,"Lyp.dat");//pp: predprob
////  fp=fopen(fnout,"w");
////  for(i=0;i<nN;i++){
////    if(Lyp[i]>0 && Lyp1[i]>0)   fprintf(fp,"%d %g %g %g #N LOOMSE saN Lyp Lyp1\n",NN[i],saN[i],Lyp[i],Lyp1[i]);
////    else if(Lyp[i]<=0 && Lyp1[i]<=0) fprintf(fp,"%d %g -  - #N LOOMSE saN\n",NN[i],saN[i]);
////    else if(Lyp[i]<=0)          fprintf(fp,"%d %g - %g #N LOOMSE saN Lyp1\n",NN[i],saN[i],Lyp1[i]);
////    else if(Lyp1[i]<=0)         fprintf(fp,"%d %g %g - #N LOOMSE saN Lyp\n",NN[i],saN[i],Lyp[i]);
////    //    fprintf(fp,"%d %g %g #N LOOMSE saN\n",NN[i],saN[i],Lyp[i],Lyp1[i]);
////  }
////  fclose(fp);
////
////  double rmse=0;
////  int ne=0;
////  for(t=0;t<nt;t++){
////    double e=yp[iL1min][t]-ypN[1][t];
////    rmse+=e*e;
////    ne++;
////  }
////  rmse=sqrt(rmse/ne);
////  
////  int *s1=(int*)malloc(sizeof(int)*nN);
////  for(i=i0;i<=ith;i++) s1[i]=s[i];
////  for(i=i0;i<ith;i++){
////    for(j=i+1;j<=ith;j++){
////      if(Lyp1[s1[i]]>Lyp1[s1[j]]){
////	int s1i=s1[i];
////	s1[i]=s1[j];
////	s1[j]=s1i;
////      }
////    }
////  }
////  fprintf(stderr,"#rmse%gpN%g-%gL",rmse,_pNth,pNth);
////  //  fprintf(stderr,"#L1m%g(rmse%g)pNth%g-%gN:",Lyp1[iL1min],rmse,_pNth,pNth);
////
////  for(i=i0;i<=ith;i++) fprintf(stderr,"%gN%d ",Lyp1[s1[i]],NN[s1[i]]);
////  //  for(i=i0;i<=ith;i++) fprintf(stderr,"%d ",NN[s1[i]]);
////  //  fprintf(stderr,"#Lyp1:%g[%d] - %g[%d]\n",Lyp1[iL1min],iL1min,Lyp1[iL1max],iL1max);
//////#define NEW2
//////#ifdef NEW2
//////  int NC=NN[iLmin];
//////  int ND=NN[iNsamax]-NN[iNsamin];
//////  int N0=NC-rN*ND;
//////  int N1=NC+rN*ND;
//////  for(i=iNsamin;i<=iNsamax;i++){
//////    if(NN[i]>=N0){
//////      i0=i;
//////      break;
//////    }
//////  }
//////  for(i=iNsamax;i>=iNsamin;i--){
//////    if(NN[i]<=N1){
//////      i1=i;
//////      break;
//////    }
//////  }
////////  int ic=iLmin;
////////  int id=i1-i0+1;
////////  i0=ic-rN*id;
////////  i1=ic+rN*id;
////////  if(i0<iNsamin) i0=iNsamin;
////////  if(i1>iNsamax) i0=iNsamax;
////////
//////#endif
////  //  fprintf(stderr,"#minLyp[N%d]%g maxLyp[N%d]%g \n",NN[iLmin],Lyp[iLmin],NN[iLmax],Lyp[iLmax]);
////  //  i0=_i0;  i1=_i1;
////
////  sprintf(fnplt,"Lyp.plt");
////  fp=fopen(fnplt,"w");
////  fprintf(fp,"set style data lines;set xlabel \"N\"\n");
////  //  fprintf(fp,"set title \"sa, Lyp (Leave-One-Out RMSE) min%gN%d max %gN%d\"\n",Lyp[iLmin],NN[iLmin],Lyp[iLmax],NN[iLmax]);
////  fprintf(fp,"plot \"%s\" using 1:2 w lp t \"|S|\",\"\" using 1:3 t \"L0\", \"\" using 1:4 t \"L1\", %g t \"min|S|%.2g\", %g t \"max|S|%.2g\", %g t \"L0th%.2g\"",fnout,saN[iNsamin],saN[iNsamin],saN[iNsamax],saN[iNsamax],Lyp[s[ith]],Lyp[s[ith]]);
////  fprintf(fp,"\npause -1 \"%s: hit return to quit.\"\n",fnplt);
////  fclose(fp);
////  sprintf(cmd,"xterm -geometry 50x5+0-0 -e gnuplot -geometry 320x180+0+0 %s",fnplt);
////  fprintf(stderr,"Execute '%s'.\n",cmd);
////  sprintf(&cmd[strlen(cmd)],"&");
////  system(cmd);
////  //  fprintf(stderr,"#Lyp: %g[%d] - %g[%d]\n",Lyp[iLmin],NN[iLmin],Lyp[iLmax],NN[iLmax]);
////  //  fprintf(stderr,"#Lyp: %g[%d] - %g[%d]\n",Lyp[iLmin],iLmin,Lyp[iLmax],iLmax);
////  //  fprintf(stderr,"####Lyp: %g[%d] - %g[%d]\n",Lyp[i0],i0,Lyp[i1],i1);
////  for(t=0;t<nt;t++){
////    ypmax[t]=-INFTY;ypmin[t]=INFTY;
////    for(i=i0;i<=ith;i++){
////      if(ypmax[t]<yp[s[i]][t]) ypmax[t]=yp[s[i]][t];
////      if(ypmin[t]>yp[s[i]][t]) ypmin[t]=yp[s[i]][t];
////    }
////  }
////
////  sprintf(fnout,"tspp.dat");//pp: predprob
////  fp=fopen(fnout,"w");
////  for(t=0;t<nt;t++){
////    fprintf(fp,"%g %g %g %g %g %g\n",ypN[0][t],ypN[1][t],yp[s[i0]][t],ypmin[t],ypmax[t],yp[s[ith]][t]);
////    //    fprintf(fp,"%g %g %g %g %g %g\n",ypN[0][t],ypN[1][t],yp[iLmin][t],ypmin[t],ypmax[t],yp[iLmax][t]);
////  }
////  fclose(fp);
////  ///////////
////  sprintf(fnplt,"tspp.plt");
////  fp=fopen(fnplt,"w");
////  fprintf(fp,"set style data lines\n");
////  //  fprintf(fp,"set title \"Nrange N%d-N%d\"\n",NN[i0],NN[i1]);
////  //  fprintf(fp,"plot \"%s\" using 1:2 w lp t \"y\", \"\" using 1:3:4:5 with yerrorbars t \"N%d-%d\" , \"\" using 1:3 w l t\"yN%d\"",fnout,NN[i0],NN[i1],NN[iLmin]);
////  fprintf(fp,"plot \"%s\" using 1:2 w lp t \"y\", \"\" using 1:3:4:5 with yerrorbars t \"N%d-%d\" , \"\" using 1:3 w l t\"yN%d\"",fnout,NN[i0],NN[i1],NN[iL1min]);
////  fprintf(fp,"\npause -1 \"%s: hit return to see details.\"\n",fnplt);
////  fprintf(fp,"plot \"%s\" using 1:2 w lp t \"y\", \"\" using 1:3:4:5 with yerrorbars t \"N%d-%d\" , \"\" using 1:3 w l t\"yN%d\"\\\n",fnout,NN[i0],NN[i1],NN[iL1min]);
////  for(i=i0;i<=ith;i++) fprintf(fp,", \"%s\" using 1:%d t \"yN%d\"\\\n",fpa,s[i]+3,NN[s[i]]);
////  fprintf(fp,"\npause -1 \"%s:hit return to quit.\"\n",fnplt);
////  fclose(fp);
////
////  sprintf(cmd,"xterm -geometry 50x5+0-0 -e gnuplot -geometry 320x180+0+0 %s",fnplt);
////  fprintf(stderr,"Execute '%s'.\n",cmd);
////  sprintf(&cmd[strlen(cmd)],"&");
////  system(cmd);
////#endif //#ifdef Lyp

  return(0);
}


#ifdef atode
#endif //#ifdef atode
