#include <stdio.h>
#include <stdlib.h>

void swap_int
(
    int *a,
    int *b
)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition_array
(
    int *array,
    int left,
    int right
)
{
    int pivot = array[(left + right) / 2];

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (array[i] < pivot)
        {
            i++;
        }

        while (array[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            swap_int(&array[i], &array[j]);
            i++;
            j--;
        }
    }

    return i;
}

void quick_sort
(
    int *array,
    int left,
    int right
)
{
    if (left >= right)
    {
        return;
    }

    int index = partition_array(array, left, right);

    quick_sort(array, left, index - 1);
    quick_sort(array, index, right);
}

int main()
{
    unsigned int N;

    if (fread(&N, sizeof(unsigned int), 1, stdin) != 1)
    {
        return 0;
    }

    int *array = (int *)malloc(sizeof(int) * N);

    if (N > 0)
    {
        fread(array, sizeof(int), N, stdin);
    }

    if (N > 0)
    {
        quick_sort(array, 0, (int)N - 1);
    }

    fwrite(array, sizeof(int), N, stdout);

    free(array);

    return 0;
}
