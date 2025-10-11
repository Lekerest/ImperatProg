#include <stdio.h>

double exp_custom(double x)
{
    int invert = 0;

    if (x < 0)
    {
        x = -x;
        invert = 1;
    }

    double term = 1.0;
    double sum = 1.0;
    int n = 1;

    // добавляем члены ряда, пока они значимы
    while (term > 1e-15 || term < -1e-15)
    {
        term *= x / n;
        sum += term;
        n++;
    }

    if (invert)
        return 1.0 / sum;
    else
        return sum;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        double x;
        fscanf(input, "%lf", &x);

        double result = exp_custom(x);

        fprintf(output, "%0.15g\n", result);
    }

    fclose(input);
    fclose(output);

    return 0;
}