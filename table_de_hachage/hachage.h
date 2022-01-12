#ifndef _HACHAGE_H_
#define _HACHAGE_H_
#include "../liste_chainee/list.h"

struct _list_node;
typedef struct _list_node s_node;
 
typedef struct {
    s_node** listes;
    int nbe; // nb d'entrées
    int* nbm; // nb de mots
} t_hachage;

t_hachage* table_creation(int nbe);

void table_destroy(t_hachage* th);

void ajouter_mot(t_hachage* th, char* mot);

void supprimer_mot(t_hachage* th, char* mot);

void afficher_statistiques(t_hachage* th);

#endif