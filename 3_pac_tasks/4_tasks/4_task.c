#include <stdio.h>

int main() 
{
    // Открываем файлы для чтения и записи
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    int arr[n], i, pos;
    for (i = 0; i < n; i++)
    {
        fscanf(input, "%d", &arr[i]);
    }

    int max_sum = arr[0];
    int cur_sum = arr[0];
    int start = 0, end = 0, temp_start = 0;

    for (pos = 1; pos < n; pos++)
    {
        // Решаем: начать новый подотрезок или продолжить текущий
        if (cur_sum + arr[pos] < arr[pos]) 
        {
            // Начинаем новый подотрезок с текущего элемента
            cur_sum = arr[pos];
            temp_start = pos;
        } 
        else 
        {
            // Продолжаем текущий подотрезок
            cur_sum += arr[pos];
        }

        // Проверяем, лучше ли этот подотрезок найденного ранее
        if (cur_sum > max_sum) 
        {
            // Новый максимум
            max_sum = cur_sum;
            start = temp_start;
            end = pos;
        } 
        else if (cur_sum == max_sum) 
        {
            // Если суммы равны — применяем правила выбора:
            if (temp_start < start) 
            {
                // выбираем подотрезок с меньшим L
                start = temp_start;
                end = pos;
            } 
            else if (temp_start == start && pos < end) 
            {
                // если L одинаковый, берём с меньшим R
                start = temp_start;
                end = pos;
            }
        }
    }

    fprintf(output, "%d %d %d\n", start, end, max_sum);

    fclose(input);
    fclose(output);
    return 0;
}