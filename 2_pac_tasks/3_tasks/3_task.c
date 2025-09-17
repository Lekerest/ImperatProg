#include <stdio.h>

int main() 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    int count_number;
    if (fscanf(input, "%d", &count_number) != 1) {
        fclose(input);
        fclose(output);
        return 1;
    }

    int count_zero = 0;
    int count_positive = 0;
    int count_negative = 0;

    for (int i = 0; i < count_number; i++)
    {
        int a;
        if (fscanf(input, "%d", &a) != 1) {
            fclose(input);
            fclose(output);
            return 1;
        }

        if (a > 0) count_positive++;
        else if (a < 0) count_negative++;
        else count_zero++;
    }

    double positive = (double)count_positive / count_number;
    double negative = (double)count_negative / count_number;
    double zero = (double)count_zero / count_number;

    fprintf(output, "%0.5lf %0.5lf %0.5lf\n", negative, zero, positive);

    fclose(input);
    fclose(output);
    return 0;
}
