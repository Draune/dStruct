#ifndef DRAUNE_STRUCT_STACK
#define DRAUNE_STRUCT_STACK
#include "link.h"

typedef struct{
    dChain* start;
}dStack;

dStack d_init_stack();
void d_push_stack(dStack* stack,void* content);
void* d_pop_stack(dStack* stack);
void d_clear_stack(dStack* stack,void (*free_content)(void*));


#endif