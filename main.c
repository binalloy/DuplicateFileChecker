#include "main.h"
#include "dupcheck.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "tdir.h"
 int main(int argc,char *argv[])  
 {      clock_t start,finish;
 	    start=clock();    
 	    double comparetime;
 	    char *tmp;
 	    
 		if(argc!=2)
 		{
 			fprintf(stderr,"the argument cout is not 2,return 1\n");
 			return 1;
 		}	


 		strcpy(WORK_PATH,argv[1]);
 		tmp = WORK_PATH;
 		while(*(tmp+1)) tmp++;
 		if((*tmp) == '/') *tmp = '\0';
 		dupcheck_init();
        listDir(argv[1]); //第一个参数为 想要遍历的 linux 目录 例如，当前目录为 ./ ,上一层目录为../  

         finish=clock();
         comparetime=(double)(finish-start)/CLOCKS_PER_SEC;
         fprintf(stderr,"%f seconds\n",comparetime);
         return 0;
 }

 void dbgmsg(char *fname, int line, char *txt) {
 	fprintf(stderr, "%s/line %d: %s\n", fname, line, txt);
 	fflush(stderr);
 }