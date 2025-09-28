#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    int count_number_first, count_number_second, i, j, temp;

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

    for (i = 0; i < count_matches - 1; i++)
    {
        for (j = 0; j < count_matches - i - 1; j++)
        {
            if (res_arr[j] > res_arr[j + 1])
            {
                temp = res_arr[j];
                res_arr[j] = res_arr[j + 1];
                res_arr[j + 1] = temp;
            }
        }
    }

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