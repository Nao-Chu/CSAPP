#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "mm.h"

char* memxx;

void mem_init(void)
{
	mem_heap = (char*)malloc(MAX_HEAP);	
	mem_brk  = (char*)mem_heap;	
	mem_max_addr = (char*)(mem_heap + MAX_HEAP);	
	memxx = mem_heap;
}

void *mem_sbrk(int incr)
{
	char* old_brk = mem_brk;
	if ( (incr < 0) || ((mem_brk + incr) > mem_max_addr))
	{
		errno = ENOMEM;
		printf("error\n");
		return (void*) -1;
	}

	mem_brk += incr;
	return (void*)old_brk;
}

