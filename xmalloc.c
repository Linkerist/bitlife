
#include <stdlib.h>
#include <stdio.h>

void *xmalloc(size_t size)
{
	register void *ptr = malloc(size);
	if(0 == ptr) {
		fprintf(stderr, "bitlife : virtual memory exhausted .\n");
		exit(1);
	}
	return ptr;
}

void *xrealloc(void *old, size_t size)
{
	register void *ptr = realloc(old, size);
	if(0 == ptr) {
		fprintf(stderr, "bitlife : virtual memory exhausted .\n");
		exit(1);
	}
	return ptr;
}
