CC := mpicc

matrix: compute.o execute.o fill.o main.o
	$(CC) -o matrix compute.o execute.o fill.o main.o

compute.o: compute.c compute.h
	$(CC) -o compute.o -c compute.c

execute.o: execute.c execute.h args.h compute.h
	$(CC) -o execute.o -c execute.c

fill.o: fill.c fill.h args.h
	$(CC) -o fill.o -c fill.c

main.o: main.c main.h args.h execute.h
	$(CC) -o main.o -c main.c

clean:
	rm -f matrix
	rm -f compute.o
	rm -f execute.o
	rm -f fill.o
	rm -f main.o

bin:
	rm -f *.bin
