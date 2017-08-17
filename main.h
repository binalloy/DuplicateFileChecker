#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>

#define PATH_MAX_LEN 512

#define DEBUG 0
#define _dbg(msg) do{dbgmsg(__FILE__,__LINE__, msg);}while(0);

char *get_WORKPATH();
FILE *get_logfp();

void dbgmsg(char *fname, int line, char *txt);

#endif
