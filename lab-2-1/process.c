#include "process.h"

int process(int argc, char **argv)
{
    int size;
    int rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("\tsize:\t%d\n", size);
    }

    int gpsize;
    int gprank;

    unsigned int color;

    getrandom(&color, sizeof(color), 0);
    color = color % args.ngroup;

    MPI_Comm comm;

    MPI_Comm_split(MPI_COMM_WORLD, color, 0, &comm);

    MPI_Comm_size(comm, &gpsize);
    MPI_Comm_rank(comm, &gprank);

    double start = MPI_Wtime();

    int rows = args.nsize / gpsize + 1;

    int from = gprank * rows;
    int to = from + rows;

    if (to > args.nsize) {
        to = args.nsize;
    }

    int *a = (int *)malloc(args.nsize * args.nsize * sizeof(int));
    int *b = (int *)malloc(args.nsize * args.nsize * sizeof(int));
    int *c = (int *)malloc(args.nsize * args.nsize * sizeof(int));

    int *counts = (int *)malloc(gpsize * sizeof(int));
    int *displs = (int *)malloc(gpsize * sizeof(int));

    if (gprank == 0) {
        int tmp;

        for (int i = 0; i < args.nsize * args.nsize; i++) {
            getrandom(&tmp, sizeof(tmp), 0);
            a[i] = tmp % 10;

            getrandom(&tmp, sizeof(tmp), 0);
            b[i] = tmp % 10;
        }

        for (int i = 0; i < gpsize; i++) {
            int ifrom = i * rows;
            int ito = ifrom + rows;

            if (ito > args.nsize) {
                ito = args.nsize;
            }

            counts[i] = (ito - ifrom) * args.nsize;
            displs[i] = ifrom * args.nsize;
        }
    }

    MPI_Scatterv(a, counts, displs, MPI_INT,
        a, (to - from) * args.nsize, MPI_INT, 0, comm);

    MPI_Bcast(b, args.nsize * args.nsize, MPI_INT, 0, comm);

    compute(c, a, b, from, to);

    MPI_Gatherv(c, (to - from) * args.nsize, MPI_INT,
        c, counts, displs, MPI_INT, 0, comm);

    MPI_Comm_free(&comm);

    double end = MPI_Wtime();

    if (gprank == 0) {
        printf("[%d]\tgroup:\t%d\n", color, gpsize);
        printf("\ttime:\t%.2fs\n", end - start);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
