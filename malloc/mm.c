#include "mm.h"

char* heap_listp;
int mm_init()
{
	if ((heap_listp = mem_sbrk(4*WSIZE)) == (void*)-1)
		return -1;

	PUT(heap_listp, 0);
	PUT(heap_listp + (1*WSIZE), PACK(DSIZE,1));
	PUT(heap_listp + (2*WSIZE), PACK(DSIZE,1));
	PUT(heap_listp + (3*WSIZE), PACK(0,1));
	print(heap_listp);
	heap_listp += (2*WSIZE);
	print(heap_listp);


	if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
		return -1;

	return 0;
}
void print(char* x)
{
	int i = 0;
	for(i = 0 ;i < 4*WSIZE;i++)
	{
		printf("%x",x[i]);
		if ((i+1) %4 == 0)
			printf("\t");
	}
	printf("\ti = %d...end\n",i);
}
void *extend_heap(size_t words)
{
	char *bp;
	size_t size;

	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;

	if ((long)(bp = mem_sbrk(size)) == -1)
		return NULL;

	PUT(HDRP(bp), PACK(size,0));
	PUT(FTRP(bp), PACK(size,0));
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0,1));

	return coalesce(bp);
}

void mm_free(void *bp)
{
	size_t size = GET_SIZE(HDRP(bp));
	
	PUT(HDRP(bp), PACK(size,0));
	PUT(FTRP(bp), PACK(size,0));
	coalesce(bp);
}

void *coalesce(void *bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HDRP(bp));

	if (prev_alloc && next_alloc) {
		return bp;
	} else if (prev_alloc && !next_alloc) {
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	} else if (!prev_alloc && next_alloc) {
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	} else{
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
			GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	}

	return bp;
}

void *mm_malloc(size_t size)
{
	size_t asize;
	size_t extendsize;
	char* bp;

	if (size == 0)
		return NULL;

	if (size <= DSIZE)
		asize = 2*DSIZE;
	else
		asize = DSIZE * ((size + (DSIZE) + (DSIZE -1)) / DSIZE);

	if ( (bp = find_fit(asize)) != NULL) {
		place(bp, size);
		return bp;
	}

	extendsize = MAX(asize,CHUNKSIZE);

	if ( (bp = extend_heap(extendsize/WSIZE)) == NULL)
		return NULL;

	place(bp, asize);
	return bp;
}

char* find_fit(size_t size)
{
	return 0;
}

void place(char* i, size_t m)
{
	int x = 0;
}

