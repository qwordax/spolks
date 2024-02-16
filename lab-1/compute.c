#include "compute.h"

void compute(int *c, const int *a, const int *b, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int t = 0;

            for (int k = 0; k < cols; k++) {
                t += a[i * cols + k] * b[j * cols + k];
            }

            c[i * cols + j] = t;
        }
    }

    return;
}
