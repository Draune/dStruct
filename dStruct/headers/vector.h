#ifndef DRAUNE_DSTRUCT_VECTOR
#define DRAUNE_DSTRUCT_VECTOR

typedef struct{
    void** content_array;
    unsigned int size;
    unsigned int real_size;
}dVector;

dVector d_init_vector(unsigned int size);
void d_push_back_vector(dVector* vector,void* content);
void* d_pop_back_vector(dVector* vector);
void* d_access_vector(dVector* vector,unsigned int i);
// /!\ d_insert_vector will not add content if i > vector->size or if the i th case of vector 
// is not empty (vector->content_array[i] != NULL)
void d_insert_vector(dVector* vector,unsigned int i,void* content);
void* d_remove_vector(dVector* vector,unsigned int i);
void d_clear_vector(dVector* vector,void (*free_content)(void*));

#endif