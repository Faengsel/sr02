/* thx.c exemple threads+X11 *
 * appelle routines definies dans thw.c et barx.c *
 * > gcc -o thx thx.c barx.o -L/usr/X11R6/lib/ -lX11 -lpthread */

/* main lance des threads qui chacun: *
 * fait progresser un rectangle horizontal, */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#define nth 3 /* nbre de threads a lancer */

/* thx.c exemple threads+X11 */
/* gcc -o thx thx.c thw.o barx.o -lX11 -lpthread */

/*pthread_t threads[nth];*/
/*pthread_mutex_t mutex;*/
/*pthread_cond_t event;*/
/*is = pthread_mutex_init(&mutex, NULL);*/
/*is = pthread_cond_init (&event, NULL);*/
/*is = pthread_mutex_lock(&mutex);*/
/*is = pthread_mutex_unlock(&mutex);*/
/*is = pthread_cond_signal(&event);*/
/*is = pthread_cond_wait(&event,&mutex);*/
/*is = pthread_create(&threads[i], NULL, th_fonc, (void *)i);*/
/*is = pthread_join( threads[j], &val);*/

pthread_mutex_t mutex;
pthread_cond_t event;

char* colors[] = { "yellow", "white", "green" };
int total = 0;

void *th_fonc (void *arg) {
	int numero = (int)arg, 
      m = 20 + numero * 10,
      j, k; 

  char str[10];
  sprintf(str, "_%d_", numero);

  pthread_mutex_lock(&mutex);
	drawstr (30, 50 * (numero + 1) + 25/*125*/, str, 3);
	drawrec (100,50 * (numero + 1),100+m*10,30);
  for (j=1;j<=m;j++) {
    printf("num %d j=%d\n",numero,j);
    /*pthread_cond_wait(&event, &mutex);*/
    usleep(100000);
    fillrec (100,50 * (numero + 1) + 2,100+j*10,26,colors[numero]);
    pthread_mutex_unlock(&mutex);
  }
  pthread_mutex_lock(&mutex);
	flushdis ();
  total += m;
  k = total;
  pthread_mutex_unlock(&mutex);

	return (void*)k;
}

int main () {
  long is, i;
  void *val=0;

  pthread_t threads[nth];

  XInitThreads();
  initrec();

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&event, NULL);
  /*pthread_mutex_lock(&mutex);*/
  /*pthread_cond_signal(&event);*/
  
  /* créer les threads */
  for(i=0; i<nth; i++) {
    printf("ici main, création thread %ld\n",i);
    if (pthread_create( &threads[i], NULL, th_fonc, (void *)i ) != 0) {
      fprintf(stderr, "Erreur dans pthread_create\n");   
      return -1;
    }
  }

  /* attendre fin des threads */
  for(i=0; i<nth; i++) {
    is = pthread_join( threads[i], &val);
    printf("ici main, fin thread %ld\n",(long)val);
  }

  char buffer[10];
  scanf("%s", buffer);
  detruitrec();
}
