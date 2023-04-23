#include"test_list.h"
#include"../create_int.h"
#include"../../dStruct/headers/list.h"
#include<stdlib.h>
#include<stdio.h>

#define END_TEST_VALUE -1
#define FIRST_REMOVE_TEST_VALUE 100
#define FIND_TEST_VALUE 2
#define REMOVE_TEST_VALUE 3

int sort_int_list(void* int_1,void* int_2){
    return (*((int*)int_1)>*((int*)int_2))?1:0;
}

void test_list_1(void){
    int* output;
    dList list = d_create_list(sort_int_list);

    d_insert_list(&list,create_int(END_TEST_VALUE));
    d_insert_list(&list,create_int(FIRST_REMOVE_TEST_VALUE));
    for(int i = 0;i<5;i++){
        d_insert_list(&list,create_int(i));
    }

    int test = FIND_TEST_VALUE;
    output = (int*)d_find_list(&list,(void*)&test);
    printf("%d\n",*output);
    if(*output == FIND_TEST_VALUE)
        printf("find ok\n");
    test = REMOVE_TEST_VALUE;
    output = (int*)d_remove_list(&list,(void*)&test);
    printf("%d\n",*output);
    if(*output == REMOVE_TEST_VALUE)
        printf("remove ok\n");
    free(output);
    output = (int*)d_remove_first_list(&list);
    printf("%d\n",*output);
    if(*output == FIRST_REMOVE_TEST_VALUE)
        printf("remove first ok\n");
    free(output);

    int end = 0;
    while (end != 1){
        output = (int*)d_remove_first_list(&list);
        printf("%d\n",*output);
        if (*output == END_TEST_VALUE)
            end = 1;
        free(output);
    }
    test = END_TEST_VALUE;
    if(d_remove_first_list(&list) == NULL && d_remove_list(&list,&test) == NULL){
        printf("ok\n");
    }
}