#include <stdio.h>
#include <stdlib.h>

// ---------- ФУНКЦИЯ СРАВНЕНИЯ ДЛЯ QSORT ----------
static int compare_int
(
    const void *a,
    const void *b
)
{
    int first_value = *(const int *)a;
    int second_value = *(const int *)b;

    if (first_value < second_value)
    {
        return -1;
    }
    else if (first_value > second_value)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // ---------- ЧТЕНИЕ РАЗМЕРА МАССИВА ----------
    int count_numbers;
    fscanf(input, "%d", &count_numbers);

    // ---------- ВЫДЕЛЕНИЕ ПАМЯТИ ПОД МАССИВ ----------
    int *array = (int *)malloc(sizeof(int) * count_numbers);

    // ---------- ЧТЕНИЕ ЭЛЕМЕНТОВ МАССИВА ----------
    for (int i = 0; i < count_numbers; i++)
    {
        fscanf(input, "%d", &array[i]);
    }

    // ---------- СОРТИРОВКА МАССИВА ----------
    qsort
    (
        array,
        count_numbers,
        sizeof(int),
        compare_int
    );

    // ---------- ПОДСЧЁТ КОЛИЧЕСТВА УНИКАЛЬНЫХ ЗНАЧЕНИЙ ----------
    int unique_count = 0;

    for (int i = 0; i < count_numbers; i++)
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

    // ---------- ВЫВОД КОЛИЧЕСТВА УНИКАЛЬНЫХ ----------
    fprintf(output, "%d\n", unique_count);

    // ---------- ВЫВОД УНИКАЛЬНЫХ ЗНАЧЕНИЙ ----------
    for (int i = 0; i < count_numbers; i++)
    {
        if (i == 0)
        {
            fprintf(output, "%d\n", array[i]);
        }
        else
        {
            if (array[i] != array[i - 1])
            {
                fprintf(output, "%d\n", array[i]);
            }
        }
    }

    // ---------- ОСВОБОЖДЕНИЕ ПАМЯТИ И ЗАКРЫТИЕ ФАЙЛОВ ----------
    free(array);

    fclose(input);
    fclose(output);

    return 0;
}