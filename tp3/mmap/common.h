#ifndef __COMMON__
#define __COMMON__

#include <unistd.h>

#define FILENAME  "titi.dat"

ssize_t projeter_fichier (const char * filename, void ** projection);

#endif
