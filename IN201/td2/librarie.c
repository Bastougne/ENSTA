#include <assert.h>
#include <stdio.h>

#define v2

#ifdef v1
char heap[16 * 1024];
void *p = &heap;

void *memalloc( size_t size ) {
    assert( p + size <= (void *)&heap + 16 * 1024 );
    p += size;
}

void memfree( void *ptr ) {}

void meminit() {}
#endif

#ifdef v2
char heap[16 * 1024];
void *p = &heap;

struct free_list {
    void *pointer;
    size_t size;
    struct free_list *next;
};

struct free_list liste;

void *memalloc( size_t size ) {
    struct free_list *zone = &liste;
    while () {
    }
}

void memfree( void *ptr ) {
}

void meminit() {
    liste.pointer = &heap;
    liste.size = 16 * 1024;
}
#endif