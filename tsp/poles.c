#include "my_plinn.h"

////////////////////////////
#define ZERO 1.0e-10
#define L_MODE 1
//#define E_CHECK
//#define alpha1 1.2
#define alpha1 1.1
#define alphaT1 5.0
//#define alphaT1 4.0
//#define alphaT1 8.0
//#define alphaT1 9.0
//#define alphaT1 15.0
//#define alphaT1 20.0 //good for 02train
//#define alphaT1 40.0
//#define alphaT1 2.0

#include "randoms.h"

#define LA(x,y1,x1,y2,x2) ((y1)+((x)-(x1))*((y2)-(y1))/((x2)-(x1))) //Linear Approximation

void poles_of_M_shrink(NET *net)
{
  int i,n,j,nn;
  FILE *fp=fopen("./tmp/poles.dat","w");
  FILE *fp0=fopen("./tmp/poles0.dat","w");//original poles, a pole in a separate line
  FILE *fp2=fopen("./tmp/poles2.dat","w");//shrinked LPC poles in each CAN2, a pole in a separate line
  FILE *fp3=fopen("./tmp/poles3.dat","w");//shrinked LSP poles, a pole in a separate line
  FILE *fp4=fopen("./tmp/poles4.dat","w");//original poles, poles in each line
  FILE *fp5=fopen("tmp/poles5.dat","w");//shrinked poles, poles in each line
  FILE *fp6=fopen("./tmp/poles6.dat","w");//shrinced LSP
  FILE *fp7=fopen("./tmp/M4.dat","w");//original LPC (Associative Matrix), LPCs in each line
  int k=net[0].k;
  int k1=k+1;
  int nEns=net[0].nEns;
  int maxk=2*k1;
  double *vn=(double*)malloc(sizeof(double)*(nEns+1));//number of data in Vi
  double *An=(double*)malloc(sizeof(double)*(k1)*(nEns+1));//Coefficients of LPC
  double *zn=(double*)malloc(sizeof(double)*maxk*(nEns+1));//for LSP of PQ
  double *theta_zn=(double*)malloc(sizeof(double)*maxk*(nEns+1));//for LPC
  double *rho_zn=(double*)malloc(sizeof(double)*maxk*(nEns+1));//for LPC
  int *i_zn=(int*)malloc(sizeof(int)*maxk*(nEns+1));//for LPC
  int *c_zn=(int*)malloc(sizeof(int)*maxk*(nEns+1));//for LPC
  double *v_zn=(double*)malloc(sizeof(double)*maxk);//for LSP of PQ
  gsl_poly_complex_workspace *wk2=gsl_poly_complex_workspace_alloc (2*k1+1);//for LSP
  gsl_poly_complex_workspace *wk= gsl_poly_complex_workspace_alloc (k+1);//for poles
  {
    //poles of M[nn]
    //each pole zn[nn]
    double *A=(double*)malloc(sizeof(double)*(k1));//for LPC
    double *z=(double*)malloc(sizeof(double)*maxk);//for LSP of PQ
    double *P=(double*)malloc(sizeof(double)*(k1+1));//for LSP
    double *Q=(double*)malloc(sizeof(double)*(k1+1));//for LSP
    double *PQ=(double*)malloc(sizeof(double)*(2*k1+1));//for LSP
    int sign;

    A[k]=-1.;
#define SELECTMETHOD 2
#if SELECTMETHOD == 2
    double *v_backup=(double*)malloc(sizeof(double)*nEns*net[0].n_cells);//number of data in Vi
    for(nn=0;nn<nEns;nn++) for(n=0;n<net[nn].n_cells;n++) v_backup[n*nEns+nn]=net[nn].cell[n].v;
    for(nn=0;nn<nEns;nn++){
      vn[nn]=0;for(j=0;j<=k;j++) An[nn*k1+j]=0;
      for(n=0;n<net[nn].n_cells;n++){
	//poles of M
	for(j=0;j<k;j++) A[j]=net[nn].cell[n].am.M[0][k-1-j];
	gsl_poly_complex_solve (A, k+1, wk, z);
	for(j=0;j<k;j++){
	  fprintf (fp0,"%+e %+e %+e %+e %+e %d %d %d #Re(z) Im(z) |z| Arg(z) v i k net\n", 
		   z[2*j], z[2*j+1],sqrt(z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1]),atan2(z[2*j+1],z[2*j]),net[nn].cell[n].v,j,k,nn);
	}
	//	fprintf(stderr,"check v=%.0f=%f*%d\n",net[nn].cell[n].v*net[nn].vmax,net[nn].cell[n].v,net[nn].vmax);
	//	if(net[nn].cell[n].v*net[nn].vmax > k ){
	if(net[nn].cell[n].v>0){
	  int NG=0;
	  for(j=0;j<k;j++){
	    double rz2=z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1];
	    if(rz2>1.0 || rz2<0.35) {NG=1; break;}
	    //	    if(rz2>1.0) {NG=1; break;}
	    //	    if(rz2>1.0 || rz2<0.3) {NG=1; break;}
	    //	    if(rz2<0.3) {NG=1; break;}//OK but few features?
	  }
	  if(net[nn].n_cells !=1 && NG==1) {
	    net[nn].cell[n].v=2;//v>1 for excluding calculation of MSE. see exec_ssp_test_ensemble in sim.c 
	    //	    fprintf(stdout,"check: net[%d].cell[%d].v=2 is not used for evaluating MSE.\n",nn,n);
	  }
	  //	    if(net[nn].n_cells !=1 && NG==1) net[nn].cell[n].v=-1;//v<0 for neglecting this unit
	  //	  if(net[nn].n_cells==1 || NG==0){
	  if(1==1){
	    for(j=0;j<=k;j++) An[nn  *k1+j]+=A[j]*net[nn].cell[n].v;
	    vn[nn]  +=net[nn].cell[n].v;
	    ///poles4.dat LPC
	    for(j=0;j<k;j++) fprintf(fp4,"%e %e ",z[2*j],z[2*j+1]);
	    //	    for(j=0;j<k;j++) fprintf(fp4,"%e %e ",log(z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1]),atan2(z[2*j+1],z[2*j]));
	    //	    for(j=0;j<k;j++) fprintf(fp4,"%e %e ",z[2*j],z[2*j+1]);
	    //	    for(j=0;j<k;j++) fprintf(fp4,"%e %e ",0.5*log(z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1]),log(0.01+fabs(atan2(z[2*j+1],z[2*j]))));
	    fprintf(fp4,"%e\n",net[nn].cell[n].v);

	    for(j=0;j<k;j++) fprintf(fp7,"%e ",net[nn].cell[n].am.M[0][j]);
	    fprintf(fp7,"%e\n",net[nn].cell[n].v);
	    //poles6.dat LSP
	    sign=1;P[k1]=-1.;P[0]=-sign;
	    for(j=0;j<k;j++) P[j+1]=A[j]+sign*A[k-1-j];
	    sign=-1;Q[k1]=-1.;Q[0]=-sign;
	    for(j=0;j<k;j++) Q[j+1]=A[j]+sign*A[k-1-j];
	    for(j=0;j<=2*k1;j++) PQ[j]=0;
	    for(j=0;j<=k1;j++){
	      for(i=0;i<=k1;i++){
		PQ[j+i] +=P[i]*Q[j];
	      }
	    }
	    gsl_poly_complex_solve (PQ, 2*k1+1, wk2, zn);
	    for(j=0;j<2*k1;j++){
	      fprintf (fp6,"%e %e ", zn[2*j], zn[2*j+1]);
	    }
	    fprintf (fp6,"%e \n",net[nn].cell[n].v);
	  }
	}
      }

      gsl_poly_complex_solve (&An[nn*k1], k+1, wk, &zn[nn*maxk]);
      net_save(net,"tmp/shrink2.net");
    }
    free(PQ);
    free(P);
    free(Q);
