/////////////////
//loo4vowels.c: leave one out method for vowels 
//Usage:
//loo4vowels N:2 k:8 rsa:2:0.7:1:20 dir:../satovowels/512 faf ffs fkm fks fms fsu ftk fyn mau mms mmy mnm msh mtm mtt mxm
/////////////////
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef PI
#undef PI
#endif
#define PI  3.141592653589793
#define nsamplemax 50//sat
int main(int argc,char **argv)
{
  int i;//,n0=1;
  int N=1;//Number of Units
  int Np;//Number of Units for pole distribution
  int k=63;//Dimension of input vector
  int k2;//Dimension of input vector(pole pattern)
  int B=20;//number of bags
  double r_max;
  double alpha=0.7;
  char rsa[20];
  char dir[256];
  char dir2[256];
  char data[256];
  char dout[256];
  int _nt,_nr,tt,tl,t0;
  char *sname[nsamplemax];//speaker name,sat
  char *text[nsamplemax];//text,sat
  char *snametext[nsamplemax];
  int s,tx;//variables for s:sameple, tx:text//sat
  int ns;//number of speaker?,sat
  int ntx;//number of speaker?,sat
  int nst=0;//number of speaker?,sat
  //  int DISP=0;
  char *DISP="00";
  //sprintf(dir,"../satovowels/512");//sat
  sprintf(rsa,"rsa:2:0.7:1:20");
  for(i=1;i<argc;i++){
    if(strncmp(argv[i],"N:",2)==0){//
      sscanf(&argv[i][2],"%d",&N);
    }
    if(strncmp(argv[i],"Np:",3)==0){//
      sscanf(&argv[i][3],"%d",&Np);
    }
    else if(strncmp(argv[i],"k:",2)==0){
      sscanf(&argv[i][2],"%d",&k);
    }
    else if(strncmp(argv[i],"B:",2)==0){
      sscanf(&argv[i][2],"%d",&B);
    }
    else if(strncmp(argv[i],"alpha:",6)==0){
      sscanf(&argv[i][6],"%lf",&alpha);
    }
    else if(strncmp(argv[i],"r_max:",6)==0){
      sscanf(&argv[i][6],"%lf",&r_max);
    }
    else if(strncmp(argv[i],"rsa:",4)==0){
      sprintf(rsa,"%s",argv[i]);
    }
    else if(strncmp(argv[i],"dir:",4)==0){
      sprintf(dir,"%s",&argv[i][4]);
    }
    else if(strncmp(argv[i],"dout:",5)==0){
      sprintf(dout,"%s",&argv[i][5]);
    }
    else if(strncmp(argv[i],"data:",5)==0){
      sprintf(data,"%s",&argv[i][5]);
    }
    else if(strncmp(argv[i],"nr:",3)==0){
      sscanf(&argv[i][3],"%d",&_nr);
    }
    else if(strncmp(argv[i],"nt:",3)==0){
      sscanf(&argv[i][3],"%d",&_nt);
    } 
    else if(strncmp(argv[i],"tt:",3)==0){
      sscanf(&argv[i][3],"%d:%d",&tt,&t0);//sat
      tl=tt+t0;
    }
    else if(strncmp(argv[i],"dir2:",5)==0){
      sprintf(dir2,"%s",&argv[i][5]);
    }
    else if(strncmp(argv[i],"st:",3)==0 ){
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
      char *p;
      s=0;
      sname[s]=p=&argv[i][3];
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
    else if(strncmp(argv[i],"DISP:",5)==0){
      DISP=&argv[i][5];
      //      sscanf(&argv[i][5],"%d",&DISP);
    }
    else if(strncmp(argv[i],"tx:",3)==0 ){
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
  }

  k2=(_nt+1)*_nr;
 
  char com[551];
  int n;
  if(nst==0){
    for(tx=0;tx<ntx;tx++){
      for(s=0;s<ns;s++){
	sprintf(snametext[nst],"%s-%s",sname[s],text[tx]);
        nst++;
      }
    }
  }
  for(n=0;n<nst;n++){ //  for(tx=0;tx<ntx;tx++){for(s=0;s<ns;s++){
    int i;
    char buff[128];
    char fn[261];
    sprintf(fn,"%s/%s.dat",dir2,snametext[n]);
    FILE *fp1=fopen(fn,"r");
    for(i=0;fgets(buff,128,fp1)!=NULL;i++);{ //
      t0=i;
      tl=t0;
    }
    //  fprintf(stderr,"%d\n",tl);
    fclose(fp1);
    sprintf(com,"mkpoleptv1+ st:%s k:%d N:%d dir:%s dout:%s DISP:%s",snametext[n],k,Np,dir,dout,DISP);
    //    sprintf(com,"mkpoleptv1 sp:%s tx:%s k:%d N:%d dir:%s data:%s ",sname[s],text[tx],k,Np,dir,data);
    sprintf(&com[strlen(com)]," %s tt:%d:%d nt:%d nr:%d",rsa,tt,tl,_nt,_nr);//
    sprintf(&com[strlen(com)]," r_max:%lf > /dev/null",r_max);
    //sprintf(com,"mkpoleptv1 sp:%s tx:%s k:8 N:24 dir:../can2b/tmp rsa:2:0.7:1:20 tt:0:400 n:18 m:2 r_max:2 > /dev/null",sname[s],text[tx]);
    //mkpoleptv1 sp:faf tx:a k:8 N:20 dir:../can2b/tmp rsa:2:0.7:1:20 tt:0:400 n:10 m:2 r_max:2 > /dev/null
    fprintf(stdout,"%s\n",com);
    system(com);
  }
  return 0;
}
