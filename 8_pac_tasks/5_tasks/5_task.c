#include <stdio.h>
#include <stdlib.h>

// Функция бинарного поиска: возвращает индекс первого элемента, не меньшего чем value
int lower_bound(int *array, int size, int value)
{
    int left = 0;
    int right = size;
    int mid;

    // Классический бинарный поиск по полуинтервалу [left, right)
    while (left < right)
    {
        mid = left + (right - left) / 2;

        if (array[mid] < value)
        {
            left = mid + 1; // смещаем в правую половину
        }
        else
        {
            right = mid; // смещаем в левую половину
        }
    }

    return left; // возвращаем позицию первого элемента >= value
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int arraySize;       // количество элементов массива
    int queryCount;      // количество запросов
    int queryValue;      // число Yj из запроса
    int resultIndex;     // индекс ближайшего элемента
    int distance;        // минимальная разница между элементом и Yj
    int index;           // индекс для циклов
    int position;        // индекс позиции найденного элемента
    int leftIndex;       // индекс левого соседа
    int rightIndex;      // индекс правого соседа
    int leftDiff;        // разница с левым элементом
    int rightDiff;       // разница с правым элементом

    // Чтение размера массива
    fscanf(input, "%d", &arraySize);

    // Выделяем память под массив
    int *array = (int *)malloc(arraySize * sizeof(int));

    // Считываем элементы массива
    for (index = 0; index < arraySize; index++)
    {
        fscanf(input, "%d", &array[index]);
    }

    // Считываем количество запросов
    fscanf(input, "%d", &queryCount);

    // Обработка каждого запроса
    for (index = 0; index < queryCount; index++)
    {
        fscanf(input, "%d", &queryValue); // читаем текущее значение Yj

        // Ищем позицию элемента, не меньшего чем Yj
        position = lower_bound(array, arraySize, queryValue);

        // Граничные случаи — если значение за пределами диапазона массива
        if (position == 0)
        {
            resultIndex = 0; // самое маленькое значение
        }
        else if (position == arraySize)
        {
            resultIndex = arraySize - 1; // самое большое значение
        }
        else
        {
            // Кандидаты — соседние элементы
            leftIndex = position - 1;
            rightIndex = position;

            // Считаем абсолютные разницы
            leftDiff = queryValue - array[leftIndex];
            if (leftDiff < 0)
            {
                leftDiff = -leftDiff;
            }

            rightDiff = array[rightIndex] - queryValue;
            if (rightDiff < 0)
            {
                rightDiff = -rightDiff;
            }

            // Если расстояние слева меньше — берём левый, иначе правый
            // При равенстве выбирается правый (по условию задачи)
            if (leftDiff < rightDiff)
            {
                resultIndex = leftIndex;
            }
            else
            {
                resultIndex = rightIndex;
            }
        }

        // Вычисляем модуль расстояния между найденным элементом и Yj
        distance = array[resultIndex] - queryValue;
        if (distance < 0)
        {
            distance = -distance;
        }

        // Вывод результата: индекс и расстояние
        fprintf(output, "%d %d\n", resultIndex, distance);
    }

    // Очистка памяти и закрытие файлов
    free(array);
    fclose(input);
    fclose(output);

    return 0;
}