#include "main.h"

int opterr = 0;

struct {
    int c;
    int i;
} flags;

int main(int argc, char **argv)
{
    int size = 0;
    int rank = 0;

    int res = 0;

    srand(time(NULL));

    while ((res = getopt(argc, argv, "cih")) != -1) {
        switch (res) {
            case 'c':
                flags.c = 1;
                break;
            case 'i':
                flags.i = 1;
                break;
            case 'h':
                fprintf(stdout, "usage: %s [-ci] <size>\n", argv[0]);
                return EXIT_SUCCESS;
            default:
                fprintf(stderr, "%s: error: invalid option \'%c\'\n", argv[0], optopt);
                return EXIT_FAILURE;
        }
    }

    if (argv[optind] == NULL) {
        fprintf(stderr, "%s: error: no arguments provided\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[optind + 1] != NULL) {
        fprintf(stderr, "%s: error: too many arguments\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *sptr = argv[optind];
    char *eptr = NULL;

    int n = strtol(sptr, &eptr, 0);

    if (n <= 0 || *sptr == '\0' || *eptr != '\0') {
        fprintf(stderr, "%s: error: invalid input\n", argv[0]);
        return EXIT_FAILURE;
    }

    int *a = (int *)malloc(n * n * sizeof(int));
    int *b = (int *)malloc(n * n * sizeof(int));
    int *c = (int *)malloc(n * n * sizeof(int));
    int *d = (int *)malloc(n * n * sizeof(int));

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Request req[2];

    int rows = (n / size) + 1;

    int from = 0;
    int to = 0;

    double start = 0.0;
    double end = 0.0;

    if (rank == 0) {
        printf("size:\t%d\n", size);
        printf("rows:\t%d\n", rows);

        start = MPI_Wtime();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i * n + j] = rand() % 20 - 10;
                b[i * n + j] = rand() % 20 - 10;
            }
        }

        for (int r = 1; r < size; r++) {
            from = r * rows;
            to = from + rows;

            if (to > n) {
                to = n;
            }

            if (flags.i) {
                MPI_Isend(a + from * n, (to - from) * n, MPI_INT,
                    r, MSG_TAG, MPI_COMM_WORLD, &req[0]);
                MPI_Isend(b, n * n, MPI_INT,
                    r, MSG_TAG, MPI_COMM_WORLD, &req[1]);

                MPI_Waitall(2, req, MPI_STATUS_IGNORE);
            } else {
                MPI_Send(a, n * n, MPI_INT,
                    r, MSG_TAG, MPI_COMM_WORLD);
                MPI_Send(b, n * n, MPI_INT,
                    r, MSG_TAG, MPI_COMM_WORLD);
            }
        }

        from = rank * rows;
        to = from + rows;

        if (to > n) {
            to = n;
        }

        compute(c, a, b, from, to, n);

        for (int r = 1; r < size; r++) {
            from = r * rows;
            to = from + rows;

            if (to > n) {
                to = n;
            }

            if (flags.i) {
                MPI_Irecv(c + from * n, (to - from) * n, MPI_INT,
                    r, MSG_TAG, MPI_COMM_WORLD, &req[0]);

                MPI_Waitall(1, req, MPI_STATUS_IGNORE);
            } else {
                MPI_Recv(c + from * n, (to - from) * n, MPI_INT,
                    r, MSG_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        end = MPI_Wtime();
    }

    if (rank != 0) {
        from = rank * rows;
        to = from + rows;

        if (to > n) {
            to = n;
        }

        if (flags.i) {
            MPI_Irecv(a + from * n, (to - from) * n, MPI_INT,
                0, MSG_TAG, MPI_COMM_WORLD, &req[0]);
            MPI_Irecv(b, n * n, MPI_INT,
                0, MSG_TAG, MPI_COMM_WORLD, &req[1]);

            MPI_Waitall(2, req, MPI_STATUS_IGNORE);
        } else {
            MPI_Recv(a, n * n, MPI_INT,
                0, MSG_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(b, n * n, MPI_INT,
                0, MSG_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        compute(c, a, b, from, to, n);

        if (flags.i) {
            MPI_Isend(c + from * n, (to - from) * n, MPI_INT,
                0, MSG_TAG, MPI_COMM_WORLD, &req[0]);

            MPI_Waitall(1, req, MPI_STATUS_IGNORE);
        } else {
            MPI_Send(c + from * n, (to - from) * n, MPI_INT,
                0, MSG_TAG, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        printf("time:\t%.2fs\n", end - start);

        if (flags.c) {
            start = MPI_Wtime();
            compute(d, a, b, 0, n, n);
            end = MPI_Wtime();

            printf("check:\t%.2fs\n", end - start);
            printf("%s\n", equal(c, d, n) ? "true" : "false");
        }
    }

    MPI_Finalize();

    free(a);
    free(b);
    free(c);
    free(d);

    return EXIT_SUCCESS;
}
