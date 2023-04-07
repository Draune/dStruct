# dStruct
## Description
Bibliothèque de structures de données génériques qui permettent d'éviter de les reprogrammer.

La bibliothèque contient actuellement les structures suivantes :
- Pile
- File
- Liste chaînée
- Tas
- Arbre AVL
## Utilisation de la bibliothèque
### Ajout à un projet
Pour utiliser la bibliothèque, il faut simplement la clonnée dans le répertoire du projet avec :
'''
git clone https://github.com/Draune/dStruct.git
'''
Ensuite la lié à votre projet en rajoutant à la fin du CMakeLists.txt de votre projet (cf CMakeLists.txt fait pour les tests de la branche dev) les lignes suivantes :
'''
add_subdirectory(dStruct)
target_link_libraries(nom_de_votre_executable dStruct)
'''
### Utilisation générale de la bibliothèque
Les noms des structures sont :
- pour la pile : dPile
- pour la file : dFile
- pour la liste : dListe
- pour le tas : dTas
- pour l'arbre AVL : dAVL

Pour initialiser une de ces structures il suffit d'appeler une des fonctions citées ultérieurement qui renvera une structure du type demandé.

Lors de l'ajout d'un élément, on passe en argument à la fonction un pointeur vers la donnée ou vers la structure de donnée que l'on veut stocker.

La suppression d'un élément revoie le pointeur de la donnée stockée (/!\ si la donnée a été allouée dynamiquement, il faudra alors la libérer).

Lorsque l'on supprime alors que la structure est de données est vide, la fonction renvoie NULL, ainsi on peut utiliser cela pour vider la structure de la manière suivante :
'''
pointeur_sortie = d_supprimer...(...);
while(pointeur_sortie != NULL){
    liberer_memoire_sortie(pointeur_sortie);
    pointeur_sortie = d_supprimer...(...);
}
'''
Avec pointeur_sortie un pointeur de votre type de donnée et liberer_memoire_sortie() une fonction qui libère la mémoire utilisée par votre donnée.

/!\ Il faut alors mieux évité d'ajouter le pointeur NULL en tant que donnée.

L'utilisation de pointeurs génériques (void*) permet de stocker n'importe quel type de donnée.

Ce système permet de stocker des données de type différent (/!\ il faudra évidemment penser à un moyen de les différenciées).

En plus des exemples donnés ci-dessous, vous pourrez en trouver d'autres dans les tests de la branche dev.

Pour les exemples suivant nous "utiliserons" un type de donnée abstrait : Contenu. Un contenu est libérer de la mémoire avec un simple free et est alloué avec la fonction void* creer_contenu(). La fonction int test_tri_contenu(void* contenu1,void* contenu2) renvoie 1 lorsque contenu1 est plus grand que contenu2.
### Utilisation de la pile
#### Création de la pile
##### Fonction
'''
dPile d_creer_pile(void)
'''
Renvoie une pile initialisée et vide.
##### Utilisation
'''
dPile pile = d_creer_pile();
'''
#### Ajout dans la pile
##### Fonction
'''
void d_empiler(dPile* pile,void* contenu)
'''
Ajoute dans la pile la donnée "contenu".
##### Utilisation
En utilisant la pile créée précédemment :
'''
d_empiler(&pile,creer_contenu());
'''
#### Suppression dans la pile
##### Fonction
'''
void* d_depiler(dPile* pile)
'''
Retire le dernier élément ajouté à la pile.
##### Utilisation
En utilisant la pile créée précédemment :
'''
Contenu* contenu = (Contenu*)d_depiler(&pile);
free(contenu);
'''
### Utilisation de la file
#### Création de la file
##### Fonction
'''
dFile d_creer_file(void)
'''
Renvoie une file initialisée et vide.
##### Utilisation
'''
dFile file = d_creer_file();
'''
#### Ajout dans la file
##### Fonction
'''
void d_enfiler(dFile* file,void* contenu)
'''
Ajoute dans la file la donnée "contenu".
##### Utilisation
En utilisant la file créée précédemment :
'''
d_enfiler(&file,creer_contenu());
'''
#### Suppression dans la file
##### Fonction
'''
void* d_defiler(dFile* file)
'''
Retire le premier élément ajouté à la file.
##### Utilisation
En utilisant la file créée précédemment :
'''
Contenu* contenu = (Contenu*)d_defiler(&file);
free(contenu);
'''
### Utilisation de la liste chaînée
#### Création de la liste
##### Fonction
'''
dListe d_creer_liste(int (*test_tri)(void*,void*))
'''
Renvoie une Liste initialisée et vide et qui utilise la fonction de tri passé en argument :

