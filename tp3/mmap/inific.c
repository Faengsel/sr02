#include "../sharemem/sharemem.h"

int main() {
  int tab1[10] = {11,22,33,44,55,66,77,88,99,1000};
  int fd;
  ssize_t w;

  if ((fd = open("titi.dat",O_RDWR|O_CREAT|O_TRUNC,0666)) < 0) {
    fprintf(stderr, "%s", strerror(errno));
    return -1;
  }

  if ((w = write (fd,tab1,10*sizeof(int))) < 0) {
    fprintf(stderr, "%s", strerror(errno));
    close(fd);
    return -1;
  }

  printf("%ld bytes written\n", w);

  close(fd);
  return 0;
}

