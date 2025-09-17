#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    int min_range;
    fscanf(input, "%d", &min_range);

    int max_range;
    fscanf(input, "%d", &max_range);

    fclose(input);
    fclose(output);
    
    return 0;
}