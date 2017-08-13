#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#include <stdint.h>

#define ZSKIPLIST_MAXLEVEL 32 /* Should be enough for 2^32 elements */
#define ZSKIPLIST_P 0.5      /* Skiplist P = 1/2 */

#define sds char*
#define zmalloc malloc
#define zfree free
#define sdsfree free
#define sdscmp cmpfile

typedef struct zskiplistNode {
    sds ele;
    int64_t score;
    struct zskiplistNode *backward;
    struct zskiplistLevel {
        struct zskiplistNode *forward;
        unsigned int span;
    } level[];
} zskiplistNode;
 
typedef struct zskiplist {
    struct zskiplistNode *header, *tail;
    unsigned long length;
    int level;
} zskiplist;

zskiplist *zslCreate(void);
void zslFree(zskiplist *zsl);
zskiplistNode *zslInsert(zskiplist *zsl, int64_t score, sds ele);
int zslDelete(zskiplist *zsl, int64_t score, sds ele, zskiplistNode **node);
unsigned long zslGetRank(zskiplist *zsl, int64_t score, sds ele);

#endif