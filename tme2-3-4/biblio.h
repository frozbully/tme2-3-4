/* biblio.h */

#ifndef biblio_h
#define biblio_h

typedef struct CellMorceau CellMorceau;
typedef struct Biblio Biblio;
/*
TODO :
  reflechir a comment eviter de print (changer struc Morceau ?)
*/
Biblio *nouvelle_biblio(int m);
Biblio *charge_n_entrees(const char *nom_fichier, int n);
void libere_biblio(Biblio *B);

void insere(Biblio *B, int num, char *titre, char *artiste);
void affiche(Biblio *B);
Biblio *uniques(Biblio *B);

CellMorceau *recherche_numero(Biblio *B, int num);
Biblio *recherche_auteur(Biblio *B, char* auteur);
CellMorceau *recherche_titre(Biblio *B, char* titre);
void supprimer_morceau(Biblio *B, CellMorceau *M);
#endif /* biblio_h */
