#include <stdio.h>
#include <stdlib.h>

int compare_long_long
(
    const void *a,
    const void *b
)
{
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;

    if (x < y)
    {
        return -1;
    }
    else if (x > y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int n;

    if (scanf("%d", &n) != 1)
    {
        return 0;
    }

    long long *array = (long long *)malloc(sizeof(long long) * n);

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &array[i]);
    }

    qsort
    (
        array,
        n,
        sizeof(long long),
        compare_long_long
    );

    long long result = 0;

    for (int i = 0; i < n; i++)
    {
        long long count = (long long)(n - 1 - i);
        long long contribution = array[i] * count;
        result += contribution;
    }

    printf("%lld\n", result);

    free(array);

    return 0;
}
