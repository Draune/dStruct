#ifndef DRAUNE_AVL
#define DRAUNE_AVL
#include "maillons.h"

typedef struct{
    dNoeud* debut;
    int (*test_tri)(void*,void*);// doit retourner 1 si le premier doit etre plus à gauche que le 2eme
}dAVL;

dAVL d_creer_avl(int (*test_tri)(void*,void*));
void d_ajouter_avl(dAVL* avl,void* contenu);
dNoeud* d_trouver_noeud_avl(dAVL* avl,void* contenu);//trouve le noeud le plus a droite qui serait a gauche de contenu
// retourne NULL si aucun ne peu etre a gauche de contenu
void* d_trouver_avl(dAVL* avl,void* contenu);
void* d_retirer_noeud_avl(dAVL* avl,dNoeud* noeud);
void* d_retirer_avl(dAVL* avl,void* contenu);

#endif