//#elif SELECTMETHOD == 1
//    for(nn=0;nn<nEns;nn++){
//      vn[nn]=0;//for(j=0;j<=k;j++) An[nn*k1+j]=0;
//      int nM0max=0,nM0min=0;
//      for(n=0;n<net[nn].n_cells;n++){	//save the original poles of M
//	for(j=0;j<k;j++) A[j]=net[nn].cell[n].am.M[0][k-1-j];
//	gsl_poly_complex_solve (A, k+1, wk, z);
//	for(j=0;j<k;j++){
//	  fprintf (fp0,"%+e %+e %+e %+e %+e %d %d %d #Re(z) Im(z) |z| Arg(z) v i k net\n", 
//		   z[2*j], z[2*j+1],sqrt(z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1]),atan2(z[2*j+1],z[2*j]),net[nn].cell[n].v,j,k,nn);
//	}
//      }
//      for(n=0;n<net[nn].n_cells;n++){//search the 
//	if(net[nn].cell[n].v*net[nn].vmax > k ){
//	  if(fabs(net[nn].cell[n].am.M[0][k])<fabs(net[nn].cell[nM0min].am.M[0][k])) nM0min=n;
//	  if(fabs(net[nn].cell[n].am.M[0][k])>fabs(net[nn].cell[nM0max].am.M[0][k])) nM0max=n;
//	}
//      }
//      fprintf(stderr,"check nM0max=%f, v=%.0f=(%e)*(%d)\n",net[nn].cell[nM0max].am.M[0][k],net[nn].cell[nM0max].v*net[nn].vmax,net[nn].cell[nM0max].v,net[nn].vmax);
//      fprintf(stderr,"check nM0min=%f, v=%.0f=(%e)*(%d)\n",net[nn].cell[nM0min].am.M[0][k],net[nn].cell[nM0min].v*net[nn].vmax,net[nn].cell[nM0min].v,net[nn].vmax);
//      for(j=0;j<k;j++) A[j]=net[nn].cell[nM0max].am.M[0][k-1-j];//use nM0max for robustness to noise?
//      //      for(j=0;j<k;j++) A[j]=net[nn].cell[nM0min].am.M[0][k-1-j];//use nM0max for robustness to noise?
//      vn[nn]  ++;
//      for(j=0;j<=k;j++) An[nn  *k1+j]+=A[j];
//      gsl_poly_complex_solve (&An[nn*k1], k+1, wk, &zn[nn*maxk]);
////#ifdef NEWSELECTMETHOD
////      {
////	FILE *fp=fopen("tmp/M1.dat","w");
////	for(j=0;j<k-1;j++) fprintf(fp,"%e\n",net[nn].cell[nM0max].am.M[0][j]);
////	//	for(j=0;j<k-1;j++) fprintf(fp,"%e\n",net[nn].cell[nM0min].am.M[0][j]);
////	fclose(fp);
////      }
////#endif
//    }
//#eif SELECTMETHOD == 0 //original
//    //    gsl_poly_complex_workspace_free(wk2);
//    for(nn=0;nn<nEns;nn++) for(n=0;n<net[nn].n_cells;n++) net[nn].cell[n].v=v_backup[n*nEns+nn];
//    for(nn=0;nn<nEns;nn++){
//      vn[nn]=0;for(j=0;j<=k;j++) An[nn*k1+j]=0;
//      //      if(nn==3){
//      //	fprintf(stderr,"check\n");
//      //      }
//      for(n=0;n<net[nn].n_cells;n++){
//	//poles of M
//	if(net[nn].cell[n].v>0){
//	  for(j=0;j<k;j++) A[j]=net[nn].cell[n].am.M[0][k-1-j];
//	  gsl_poly_complex_solve (A, k+1, wk, z);
//	  for(j=0;j<k;j++){
//	    fprintf (fp0,"%+e %+e %+e %+e %+e %d %d %d #Re(z) Im(z) |z| Arg(z) v i k net\n", 
//		     z[2*j], z[2*j+1],sqrt(z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1]),atan2(z[2*j+1],z[2*j]),net[nn].cell[n].v,j,k,nn);
//	    fprintf(fp4,"%e %e ",z[2*j],z[2*j+1]);
//	  }
//	  fprintf(fp4,"\n");
//	  {
//	    int NG=0;
//	    for(j=0;j<k;j++){
//	      //	    if(fabs(net[nn].cell[n].am.M[0][k])>1e-5) {NG=1; break;}//constant term 
//	      double rz2=z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1];
//	      //	    if(rz2>=1 || rz2<0.5) {NG=1; break;  }
//	      //	  if(rz2<0.5) {NG=1; break;}
//	      if(rz2>1.01) {NG=1; break;}
//	      //	    if(fabs(z[2*j+1])<ZERO) {NG=1; break;}
//	    }
//	    //	  if(nEns==1 || NG==0){
//	    if(net[nn].n_cells==1 || NG==0){
//	      //	  if(1==1 || nEns==1 || NG==0){
//	      //	  if(nEns==1 || NG==0){
//	      //	  if(1==1 || nEns==1 || NG==0){
//	      for(j=0;j<=k;j++){
//		//	      An[nn  *k1+j]+=A[j]*net[nn].cell[n].E;
//		An[nn  *k1+j]+=A[j]*net[nn].cell[n].v;
//	      }
//	      //	    vn[nn]  +=net[nn].cell[n].E;
//	      vn[nn]  +=net[nn].cell[n].v;
//	    }
//	  }
//	}
//      }
//      //      if(fabs(An[nn*k1])<ZERO){
//      //	fprintf(stderr,"Error nn=%d\n",nn);
//      //      }
//      gsl_poly_complex_solve (&An[nn*k1], k+1, wk, &zn[nn*maxk]);
//    }
#endif
    fclose(fp0);
    //////////////////////////////
    //mean poles zn[nEns]
    vn[nEns]=0;for(j=0;j<=k;j++) An[nEns*k1+j]=0;// mean An
    for(nn=0;nn<nEns;nn++){
      for(j=0;j<k1;j++) An[nEns*k1+j] += An[nn*k1+j];
      vn[nEns]+=vn[nn];
    }
    for(nn=0;nn<=nEns;nn++){for(j=0;j<k1;j++) An[nn*k1+j]/=vn[nn];}
    //    M0mean/=vn[nEns];
    gsl_poly_complex_solve (&An[nEns*k1], k+1, wk, &zn[nEns*maxk]);//poles of mean An
    //    gsl_poly_complex_workspace_free (wk);
    
    //order w.r.t. rho and angle
    for(nn=0;nn<=nEns;nn++){
      double *znn=&zn[nn*maxk];
      double *rhon=&rho_zn[nn*maxk];
      double *thetan=&theta_zn[nn*maxk];
      int *in=&i_zn[nn*maxk];
      int itmp;
      for(j=0;j<k;j++){
	rhon[j]=sqrt(square(znn[2*j])+square(znn[2*j+1]));
	//	thetan[j]=atan2(znn[2*j+1],znn[2*j]);
	//	thetan[j]=fabs(atan2(znn[2*j+1],znn[2*j]));
	thetan[j]=(atan2(znn[2*j+1],znn[2*j]));
      }
      for(j=0;j<k;j++) in[j]=j;
      for(j=0;j<k-1;j++){
      	for(i=j+1;i<k;i++){
      	  if(thetan[in[j]]>thetan[in[i]] || //sort from smallest theta
      	     (fabs(thetan[in[j]]-thetan[in[i]])<ZERO && rhon[in[j]]> rhon[in[i]])){//sort from smallest rho
      	    itmp=in[j];
      	    in[j]=in[i];
      	    in[i]=itmp;
      	  }
      	}
      }
    }
    //nearest poles
    //    double *thetaEns=&theta_zn[nEns*k];
    double *znEns=&zn[nEns*maxk];
    double dd,ddmin;
    int ii,jj;
    for(nn=0;nn<=nEns;nn++){//search nearest poles
      double *znn=&zn[nn*maxk];
      for(ii=0;ii<k;ii++){
	c_zn[nn*maxk+ii]=-1;
	i=i_zn[nEns*maxk+ii];
	ddmin=1e20;
	for(j=0;j<k;j++){
	  dd=square(znn[2*j]-znEns[2*i])+square(znn[2*j+1]-znEns[2*i+1]);
	  if(ddmin>dd){
	    ddmin=dd;
	    c_zn[nn*maxk+ii]=j;
	  }
	}
      }
    }
    
    for(ii=0;ii<k;ii++){
      v_zn[ii]=0;
      i=i_zn[nEns*maxk+ii];
      for(nn=0;nn<nEns;nn++){//mean of poles
	double *znn=&zn[nn*maxk];
	j=c_zn[nn*maxk+ii];
	dd=square(znn[2*j]-znEns[2*i])+square(znn[2*j+1]-znEns[2*i+1]);
	v_zn[ii]+=(dd*dd);
      }
      v_zn[ii]/=nEns;//mean distance
    }
    
    for(nn=0;nn<nEns;nn++){
      for(j=0;j<k;j++){
	ii=-1;for(i=0;i<k;i++) if(j==c_zn[nn*maxk+i]) {ii=i;break;}
	jj=-1;for(i=0;i<k;i++) if(j==i_zn[nn*maxk+i]) {jj=i;break;}
	fprintf (fp,"%+e %+e %+e %+e %e %d %d %d %d #Re(z) Im(z) |z| Arg(z) v i c j nn\n", 
		 zn[nn*maxk+2*j],zn[nn*maxk+2*j+1],rho_zn[nn*maxk+j],theta_zn[nn*maxk+j],v_zn[ii],jj,ii,j,nn);
      }
    }

