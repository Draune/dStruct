#include"test_avl.h"
#include"../../dStruct/headers/avl.h"
#include<stdlib.h>
#include<stdio.h>
#include"../creer_int.h"

int tri_int_avl(void* int_1,void* int_2){
    return (*((int*)int_1)<=*((int*)int_2))?1:0; // cf avl.h (retourner 1 si le premier doit etre plus a gauche)
    // donc tas trié en ordre croissant
}

#define VALEUR_FAIBLE 1
#define VALEUR_MOYENNE 2
#define VALEUR_FORTE 3
void test_avl_rotations();
void test_avl_rotation_gauche();
void test_avl_rotation_droite_gauche();
void test_avl_rotation_droite();
void test_avl_rotation_gauche_droite();
void test_avl_liaisons(dNoeud* dessus,dNoeud* gauche,dNoeud* droite);
void test_avl_ordre(dNoeud* dessus,dNoeud* gauche,dNoeud* droite);
void test_avl_liberer(dNoeud* dessus,dNoeud* gauche,dNoeud* droite);

#define VALEUR_DEBUT 100
#define VALEUR_INTERMEDIAIRE 20
#define VALEUR_FIN -1
#define VALEUR_TROUVER 17
void test_avl_total();

void test_avl_1(void){
    test_avl_rotations();
    test_avl_total();
}

void test_avl_rotations(){
    test_avl_rotation_gauche();
    test_avl_rotation_droite_gauche();
    test_avl_rotation_droite();
    test_avl_rotation_gauche_droite();
}

void test_avl_rotation_gauche(){
    dAVL avl = d_creer_avl(tri_int_avl);
    d_ajouter_avl(&avl,creer_int(VALEUR_FAIBLE));
    d_ajouter_avl(&avl,creer_int(VALEUR_MOYENNE));
    d_ajouter_avl(&avl,creer_int(VALEUR_FORTE));

    dNoeud* debut = avl.debut;
    dNoeud* droite = avl.debut->droite;
    dNoeud* gauche = avl.debut->gauche;

    printf("test rotation gauche\n");
    test_avl_liaisons(debut,gauche,droite);
    test_avl_ordre(debut,gauche,droite);
    test_avl_liberer(debut,gauche,droite);
}

void test_avl_rotation_droite_gauche(){
    dAVL avl = d_creer_avl(tri_int_avl);
    d_ajouter_avl(&avl,creer_int(VALEUR_FAIBLE));
    d_ajouter_avl(&avl,creer_int(VALEUR_FORTE));
    d_ajouter_avl(&avl,creer_int(VALEUR_MOYENNE));

    dNoeud* debut = avl.debut;
    dNoeud* droite = avl.debut->droite;
    dNoeud* gauche = avl.debut->gauche;

    printf("test rotation droite gauche\n");
    test_avl_liaisons(debut,gauche,droite);
    test_avl_ordre(debut,gauche,droite);
    test_avl_liberer(debut,gauche,droite);
}

void test_avl_rotation_droite(){
    dAVL avl = d_creer_avl(tri_int_avl);
    d_ajouter_avl(&avl,creer_int(VALEUR_FORTE));
    d_ajouter_avl(&avl,creer_int(VALEUR_MOYENNE));
    d_ajouter_avl(&avl,creer_int(VALEUR_FAIBLE));

    dNoeud* debut = avl.debut;
    dNoeud* droite = avl.debut->droite;
    dNoeud* gauche = avl.debut->gauche;

    printf("test rotation droite\n");
    test_avl_liaisons(debut,gauche,droite);
    test_avl_ordre(debut,gauche,droite);
    test_avl_liberer(debut,gauche,droite);
}

void test_avl_rotation_gauche_droite(){
    dAVL avl = d_creer_avl(tri_int_avl);
    d_ajouter_avl(&avl,creer_int(VALEUR_FORTE));
    d_ajouter_avl(&avl,creer_int(VALEUR_FAIBLE));
    d_ajouter_avl(&avl,creer_int(VALEUR_MOYENNE));

    dNoeud* debut = avl.debut;
    dNoeud* droite = avl.debut->droite;
    dNoeud* gauche = avl.debut->gauche;

    printf("test rotation gauche droite\n");
    test_avl_liaisons(debut,gauche,droite);
    test_avl_ordre(debut,gauche,droite);
    test_avl_liberer(debut,gauche,droite);
}

