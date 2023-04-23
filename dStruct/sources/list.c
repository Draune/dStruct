#include"../headers/list.h"

dList d_create_list(int (*sort_test)(void*,void*)){
    dList list;
    list.start = NULL;
    list.sort_test = sort_test;
    return list;
}

void d_insert_list(dList* list,void* content){
    dDoubleChain* new = d_create_double_chain(content);
    if(list->start == NULL){
        list->start = new;
    }
    else if(list->sort_test((void*)content,(void*)list->start->content)){
        new->next = list->start;
        list->start->prev = new;
        list->start = new;
    }
    else{
        dDoubleChain* location = list->start;
        while (location->next != NULL && list->sort_test((void*)location->next->content,(void*)content)){
            location = location->next;
        }
        
        new->next = location->next;
        if(location->next != NULL)
            location->next->prev = new;
        new->prev = location;
        location->next = new;
    }
}

dDoubleChain* d_find_chain_list(dList* list,void* content){
    dDoubleChain* find = list->start;
    while(find != NULL && list->sort_test((void*)find->content,(void*)content))
        find = find->next;
    if(find == NULL){
        return NULL;
    }
    return find;
}

void* d_find_list(dList* list,void* content){
    dDoubleChain* return_ = d_find_chain_list(list,content);
    if(return_ == NULL)
        return NULL;
    return (void*)return_->content;
}

void* d_remove_chain_list(dList* list,dDoubleChain* chain){
    if(chain == NULL){
        return NULL;
    }
    if(chain->prev != NULL)
        chain->prev->next = chain->next;
    else
        list->start = chain->next;
    if(chain->next != NULL)
        chain->next->prev = chain->prev;

    return d_destroy_double_chain(chain);
}

void* d_remove_list(dList* list,void* content){
    return d_remove_chain_list(list,d_find_chain_list(list,content));    
}

void* d_remove_first_list(dList* list){
    if(list->start == NULL){
        return NULL;
    }
    dDoubleChain* to_delete = list->start;
    list->start = to_delete->next;
    if (list->start != NULL)
        list->start->prev = NULL;

    return d_destroy_double_chain(to_delete);
}

void* d_clear_list(dList* list,void (*free_content)(void*)){
    while(list->start != NULL){
        void* to_delete = d_remove_first_list(list);
        if(to_delete != NULL)
            free_content(to_delete);
    }
}