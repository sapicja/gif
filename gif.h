#ifndef __INCLUDE_SWAP_H__
#define __INCLUDE_SWAP_H__
#include<stdio.h>
#include<math.h>
#include<string.h>

#define ADCFAC 5.525E-9
#define FREQ 50000       // Hz
#define TIME 60          // sec
#define BIN 5000         // <-> 0.1sec in 50kHz
#define PI 3.1415926535897932384626


//-----------------------------------------------------------------
// 関数宣言
//-----------------------------------------------------------------
int convert_pd2phase(long *id0,long *id1,long *id2,double *fringe, double *zabs0);

#endif //__INCLUDE_SWAP_H__
