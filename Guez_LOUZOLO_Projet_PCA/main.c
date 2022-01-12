#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "liste_chainee/list.h"
#include "test/testListHelpers.h"
#include "table_de_hachage/hachage.h"
#include "chargement_et_analyse_des_textes/charge_analyse.h"
#include "alignement_des_textes/alignement.h"

#define NB_LISTES_TH 5

int compareInt(s_node *node, void* val) {
    int * valeur_noeud=(int*) list_get_data(node);
    int * valeur=(int*) val;
    if(*valeur_noeud < *valeur) {
        return -1;
    } else if(*valeur_noeud == *valeur) {
        return 0;
    } else {
        return 1;
    }
}

int node_to_string(s_node * node, char *buffer, int size) {
	char * value;
	int str_length;

	value=(char*)list_get_data(node);
    int nbc=strlen(value);
    for(int i=0;i<nbc;i++) {
	    str_length=snprintf(&buffer[i], size, "%c", value[i]);

    }
	return (str_length >= size); 
}


/*void on_file_activated(GtkWidget *widget, gpointer data) {

}*/

static void open_dialog(GtkWidget* ouvrirItem, gpointer fenetre_principale)
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Chosse a file", GTK_WINDOW(fenetre_principale), GTK_FILE_CHOOSER_ACTION_OPEN, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
//  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),"/");
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    else
        g_print("You pressed Cancel\n");
    gtk_widget_destroy(dialog);
}

int main(int argc, char* argv[]) {

    gtk_init(&argc, &argv);
    GtkWidget *fenetre_principale = NULL;
    GtkWidget *texteview1 = NULL;//
    GtkTextIter iter;//
    GtkWidget *ouvrirItem=NULL;
    GtkBuilder *builder = NULL;
    GError *error = NULL;
    gchar *filename = NULL;

    /* Initialisation de la librairie Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale */
    builder = gtk_builder_new();

    /* Création du chemin complet pour accéder au fichier test.glade. */
    /* g_build_filename(); construit le chemin complet en fonction du système */
    /* d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("conception_ihm/follow.glade", NULL);

        /* Chargement du fichier test.glade. */
    gtk_builder_add_from_file (builder, filename, &error);
    g_free (filename);
    if (error)
    {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
    }

    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));
    texteview1=GTK_WIDGET(gtk_builder_get_object(builder,"texte1"));//
    ouvrirItem=GTK_WIDGET(gtk_builder_get_object(builder, "ouvrir"));
    /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /* fermeture de la fenêtre. */
    g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);
     g_signal_connect(ouvrirItem, "activate", G_CALLBACK(open_dialog), fenetre_principale);

    GtkTextBuffer *buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(texteview1));//
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    //gtk_text_buffer_insert(buffer, &iter, "Plain text ... it's working\n", -1);
    gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

    gtk_main();

    /*t_hachage* th=table_creation(NB_LISTES_TH);

    char* texte_ref=NULL;
    char* texte_nouveau=NULL;

    wt_ref=init_word_tokens();
    sst_ref=init_short_space_tokens();
    st_ref=init_space_tokens();

    wt_nouveau=init_word_tokens();
    sst_nouveau=init_short_space_tokens();
    st_nouveau=init_space_tokens();

    noms_communs=init_word_tokens();
    mots_supp=init_word_tokens();
    mots_ins=init_word_tokens();
    mots_remp=init_word_tokens();

    texte_ref=charger_texte(argv[1],th, &wt_ref, &sst_ref, &st_ref);
    texte_nouveau=charger_texte(argv[2], th, &wt_nouveau, &sst_nouveau, &st_nouveau);

    if(texte_ref==NULL || texte_nouveau==NULL) return 1;

    memalloc_matrice_plsc();
    
    remplir_matrice_plsc();
    mise_en_oeuvre_plsc();
    trouve_mot_remp();

    affiche_matrice_plsc();

    afficher_word_tokens(noms_communs);
    printf("\n");
    afficher_word_tokens(mots_supp);
    printf("\n");
    afficher_word_tokens(mots_ins);
    printf("\n");
    afficher_word_tokens(mots_remp);

    table_destroy(th);
    terminer_alignement();
    destroy_matrice_plsc();
    free_word_tokens(&wt_ref);
    free_word_tokens(&wt_nouveau);
    free_word_tokens(&noms_communs);
    free_word_tokens(&mots_ins);
    free_word_tokens(&mots_supp);
    free_word_tokens(&mots_remp);
    free_short_space_tokens(&sst_ref);
    free_short_space_tokens(&sst_nouveau);
    free_space_tokens(&st_ref);
    free(texte_ref);
    free(texte_nouveau);*/
        
    return 0;
}