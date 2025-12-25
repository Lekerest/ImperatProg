#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- ОДНА ЗАПИСЬ: ХРАНИМ ТОЛЬКО СТРОКУ ----------
struct Record
{
    char value[8];
};

// ---------- ДИНАМИЧЕСКИЙ МАССИВ ЗАПИСЕЙ ----------
struct DynamicArray
{
    struct Record *data;
    int size;
    int capacity;
};

// ---------- ИНИЦИАЛИЗАЦИЯ ПУСТОГО ДИНАМИЧЕСКОГО МАССИВА ----------
static void init_array
(
    struct DynamicArray *arr
)
{
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

// ---------- ДОБАВЛЕНИЕ ЭЛЕМЕНТА В КОНЕЦ (push_back) ----------
static void push_back
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

        struct Record *new_data =
            (struct Record *)realloc(arr->data, sizeof(struct Record) * new_capacity);

        if (new_data == NULL)
        {
            exit(0);
        }

        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    arr->data[arr->size] = rec;
    arr->size = arr->size + 1;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // ---------- ЧТЕНИЕ КОЛИЧЕСТВА ЗАПИСЕЙ ----------
    int N;
    fscanf(input, "%d", &N);

    // ---------- СОЗДАЁМ 10^6 + 1 КОРЗИН ----------
    const int MAX_KEY = 1000000;

    struct DynamicArray *buckets =
        (struct DynamicArray *)malloc(sizeof(struct DynamicArray) * (MAX_KEY + 1));

    // ---------- ИНИЦИАЛИЗИРУЕМ КАЖДУЮ КОРЗИНУ ----------
    for (int i = 0; i <= MAX_KEY; i++)
    {
        init_array(&buckets[i]);
    }

    // ---------- ЧИТАЕМ ЗАПИСИ И РАСКЛАДЫВАЕМ ПО КОРЗИНАМ ----------
    for (int i = 0; i < N; i++)
    {
        int key;
        char input_value[8];

        fscanf(input, "%d %7s", &key, input_value);

        struct Record rec;
        strcpy(rec.value, input_value);

        push_back(&buckets[key], rec);
    }

    // ---------- ВЫВОДИМ В ПОРЯДКЕ ВОЗРАСТАНИЯ КЛЮЧА ----------
    for (int key = 0; key <= MAX_KEY; key++)
    {
        struct DynamicArray *arr = &buckets[key];

        for (int i = 0; i < arr->size; i++)
        {
            fprintf(output, "%d %s\n", key, arr->data[i].value);
        }
    }

    // ---------- ОСВОБОЖДАЕМ ПАМЯТЬ ----------
    for (int i = 0; i <= MAX_KEY; i++)
    {
        free(buckets[i].data);
    }

    free(buckets);

    fclose(input);
    fclose(output);

    return 0;
}