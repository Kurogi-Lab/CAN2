#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include "my_misc.c"
#define PI 3.141592653589793
#undef isnump
#define isnump(c) ((c >= '0' && c <= '9')||c=='.'||c=='-'||c=='+'||c==' '||c=='e')
typedef struct{
  int s0;
  int v0;
  double mse;
} Recog;

int _t4=200;
int _t0,_t1;
int k2=0;
char *DISP="00";
char directry[128];
#define fnsize 256
#define INF 1e20

#define nsamplemax 50
int main(int argc,char **argv)
{
  if(argc<2){
    fprintf(stderr,"Usage: %s [optins below] \n",argv[0]);
    fprintf(stderr,"sp:<name1>:<name2>...  : names of speakers.\n");//sat
    fprintf(stderr,"tx:<text1>:<text2>...  : names of texts.\n");//sat
    fprintf(stderr,"k:<k>                  : analysis order.\n");
    fprintf(stderr,"N:<N1>-<N2>            : Number of Units for CAN2 Ensemble.\n");
    fprintf(stderr,"T:<T>                  : number of training iterations.\n");
    fprintf(stderr,"t:<t0>-<t3>            : [0,<t0>] for training, [<t0>,<t3>] for test.\n");
    fprintf(stderr,"t:<t0>:<t1>-<t3>       : [0,<t0>] for training [<t1>,<t3>] for test.\n");
    fprintf(stderr,"ttr:<t0>:<t1>:<toffset>:[<toffset>,<t0>+<toffset>] for training, [<t0>+<toffset>,<t1>+<toffset>] for bestmsp.\n");
    fprintf(stderr,"tte:<t2>:<t3>          : [<t2>,<t3>] for test.\n");
    fprintf(stderr,"tt:<t0>:<t1>:<t2>:<t3>:<t4> :[<t0>,<t0>+<t1>] for training, [<t2>,<t2>+<t3>] for test, <t4> for bestmsp.\n");
    fprintf(stderr,"m:<shrink || direct>   : recognition method.\n");
    fprintf(stderr,"DISP:<00||10||11>          : DISP[0]==1 for generate graphic files,  DISP[1]==1 for nodisplay.\n");

    return(-1);
  }
  int N1=1,N2=1;
  int k=9;
  int T=100;//number of training iterations
  int N;  //  int nEns=1,NN,N;
//#define nvowel 5//sat
  int i,j;
  char *sname[nsamplemax];//speaker name,sat
  char *text[nsamplemax];//text,sat
  char *snametext[nsamplemax];
  char cmd[5000];
  FILE *fp;
  char *method="shrink               ";
  int t0,t1,toffset=0;//sat
  int tp[2];//sat
  //int ncorrect;
  int itr;  //  int ite,itr;
  //  int t,v;
  int s,tx;//variables for s:sameple, tx:text//sat
  int ns=0;//number of speaker?,sat
  int ntx=0;//number of speaker?,sat
  int nst=0;//number of speaker?,sat
  int rs_method=-1,rs_seed=0,rs_ens=20,rs_Boost=0,rs_t_boost=0;double rs_alpha=0.7;//2017
  //  int rs_method=-1,rs_seed=0,rs_ens=20,rs_Boost=2,rs_t_boost=1;double rs_alpha=0.7;//2012
  
  //sprintf(directry,"../data");//sat?
  char cmd0[1024]; sprintf(cmd0,"%s",argv[0]); for(i=1;i<argc;i++) sprintf(&cmd0[strlen(cmd0)]," %s",argv[i]);
  int *uav=(int *)malloc(argc*sizeof(int));//use argv or not.
  for(i=1;i<argc;i++) uav[i]=1;
  for(i=1;i<argc;i++){
    uav[i]=0;
    if(strncmp(argv[i],"st:",3)==0 ){
      itr=i;//reference or training
      char *p;
      s=0;
      snametext[s]=p=&argv[i][3];
      //      s++;
      for(;;){
	if(*p==0) break;
	if(*p==':') {
	  *p=0;
	  s++;p++;
	  snametext[s]=p;
	}
	p++;
      }
      nst=s+1;
    }
    else if(strncmp(argv[i],"sp:",3)==0 ){
      itr=i;//reference or training
      char *p;
      s=0;
      sname[s]=p=&argv[i][3];
      //      s++;
      for(;;){
	if(*p==0) break;
	if(*p==':') {
	  *p=0;
	  s++;p++;
	  sname[s]=p;
	}
	p++;
      }
      ns=s+1;
    }
    else if(strncmp(argv[i],"tx:",3)==0 ){
      itr=i;//reference or training
      char *p;
      tx=0;
      text[tx]=p=&argv[i][3];
      for(;;){
	if(*p==0) break;
	if(*p==':') {
	  *p=0;
	  tx++;p++;
	  text[tx]=p;
	}
	p++;
      }
      ntx=tx+1;
    }
    else if(strncmp(argv[i],"N:",2)==0){
      uav[i]=0;
      sscanf(&argv[i][2],"%d",&N);
      N1=N2=N;
      //      nEns=N2-N1+1;
    }
    else if(strncmp(argv[i],"k:",2)==0){
      uav[i]=0;
      sscanf(&argv[i][2],"%d",&k);
    }
    else if(strncmp(argv[i],"m:",2)==0){
      uav[i]=0;
      method=&argv[i][2];
    }
    else if(strncmp(argv[i],"T:",2)==0){
      uav[i]=0;
      sscanf(&argv[i][2],"%d",&T);
    }
    else if(strncmp(argv[i],"dir:",4)==0){
      uav[i]=0;
      sprintf(directry,"%s",&argv[i][4]);
    }
    else if(strncmp(argv[i],"rsa:",4)==0){
      uav[i]=1;
      sscanf(&argv[i][4],"%d:%lf:%d:%d",&rs_method,&rs_alpha,&rs_seed,&rs_ens);
      if(rs_method==-1){
	rs_ens=1;
	rs_alpha=0;
	rs_seed=0;
	rs_t_boost=0;
	rs_Boost=0;
      }
    }
    else if(strncmp(argv[i],"DISP:",5)==0){
      uav[i]=1;
      DISP=&argv[i][5];
      //      sscanf(&argv[i][5],"%d",&DISP);
    }
    else if(strncmp(argv[i],"tt:",3)==0){
      uav[i]=0;
      sscanf(&argv[i][3],"%d:%d",&_t0,&_t1);//sat
    }
    else if(strncmp(argv[i],"tp:",3)==0){//use this
      uav[i]=0;
      sscanf(&argv[i][3],"%d-%d",&t0,&t1);//new,sat
      tp[0]=t0;
      tp[1]=t1;
      toffset=t0;
    }
  }

  //
  DIR *pdir;
  if((pdir=opendir("./tmp"))==NULL) system("mkdir ./tmp"); else closedir(pdir);
  //
  if(nst==0){
    for(tx=0;tx<ntx;tx++){
      for(s=0;s<ns;s++){
	sprintf(snametext[nst],"%s-%s",sname[s],text[tx]);
        nst++;
      }
    }
  }
  int n;
  char **snets;//sat
  char **sfb;//sat
  snets=(char**)malloc(nst*sizeof(char*));//sat
  sfb  =(char**)malloc(nst*sizeof(char*));//sat
  for(n=0;n<nst;n++){ //sat
    snets[n]=(char*)malloc(fnsize*rs_ens*sizeof(char));//sat
    sfb[n]  =(char*)malloc(fnsize*sizeof(char));//sat
  }//sat
//  snets=(char***)malloc(ntx*sizeof(char**));//sat
//  sfb  =(char***)malloc(ntx*sizeof(char**));//sat
//  for(tx=0;tx<ntx;tx++){//sat
//    snets[tx]=(char**)malloc(ns*sizeof(char*));//sat
//    sfb[tx]  =(char**)malloc(ns*sizeof(char*));//sat
//    for(s=0;s<ns;s++){ //sat
//      snets[tx][s]=(char*)malloc(fnsize*rs_ens*sizeof(char));//sat
//      sfb[tx][s]  =(char*)malloc(fnsize*sizeof(char));//sat
//    }//sat
//  }//sat
  //nst nx+ntx-> nst
  for(n=0;n<nst;n++){ 
    //  for(tx=0;tx<ntx;tx++){ for(s=0;s<ns;s++){
    //training
    //int _t11=_t1+1;
    int i;
    char buff[128];
    char fn[128];
    sprintf(fn,"%s/%s.dat",directry,snametext[n]);//tmp/fms-zero9-mmt-nana10-R0.4.dat?
    FILE *fp1=fopen(fn,"r");
    for(i=0;fgets(buff,128,fp1)!=NULL;i++);{
      _t1=i;
    }
    fclose(fp1);
    sprintf(cmd,"./tspredv3 %s/%s.dat %d-%d:%d-%d k:%d N:%d-%d:1",directry,snametext[n],_t0,_t1,_t1-1,_t1,k,N,N);//sat
    sprintf(&cmd[strlen(cmd)]," rsa:%d:%g:%d:%d",rs_method,rs_alpha,rs_seed,rs_ens);
    sprintf(&cmd[strlen(cmd)]," DiffMode:0 M:1-1:1 ib:0:0:0:0 y:0:0:0:0 w:0.2 vt:0.5 vr:10");
    //for(i=1;i<argc;i++){if(uav[i]==1) sprintf(&cmd[strlen(cmd)]," %s",argv[i]);}
    sprintf(&cmd[strlen(cmd)]," DISP:0");
    fprintf(stderr,"Running '%s'\n",cmd);
    sprintf(&cmd[strlen(cmd)]," > /dev/null");
    system(cmd);
    //store result net file name
    for(snets[n][0]=0,j=0;j<rs_ens;j++){
      //    for(snets[tx][s][0]=0,j=0;j<rs_ens;j++){
      sprintf(&snets[n][strlen(snets[n])],"result-ensrs2ge/net/%s:y%d-%d+m%da%gb%d:%ds%dj%dN%dK%d.net ",
	      snametext[n],_t0,_t1,rs_method,rs_alpha,rs_t_boost,rs_Boost,rs_seed,j,N,k);//
    }
    
    sprintf(sfb[n],"%s-k%dN%dt%d-%d",snametext[n],k,N,_t0,_t1);//use later?
    //      sprintf(sfb[tx][s],"%s-%s-k%dN%dt%d-%d",text[tx],sname[s],k,N,_t0,_t1);//use later?
    
    FILE *fp=fopen("param.dat","w");
    fprintf(fp,"0          #0:timeseries,1:function approximation in my_function.c\n");
    fprintf(fp,"%d %d       #channels\n",k,k2);
    fprintf(fp,"%s/%s.dat #training file\n",directry,snametext[n]);
    fprintf(fp,"%d %d      #Ttrain,Ttotal: points in time of training and total data\n",k,0);//dummy
    fprintf(fp,"0 0 0 0    #y0min y0max y1min y1max for normalization\n");
    fprintf(fp,"nls\n");
    fprintf(fp,"%s\n",snets[n]);
    fprintf(fp,"swM\n");
    fprintf(fp,"!cp tmp/M.dat tmp/%s-M.dat\n",sfb[n]);
//    fprintf(fp,"pMs        #poles_M_shrink\n");
//    fprintf(fp,"!cp tmp/M4.dat tmp/%s-M4.dat\n",sfb[n]);
//    fprintf(fp,"!cp tmp/poles4.dat tmp/%s-poles4.dat\n",sfb[n]);//
//    fprintf(fp,"!cp tmp/poles0.dat tmp/%s-poles0.dat\n",sfb[n]);
//    fprintf(fp,"!cp tmp/poles5.dat tmp/%s-poles5.dat\n",sfb[n]);
    fprintf(fp,"quit\n");
    fclose(fp);
    system("./can2<param.dat");
  }
  
  FILE *fpout=stderr;//    fp=stdout;
  {
    fprintf(fpout,"cmd='%s'\n",cmd0);//fprintf(fpout," > /dev/null'\n");
  }

#ifdef ATODE
  if(DISP[0]=='1')
  {
    char fbody[64];
    char *poles[3]={"poles0", "poles",};
    char *pos[6]={"x1,y3","x2,y3", "x1,y2","x2,y2","x1,y1","x2,y1"};
    int p;
    for(n=0;n<nst;n++){      //    for(tx=0;tx<ntx;tx++){for(s=0;s<ns;s++){
      for(p=0;p<1;p++){
	sprintf(fbody,"_sprecog-%s-%s-N%d",snametext[n],poles[p],N);
	fp=fopen("tmp/mkfigs.gpl","w");
	//	fprintf(fp,"set title \"%s-N%dk%d\"\n",snametext[n],N,k);
	fprintf(fp,"set xtics (-2,-1,0,1,2); set ytics (-2,-1,0,1,2); set grid; set size square; set parametric; set pointsize 0.5\n");
	fprintf(fp,"set pointsize 0.4;x1=0.1;x2=0.6;y1=0.1;y2=0.4;y3=0.7;dd=0.4;\n");
	fprintf(fp,"set term postscript eps enhanced color; set output \"tmp/%s.eps\";\n",fbody);
	//	  fprintf(fp,"set terminal tgif; set output \"tmp/%s.obj\"; set pointsize 0.5;x1=0.1;x2=0.6;y1=0.1;y2=0.4;y3=0.7;dd=0.4;\n",fbody);
	//	  fprintf(fp,"#set terminal x11; set pointsize 2;x1=0.1;x2=0.1;y1=0.1;y2=0.1;y3=0.1;dd=0.4;\n");
	//	  fprintf(fp,"set size square dd,dd; set rmargin 0; set lmargin 0; set tmargin 0; set bmargin 0;set multiplot\n");
	if(1==1){//donot use multiplot
	  fprintf(fp,"plot [0:2*pi][-2:2][-2:2] \"tmp/%s-%s.dat\" using 1:2 w p pt 6 lc rgb 'black' t \"%s\", ",sfb[n],poles[p],snametext[n]);
	  fprintf(fp,"cos(t),sin(t) t \"1.0\" w l lw 10 lt 1 lc rgb 'green', 2*cos(t),2*sin(t) t \"2\" w l lw 10 lt 1 lc rgb 'red'\n");
	}
	else if(tx>=6){
	  for(tx=0;tx<6;tx++){
	    //	      fprintf(fp,"set origin %s\n",pos[tx]);
	    fprintf(fp,"plot [0:2*pi][-2:2][-2:2] \"tmp/%s.dat\" using 1:2 t \"%s-%s\", ",sfb[n],poles[p],snametext[n]);
	    fprintf(fp,"cos(t),sin(t) t \"1.0\" w l lw 10 lt 1 lc rgb 'blue', 0.7*cos(t),0.7*sin(t) t \"0.7\" w l lw 10 lt 1 lc rgb 'green'\n");
	    //	      fprintf(fp,"cos(t),sin(t) t \"1.0\" w l lw 10 lc rgb 'blue', 0.7*cos(t),0.7*sin(t) t \"0.7\" w l lw 10 lc rgb 'green'\n");
	    //	      fprintf(fp,"cos(t),sin(t) t \"1.0\" w l lw 10 lt 2, 0.7*cos(t),0.7*sin(t) t \"0.7\" w l lw 10 lt 4\n");
	  }
	}
	else{
	  for(tx=0;tx<ntx;tx++){
	    //	      fprintf(fp,"set origin %s\n",pos[tx]);
	    fprintf(fp,"plot [0:2*pi][-2:2][-2:2] \"tmp/%s-%s.dat\" using 1:2 t \"%s\", ",sfb[n],poles[p],snametext[n]);
	    fprintf(fp,"cos(t),sin(t) t \"1.0\" w l lw 10 lt 1 lc rgb 'blue', 0.7*cos(t),0.7*sin(t) t \"0.7\" w l lw 10 lt 1 lc rgb 'green'\n");
	  }
	}
	fprintf(fp,"set term tgif; set output \"tmp/%s.obj\";replot\n",fbody);
	fprintf(fp,"quit\n");
	fclose(fp);
	sprintf(cmd,"gnuplot tmp/mkfigs.gpl;");
	system(cmd);
        if(strlen(DISP)<=1 || DISP[1]!='0'){
          sprintf(cmd,"gv tmp/%s.eps&",fbody);//pole distribution 
          system(cmd);
	}
	//	sprintf(cmd,"gnuplot tmp/mkfigs.gpl;wait;gv tmp/%s.eps&",fbody);
	//	  sprintf(cmd,"gnuplot tmp/mkfigs.gpl; tgif tmp/%s.obj; gv tmp/%s.eps &",fbody,fbody);
	//	  fprintf(stderr,"************************************************************************\n");
	//	  fprintf(stderr,"* Executing 'gnuplot tmp/mkfigs.gpl; tgif tmp/%s.obj; gv tmp/%s.eps &' *\n",fbody,fbody);
	//	  fprintf(stderr,"* Type 'Ctrl+p' and 'Ctrl+q' at gnuplot window                         *\n");
	//	  fprintf(stderr,"************************************************************************\n");
      }
    }
  }
#endif //ATODE
  return(1);
}
