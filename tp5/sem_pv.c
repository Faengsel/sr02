#include "sem_pv.h"

static int semid = -1;

int init_semaphore () {
  // si deja initialisee
	if (semid != -1) { 
    fprintf(stderr, "err: Les semaphores sont deja initialisees\n");
    return -1;	
  }

	if ((semid = semget(IPC_PRIVATE,N_SEM,0666)) == -1) {
    // echec de creation
    fprintf(stderr, "err: semget\n");
    return -2;
  }

	int i = 0, ret;	
	union semnum valeur;
	valeur.val = 0;
  
  // Les semaphores du groupe sont identifies par un entier 
  // dont la valeur varie de 0 a N_SEM-1
	for (i = 0; i < N_SEM; i++) {
    ret = val_sem(0, i);
    if (ret == -2) {
      return -2; 
    }
	}

	return 0;	
}

int detruire_semaphore () {
	if (semid == -1) { 
    fprintf(stderr, "err: Aucune semaphore a detruire\n");
    return -1; 
  }

	return semctl(semid,0,IPC_RMID,0);
}

int val_sem (int val, int sem) {
	if (semid == -1) {
    fprintf(stderr, "err: Aucune semaphore\n");
    return -1;
  }

	union semnum valeur;
	valeur.val = val;
	if (semctl(semid,sem,SETVAL,valeur) == -1) { 
    fprintf(stderr, "erreur lors de la modification de la semaphore %d\n", sem);
    return -2; 
  }

  return 0;
}

int P(int sem){
	if (semid == -1) { 
    fprintf(stderr, "err: Aucune semaphore\n");
    return -1; 
  }

	struct sembuf A;
	A.sem_num = sem;	
	A.sem_op = -1;
	A.sem_flg = 0;

  printf("going to return\n");
	return semop(semid, &A, 1);
}

int V (int sem) {
	if (semid == -1) { 
    fprintf(stderr, "err: Aucune semaphore\n");
    return -1; 
  }

	struct sembuf B;
	B.sem_num = sem;	
	B.sem_op = 1;
	B.sem_flg = 0;
	return semop(semid, &B, 1);
}

