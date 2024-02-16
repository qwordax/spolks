#include "equal.h"

int equal(const int *a, const int *b, int rows, int cols)
{
    int res = 1;

    for (int i = 0; i < rows * cols; i++) {
        res &= a[i] == b[i];
    }

    return res;
}
