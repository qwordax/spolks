#include "fill.h"

void fill()
{
    FILE *fa = fopen("a.bin", "wb");
    FILE *fb = fopen("b.bin", "wb");

    int tmp;

    for (int i = 0; i < args.nsize; i++) {
        for (int j = 0; j < args.nsize; j++) {
            getrandom(&tmp, sizeof(tmp), 0);
            tmp = tmp % 10;

            fwrite(&tmp, sizeof(tmp), 1, fa);

            getrandom(&tmp, sizeof(tmp), 0);
            tmp = tmp % 10;

            fwrite(&tmp, sizeof(tmp), 1, fb);
        }
    }

    fclose(fa);
    fclose(fb);

    return;
}
