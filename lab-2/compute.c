#include "compute.h"

void compute(int *c, const int *a, const int *b, int from, int to, int n)
{
    for (int i = from; i < to; i++) {
        for (int j = 0; j < n; j++) {
            c[i * n + j] = 0;

            for (int k = 0; k < n; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }

    return;
}
