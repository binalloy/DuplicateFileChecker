#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "main.h"
#define MAXSIZE 1024*500//proper size
int cmpfile(char *rel_path1 ,char *rel_path2,int64_t size){ 
    char line1[MAXSIZE]= {0}, line2[MAXSIZE]= {0};
    int count = 0;
    //int full = 0;
 	//clock_t start,finish;
 	//double comparetime;
    char path1[PATH_MAX_LEN] = {0};
    char path2[PATH_MAX_LEN] = {0};
    
    // strcpy(path1, WORK_PATH);
    // strcat(path1, rel_path1);
    // strcpy(path2, WORK_PATH);
    // strcat(path2, rel_path2);
    sprintf(path1,"%s/%s",WORK_PATH,rel_path1);
    sprintf(path2,"%s/%s",WORK_PATH,rel_path2);
    #if DEBUG
    _dbg(path1)
    _dbg(path2)
    _dbg(rel_path1)
    _dbg(rel_path2)
    _dbg(WORK_PATH)
    #endif
    int times;
    int result;
    FILE *ifp1;
    ifp1=fopen(path1, "r");

    FILE *ifp2;
    ifp2=fopen(path2, "r");
    
    if((ifp1==NULL)||(ifp2==NULL)){
    	fprintf(stderr,"Error:file cannot be opened.\n");
        exit(1);
    }
     //start=clock();
     if((size>=0)&&(size<((int64_t)1<<20)*50L)){//  50M>filesize>0M
     	 while ((fread(line1, MAXSIZE,sizeof(char), ifp1) != 0) &&
          (fread(line2, MAXSIZE,sizeof(char), ifp2) != 0)) {
         if ((result=memcmp(line1, line2,MAXSIZE)) == 0) {
             count++;
              //full = 1;
            }
         else {
         	   //printf("these two file is different.");
         break;
             }
        }
     }
     else if((size>=((int64_t)1<<20)*50L)&&(size<((int64_t)1<<30)*5L)){//5G>filesize>50M
         times=(size>>20)/5;
     	 while ((fread(line1, MAXSIZE,sizeof(char), ifp1) != 0) &&
          (fread(line2, MAXSIZE,sizeof(char), ifp2) != 0)) {
         if ((result=memcmp(line1, line2,MAXSIZE)) == 0) {
             count++;
             fseek(ifp1,size/times,SEEK_CUR);//skip some bytes for pointer
             fseek(ifp2,size/times,SEEK_CUR);
              //full = 1;
            }
         else {
         	   //printf("these two file is different.");
         break;
             }
        }
     }
     
     else {//filesize>5G
     	 	 while ((fread(line1, MAXSIZE,sizeof(char), ifp1) != 0) &&
          (fread(line2, MAXSIZE, sizeof(char),ifp2) != 0)) {
         if ((result=memcmp(line1, line2,MAXSIZE)) == 0) {
             count++;
             fseek(ifp1,size/1500,SEEK_CUR);//skip some bytes for pointer
             fseek(ifp2,size/1500,SEEK_CUR);
             //full = 1;
            }
         else {
         	   //printf("these two file is different.");
         break;
             }
        }

     }	
    fclose(ifp1);
    fclose(ifp2);
    //free(line1);
    //free(line2);
     //finish=clock();
     //comparetime=(double)(finish-start)/CLOCKS_PER_SEC;
     //printf("loop is finished\n");
    // printf("%f seconds\n",comparetime);
    if((feof(ifp1)!=0)&&(feof(ifp2)!=0)){// file is end
    fprintf(stderr, " Unknow error: %s and %s cannot be read!\n",path1,path2);
     //exit(1);
    path1[0]='\0';
    path2[0]='\0';
    }
   
    
    return result;
 }