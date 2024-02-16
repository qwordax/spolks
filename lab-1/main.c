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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i * n + j] = rand() % 20 - 10;
            b[i * n + j] = rand() % 20 - 10;
        }
    }

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Finalize();

    if (rank == 0 && flags.c) {
        printf("%s\n", equal(c, d, n, n) ? "true" : "false");
    }

    free(a);
    free(b);
    free(c);
    free(d);

    return EXIT_SUCCESS;
}
