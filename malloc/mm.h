#ifndef _MM_H_
#define _MM_H_

#include <stdio.h>
#define WSIZE	4
#define DSIZE	8
#define CHUNKSIZE	(1<<12)

#define MAX(x,y)	((x) > (y)? (x) : (y))

#define PACK(size, alloc) ((size) | (alloc))

#define GET(p)		(*(unsigned int *)(p))
#define PUT(p, val)	(*(unsigned int *)(p) = (val))

#define GET_SIZE(p)	(GET(p) & ~0x7)
#define GET_ALLOC(p)	(GET(p) & 0x1)

#define HDRP(bp)	((char *)(bp) - WSIZE)
#define FTRP(bp)	((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp)	((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)	((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

#define MAX_HEAP	(1 << 15)	
void mem_init();
void *mem_sbrk(int incr);
static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

int mm_init();
void *extend_heap(size_t words);
void *coalesce(void *bp);
char* find_fit(size_t size);
void place(char*,size_t);
void print(char*);
#endif
