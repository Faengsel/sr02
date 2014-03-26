#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "common.h"
#include "lirfic.h"

int main() {
  int nombres[BUFFER_SIZE], fd;
  unsigned int i;
  ssize_t r;

  if ((fd = open(FILENAME,O_RDWR,0666)) < 0) {
    fprintf(stderr, "%s", strerror(errno));
    return -1;
  }

  while ((r = read(fd, &nombres, BUFFER_SIZE * sizeof(int))) > 0) {
    printf("%ld bytes read\n", r);
    for (i = 0; i < (r / sizeof(int)); i++) {
      printf("%d ", nombres[i]);
    }
  }

  printf("\n");

  if (r < 0) {
    fprintf(stderr, "%s", strerror(errno));
    close(fd);
    return -1;
  }

  close(fd);

  return 0;
}
