#include<stdlib.h>
#include"creer_int.h"

void* creer_int(int num){
    int* return_ = (int*)malloc(sizeof(int));
    *return_ = num;
    return (void*)return_;
}