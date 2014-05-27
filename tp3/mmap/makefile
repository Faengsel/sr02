CC=gcc
EXEC=inific lirfic modfic showfic

all: $(EXEC)

inific: inific.o
	$(CC) $^ -o $@

lirfic: lirfic.o
	$(CC) $^ -o $@

modfic: modfic.o common.o
	$(CC) $^ -o $@

showfic: showfic.o common.o
	$(CC) $^ -o $@

%.o: %.c 
	$(CC) -c $< -o $@

clean:
	rm -rvf *.o $(EXEC) 
