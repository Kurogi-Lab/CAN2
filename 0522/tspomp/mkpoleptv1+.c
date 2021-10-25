#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI  3.141593
#define MAX 256
int main(int argc,char **argv)
{ 
  fprintf(stderr,"******************************************************1\n");
  int i;
  int n,m,K,M,tt,tl,t0;
  double r_max;
  int rs_method=-1,rs_ens=20;
  int *q;
  int N=1;//Number of Units
  int k=63;//Dimension of input vector
  char dir[256];
  char dout[256];
  char *sname;//speaker name,sat
  char *text;//text,sat
  char *snametext;
  char str[MAX];
  char fname[MAX+21];//  char fname[MAX];
  FILE *fp;
  float *sa0;
  float *sa1;
  double *pr;
  double *pt;
  int j,l,x;
  char *DISP="00";
  //  int DISP=0;

  for(i=1;i<argc;i++){
    if(strncmp(argv[i],"N:",2)==0){//
      sscanf(&argv[i][2],"%d",&N);
    }
    else if(strncmp(argv[i],"k:",2)==0){
      sscanf(&argv[i][2],"%d",&k);
    }
   else if(strncmp(argv[i],"r_max:",6)==0){
      sscanf(&argv[i][6],"%lf",&r_max);
    }
    else if(strncmp(argv[i],"nt:",3)==0){
      sscanf(&argv[i][3],"%d",&n);
    }
    else if(strncmp(argv[i],"nr:",3)==0){
      sscanf(&argv[i][3],"%d",&m);
    } 
    else if(strncmp(argv[i],"tt:",3)==0){
      sscanf(&argv[i][3],"%d:%d",&tt,&t0);//sat
      tl=tt+t0;
    }
    else if(strncmp(argv[i],"rsa:",4)==0){
      sscanf(&argv[i][4],"%d:%d",&rs_method,&rs_ens);
    }
    else if(strncmp(argv[i],"dir:",4)==0){
      sprintf(dir,"%s",&argv[i][4]);
    }
    else if(strncmp(argv[i],"dout:",5)==0){
      sprintf(dout,"%s",&argv[i][5]);
    }
    else if(strncmp(argv[i],"st:",3)==0 ){
      snametext=&argv[i][3];
    }
    else if(strncmp(argv[i],"sp:",3)==0 ){
      sname=&argv[i][3];
    }
    else if(strncmp(argv[i],"tx:",3)==0 ){ 
      text=&argv[i][3];
    }
    else if(strncmp(argv[i],"DISP:",5)==0){
      DISP=&argv[i][5];
      //      sscanf(&argv[i][5],"%d",&DISP);
    }
  }

  if(rs_method == 2){
    K = k*N*rs_ens;
  }
  else{
    K=k*N;
  }
  //M = (n+1)*m;
  M = n*m;//9/19 nt*nr;m=nr,n=nt

  sprintf(fname,"%s/%s-k%dN%dt%d-%d-poles0.dat",dir,snametext,k,N,tt,tl);
  //  sprintf(fname,"%s/%s-%s-k%dN%dt%d-%d-poles0.dat",dir,text,sname,k,N,tt,tl);
  //sprintf(fname,"tmp/%s-%s-k%dN%dt%d-%d-poles0.dat",text,sname,k,N,tt,tl);
  printf("#fname=%s\n",fname);

  sa0 = (float *)malloc( K * sizeof(float));
  //if(!sa1){
  // printf("sa1割り当てエラー");
  // exit(1);
  //}
  sa1 = (float *)malloc( K * sizeof(float));
  //if(!sa2){
  // printf("sa2割り当てエラー");
  //exit(1);
  //}
  q = (int *)malloc( M * sizeof(int)); 
  if(!q){
    printf("q malloc error");
    exit(1);
  }

  pr = (double*)malloc((K+1)*sizeof(double));
  if(!pr){
    printf("pr malloc error");
    exit(1);
  }
  pt = (double*)malloc(K*sizeof(double));
  if(!pt){
    printf("pt malloc error");
    exit(1);
  }

  if((fp = fopen(fname,"r")) ==NULL){ 
    printf("error\n");
    exit(1);
  }

  for(i=0;i<=K;i++){
    fgets(str,MAX,fp);
    if(feof(fp))break;
    if(str[0] == '#')continue;
    sscanf(str,"%f%f%lf%lf",&sa0[i],&sa1[i],&pr[i],&pt[i]);
    // fprintf(stderr,"%d %lf %lf\n",K,pr[i],pt[i]);
  }
  
  //fprintf(stderr,"1\n");
  /* ベクトルqを作成します */
  x=0;
  for(i=0;i<n;i++){ //n=nt
    for(j=0;j<m;j++){//m=nr
      q[x]=0;
      for(l=0;l<K;l++){
	if(pr[l] >= r_max*j/m && pr[l] < r_max*(double)(j+1)/(double)m &&
	   pt[l] >= PI*i/n && pt[l] < PI*(double)(i+1)/n  // pt[l] >= PI*i/n && pt[l] < PI*(double)(i+1)/n
	   && pt[l] > 0 //9/20 for neglect θ=0
           && pt[l] <PI
           ){//9/20
	  q[x]++;
	}
	//        if(pt[l]==0) printf("#l%d i%d j%d x%d q%d\n",l,i,j,x,q[x]);
      }
      x++;
    }
  }

//  //θ=πのとき 
//  for(j=0;j<m;j++){
//    q[x] = 0;
//    for(l=0;l<K;l++){
//      if(pr[l] >= r_max/m*j && pr[l] < r_max/m*(j+1) &&
//	 pt[l] == PI ){
//	q[x]++;
//	//fprintf(stderr,"%lf %lf\n",pr[l],pt[l]);
//      }
//    }
//    x++;
//  }
  //9/18
  //free(sa1);
  //free(sa2);
  //free(sa3);
  //free(sa4);
  //free(sa);
  //free(pr);
  //free(pt);
  sprintf(fname,"%s/%s-p.dat",dout,snametext);
  //sprintf(fname,"../datap2/%s-%s-p.dat",sname,text);
  fprintf(stdout,"#saved in %s\n",fname);
  fclose(fp);
  /*出力用にファイルを開く*/
  if((fp=fopen(fname,"w")) == NULL){
    printf("cannt open file:%s\n",fname);
    exit(1);
  }
  FILE *fpq=fopen("tmp/q.dat","w");
  FILE *fpq2=fopen("tmp/q2.dat","w");
  for(i=0;i<M;i++){//  for(i=0;i<M-1;i++){
    fprintf(fp,"%d ",q[i]);
    fprintf(fpq,"%d\n",q[i]);
    fprintf(stderr,"%d ",q[i]);
    if(i%2==0) fprintf(fpq2,"%d %d\n",q[i],q[i+1]);
    //fprintf(stderr,"%d\n",q[i]);
  }
  for(i=0;i<M;i+=2){//  for(i=0;i<M-1;i++){
    fprintf(fpq2,"%d %d\n",q[i],q[i+1]);
  }
  fprintf(fp,"\n"); //  fprintf(fp,"%d\n",q[i]); //replaced 20180911 
  fclose(fp);
  fclose(fpq);
  fclose(fpq2);
  fprintf(stderr,"%d\n",q[i]);
  fprintf(stderr,"******************************************************\n");
  if(DISP[0]=='1')
  {
    char *fb2="tmp/q2";
    fp=fopen("tmp/q2.plt","w");
    fprintf(fp,"set style fill solid border lc rgb \"black\"\n");
    fprintf(fp,"set boxwidth 1\n");
    fprintf(fp,"set term postscript eps enhanced color; set output \"%s.eps\"\n",fb2);
    fprintf(fp,"plot [0:36][0:300] \"%s.dat\" using ($0*2+0.5):1 with boxes lw 2 lt 1 lc rgb \"light-green\", \\\n",fb2);
    fprintf(fp,"\"%s.dat\" using ($0*2+1.5):2 with boxes lw 2 lt 1 lc rgb \"light-red\"\n",fb2);
    fprintf(fp,"set term tgif; set output \"%s.obj\";replot\n",fb2);
    fprintf(fp,"quit\n");
    fclose(fp);
    char cmd[128];
    sprintf(cmd,"gnuplot tmp/q2.plt;wait");
    system(cmd);
    if(strlen(DISP)<=1 || DISP[1]!='0'){
      sprintf(cmd,"gv tmp/q2.eps&");
      system(cmd);
    }
//    fprintf(fp,"set title \"%s\"\n",snametext);
//    fprintf(fp,"set term postscript eps enhanced color; set output \"tmp/q.eps\";\n");
//    fprintf(fp,"plot [0:36][0:600] \"tmp/q.dat\" using 0:1 w l\n");
//    fprintf(fp,"set term tgif; set output \"tmp/q.obj\";replot\n");
//    fprintf(fp,"quit\n");
//    fclose(fp);
//    char cmd[128];
//    sprintf(cmd,"gnuplot tmp/q.plt;wait;gv tmp/q.eps&");
//    system(cmd);
  }


 return 0;

}

