#include "../headers/tas.h"
#include "../headers/pile.h"
#include <stdlib.h>

#define GAUCHE 0
#define DROITE 1
dNoeud* emplacement_libre(dTas* tas);
void* creer_direction(int direction);
dNoeud* emplacement_par_num(dTas* tas, int num);
#define CONTINUER 0
#define ARRETER 1
void echanger(dTas* tas,dNoeud* noeud_dessus,dNoeud* noeud_dessous);
int remonter(dTas *tas,dNoeud* noeud);
int descendre(dTas *tas,dNoeud* noeud);

dTas d_creer_tas(int (*test_tri)(void*,void*)){
    dTas tas;
    tas.debut = NULL;
    tas.count = 0;
    tas.test_tri = test_tri;
    return tas;
}

void d_entasser(dTas* tas,void* contenu){
    dNoeud* nouveau = d_creer_dNoeud(contenu);
    if(tas->debut == NULL)
        tas->debut = nouveau;
    else{
        nouveau->precedent = emplacement_libre(tas);
        if(nouveau->precedent->count == GAUCHE)
            nouveau->precedent->gauche = nouveau;
        else
            nouveau->precedent->droite = nouveau;
        while(remonter(tas,nouveau) == CONTINUER){}
    }
    (tas->count)++;
}

void* d_detasser(dTas* tas){
    dNoeud* a_supprimer;
    if(tas->debut == NULL)
        return NULL;
    else if(tas->count == 1){
        a_supprimer = tas->debut;
        tas->debut = NULL;
    }
    else{
        dNoeud* remplacement = emplacement_par_num(tas,tas->count - 1);
    
        if(tas->debut->droite != NULL){
            if(tas->debut->droite == remplacement)
                remplacement->droite = NULL;
            else{
                tas->debut->droite->precedent = remplacement;
                remplacement->droite = tas->debut->droite;
            }
        }
        if(tas->debut->gauche != NULL){
            if(tas->debut->gauche == remplacement)
                remplacement->gauche = NULL;
            else{
                tas->debut->gauche->precedent = remplacement;
                remplacement->gauche = tas->debut->gauche;
            }
        }
        if(remplacement->precedent->gauche == remplacement)
            remplacement->precedent->gauche = NULL;
        else
            remplacement->precedent->droite = NULL;
        remplacement->precedent = NULL;
    
        a_supprimer = tas->debut;
        tas->debut = remplacement;
        while(descendre(tas,remplacement) == CONTINUER){}
    }
    

    (tas->count)--;
    return d_supprimer_dNoeud(a_supprimer);
}


dNoeud* emplacement_libre(dTas* tas){
    dNoeud* return_;
    if(tas->count%2 == 1){
        return_ = emplacement_par_num(tas,(tas->count-1)/2);
        return_->count = GAUCHE;
    }
    else{
        return_ = emplacement_par_num(tas,(tas->count-2)/2);
        return_->count = DROITE;
    }
    return return_;
}

void* creer_direction(int direction){
    int* return_  = (int*)malloc(sizeof(int));
    *return_ = direction;
    return (void*)return_;
}

dNoeud* emplacement_par_num(dTas* tas, int num){
    dPile pile = d_creer_pile();
    int direction;
    while(num != 0){
        if(num%2 == 1){
            num = (num-1)/2;
            direction = GAUCHE;
        }
        else{
            num = (num-2)/2;
            direction = DROITE;
        }
        d_enpiler(&pile,creer_direction(direction));
    }

    dNoeud* return_ = tas->debut;
    while(pile.debut != NULL){
        int* p_direction = (int*)d_depiler(&pile);
        return_ = (*p_direction == GAUCHE)? return_->gauche:return_->droite;
        free(p_direction);
    }

    return return_;
}

void echanger(dTas* tas,dNoeud* noeud_dessus,dNoeud* noeud_dessous){
    dNoeud* tmp;
    if(noeud_dessus->gauche == noeud_dessous){ // noeud du dessous à gauche
        //droite
        tmp = noeud_dessous->droite;

        noeud_dessous->droite = noeud_dessus->droite;
        if(noeud_dessus->droite != NULL)
            noeud_dessus->droite->precedent = noeud_dessous;
        
        noeud_dessus->droite = tmp;
        if(tmp != NULL)
            tmp->precedent = noeud_dessus;

        //gauche
        tmp = noeud_dessous->gauche;

        noeud_dessous->gauche = noeud_dessus;// on modifie le precedent de noeud_dessus apres

        noeud_dessus->gauche = tmp;
        if(tmp != NULL)
            tmp->precedent = noeud_dessus;

        
    }
    else{ // noeud du dessous à droite
        //gauche
        tmp = noeud_dessous->gauche;

        noeud_dessous->gauche = noeud_dessus->gauche;
        if(noeud_dessus->gauche != NULL)
            noeud_dessus->gauche->precedent = noeud_dessous;
        
        noeud_dessus->gauche = tmp;
        if(tmp != NULL)
            tmp->precedent = noeud_dessus;

        //droite
        tmp = noeud_dessous->droite;

        noeud_dessous->droite = noeud_dessus;// on modifie le precedent de noeud_dessus apres

        noeud_dessus->droite = tmp;
        if(tmp != NULL)
            tmp->precedent = noeud_dessus;
    }
    //precedent
    noeud_dessous->precedent = noeud_dessus->precedent;
    if(noeud_dessus->precedent != NULL){
        if(noeud_dessus->precedent->gauche == noeud_dessus)
            noeud_dessus->precedent->gauche = noeud_dessous;
        else
            noeud_dessus->precedent->droite = noeud_dessous;
    }
    else
        tas->debut = noeud_dessous;
        
    noeud_dessus->precedent = noeud_dessous;
}

int remonter(dTas *tas,dNoeud* noeud){
    if((noeud->precedent != NULL) && tas->test_tri((void*)noeud->contenu,(void*)noeud->precedent->contenu)){ // donc noeud doit monter
        echanger(tas,noeud->precedent,noeud);
        return CONTINUER;
    }
    return ARRETER;
}

int descendre(dTas *tas,dNoeud* noeud){
    if(noeud->gauche == NULL && noeud->droite ==NULL){
        return ARRETER;
    }
    else if((noeud->droite != NULL) && ((noeud->gauche == NULL) || tas->test_tri((void*)noeud->droite->contenu,(void*)noeud->gauche->contenu)) && tas->test_tri((void*)noeud->droite->contenu,(void*)noeud->contenu)){
        echanger(tas,noeud,noeud->droite);
        return CONTINUER;
    }
    else if((noeud->gauche != NULL) && tas->test_tri((void*)noeud->gauche->contenu,(void*)noeud->contenu)){
        echanger(tas,noeud,noeud->gauche);
        return CONTINUER;
    }
    return ARRETER;
}