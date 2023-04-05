#include "../headers/avl.h"

// /!\ faire les tests de l'ajout d'abord /!\

#define FIXER 1
#define NON_FIXER 0
void fixer(dAVL* avl,dNoeud* noeud);
void tri(dAVL* avl,dNoeud* noeud);
void rotation_droite(dAVL* avl,dNoeud* dessus);
void rotation_gauche(dAVL* avl,dNoeud* dessus);
void set_hauteur(dNoeud* noeud);
int get_diff_hauteur(dNoeud* noeud);
int get_hauteur(dNoeud* noeud);

dNoeud* trouver_remplacement(dNoeud* noeud);
dNoeud* remplacer(dAVL* avl,dNoeud* noeud,dNoeud* remplacement); // la sortie pour le tri

dAVL d_creer_avl(int (*test_tri)(void*,void*)){
    dAVL avl;
    avl.debut = NULL;
    avl.test_tri = test_tri;
    return avl;
}

void d_ajouter_avl(dAVL* avl,void* contenu){
    dNoeud* nouveau = d_creer_dNoeud(contenu);
    fixer(avl,nouveau);
    tri(avl,nouveau);
}

dNoeud* d_trouver_noeud_avl(dAVL* avl,void* contenu){
    if(avl->debut == NULL)
        return NULL;
    dNoeud* return_ = NULL;
    dNoeud* actuel = avl->debut;
    while(actuel != NULL){
        if(avl->test_tri((void*)actuel->contenu,(void*)contenu)){
            return_ = actuel;
            actuel = actuel->droite;
        }
        else
            actuel = actuel->gauche;
    }
    return return_;
}

void* d_trouver_avl(dAVL* avl,void* contenu){
    dNoeud* return_ = d_trouver_noeud_avl(avl,contenu);
    if(return_ == NULL)
        return NULL;
    return (void*)return_->contenu;
}

void* d_retirer_noeud_avl(dAVL* avl,dNoeud* noeud){
    if(noeud == NULL)
        return NULL;
    
    tri(avl,remplacer(avl,noeud,trouver_remplacement(noeud)));
    return d_supprimer_dNoeud(noeud);
}

void* d_retirer_avl(dAVL* avl,void* contenu){
    return (void*)d_retirer_noeud_avl(avl,d_trouver_noeud_avl(avl,contenu));
}

void fixer(dAVL* avl,dNoeud* noeud){
    if(avl->debut == NULL)
        avl->debut = noeud;
    else{
        dNoeud* actuel = avl->debut;
        int fixe = NON_FIXER;
        while(fixe != FIXER){
            if(avl->test_tri((void*)noeud->contenu,(void*)actuel->contenu)){
                if(actuel->gauche == NULL){
                    noeud->precedent = actuel;
                    actuel->gauche = noeud;
                    fixe = FIXER;
                }
                else
                    actuel = actuel->gauche;
            }
            else{
                if(actuel->droite == NULL){
                    noeud->precedent = actuel;
                    actuel->droite = noeud;
                    fixe = FIXER;
                }
                else
                    actuel = actuel->droite;
            }
        }
    }
}

void tri(dAVL* avl,dNoeud* noeud){
    while(noeud != NULL){
        switch (get_diff_hauteur(noeud)){
        case -2:// plus haut a gauche
            if(get_diff_hauteur(noeud->gauche) == 1){// alors desequilibre a gauche puis droite
                noeud = noeud->gauche;
                rotation_gauche(avl,noeud);
                set_hauteur(noeud);
                noeud = noeud->precedent->precedent;
                rotation_droite(avl,noeud);
            }
            else
                rotation_droite(avl,noeud);
            break;
        case 2:// plus haut a droite
            if(get_diff_hauteur(noeud->droite) == -1){// alors desequilibre a droite puis gauche
                noeud = noeud->droite;
                rotation_droite(avl,noeud);
                set_hauteur(noeud);
                noeud = noeud->precedent->precedent;
                rotation_gauche(avl,noeud);
            }
            else
                rotation_gauche(avl,noeud);
            break;
        case -1:
        case 0: // cas normaux
        case 1:
            break;
        default:
            break;
        }
        set_hauteur(noeud);
        noeud = noeud->precedent;
    }
}

