#include <stdio.h>
#include <stdlib.h>



typedef struct
{
    int key;
    char val[8];
    int orig_index;
} Record;



// ---------- ФУНКЦИЯ СРАВНЕНИЯ ДЛЯ QSORT ----------
// Сортируем сначала по key по возрастанию.
// Если ключи равны, сортируем по orig_index, чтобы сохранить исходный порядок
// (то есть делаем сортировку стабильной вручную).
static int compare_records(const void *a, const void *b)
{
    const Record *first = (const Record *)a;
    const Record *second = (const Record *)b;

    if (first->key != second->key)
    {
        return first->key - second->key;
    }

    return first->orig_index - second->orig_index;
}



int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");



    // ---------- ЧТЕНИЕ КОЛИЧЕСТВА ЗАПИСЕЙ ----------
    int record_count;
    fscanf(input, "%d", &record_count);



    // ---------- ВЫДЕЛЕНИЕ ПАМЯТИ ПОД МАССИВ ЗАПИСЕЙ ----------
    Record *records = (Record *)malloc(record_count * sizeof(Record));



    // ---------- ЧТЕНИЕ ЗАПИСЕЙ И СОХРАНЕНИЕ ИСХОДНОГО ПОРЯДКА ----------
    for (int i = 0; i < record_count; i++)
    {
        fscanf(input, "%d %7s", &records[i].key, records[i].val);

        records[i].orig_index = i;
    }



    // ---------- СОРТИРОВКА ----------
    qsort(records, record_count, sizeof(Record), compare_records);



    // ---------- ВЫВОД ОТСОРТИРОВАННЫХ ДАННЫХ ----------
    for (int i = 0; i < record_count; i++)
    {
        fprintf(output, "%d %s\n", records[i].key, records[i].val);
    }



    // ---------- ОСВОБОЖДЕНИЕ ПАМЯТИ И ЗАКРЫТИЕ ФАЙЛОВ ----------
    free(records);

    fclose(input);
    fclose(output);

    return 0;
}
