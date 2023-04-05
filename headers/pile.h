#ifndef DRAUNE_STRUCT_PILE
#define DRAUNE_STRUCT_PILE
#include "maillons.h"

typedef struct{
    dChaine* debut;
}dPile;

dPile d_creer_pile();
void d_empiler(dPile* pile,void* contenu);
void* d_depiler(dPile* pile);


#endif