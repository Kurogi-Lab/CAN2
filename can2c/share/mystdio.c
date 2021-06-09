/*
 * mystdio.c
 *
 */
#include <stdio.h>
#define iskugiri(c) ((c==',')||(c==';')||(c==':')||(c==0x0a)||(c==0x0d))
#define isspace(c) ((c==' ')||(c==0x08))

char scanbuff[512];
char *scanargv[50];
char scanargc;

int myscanf(form,var0,var1,var2,var3,var4,var5,var6,var7)
     char *form;
     int *var0,*var1,*var2,*var3,*var4,*var5,*var6,var7;
{
  char *p,*pf;
  int i;

  for(i=0;i<5;i++) scanargv[i]=NULL;
  for(i=0;i<512;i++) scanbuff[i]=0;
  fgets(scanbuff,256,stdin);
  p = scanbuff;
  for(;*p != 0; p++) if(isspace(*p)) *p=',';
  scanbuff2argv();
  pf = form;
  i = 0;
  for(;;pf++){
    if(*pf == 0) break;
    else if(*pf == '%'){
      if(i>=scanargc) break;
      if(scanargv[i] != 0 ){
	if(i==0) sscanf(scanargv[0],pf,var0);
	if(i==1) sscanf(scanargv[1],pf,var1);
	if(i==2) sscanf(scanargv[2],pf,var2);
	if(i==3) sscanf(scanargv[3],pf,var3);
	if(i==4) sscanf(scanargv[4],pf,var4);
	if(i==5) sscanf(scanargv[5],pf,var5);
	if(i==6) sscanf(scanargv[6],pf,var6);
	if(i==7) sscanf(scanargv[7],pf,var7);
      }
      i++;
    }
  }
  return(scanargc);
}

void scanbuff2argv()
{
  char *p;

  scanargc=0;
  p = scanbuff;
  for(;*p != 0; p++) if(isspace(*p)) *p=',';
  p = scanbuff;
  scanargc=0;
  for(;*p != 0; p++){
    if(iskugiri(*p)){
      scanargv[scanargc++] = 0;
      *p = 0;
    }
    else {
      scanargv[scanargc++] = p++;
      for(;*p!=0;p++) if(iskugiri(*p)) break;
    }
  }
  return;
}

void myprintf(form,a,b,c,d,e,f,g,h,i,j,k,l,m,n)
char *form;
double a,b,c,d,e,f,g,h,i,j,k,l,m,n;
{
  char buf[256];
/*  printf(form,a,b,c,d,e,f,g,h,i);*/
#ifdef Solaris
  write(1,buf,sprintf(buf,form,a,b,c,d,e,f,g,h,i,j,k,l,m,n));
#else
  sprintf(buf,form,a,b,c,d,e,f,g,h,i,j,k,l,m,n);
  write(1,buf,strlen(buf));
#endif
  return;
}

