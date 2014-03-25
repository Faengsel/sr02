#include "sharemem.h"

int main(){
    int cpt;

    // Initialiser à "1" deux tableaux d'entiers tab1[10] et tab2[10],
    int tab1[10] = {1}, tab2[10] = {1};

    // Créer et attacher un segment de mémoire partagée,
	int *ptr = shmget();

    // Faire un fork(),
    pid_t child = fork();
    if(child==-1) printf(stderr, "Erreur de creation du fils\n");
    if(child == 0){
        // Le fils met tab2[] à "2",
        for(cpt=0;cpt<10;cpt++){tab2[cpt] = 2;}

        // Le fils imprime tab2[],
        printf("Le fils, tab2[] :  ");
        for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
        printf("\n");

        // Le fils copie tab2 dans le segment de mémoire partagée,
        // --TODO--

        // Le fils se termine,
        exit(0);
    }
    else{
        // Le père attend 1/2 seconde,
        usleep(500000);

        // Le père imprime tab2[],
        printf("Le pere, tab2[] :  ");
        for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
        printf("\n");

        // Le père attend 1/2 seconde,
        usleep(500000);

        // Le père copie le segment de mémoire partagée dans tab2,
        // --TODO--

        // Le père imprime tab2[],
        printf("Le pere, tab2[] :  ");
        for(cpt=0;cpt<10;cpt++){printf("%d ", tab2[cpt]);}
        printf("\n");

        // Le père fait un wait de la fin du fils,
        wait();
        printf("Fin du fils\n");

        // Le père détruit le segment de mémoire partagée,
        // --TODO--

        // Le père se termine.
        exit(0);
    }
}
