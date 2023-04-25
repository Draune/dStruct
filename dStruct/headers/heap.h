#ifndef DRAUNE_STRUCT_HEAP
#define DRAUNE_STRUCT_HEAP
#include "link.h"

typedef struct{
    dNode* start;
    int count;
    int (*sort_test)(void*,void*);// must return 1 if the 1st have to be on top of the 2nd
}dHeap;

dHeap d_init_heap(int (*sort_test)(void*,void*));
void d_push_heap(dHeap* heap,void* content);
void* d_pop_heap(dHeap* heap);
void d_clear_heap(dHeap* heap,void (*free_content)(void*));

#endif