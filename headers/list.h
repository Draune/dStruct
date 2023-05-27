#ifndef DRAUNE_STRUCT_LIST
#define DRAUNE_STRUCT_LIST
#include "link.h"

typedef struct
{
    dDoubleChain *start;
    int (*sort_test)(void *, void *);
    /* must return : 1 if the 1st have to be before the 2nd
                     0 if they're equals
                     -1 else*/
} dList;

dList d_init_list(int (*sort_test)(void *, void *));
int d_insert_list(dList *list, void *content);
dDoubleChain *d_find_chain_list(dList *list, void *content);
void *d_find_list(dList *list, void *content);
dDoubleChain *d_find_eq_chain_list(dList *list, void *content);
void *d_find_eq_list(dList *list, void *content);
void *d_remove_chain_list(dList *list, dDoubleChain *chain);
void *d_remove_list(dList *list, void *content);
void *d_remove_first_list(dList *list);
int d_clear_list(dList *list, void (*free_content)(void *));

#endif