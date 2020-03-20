#include <stdio.h>
#include "biblio.h"

int main(int argc, char const *argv[]) {
  Biblio * B = charge_n_entrees("BiblioMusicale.txt", 10);
  affiche(B);
  return 0;
}
