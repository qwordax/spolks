CC := mpicc

matrix: main.o process.o
	$(CC) -o matrix main.o process.o

main.o: main.c main.h args.h
	$(CC) -o main.o -c main.c

process.o: process.c process.h args.h
	$(CC) -o process.o -c process.c

clean:
	rm -f matrix
	rm -f main.o
	rm -f process.o
