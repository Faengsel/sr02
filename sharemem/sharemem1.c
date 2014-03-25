#include "sharemem.h"

int main(){
    int cpt;

    // Initialiser � "1" deux tableaux d'entiers tab1[10] et tab2[10],
    int tab1[10] = {1}, tab2[10] = {1};

    // Cr�er et attacher un segment de m�moire partag�e,
	int *ptr = shmget();

    // Faire un fork(),
    pid_t child = fork();
    if(child==-1) printf(stderr, "Erreur de creation du fils\n");
    if(child == 0){
        // Le fils met tab2[] � "2",
        for(cpt=0;cpt<10;cpt++){tab2[cpt] = 2;}

        // Le fils imprime tab2[],
        printf("Le fils, tab2[] :  ");
        for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
        printf("\n");

        // Le fils copie tab2 dans le segment de m�moire partag�e,
        // --TODO--

        // Le fils se termine,
        exit(0);
    }
    else{
        // Le p�re attend 1/2 seconde,
        usleep(500000);

        // Le p�re imprime tab2[],
        printf("Le pere, tab2[] :  ");
        for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
        printf("\n");

        // Le p�re attend 1/2 seconde,
        usleep(500000);

        // Le p�re copie le segment de m�moire partag�e dans tab2,
        // --TODO--

        // Le p�re imprime tab2[],
        printf("Le pere, tab2[] :  ");
        for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
        printf("\n");

        // Le p�re fait un wait de la fin du fils,
        wait();
        printf("Fin du fils\n");

        // Le p�re d�truit le segment de m�moire partag�e,
        // --TODO--

        // Le p�re se termine.
        exit(0);
    }
}
