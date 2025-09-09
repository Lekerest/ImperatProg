#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }
    
    int arr[3];
    
    for (int i = 0; i < 3; i++) 
    {
        if (fscanf(input, "%d", &arr[i]) != 1)
        {
            fclose(input);
            fclose(output);
            return 1;
        } 
        else if (arr[i] <= 0)
        {
            int index = i + 1;
            fprintf(output, "%d ", -index);
            return 0;

        }

    }
    
    int a = arr[0];
    int b = arr[1]; 
    int c = arr[2];

    int s = 2 * (a*b + b*c + a*c);
    fprintf(output, "%d ", s);
    
    fclose(input);
    fclose(output);
    
    return 0;
}