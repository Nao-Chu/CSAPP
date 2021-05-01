#include "malloc.h"
#include "mm.h"

int MmInit()
{
	pHeapList = (char *)MemSbrk(4*WSIZE);
	if (pHeapList == (void*)-1)
		return -1;

	Put(pHeapList, 0);
	Put(pHeapList + 1*WSIZE, Pack(DSIZE,1));
	Put(pHeapList + 2*WSIZE, Pack(DSIZE,1));
	Put(pHeapList + 3*WSIZE, Pack(0,1));
	Output(pHeapList);
	pHeapList += 2*WSIZE;
	Output(pHeapList);

	if(ExtendHeap(CHUNKSIZE/WSIZE) == NULL)
		return -1;

	return 0;
}

void *ExtendHeap(size_t words)
{
	char* bp;
	size_t size;

	words = (words+1) & ~(0x1);
	size = words * WSIZE;

	bp = (char*)MemSbrk(size);
	if ((long)bp == -1)
		return NULL;

	Put(HdRP(bp), Pack(size,0));
	Put(FtRP(bp), Pack(size,0));
	Put(HdRP(NextBlkp(bp)), Pack(size,1));

	return Coalesce(bp);

}

void* Coalesce(void* bp)
{
	char* pPrevBlkp = PrevBlkp(bp);
	char* pNextBlkp = NextBlkp(bp);
	size_t prevAlloc = GetAlloc(FtRP(pPrevBlkp));
	size_t nextAlloc = GetAlloc(HdRP(pNextBlkp));
	size_t size = GetSize(HdRP(bp));

	if (prevAlloc && nextAlloc){
		return bp;
	} else if (prevAlloc && !nextAlloc){
		size += GetSize(HdRP(pNextBlkp));
		Put(HdRP(bp), Pack(size,0));
		Put(FtRP(pNextBlkp), Pack(size,0));
		return bp; 
	} else if (!prevAlloc && nextAlloc){
		size += GetSize(HdRP(pPrevBlkp));
		Put(HdRP(pPrevBlkp), Pack(size,0));
		Put(FtRP(bp), Pack(size,0));
		return PrevBlkp(bp);
	} else {
		size += GetSize(HdRP(pPrevBlkp));
		size += GetSize(HdRP(pNextBlkp));
		Put(HdRP(pPrevBlkp), Pack(size,0));
		Put(FtRP(pNextBlkp), Pack(size,0));
		return PrevBlkp(bp);
	}
}

void Output(char* pData)
{
	int i = 0;
	for (;i < 4*WSIZE; i++)
	{
		printf("%x",pData[i]);
		if ((i+1) % 4 == 0)
			printf("\t");
	}
	printf("\ti = %d ... end\n",i);

}

char* FindFit(size_t size)
{
	void *bp;
	size_t iHeadSize = GetSize(HdRP(bp));
	for(bp = pHeapList; iHeadSize > 0;){
		iHeadSize = GetSize(HdRP(bp));
		int iHdRP = GetAlloc(HdRP(bp));
		if (!iHdRP && size <= iHeadSize)
			return (char*)bp;
		bp = NextBlkp(bp);
	}

	return NULL;
}

void place(void* bp, size_t size)
{
	size_t cSize = size - GetSize(HdRP(bp));

	if (cSize >= (2*DSIZE)){
		Put(HdRP(bp), Pack(size, 1));
		Put(FtRP(bp), Pack(size, 1));
		bp = NextBlkp(bp);
		Put(HdRP(bp), Pack(cSize, 0));
		Put(FtRP(bp), Pack(cSize, 0));
	} else {
		Put(HdRP(bp), Pack(size, 1));
		Put(FtRP(bp), Pack(size, 1));
	}
}

void* MmMalloc(size_t size)
{
	size_t aSize;
	char* bp;

	if (size == 0)
		return NULL;

	if (size <= DSIZE)
		aSize = 2*DSIZE;
	else
		aSize = DSIZE*((size + 2*DSIZE -1) / DSIZE);

	bp = FindFit(aSize);
	if (bp != NULL) {
		place(bp, aSize);
		return bp;
	}

	size_t eSize = Max(aSize,CHUNKSIZE);
	bp = (char*)ExtendHeap(eSize/WSIZE);
	if (bp == NULL)
		return NULL;
	
	place(bp, aSize);
	return bp;
}

void MmFree(void* bp)
{
	size_t size = GetSize(HdRP(bp));
	Put(HdRP(bp), Pack(size, 0));
	Put(FtRP(bp), Pack(size, 0));
	Coalesce(bp);
}
