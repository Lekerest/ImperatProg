#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record
{
    long long key;
    char value[8];
    int original_index;
};

void merge
(
    struct Record *array,
    struct Record *buffer,
    int left,
    int middle,
    int right
)
{
    int i = left;
    int j = middle;
    int k = left;

    while (i < middle && j < right)
    {
        if (array[i].key < array[j].key)
        {
            buffer[k] = array[i];
            i++;
            k++;
        }
        else if (array[i].key > array[j].key)
        {
            buffer[k] = array[j];
            j++;
            k++;
        }
        else
        {
            if (array[i].original_index < array[j].original_index)
            {
                buffer[k] = array[i];
                i++;
                k++;
            }
            else
            {
                buffer[k] = array[j];
                j++;
                k++;
            }
        }
    }

    while (i < middle)
    {
        buffer[k] = array[i];
        i++;
        k++;
    }

    while (j < right)
    {
        buffer[k] = array[j];
        j++;
        k++;
    }

    for (int t = left; t < right; t++)
    {
        array[t] = buffer[t];
    }
}

void merge_sort
(
    struct Record *array,
    struct Record *buffer,
    int left,
    int right
)
{
    if (right - left <= 1)
    {
        return;
    }

    int middle = (left + right) / 2;

    merge_sort(array, buffer, left, middle);
    merge_sort(array, buffer, middle, right);

    merge(array, buffer, left, middle, right);
}

int main()
{
    int N;

    if (scanf("%d", &N) != 1)
    {
        return 0;
    }

    struct Record *array = (struct Record *)malloc(sizeof(struct Record) * N);
    struct Record *buffer = (struct Record *)malloc(sizeof(struct Record) * N);

    for (int i = 0; i < N; i++)
    {
        scanf("%lld %7s", &array[i].key, array[i].value);
        array[i].original_index = i;
    }

    merge_sort(array, buffer, 0, N);

    for (int i = 0; i < N; i++)
    {
        printf("%lld %s\n", array[i].key, array[i].value);
    }

    free(array);
    free(buffer);

    return 0;
}
