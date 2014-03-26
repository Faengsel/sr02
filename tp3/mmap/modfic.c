#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "common.h"

int main () {
  int * projection;
  unsigned int i; 
  int n;
  ssize_t taille_fichier;

  taille_fichier = projeter_fichier(FILENAME, (void **)&projection);
  if (taille_fichier < 0) {
    return -1;
  }
  
  i = 0;
  printf("Entrez un nombre (99 pour quitter): ");
  scanf("%d", &n);

  while (n != 99 && i < taille_fichier / sizeof(int)) {
    projection[i]++;

    printf("Entrez un nombre (99 pour quitter): ");
    scanf("%d", &n);

    i++;
  } 

  munmap((void *)projection, taille_fichier);

  return 0;
}

