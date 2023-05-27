#ifndef DRAUNE_STRUCT_QUEUE
#define DRAUNE_STRUCT_QUEUE
#include "link.h"

typedef struct
{
    dChain *start;
    dChain *end;
} dQueue;

dQueue d_init_queue();
int d_push_queue(dQueue *queue, void *content);
void *d_pop_queue(dQueue *queue);
int d_clear_queue(dQueue *queue, void (*free_content)(void *));

#endif