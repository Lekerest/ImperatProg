#include <stdio.h>
#include <stdlib.h>



// ---------- ФУНКЦИЯ СРАВНЕНИЯ ДЛЯ QSORT ----------
// Сравнивает два int-значения по возрастанию.
// Возвращает:
//   -1, если первый меньше второго
//    1, если первый больше второго
//    0, если равны
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
    // ---------- ЧТЕНИЕ РАЗМЕРА МАССИВА ----------
    int count_numbers;

    if (scanf("%d", &count_numbers) != 1)
    {
        return 0;
    }

    // ---------- ВЫДЕЛЕНИЕ ПАМЯТИ ПОД МАССИВ ----------
    int *array = (int *)malloc(sizeof(int) * count_numbers);

    // ---------- ЧТЕНИЕ ЭЛЕМЕНТОВ МАССИВА ----------
    for (int i = 0; i < count_numbers; i++)
    {
        scanf("%d", &array[i]);
    }

    // ---------- СОРТИРОВКА МАССИВА ----------
    // После сортировки одинаковые значения окажутся рядом,
    // и дубликаты можно будет легко убрать одним проходом.
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
            // Первый элемент всегда уникальный, потому что сравнивать не с чем
            unique_count++;
        }
        else
        {
            // Если текущий элемент отличается от предыдущего,
            // значит началось новое уникальное значение
            if (array[i] != array[i - 1])
            {
                unique_count++;
            }
        }
    }

    // ---------- ВЫВОД КОЛИЧЕСТВА УНИКАЛЬНЫХ ----------
    printf("%d\n", unique_count);

    // ---------- ВЫВОД УНИКАЛЬНЫХ ЗНАЧЕНИЙ ----------
    // Печатаем первый элемент, а затем печатаем только те,
    // которые отличаются от предыдущего.
    for (int i = 0; i < count_numbers; i++)
    {
        if (i == 0)
        {
            printf("%d\n", array[i]);
        }
        else
        {
            if (array[i] != array[i - 1])
            {
                printf("%d\n", array[i]);
            }
        }
    }

    // ---------- ОСВОБОЖДЕНИЕ ПАМЯТИ ----------
    free(array);

    return 0;
}
