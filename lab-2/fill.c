#include "fill.h"

void fill()
{
    FILE *fa = fopen("a.bin", "wb");
    FILE *fb = fopen("b.bin", "wb");

    int t;

    for (int i = 0; i < args.nsize; i++) {
        for (int j = 0; j < args.nsize; j++) {
            t = rand() % 10 - 5;
            fwrite(&t, sizeof(int), 1, fa);

            t = rand() % 10 - 5;
            fwrite(&t, sizeof(int), 1, fb);
        }
    }

    fclose(fa);
    fclose(fb);

    return;
}
