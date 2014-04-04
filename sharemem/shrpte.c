#include "sharemem.h"


int main(){
	int cpt, cpt2;		// Pour les boucles etc..
	int shmid;		// Id dans la table système
	int **addr;		// Adresse virtuelle dans le processus de la zonne partagée pointeur vers un tableau de pointeur

	// Calculer la taille qu'il faut reserver pour le segment
		// 5 pointeurs et 5 tableaux de 3 entiers
	int taille = 5*sizeof(int**) + 5*3*sizeof(int);
	
	// Création d'un segment dans la table globale des seg de mem partagée et gestion erreurs
	shmid = shmget(CLE, taille, 0600|IPC_CREAT); // Droits: lecture/ecriture owner
	if(shmid == -1){perror("Creation du segment partage echoue");exit(1);}

	// Attachement en mode auto au segment de données du processus
	addr = shmat(shmid, 0, 0); 
	if(*addr == (int*)-1){perror("Attachement du segment echoue");exit(1);}


	// Init du tableau de pointeur avec les adresses correspondantes
	for(cpt=0;cpt<5;cpt++){
		addr[cpt] = (int*)((addr+5*sizeof(int*)) + (cpt*3*sizeof(int)));
	}

	// Init des vecteurs avec des nombres aléatoires
	srand(getpid());

	for(cpt=0;cpt<5;cpt++) 
		for(cpt2=0;cpt2<3;cpt2++) addr[cpt][cpt2] = random()%100;
	

	// Affichages demandés
	printf("\nshrpte:: Adresse tableau de pointeurs: %p\n", addr);
	
	printf("shrpte:: Contenu du tableau de pointeurs:\n");
	printf("\tCase\tContenu\n");
	for(cpt=0;cpt<5;cpt++) printf("\t%d\t%p\n", cpt, addr[cpt]);
	printf("\n");
	
	printf("shrpte:: Affichages des vecteurs:\n");
	printf("\tNum\tAdresse\t\t\tContenu\n");
	for(cpt=0;cpt<5;cpt++){
		printf("\t%d\t%p\t\t( ", cpt, addr[cpt]);
		for(cpt2=0;cpt2<3;cpt2++){
			if(cpt2!=0) printf(", ");
			if(addr[cpt][cpt2]<10) printf(" ");
			printf("%d ", addr[cpt][cpt2]);
		}
		printf(")\n");
	}

	// Détachement et suppression du segment
	shmdt(addr);
	
	//Attendre 40 sec et supprimer le segment
	sleep(40);
	shmctl(shmid, IPC_RMID, 0);

	printf("Fin du programme ecrivain\n");

	return 0;
}
