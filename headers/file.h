#ifndef DRAUNE_STRUCT_FILE
#define DRAUNE_STRUCT_FILE
#include "maillons.h"

typedef struct{
    dChaine* debut;
    dChaine* fin;
}dFile;

dFile d_creer_file();
void d_enfiler(dFile* file,void* contenu);
void* d_defiler(dFile* file);

#endif