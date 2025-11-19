#include <stdio.h>

int main() {
    // Открываем входной и выходной файлы
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int n;
    fscanf(input, "%d", &n);   // Считываем количество элементов
    int arr[n];                // Основной массив
    int res_arr[n];            // Массив для результата

    // Чтение массива из входного файла
    for (int i = 0; i < n; i++) 
    {
        fscanf(input, "%d", &arr[i]);
    }
    
    int buf;
    int count = 0;
    int is;

    // Для каждого элемента массива считаем,
    // сколько элементов справа меньше текущего
    for (int i = 0; i < n; i++)
    {
        buf = arr[i];  // Текущий элемент
        is = i;        // Индекс для прохода вправо

        // Проходим все элементы справа (i < n)
        while(is < n)
        {
            // Если найден элемент меньше текущего — увеличиваем счётчик
            if(arr[is] < buf)
            {
                count++;
            }
            is++;
        }

        // Записываем количество меньших элементов
        res_arr[i] = count;
        count = 0; // Обнуляем счётчик перед следующим i
    }

    // Вывод результата в файл
    for (int i = 0; i < n; i++) 
    {
        fprintf(output, "%d ", res_arr[i]);
    }

    // Закрываем файлы
    fclose(input);
    fclose(output);
    return 0;
}