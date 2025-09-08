#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &n);
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int num;
        fscanf(input, "%d", &num);
        
        if (num % 2 != 0) {
            sum += num;
        }
    }
    
    fprintf(output, "%d", sum);
    
    fclose(input);
    fclose(output);
    return 0;
}