#include"../headers/link.h"
#include <stdlib.h>

dChain* d_create_chain(void* content){
    dChain* return_ = (dChain*)malloc(sizeof(dChain));
    return_->content = content;
    return_->next = NULL;
    return return_;
}

dDoubleChain* d_create_double_chain(void* content){
    dDoubleChain* return_ = (dDoubleChain*)malloc(sizeof(dDoubleChain));
    return_->content = content;
    return_->next = NULL;
    return_->prev = NULL;
    return return_;
}

dNode* d_create_node(void* content){
    dNode* return_ = (dNode*)malloc(sizeof(dNode));
    return_->content = content;
    return_->left = NULL;
    return_->right = NULL;
    return_->prev = NULL;
    return return_;
}

void* d_destroy_chain(dChain* chain){
    void* return_ = chain->content;
    free(chain);
    return return_;
}

void* d_destroy_double_chain(dDoubleChain* double_chain){
    void* return_ = double_chain->content;
    free(double_chain);
    return return_;
}

void* d_destroy_node(dNode* node){
    void* return_ = node->content;
    free(node);
    return return_;
}