void rotation_droite(dAVL* avl,dNoeud* dessus){
    dNoeud* gauche = dessus->gauche;

    if(dessus->precedent != NULL){
        if(dessus->precedent->gauche == dessus)
            dessus->precedent->gauche = gauche;
        else
            dessus->precedent->droite = gauche;
    }
    else
        avl->debut = gauche;
    gauche->precedent = dessus->precedent;

    if(gauche->droite != NULL)
        gauche->droite->precedent = dessus;
    dessus->gauche = gauche->droite;

    dessus->precedent = gauche;
    gauche->droite = dessus;
}

void rotation_gauche(dAVL* avl,dNoeud* dessus){
    dNoeud* droite = dessus->droite;

    if(dessus->precedent != NULL){
        if(dessus->precedent->gauche == dessus)
            dessus->precedent->gauche = droite;
        else
            dessus->precedent->droite = droite;
    }
    else
        avl->debut = droite;
    droite->precedent = dessus->precedent;

    if(droite->gauche != NULL)
        droite->gauche->precedent = dessus;
    dessus->droite = droite->gauche;

    dessus->precedent = droite;
    droite->gauche = dessus;
}

void set_hauteur(dNoeud* noeud){
    noeud->count = (get_hauteur(noeud->droite) > get_hauteur(noeud->gauche))? get_hauteur(noeud->droite):get_hauteur(noeud->gauche);
    (noeud->count)++;
}

int get_diff_hauteur(dNoeud* noeud){
    return get_hauteur(noeud->droite) - get_hauteur(noeud->gauche);
}

int get_hauteur(dNoeud* noeud){
    if(noeud == NULL)
        return 0;
    else
        return noeud->count;
}

dNoeud* trouver_remplacement(dNoeud* noeud){
    if(noeud->droite == NULL && noeud->gauche == NULL)
        return NULL;
    dNoeud* return_;
    if(noeud->droite == NULL){
        return_ = noeud->gauche;
        if(return_->gauche != NULL)
            return_->gauche->precedent = noeud;
        noeud->gauche = return_->gauche;

        if(return_->droite != NULL)
            return_->droite->precedent = noeud;
        noeud->droite = return_->droite;
    }
    else if(noeud->gauche == NULL){
        return_ = noeud->droite;
        if(return_->gauche != NULL)
            return_->gauche->precedent = noeud;
        noeud->gauche = return_->gauche;

        if(return_->droite != NULL)
            return_->droite->precedent = noeud;
        noeud->droite = return_->droite;
    }
    else{
        return_ = noeud->gauche;
        while(return_->droite != NULL)
            return_ = return_->droite;
        
        if(return_->precedent->droite == return_)
            return_->precedent->droite = return_->gauche;
        else
            return_->precedent->gauche = return_->gauche;
        if(return_->gauche != NULL)
            return_->gauche->precedent = return_->precedent;
    }
    return return_;
}

dNoeud* remplacer(dAVL* avl,dNoeud* noeud,dNoeud* remplacement){
    dNoeud* return_;
    if(noeud->precedent != NULL){
        if(noeud->precedent->gauche == noeud)
            noeud->precedent->gauche = remplacement;
        else 
            noeud->precedent->droite = remplacement;
    }
    else
        avl->debut = remplacement;

    if(remplacement == NULL)
        return_ = noeud->precedent;
    else{
        return_ = remplacement->precedent;
        
        remplacement->precedent = noeud->precedent;

        if(noeud->gauche != NULL)
            noeud->gauche->precedent = remplacement;
        remplacement->gauche = noeud->gauche;

        if(noeud->droite != NULL)
            noeud->droite->precedent = remplacement;
        remplacement->droite = noeud->droite;
    }
    return return_;
}