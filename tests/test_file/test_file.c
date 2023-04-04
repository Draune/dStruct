#include"../../dStruct/headers/file.h"
#include"test_file.h"
#include"../creer_int.h"
#include<stdio.h>
#include<stdlib.h>

#define VALEUR_TEST 20

void test_file_1(void){
    int* sortie;
    dFile file = d_creer_file();
    for(int i = 0;i<5;i++){
        d_enfiler(&file,creer_int(i));
    }
    d_enfiler(&file,creer_int(VALEUR_TEST));


    int fin = 0;
    while (fin != 1){
        sortie = (int*)d_defiler(&file);
        printf("%d\n",*sortie);
        if (*sortie == VALEUR_TEST)
            fin = 1;
        free(sortie);
    }
    if(d_defiler(&file) == NULL){
        printf("ok\n");
    }

}