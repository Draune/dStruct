#ifndef DRAUNE_STRUCT_LISTE
#define DRAUNE_STRUCT_LISTE
#include "maillons.h"

typedef struct{
    dDoubleChaine* debut;
    int (*test_tri)(void*,void*);// doit retourner 1 si le premier doit etre plus proche du debut que le 2eme
}dListe;

dListe d_creer_liste(int (*test_tri)(void*,void*));
void d_ajouter_liste(dListe* liste,void* contenu);
dDoubleChaine* d_trouver_chaine_liste(dListe* liste,void* contenu);
void* d_trouver_liste(dListe* liste,void* contenu);
void* d_retirer_chaine_liste(dListe* liste,dDoubleChaine* chaine);
void* d_retirer_liste(dListe* liste,void* contenu);
void* d_retirer_premier_liste(dListe* liste);


#endif