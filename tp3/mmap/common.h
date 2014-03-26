#ifndef __COMMON__
#define __COMMON__

#include <unistd.h>

#define FILENAME  "titi.dat"

ssize_t projeter_fichier (const char * filename, void ** projection);
void tq_different_99 (int * projection, size_t taille_fichier,
                      void (*func)(int * projection, size_t taille));

#endif
