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
        printf("size:\t%d\n", size);
    }

    int nsize;
    int nrank;

    unsigned int color;

    getrandom(&color, sizeof(color), 0);
    color = color % args.ngroup;

    MPI_Comm comm;

    MPI_Comm_split(MPI_COMM_WORLD, color, 0, &comm);

    MPI_Comm_size(comm, &nsize);
    MPI_Comm_rank(comm, &nrank);

    if (nrank == 0) {
        printf("group:\t%d\n", color);
    }

    int rows = (args.nsize / nsize) + 1;

    int from = nrank * rows;
    int to = from + rows;

    if (to > args.nsize) {
        to = args.nsize;
    }

    double start = 0.0;
    double end = 0.0;

    if (nrank == 0) {
        printf("[%d]\t%.2fs\n", color, end - start);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
