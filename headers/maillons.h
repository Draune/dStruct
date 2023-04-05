#ifndef DRAUNE_STRUCT_MAILLONS
#define DRAUNE_STRUCT_MAILLONS
#include <stddef.h>

typedef struct dChaine{
    void* contenu;
    struct dChaine* suivant;
}dChaine;

typedef struct dDoubleChaine{
    void* contenu;
    struct dDoubleChaine* suivant;
    struct dDoubleChaine* precedent;
}dDoubleChaine;

typedef struct dNoeud{
    void* contenu;
    int count;
    struct dNoeud* gauche;
    struct dNoeud* droite;
    struct dNoeud* precedent;
}dNoeud;

dChaine* d_creer_dChaine(void* contenu);
dDoubleChaine* d_creer_dDoubleChaine(void* contenu);
dNoeud* d_creer_dNoeud(void* contenu);

void* d_supprimer_dChaine(dChaine* chaine);
void* d_supprimer_dDoubleChaine(dDoubleChaine* double_chaine);
void* d_supprimer_dNoeud(dNoeud* noeud);

#endif