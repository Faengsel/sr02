#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "common.h"

ssize_t projeter_fichier (const char * filename, void ** projection, int prot) {
  int fd; 
  size_t taille_fichier;
  struct stat etat_fichier;

  // Recupere un descripteur sur le fichier ainsi
  // que sa taille afin de pouvoir le projeter
  // en memoire
  if ((fd = open(filename, O_RDWR)) < 0) {
    perror("open");
    return -1;
  }

  if (fstat(fd, &etat_fichier) < 0) {
    perror("fstat");
    return -1;
  }

  taille_fichier = etat_fichier.st_size;

  // MAP_SHARED permet de partager le segment memoire,
  // les modifications apportees sont ainsi visibles
  // immediatement par tout processus partageant ce
  // segment memoire
  *projection = (int *) mmap(NULL, taille_fichier, prot, 
                            MAP_SHARED, fd, 0);
  if (*projection == (int *) MAP_FAILED) {
    perror("mmap");
    return -1;
  }

  close(fd);

  return taille_fichier;
}

// Appelle la fonction "func" tant que l'utilisateur n'a pas
// rentree 99 et que la projection n'a pas ete entierement lue
void tq_different_99 (int * projection, size_t taille_fichier,
                      void (*func)(int * projection, size_t taille)) 
{
  unsigned int i = 0; 
  int n;

  printf("Entrez un nombre (99 pour quitter): ");
  scanf("%d", &n);

  while (n != 99 && i < taille_fichier / sizeof(int)) {
    func(projection, taille_fichier);
    printf("Entrez un nombre (99 pour quitter): ");
    scanf("%d", &n);

    i++;
  } 
}
