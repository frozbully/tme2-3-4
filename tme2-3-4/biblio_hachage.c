#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "biblio_hachage.h"
#include "biblio.h"
/*
TODO :
  nouvelle_biblio
  comment structs
*/
struct CellMorceau {
  struct CellMorceau *suiv;
  unsigned int cle;
  int num;
  char *titre;
  char *artiste;
};

struct Biblio {
  int nE;
  int m;
  CellMorceau **T;
};

//Q4.1
unsigned int fonction_cle(const char *artiste) {
  /*renvoie la somme des valeurs des caracteres d'un nom d'artiste*/
  int i=0;
  unsigned int sum;
  while (artiste[i] != '\0') {

    sum += (int)artiste[i];
    i++;
  }
  return 0;
}

//Q4.2
unsigned int fonction_hachage(unsigned int cle, int m) {
  /*renvoie une cle de hachage a partir d'un entier cle
    et d'une taille maximum m*/
  float A= (sqrt(5)-1)/2;
  return floor(m*( cle*A-floor(cle*A) ));
}

//Q4.3
void insere(Biblio *B, int num, char *titre, char *artiste) {
  /*insere le Morceau definit par les parametres
    a la position definie par les fonctions de hachage*/

  /*creation du morceau*/
  CellMorceau *morceau = malloc(sizeof(CellMorceau));
  morceau->num = num;
  morceau->titre = titre;
  morceau->artiste = artiste;
  morceau->cle = fonction_cle(artiste);
  morceau->suiv = NULL;
  /*insertion en tete du morceau*/
  unsigned int h = fonction_hachage(morceau->cle,B->m);
  morceau->suiv = (B->T)[h];
  (B->T)[h] = morceau;
}

//Q4.4
Biblio *nouvelle_biblio(int m);

void libere_biblio(Biblio *B) {
  /*libere l'espace memoire alloue a B */
  CellMorceau *cell;
  CellMorceau *next;
  int i;
  /*parcours de la table de hachage*/
  for (i=0; i < B->m; i++) {
    next = NULL;
    cell = (B->T)[i];
    /*on libere chaque cellule*/
    while (cell != NULL) {
      next = cell->suiv;
      free(cell);
      cell = next;
    }
  }
  /*on libere la table de hachage*/
  free(B->T);
  /*on libere la Biblio*/
  free(B);
}

void affiche(Biblio *B) {
  /*affiche toutes les CellMorceau de Biblio*/
  CellMorceau *cell;
  int i;
  printf("Nombre d'elements %d\n", B->nE);
  /*parcours de la table de hachage*/
  for (i=0; i < B->m; i++) {
    cell = (B->T)[i];
    /*on parcours chaque cellule*/
    while (cell != NULL) {
      printf("\t%d\t%s\t%s\n", cell->num, cell->titre, cell->artiste);
      cell = cell->suiv;
    }
  }
}

Biblio *uniques(Biblio *B) {
  /*renvoie la liste des morceaux qui n'ont pas de doublons
    dans B*/
  CellMorceau *cell;
  CellMorceau *reste;
  int unique; //boolean
  int i;
  Biblio *res = nouvelle_biblio(B->m);
  /*parcours de la table de hachage*/
  for (i=0; i < B->m ; i++) {
    cell = (B->T)[i];
    /*on parcours chaque cellule*/
    while (cell != NULL) {
      unique = 1; //unique=true
      reste = cell->suiv;
      /*on la compare a toutes les suivantes*/
      while (reste != NULL ) {
        /*si un doublon est trouve*/
        if ((reste->titre == cell->titre) && (reste->artiste == cell->titre)) {
          unique = 0; //unique=false
        }
      }

      if (unique) {
        insere(B, cell->num, cell->titre, cell->artiste);
      }
      cell = cell->suiv;
    }

  }

  return res;
}

Biblio *recherche_auteur(Biblio *B, char* auteur) {
  /*renvoie la biblio des titres de auteur dans B*/
  Biblio *res = nouvelle_biblio(1);
  int h = fonction_hachage(fonction_cle(auteur),B->m);
  CellMorceau *cell = (B->T)[h];

  while(cell != NULL) {
    insere(res, cell->num, cell->titre, cell->artiste);
    cell=cell->suiv;
  }
  return res;
}

CellMorceau *recherche_numero(Biblio *B, int num) {
  /*renvoie le premier */
  CellMorceau *cell;
  int i;
  /*parcours de la table de hachage*/
  for (i=0; i < B->m ; i++) {
    cell = (B->T)[i];
    /*on parcours chaque cellule*/
    while (cell != NULL) {
      if (cell->num == num) {
        return cell;
      }
      cell=cell->suiv;
    }
  }
  return NULL;
}
CellMorceau * recherche_titre(Biblio *B, char* titre) {
  /*renvoie le premier */
  CellMorceau *cell;
  int i;
  /*parcours de la table de hachage*/
  for (i=0; i < B->m ; i++) {
    cell = (B->T)[i];
    /*on parcours chaque cellule*/
    while (cell != NULL) {
      if (cell->titre == titre) {
        return cell;
      }
      cell=cell->suiv;
    }
  }
  return NULL;
}

void supprimer_morceau(Biblio *B, CellMorceau *M) {
    /*libere l'espace memoire d'un morceaux
      dans une table de hachage*/
    /*le titre se trouve forcement dans cette liste chainee*/
    CellMorceau *cell = recherche_titre(B, M->artiste);
    CellMorceau *temp;
    if (cell == NULL) {
      return;
    }
    if (cell == M) {
      (B->T)[fonction_hachage(fonction_cle(M->artiste),B->m)] = cell->suiv;
      free(cell);
      return;
    }
    while (cell->suiv != NULL) {
      temp=cell;
      cell=cell->suiv;
      if (cell == M) {
        temp->suiv = cell->suiv;
        return;
      }
    }
}
