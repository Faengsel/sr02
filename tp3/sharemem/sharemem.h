#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define CLE   666
#define PROT 0666

void fils (int *tab, void *addr);
void pere (int *tab, void *addr, int shmid);
void initialiser_tableau(int * tab, int val, int size);
void afficher_tableau(const int *tab, int size);
