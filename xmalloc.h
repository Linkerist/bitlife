
#ifndef __XMALLOC_H__
#define __XMALLOC_H__

/* number of directory entries to initialize allocatation */
#define MEM_INIT 32
/* allocatation increment */
#define MEM_INC_STEP 32

void *xmalloc(size_t size);
void *xrealloc(void *old, size_t size)

#endif
