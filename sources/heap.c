#include "../headers/heap.h"
#include "../headers/stack.h"
#include <stdlib.h>

#define LEFT 0
#define RIGHT 1
dNode* free_location(dHeap* heap);
void* create_direction(int direction);
dNode* location_per_num(dHeap* heap, int num);
#define CONTINUE 0
#define STOP 1
void exchange(dHeap* heap,dNode* top_node,dNode* bottom_node);
int go_up(dHeap *heap,dNode* node);
int go_down(dHeap *heap,dNode* node);

dHeap d_init_heap(int (*sort_test)(void*,void*)){
    dHeap heap;
    heap.start = NULL;
    heap.count = 0;
    heap.sort_test = sort_test;
    return heap;
}

void d_push_heap(dHeap* heap,void* content){
    dNode* new = d_create_node(content);
    if(heap->start == NULL)
        heap->start = new;
    else{
        new->prev = free_location(heap);
        if(new->prev->count == LEFT)
            new->prev->left = new;
        else
            new->prev->right = new;
        while(go_up(heap,new) == CONTINUE){}
    }
    (heap->count)++;
}

void* d_pop_heap(dHeap* heap){
    dNode* to_delete;
    if(heap->start == NULL)
        return NULL;
    else if(heap->count == 1){
        to_delete = heap->start;
        heap->start = NULL;
    }
    else{
        dNode* replacement = location_per_num(heap,heap->count - 1);
    
        if(heap->start->right != NULL){
            if(heap->start->right == replacement)
                replacement->right = NULL;
            else{
                heap->start->right->prev = replacement;
                replacement->right = heap->start->right;
            }
        }
        if(heap->start->left != NULL){
            if(heap->start->left == replacement)
                replacement->left = NULL;
            else{
                heap->start->left->prev = replacement;
                replacement->left = heap->start->left;
            }
        }
        if(replacement->prev->left == replacement)
            replacement->prev->left = NULL;
        else
            replacement->prev->right = NULL;
        replacement->prev = NULL;
    
        to_delete = heap->start;
        heap->start = replacement;
        while(go_down(heap,replacement) == CONTINUE){}
    }
    

    (heap->count)--;
    return d_destroy_node(to_delete);
}

void d_clear_heap(dHeap* heap,void (*free_content)(void*)){
    while(heap->start != NULL){
        void* to_delete = d_pop_heap(heap);
        if(to_delete != NULL)
            free_content(to_delete);
    } 
}

dNode* free_location(dHeap* heap){
    dNode* return_;
    if(heap->count%2 == 1){
        return_ = location_per_num(heap,(heap->count-1)/2);
        return_->count = LEFT;
    }
    else{
        return_ = location_per_num(heap,(heap->count-2)/2);
        return_->count = RIGHT;
    }
    return return_;
}

void* create_direction(int direction){
    int* return_  = (int*)malloc(sizeof(int));
    *return_ = direction;
    return (void*)return_;
}

dNode* location_per_num(dHeap* heap, int num){
    dStack stack = d_init_stack();
    int direction;
    while(num != 0){
        if(num%2 == 1){
            num = (num-1)/2;
            direction = LEFT;
        }
        else{
            num = (num-2)/2;
            direction = RIGHT;
        }
        d_push_stack(&stack,create_direction(direction));
    }

    dNode* return_ = heap->start;
    while(stack.start != NULL){
        int* p_direction = (int*)d_pop_stack(&stack);
        return_ = (*p_direction == LEFT)? return_->left:return_->right;
        free(p_direction);
    }

    return return_;
}

void exchange(dHeap* heap,dNode* top_node,dNode* bottom_node){
    dNode* tmp;
    if(top_node->left == bottom_node){ // bottom_node is on the left
        //right
        tmp = bottom_node->right;

        bottom_node->right = top_node->right;
        if(top_node->right != NULL)
            top_node->right->prev = bottom_node;
        
        top_node->right = tmp;
        if(tmp != NULL)
            tmp->prev = top_node;

        //left
        tmp = bottom_node->left;

        bottom_node->left = top_node;// we edit the top_node's prev after

        top_node->left = tmp;
        if(tmp != NULL)
            tmp->prev = top_node;

        
    }
    else{ // bottom_node is on the right
        //left
        tmp = bottom_node->left;

        bottom_node->left = top_node->left;
        if(top_node->left != NULL)
            top_node->left->prev = bottom_node;
        
        top_node->left = tmp;
        if(tmp != NULL)
            tmp->prev = top_node;

        //right
        tmp = bottom_node->right;

        bottom_node->right = top_node;// we edit the top_node's prev after

        top_node->right = tmp;
        if(tmp != NULL)
            tmp->prev = top_node;
    }
    //prev
    bottom_node->prev = top_node->prev;
    if(top_node->prev != NULL){
        if(top_node->prev->left == top_node)
            top_node->prev->left = bottom_node;
        else
            top_node->prev->right = bottom_node;
    }
    else
        heap->start = bottom_node;
        
    top_node->prev = bottom_node;
}

int go_up(dHeap *heap,dNode* node){
    if((node->prev != NULL) && heap->sort_test((void*)node->content,(void*)node->prev->content)){ // so node go_up
        exchange(heap,node->prev,node);
        return CONTINUE;
    }
    return STOP;
}

int go_down(dHeap *heap,dNode* node){
    if(node->left == NULL && node->right ==NULL){
        return STOP;
    }
    else if((node->right != NULL) && ((node->left == NULL) || heap->sort_test((void*)node->right->content,(void*)node->left->content)) && heap->sort_test((void*)node->right->content,(void*)node->content)){
        exchange(heap,node,node->right);
        return CONTINUE;
    }
    else if((node->left != NULL) && heap->sort_test((void*)node->left->content,(void*)node->content)){
        exchange(heap,node,node->left);
        return CONTINUE;
    }
    return STOP;
}