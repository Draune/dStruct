# dStruct
## Description
Bibliothèque de structures de données génériques qui permettent d'éviter de les reprogrammer.

La bibliothèque contient actuellement les structures suivantes :
- Pile (LIFO)
- File (FIFO)
- Liste chaînée (triée)
- Tas
- Arbre AVL
- Vector (un peu comme en C++)
## Utilisation de la bibliothèque
### Ajout à un projet
Pour utiliser la bibliothèque, il faut simplement la clonnée dans le répertoire du projet avec :
```
git clone https://github.com/Draune/dStruct.git
```
Ensuite la lié à votre projet en rajoutant à la fin du CMakeLists.txt de votre projet (cf CMakeLists.txt fait pour les tests de la branche dev) les lignes suivantes :
```
add_subdirectory(dStruct)
target_link_libraries(nom_de_votre_executable dStruct)
```
### Utilisation générale de la bibliothèque
Les noms des structures sont :
- pour la pile : dStack
- pour la file : dQueue
- pour la liste : dList
- pour le tas : dHeap
- pour l'arbre AVL : dAVL
- pour le vector : dVector

Pour initialiser une de ces structures il suffit d'appeler une des fonctions citées ultérieurement qui renvera une structure du type demandé.

Lors de l'ajout d'un élément, on passe en argument à la fonction un pointeur vers la donnée ou vers la structure de donnée que l'on veut stocker.

La suppression d'un élément revoie le pointeur de la donnée stockée (/!\ si la donnée a été allouée dynamiquement, il faudra alors la libérer).

Lorsque l'on supprime alors que la structure est de données est vide, la fonction renvoie NULL.

Toute les structures ont une fonction qui permet de les vider entièrement.

/!\ Il faut mieux évité d'ajouter le pointeur NULL en tant que donnée.

L'utilisation de pointeurs génériques (void*) permet de stocker n'importe quel type de donnée.

Ce système permet de stocker des données de type différent (/!\ il faudra évidemment penser à un moyen de les différenciées).

En plus des exemples donnés ci-dessous, vous pourrez en trouver d'autres dans les tests de la branche dev.

Pour les exemples suivant nous "utiliserons" un type de donnée abstrait : Contenu. Un contenu est libérer de la mémoire avec un simple free et est alloué avec la fonction void* creer_contenu(). La fonction int test_tri_contenu(void* contenu1,void* contenu2) renvoie 1 lorsque contenu1 est plus grand que contenu2.
### Utilisation de la pile
#### Création de la pile
##### Fonction
```
dStack d_init_stack();
```
Renvoie une pile initialisée et vide.
##### Utilisation
```
dStack pile = d_init_stack();
```
#### Ajout dans la pile
##### Fonction
```
void d_push_stack(dStack* stack,void* content);
```
Ajoute dans la pile la donnée "content".
##### Utilisation
En utilisant la pile créée précédemment :
```
d_push_stack(&pile,creer_contenu());
```
#### Suppression dans la pile
##### Fonction
```
void* d_pop_stack(dStack* stack);
```
Retire le dernier élément ajouté à la pile.
##### Utilisation
En utilisant la pile créée précédemment :
```
Contenu* contenu = (Contenu*)d_depiler(&pile);
free(contenu);
```
#### Vider la pile
La fonction suivante permet de vider la pile :
```
void d_clear_stack(dStack* stack,void (*free_content)(void*));
```
Dans notre cas il faudrait passer la fonction free de stdlib.h, sinon mettre la fonction qui permet de liberer la memoire du contenu.
### Utilisation de la file
#### Création de la file
##### Fonction
```
dQueue d_init_queue();
```
Renvoie une file initialisée et vide.
##### Utilisation
```
dQueue file = d_init_queue();
```
#### Ajout dans la file
##### Fonction
```
void d_push_queue(dQueue* queue,void* content)
```
Ajoute dans la file la donnée "content".
##### Utilisation
En utilisant la file créée précédemment :
```
d_push_queue(&file,creer_contenu());
```
#### Suppression dans la file
##### Fonction
```
void* d_pop_queue(dQueue* queue)
```
Retire le premier élément ajouté à la file.
##### Utilisation
En utilisant la file créée précédemment :
```
Contenu* contenu = (Contenu*)d_pop_queue(&file);
free(contenu);
```
#### Vider la file
La fonction suivante permet de vider la file :
```
void d_clear_queue(dQueue* queue,void (*free_content)(void*));
```
Mêmes indications que pour la pile.
### Utilisation de la liste chaînée
#### Création de la liste
##### Fonction
```
dList d_init_list(int (*sort_test)(void*,void*));
```
Renvoie une List initialisée et vide et qui utilise la fonction de tri passé en argument :

