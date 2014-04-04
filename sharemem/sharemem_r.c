#include "sharemem.h"

int main(){
	int tab2[10];			// Tableau de reception
	
	int cpt;			// Pour les boucles etc..
	int shmid;			// Id dans la table système
	int *addr;			// Adresse virtuelle dans le processus de la zonne partagée (int* imposé)


	// Création d'un segment dans la table globale des seg de mem partagée et gestion erreurs
	shmid = shmget(CLE, sizeof(tab2), 0400);	// Droits: lecture owner
	if(shmid == -1){perror("Creation du segment partage echoue");exit(1);}

	// Attachement en mode auto au segment de données du processus
	addr = shmat(shmid, 0, SHM_RDONLY); 
	if(*addr == -1){perror("Attachement du segment echoue");exit(1);}

	// Copie tab2 dans le segment de mémoire partagée
		/* L'énoncé impose un pointeur d'entier pour l'accès au segment, on suppose
		donc qu'il faut faire une boucle mais un memcpy aurait aussi fonctionné */
	for(cpt=0;cpt<10;cpt++){tab2[cpt]=addr[cpt];}
	
	// Affichage après
		printf("Affichage de ce qui a ete lu par le lecteur:\n");
		for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
		printf("\n");

	// Détachement du segment, sheremem_e le supprimera 
	shmdt(addr);

	printf("Fin du programme lecteur\n");

	return 0;
}
