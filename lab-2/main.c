#include "main.h"

int opterr = 0;

struct flags flags;

int main(int argc, char **argv)
{
    flags.c = 0;
    flags.p = 0;

    int res = 0;

    while ((res = getopt(argc, argv, "chp")) != -1) {
        switch (res) {
            case 'c':
                flags.c = 1;
                break;
            case 'h':
                fprintf(stdout, "usage: %s [-chp] <nsize> <ngroup>\n", argv[0]);
                return EXIT_SUCCESS;
            case 'p':
                flags.p = 1;
                break;
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

    return execute(argc, argv);
}
