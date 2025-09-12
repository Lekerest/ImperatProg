#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }
    
    int n;
    fscanf(input, "%d", &n);
    
    int min = 10000, max = -10000;
    int index_min = 0, index_max = 0;
    int current;
    
    for (int i = 0; i < n; i++) {
        if (fscanf(input, "%d", &current) != 1) {
            fclose(input);
            fclose(output);
            return 1;
        }
        
        if (current < min) {
            min = current;
            index_min = i;
        }
        
        if (current > max) {
            max = current;
            index_max = i;
        }
    }
    
    fprintf(output, "%d %d %d %d", min, index_min + 1, max, index_max + 1);
    
    fclose(input);
    fclose(output);
    
    return 0;
}