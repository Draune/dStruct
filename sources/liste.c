#include"../headers/liste.h"

dListe d_creer_liste(int (*test_tri)(void*,void*)){
    dListe liste;
    liste.debut = NULL;
    liste.test_tri = test_tri;
    return liste;
}

void d_ajouter_liste(dListe* liste,void* contenu){
    dDoubleChaine* nouveau = d_creer_dDoubleChaine(contenu);
    if(liste->debut == NULL){
        liste->debut = nouveau;
    }
    else if(liste->test_tri((void*)contenu,(void*)liste->debut->contenu)){
        nouveau->suivant = liste->debut;
        liste->debut->precedent = nouveau;
        liste->debut = nouveau;
    }
    else{
        dDoubleChaine* emplacement = liste->debut;
        while (emplacement->suivant != NULL && liste->test_tri((void*)emplacement->suivant->contenu,(void*)contenu)){
            emplacement = emplacement->suivant;
        }
        
        nouveau->suivant = emplacement->suivant;
        if(emplacement->suivant != NULL)
            emplacement->suivant->precedent = nouveau;
        nouveau->precedent = emplacement;
        emplacement->suivant = nouveau;
    }
}

dDoubleChaine* d_trouver_chaine_liste(dListe* liste,void* contenu){
    dDoubleChaine* trouver = liste->debut;
    while(trouver != NULL && liste->test_tri((void*)trouver->contenu,(void*)contenu))
        trouver = trouver->suivant;
    if(trouver == NULL){
        return NULL;
    }
    return trouver;
}

void* d_trouver_liste(dListe* liste,void* contenu){
    dDoubleChaine* return_ = d_trouver_chaine_liste(liste,contenu);
    if(return_ == NULL)
        return NULL;
    return (void*)return_->contenu;
}

void* d_retirer_chaine_liste(dListe* liste,dDoubleChaine* chaine){
    if(chaine == NULL){
        return NULL;
    }
    if(chaine->precedent != NULL)
        chaine->precedent->suivant = chaine->suivant;
    else
        liste->debut = chaine->suivant;
    if(chaine->suivant != NULL)
        chaine->suivant->precedent = chaine->precedent;

    return d_supprimer_dDoubleChaine(chaine);
}

void* d_retirer_liste(dListe* liste,void* contenu){
    return d_retirer_chaine_liste(liste,d_trouver_chaine_liste(liste,contenu));    
}

void* d_retirer_premier_liste(dListe* liste){
    if(liste->debut == NULL){
        return NULL;
    }
    dDoubleChaine* a_supprimer = liste->debut;
    liste->debut = a_supprimer->suivant;
    if (liste->debut != NULL)
        liste->debut->precedent = NULL;

    return d_supprimer_dDoubleChaine(a_supprimer);
}

