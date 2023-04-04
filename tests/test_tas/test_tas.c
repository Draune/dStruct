#include"../../dStruct/headers/tas.h"
#include"test_tas.h"
#include"../creer_int.h"
#include<stdio.h>
#include<stdlib.h>

#define VALEUR_TEST -1

int tri_int_tas(void* int_1,void* int_2){
    return (*((int*)int_1)>*((int*)int_2))?1:0; // cf tas.h (retourner 1 si le premier doit etre au dessus)
    // donc tas trié en ordre decroissant
}

void test_tas_1(void){
    int* sortie;
    dTas tas = d_creer_tas(tri_int_tas);

    d_entasser(&tas,creer_int(VALEUR_TEST));
    for(int i = 0;i<5;i++){
        d_entasser(&tas,creer_int(i));
    }

    int fin = 0;
    while (fin != 1){
        sortie = (int*)d_detasser(&tas);
        printf("%d\n",*sortie);
        if (*sortie == VALEUR_TEST)
            fin = 1;
        free(sortie);
    }
    if(d_detasser(&tas) == NULL){
        printf("ok\n");
    }
}