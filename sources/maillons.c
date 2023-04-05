#include"../headers/maillons.h"
#include <stdlib.h>

dChaine* d_creer_dChaine(void* contenu){
    dChaine* return_ = (dChaine*)malloc(sizeof(dChaine));
    return_->contenu = contenu;
    return_->suivant = NULL;
    return return_;
}

dDoubleChaine* d_creer_dDoubleChaine(void* contenu){
    dDoubleChaine* return_ = (dDoubleChaine*)malloc(sizeof(dDoubleChaine));
    return_->contenu = contenu;
    return_->suivant = NULL;
    return_->precedent = NULL;
    return return_;
}

dNoeud* d_creer_dNoeud(void* contenu){
    dNoeud* return_ = (dNoeud*)malloc(sizeof(dNoeud));
    return_->contenu = contenu;
    return_->gauche = NULL;
    return_->droite = NULL;
    return_->precedent = NULL;
    return return_;
}

void* d_supprimer_dChaine(dChaine* chaine){
    void* return_ = chaine->contenu;
    free(chaine);
    return return_;
}

void* d_supprimer_dDoubleChaine(dDoubleChaine* double_chaine){
    void* return_ = double_chaine->contenu;
    free(double_chaine);
    return return_;
}

void* d_supprimer_dNoeud(dNoeud* noeud){
    void* return_ = noeud->contenu;
    free(noeud);
    return return_;
}