#include "ch.h"
#include "jhc_rts_header.h"

#define MALLOC_HEAPSIZE (2*1024)
static char malloc_heapstart[MALLOC_HEAPSIZE];
static MemoryHeap heap_desc;

void malloc_init(void) {
	chHeapInit(&heap_desc, (void *)malloc_heapstart, MALLOC_HEAPSIZE);
}

void *malloc(size_t size) {
	return chHeapAlloc(&heap_desc, size);
}

void free(void *ptr) {
	chHeapFree(ptr);
}

void *realloc(void *optr, size_t size)
{
	void *nptr = malloc(size);

	if (NULL != optr) {
		// bcopy(optr, nptr, size); // xxx
		free(optr);
	}
	return nptr;
}

void abort() {
	for (;;);
}

void exit(int status) {
	abort();
}

void *memalign(size_t __alignment, size_t __size) {
	abort();
}

char *setlocale(int category, const char *locale) {
	return NULL;
}

int jhc_printf_stderr(const char *format, ...) {
	return 0;
}

int jhc_fputs_stderr(const char *s) {
	return 0;
}

int jhc_fflush_stdout() {
	return 0;
}

void jhc_print_profile(void) {
}

int jhc_utf8_getchar(void) {
	return 0;
}

int jhc_utf8_getc(FILE *f)  {
	return 0;
}

int jhc_utf8_putchar(int ch)  {
	return 0;
}

int jhc_utf8_putc(int ch, FILE *f)  {
	return 0;
}

