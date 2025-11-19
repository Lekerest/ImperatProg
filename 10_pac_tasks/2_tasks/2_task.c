#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record
{
    char value[8];
};

struct DynamicArray
{
    struct Record *data;
    int size;
    int capacity;
};

void init_array
(
    struct DynamicArray *arr
)
{
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void push_back
(
    struct DynamicArray *arr,
    struct Record rec
)
{
    if (arr->size == arr->capacity)
    {
        int new_capacity;

        if (arr->capacity == 0)
        {
            new_capacity = 2;
        }
        else
        {
            new_capacity = arr->capacity * 2;
        }

        struct Record *new_data = (struct Record *)malloc(sizeof(struct Record) * new_capacity);

        for (int i = 0; i < arr->size; i++)
        {
            new_data[i] = arr->data[i];
        }

        free(arr->data);

        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    arr->data[arr->size] = rec;
    arr->size = arr->size + 1;
}

int main()
{
    int N;

    if (scanf("%d", &N) != 1)
    {
        return 0;
    }

    int MAX_KEY = 1000000;

    struct DynamicArray *buckets =
        (struct DynamicArray *)malloc(sizeof(struct DynamicArray) * (MAX_KEY + 1));

    for (int i = 0; i <= MAX_KEY; i++)
    {
        init_array(&buckets[i]);
    }

    for (int i = 0; i < N; i++)
    {
        int key;
        char value[8];

        scanf("%d %7s", &key, value);

        struct Record rec;
        strcpy(rec.value, value);

        push_back(&buckets[key], rec);
    }

    for (int key = 0; key <= MAX_KEY; key++)
    {
        struct DynamicArray *arr = &buckets[key];

        for (int i = 0; i < arr->size; i++)
        {
            printf("%d %s\n", key, arr->data[i].value);
        }
    }

    for (int i = 0; i <= MAX_KEY; i++)
    {
        free(buckets[i].data);
    }

    free(buckets);

    return 0;
}
