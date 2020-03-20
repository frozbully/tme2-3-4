/* biblio.c */
#include <stdlib.h>
#include "biblio.h"
#include "parser.h"


Biblio *charge_n_entrees (const char *nom_fichier, int n) {

    FILE* f=fopen(nom_fichier,"r");

    char* artiste = NULL;
    char* titre = NULL;
    int nb;
    int taille;
    //char vide; -Wunused-variable
    Biblio* B=nouvelle_biblio(n);
    while(end_of_file(f) && n>0){
        parse_int(f,&nb);
        parse_char(f,'\t');
        parse_string(f,&titre,&taille,'\t');
        parse_string(f,&artiste,&taille,'\n');
        insere(B,nb,titre,artiste);
        n--;
    }

    free(artiste);
    free(titre);
    fclose(f);

    return B;
}
