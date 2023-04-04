#include"../../dStruct/headers/pile.h"
#include"test_pile.h"
#include"../creer_int.h"
#include<stdio.h>
#include<stdlib.h>

#define VALEUR_TEST 20

void test_pile_1(void){
    int* sortie;
    dPile pile = d_creer_pile();

    d_enpiler(&pile,creer_int(VALEUR_TEST));
    for(int i = 0;i<5;i++){
        d_enpiler(&pile,creer_int(i));
    }

    int fin = 0;
    while (fin != 1){
        sortie = (int*)d_depiler(&pile);
        printf("%d\n",*sortie);
        if (*sortie == VALEUR_TEST)
            fin = 1;
        free(sortie);
    }
    if(d_depiler(&pile) == NULL){
        printf("ok\n");
    }

}