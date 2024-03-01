#include "execute.h"

int execute(int argc, char **argv)
{
    int size;
    int rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
