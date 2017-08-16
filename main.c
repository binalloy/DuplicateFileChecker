//group member:11510257 彭福，11510746张晓文，11611601何海彬
#include "main.h"
#include "dupcheck.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "tdir.h"
#include <dirent.h> 

char WORK_PATH[PATH_MAX_LEN];

int main(int argc,char *argv[])  {      //clock_t start;
 	    clock_t finish;
 	    //start=clock();    
 	    double comparetime;
 	    char *tmp;
 	    DIR  *pDir ;  
 	    
 		if(argc!=2)
 		{
 			fprintf(stderr,"Sorry!Parameter error: the argument count is not 2!\nPlease enter the programe name and a file path.\nExit the program.\n");
 			return 1;
 		}	
        pDir=opendir(argv[1]);

        if(NULL==pDir)
         {  
           
            fprintf(stderr,"Sorry! Dirent error:\n\
PATH : \"%s\" cannot be opened by \"opendir function\" or does not exist.\nPlease reboot this programe and enter a correct file path.\n\
Exit the program.\n", argv[1]);
          

         	return 1; 
         	}   

 		strcpy(WORK_PATH,argv[1]);
 		tmp = WORK_PATH;
 		while(*(tmp+1)) tmp++;
 		if((*tmp) == '/') *tmp = '\0';
 		dupcheck_init();
        listDir(argv[1]); //第一个参数为 想要遍历的 linux 目录 例如，当前目录为 ./ ,上一层目录为../  

         finish=clock();
         comparetime=(double)(finish)/CLOCKS_PER_SEC;
         fprintf(stderr,"scaning finished!it has token %f seconds CPU time.\n",comparetime);
         return 0;
 }

 void dbgmsg(char *fname, int line, char *txt) {
 	fprintf(stderr, "%s/line %d: %s\n", fname, line, txt);
 	fflush(stderr);
 }
