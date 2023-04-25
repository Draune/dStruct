#include "../headers/stack.h"

dStack d_init_stack(){
    dStack stack;
    stack.start = NULL;
    return stack;
}

void d_push_stack(dStack* stack,void* contenu){
    dChain* new = d_create_chain(contenu);
    new->next = stack->start;
    stack->start = new;
}

void* d_pop_stack(dStack* stack){
    dChain* to_delete = stack->start;
    if(to_delete == NULL){
        return NULL;
    }
    stack->start = to_delete->next;
    return d_destroy_chain(to_delete);
}

void d_clear_stack(dStack* stack,void (*free_content)(void*)){
    while(stack->start != NULL){
        void* to_delete = d_pop_stack(stack);
        if(to_delete != NULL)
            free_content(to_delete);
    }
}