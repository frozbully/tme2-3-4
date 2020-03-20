/* biblio_tabdyn.c */
/*
TODO :
  insere : handle realloc errors
  uniques : optimise
  recherche_titre, recherche_auteur, recherche_numero : return type
  supprimer_morceau
  printM() ?
  comment structs
*/
#include <stdlib.h>
#include <stdio.h>
#include "biblio.h"
#define DEFAULT_SIZE 10

struct CellMorceau{
  char *titre;
  char *artiste;
  int num;
};

struct Biblio {
  int nE;
  int capacite;
  CellMorceau *T;
};

//Q3.1
void insere(Biblio *B, int num, char *titre, char *artiste) {
  /* insere le Morceau definit par les parametres
     a la position B->nE du tableau B->T et double
     la capacite B->capacite si le tableau est plein*/
  CellMorceau m;
  m.num = num;
  m.artiste = artiste;
  m.titre = titre;

  /*si il n'y a plus de place*/
  if ( B->capacite == B->nE ) {
    B->capacite = B->capacite *2;
    B->T = realloc(B->T,(B->capacite)*sizeof(CellMorceau));
    //TODO: realloc error ?
  }
  /*on insere le Morceau*/
  (B->T)[B->nE] = m;
  B->nE ++;
}

//Q3.2
Biblio *nouvelle_biblio(int size) {
  /*initialise une nouvelle Biblio de taille DEFAULT_SIZE
    retourne NULL si un malloc echoue*/

  Biblio *res = malloc(sizeof(Biblio));
  /*si malloc echoue sur Biblio *res */
  if (res == NULL) {
    return NULL;
  }

  res->T=malloc(size*sizeof(CellMorceau));
  /*si malloc echoue sur Morceau *T */
  if (res->T == NULL) {
    free(res);
    return NULL;
  }

  res->nE=0;
  res->capacite=size;
  return res;
}

void libere_biblio(Biblio *B) {
  /*libere l'espace memoire alloue a B
    libere B->T et B */
    free(B->T);
    free(B);
}

void affiche(Biblio *B) {
  /*affiche tous les elements de B*/
  CellMorceau m;
  int i;
  printf("Nombre d'elements %d\n", B->nE);
  for (i=0; i < B->nE; i++) {
    m=(B->T)[i];
    printf("\t%d\t%s\t%s\n", m.num, m.titre, m.artiste);
  }
}


Biblio *uniques(Biblio *B) {
  /*renvoie la liste des morceaux qui n'ont pas de doublons
    dans B, renvoie NULL si malloc echoue ou si B=NULL*/
  if (B==NULL) return NULL;
  /*ici on pourrait ne pas utiliser nouvelle_biblio DEFAULT_SIZE
    pour optimiser les realloc et allouer directement
    B->nE cases dans res->T */
  CellMorceau m1,m2;
  int i,j;
  int unique;//boolean
  Biblio *res = nouvelle_biblio(DEFAULT_SIZE);
  for (i=0; i < B->nE; i++) {
    unique = 1; //unique=true
    m1=(B->T)[i];

    for (j=0; j < res->nE; j++) {
      m2=(res->T)[j];

      /*si m1 est deja dans res (c'est un doublon)*/
      if ((m1.artiste == m2.artiste) && (m1.titre == m2.titre)) {
        unique = 0; //unique=false
        break;// while instead of for+break ?
      }
    }

    if (unique) {
      insere(res, m1.num, m1.titre, m1.artiste);
    }
  }
  return res;
}

CellMorceau  *recherche_numero(Biblio *B, int num) {
  /*retourne le premier Morceau  de B dont le
    numero == num*/
  CellMorceau m;
  int i;

  for (i=0; i < B->nE; i++) {
    m=(B->T)[i];
    if (m.num == num) {
      //printf("%d\t%s\t%s\n", m.num, m.titre, m.artiste);
      return (B->T)+i;
    }
  }
  return NULL;
}

Biblio *recherche_auteur(Biblio *B, char *auteur) {
  /*retourne un Biblio contenant tous les titres de auteur*/
  Biblio *res = nouvelle_biblio(DEFAULT_SIZE);
  CellMorceau m;
  int i;

  for (i=0; i < B->nE; i++) {
    m=(B->T)[i];
    if (m.artiste == auteur) {
      insere(res, m.num, m.titre, m.artiste);
    }
  }
  return res;
}

CellMorceau *recherche_titre(Biblio *B, char* titre) {
  /*retourne le premier Morceau  de B dont le
    titre == titre*/
  CellMorceau m;
  int i;

  for (i=0; i < B->nE; i++) {
    m=(B->T)[i];
    if (m.titre == titre) {
      //printf("%d\t%s\t%s\n", m.num, m.titre, m.artiste);
      return (B->T)+i;
    }
  }
  return NULL;
}
//void supprimer_morceau(Biblio *B, CellMorceau M);
