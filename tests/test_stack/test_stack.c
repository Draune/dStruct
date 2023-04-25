#include"../../dStruct/headers/stack.h"
#include"test_stack.h"
#include"../create_int.h"
#include<stdio.h>
#include<stdlib.h>

#define TEST_VALUE 20

void test_stack_1(void){
    int* output;
    dStack stack = d_init_stack();

    d_push_stack(&stack,create_int(TEST_VALUE));
    for(int i = 0;i<5;i++){
        d_push_stack(&stack,create_int(i));
    }

    int end = 0;
    while (end != 1){
        output = (int*)d_pop_stack(&stack);
        printf("%d\n",*output);
        if (*output == TEST_VALUE)
            end = 1;
        free(output);
    }
    if(d_pop_stack(&stack) == NULL){
        printf("ok\n");
    }

}