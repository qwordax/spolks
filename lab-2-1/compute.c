#include "compute.h"

void compute(int *c, const int *a, const int *b, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            c[i * cols + j] = 0;

            for (int k = 0; k < cols; k++) {
                c[i * cols + j] += a[i * cols + k] * b[k * cols + j];
            }
        }
    }

    return;
}
