#ifndef DRAUNE_DSTRUCT_AVL
#define DRAUNE_DSTRUCT_AVL
#include "link.h"

typedef struct{
    dNode* start;
    int (*sort_test)(void*,void*);
    /* must return : 1 if the 1st have to be more on the left than the 2nd
                     0 if they're equals
                     -1 else*/
}dAVL;

dAVL d_init_avl(int (*sort_test)(void*,void*));
void d_insert_avl(dAVL* avl,void* content);
// find the node the more on the right which will be on the left of content
// return NULL if no one can be on the left of content
dNode* d_find_node_avl(dAVL* avl,void* content);
void* d_find_avl(dAVL* avl,void* content);
dNode* d_find_eq_node_avl(dAVL* avl,void* content);
void* d_find_eq_avl(dAVL* avl,void* content);
void* d_remove_node_avl(dAVL* avl,dNode* node);
void* d_remove_avl(dAVL* avl,void* content);
void d_clear_avl(dAVL* avl,void (*free_content)(void*));

#endif