#include "../headers/file.h"

dFile d_creer_file(){
    dFile file;
    file.debut = NULL;
    file.fin = NULL;
    return file;
}

void d_enfiler(dFile* file,void* contenu){
    dChaine* nouveau = d_creer_dChaine(contenu);
    if(file->debut == NULL){
        file->debut = nouveau;
        file->fin = nouveau;
    }
    else{
        file->fin->suivant = nouveau;
        file->fin = file->fin->suivant;
    }
}

void* d_defiler(dFile* file){
    dChaine* a_supprimer = file->debut;
    if(a_supprimer == NULL){
        return NULL;
    }
    if(a_supprimer->suivant == NULL){
        file->fin = NULL;
    }
    file->debut = a_supprimer->suivant;
    return d_supprimer_dChaine(a_supprimer);
}