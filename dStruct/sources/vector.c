#include"../headers/vector.h"
#include<math.h>
#include<stdlib.h>

dVector d_init_vector(unsigned int size){
    dVector vector;

    if(size != 0){
        double double_real_size_pow = log2((double)size);
        unsigned int int_real_size_pow = (int)double_real_size_pow;
        if(double_real_size_pow != (double)int_real_size_pow)
            int_real_size_pow++;
        vector.real_size = (unsigned int)pow(2.0,(double)int_real_size_pow);
        vector.size = size;
        vector.content_array = malloc(vector.real_size * sizeof(void*));
        for(int i  = 0;i<vector.real_size;i++)
            vector.content_array[i] = NULL;
    }
    else{
        vector.real_size = 0;
        vector.size = 0;
        vector.content_array = NULL;
    }
    
    return vector;
}

void d_push_back_vector(dVector* vector,void* content){
    if(vector->real_size == 0){
        vector->real_size = 1;
        vector->content_array = malloc(vector->real_size*sizeof(void*));
        vector->content_array[0] = NULL;
    }
    else if(vector->size == vector->real_size){
        vector->real_size *= 2;
        vector->content_array = realloc(vector->content_array,vector->real_size*sizeof(void*));
        for(int i = vector->size;i<vector->real_size;i++)
            vector->content_array[i] = NULL;
    }

    (vector->size)++;
    d_insert_vector(vector,vector->size-1,content);
}

void* d_pop_back_vector(dVector* vector){
    if(vector->size == 0)
        return NULL;

    void* _return = d_remove_vector(vector,vector->size-1);
    if(vector->size == 1){
        free(vector->content_array);
        *vector = d_init_vector(0);
        (vector->size)++;
    }
    else if(vector->size < vector->real_size/3){
        vector->real_size /= 2;
        vector->content_array = realloc(vector->content_array,vector->real_size*sizeof(void*));
    }
    (vector->size)--;
    return _return;
}

void* d_access_vector(dVector* vector,unsigned int i){
    return (i >= vector->size)? NULL:vector->content_array[i];
}

void d_insert_vector(dVector* vector,unsigned int i,void* content){
    if(i < vector->size && vector->content_array[i] == NULL)
        vector->content_array[i] = content;
}

void* d_remove_vector(dVector* vector,unsigned int i){
    void* _return;
    if(i < vector->size){
        _return = vector->content_array[i];
        vector->content_array[i] = NULL;
    }
    else
        _return = NULL;
    return _return;
}

void d_clear_vector(dVector* vector,void (*free_content)(void*)){
    for(int i = 0;i<vector->size;i++){
        void* access = d_access_vector(vector,i);
        if(access != NULL)
            free_content(access);
    }
    free(vector->content_array);

    *vector = d_init_vector(0);
}