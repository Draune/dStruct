#include"test_avl.h"
#include"../../dStruct/headers/avl.h"
#include<stdlib.h>
#include<stdio.h>
#include"../create_int.h"

int sort_int_avl(void* int_1,void* int_2){
    return (*((int*)int_1)<=*((int*)int_2))?1:-1;
}

void test_avl_clear();

#define LOW_VALUE 1
#define AVERAGE_VALUE 2
#define HIGH_VALUE 3
void test_avl_rotate();
void test_avl_rotate_left();
void test_avl_rotate_right_left();
void test_avl_rotate_right();
void test_avl_rotate_left_right();
void test_avl_links(dNode* top,dNode* left,dNode* right);
void test_avl_order(dNode* top,dNode* left,dNode* right);
void test_avl_free(dNode* top,dNode* left,dNode* right);

#define START_VALUE 100
#define INTERMEDIATE_VALUE 20
#define END_VALUE -1
#define FIND_VALUE 17
void test_avl_total();

void test_avl_1(void){
    test_avl_clear();
    test_avl_rotate();
    test_avl_total();
}

void test_avl_clear(){
    dAVL avl = d_init_avl(sort_int_avl);
    for(int i = 0;i<20;i++)
        d_insert_avl(&avl,create_int(i));
    d_clear_avl(&avl,free);
    if(avl.start == NULL)
        printf("test clear ok\n\n");
}

void test_avl_rotate(){
    test_avl_rotate_left();
    test_avl_rotate_right_left();
    test_avl_rotate_right();
    test_avl_rotate_left_right();
}

void test_avl_rotate_left(){
    dAVL avl = d_init_avl(sort_int_avl);
    d_insert_avl(&avl,create_int(LOW_VALUE));
    d_insert_avl(&avl,create_int(AVERAGE_VALUE));
    d_insert_avl(&avl,create_int(HIGH_VALUE));

    dNode* start = avl.start;
    dNode* right = avl.start->right;
    dNode* left = avl.start->left;

    printf("test rotate left\n");
    test_avl_links(start,left,right);
    test_avl_order(start,left,right);
    test_avl_free(start,left,right);
}

void test_avl_rotate_right_left(){
    dAVL avl = d_init_avl(sort_int_avl);
    d_insert_avl(&avl,create_int(LOW_VALUE));
    d_insert_avl(&avl,create_int(HIGH_VALUE));
    d_insert_avl(&avl,create_int(AVERAGE_VALUE));

    dNode* start = avl.start;
    dNode* right = avl.start->right;
    dNode* left = avl.start->left;

    printf("test rotate right left\n");
    test_avl_links(start,left,right);
    test_avl_order(start,left,right);
    test_avl_free(start,left,right);
}

void test_avl_rotate_right(){
    dAVL avl = d_init_avl(sort_int_avl);
    d_insert_avl(&avl,create_int(HIGH_VALUE));
    d_insert_avl(&avl,create_int(AVERAGE_VALUE));
    d_insert_avl(&avl,create_int(LOW_VALUE));

    dNode* start = avl.start;
    dNode* right = avl.start->right;
    dNode* left = avl.start->left;

    printf("test rotate right\n");
    test_avl_links(start,left,right);
    test_avl_order(start,left,right);
    test_avl_free(start,left,right);
}

void test_avl_rotate_left_right(){
    dAVL avl = d_init_avl(sort_int_avl);
    d_insert_avl(&avl,create_int(HIGH_VALUE));
    d_insert_avl(&avl,create_int(LOW_VALUE));
    d_insert_avl(&avl,create_int(AVERAGE_VALUE));

    dNode* start = avl.start;
    dNode* right = avl.start->right;
    dNode* left = avl.start->left;

    printf("test rotate left right\n");
    test_avl_links(start,left,right);
    test_avl_order(start,left,right);
    test_avl_free(start,left,right);
}

void test_avl_links(dNode* top,dNode* left,dNode* right){
    if(left->left == NULL && left->right == NULL && right->left == NULL && right->right == NULL)
        printf("bottom links null\n");
    else
        printf("bottom links not-null\n");
    
    if(top->right == right && right->prev == top)
        printf("links right ok\n");
    else
        printf("links right not-ok\n");

    if(top->left == left && left->prev == top)
        printf("links left ok\n");
    else
        printf("links left not-ok\n");

    if(top->prev == NULL)
        printf("link top null\n");
    else
        printf("link top not-null\n");
}

void test_avl_order(dNode* top,dNode* left,dNode* right){
    int output = *((int*)left->content);
    if(output == LOW_VALUE)
        printf("value left ok\n");
    else
        printf("value left not-ok\n");

    output = *((int*)top->content);
    if(output == AVERAGE_VALUE)
        printf("value top ok\n");
    else
        printf("value top not-ok\n");

    output = *((int*)right->content);
    if(output == HIGH_VALUE)
        printf("value right ok\n");
    else
        printf("value right not-ok\n");
}

void test_avl_free(dNode* top,dNode* left,dNode* right){
    free((int*)top->content);
    free((int*)right->content);
    free((int*)left->content);
    free(top);
    free(right);
    free(left);
}

void test_avl_total(){
    dAVL avl = d_init_avl(sort_int_avl);
    d_insert_avl(&avl,create_int(START_VALUE));
    d_insert_avl(&avl,create_int(INTERMEDIATE_VALUE));
    d_insert_avl(&avl,create_int(END_VALUE));
    d_insert_avl(&avl,create_int(FIND_VALUE));

    for(int i = 10;i<15;i++)
        d_insert_avl(&avl,create_int(i));
    for(int i = 30;i<35;i++)
        d_insert_avl(&avl,create_int(i));

    printf("\ntest total\n\n");

    int input = FIND_VALUE;
    int* output = (int*)d_find_avl(&avl,&input);
    if(*output == FIND_VALUE)
        printf("value find ok\n");
    else
        printf("value find not-ok\n");
    printf("%d\n",*output);

    input = START_VALUE;
    output = (int*)d_remove_avl(&avl,&input);
    if(*output == START_VALUE)
        printf("value start ok\n");
    else
        printf("value start not-ok\n");
    printf("%d\n",*output);

    while(*output != INTERMEDIATE_VALUE){
        free(output);
        output = (int*)d_remove_avl(&avl,&input);
        printf("%d\n",*output);
    }
    
    printf("value interediate ok\n");

    for(int i = 30;i<35;i++)
        d_insert_avl(&avl,create_int(i));

    while (*output != END_VALUE){
        free(output);
        output = (int*)d_remove_avl(&avl,&input);
        printf("%d\n",*output);
    }
    free(output);
    printf("value end ok\n");

    if(d_remove_avl(&avl,&input) == NULL)
        printf("end ok \n");
    else
        printf("end not-ok \n");
}