#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "exo2.h"

int cpt = 0;
int len = 1;

int main () {
  listen_to_child();

  pid_t child = fork();

  // child process
  if (child == 0) {
    listen_to_parent();
    child_ready();

    while (1) { pause(); }
  }
  else {
    waitpid(child, NULL, 0);
    printf("\n");
  }

  return 0;
}

void parent_handler (int signum, siginfo_t * info, void * unused) {
  if (signum == SIGUSR2) {
    struct sigaction usr1;
    usr1.sa_sigaction = parent_handler;
    usr1.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGUSR1, &usr1, NULL);

    kill(info->si_pid, SIGUSR1);
  }
  else if (signum == SIGUSR1) {
    int i;
    for (i = 0; i < len && cpt < 26; i++) {
      printf("%c", (char)(65 + cpt));  
      fflush(stdout);
      cpt++;
    }
    len++;

    if (cpt < 26) {
      kill(info->si_pid, SIGUSR1);
    }
    else {
      kill(info->si_pid, SIGTERM);
    }
  }
}

void child_handler (int signum) {
  if (signum == SIGUSR1) {
    int i;
    for (i = 0; i < len && cpt < 26; i++) {
      printf("%c", (char)(97 + cpt));  
      fflush(stdout);
      cpt++;
    }
    len++;

    kill(getppid(), SIGUSR1);
  }
}

void listen_to_child () {
  struct sigaction usr2;

  usr2.sa_sigaction = parent_handler;
  usr2.sa_flags = SA_SIGINFO | SA_RESTART | SA_RESETHAND;
  sigaction(SIGUSR2, &usr2, NULL);
}

void listen_to_parent () {
  struct sigaction usr1;
  usr1.sa_handler = child_handler;
  sigaction(SIGUSR1, &usr1, NULL);
}

void child_ready () {
  int ppid = getppid();
  kill(ppid, SIGUSR2);
}

