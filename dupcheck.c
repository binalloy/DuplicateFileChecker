#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "skiplist.h"
#include "dupcheck.h"
#include "cmpfile.h"
#include "main.h"

static zskiplist *skiplist;

void print_list(FILE *steam) {
	zskiplistNode *x;
	
	if(skiplist && steam) {
		x = skiplist->header;
		while(x) {
			fprintf(steam, "%lld\t\t%s\n", x->score, x->ele);
			x = x->level[0].forward;
		}
	}
}

int dup_handle(char *ele1, char *ele2) {
	fprintf(stdout, "%s\t%s\n", ele1, ele2);
	return 0;
}

int dupcheck_init() {
	skiplist = zslCreate();
	//WORK_PATH = strdup(path);
	#if DEBUG
    _dbg("zsl is not null")
    #endif
	return 0;
}

int dupcheck(char *path) {
	int64_t size;
	struct stat statbuf;
	zskiplistNode *slnode;
	char *rel_path;
	FILE *log_fp;
	
	/* get file size */
    stat(path,&statbuf);
    size = statbuf.st_size;
	
	/* check duplicate file, if no, save it in the list */
	//rel_path = malloc((strlen(path)-strlen(WORK_PATH)) * sizeof(char));
	//stpcpy(rel_path, path+strlen(WORK_PATH)+1);
	rel_path = strdup(path+strlen(get_WORKPATH()));
	#if DEBUG
	_dbg(path)
	_dbg(rel_path)
	#endif
	if((log_fp = get_logfp())) fprintf(log_fp,"\tChecking: %s\n", rel_path);
	slnode = zslInsert(skiplist, size, rel_path); //return the duplicate one
	#if DEBUG
	_dbg("bbb")
	#endif
	if(slnode) {
		//dup_handle(slnode->ele, rel_path);
		fprintf(stdout, "%s\t%s\n", slnode->ele, rel_path);
	}
	return 0;
}

// int filecmp_caller(char *rel_path1,char *rel_path2,int64_t size) {
// 	char abs_path1[PATH_MAX_LEN];
// 	char abs_path2[PATH_MAX_LEN];
	
// 	strcpy(abs_path1, WORK_PATH);
// 	strcat(abs_path1, rel_path1);
// 	strcpy(abs_path2, WORK_PATH);
// 	strcat(abs_path2, rel_path2);
	
	
	
// 	return 0;
// }
	