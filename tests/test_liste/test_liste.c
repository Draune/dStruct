#include"test_liste.h"
#include"../creer_int.h"
#include"../../dStruct/headers/liste.h"
#include<stdlib.h>
#include<stdio.h>

#define VALEUR_TEST_FIN -1
#define VALEUR_TEST_RETIRER_PREMIER 100
#define VALEUR_TEST_TROUVER 2
#define VALEUR_TEST_SUPPRIMER 3

int tri_int_liste(void* int_1,void* int_2){
    return (*((int*)int_1)>*((int*)int_2))?1:0; // cf liste.h (retourner 1 si le premier doit etre plus proche du debut)
    // donc tas trié en ordre decroissant
}

void test_liste_1(void){
    int* sortie;
    dListe liste = d_creer_liste(tri_int_liste);

    d_ajouter_liste(&liste,creer_int(VALEUR_TEST_FIN));
    d_ajouter_liste(&liste,creer_int(VALEUR_TEST_RETIRER_PREMIER));
    for(int i = 0;i<5;i++){
        d_ajouter_liste(&liste,creer_int(i));
    }

    int test = VALEUR_TEST_TROUVER;
    sortie = (int*)d_trouver_liste(&liste,(void*)&test);
    printf("%d\n",*sortie);
    if(*sortie == VALEUR_TEST_TROUVER)
        printf("trouver ok\n");
    test = VALEUR_TEST_SUPPRIMER;
    sortie = (int*)d_retirer_liste(&liste,(void*)&test);
    printf("%d\n",*sortie);
    if(*sortie == VALEUR_TEST_SUPPRIMER)
        printf("retirer ok\n");
    free(sortie);
    sortie = (int*)d_retirer_premier_liste(&liste);
    printf("%d\n",*sortie);
    if(*sortie == VALEUR_TEST_RETIRER_PREMIER)
        printf("retirer premier ok\n");
    free(sortie);

    int fin = 0;
    while (fin != 1){
        sortie = (int*)d_retirer_premier_liste(&liste);
        printf("%d\n",*sortie);
        if (*sortie == VALEUR_TEST_FIN)
            fin = 1;
        free(sortie);
    }
    test = VALEUR_TEST_FIN;
    if(d_retirer_premier_liste(&liste) == NULL && d_retirer_liste(&liste,&test) == NULL){
        printf("ok\n");
    }
}