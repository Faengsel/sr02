#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "common.h"

void inc_one (int * projection, size_t taille) {
  // Le compteur n'etant pas fourni en parametre,
  // on le declare en static ici afin d'incrementer
  // la valeur a l'index suivant a chaque appel
  static int i = 0;
  projection[i]++;
  i++;
}

int main () {
  int * projection;
  ssize_t taille_fichier;

  taille_fichier = projeter_fichier(FILENAME, (void **)&projection,
                                    PROT_READ | PROT_WRITE);
  if (taille_fichier < 0) {
    return -1;
  }
  
  tq_different_99(projection, taille_fichier, inc_one);

  munmap((void *)projection, taille_fichier);

  return 0;
}

