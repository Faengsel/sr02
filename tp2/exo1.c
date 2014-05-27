#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void handler (int signum) {
  if (signum == SIGUSR1) {
    printf("SIGUSR1 received\n");
  }
}

int main () {
  pid_t child = fork();

  // child process
  if (child == 0) {
    struct sigaction act;
    act.sa_handler = handler;

    sigaction(SIGUSR1, &act, NULL);
    while (1) {
      pause();
    }
  }
  else {
    while (1) {
      sleep(2);
      printf("Sending SIGUSR1\n");
      kill(child, SIGUSR1); 
    }
  }

  return 0;
}
