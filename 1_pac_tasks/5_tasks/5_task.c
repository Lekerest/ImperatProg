#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }
    
    int a, b;
    fscanf(input, "%d %d", &a, &b);
    
    int simple_div = a / b;
    
    int remainder = a % b;
    
    if (remainder < 0) {
        if (b > 0) {
            remainder += b;
        } else {
            remainder -= b;
        }
    }
    
    int floor_div = simple_div;
    int ceil_div = simple_div;

    if (remainder != 0) 
    {
        if ((a < 0 && b > 0) || (a > 0 && b < 0)) 
        {
            floor_div = simple_div - 1;
        } 
        else 
        {
            ceil_div = simple_div + 1;
        }
    }
    
    fprintf(output, "%d %d %d %d", floor_div, ceil_div, simple_div, remainder);
    
    fclose(input);
    fclose(output);
    return 0;
}