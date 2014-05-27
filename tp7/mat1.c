#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>

#define maxsize 5000

double A[maxsize][maxsize] , X[maxsize] , Y[maxsize] , D;
double B[maxsize][maxsize] , C[maxsize][maxsize];

int i, j, k;

void initaxy(int size){
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			A[i][j]=B[i][j]=(double)(i+j);
			C[i][j]=0.0;
		}
	}
}

void mulaxy(int size){
	for(i=0; i<size; i++)
      for(j=0; j<size; j++){
			C[i][j]=0;
			for(k=0; k<size; k++) C[i][j]+=A[i][k]*B[k][j];
		}
}

void sumdiac(int size){
	D=0;
	for(i=0; i<size; i++) D+=C[i][i];
}

int main(int argc, char* argv[]){
	// Verif arguments
	if(argc < 2){
		printf("Il manque un argument size\n");
		return -1;
	}
	int size = atoi(argv[1]);



	clock_t tbegin , tend;
	struct tms tmsbufbegin, tmsbufend;
	double tickspsec, delai;

	tbegin=times(&tmsbufbegin);

	/* traitement ou appel de fonction à mesurer */
	initaxy(size);
	mulaxy(size);
	sumdiac(size);
	
	
	tend=times(&tmsbufend);
	tickspsec = sysconf(_SC_CLK_TCK);
	delai=(tend-tbegin)/tickspsec; 


	
	printf("Valeur de D: %.2f\n", D);
	printf("Calcul effectue en: %.4f secondes \n", delai);
	return 0;
} 
