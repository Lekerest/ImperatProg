#include <stdio.h>

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

        double term = x;
        double result = x;
        int k = 1;

        while (term > 1e-15 || term < -1e-15)
        {
            /* 
            ---ЧИСЛИТЕЛЬ---
        term - член ряда (х)
        - потому что знаки чередуются
        берем старое значение term и добавлем к нему новое
        term * x^2 сдвиг так как каждый следующий член больше
            ------

            ---Знаменатель---
        Деление на нужный факториал
        Происходит с помощью рекурентной функции Tk/Tk-1
        Если подставить в ряд тейлора и сократить
        Получится формула (2k) * (2k+1)
            */

            term = - term * x * x / ((2*k) * (2*k + 1));
            result += term;
            k++;
        }

        fprintf(output, "%0.15lf\n", result);
    }

    fclose(input);
    fclose(output);

    return 0;
}