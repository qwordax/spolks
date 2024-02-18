#include "equal.h"

int equal(const int *a, const int *b, int n)
{
    int res = 1;

    for (int i = 0; i < n * n; i++) {
        res &= a[i] == b[i];
    }

    return res;
}
