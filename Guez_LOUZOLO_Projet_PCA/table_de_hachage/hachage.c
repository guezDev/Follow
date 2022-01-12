#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../liste_chainee/list.h"
#include "hachage.h"

t_hachage* table_creation(int nbe) {
    t_hachage* th=(t_hachage*) malloc(sizeof(t_hachage));
    th->listes= (s_node**) malloc(sizeof(s_node*)*nbe);
    th->nbm=(int*) malloc(sizeof(int)*nbe);

    for(int i=0;i<nbe;i++) {
        th->listes[i]=list_create();
        th->nbm[i]=0;
    }

    th->nbe=nbe;
    
    return th;
}

void table_destroy(t_hachage* th) {
    s_node* node=NULL;

    for(int i=0;i<th->nbe;i++) {
        node=th->listes[i];
        while(node!=NULL) {
            free(list_get_data(node));
            node=node->next;
        }
        list_destroy(th->listes[i]);
    }
    free(th->listes);
    free(th->nbm);
    free(th);
}

static int compare_mot(s_node * node, void * data) {
    return strcmp((char*) list_get_data(node), (char*) data);
}

static int clef_hachage(char* mot, int nbe) {    
    int clef=0, nbc=strlen(mot);
    for(int i=0;i<nbc;i++) {
        clef*=2;
        clef+=mot[i];
    }
    return clef % nbe;
}

void ajouter_mot(t_hachage* th, char* mot) {
    if(strlen(mot)==0) return;
    int clef=clef_hachage(mot,th->nbe);

    s_node* ptr=th->listes[clef];
    while(ptr!=NULL) {
        if(strcmp((char*) list_get_data(ptr), mot)==0) {
            return;
        }
        ptr=ptr->next;
    }
    char* _mot=strdup(mot);
    th->listes[clef]=list_orderedAppend(&th->listes[clef], &compare_mot, _mot);
    th->nbm[clef]=(th->nbm[clef])+1;
    

    
}

void supprimer_mot(t_hachage* th, char* mot) {
    if(strlen(mot)==0) return;
    int clef=clef_hachage(mot,th->nbe);

    s_node* ptr=th->listes[clef];
    while(ptr!=NULL) { // pour trouver le noeud et libérer sa donnée
        if(strcmp((char*) list_get_data(ptr), mot)==0) {
            void* _data=list_get_data(ptr);
            th->listes[clef]=list_remove(th->listes[clef], list_get_data(ptr));
            th->nbm[clef]=(th->nbm[clef])-1;
            free(_data);
            return;
        }
        ptr=ptr->next;
    }
}

void afficher_statistiques(t_hachage* th) {
    double som=0, _som=0;
    int min=th->nbm[0], max=th->nbm[0];
    printf("\n---Statistiques\n"); 
    for(int i=0;i<th->nbe;i++) {
        som+=th->nbm[i];
    }
    printf("Nombre total d'elements : %.3lf\n", som);

    for(int i=0;i<th->nbe;i++) {
        if(th->nbm[i]<min) {
            min=th->nbm[i];
        }

        if(th->nbm[i]>max) {
            max=th->nbm[i];
        }
    }
    
    printf("Nombre d'éléments minimum : %d\n", min);
    printf("Nombre d'éléments maximum : %d\n", max);

    double x=som/(th->nbe*1.0);
    for(int i=0;i<th->nbe;i++) {
        _som+=(th->nbm[i]-x)*(th->nbm[i]-x);
    }
    printf("Ecart type : %.3lf\n", sqrt(_som/(th->nbe*1.0)));
    
}
