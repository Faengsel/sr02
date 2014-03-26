#include "sharemem.h"

int main(){
  int cpt;

  int tab1[10] = {1}, tab2[10] = {[0 ... 9]= 1};
  int shmid = shmget(CLE, 10 * sizeof(int), PROT | IPC_CREAT);
  void * addr = shmat(shmid, 0, 0); 

  pid_t child = fork();
  if(child==-1) fprintf(stderr, "Erreur de creation du fils\n");
  if(child == 0){
    for(cpt=0;cpt<10;cpt++){tab2[cpt] = 2;}

    printf("Le fils, tab2[] :  ");
    for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
    printf("\n");


    // Le fils copie tab2 dans le segment de mémoire partagée,
    // --TODO--
    memcpy(addr, tab2, 10 * sizeof(int));


    shmdt(addr);
  }
  else{
    usleep(500000);

    printf("Le pere, tab2[] :  ");
    for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
    printf("\n");

    usleep(500000);

    // --TODO--
    memcpy(tab2, addr, 10 * sizeof(int));

    printf("Le pere, tab2[] :  ");
    for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
    printf("\n");

    wait();
    printf("Fin du fils\n");

    shmdt(addr);
    shmctl(shmid, IPC_RMID, 0);
  }

  return 0;
}
