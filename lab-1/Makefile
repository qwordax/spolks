CC := mpicc

matrix: compute.o equal.o main.o
	$(CC) -o matrix compute.o equal.o main.o

compute.o: compute.c compute.h
	$(CC) -o compute.o -c compute.c

equal.o: equal.c equal.h
	$(CC) -o equal.o -c equal.c

main.o: main.c compute.h equal.h main.h
	$(CC) -o main.o -c main.c

clean:
	rm -f matrix
	rm -f compute.o
	rm -f equal.o
	rm -f main.o
