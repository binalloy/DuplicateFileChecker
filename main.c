//group members:11510257 彭福，11510746张晓文，11611601何海彬
#include "main.h"
#include "dupcheck.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "tdir.h"
#include <dirent.h>

static char WORK_PATH[PATH_MAX_LEN];
static FILE *log_fp = NULL;

void print_usage(char *program_name) {
	fprintf(stderr, "Usage: %s [-l [log_file_path]] to_be_scaned_path\n", program_name);
	fprintf(stderr, "\t-l [log_file_path]    Output log file. If no path behind, infomation will directly output to stderr.\n");
}

int main(int argc, char *argv[]) {      //clock_t start;
	clock_t finish;
	//start=clock();
	double comparetime;
	char *tmp;
	DIR  *pDir ;
	int opt;

	while((opt = getopt(argc, argv, "l:")) != -1) {
		switch (opt) {
		case 'l':
			if(optarg) {
				log_fp = fopen(optarg, "w");
				if(!log_fp) {
					fprintf(stderr, "ERROR: log file open fail.");
					exit(EXIT_FAILURE);
				}
			}
			break;
		default: /* '?' */
			print_usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	
	/* check work path */
	if(optind == argc) {
        print_usage(argv[0]);
		exit(EXIT_FAILURE);
    }
	pDir = opendir(argv[optind]);
	if(NULL == pDir) {
		fprintf(stderr,"Sorry! Dirent error:\n\
PATH : \"%s\" cannot be opened by \"opendir function\" or does not exist.\nPlease reboot this programe and enter a correct file path.\n\
Exit the program.\n", argv[optind]);
		exit(EXIT_FAILURE);
	} else {
		/* set work path */
		if(strlen(argv[optind]) >= PATH_MAX_LEN-1) {
			fprintf(stderr, "ERROR: scan path open fail.");
			exit(EXIT_FAILURE);
		} else {
			strcpy(WORK_PATH,argv[optind]);
			tmp = WORK_PATH;
			while(*(tmp)) tmp++;
			if((*(tmp-1)) != '/') {
				*(tmp) = '/';
				*(tmp+1) = '\0';
			}
		}
	}

	dupcheck_init();
	listDir(WORK_PATH);
	
	#if DEBUG
	print_list(stderr);
	if(log_fp) print_list(log_fp);
	#endif

	finish=clock();
	comparetime=(double)(finish)/CLOCKS_PER_SEC;
	fprintf(stderr,"scaning finished!it has token %f seconds CPU time.\n",comparetime);
	closedir(pDir);
	fclose(log_fp);
	return 0;
}

char *get_WORKPATH() {return WORK_PATH;}

FILE *get_logfp() {return log_fp;}

void dbgmsg(char *fname, int line, char *txt) {
	fprintf(stderr, "%s/line %d: %s\n", fname, line, txt);
	fflush(stderr);
}
