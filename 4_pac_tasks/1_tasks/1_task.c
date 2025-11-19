#include <stdio.h>
#include <stdlib.h>

// qsort нужна такая сигнатура 2 указателя типа const void *
int compare(const void *a, const void *b)
{
    // каст - привести к нужному типу
    // (const int *)a — приведение void * к указателю на const int.
    // Это говорит: «надо интерпретировать a как адрес int».
    int int_a = *(const int *)a;
    // *(const int *)a — разыменование этого указателя, то есть получение значения int, находящегося по адресу a.
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int count_number_first, count_number_second, i, j;

    fscanf(input, "%d", &count_number_first);
    int arrA[count_number_first];
    for (i = 0; i < count_number_first; i++)
    {
        fscanf(input, "%d", &arrA[i]);
    }

    fscanf(input, "%d", &count_number_second);
    int arrB[count_number_second];
    for (i = 0; i < count_number_second; i++)
    {
        fscanf(input, "%d", &arrB[i]);
    }

    int res_arr[count_number_first];
    int count_matches = 0;

    for (i = 0; i < count_number_first; i++)
    {
        int found = 0;
        for (j = 0; j < count_number_second; j++)
        {
            if (arrA[i] == arrB[j])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            res_arr[count_matches++] = arrA[i];
        }
    }

    // сам массив, указатель на 1 элемент
    // количество элементов для сортировки
    // размер 1 элемента массива
    // функция сортировки
    qsort(res_arr, count_matches, sizeof(int), compare);

    int unique[count_matches];
    int unique_count = 0;
    for (i = 0; i < count_matches; i++)
    {
        if (i == 0 || res_arr[i] != res_arr[i - 1])
        {
            unique[unique_count++] = res_arr[i];
        }
    }

    fprintf(output, "%d\n", unique_count);
    for (i = 0; i < unique_count; i++)
    {
        fprintf(output, "%d ", unique[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}