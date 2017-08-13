#include <stdio.h>
#include <string.h>
#include "skiplist.h"
#include "dupcheck.h"

static zskiplist *skiplist;
static char *work_path;

int dup_handle(char *ele1, char *ele2) {
	fprintf(stdout, "%s\t%s\n", ele1, ele2);
	return 0;
}

int dupcheck_init(char *path) {
	skiplist = zslCreate();
	work_path = strdup(path);
	return 0;
}

int dupcheck(char *path) {
	int64_t size;
	struct stat statbuf;
	zskiplistNode *slnode;
	char *rel_path;
	
	/* get file size */
    stat(path,&statbuf);
    size = statbuf.st_size;
	
	/* check duplicate file, if no, save it in the list */
	//rel_path = malloc((strlen(path)-strlen(work_path)) * sizeof(char));
	//stpcpy(rel_path, path+strlen(work_path)+1);
	rel_path = strdup(path+strlen(work_path)+1);
	slnode = zslInsert(skiplist, size, rel_path); //return the duplicate one
	if(slnode) {
		//dup_handle(slnode->ele, rel_path);
		fprintf(stdout, "%s\t%s\n", slnode->ele, rel_path);
	}
	
	return 0;
}

int filecmp_caller(char *rel_path1,char *rel_path2) {
	char *abs_path1[512];
	char *abs_path2[512];
	
	strcpy(abs_path1, work_path);
	strcat(abs_path1, rel_path1);
	strcpy(abs_path2, work_path);
	strcat(abs_path2, rel_path2);
	
	
	
	return 0;
}
	