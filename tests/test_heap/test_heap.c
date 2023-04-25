#include"../../dStruct/headers/heap.h"
#include"test_heap.h"
#include"../create_int.h"
#include<stdio.h>
#include<stdlib.h>

#define VALEUR_TEST -1

int sort_int_heap(void* int_1,void* int_2){
    return (*((int*)int_1)>*((int*)int_2))?1:0;
}

void test_heap_1(void){
    int* output;
    dHeap heap = d_init_heap(sort_int_heap);

    d_push_heap(&heap,create_int(VALEUR_TEST));
    for(int i = 0;i<5;i++){
        d_push_heap(&heap,create_int(i));
    }

    int end = 0;
    while (end != 1){
        output = (int*)d_pop_heap(&heap);
        printf("%d\n",*output);
        if (*output == VALEUR_TEST)
            end = 1;
        free(output);
    }
    if(d_pop_heap(&heap) == NULL){
        printf("ok\n");
    }
}