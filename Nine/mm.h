#ifndef _MM_H_
#define _MM_H_

#include <stdio.h>

#define WSIZE	4
#define DSIZE	8
#define CHUNKSIZE (1<<12)

static char* pHeapList;
inline int Max(int x, int y)
{
	return x > y? x : y;
}

inline int Pack(int size, int alloc)
{
	return size | alloc;
}

inline unsigned int Get(char* p)
{
	return *(unsigned int*)p;
}

inline void Put(char* p, int val)
{
	*(unsigned int*)p = val;
}

inline int GetSize(char* p)
{
	return Get(p) & ~0x7;
}

inline int GetAlloc(char* p)
{
	return Get(p) & 0x1;
}

inline char* HdRP(void* bp)
{
	return (char *)bp - WSIZE;
}

inline char* NextBlkp(void* bp)
{
	char* cHead = HdRP(bp);
	size_t iBlkpSize = GetSize(cHead);
	return (char*)bp + iBlkpSize;
}

inline char* FtRP(void* bp)
{
	return NextBlkp(bp) - DSIZE;
}

inline char* PrevBlkp(void* bp)
{
	char* cFoot = (char *)bp - DSIZE;
	size_t iBlkpSize = GetSize(cFoot);
	return (char *)bp - iBlkpSize;
	
}
#endif
