#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

#include "sem_pv.h"

int main(){
	int a; 				// Variable de l'�nonc�
	int cpt;			// Pour les boucles etc..
	int shmid;			// Id dans la table syst�me
	int *addr;			// Adresse virtuelle dans le processus de la zonne partag�e


	// Cr�ation d'un segment dans la table globale des seg de mem partag�e et gestion erreurs
	shmid = shmget(IPC_PRIVATE, sizeof(int), 0600|IPC_CREAT|IPC_EXCL|IPC_PRIVATE);	// Droits: lecture+ecriture owner
	if(shmid == -1){perror("Creation du segment partage echoue");exit(1);}

	// Attachement en mode auto au segment de donn�es du processus
	addr = shmat(shmid, 0, 0); 
	if(*addr == -1){perror("Attachement du segment echoue");exit(1);}

	// On cr�er un fils et on g�re les erreurs
	pid_t child = fork();
	if(child==-1){perror("Erreur creation du fils");exit(1);}
	
	// Initialisation de l'entier "E" � 0
	*addr = 0;
	
	// Cr�er semaphore
	if(init_semaphore() < 0){perror("Erreur creation semaphore");exit(1);}
	
	// Init � 1
	 if(val_sem(0, 1) < 0){perror("Erreur initialisation semaphore");exit(1);}
	

	// --------- FILS ---------	
	if(child == 0){
		// Initialisation random
		srand(getpid());

		for(cpt=0;cpt<100;cpt++){
			/* SECTION CRITIQUE */
			P(0);
			a = *addr;
			usleep(20+rand()%80);
			a++;
			*addr = a;
			V(0);
			/* FIN SECTION CRITIQUE */

			usleep(20+rand()%80);
		}

		// Le fils se d�tache du segment partag�
		shmdt(addr);
	}


	// --------- PERE ---------
	else{	
		// Initialisation random
		srand(getpid());

		for(cpt=0;cpt<100;cpt++){
			/* SECTION CRITIQUE */
			P(0);
			a = *addr;
			usleep(20+rand()%80);
			a++;
			*addr = a;
			V(0);
			/* FIN SECTION CRITIQUE */

			usleep(20+rand()%80);
		}
		
		// Attente de la fin du fils
		wait();
		printf("A la fin E= %d\n", *addr);
		
		// Destruction
		detruire_semaphore();

		// D�tachement et suppression du segment
		shmdt(addr);
		shmctl(shmid, IPC_RMID, 0);

		printf("Fin du pere\n");
	}
	
	return 0;
}
