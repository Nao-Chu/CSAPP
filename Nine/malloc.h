#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
static char *pMemHeap;
static char *pMemBrk;
static char *pMemMaxAddr;
static unsigned int iMaxHeap;

void MemInit();
void *MemSbrk(int incr);

int MmInit();
void* MmMalloc();
void MmFree(void *bp);
void *ExtendHeap(size_t words);
void *Coalesce(void *bp);
char *FindFit(size_t size);
void Place(void* bp, size_t size);
void Output(char* pData);

#endif
