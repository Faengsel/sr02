#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "common.h"

void afficher_projection (int * projection, size_t taille_fichier) {
  unsigned int i;

  // La taille du fichier etant exprime en octets, il faut
  // la diviser par la taille d'un entier pour obtenir le
  // nombre de "cases" contenues dans la projection
  for (i = 0; i < taille_fichier / sizeof(int); i++) {
    printf("%d ", projection[i]);
  }
  printf("\n");
}

int main () {
  int * projection;
  ssize_t taille_fichier;

  taille_fichier = projeter_fichier(FILENAME, (void **)&projection, PROT_READ);
  if (taille_fichier < 0) {
    return -1;
  }

  tq_different_99(projection, taille_fichier, afficher_projection);
  munmap((void *)projection, taille_fichier);

  return 0;
}
