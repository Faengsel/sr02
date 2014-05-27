#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>

sigjmp_buf context;

int probe (long addr) {
  if (sigsetjmp(context, 1) != 0) {
    return 0;
  }

  int * useless = (int*)addr;
  int even_more_useless = *useless; 

  return 1;
}

void signal_handler (int signum) {
  if (signum == SIGSEGV) {
    siglongjmp(context, 1);
  }
}

int main () {
  struct sigaction act;
  act.sa_handler = signal_handler;
  sigaction(SIGSEGV, &act, NULL);

  int tab[1000];
  int index = 1;
  long ia1;
  int i;

  while (1) {
    ia1 = (long)&tab[index];
    i = probe(ia1);

    if (i==0) {
      printf("probe failed at index=%d ia1=%lx\n",index,ia1);
      break;
    }

    index++;
  }
}