La fonction de tri doit renvoyer 1 lorsque le premier contenu (contenu représenté par void*) doit être plus proche du début que le deuxième, 0 sinon.
##### Utilisation
'''
dListe liste = d_creer_liste(test_tri_contenu);
'''
On crée alors une liste qui trie les contenus par ordre décroissant.
#### Ajout dans la liste
##### Fonction
'''
void d_ajouter_liste(dListe* liste,void* contenu)
'''
Ajoute dans la liste la donnée "contenu" (tri lors de l'insertion).
##### Utilisation
En utilisant la liste créée précédemment :
'''
d_ajouter_liste(&liste,creer_contenu());
'''
#### Recherche dans la liste
##### Fonction
'''
dDoubleChaine* d_trouver_chaine_liste(dListe* liste,void* contenu)
void* d_trouver_liste(dListe* liste,void* contenu)
'''
Renvoient sans supprimer de la chaine l'élément le plus proche du début tel que test_tri(contenu,contenu_passer_en_argument) renvoie 0;
#### Suppression dans la liste
##### Fonction
'''
void* d_retirer_chaine_liste(dListe* liste,dDoubleChaine* chaine)
void* d_retirer_liste(dListe* liste,void* contenu)
void* d_retirer_premier_liste(dListe* liste)
'''
Font la même chose que les fonctions trouver mais en suppriment l'élément de la liste.
##### Utilisation
En utilisant la liste créée précédemment :
'''
Contenu* contenu = (Contenu*)d_retirer_premier_liste(&liste);
free(contenu);
'''
### Utilisation du tas
#### Création du tas
##### Fonction
'''
dTas d_creer_tas(int (*test_tri)(void*,void*))
'''
Renvoie un tas initialisé et vide et qui utilise la fontion de tri test_tri :

Cette fonction de tri doit renvoyer 1 lorsque le premier contenu doit être plus haut dans le tas que le deuxième.
##### Utilisation
'''
dTas tas = d_creer_tas(test_tri_contenu);
'''
Crée donc un tas qui va ressortir son élément le plus "grand".
#### Ajout dans le tas
##### Fonction
'''
void d_entasser(dTas* tas,void* contenu)
'''
Ajoute dans le tas la donnée "contenu" en triant le tas.
##### Utilisation
En utilisant le tas créé précédemment :
'''
d_entasser(&tas,creer_contenu());
'''
#### Suppression dans le tas
##### Fonction
'''
void* d_detasser(dTas* tas)
'''
Retire l'élément le plus haut dans le tas.
##### Utilisation
En utilisant le tas créé précédemment :
'''
Contenu* contenu = (Contenu*)d_detasser(&tas);
free(contenu);
'''
### Utilisation de l'arbre AVL
#### Création de l'AVL
##### Fonction
'''
dAVL d_creer_avl(int (*test_tri)(void*,void*))
'''
Renvoie un AVL initialisé et vide et qui utilise la fonction de tri passé en argument :

La fonction de tri doit renvoyer 1 lorsque le premier contenu (contenu représenté par void*) doit être plus à gauche que le deuxième, 0 sinon.
##### Utilisation
'''
dAVL avl = d_creer_avl(test_tri_contenu);
'''
On crée alors un AVL qui trie les contenus par ordre décroissant (de gauche à droite).
#### Ajout dans l'AVL
##### Fonction
'''
void d_ajouter_avl(dAVL* avl,void* contenu)
'''
Ajoute dans l'AVL la donnée "contenu" (tri lors de l'insertion).
##### Utilisation
En utilisant l'AVL créé précédemment :
'''
d_ajouter_avl(&avl,creer_contenu());
'''
#### Recherche dans l'AVL
##### Fonction
'''
dNoeud* d_trouver_noeud_avl(dAVL* avl,void* contenu)
void* d_trouver_avl(dAVL* avl,void* contenu)
'''
Renvoient sans supprimer de l'arbre l'élément le plus a droite tel que test_tri(contenu,contenu_passer_en_argument) renvoie 1;
#### Suppression dans l'AVL
##### Fonction
'''
void* d_retirer_noeud_avl(dAVL* avl,dNoeud* noeud);
void* d_retirer_avl(dAVL* avl,void* contenu);
'''
Font la même chose que les fonctions trouver mais en suppriment l'élément de la liste.
##### Utilisation
En utilisant le tas créé précédemment :
'''
Contenu* test = creer_contenu();
Contenu* contenu = (Contenu*)d_retirer_avl(&avl,test);
free(test);
free(contenu);
'''
Va donc renvoyer l'élément le plus proche de test tel que "*contenu >= *test".