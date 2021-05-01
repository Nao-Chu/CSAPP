#include "malloc.h"
#include <stdlib.h>

void MemInit()
{
	iMaxHeap = 1 << 24;
	pMemHeap = (char *)malloc(iMaxHeap);
	pMemBrk  = (char *)pMemHeap;
	pMemMaxAddr = (char *)(pMemHeap + iMaxHeap);
}

void* MemSbrb(int incr)
{
	char* pOldBrk = pMemBrk;
	if (incr < 0 || (pMemBrk + incr) > pMemMaxAddr)
	{
		printf("add fail\n");
		return (void *)-1;
	}

	pMemBrk += incr;
	return (void*)pOldBrk;
}

