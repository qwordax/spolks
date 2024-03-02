#include "main.h"

int opterr = 0;

struct args args;

int main(int argc, char **argv)
{
    int res = 0;

    while ((res = getopt(argc, argv, "h")) != -1) {
        switch (res) {
            case 'h':
                fprintf(stdout, "usage: %s [-h] <nsize> <ngroup>\n", argv[0]);
                return EXIT_SUCCESS;
            case '?':
                fprintf(stderr, "error: invalid option \'%c\'\n", optopt);
                fprintf(stderr, "try \'%s -h\' for more information\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (argv[optind] == NULL || argv[optind + 1] == NULL) {
        fprintf(stderr, "error: no arguments provided\n");
        fprintf(stderr, "try \'%s -h\' for more information\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[optind + 2] != NULL) {
        fprintf(stderr, "error: too many arguments\n");
        fprintf(stderr, "try \'%s -h\' for more information\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *start = NULL;
    char *end = NULL;

    start = argv[optind];
    args.nsize = strtol(start, &end, 0);

    if (args.nsize <= 0 || *start == '\0' || *end != '\0') {
        fprintf(stderr, "error: invalid input\n");
        fprintf(stderr, "try \'%s -h\' for more information\n", argv[0]);
        return EXIT_FAILURE;
    }

    start = argv[optind + 1];
    args.ngroup = strtol(start, &end, 0);

    if (args.ngroup <= 0 || *start == '\0' || *end != '\0') {
        fprintf(stderr, "error: invalid input\n");
        fprintf(stderr, "try \'%s -h\' for more information\n", argv[0]);
        return EXIT_FAILURE;
    }

    return process(argc, argv);
}