void test_avl_liaisons(dNoeud* dessus,dNoeud* gauche,dNoeud* droite){
    if(gauche->gauche == NULL && gauche->droite == NULL && droite->gauche == NULL && droite->droite == NULL)
        printf("liaisons basses nulles\n");
    else
        printf("liaisons basses non-nulles\n");
    
    if(dessus->droite == droite && droite->precedent == dessus)
        printf("liaisons droite ok\n");
    else
        printf("liaisons droite non-ok\n");

    if(dessus->gauche == gauche && gauche->precedent == dessus)
        printf("liaisons gauche ok\n");
    else
        printf("liaisons gauche non-ok\n");

    if(dessus->precedent == NULL)
        printf("liaison haute nulle\n");
    else
        printf("liaison haute non-nulle\n");
}

void test_avl_ordre(dNoeud* dessus,dNoeud* gauche,dNoeud* droite){
    int sortie = *((int*)gauche->contenu);
    if(sortie == VALEUR_FAIBLE)
        printf("valeur gauche ok\n");
    else
        printf("valeur gauche non-ok\n");

    sortie = *((int*)dessus->contenu);
    if(sortie == VALEUR_MOYENNE)
        printf("valeur dessus ok\n");
    else
        printf("valeur dessus non-ok\n");

    sortie = *((int*)droite->contenu);
    if(sortie == VALEUR_FORTE)
        printf("valeur droite ok\n");
    else
        printf("valeur droite non-ok\n");
}

void test_avl_liberer(dNoeud* dessus,dNoeud* gauche,dNoeud* droite){
    free((int*)dessus->contenu);
    free((int*)droite->contenu);
    free((int*)gauche->contenu);
    free(dessus);
    free(droite);
    free(gauche);
}

void test_avl_total(){
    dAVL avl = d_creer_avl(tri_int_avl);
    d_ajouter_avl(&avl,creer_int(VALEUR_DEBUT));
    d_ajouter_avl(&avl,creer_int(VALEUR_INTERMEDIAIRE));
    d_ajouter_avl(&avl,creer_int(VALEUR_FIN));
    d_ajouter_avl(&avl,creer_int(VALEUR_TROUVER));

    for(int i = 10;i<15;i++)
        d_ajouter_avl(&avl,creer_int(i));
    for(int i = 30;i<35;i++)
        d_ajouter_avl(&avl,creer_int(i));

    printf("\ntest total\n\n");

    int entree = VALEUR_TROUVER;
    int* sortie = (int*)d_trouver_avl(&avl,&entree);
    if(*sortie == VALEUR_TROUVER)
        printf("valeur trouver ok\n");
    else
        printf("valeur trouver non-ok\n");
    printf("%d\n",*sortie);

    entree = VALEUR_DEBUT;
    sortie = (int*)d_retirer_avl(&avl,&entree);
    if(*sortie == VALEUR_DEBUT)
        printf("valeur debut ok\n");
    else
        printf("valeur debut non-ok\n");
    printf("%d\n",*sortie);

    while(*sortie != VALEUR_INTERMEDIAIRE){
        free(sortie);
        sortie = (int*)d_retirer_avl(&avl,&entree);
        printf("%d\n",*sortie);
    }
    
    printf("valeur intermediaire ok\n");

    for(int i = 30;i<35;i++)
        d_ajouter_avl(&avl,creer_int(i));

    while (*sortie != VALEUR_FIN){
        free(sortie);
        sortie = (int*)d_retirer_avl(&avl,&entree);
        printf("%d\n",*sortie);
    }
    free(sortie);
    printf("valeur fin ok\n");

    if(d_retirer_avl(&avl,&entree) == NULL)
        printf("fini ok \n");
    else
        printf("fini non-ok \n");
}