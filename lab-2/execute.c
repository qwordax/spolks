#include "execute.h"

int execute(int argc, char **argv)
{
    fill();

    int size;
    int rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("\tsize:\t%d\n", size);
    }

    int csize;
    int crank;

    unsigned int color;

    getrandom(&color, sizeof(color), 0);
    color = color % args.ngroup;

    MPI_Comm comm;

    MPI_Comm_split(MPI_COMM_WORLD, color, 0, &comm);

    MPI_Comm_size(comm, &csize);
    MPI_Comm_rank(comm, &crank);

    if (crank == 0) {
        printf("\tgroup:\t%d:%d\n", color, csize);
    }

    int rows = (args.nsize / csize) + 1;

    int from = crank * rows;
    int to = from + rows;

    if (to > args.nsize) {
        to = args.nsize;
    }

    double start = 0.0;
    double end = 0.0;

    if (crank == 0) {
        printf("[%d]\ttime:\t%.2fs\n", color, end - start);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
