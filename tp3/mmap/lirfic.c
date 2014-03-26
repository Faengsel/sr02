#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  int nombre, fd, fin;

  fd=open("titi.dat",O_RDWR,0666);

  fin = read(fd, &nombre, sizeof(int));

  while( fin != 0){
    printf("%d ", nombre);

    fin = read(fd, &nombre, sizeof(int));
  }

  close(fd);

  return 0;
}
