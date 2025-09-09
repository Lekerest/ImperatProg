#include <stdio.h>
#include <math.h>

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
    
    for (int i = 0; i < n; i++) 
    {
        if (fscanf(input, "%d", &arr[i]) != 1)
        {
            fclose(input);
            fclose(output);
            return 1;
        } 
    }

    int min = 10000, max = -10000;
    int index_min = 0, index_max = 0;

    for (int i = 0; i < n; i++) 
    {
        if (min > arr[i])
        {
            min = arr[i];
            index_min = i;
        }
        
        if (max < arr[i])
        {
            max = arr[i];
            index_max = i;
        }
    }

    fprintf(output, "%d %d %d %d", min, index_min + 1, max, index_max + 1);

    fclose(input);
    fclose(output);
    
    return 0;
}