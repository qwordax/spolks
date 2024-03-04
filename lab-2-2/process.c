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

    MPI_File_open(comm, FOLDER FILE_A,
        MPI_MODE_RDONLY, MPI_INFO_NULL, &fpa);

    MPI_File_open(comm, FOLDER FILE_B,
        MPI_MODE_RDONLY, MPI_INFO_NULL, &fpb);

    char fname[100];
    sprintf(fname, FOLDER FILE_C, color);

    MPI_File_open(comm, fname,
        MPI_MODE_CREATE | MPI_MODE_WRONLY,
        MPI_INFO_NULL, &fpc);

    MPI_File_set_size(fpc, args.nsize * args.nsize * sizeof(int));

    double start = MPI_Wtime();

    int rows = args.nsize / gpsize + (args.nsize % gpsize != 0);

    int from = gprank * rows;
    int to = from + rows;

    if (to > args.nsize) {
        to = args.nsize;
    }

    if (from > to) {
        from = to;
    }

    int *a = (int *)malloc((to - from) * args.nsize * sizeof(int));
    int *b = (int *)malloc(args.nsize * args.nsize * sizeof(int));
    int *c = (int *)malloc((to - from) * args.nsize * sizeof(int));

    MPI_File_read_at_all(fpa, from * args.nsize * sizeof(int),
        a, (to - from) * args.nsize,
        MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_read_all(fpb,
        b, args.nsize * args.nsize,
        MPI_INT, MPI_STATUS_IGNORE);

    compute(c, a, b, to - from, args.nsize);

    MPI_File_write_at_all(fpc, from * args.nsize * sizeof(int),
        c, (to - from) * args.nsize,
        MPI_INT, MPI_STATUS_IGNORE);

    double end = MPI_Wtime();

    if (gprank == 0) {
        printf("[%d]\tgroup:\t%d\n", color, gpsize);
        printf("\trows:\t%d\n", rows);
        printf("\ttime:\t%.2fs\n", end - start);
    }

    free(a);
    free(b);
    free(c);

    MPI_File_close(&fpa);
    MPI_File_close(&fpb);
    MPI_File_close(&fpc);

    MPI_Comm_free(&comm);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
