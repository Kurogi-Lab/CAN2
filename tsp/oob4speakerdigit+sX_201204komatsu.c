/////////////////
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_nSnD 100//sat //7*14=98
int nS=7;//number of speakers
int nD=10;//number of texts
int nL=10;//number of text data for a text
int m_sd1(int s,int d){return(s);}
int m_sd2(int s,int d){return(d);}
int m_sd3(int s,int d){return(s*nD+d);}
int sX=-1; //speaker exclude
int mX1(int m){ return((m==sX)?1:0);}
int mX2(int m){ return(0);}
int mX3(int m){ return(((m/nD)==sX)?1:0);}


int main(int argc,char **argv)
{
  int i;//,n0=1;
  int N=1;//Number of Units
  int k=63;//Dimension of input vector
  char mbas[20];//="2:20:0.7:1";
  char *_mbas[4];
  int _b;
  //  int _m=2,_b=20,_s=1;
  //  double _a=0.7;
  char dir[256];
  //////////////////////////////////////////
  char *sname[max_nSnD];//speaker name,sat
  char *text[max_nSnD];//text,sat
  int s,tx,txi;//variables for s:sameple, tx:text//sat
  //sprintf(dir,"../satovowels/512");//sat
  //  sprintf(rsa,"2:0.7:1:20");//
  //*********蠑墓焚隱ｭ縺ｿ霎ｼ縺ｿ***************************
  char cmd0[512]={0,};
  char *sd=NULL;//sd=1 for speaker, 2 for digit 3 for speakerdigit
  int nsd,isd;
  int _sm=-1,_dm=-1,_nsdm=-1;
  int (*m_sd)();
  int (*mX)();
  int m,nM,m1,m2;
  char *IDR="";//ID for discriminate the result
  for(i=0;i<argc;i++) sprintf(&cmd0[strlen(cmd0)],"%s ", argv[i]);
  for(i=1;i<argc;i++){
    if(strncmp(argv[i],"N:",2)==0){//
      sscanf(&argv[i][2],"%d",&N);
    }
    else if(strncmp(argv[i],"sX:",3)==0){
      sscanf(&argv[i][3],"%d",&sX);
    }
    else if(strncmp(argv[i],"k:",2)==0){
      sscanf(&argv[i][2],"%d",&k);
    }
    else if(strncmp(argv[i],"IDR:",4)==0){
      IDR=&argv[i][4];
    }
    else if(strncmp(argv[i],"s:",2)==0){
      nsd=1;isd=i;
      sd="s";
      m_sd=m_sd1;
      mX=mX1;
      nM=nS;//speaker
      sscanf(&argv[i][2],"%d",&_sm);
      if(_sm>=0){m1=_sm;m2=m1+1;}
      else{m1=0;m2=nM;}
    }
    else if(strncmp(argv[i],"d:",2)==0){
      nsd=2;isd=i;
      sd="d";
      m_sd=m_sd2;
      mX=mX2;
      nM=nD;//digit
      sscanf(&argv[i][2],"%d",&_dm);
      if(_dm>=0){m1=_dm;m2=m1+1;}
      else{m1=0;m2=nM;}
    }
    else if(strncmp(argv[i],"sd:",3)==0){
      nsd=3;isd=i;
      sd="sd";
      m_sd=m_sd3;
      mX=mX3;
      nM=nD*nS;//speakerdigit
      sscanf(&argv[i][3],"%d:%d",&_sm,&_dm);
      if(_sm>=0 && _dm>=0){m1=_sm*nD+_dm;m2=m1+1;}
      else{m1=0;m2=nM;}
    }
    else if(strncmp(argv[i],"mbas:",5)==0){
      sprintf(mbas,"%s",&argv[i][5]);
      char *p=&argv[i][5];
      _mbas[0]=p;
      int i;
      for(i=1;i<4;i++){
	for(p++;;p++) if(*p==':') break;
	*p++=0;
	_mbas[i]=p;
      }
      sscanf(_mbas[1],"%d",&_b);//change 20140322      sscanf(_mbas[2],"%d",&_b);
    }
    else if(strncmp(argv[i],"dir:",4)==0){
      sprintf(dir,"%s",&argv[i][4]);
    }
    else if(strncmp(argv[i],"nL:",3)==0){
      sscanf(&argv[i][3],"%d",&nL);
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
      nS=s+1;
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
      nD=tx+1;
    }
  }
  fprintf(stderr,"#nD=%d,nS=%d\n",nD,nS);
  //*******************************************************
//  if(nsd==1){
//    m_sd=m_sd1;
//    nM=nS;//speaker
//  }
//  else if(nsd==2){
//    m_sd=m_sd2;
//    nM=nD;//digit
//  }
//  else if(nsd==3){
//    m_sd=m_sd3;
//    nM=nS*nD;//speakerdigit
//  }
//  if(_nsdm<1){
//    m1=0;m2=nM;
//  }
//  else if(_nsdm==1){//s or d
//    if(_sm>=0){m1=_sm;m2=m1+1;}
//    else{m1=0;m2=nM;}
//  }
//  else if(_nsdm==2){
//    if(_sm>=0 && _dm>=0){
//      m1=_sm*nD+_dm;
//      m2=m1+1;
//    }
//  }
  char fnw[291];
  sprintf(fnw,"%s/oob4%sN%dmbas%ssX%d%s.y",dir,argv[isd],N,mbas,sX,IDR);
  FILE *fpw=fopen(fnw,"w");
  char fns[295];sprintf(fns,"%s/oob4%sN%dmbas%ssX%d%s.ystat",dir,argv[isd],N,mbas,sX,IDR);
  FILE *fps=fopen(fns,"w");
  fprintf(fpw,"#%s\n",cmd0);fflush(fpw);
  fprintf(fps,"#%s\n",cmd0);fflush(fps);
  int sm,txm;
  ////////////////////////////////////////
  char fntrain[80];
  char fntest[80];
  //  char *fn;
  char com[512];

#define buffsize 256
  char buff[buffsize];
  double TP,TN,FP,FN;
  double TPX,TNX,FPX,FNX;
  double _y,_yp;int _n;
  int nr;
#define ZERO (1e-20)
  for(m=m1;m<m2;m++){
    //  for(m=0;m<nM;m++){
    //  for(sm=0;sm<ns;sm++){for(txm=0;txm<nD;txm++){
    //Out-of-bag testing of CAN2^{sm,txm} which learns all X(s,tx,txi) 
    if(mX(m)) continue;
    TP=TN=FP=FN=0;
    TPX=TNX=FPX=FNX=0;
    sprintf(com,"make data-clean");system(com);
    sprintf(fntrain,"./train_");
    sprintf(com,"cat /dev/null > %sx.dat",fntrain);system(com);//clear data in files
    sprintf(com,"cat /dev/null > %sy.dat",fntrain);system(com);
    sprintf(fntest,"./test_");
    for(s=0;s<nS;s++){
      fprintf(stderr,".");fflush(stderr);
      if(s==sX){
        //        sprintf(fntest,"./test_");
        sprintf(com,"cat /dev/null > %sx.dat",fntest);
        system(com);
        sprintf(com,"cat /dev/null > %sy.dat",fntest);
        system(com);
        for(tx=0;tx<nD;tx++){//tx-th test digit
          for(txi=0;txi<nL;txi++){//txi-th sample
            //	    sprintf(fntest,"%s/test_",dir);//20140320 remove????
            sprintf(com,"col=`cat %s/%s-%s%d-p.dat`;echo $col >> %sx.dat",dir,sname[sX],text[tx],txi+1,fntest);//ポールファイルに改行が有ってもなくてもOK
            //	    sprintf(com,"cat %s/%s-%s%d-p.dat >> %sx.dat",dir,sname[sX],text[tx],txi+1,fntest);//１行のとき
            system(com);
            if(m==(*m_sd)(s,tx)){
              sprintf(com,"echo 1 >> %sy.dat",fntest);//CAN2^{sm} produces y=1 for s2=sm
            }
            else sprintf(com,"echo -1 >> %sy.dat",fntest);
            system(com);
          }
        }
        sprintf(com,"concat_io1 %sx.dat %sy.dat > %sxy.dat 2>/dev/null",fntest,fntest,fntest);system(com);
      }//if(s==sX){
      else{//s!=sX
        for(tx=0;tx<nD;tx++){//test of tx-th multi-step identification/recognition
          for(txi=0;txi<nL;txi++){//test for txi-th indexed tx-th text(digit)
            sprintf(com,"col=`cat %s/%s-%s%d-p.dat`;echo $col >> %sx.dat",dir,sname[s],text[tx],txi+1,fntrain);//ポールファイルに改行が有ってもなくてもOK
            //            sprintf(com,"cat %s/%s-%s%d-p.dat >> %sx.dat",dir,sname[s],text[tx],txi+1,fntrain);//by Mineishi
            system(com);
            if(m==(*m_sd)(s,tx)) sprintf(com,"echo 1 >> %sy.dat",fntrain);//CAN2^{sm} produces y=1 for s2=sm
            else sprintf(com,"echo -1 >> %sy.dat",fntrain);
            system(com);
            //	  fprintf(stderr,"s,tx,txi=%d %d %d\n",s,tx,txi);
          }//for(txi=0;txi<nL;txi++){
        }//for(tx=0;tx<nD;tx++){
      }
    }//for(s=0;s<nS;s++){
    sprintf(com,"paste %sx.dat %sy.dat > %sxy.dat 2>/dev/null",fntrain,fntrain,fntrain);system(com);
    //    sprintf(com,"concat_io1 %sx.dat %sy.dat > %sxy.dat 2>/dev/null",fntrain,fntrain,fntrain);system(com);
    sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null nop:1",fntrain,mbas,N,N,k);
    //    sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null nop:1 > /dev/null",fntrain,mbas,N,N,k);
    fprintf(stderr,"1Executing '%s'\n",com); system(com);
    sprintf(com,"cp predict+.dat predict+0.dat"); system(com);
    ////
    if(sX>=0){//bag using oob-result ???
      //?? necessary??
      int j;//20141119 activate from here
      for(j=0;j<_b;j++){//use predict?
	sprintf(com,"mv result-ensrs/tmp/train_xy+null+m%sa%sb0:0s%sj%dk%dN%dpred.dat result-ensrs/tmp/train_xy+test_xy+m%sa%sb0:0s%sj%dk%dN%dpred.dat",_mbas[0],_mbas[2],_mbas[3],j,k,N,_mbas[0],_mbas[2],_mbas[3],j,k,N);
	//	sprintf(com,"mv result-ensrs/tmp/train_xy+null+m%da%gb0:0s%dj%dk%dN%dpred.dat result-ensrs/tmp/train_xy+test_xy+m%da%gb0:0s%dj%dk%dN%dpred.dat",_m,_a,_s,j,k,N,_m,_a,_s,j,k,N);
	fprintf(stderr,"2Executing '%s'\n",com); system(com);
      }
      //      sprintf(com,"rm result-ensrs/tmp/*.dat");system(com); //use nets
      //      sprintf(com,"rm -rf result-ensrs/tmp");system(com); //use nets
      //      sprintf(com,"rm -rf result-ensrs");system(com); //dont use net and tmp
      sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:%sxy.dat > /dev/null",fntrain,mbas,N,N,k,fntest);
      //20141119 activate to here
      fprintf(stderr,"3Executing '%s'\n",com); system(com);
      //      sprintf(&com[strlen(com)],"y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null > /dev/null");//
    }
  
    FILE *fp0=fopen("predict+0.dat","r");//prediction of traindata by oob
    FILE *fp1=fopen("predict+.dat","r");//prediction of test(sX) data by bag
    FILE *fp;
    for(s=0;s<nS;s++){
      if(s==sX) fp=fp1; else fp=fp0;
      for(tx=0;tx<nD;tx++){//test of tx-th multi-step identification/recognition
        for(txi=0;txi<nL;txi++){//test for txi-th indexed tx-th text(digit)
          fgets(buff,buffsize,fp);
          if(feof(fp)) break;//not necessary
          nr=sscanf(buff,"%lf%d%lf",&_yp,&_n,&_y);
          if(nr<3) break;//not necessary
          fprintf(fpw,"%g ",_yp);//Yp[m][s][t][i] //
          if(s==sX){//20131209     //	  if(s!=sX){//20131209,20141118
            if(_yp>=0){
              if(_y>0){
                TPX++;
                fprintf(stdout,"#check: TP%g yp[%d %d %d]=%g\n",TPX,s,tx,txi,_yp);
              }
              else FPX++;
            }
            else if(_y>0) FNX++;
            else{
              TNX++;
              fprintf(stdout,"#check: TN%g yp[%d %d %d]=%g\n",TNX,s,tx,txi,_yp);
            }
          }
          if(_yp>=0){if(_y>0) TP++; else FP++;}
          else if(_y>0) FN++; else TN++;
          if(m==(*m_sd)(s,tx) && _y<0) fprintf(stderr,"#Check Hen!!!!!(s,tx)=(%d,%d)",s,tx);
        }//end of for(txi=0;txi<nL;txi++){
      }//end of for(tx=0;tx<nD;tx++){//test-text 
//      {
//        double n=TP+TN+FP+FN;double TPFN=TP+FN,FPTN=FP+TN,ER=(FP+FN)/(n+ZERO);;
//        TP/=(TPFN+ZERO);FN/=(TPFN+ZERO);FP/=(FPTN+ZERO);TN/=(FPTN+ZERO);ER=(FP+FN)/(n+ZERO);
//        double nX=TPX+TNX+FPX+FNX, TPFNX=TPX+FNX,FPTNX=FPX+TNX,ERX=(FPX+FNX)/(nX+ZERO);;
//        TPX/=(TPFNX+ZERO);FNX/=(TPFNX+ZERO);FPX/=(FPTNX+ZERO);TNX/=(FPTNX+ZERO);ERX=(FPX+FNX)/(nX+ZERO);
//        fprintf(stderr,"#%.5f %.5f %.5f %.5f %.5f %.1f %d %d #TP,TN,FP,FN,ERR,n,s,sm\n",TP,TN,FP,FN,ER,n,s,sm);
//        fprintf(stderr,"#%.5f %.5f %.5f %.5f %.5f %.1f %d %d #TP,TN,FP,FN,ERR,n,s,sm\n",TPX,TNX,FPX,FNX,ERX,nX,s,sm);
//      }
    }//end of for(s=0;s<nS;s++){//test-speaker
    fclose(fp);
    //    fprintf(fpw,"#%d sm\n",sm);
    {
      int n=TP+TN+FP+FN;double TPFN=TP+FN,FPTN=FP+TN,ER;
      TP/=TPFN;FN/=(TPFN+ZERO);FP/=(FPTN+ZERO);TN/=(FPTN+ZERO);ER=(FP+FN)/n;
      double nX=TPX+TNX+FPX+FNX, TPFNX=TPX+FNX,FPTNX=FPX+TNX,ERX;
      TPX/=(TPFNX+ZERO);FNX/=(TPFNX+ZERO);FPX/=(FPTNX+ZERO);TNX/=(FPTNX+ZERO);ERX=(FPX+FNX)/(nX+ZERO);
      double RC=TP/(TP+FP+ZERO),PR=TP/(TP+FN+ZERO); //recall and precesion
      double F=2.*RC*PR/(RC+PR+ZERO);
      //      fprintf(fpw,  "#%.5f %.5f %.5f %.5f %.5f %.5f %d #TP,TN,FP,FN,ERR,n,sm\n",TP,TN,FP,FN,ER,n,sm);
      //      fprintf(fpw,"#sm%d\n",sm);
      if(nsd==1){
        sm=m;
        sprintf(com,"%.3f %.3f %.3f %.3f %.3e %.3f %.3f %.3f %d %d #TP,TN,FP,FN,ERR,RC,PR,F,n,sm%d",TP,TN,FP,FN,ER,RC,PR,F,n,sm,sm);
      }
      else if(nsd==2){
        txm=m;
        sprintf(com,"%.3f %.3f %.3f %.3f %.3e %d %d #TP,TN,FP,FN,ERR,n,txm%d",TP,TN,FP,FN,ER,n,txm,txm);
      }
      else if(nsd==3){
        sm=m/nD;txm=m%nD;
        sprintf(com,"%.3f %.3f %.3f %.3f %.3e %d %d %d #TP,TN,FP,FN,ERR,n,sm%d txm%d",TP,TN,FP,FN,ER,n,sm,txm,sm,txm);
      }
      
      if(sX>=0) sprintf(&com[strlen(com)], " sX%d(TP%.3f TN%.3f ER%.3e n%.0f)",sX,TPX,TNX,ERX,nX);
      fprintf(fpw,"%s\n",com);
      fprintf(fps,"%s\n",com);fflush(fps);
      fprintf(stdout,"%s for check.\n",com);
    }
  }//for(m=m1;m<m2;m++){
  fclose(fpw);
  fclose(fps);
  fprintf(stderr,"#result in '%s' and '%s'.\n",fnw,fns);
  return 0;
}