//    {
//      FILE *fp4m=fopen("./tmp/poles4m.dat","w");//original poles, poles in each line
//      for(nn=0;nn<=nEns;nn++){
//	double *znn=&zn[nn*maxk];
//	for(ii=0;ii<k;ii++){
//	  j=c_zn[nn*maxk+ii];
//	  fprintf (fp4m,"%g %g ", znn[2*j], znn[2*j+1]);
//	}
//	fprintf(fp4m,"%g\n",1.0);
//      }
//      fclose(fp4m);
//    }

    {
      for(nn=0;nn<=nEns;nn++){
	double *znn=&zn[nn*maxk];
	for(ii=0;ii<k;ii++){
	  j=c_zn[nn*maxk+ii];
	  fprintf (fp2,"%+e %+e %e %d ", znn[2*j], znn[2*j+1],sqrt(v_zn[ii]),ii);
	}
	fprintf (fp2,"%d \n",nn);
      }
    }
//    {
//      FILE *fp=fopen("tmp/poles4.dat","w");
//      for(nn=0;nn<nEns;nn++){
//	double *znn=&zn[nn*maxk];
//	for(j=0;j<k;j++){
//	  fprintf (fp,"%+e %+e ", znn[2*j], znn[2*j+1]);
//	}
//	fprintf (fp,"\n");
//      }
//      fclose(fp);
//    }
    {
      nn=nEns;
      {
	double *znn=&zn[nn*maxk];
	for(j=0;j<k;j++){
	  fprintf (fp5,"%e %e ", znn[2*j], znn[2*j+1]);
	}
	//	fprintf(fp5,"%e\n",net[nn].cell[n].v);
	fprintf(fp5,"%e\n",1.0);
      }
      fclose(fp5);
    }

    {//remove poles with only real part
      FLOAT *M0=(FLOAT*)malloc(sizeof(double)*k1);
      FLOAT *M1=(FLOAT*)malloc(sizeof(double)*k1);
      M1[0]=1;for(i=1;i<k1;i++) M1[i]=0;
      for(j=0;j<k;j++){
	for(i=0;i<k1;i++) M0[i]=M1[i];
	if(fabs(znEns[2*j+1])<1e-20){
	  //	  for(i=0;i<k1-1;i++) M1[i+1]-=M0[i]*znEns[2*j];
	  continue; //remove poles with only real part
	}
	else if(znEns[2*j+1]>0){
	  for(i=0;i<k1-1;i++) M1[i+1]-=(M0[i]*2.0*znEns[2*j]);
	  for(i=0;i<k1-2;i++) M1[i+2]+=(M0[i]*(square(znEns[2*j])+square(znEns[2*j+1])));
//	  double re=cos(atan2(znEns[2*j+1],znEns[2*j]));//magnify to 1
//	  for(i=0;i<k1-1;i++) M1[i+1]-=(M0[i]*2.0*re);
//	  for(i=0;i<k1-2;i++) M1[i+2]+=(M0[i]);
	}
      }

      for(j=0;j<k;j++) net[0].cell[0].am.M[0][j]=-M1[j+1];
      net[0].cell[0].am.M[0][k]=0;
      //      net[0].cell[0].am.M[0][k]=M0mean;
      //      net[0].cell[0].am.M[0][j]=0;//??
      net[0].nEns=1;
      net[0].n_cells=1;
      net_save(net,"tmp/shrink1.net");
      //#ifndef NEWSELECTMETHOD
      {
	FILE *fp=fopen("tmp/M1.dat","w");
	for(j=0;j<k;j++) fprintf(fp,"%e\n",net[0].cell[0].am.M[0][j]);
	fclose(fp);
      }
      //#endif
      {
	double *thetanEns=&theta_zn[nEns*maxk];
	int *inEns=&i_zn[nEns*maxk];
	FILE *fp=fopen("tmp/theta1.dat","w");
	for(j=0;j<k;j++) fprintf(fp,"%e\n",thetanEns[inEns[j]]);
	fclose(fp);
      }

      fprintf(stdout,"Net is shrinked to single unit and saved in shrink1.net.\n");
      free(M0);
      free(M1);
    }

    free(A);
    free(z);
  }
  /// LSP
  {
    //LSP:Line Spectral Pairs
    //    if(1==0){
    //      gsl_poly_complex_workspace *wk1= gsl_poly_complex_workspace_alloc (k1+1);//for LSP
    //      sign=1;P[k1]=-1.;P[0]=-sign;
    //      for(j=0;j<k;j++) P[j+1]=As[j]+sign*As[k-1-j];   //  for(i=0;i<=k1;i++) printf("P[%d]=%e\n",i,P[i]);
    //      //    w= gsl_poly_complex_workspace_alloc (k2);//for poles
    //      gsl_poly_complex_solve (P, k1+1, wk1, z);
    //      for(j=0;j<k1;j++){
    //	fprintf (fp3,"%+e %+e %+e %+e %d %d #Re(z) Im(z) |z| Arg(z) v i k net\n", 
    //		 z[2*j], z[2*j+1],sqrt(z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1]),atan2(z[2*j+1],z[2*j]),j,k);
    //      }
    //      sign=-1;Q[k1]=-1.;Q[0]=-sign;
    //      for(j=0;j<k;j++) Q[j+1]=As[j]+sign*As[k-1-j]; //  for(i=0;i<=k1;i++) printf("Q[%d]=%e\n",i,P[i]);
    //      //    w= gsl_poly_complex_workspace_alloc (k2);//for poles
    //      gsl_poly_complex_solve (Q, k1+1, wk1, z);
    //      gsl_poly_complex_workspace_free (wk1);
    //      for(j=0;j<k1;j++){
    //	fprintf (fp3,"%+e %+e %+e %+e %d %d #Re(z) Im(z) |z| Arg(z) v i k net\n", 
    //		 z[2*j], z[2*j+1],sqrt(z[2*j]*z[2*j]+z[2*j+1]*z[2*j+1]),atan2(z[2*j+1],z[2*j]),j,k);
    //      }
    //      gsl_poly_complex_workspace_free (wk1);
    //      free(P);
    //      free(Q);
    //    }
    
    {//k3=2*k1+1
      double *P=(double*)malloc(sizeof(double)*(k1+1));//for LSP
      double *Q=(double*)malloc(sizeof(double)*(k1+1));//for LSP
      double *PQ=(double*)malloc(sizeof(double)*(2*k1+1));//for LSP
      double *As=&An[nEns*k1];
      int sign;
      //      gsl_poly_complex_workspace *wk2=gsl_poly_complex_workspace_alloc (2*k1+1);//for LSP
      sign=1;P[k1]=-1.;P[0]=-sign;
      for(j=0;j<k;j++) P[j+1]=As[j]+sign*As[k-1-j];
      sign=-1;Q[k1]=-1.;Q[0]=-sign;
      for(j=0;j<k;j++) Q[j+1]=As[j]+sign*As[k-1-j];
      for(j=0;j<=2*k1;j++) PQ[j]=0;
      for(j=0;j<=k1;j++){
	for(i=0;i<=k1;i++){
	  PQ[j+i] +=P[i]*Q[j];
	}
      }
      //      for(i=0;i<2*k1;i++) printf("PQ[%d]=%e\n",i,PQ[i]);
      gsl_poly_complex_solve (PQ, 2*k1+1, wk2, zn);
      //      gsl_poly_complex_workspace_free (w);
      //    gsl_poly_complex_solve (Q, k1+1, w2, z);
      for(j=0;j<2*k1;j++){
	fprintf (fp3,"%+e %+e %+e %+e %d %d #Re(z) Im(z) |z| Arg(z) v i k net\n", 
		 zn[2*j], zn[2*j+1],sqrt(zn[2*j]*zn[2*j]+zn[2*j+1]*zn[2*j+1]),atan2(zn[2*j+1],zn[2*j]),j,k);
      }
      //      gsl_poly_complex_workspace_free(wk2);
      free(PQ);
      free(P);
      free(Q);
    }

//    {//k3=2*k1+1
//      double *P=(double*)malloc(sizeof(double)*(k1+1));//for LSP
//      double *Q=(double*)malloc(sizeof(double)*(k1+1));//for LSP
//      FILE *fp6=fopen("./tmp/poles6.dat","w");
//      double *PQ=(double*)malloc(sizeof(double)*(2*k1+1));//for LSP
//      int sign;
//      gsl_poly_complex_workspace *wk2=gsl_poly_complex_workspace_alloc (2*k1+1);//for LSP
//      for(nn=0;nn<nEns;nn++){
//	double *As=&An[nn*k1];
//	sign=1;P[k1]=-1.;P[0]=-sign;
//	for(j=0;j<k;j++) P[j+1]=As[j]+sign*As[k-1-j];
//	sign=-1;Q[k1]=-1.;Q[0]=-sign;
//	for(j=0;j<k;j++) Q[j+1]=As[j]+sign*As[k-1-j];
//	for(j=0;j<=2*k1;j++) PQ[j]=0;
//	for(j=0;j<=k1;j++){
//	  for(i=0;i<=k1;i++){
//	    PQ[j+i] +=P[i]*Q[j];
//	  }
//	}
//	gsl_poly_complex_solve (PQ, 2*k1+1, wk2, zn);
//	for(j=0;j<2*k1;j++){
//	  fprintf (fp6,"%e %e ", zn[2*j], zn[2*j+1]);
//	}
//	fprintf (fp6,"%e \n",net[nn].cell[n].v);
//      }
//      gsl_poly_complex_workspace_free(wk2);
//      fclose(fp6);
//      free(PQ);
//      free(P);
//      free(Q);
//    }
  }

  {//shrink the net
    FLOAT vsum=0;
    FLOAT *M0=(FLOAT*)malloc(sizeof(FLOAT)*(k+1));
    for(j=0;j<=k;j++) M0[j]=0;
    for(nn=0;nn<nEns;nn++){
      for(n=0;n<net[nn].n_cells;n++){
	//	if(fabs(net[nn].cell[n].am.M[0][k])>1e-5) continue;
	for(j=0;j<=k;j++) M0[j]+=(net[nn].cell[n].am.M[0][j]*net[nn].cell[n].v);
	vsum+=net[nn].cell[n].v;
      }
    }
    for(j=0;j<=k;j++) net[0].cell[0].am.M[0][j]=M0[j]/vsum;
    net[0].nEns=1;
    net[0].n_cells=1;
    net_save(net,"tmp/shrink.net");
    fprintf(stdout,"Net is shrinked to single unit and saved in shrink.net.\n");
    free(M0);
  }

  gsl_poly_complex_workspace_free (wk);
  gsl_poly_complex_workspace_free(wk2);
  free(vn);
  free(An);
  free(zn);
  free(theta_zn);
  free(rho_zn);
  free(i_zn);
  free(c_zn);
  free(v_zn);
  fclose(fp3);
  fclose(fp2);
  fclose(fp);
  fclose(fp4);
  fclose(fp6);
  fclose(fp7);
  //  fprintf(stdout,"Poles of M are saved in '%s','%s','%s'.",fname,fname2,fname3);
  fprintf(stdout,"Poles of M are saved in './tmp/poles?.dat'.");
}
