#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../chargement_et_analyse_des_textes/charge_analyse.h"
#include "alignement.h"

static void ajoute_mot_remp(t_token* tk) {
    int trouve=0;
    for(int i=0;i<noms_communs.nbt && !trouve;i++) {
        if(strcmp(noms_communs.tab_word_tokens[i]->data.word, tk->data.word)==0) {
            trouve=1;
        }
    }

    for(int j=0;j<mots_supp.nbt && !trouve;j++) {
        if(strcmp(mots_supp.tab_word_tokens[j]->data.word, tk->data.word)==0) {
            trouve=1;
        }
    }

    for(int k=0;k<mots_ins.nbt && !trouve;k++) {
        if(strcmp(mots_ins.tab_word_tokens[k]->data.word, tk->data.word)==0) {
            trouve=1;
        }
    }

    if(!trouve) {
        mots_remp.nbt++;
        mots_remp.tab_word_tokens=(t_token**) realloc(mots_remp.tab_word_tokens, sizeof(t_token*)*mots_remp.nbt);
        mots_remp.tab_word_tokens[mots_remp.nbt-1]=tk;
        mots_remp.tab_word_tokens[mots_remp.nbt-1]->type=REPLACE;
    }
}

void trouve_mot_remp() {
    for(int i=0;i<wt_ref.nbt;i++) {
        ajoute_mot_remp(wt_ref.tab_word_tokens[i]);
    }

    for(int j=0;j<wt_nouveau.nbt;j++) {
        ajoute_mot_remp(wt_nouveau.tab_word_tokens[j]);
    }
}

static char* last_word;
static char* chaine;

void terminer_alignement() {
    free(last_word);
    free(chaine);
}

int lg(int i, int j) {
    if(i==0 || j==0) return 0;
    if(strcmp(wt_ref.tab_word_tokens[i-1]->data.word,wt_nouveau.tab_word_tokens[j-1]->data.word)==0) {
        return lg(i-1,j-1)+1;
    } else {
        return lg(i,j-1) > lg(i-1,j) ? lg(i,j-1) : lg(i-1,j);
    }
}

static char* plsc(int i, int j) {
    chaine=(char*) malloc(sizeof(char)*NB_MAX_CAR_MOT);
    strcpy(chaine, "");
    last_word=(char*) malloc(sizeof(char)*NB_MAX_CAR_MOT);
    strcpy(last_word, "");
    while(i!=0 && j!=0) {
        if(matrice_plsc[(wt_nouveau.nbt-j)+1][(wt_ref.nbt-i)+1]==matrice_plsc[wt_nouveau.nbt-j][wt_ref.nbt-i]-1 && strcmp(wt_ref.tab_word_tokens[i-1]->data.word,wt_nouveau.tab_word_tokens[j-1]->data.word)==0) {
            strcat(chaine, wt_ref.tab_word_tokens[i-1]->data.word);
            strcpy(last_word, wt_ref.tab_word_tokens[i-1]->data.word);
            i--;
            j--;
        } else if(matrice_plsc[(wt_nouveau.nbt-j)+1][wt_ref.nbt-i]==matrice_plsc[wt_nouveau.nbt-j][wt_ref.nbt-i]) {
            i--;
        } else {
            j--;
        }
    }
    return chaine;
}

static void application_plsc(int i, int j) {
    if(strcmp(plsc(i,j),strcat(plsc(i-1,j-1), wt_ref.tab_word_tokens[i-1]->data.word))==0 && strcmp(wt_ref.tab_word_tokens[i-1]->data.word,wt_nouveau.tab_word_tokens[j-1]->data.word)==0) {
        noms_communs.nbt++;
        noms_communs.tab_word_tokens=(t_token**) realloc(noms_communs.tab_word_tokens, sizeof(t_token*)*noms_communs.nbt);
        noms_communs.tab_word_tokens[noms_communs.nbt-1]=wt_ref.tab_word_tokens[i-1];
    } else {
        plsc(i,j-1);
        if(strcmp(last_word, wt_ref.tab_word_tokens[i-1]->data.word)==0) {
            mots_supp.nbt++;
            mots_supp.tab_word_tokens=(t_token**) realloc(mots_supp.tab_word_tokens, sizeof(t_token*)*mots_supp.nbt);
            mots_supp.tab_word_tokens[mots_supp.nbt-1]=wt_ref.tab_word_tokens[i-1];
            mots_supp.tab_word_tokens[mots_supp.nbt-1]->type=ERASE;
        }

        plsc(i-1,j);
        if(strcmp(last_word, wt_nouveau.tab_word_tokens[j-1]->data.word)==0) {
            mots_ins.nbt++;
            mots_ins.tab_word_tokens=(t_token**) realloc(mots_ins.tab_word_tokens, sizeof(t_token*)*mots_ins.nbt);
            mots_ins.tab_word_tokens[mots_ins.nbt-1]=wt_ref.tab_word_tokens[i-1];
            mots_ins.tab_word_tokens[mots_ins.nbt-1]->type=INSERT;
        }
    }
}


void memalloc_matrice_plsc() {
    matrice_plsc=(int**) malloc(sizeof(int*)*(wt_nouveau.nbt+1));

    for(int j=0;j<=wt_nouveau.nbt;j++) {
        matrice_plsc[j]=(int*) malloc(sizeof(int)*(wt_ref.nbt+1));
    }
}

void remplir_matrice_plsc() {
    if(matrice_plsc==NULL) return;
    for(int i=0; i<=wt_nouveau.nbt;i++) {
        for(int j=0; j<=wt_ref.nbt;j++) {
            matrice_plsc[i][j]=lg(wt_ref.nbt-j,wt_nouveau.nbt-i);
        }
    }
}

void mise_en_oeuvre_plsc() {
    for(int i=0; i<=wt_nouveau.nbt-1;i++) {
        for(int j=0; j<=wt_ref.nbt-1;j++) {
            application_plsc(wt_ref.nbt-j,wt_nouveau.nbt-i);
        }
    }
}


void affiche_matrice_plsc() {
    if(matrice_plsc==NULL) return;
    for(int i=0;i<=wt_nouveau.nbt;i++) {
        for(int j=wt_ref.nbt;j>=0;j--) {
            printf("%d ", matrice_plsc[i][j]);
        }
        printf("\n");
    }
}

void destroy_matrice_plsc() {
    for(int j=0;j<=wt_nouveau.nbt;j++) {
        free(matrice_plsc[j]);
    }

    free(matrice_plsc);
}