La fonction de tri doit renvoyer 1 lorsque le premier contenu (contenu représenté par void*) doit être plus proche du début que le deuxième, 0 si égal et -1 sinon.
##### Utilisation
```
dList liste = d_init_list(test_tri_contenu);
```
On crée alors une liste qui trie les contenus par ordre décroissant.
#### Ajout dans la liste
##### Fonction
```
void d_insert_list(dList* list,void* content);
```
Ajoute dans la liste la donnée "content" (tri lors de l'insertion).
##### Utilisation
En utilisant la liste créée précédemment :
```
d_insert_list(&liste,creer_contenu());
```
#### Recherche dans la liste
##### Fonction
```
dDoubleChain* d_find_chain_list(dList* list,void* content);
void* d_find_list(dList* list,void* content);
```
Renvoient sans supprimer de la chaine l'élément le plus proche du début tel que sort_test(contenu,contenu_passer_en_argument) renvoie 0 ou -1;
#### Suppression dans la liste
##### Fonction
```
void* d_remove_chain_list(dList* list,dDoubleChain* chain);
void* d_remove_list(dList* list,void* content);
void* d_remove_first_list(dList* list);
```
Font la même chose que les fonctions trouver mais en suppriment l'élément de la liste.
##### Utilisation
En utilisant la liste créée précédemment :
```
Contenu* contenu = (Contenu*)d_remove_first_list(&liste);
free(contenu);
```
#### Vider la liste
La fonction suivante permet de vider la liste :
```
void d_clear_list(dList* list,void (*free_content)(void*));
```
Mêmes indications que pour la pile.
### Utilisation du tas
#### Création du tas
##### Fonction
```
dHeap d_init_heap(int (*sort_test)(void*,void*));
```
Renvoie un tas initialisé et vide et qui utilise la fontion de tri test_tri :

Cette fonction de tri doit renvoyer 1 lorsque le premier contenu doit être plus haut dans le tas que le deuxième.
##### Utilisation
```
dHeap tas = d_init_heap(test_tri_contenu);
```
Crée donc un tas qui va ressortir son élément le plus "grand".
#### Ajout dans le tas
##### Fonction
```
void d_push_heap(dHeap* heap,void* content)
```
Ajoute dans le tas la donnée "content" en triant le tas.
##### Utilisation
En utilisant le tas créé précédemment :
```
d_push_heap(&tas,creer_contenu());
```
#### Suppression dans le tas
##### Fonction
```
void* d_pop_heap(dHeap* heap);
```
Retire l'élément le plus haut dans le tas.
##### Utilisation
En utilisant le tas créé précédemment :
```
Contenu* contenu = (Contenu*)d_pop_heap(&tas);
free(contenu);
```
#### Vider le tas
La fonction suivante permet de vider le tas :
```
void d_clear_heap(dHeap* heap,void (*free_content)(void*));
```
Mêmes indications que pour la pile.
### Utilisation de l'arbre AVL
#### Création de l'AVL
##### Fonction
```
dAVL d_init_avl(int (*sort_test)(void*,void*))
```
Renvoie un AVL initialisé et vide et qui utilise la fonction de tri passé en argument :

La fonction de tri doit renvoyer 1 lorsque le premier contenu (contenu représenté par void*) doit être plus à gauche que le deuxième, 0 si égal et -1 sinon.
##### Utilisation
```
dAVL avl = d_init_avl(test_tri_contenu);
```
On crée alors un AVL qui trie les contenus par ordre décroissant (de gauche à droite).
#### Ajout dans l'AVL
##### Fonction
```
void d_insert_avl(dAVL* avl,void* content)
```
Ajoute dans l'AVL la donnée "content" (tri lors de l'insertion).
##### Utilisation
En utilisant l'AVL créé précédemment :
```
d_insert_avl(&avl,creer_contenu());
```
#### Recherche dans l'AVL
##### Fonction
```
dNode* d_find_node_avl(dAVL* avl,void* content);
void* d_find_avl(dAVL* avl,void* content);
```
Renvoient sans supprimer de l'arbre l'élément le plus a droite tel que test_tri(contenu,contenu_passer_en_argument) renvoie 1 ou 0;
#### Suppression dans l'AVL
##### Fonction
```
void* d_remove_node_avl(dAVL* avl,dNode* node);
void* d_remove_avl(dAVL* avl,void* content);
```
Font la même chose que les fonctions trouver mais en suppriment l'élément de l'AVL.
##### Utilisation
En utilisant l'AVL créé précédemment :
```
Contenu* test = creer_contenu();
Contenu* contenu = (Contenu*)d_remove_avl(&avl,test);
free(test);
free(contenu);
```
Va donc renvoyer l'élément le plus proche de test tel que "*contenu >= *test".
#### Vider l'AVL
La fonction suivante permet de vider l'AVL :
```
void d_clear_avl(dAVL* avl,void (*free_content)(void*));
```
Mêmes indications que pour la pile.
### Utilisation du vector
Le vector est un tableau de pointeurs vers les données, donc les données doivent être allouées dynamiquement.
#### Création du vector
```
dVector d_init_vector(unsigned int size);
```
Renvoie un vector de la taille de size initialisé à NULL;
#### Ajout dans un vector
```
void d_push_back_vector(dVector* vector,void* content);
void d_insert_vector(dVector* vector,unsigned int i,void* content);
```
d_push_back_vector ajoute à la fin en augmentant la taille du vector et d_insert_vector ajoute à l'emplacement i à condition que celui-ci soit vide et que i < vector->size.
#### Parcourir le vector
```
void* d_access_vector(dVector* vector,unsigned int i);
```
Renvoie la donnée de la case i sans la supprimer du vector.

Pour parcourir le vector on peut faire :
```
for(int i = 0;i<vector.size;i++){
    print_contenu(d_access_vector(&vector,i));
}
```
#### Suppression dans le vector
```
void* d_pop_back_vector(dVector* vector);
void* d_remove_vector(dVector* vector,unsigned int i);
```
Les deux fonctions renvoient un pointeur sur la donnée qui a été retirée du vector, d_pop_back_vector retire la dernière donnée en réduisant la taille du vector et d_remove_vector retire la donnée de la case i.