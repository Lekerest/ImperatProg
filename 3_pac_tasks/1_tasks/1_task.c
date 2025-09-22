#include <stdio.h>

int main() {
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

    for (int i = 0; i < n; i++) 
    {
        fscanf(input, "%d", &arr[i]);
    }
    
    int buf;
    int count = 0;
    int is;

    for (int i = 0; i < n; i++)
    {
        buf = arr[i];
        is = i;

        while(is < n)
        {
            if(arr[is] < buf)
            {
                count++;
            }
            is++;
        }
        res_arr[i] = count++;
        count = 0;
    }

    for (int i = 0; i < n; i++) 
    {
        fprintf(output, "%d ", res_arr[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}
