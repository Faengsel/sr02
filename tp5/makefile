CC=gcc

all: sem1 prod-conso

sem1: libsempv.a
	$(CC) -o sem1 sem1.c -L. -lsempv

sem1.c: libsempv.a

libsempv.a: sem_pv.o
	ar rvs libsempv.a sem_pv.o

sem_pv.o:
	$(CC) -c sem_pv.c -o sem_pv.o

prod-conso: libsempv.a
	$(CC) prod-conso.c -o prod-conso -L. -lsempv

clean:
	rm -rvf sem1 prod-conso libsempv.a sem_pv.o

.PHONY: clean


