#include <stdio.h>

int main() 
{
    // Открываем файлы для чтения и записи
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int n;
    fscanf(input, "%d", &n);    // Считываем количество элементов массива

    int arr[n];                 // Основной массив
    int res_arr[n];             // Массив для результатов t_k

    int result = 0;
    int i = 0;
    int j = 0;

    // Считываем массив из входного файла
    for (i = 0; i < n; i++) 
    {
        fscanf(input, "%d", &arr[i]);
    }

    // Для каждого k (индекс i соответствует k = i+1)
    // вычисляем сумму элементов с шагом k
    for (i = 0; i < n; i++) 
    {
        result = 0;   // Обнуляем сумму для текущего k

        // Идём по массиву с шагом (i+1), начиная со позиции i
        // j = i соответствует элементу a_(k), потому что индексы с 0
        for (j = i; j < n; j += (i + 1)) 
        {
            result += arr[j];   // Суммируем каждый k-й элемент
        }

        // Записываем сумму t_k в результирующий массив
        res_arr[i] = result;
    }

    // Выводим каждое t_k на новой строке
    for (i = 0; i < n; i++)
    {
        fprintf(output, "%d\n", res_arr[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}
