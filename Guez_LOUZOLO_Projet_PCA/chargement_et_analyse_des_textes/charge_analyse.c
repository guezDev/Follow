#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../table_de_hachage/hachage.h"
#include "charge_analyse.h"

t_word_tokens init_word_tokens() {
    return (t_word_tokens) {NULL, 0};
}
t_short_space_tokens init_short_space_tokens() {
    return (t_short_space_tokens) {NULL, 0};
}
t_space_tokens init_space_tokens() {
    return (t_space_tokens) {NULL, 0};
}


char* charger_texte(char* fichier, t_hachage* th, t_word_tokens* word_tokens, t_short_space_tokens* short_space_tokens, t_space_tokens* space_tokens) {
    FILE* f=fopen(fichier,"r");
    if(f==NULL) return NULL;

    t_token* token=NULL;
    char* texte=(char*) malloc(sizeof(char)*NB_TAILLE_TEXTE);
    strcpy(texte,"");
    int c=fgetc(f);
    int j, offset=0;
    while(c!=EOF) {
        token=(t_token*) malloc(sizeof(t_token)); 
        token->data.word=(char*) malloc(sizeof(char)*NB_MAX_CAR_MOT);
        j=0;
        
        if(c==' ' || c=='\t' || c=='\n') {
            while(c==' ' || c=='\t' || c=='\n') {
                token->data.word[j]=c;
                c=fgetc(f);
                j++;
            }
            token->data.word[j]='\0';
            token->textOffset=offset;
            offset+=strlen(token->data.word);

            if(j<=4) {
                token->type=SHORT_SPACE;
                ajouter_mot(th,token->data.word);
                strcat(texte,token->data.word);

                for(int i=0;j<i;j++) {
                    token->data.space[i]=token->data.word[i];
                }

                short_space_tokens->nbt++;
                short_space_tokens->tab_short_space_tokens=(t_token**) realloc(short_space_tokens->tab_short_space_tokens, sizeof(t_token*)*short_space_tokens->nbt);
                short_space_tokens->tab_short_space_tokens[short_space_tokens->nbt-1]=token;
            } else {
                token->type=SPACE;
                ajouter_mot(th, token->data.word);
                strcat(texte,token->data.word);

                space_tokens->nbt++;
                space_tokens->tab_space_tokens=(t_token**) realloc(space_tokens->tab_space_tokens, sizeof(t_token*)*space_tokens->nbt);
                space_tokens->tab_space_tokens[space_tokens->nbt-1]=token;
            }
        } 
        else {
            while(c!=' ' && c!='\t' && c!='\n' && c!=EOF) {
                token->data.word[j]=c;
                c=fgetc(f);
                j++;
            }
            token->data.word[j]='\0';
            token->textOffset=offset;
            offset+=strlen(token->data.word);
            token->type=WORD;
            ajouter_mot(th, token->data.word);
            strcat(texte,token->data.word);


            word_tokens->nbt++;
            word_tokens->tab_word_tokens=(t_token**) realloc(word_tokens->tab_word_tokens, sizeof(t_token*)*word_tokens->nbt);
            word_tokens->tab_word_tokens[word_tokens->nbt-1]=token;
        }
    }

    fclose(f);
    return texte;
}

static char* get_type(t_type type) {
    switch (type)
    {
        case WORD:
            return "WORD";
        case SHORT_SPACE:
            return "SHORT_SPACE";
        case SPACE:
            return "SPACE";
        case ERASE:
            return "ERASE";
        case INSERT:
            return "INSERT";
        case REPLACE:
            return "REPLACE";
        case EMPTY:
            return "EMPTY"; 
        default:
            return "PB";
    }
}

void afficher_word_tokens(t_word_tokens word_tokens) {
    for(int i=0;i<word_tokens.nbt;i++) {
        printf("Type: %s\tchaine: %s\t\toffset: %d\n", get_type(word_tokens.tab_word_tokens[i]->type),word_tokens.tab_word_tokens[i]->data.word, word_tokens.tab_word_tokens[i]->textOffset);
    }
}

void afficher_short_space_tokens(t_short_space_tokens short_space_tokens) {
    for(int i=0;i<short_space_tokens.nbt;i++) {
        printf("Type: %s\tchaine: '%s'\t\toffset: %d\n", get_type(short_space_tokens.tab_short_space_tokens[i]->type),short_space_tokens.tab_short_space_tokens[i]->data.word, short_space_tokens.tab_short_space_tokens[i]->textOffset);
    }
}

void afficher_space_tokens(t_space_tokens space_tokens) {
    for(int i=0;i<space_tokens.nbt;i++) {
        printf("Type: %s\tchaine: '%s'\t\toffset: %d\n", get_type(space_tokens.tab_space_tokens[i]->type),space_tokens.tab_space_tokens[i]->data.word, space_tokens.tab_space_tokens[i]->textOffset);
    }
}

void free_word_tokens(t_word_tokens* word_tokens) {
    if(word_tokens->nbt==0) return;
    for(int i=0;i<word_tokens->nbt;i++) {
        free(word_tokens->tab_word_tokens[i]);
    }
    free(word_tokens->tab_word_tokens);
}

void free_short_space_tokens(t_short_space_tokens* short_space_tokens) {
    if(short_space_tokens->nbt==0) return;

    for(int i=0; i<short_space_tokens->nbt;i++) {
        free(short_space_tokens->tab_short_space_tokens[i]);
    }
    free(short_space_tokens->tab_short_space_tokens);
}

void free_space_tokens(t_space_tokens* space_tokens) {
    if(space_tokens->nbt==0) return;

    for(int i=0;i<space_tokens->nbt;i++) {
        free(space_tokens->tab_space_tokens[i]);
    }

    free(space_tokens->tab_space_tokens);
}