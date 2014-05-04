#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "prod-conso.h"
#include "sem_pv.h"

int main () {
  int i, ret;
  int shmid;
  int* addr;

  // Creation d'un segment de memoire partagee pouvant contenir 5 entiers
  if ((shmid = shmget(KEY, 5 * sizeof(int), IPC_CREAT | 0666)) < 0 ||
      (addr = (int*) shmat(shmid, 0, 0)) == (int*)-1) {

    fprintf(stderr, "%s", strerror(errno));
    return -1;
  }

	init_semaphore();

  pid_t child = fork();

  switch (child) {
    case -1:
      perror("fork");
      return -1;
    case 0:
      fils(addr);
      break;
    default:
      pere(addr, shmid);
      break;
  }

  return 0;
}

void pere (int * addr, int shmid) {
  int count, index; 

  for (count = 0; count < 50; count++) {
    printf("PERE: %d\n", count);
    index = count % N_SEM;
    P(index);
    printf("consomme %d\n", addr[index]);
  }

  detruire_semaphore();
  shmdt(addr);
  shmctl(shmid, IPC_RMID, 0);
}

void fils (int * addr) {
  int count = 0, index = 0; // index d'ecriture

  for (count = 0; count < 50; count++) {
    index = count % N_SEM;
    printf("produit %d\n", count);
    addr[index] = count;
    V(index);
  }

  shmdt(addr);
}
