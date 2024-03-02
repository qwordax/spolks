#include "process.h"

int process(int argc, char **argv)
{
    int size, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("\tsize:\t%d\n", size);
        printf("\tgroup:\t%d\n", args.ngroup);
    }

    int gpsize, gprank;
    unsigned int color;

    getrandom(&color, sizeof(color), 0);
    color = color % args.ngroup;

    MPI_Comm comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, 0, &comm);

    MPI_Comm_size(comm, &gpsize);
    MPI_Comm_rank(comm, &gprank);

    MPI_Comm_free(&comm);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
