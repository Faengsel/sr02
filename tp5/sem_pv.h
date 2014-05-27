#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define N_SEM 5


union semnum{ 
  int val;
	struct semid* buf;
	ushort *array;
};

int init_semaphore();
int detruire_semaphore();
int val_sem(int val, int sem);
int P(int sem);
int V(int sem);
