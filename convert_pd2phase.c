#include<stdio.h>
#include"gif.h"

int convert_pd2phase(long *id0,long *id1,long *id2,double *fringe, double *zabs0){
  double pmax0,pmin0,smax0,smin0,pp,ss,pp0,ss0,aa,zabs,zz1,zz2,zzs1,zzs2,zzmax,zzmin,zzsmax,zzsmin,xx,xx0,dxx;
  double x4,y4,x1y3,x2y2,x3y1,x3,y3,x1y2,x2y1,x2,y2,x1y1,x1,y1,p00=1.e20,p01=1.e20;
  double dsin,dsn,dcos,da,dab1,dab2,dab3,dab4,dab5,b1,b2,b3,b4,b5,a00,b00,x0,y0,sp0,cp0;
  int ll,nmin1,j,n;
  x4=0.0;
  y4=0.0;
  x1y3=0.0;
  x2y2=0.0;
  x3y1=0.0;
  x3=0.0;
  y3=0.0;
  x1y2=0.0;
  x2y1=0.0;
  x2=0.0;
  y2=0.0;
  x1y1=0.0;
  x1=0.0;
  y1=0.0;
  pp0=0.0;
  ss0=0.0;
  
  for(j=0;j<BIN;j++){
    pp0+=(double)id0[j]*ADCFAC/((double)id2[j]*ADCFAC);
    ss0+=(double)id1[j]*ADCFAC/((double)id2[j]*ADCFAC);
  }
  
  pp0/=(double)BIN;
  ss0/=(double)BIN;
  
  for(j=0;j<BIN;j++){
    pp=(double)id0[j]*ADCFAC/((double)id2[j]*ADCFAC)-pp0;
    ss=(double)id1[j]*ADCFAC/((double)id2[j]*ADCFAC)-ss0;
    x4+=pp*pp*pp*pp;
    y4+=ss*ss*ss*ss;
    x1y3+=pp*ss*ss*ss;
    x2y2+=pp*pp*ss*ss;
    x3y1+=pp*pp*pp*ss;
    x3+=pp*pp*pp;
    y3+=ss*ss*ss;
    x1y2+=pp*ss*ss;
    x2y1+=pp*pp*ss;
    x2+=pp*pp;
    y2+=ss*ss;
    x1y1+=pp*ss;
    x1+=pp;
    y1+=ss;
  }

  da= x1y1*x1y1*x1y3*x1y3*x4 - 2*x1y1*x1y1*x1y3*x2y2*x3y1 + x1y1*x1y1*x2y2*x2y2*x2y2 - 
    x1y1*x1y1*x2y2*x4*y4 + x1y1*x1y1*x3y1*x3y1*y4 - 2*x1y1*x1y2*x1y2*x1y3*x4 + 
    2*x1y1*x1y2*x1y2*x2y2*x3y1 + 2*x1y1*x1y2*x1y3*x2y1*x3y1 + 
    2*x1y1*x1y2*x1y3*x2y2*x3 - 4*x1y1*x1y2*x2y1*x2y2*x2y2 + 
    2*x1y1*x1y2*x2y1*x4*y4 + 2*x1y1*x1y2*x2y2*x4*y3 - 
    2*x1y1*x1y2*x3*x3y1*y4 - 2*x1y1*x1y2*x3y1*x3y1*y3 - 
    2*x1y1*x1y3*x1y3*x2y1*x3 + 2*x1y1*x1y3*x2y1*x2y1*x2y2 - 
    2*x1y1*x1y3*x2y1*x4*y3 + 2*x1y1*x1y3*x3*x3y1*y3 - 
    2*x1y1*x2y1*x2y1*x3y1*y4 + 2*x1y1*x2y1*x2y2*x3*y4 + 
    2*x1y1*x2y1*x2y2*x3y1*y3 - 2*x1y1*x2y2*x2y2*x3*y3 + x1y2*x1y2*x1y2*x1y2*x4 - 
    2*x1y2*x1y2*x1y2*x2y1*x3y1 - 2*x1y2*x1y2*x1y2*x2y2*x3 + 2*x1y2*x1y2*x1y3*x2y1*x3 + 
    x1y2*x1y2*x2*x2y2*x2y2 - x1y2*x1y2*x2*x4*y4 + 3*x1y2*x1y2*x2y1*x2y1*x2y2 - 
    2*x1y2*x1y2*x2y1*x4*y3 - x1y2*x1y2*x2y2*x4*y2 + x1y2*x1y2*x3*x3*y4 + 
    2*x1y2*x1y2*x3*x3y1*y3 + x1y2*x1y2*x3y1*x3y1*y2 - 2*x1y2*x1y3*x2*x2y1*x2y2 + 
    2*x1y2*x1y3*x2*x4*y3 - 2*x1y2*x1y3*x2y1*x2y1*x2y1 + 2*x1y2*x1y3*x2y1*x4*y2 - 
    2*x1y2*x1y3*x3*x3*y3 - 2*x1y2*x1y3*x3*x3y1*y2 + 2*x1y2*x2*x2y1*x3y1*y4 - 
    2*x1y2*x2*x2y2*x3y1*y3 - 2*x1y2*x2y1*x2y1*x3*y4 + 2*x1y2*x2y1*x2y1*x3y1*y3 - 
    2*x1y2*x2y1*x2y2*x3y1*y2 + 2*x1y2*x2y2*x2y2*x3*y2 + x1y3*x1y3*x2*x2y1*x2y1 - 
    x1y3*x1y3*x2*x4*y2 + x1y3*x1y3*x3*x3*y2 - 2*x1y3*x2*x2y1*x3y1*y3 + 
    2*x1y3*x2*x2y2*x3y1*y2 + 2*x1y3*x2y1*x2y1*x3*y3 - 2*x1y3*x2y1*x2y2*x3*y2 - 
    x2*x2y1*x2y1*x2y2*y4 + 2*x2*x2y1*x2y2*x2y2*y3 - x2*x2y2*x2y2*x2y2*y2 + 
    x2*x2y2*x4*y2*y4 - x2*x2y2*x4*y3*y3 - x2*x3y1*x3y1*y2*y4 + x2*x3y1*x3y1*y3*y3 + 
    x2y1*x2y1*x2y1*x2y1*y4 - 2*x2y1*x2y1*x2y1*x2y2*y3 + x2y1*x2y1*x2y2*x2y2*y2 - x2y1*x2y1*x4*y2*y4 + 
    x2y1*x2y1*x4*y3*y3 + 2*x2y1*x3*x3y1*y2*y4 - 2*x2y1*x3*x3y1*y3*y3 - 
    x2y2*x3*x3*y2*y4 + x2y2*x3*x3*y3*y3;

  dab1= x1y2*x1y2*(x1*(x1y3*x2y1 + x3*y4 + x3y1*y3) + x1y1*x1y1*x2y2 + 
		   x1y1*(-2*x1y3*x2 + x3*y3 + 2*x3y1*y2) + x1y3*x3*y1 - x2*x2*y4 - 
		   2*x2*x2y1*y3 + x2y1*x2y1*y2 + 2*x2y1*x2y2*y1) + 
    x1y2*(x1y1*(x1*x1y3*x2y2 - x1*x3y1*y4 + x1y3*x3y1*y1 + 3*x2*x2y1*y4 + 
		x2*x2y2*y3 + x2y1*x2y1*y3 - 4*x2y1*x2y2*y2 - x2y2*x2y2*y1) - 
	  x1y3*(2*x1*x3*y3 + x1*x3y1*y2 - 2*x2*x2*y3 - x2*x2y1*y2 + x2*x2y2*y1 + 
		2*x2y1*x2y1*y1) - x1*x2y1*x2y1*y4 + x1*x2y2*x2y2*y2 + 
	  x1y1*x1y1*(x1y3*x2y1 - x3*y4 - 2*x3y1*y3) + x2*x3y1*y1*y4 - 
	  x2*x3y1*y2*y3 - x2y1*x3*y1*y4 + x2y1*x3*y2*y3 + x2y1*x3y1*y1*y3 - 
	  x2y1*x3y1*y2*y2 - x2y2*x3*y1*y3 + x2y2*x3*y2*y2) - 
    x1y2*x1y2*x1y2*(x1*x2y2 + x1y1*x2y1 + x3*y2 + x3y1*y1) + 
    x1y1*(x1*((-x1y3*x1y3)*x2y1 + x1y3*x3y1*y3 + x2y2*(x2y1*y4 - x2y2*y3)) - 
	  x1y3*x1y3*x3*y1 + x1y3*(-3*x2*x2y1*y3 + x2*x2y2*y2 + x2y1*x2y1*y2 + 
				  x2y1*x2y2*y1) - x2*x3y1*y2*y4 + x2*x3y1*y3*y3 + x2y1*x3*y2*y4 - 
	  x2y1*x3*y3*y3 - x2y1*x3y1*y1*y4 + x2y1*x3y1*y2*y3 + x2y2*x3*y1*y4 - 
	  x2y2*x3*y2*y3) + x1*x1y3*x1y3*x3*y2 + x1*x1y3*x2y1*x2y1*y3 - 
    x1*x1y3*x2y1*x2y2*y2 + x1*x2y1*x3y1*y2*y4 - x1*x2y1*x3y1*y3*y3 - 
    x1*x2y2*x3*y2*y4 + x1*x2y2*x3*y3*y3 + x1y1*x1y1*x1y1*(x3y1*y4 - x1y3*x2y2) + 
    x1y1*x1y1*(x1y3*x1y3*x2 + x1y3*x3*y3 - x1y3*x3y1*y2 - x2*x2y2*y4 - 
	       x2y1*x2y1*y4 + x2y1*x2y2*y3 + x2y2*x2y2*y2) + x1y2*x1y2*x1y2*x1y2*x2 - x1y3*x1y3*x2*x2*y2 + 
    x1y3*x1y3*x2*x2y1*y1 - x1y3*x2*x3y1*y1*y3 + x1y3*x2*x3y1*y2*y2 + 
    x1y3*x2y1*x3*y1*y3 - x1y3*x2y1*x3*y2*y2 + x2*x2*x2y2*y2*y4 - 
    x2*x2*x2y2*y3*y3 - x2*x2y1*x2y1*y2*y4 + x2*x2y1*x2y1*y3*y3 - 
    x2*x2y1*x2y2*y1*y4 + x2*x2y1*x2y2*y2*y3 + x2*x2y2*x2y2*y1*y3 - 
    x2*x2y2*x2y2*y2*y2 + x2y1*x2y1*x2y1*y1*y4 - x2y1*x2y1*x2y1*y2*y3 - x2y1*x2y1*x2y2*y1*y3 + 
    x2y1*x2y1*x2y2*y2*y2;

  dab2= x1y2*x1y2*(-2*x1*x2y1*x3y1 - x1*x2y2*x3 + x1y1*x1y1*(-x4) + 
		   x2*(x1y1*x3y1 + x2y1*x2y1 - x4*y2) + x1y1*x2y1*x3 + x2*x2*x2y2 - 
		   x2y1*x4*y1 + x3*x3*y2 + x3*x3y1*y1) + 
    x1y2*(x1y3*((-x1)*x1y1*x4 + x1*x2y1*x3 + x1y1*x2*x3 - x2*x2*x2y1 + 
		x2*x4*y1 - x3*x3*y1) - x1y1*((-x1)*x2y2*x3y1 + 4*x2*x2y1*x2y2 - 
					     x2*x4*y3 + x2y1*x2y1*x2y1 - 3*x2y1*x4*y2 - x2y2*x4*y1 + x3*x3*y3 + 
					     3*x3*x3y1*y2 + x3y1*x3y1*y1) + 2*x1*x2y1*x2y1*x2y2 - x1*x2y1*x4*y3 - 
	  x1*x2y2*x4*y2 + x1*x3*x3y1*y3 + x1*x3y1*x3y1*y2 + 
	  x1y1*x1y1*(x2y1*x3y1 + x2y2*x3) - x2*x2*x3y1*y3 + x2*x2y1*x3*y3 + 
	  x2*x2y1*x3y1*y2 + x2*x2y2*x3*y2 - x2*x2y2*x3y1*y1 - 2*x2y1*x2y1*x3*y2 + 
	  x2y1*x2y1*x3y1*y1) + 
    x1y1*(x1y3*(x1*x2y1*x3y1 + 2*x2*x2y1*x2y1 - x2*x4*y2 - x2y1*x4*y1 + 
		x3*x3*y2 + x3*x3y1*y1) - x1*(x2y1*x2y2*x2y2 - x2y2*x4*y3 + x3y1*x3y1*y3) - 
	  x2*x2y2*x3*y3 + x2*x2y2*x3y1*y2 + x2y1*x2y1*x3*y3 - 2*x2y1*x2y1*x3y1*y2 + 
	  x2y1*x2y2*x3*y2 + x2y1*x2y2*x3y1*y1 - x2y2*x2y2*x3*y1) + 
    x1y2*x1y2*x1y2*(x1*x4 - x2*x3) - x1*x1y3*x2y1*x2y1*x2y1 + x1*x1y3*x2y1*x4*y2 - 
    x1*x1y3*x3*x3y1*y2 + x1*x2y1*x2y1*x3y1*y3 - x1*x2y1*x2y2*x3*y3 - 
    x1*x2y1*x2y2*x3y1*y2 + x1*x2y2*x2y2*x3*y2 + x1y1*x1y1*x1y1*(x1y3*x4 - x2y2*x3y1) + 
    x1y1*x1y1*(x2*(x2y2*x2y2 - x1y3*x3y1) - x2y1*(2*x1y3*x3 + x4*y3) + 
	       x2y1*x2y1*x2y2 - x2y2*x4*y2 + x3*x3y1*y3 + x3y1*x3y1*y2) + 
    x1y3*x2*x2*x3y1*y2 - x1y3*x2*x2y1*x3*y2 - x1y3*x2*x2y1*x3y1*y1 + 
    x1y3*x2y1*x2y1*x3*y1 + x2*x2*x2y1*x2y2*y3 - x2*x2*x2y2*x2y2*y2 - x2*x2y1*x2y1*x2y1*y3 + 
    x2*x2y1*x2y2*x2y2*y1 - x2*x2y2*x4*y1*y3 + x2*x2y2*x4*y2*y2 + 
    x2*x3y1*x3y1*y1*y3 - x2*x3y1*x3y1*y2*y2 + x2y1*x2y1*x2y1*x2y1*y2 - x2y1*x2y1*x2y1*x2y2*y1 + 
    x2y1*x2y1*x4*y1*y3 - x2y1*x2y1*x4*y2*y2 - 2*x2y1*x3*x3y1*y1*y3 + 
    2*x2y1*x3*x3y1*y2*y2 + x2y2*x3*x3*y1*y3 - x2y2*x3*x3*y2*y2;

  dab3= x1y2*(x1y1*((-x1)*x2y2*x2y2 + x1*x4*y4 + x1y3*x2*x2y1 - x1y3*x4*y1 - 
		    x2*x3*y4 - 2*x2*x3y1*y3 - 2*x2y1*x3*y3 + x2y1*x3y1*y2 + 
		    3*x2y2*x3*y2 + x2y2*x3y1*y1) + x1*((-x1y3)*x2y1*x2y1 + x1y3*x4*y2 - 
						       x2y1*x3*y4 + x2y1*x3y1*y3 + x2y2*x3*y3 - x2y2*x3y1*y2) + 
	      x1y1*x1y1*(2*x4*y3 - 2*x2y1*x2y2) - x1y3*x2*x3*y2 + x1y3*x2y1*x3*y1 + 
	      x2*x2*x2y1*y4 - x2*x2*x2y2*y3 + x2*x2y1*x2y1*y3 - 2*x2*x2y1*x2y2*y2 + 
	      x2*x2y2*x2y2*y1 - x2*x4*y1*y4 + x2*x4*y2*y3 + x2y1*x2y1*x2y1*(-y2) + 
	      x2y1*x2y1*x2y2*y1 - x2y1*x4*y1*y3 + x2y1*x4*y2*y2 + x3*x3*y1*y4 - 
	      x3*x3*y2*y3 + x3*x3y1*y1*y3 - x3*x3y1*y2*y2) + 
    x1y2*x1y2*(x1*x2y1*x2y2 - x1*x4*y3 + x1y1*(x2*x2y2 + x2y1*x2y1 - 2*x4*y2) + 
	       x2*x3*y3 + x2*x3y1*y2 + x2y1*x3*y2 - x2y1*x3y1*y1 - 2*x2y2*x3*y1) + 
    x1y1*(x1*(x1y3*x2y1*x2y2 - x1y3*x4*y3 - x2y1*x3y1*y4 + x2y2*x3y1*y3) - 
	  x2y1*(2*x1y3*x3*y2 - 3*x2*x2y2*y3 + x2y2*x2y2*y1 - x4*y1*y4 + 
		x4*y2*y3) + x1y3*x2*x3*y3 + x1y3*x2y2*x3*y1 + 
	  x2y1*x2y1*(x2y2*y2 - 2*x2*y4) - x2*x2y2*x2y2*y2 + x2*x4*y2*y4 - 
	  x2*x4*y3*y3 - x3*x3*y2*y4 + x3*x3*y3*y3 - x3*x3y1*y1*y4 + 
	  x3*x3y1*y2*y3) + x1*x1y3*x2y1*x3*y3 - x1*x1y3*x2y2*x3*y2 + 
    x1*x2y1*x2y1*x2y1*y4 - 2*x1*x2y1*x2y1*x2y2*y3 + x1*x2y1*x2y2*x2y2*y2 - 
    x1*x2y1*x4*y2*y4 + x1*x2y1*x4*y3*y3 + x1*x3*x3y1*y2*y4 - 
    x1*x3*x3y1*y3*y3 + x1y1*x1y1*x1y1*(x2y2*x2y2 - x4*y4) + 
    x1y1*x1y1*((-x1y3)*x2*x2y2 + x1y3*x4*y2 + x2*x3y1*y4 + 2*x2y1*x3*y4 - 
	       2*x2y2*x3*y3 - x2y2*x3y1*y2) + x1y2*x1y2*x1y2*(x4*y1 - x2*x2y1) - 
    x1y3*x2*x2*x2y1*y3 + x1y3*x2*x2*x2y2*y2 + x1y3*x2*x2y1*x2y1*y2 - 
    x1y3*x2*x2y1*x2y2*y1 + x1y3*x2*x4*y1*y3 - x1y3*x2*x4*y2*y2 - 
    x1y3*x3*x3*y1*y3 + x1y3*x3*x3*y2*y2 - x2*x2*x3y1*y2*y4 + x2*x2*x3y1*y3*y3 + 
    x2*x2y1*x3*y2*y4 - x2*x2y1*x3*y3*y3 + x2*x2y1*x3y1*y1*y4 - 
    x2*x2y1*x3y1*y2*y3 - x2*x2y2*x3y1*y1*y3 + x2*x2y2*x3y1*y2*y2 - 
    x2y1*x2y1*x3*y1*y4 + x2y1*x2y1*x3*y2*y3 + x2y1*x2y2*x3*y1*y3 - 
    x2y1*x2y2*x3*y2*y2;

  dab4= x1y2*(-2*x1*(x1y3*x2y1*x2y2 - x1y3*x4*y3 - x2y1*x3y1*y4 + x2y2*x3y1*y3) + 
	      x1y1*x1y1*(x4*y4 - x2y2*x2y2) + x1y1*(x1y3*x2*x2y2 - x1y3*x2y1*x2y1 - 
						    x2*x3y1*y4 - x2y1*x3*y4 + x2y1*x3y1*y3 + x2y2*x3*y3) - 
	      2*x1y3*x2*x3*y3 - x1y3*x2*x3y1*y2 + x1y3*x2y1*x3*y2 + 
	      x1y3*x2y1*x3y1*y1 + x1y3*x2y2*x3*y1 - x2*x2y1*x2y1*y4 + x2*x2y2*x2y2*y2 + 
	      2*x2y1*x2y1*x2y2*y2 - 2*x2y1*x2y2*x2y2*y1 + x2y1*x4*y1*y4 - x2y1*x4*y2*y3 + 
	      x2y2*x4*y1*y3 - x2y2*x4*y2*y2 - x3*x3y1*y1*y4 + x3*x3y1*y2*y3 - 
	      x3y1*x3y1*y1*y3 + x3y1*x3y1*y2*y2) + 
    x1y2*x1y2*(x1*x2y2*x2y2 - x1*x4*y4 + x1y1*x2y1*x2y2 - x1y1*x4*y3 + 
	       x1y3*x2*x2y1 - x1y3*x4*y1 + x2*x3*y4 + x2*x3y1*y3 - 2*x2y1*x3y1*y2 - 
	       x2y2*x3*y2 + x2y2*x3y1*y1) + x1*x1y3*x1y3*x2y1*x2y1 - x1*x1y3*x1y3*x4*y2 - 
    2*x1*x1y3*x2y1*x3y1*y3 + 2*x1*x1y3*x2y2*x3y1*y2 - x1*x2y1*x2y1*x2y2*y4 + 
    2*x1*x2y1*x2y2*x2y2*y3 - x1*x2y2*x2y2*x2y2*y2 + x1*x2y2*x4*y2*y4 - 
    x1*x2y2*x4*y3*y3 - x1*x3y1*x3y1*y2*y4 + x1*x3y1*x3y1*y3*y3 + 
    x1y1*x1y1*(x1y3*x2y1*x2y2 - x1y3*x4*y3 - x2y1*x3y1*y4 + x2y2*x3y1*y3) + 
    x1y1*(x1y3*x1y3*(x4*y1 - x2*x2y1) + x1y3*(x2*x3y1*y3 + x2y1*x3*y3 + 
					      x2y1*x3y1*y2 - x2y2*(x3*y2 + 2*x3y1*y1)) + 
	  x2y2*(x2*x2y1*y4 - 2*x2y1*x2y1*y3 - x4*y1*y4 + x4*y2*y3) - 
	  x2*x2y2*x2y2*y3 + x2y1*x2y1*x2y1*y4 - x2y1*x4*y2*y4 + x2y1*x4*y3*y3 + x2y2*x2y2*x2y2*y1 + 
	  x3*x3y1*y2*y4 - x3*x3y1*y3*y3 + x3y1*x3y1*y1*y4 - x3y1*x3y1*y2*y3) + 
    x1y2*x1y2*x1y2*(x4*y2 - x2*x2y2) + x1y3*x1y3*x2*x3*y2 - x1y3*x1y3*x2y1*x3*y1 + 
    x1y3*x2*x2y1*x2y1*y3 - x1y3*x2*x2y1*x2y2*y2 - x1y3*x2y1*x2y1*x2y1*y2 + 
    x1y3*x2y1*x2y1*x2y2*y1 - x1y3*x2y1*x4*y1*y3 + x1y3*x2y1*x4*y2*y2 + 
    x1y3*x3*x3y1*y1*y3 - x1y3*x3*x3y1*y2*y2 + x2*x2y1*x3y1*y2*y4 - 
    x2*x2y1*x3y1*y3*y3 - x2*x2y2*x3*y2*y4 + x2*x2y2*x3*y3*y3 - 
    x2y1*x2y1*x3y1*y1*y4 + x2y1*x2y1*x3y1*y2*y3 + x2y1*x2y2*x3*y1*y4 - 
    x2y1*x2y2*x3*y2*y3 + x2y1*x2y2*x3y1*y1*y3 - x2y1*x2y2*x3y1*y2*y2 - 
    x2y2*x2y2*x3*y1*y3 + x2y2*x2y2*x3*y2*y2;

  dab5= x1y3*(x1y2*(x1*x2y1*x3y1 + x1*x2y2*x3 + x1y1*x1y1*(-x4) + 
		    x2*(x1y1*x3y1 - 2*x2y1*x2y1 + x4*y2) + x1y1*x2y1*x3 - x2*x2*x2y2 + 
		    2*x2y1*x4*y1 - x3*x3*y2 - 2*x3*x3y1*y1) + 
	      x1*(-2*x1y1*x2y2*x3y1 + x2y1*x2y1*x2y2 - x2y1*x4*y3 + x3*x3y1*y3) + 
	      x1y2*x1y2*(x2*x3 - x1*x4) + x1y1*x1y1*x2y2*x3 + x1y1*x2*x4*y3 - 
	      x1y1*x2y1*x4*y2 - x1y1*x3*x3*y3 + x1y1*x3*x3y1*y2 - x2*x2*x3y1*y3 + 
	      x2*x2y1*x3*y3 - x2*x2y1*x3y1*y2 + 2*x2*x2y2*x3y1*y1 + x2y1*x2y1*x3*y2 - 
	      2*x2y1*x2y2*x3*y1) + 
    x1y2*(x1*(-2*x2y1*x2y2*x2y2 + x2y1*x4*y4 + x2y2*x4*y3 - x3*x3y1*y4 - 
	      x3y1*x3y1*y3) + x1y1*x1y1*x2y2*x3y1 + 
	  x1y1*((-x2)*x4*y4 + x2y1*x2y1*x2y2 - x2y1*x4*y3 + x2y2*x4*y2 + x3*x3*y4 + 
		x3*x3y1*y3 - x3y1*x3y1*y2) + x2*x2*x3y1*y4 - x2*x2y1*x3*y4 + 
	  x2*x2y1*x3y1*y3 - x2*x2y2*x3*y3 - x2*x2y2*x3y1*y2 + x2y1*x2y1*x3y1*y2 - 
	  2*x2y1*x2y2*x3y1*y1 + 2*x2y2*x2y2*x3*y1) + 
    x1y2*x1y2*(x1*x2y2*x3y1 - x1y1*(x2y1*x3y1 + 2*x2y2*x3) + 2*x2*x2y1*x2y2 - 
	       x2y1*x4*y2 - x2y2*x4*y1 + x3*x3y1*y2 + x3y1*x3y1*y1) + 
    x1y3*x1y3*(x1*x1y1*x4 - x1*x2y1*x3 - x2*(x1y1*x3 + x4*y1) + x2*x2*x2y1 + 
	       x3*x3*y1) + x1*x1y1*x2y2*x2y2*x2y2 - x1*x1y1*x2y2*x4*y4 + x1*x1y1*x3y1*x3y1*y4 - 
    x1*x2y1*x2y1*x3y1*y4 + x1*x2y1*x2y2*x3*y4 + x1*x2y1*x2y2*x3y1*y3 - 
    x1*x2y2*x2y2*x3*y3 - x1y1*x1y1*x2y1*x2y2*x2y2 + x1y1*x1y1*x2y1*x4*y4 - 
    x1y1*x1y1*x3*x3y1*y4 + x1y2*x1y2*x1y2*(x1y1*x4 - x2*x3y1) + x1y1*x2*x2y2*x3*y4 - 
    x1y1*x2*x2y2*x3y1*y3 - x1y1*x2y1*x2y1*x3*y4 + x1y1*x2y1*x2y2*x3*y3 + 
    x1y1*x2y1*x2y2*x3y1*y2 - x1y1*x2y2*x2y2*x3*y2 - x2*x2*x2y1*x2y2*y4 + 
    x2*x2*x2y2*x2y2*y3 + x2*x2y1*x2y1*x2y1*y4 - x2*x2y1*x2y1*x2y2*y3 + x2*x2y1*x2y2*x2y2*y2 - 
    x2*x2y2*x2y2*x2y2*y1 + x2*x2y2*x4*y1*y4 - x2*x2y2*x4*y2*y3 - x2*x3y1*x3y1*y1*y4 + 
    x2*x3y1*x3y1*y2*y3 - x2y1*x2y1*x2y1*x2y2*y2 + x2y1*x2y1*x2y2*x2y2*y1 - x2y1*x2y1*x4*y1*y4 + 
    x2y1*x2y1*x4*y2*y3 + 2*x2y1*x3*x3y1*y1*y4 - 2*x2y1*x3*x3y1*y2*y3 - 
    x2y2*x3*x3*y1*y4 + x2y2*x3*x3*y2*y3;

  b1=dab1/da;
  b2=dab2/da;
  b3=dab3/da;
  b4=dab4/da;
  b5=dab5/da;
  a00=sqrt(4*b2/(b3*b3 -4*b1*b2)*(-1+(b1*b5*b5+b2*b4*b4-b3*b4*b5)/(b3*b3-4*b1*b2)));
  b00=sqrt(4*b1/(b3*b3 -4*b1*b2)*(-1+(b1*b5*b5+b2*b4*b4-b3*b4*b5)/(b3*b3-4*b1*b2)));
  x0=(2*b2*b4 - b3*b5)/(b3*b3-4*b1*b2);
  y0=(-b3*b4 + 2*b1*b5)/(b3*b3-4*b1*b2);
  sp0=-b3/2/sqrt(b1*b2);
  cp0=sqrt(1-sp0*sp0);
  aa=atan2(sp0,cp0);

  x0+=pp0;
  y0+=ss0;

  /*
    求めたパラメータでそれぞれの位相をもとめる。
  */
  for(j=0;j<BIN;j++){
    pp=(double)id0[j]*ADCFAC/((double)id2[j]*ADCFAC);
    ss=(double)id1[j]*ADCFAC/((double)id2[j]*ADCFAC);
    dcos=(pp-x0)/a00;
    dsin=(ss-y0)/b00;
    dsn=(dsin-sin(aa)*dcos)/cos(aa);
    zabs=sqrt(dsn*dsn+dcos*dcos);
    xx=atan2(dsn,dcos);
    // unwrap
    if(n==0){
      ll=0;
      xx0=xx;
      fringe[j]=xx;
      n++;
    }
    else{
      if(xx-xx0>PI){
	ll--;
      }
      else if(xx-xx0<-PI){
	ll++;
      }
      xx0=xx;
      fringe[j]=xx+2.*PI*(double)ll;
      n++;
    }
    zabs0[j]=zabs;
  }
  return 1;
}
