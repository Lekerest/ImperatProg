#include <stdio.h>
#include <math.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }
    
    int a;
    if (fscanf(input, "%d", &a) != 1) 
    {
        fclose(input);
        fclose(output);
        return 1;
    }

    int b;
    if (fscanf(input, "%d", &b) != 1) 
    {
        fclose(input);
        fclose(output);
        return 1;
    }

    if (b != 0)
    {
        int floor_div = (int)floor((double)a / b);
        int ceil_div = (int)ceil((double)a / b);
        int trunc_div = (int)trunc((double)a / b);
        int remainder = a % b;
        if (remainder < 0) {
            remainder += b;
        }
        fprintf(output, "%d %d %d %d", floor_div, ceil_div, trunc_div, remainder);
    }
    else
    {
        fprintf(output, "0 0 0 %d", b);
    }

    fclose(input);
    fclose(output);
    
    return 0;
}