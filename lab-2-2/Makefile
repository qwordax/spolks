CC := mpicc

matrix: compute.o main.o process.o
	$(CC) -o matrix compute.o main.o process.o

compute.o: compute.c compute.h args.h
	$(CC) -o compute.o -c compute.c

main.o: main.c main.h args.h process.h
	$(CC) -o main.o -c main.c

process.o: process.c process.h args.h compute.h
	$(CC) -o process.o -c process.c

clean: remove
	rm -f matrix
	rm -f compute.o
	rm -f main.o
	rm -f process.o

remove:
	rm -rf bin
