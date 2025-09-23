#include <stdio.h>

int main() 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    int arr[n];
    int unique[n];
    int res_arr[n];

    int i, j, found, temp;

    int count_unique = 0;

    for (i = 0; i < n; i++) 
    {
        fscanf(input, "%d", &arr[i]);

        found = 0;
        for (j = 0; j < count_unique; j++) 
        {
            if (arr[i] == unique[j]) 
            {
                res_arr[j]++;
                found = 1;
                break;
            }
        }

        if (found == 0) 
        {
            unique[count_unique] = arr[i];
            res_arr[count_unique] = 1;
            count_unique++;
        }
    }

    for (i = 0; i < count_unique - 1; i++)
    {
        for (j = 0; j < count_unique - i - 1; j++)
        {
            if (unique[j] > unique[j + 1])
            {
                temp = unique[j];
                unique[j] = unique[j + 1];
                unique[j + 1] = temp;

                temp = res_arr[j];
                res_arr[j] = res_arr[j + 1];
                res_arr[j + 1] = temp;
            }
        }
    }
    
    for (i = 0; i < count_unique; i++)
    {
        fprintf(output, "%d: %d\n", unique[i], res_arr[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}