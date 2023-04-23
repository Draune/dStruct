#ifndef DRAUNE_STRUCT_LINK
#define DRAUNE_STRUCT_LINK
#include <stddef.h>

typedef struct dChain{
    void* content;
    struct dChain* next;
}dChain;

typedef struct dDoubleChain{
    void* content;
    struct dDoubleChain* next;
    struct dDoubleChain* prev;
}dDoubleChain;

typedef struct dNode{
    void* content;
    int count;
    struct dNode* left;
    struct dNode* right;
    struct dNode* prev;
}dNode;

dChain* d_create_chain(void* content);
dDoubleChain* d_create_double_chain(void* content);
dNode* d_create_node(void* content);

void* d_destroy_chain(dChain* chain);
void* d_destroy_double_chain(dDoubleChain* double_chain);
void* d_destroy_node(dNode* node);

#endif