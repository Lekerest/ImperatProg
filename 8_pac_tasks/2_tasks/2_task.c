#include <stdio.h>
#include <stdlib.h>

// Функция бинарного поиска последнего вхождения значения
int binary_search_last(int *array, int size, int value)
{
    int left = 0;
    int right = size - 1;
    int result = -1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (array[mid] == value)
        {
            result = mid;      // нашли совпадение, запоминаем
            left = mid + 1;    // продолжаем искать правее
        }
        else if (array[mid] < value)
        {
            left = mid + 1;    // сдвигаем границу влево
        }
        else
        {
            right = mid - 1;   // сдвигаем границу вправо
        }
    }

    return result; // возвращаем индекс или -1
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int arraySize; // количество элементов массива
    fscanf(input, "%d", &arraySize);

    int *array = (int *)malloc(arraySize * sizeof(int));

    int index;
    for (index = 0; index < arraySize; index++)
    {
        fscanf(input, "%d", &array[index]); // читаем элементы массива
    }

    int queryCount; // количество запросов
    fscanf(input, "%d", &queryCount);

    int queryValue;    // Xj
    int searchValue;   // Yj = Xj + Rj-1
    int lastResult = 0; // предыдущий результат (Rj-1)
    int result;         // текущий ответ

    for (index = 0; index < queryCount; index++)
    {
        fscanf(input, "%d", &queryValue); // читаем Xj

        if (index == 0)
        {
            searchValue = queryValue; // первый запрос: Y0 = X0
        }
        else
        {
            searchValue = queryValue + lastResult; // Yj = Xj + Rj-1
        }

        result = binary_search_last(array, arraySize, searchValue); // ищем значение

        lastResult = result; // сохраняем результат для следующего запроса

        fprintf(output, "%d\n", result); // выводим ответ
    }

    free(array);
    fclose(input);
    fclose(output);

    return 0;
}