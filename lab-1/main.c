#include "main.h"

int opterr = 0;

int main(int argc, char **argv)
{
    int size = 0;
    int rank = 0;

    int opt = 0;
    int res = 0;

    while ((res = getopt(argc, argv, "hi")) != -1) {
        switch (res) {
            case 'h':
                fprintf(stdout, "usage: %s [-i]\n", argv[0]);
                return EXIT_SUCCESS;
            case 'i':
                opt = 1;
                break;
            default:
                fprintf(stderr, "error: invalid option \'%c\'\n", optopt);
                return EXIT_FAILURE;
        }
    }

    if (argv[optind] == NULL) {
        fprintf(stderr, "error: no matrix size\n");
        return EXIT_FAILURE;
    }

    char *sptr = argv[optind];
    char *eptr = NULL;

    int n = strtol(sptr, &eptr, 0);

    if (n <= 0 || *sptr == '\0' || *eptr != '\0') {
        fprintf(stderr, "error: invalid input\n");
        return EXIT_FAILURE;
    }

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
