#include "sem_pv.h"
#include <errno.h>

static int semid = -1;
static struct sembuf	op_P = {-1, -1, 0},
			op_V = {-1, 1, 0};

  union semun {
               int val;
               struct semid_ds *buf;
               ushort *array;
          };
			
/*-------------------------------------------------------------------------*/			
int init_semaphore(void)
{
  int i;
  union semun arg0;

  arg0.val=0;

  if(semid != -1)
  {
    fprintf(stderr, "Creation deja realisee\n");
    return(1);
  }

  if((semid=semget(IPC_PRIVATE, N_SEM, 0600))==-1)
  {
    fprintf(stderr, "%d Creation des semaphores impossible : ", errno);
    perror(NULL);
    return(2);
  }

  for(i=0; i<N_SEM; i++) semctl(semid, i, SETVAL, arg0);

  return(0);
}

/*-------------------------------------------------------------------------*/
int detruire_semaphore(void)
{
  int val;

  if(semid == -1)
  {
    fprintf(stderr, "Semaphores non crees\n");
    return(-1);
  }

  val=semctl(semid,0,IPC_RMID,0);
  semid=-1;
  return(val);
}

/*-------------------------------------------------------------------------*/
int val_sem(int numero, int val)
{
  union semun argval;

  argval.val=val;

  if(semid == -1)
  {
    fprintf(stderr, "Semaphores non crees\n");
    return(-1);
  }

  if(numero<0 || numero>=N_SEM)
  {
    fprintf(stderr, "Numero de semaphore incorrect\n");
    return(-2);
  }

  return(semctl(semid, numero, SETVAL, argval));
}

/*-------------------------------------------------------------------------*/
int P(int numero)
{
  if(semid == -1)
  {
    fprintf(stderr, "Semaphores non crees\n");
    return(-1);
  }

  if(numero<0 || numero>=N_SEM)
  {
    fprintf(stderr, "Numero de semaphore incorrect\n");
    return(-2);
  }

  op_P.sem_num=numero;

  return(semop(semid, &op_P, 1));
}

/*-------------------------------------------------------------------------*/
int V(int numero)
{
  if(semid == -1)
  {
    fprintf(stderr, "Semaphores non crees\n");
    return(-1);
  }

  if(numero<0 || numero>=N_SEM)
  {
    fprintf(stderr, "Numero de semaphore incorrect\n");
    return(-2);
  }

  op_V.sem_num=numero;

  return(semop(semid, &op_V, 1));
}


