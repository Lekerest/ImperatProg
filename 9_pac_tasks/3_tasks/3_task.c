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

    int unique_count = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            unique_count++;
        }
        else
        {
            if (array[i] != array[i - 1])
            {
                unique_count++;
            }
        }
    }

    printf("%d\n", unique_count);

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            printf("%lld\n", array[i]);
        }
        else
        {
            if (array[i] != array[i - 1])
            {
                printf("%lld\n", array[i]);
            }
        }
    }

    free(array);

    return 0;
}
