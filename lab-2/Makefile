CC := mpicc

matrix: execute.o main.o
	$(CC) -o matrix execute.o main.o

execute.o: execute.c execute.h args.h
	$(CC) -o execute.o -c execute.c

main.o: main.c main.h args.h execute.h
	$(CC) -o main.o -c main.c

clean:
	rm -f matrix
	rm -f execute.o
	rm -f main.o
