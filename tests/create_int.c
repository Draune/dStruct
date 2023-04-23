#include<stdlib.h>
#include"create_int.h"

void* create_int(int num){
    int* return_ = (int*)malloc(sizeof(int));
    *return_ = num;
    return (void*)return_;
}