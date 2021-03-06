#include "sharemem.h"


int main(){
	int cpt, cpt2;			// Pour les boucles etc..
	int shmid;			// Id dans la table syst�me
	int **addr;			// Adresse virtuelle dans le processus de la zonne partag�e (int* impos�)

	
	// Recuperer le segment dans la table globale des seg de mem partag�e
	shmid = shmget(CLE, 0, 0400); // Droits: lecture owner
	if(shmid == -1){perror("Creation du segment partage echoue");exit(1);}

	// Attachement en mode auto au segment de donn�es du processus
	addr = shmat(shmid, 0, 0); 
	if(*addr == (int*)-1){perror("Attachement du segment echoue");exit(1);}
	
	// Init du tableau de pointeur - il faut remettre les adresses correctement car chgt de zone mem virtuelle
	for(cpt=0;cpt<5;cpt++){
		addr[cpt] = (int*)((addr+5*sizeof(int*)) + (cpt*3*sizeof(int)));
	}

	// Affichages demand�s
	printf("\nshrptr:: Adresse tableau de pointeurs: %p\n", addr);
	
	printf("shrptr:: Contenu du tableau de pointeurs:\n");
	printf("\tCase\tContenu\n");
	for(cpt=0;cpt<5;cpt++) printf("\t%d\t%p\n", cpt, addr[cpt]);
	printf("\n");
	
	printf("shrptr:: Affichages des vecteurs:\n");
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


	// D�tachement et suppression du segment
	shmdt(addr);
	
	printf("Fin du programme lecteur\n");

	return 0;
}
