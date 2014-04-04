#include "sharemem.h"

int main(){
	int tab2[10] = {[0 ... 9]= 1};	// Initialisation de toutes les cases a "1" (uniquement sous GCC)
	
	int cpt;			// Pour les boucles etc..
	int shmid;			// Id dans la table système
	int *addr;			// Adresse virtuelle dans le processus de la zonne partagée (int* imposé)


	// Création d'un segment dans la table globale des seg de mem partagée et gestion erreurs
	shmid = shmget(IPC_PRIVATE, sizeof(tab2), 0600|IPC_CREAT|IPC_EXCL|IPC_PRIVATE);	// Droits: lecture+ecriture owner
	if(shmid == -1){perror("Creation du segment partage echoue");exit(1);}

	// Attachement en mode auto au segment de données du processus
	addr = shmat(shmid, 0, 0); 
	if(*addr == -1){perror("Attachement du segment echoue");exit(1);}

	// On créer un fils et on gère les erreurs
	pid_t child = fork();
	if(child==-1){perror("Erreur creation du fils");exit(1);}


	// --------- FILS ---------	
	if(child == 0){
		// Toutes les cases sont mises à "2"
		for(cpt=0;cpt<10;cpt++){tab2[cpt] = 2;}
		
		// Affichage
		printf("Le fils, tab2[] :  ");
		for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
		printf("\n");


		// Le fils copie tab2 dans le segment de mémoire partagée
			/* L'énoncé impose un pointeur d'entier pour l'accès au segment, on suppose
			donc qu'il faut faire une boucle mais un memcpy aurait aussi fonctionné */
		for(cpt=0;cpt<10;cpt++){addr[cpt]=tab2[cpt];}

		// Le fils se détache du segment partagé
		shmdt(addr);
	}


	// --------- PERE ---------
	else{	
		// Attendre 1/2 seconde
		usleep(500000);
		
		// Affichage avant
		printf("Le pere, tab2[] local:  ");
		for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
		printf("\n");

		usleep(500000);

		// Le père copie le contenu de la mémoire partégée dans son tab2
		for(cpt=0;cpt<10;cpt++){tab2[cpt]=addr[cpt];}

		// Affichage après
		printf("Le pere, tab2[] apres copie depuis shm:  ");
		for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
		printf("\n");
		
		// Attente de la fin du fils
		wait();
		printf("Fin du fils\n");
		
		// Détachement et suppression du segment
		shmdt(addr);
		shmctl(shmid, IPC_RMID, 0);

		printf("Fin du pere\n");
	}
	
	return 0;
}
