#ifndef _ALIGNEMENT_H_
#define _ALIGNEMENT_H_

#include "../chargement_et_analyse_des_textes/charge_analyse.h"

int** matrice_plsc;
t_word_tokens noms_communs;
t_word_tokens mots_supp;
t_word_tokens mots_ins;
t_word_tokens mots_remp;

int lg(int i, int j);
void memalloc_matrice_plsc();
void remplir_matrice_plsc();
void trouve_mot_remp();
void mise_en_oeuvre_plsc();
void affiche_matrice_plsc();

void terminer_alignement();
void destroy_matrice_plsc();

#endif