#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- ОДНА ЗАПИСЬ: ХРАНИМ ТОЛЬКО СТРОКУ ----------
// Ключ хранить не нужно, потому что ключ = индекс корзины.
struct Record
{
    char value[8];
};

// ---------- ДИНАМИЧЕСКИЙ МАССИВ ЗАПИСЕЙ ----------
// data     — указатель на массив Record в куче
// size     — сколько элементов реально записано
// capacity — сколько элементов помещается без расширения
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
// Если места нет, увеличиваем capacity (в 2 раза) и расширяем память через realloc.
static void push_back
(
    struct DynamicArray *arr,
    struct Record rec
)
{
    // ---------- ЕСЛИ МЕСТА НЕТ, НАДО РАСШИРИТЬ МАССИВ ----------
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

        // ---------- REALLOC: УВЕЛИЧИВАЕМ (ИЛИ СОЗДАЁМ) БЛОК ПАМЯТИ ----------
        // realloc может:
        // 1) расширить блок на месте
        // 2) выделить новый блок, скопировать старые данные и освободить старый
        // 3) вернуть NULL, если памяти не хватило (старый блок при этом остаётся)
        struct Record *new_data =
            (struct Record *)realloc(arr->data, sizeof(struct Record) * new_capacity);

        if (new_data == NULL)
        {
            // В рамках учебных задач обычно достаточно просто завершиться,
            // потому что продолжать работу без памяти невозможно.
            exit(0);
        }

        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    // ---------- ДОБАВЛЯЕМ ЭЛЕМЕНТ В КОНЕЦ ----------
    arr->data[arr->size] = rec;
    arr->size = arr->size + 1;
}



int main(void)
{
    // ---------- ЧТЕНИЕ КОЛИЧЕСТВА ЗАПИСЕЙ ----------
    int N;

    if (scanf("%d", &N) != 1)
    {
        return 0;
    }

    // ---------- СОЗДАЁМ 10^6 + 1 КОРЗИН (ПО ОДНОЙ НА КАЖДЫЙ КЛЮЧ) ----------
    // По условию ключи в диапазоне 0..10^6 включительно. :contentReference[oaicite:1]{index=1}
    const int MAX_KEY = 1000000;

    struct DynamicArray *buckets = (struct DynamicArray *)malloc(sizeof(struct DynamicArray) * (MAX_KEY + 1));


    // ---------- ИНИЦИАЛИЗИРУЕМ КАЖДУЮ КОРЗИНУ КАК ПУСТОЙ ДИНАМИЧЕСКИЙ МАССИВ ----------
    for (int i = 0; i <= MAX_KEY; i++)
    {
        init_array(&buckets[i]);
    }

    // ---------- ЧИТАЕМ ЗАПИСИ И РАСКЛАДЫВАЕМ ПО КОРЗИНАМ ----------
    // Для ключа key добавляем запись в buckets[key].
    // Порядок внутри одной корзины сохраняется, потому что мы делаем push_back в конец. :contentReference[oaicite:2]{index=2}
    for (int i = 0; i < N; i++)
    {
        int key;
        char input_value[8];

        scanf("%d %7s", &key, input_value);

        struct Record rec;
        strcpy(rec.value, input_value);

        push_back(&buckets[key], rec);
    }

    // ---------- ВЫВОДИМ В ПОРЯДКЕ ВОЗРАСТАНИЯ КЛЮЧА ----------
    // Идём key от 0 до MAX_KEY.
    // Для каждого ключа печатаем записи в том порядке, как они были добавлены (стабильно). :contentReference[oaicite:3]{index=3}
    for (int key = 0; key <= MAX_KEY; key++)
    {
        struct DynamicArray *arr = &buckets[key];

        for (int i = 0; i < arr->size; i++)
        {
            printf("%d %s\n", key, arr->data[i].value);
        }
    }

    // ---------- ОСВОБОЖДАЕМ ПАМЯТЬ ----------
    for (int i = 0; i <= MAX_KEY; i++)
    {
        free(buckets[i].data);
    }

    free(buckets);

    return 0;
}
