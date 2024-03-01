#include "execute.h"

int execute(int argc, char **argv)
{
    int size;
    int rank;

    MPI_File fda;
    MPI_File fdb;

    srand(time(NULL));

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (args.ngroup > size) {
        args.ngroup = size;
    }

    args.nproc = size / args.ngroup;

    MPI_File_open(MPI_COMM_WORLD, "a.bin",
        MPI_MODE_CREATE | MPI_MODE_WRONLY,
        MPI_INFO_NULL, &fda);

    MPI_File_open(MPI_COMM_WORLD, "b.bin",
        MPI_MODE_CREATE | MPI_MODE_WRONLY,
        MPI_INFO_NULL, &fdb);

    if (rank == 0) {
        printf("size:\t%d\n", size);
        printf("ngroup:\t%d\n", args.ngroup);
        printf("nproc:\t%d\n", args.nproc);

        int t = 0;

        for (int i = 0; i < args.nsize; i++) {
            for (int j = 0; j < args.nsize; j++) {
                t = rand() % 20 - 10;
                MPI_File_write(fda, &t, 1, MPI_INT, MPI_STATUS_IGNORE);

                t = rand() % 20 - 10;
                MPI_File_write(fdb, &t, 1, MPI_INT, MPI_STATUS_IGNORE);
            }
        }
    }

    MPI_File_close(&fda);
    MPI_File_close(&fdb);

    int nsize;
    int nrank;

    int color = rank / (size / args.ngroup);

    MPI_Comm comm;

    MPI_Comm_split(MPI_COMM_WORLD, color, 0, &comm);

    MPI_Comm_size(comm, &nsize);
    MPI_Comm_rank(comm, &nrank);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
