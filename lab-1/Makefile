CC := mpicc

matrix: compute.o main.o
	$(CC) -o matrix compute.o main.o

compute.o: compute.c compute.h
	$(CC) -o compute.o -c compute.c

main.o: main.c main.h
	$(CC) -o main.o -c main.c

clean:
	rm -f matrix
	rm -f compute.o
	rm -f main.o
