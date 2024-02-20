CC := mpicc

matrix: main.o
	$(CC) -o matrix main.o

main.o: main.c main.h
	$(CC) -o main.o -c main.c

clean:
	rm -f matrix
	rm -f main.o
