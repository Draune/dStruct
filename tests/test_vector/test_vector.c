#include"../../dStruct/headers/vector.h"
#include"test_vector.h"
#include"../create_int.h"
#include<stdio.h>
#include<stdlib.h>

void test_create();
void test_access_insert_remove();
void test_push_pop_back();

void test_vector_1(){
    test_create();
    test_access_insert_remove();
    test_push_pop_back();
}

void test_create(){
    printf("test_create\n");

    dVector vector = d_create_vector(1);
    printf("%d\t%d\n",vector.size,vector.real_size);
    d_clear_vector(&vector,free);

    vector = d_create_vector(13);
    printf("%d\t%d\n",vector.size,vector.real_size);
    d_clear_vector(&vector,free);

    printf("end test_create\n\n");
}

void test_access_insert_remove(){
    printf("test_access_insert_remove\n");

    dVector vector = d_create_vector(13);
    int is_null = 1;
    for (int i = 0;i<vector.size;i++){
        if(d_access_vector(&vector,i) != NULL)
            is_null = 0;
    }
    printf((is_null)?"access NULL ok\n":"access NULL not-ok\n");

    for(int i = 0;i<5;i++){
        d_insert_vector(&vector,i,create_int(i));
    }
    for (int i = 0;i<vector.size;i++){
        if(d_access_vector(&vector,i) != NULL)
            printf("%d\n",*((int*)d_access_vector(&vector,i)));
        else
            printf("NULL\n");
    }

    int* test = create_int(2);
    d_insert_vector(&vector,1,test);
    if(*((int*)d_access_vector(&vector,1)) == 1)
        printf("insert ok\n");
    else 
        printf("insert not-ok\n");
    free(test);

    test = d_remove_vector(&vector,1);
    printf("%d\n",*test);
    free(test);

    d_remove_vector(&vector,14);
    d_remove_vector(&vector,-1);
    d_remove_vector(&vector,100);

    test = create_int(10);
    d_insert_vector(&vector,14,test);
    d_insert_vector(&vector,-1,test);
    d_insert_vector(&vector,100,test);

    printf("result test_access_insert_remove\n");
    for(int i = 0;i<vector.size;i++){
        if(d_access_vector(&vector,i) != NULL)
            printf("%d\n",*((int*)d_access_vector(&vector,i)));
        else
            printf("NULL\n");
    }

    d_clear_vector(&vector,free);
    
    printf("end test_access_insert_remove\n\n");
}

void test_push_pop_back(){
    printf("test_push_pop\n");

    dVector vector = d_create_vector(0);
    printf("%d\t%d\n",vector.size,vector.real_size);
    for(int i = 0;i<10;i++){
        d_push_back_vector(&vector,create_int(i));
        printf("%d:\t%d\t%d\n",i,vector.size,vector.real_size);
    }

    for (int i = 0;i<vector.size;i++){
        if(d_access_vector(&vector,i) != NULL)
            printf("%d\n",*((int*)d_access_vector(&vector,i)));
        else
            printf("NULL\n");
    }

    int* test = d_pop_back_vector(&vector);
    
    while(test != NULL){
        printf("%d:\t%d\t%d\n",*test,vector.size,vector.real_size);
        free(test);
        test = d_pop_back_vector(&vector);
    }
    printf("end test_push_pop\n");
}

