#include "process.h"

int process(int argc, char **argv)
{
    int size, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("\tsize:\t%d\n", size);
    }

    int gpsize, gprank;
    unsigned int color;

    getrandom(&color, sizeof(color), 0);
    color = color % args.ngroup;

    MPI_Comm comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, 0, &comm);

    MPI_Comm_size(comm, &gpsize);
    MPI_Comm_rank(comm, &gprank);

    MPI_File fpa, fpb, fpc;

    MPI_File_open(comm, "a.bin",
        MPI_MODE_RDONLY, MPI_INFO_NULL, &fpa);

    MPI_File_open(comm, "b.bin",
        MPI_MODE_RDONLY, MPI_INFO_NULL, &fpb);

    char fname[100];
    sprintf(fname, "c-%d.bin", color);

    MPI_File_open(comm, fname,
        MPI_MODE_CREATE | MPI_MODE_WRONLY,
        MPI_INFO_NULL, &fpc);

    MPI_File_set_size(fpc, args.nsize * args.nsize * sizeof(int));

    int rows = args.nsize / gpsize + 1;

    int from = gprank * rows;
    int to = from + rows;

    if (to > args.nsize) {
        to = args.nsize;
    }

    int *a = (int *)malloc((to - from) * args.nsize * sizeof(int));
    int *b = (int *)malloc(args.nsize * args.nsize * sizeof(int));

    MPI_File_read_at_all(fpa, from * args.nsize, a,
        (to - from) * args.nsize,
        MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_read_all(fpb, b,
        args.nsize * args.nsize,
        MPI_INT, MPI_STATUS_IGNORE);

    int *c = (int *)malloc((to - from) * args.nsize * sizeof(int));

    compute(c, a, b, from, to);

    MPI_File_write_at_all(fpc, from * args.nsize, c,
        (to - from) * args.nsize,
        MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_close(&fpa);
    MPI_File_close(&fpb);
    MPI_File_close(&fpc);

    MPI_Comm_free(&comm);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
