#include <stdio.h>
#include "mm.h"

extern char* memxx;
int main()
{
	mem_init();
	printf("heap = %s\n", memxx);
	mm_init();
}
