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
    int res_arr[n];

    int result = 0;
    int step;

    int i = 0;
    int j = 0;

    for (i = 0; i < n; i++) 
    {
        fscanf(input, "%d", &arr[i]);
    }

    for (i = 0; i < n; i++) 
    {
        result = 0;
        for (j = i; j < n; j += (i + 1)) 
        {
            result += arr[j];
        }
        res_arr[i] = result;
    }

    for (i = 0; i < n; i++)
    {
        fprintf(output, "%d\n", res_arr[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}
