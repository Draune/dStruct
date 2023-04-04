#ifndef DRAUNE_STRUCT_TAS
#define DRAUNE_STRUCT_TAS
#include "maillons.h"

typedef struct{
    dNoeud* debut;
    int count;
    int (*test_tri)(void*,void*);// doit retourner 1 si le premier doit etre au dessus du 2eme
}dTas;

dTas d_creer_tas(int (*test_tri)(void*,void*));
void d_entasser(dTas* tas,void* contenu);
void* d_detasser(dTas* tas);

#endif