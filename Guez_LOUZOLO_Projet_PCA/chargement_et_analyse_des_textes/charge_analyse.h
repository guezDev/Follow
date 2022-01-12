#ifndef _CHARGE_ANALYSE_H_
#define _CHARGE_ANALYSE_H_

#include <stdlib.h>
#include "../table_de_hachage/hachage.h"

#define NB_MAX_CAR_MOT 26
#define NB_TAILLE_TEXTE 1001

typedef enum {WORD, SHORT_SPACE, SPACE, ERASE, INSERT, REPLACE, EMPTY } t_type;

struct token {
    t_type type;
    int textOffset;
    union {
        char* word;
        char space[4];
    } data;
};

typedef struct token t_token;

typedef struct {
    t_token** tab_word_tokens;
    int nbt;
} t_word_tokens;

typedef struct {
    t_token** tab_space_tokens;
    int nbt;
} t_space_tokens;

typedef struct {
    t_token** tab_short_space_tokens;
    int nbt;

} t_short_space_tokens;

t_word_tokens wt_ref;
t_short_space_tokens sst_ref;
t_space_tokens st_ref;

t_word_tokens wt_nouveau;
t_short_space_tokens sst_nouveau;
t_space_tokens st_nouveau;

t_word_tokens init_word_tokens();
t_short_space_tokens init_short_space_tokens();
t_space_tokens init_space_tokens();


char* charger_texte(char* fichier, t_hachage* th, t_word_tokens* word_tokens, t_short_space_tokens* short_space_tokens, t_space_tokens* space_tokens);

void afficher_word_tokens(t_word_tokens word_tokens);
void afficher_short_space_tokens(t_short_space_tokens short_space_tokens);
void afficher_space_tokens(t_space_tokens space_tokens);

void free_word_tokens(t_word_tokens* word_tokens);
void free_short_space_tokens(t_short_space_tokens* short_space_tokens);
void free_space_tokens(t_space_tokens* space_tokens);

#endif