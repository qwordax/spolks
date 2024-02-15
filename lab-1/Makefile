PROGRAM := matrix

CC := mpicc

$(PROGRAM): main.o
	$(CC) -o $(PROGRAM) main.o

main.o: main.c
	$(CC) -o main.o -c main.c

clean:
	rm -f $(PROGRAM)
	rm -f main.o
