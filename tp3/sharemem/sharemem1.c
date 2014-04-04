#include "sharemem.h"

int main(){
  int tab[10];
  initialiser_tableau(tab, 1, 10);

  int shmid;
  void * addr;

  if ((shmid = shmget(CLE, 10 * sizeof(int), PROT | IPC_CREAT)) < 0 ||
      (addr = shmat(shmid, 0, 0)) < 0) {

    fprintf(stderr, "%s", strerror(errno));
    return -1;
  }

  pid_t child = fork();

  switch (child) {
    case -1:
      fprintf(stderr, "%s", strerror(errno));
      return -1;
    case 0: // processus fils
      fils(tab, addr);
      break;
    default: // processus pere
      pere(tab, addr, shmid);
      break;
  }

  return 0;
}

void fils (int *tab, void *addr) {
  // Change les valeurs du tableau
  // dans la memoire du processus fils
  initialiser_tableau(tab, 2, 10);

  printf("Le fils, tab2[] :  ");
  afficher_tableau(tab, 10);

  // Copie le tableau modifie dans le
  // segment memoire partage
  memcpy(addr, tab, 10 * sizeof(int));

  shmdt(addr);
}

void pere (int *tab, void *addr, int shmid) {
  usleep(500000);

  printf("Le pere, tab2[] :  ");
  // Affiche la valeur initiale du tableau
  // car le processus pere n'a pas encore
  // recupere les modifications apportees
  // par le processus fils
  afficher_tableau(tab, 10);

  usleep(500000);

  // Recupere les modifications
  memcpy(tab, addr, 10 * sizeof(int));

  printf("Le pere, tab2[] :  ");
  // affiche les nouvelles valeurs
  afficher_tableau(tab, 10);

  wait();

  shmdt(addr);

  // Detruit le segment de memoire partagee
  // une fois que tous les processus s'en
  // sont detaches
  shmctl(shmid, IPC_RMID, 0);
}

void initialiser_tableau (int *tab, int val, int size) {
  int i;

  for (i = 0; i < size; i++) {
    tab[i] = val;
  }
}

void afficher_tableau (const int *tab, int size) {
  int cpt;
  for (cpt = 0; cpt < size; cpt++) {
    printf("%d ", tab[cpt]);
  }
  printf("\n");
}
