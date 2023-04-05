#include "../headers/pile.h"

dPile d_creer_pile(){
    dPile pile;
    pile.debut = NULL;
    return pile;
}

void d_enpiler(dPile* pile,void* contenu){
    dChaine* nouveau = d_creer_dChaine(contenu);
    nouveau->suivant = pile->debut;
    pile->debut = nouveau;
}

void* d_depiler(dPile* pile){
    dChaine* a_supprimer = pile->debut;
    if(a_supprimer == NULL){
        return NULL;
    }
    pile->debut = a_supprimer->suivant;
    return d_supprimer_dChaine(a_supprimer);
}