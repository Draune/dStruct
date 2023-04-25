#include"../../dStruct/headers/queue.h"
#include"test_queue.h"
#include"../create_int.h"
#include<stdio.h>
#include<stdlib.h>

#define TEST_VALUE 20

void test_queue_1(void){
    int* output;
    dQueue queue = d_init_queue();
    for(int i = 0;i<5;i++){
        d_push_queue(&queue,create_int(i));
    }
    d_push_queue(&queue,create_int(TEST_VALUE));


    int end = 0;
    while (end != 1){
        output = (int*)d_pop_queue(&queue);
        printf("%d\n",*output);
        if (*output == TEST_VALUE)
            end = 1;
        free(output);
    }
    if(d_pop_queue(&queue) == NULL){
        printf("ok\n");
    }

}