#include"gif.h"

long ad0[BIN],ad1[BIN],ad2[BIN],ad3[BIN]; // ファイルから読み込んだ各PDの値たち [count]

int getdata(char* filename, long *data){
  FILE *fin0;
  if((fin0=fopen(filename,"rb"))==NULL){
    printf("file open error (%s) !! \n",filename);
    return(-1);
  }
  if(fread(data,8,BIN,fin0)!=BIN){ //sizeof(int)だとだめだった。4だった。
    puts("end of file ! ");
    return(-1);
  }
  return 1;
}

int convert_fringe(char* filename){
  FILE *ftest;
  double fringe[BIN],zabs0[BIN];
  char adname0[250],adname1[250],adname2[250],adname3[250],phasefilename[250];
  sprintf(adname0,"%s.AD00",filename);
  sprintf(adname1,"%s.AD01",filename);
  sprintf(adname2,"%s.AD02",filename);
  sprintf(adname3,"%s.AD03",filename);
  getdata(adname0,ad0);
  getdata(adname1,ad1);
  getdata(adname2,ad2);
  getdata(adname3,ad3);


  if((ftest=fopen("test.phase","w"))==NULL){
    puts("output file open error (.txt) !!");
    return(-1);
  }
  
  for(int k=0;k<FREQ/BIN*TIME;k++){
    convert_pd2phase(ad0,ad1,ad2,fringe,zabs0);
    for(int i=0;i<BIN;i++){
      int n = k*BIN+i;
      fprintf(ftest,"%d %25.16e %25.16e \n",n,zabs0[i],fringe[i]);    
    }
  }
  return 0;
}

int main(){
  //char filename[250] = "../PXI1_data/50kHz/10/1609051000";
  char filename[250] = "/Users/miyo_mac/HDPF-UT/GIF/PXI1_data/50kHz/10/1609051000";
  convert_fringe(filename);
}
