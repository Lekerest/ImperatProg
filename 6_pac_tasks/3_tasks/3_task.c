#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int N;
    fscanf(input, "%d", &N);

    for (int i = 0; i < N; i++)
    {
        unsigned long long P;
        unsigned long long Q;
        unsigned long long M;

        fscanf(input, "%llu/%llu xor %llx", &P, &Q, &M);
        // В x записывается 64-битное число в формате 
        // IEEE-754 (1 бит знака, 11 бит экспоненты, 52 бита мантиссы).
        double x = (double)P / (double)Q;
        // bits - 8b x - 8b
        // берем адресс x
        // явно приводим тип указателя из дабл в лонг лонг чтобы потом разыменовывать
        // разыменовываем и записываем результат в bits
        unsigned long long bits = *(unsigned long long *)&x;
        
        // Операция XOR поразрядно инвертирует в bits те биты, где в M стоит 1.
        bits = bits ^ M;

        double y = *(double *)&bits;

        fprintf(output, "%.15g\n", y);
    }

    fclose(input);
    fclose(output);

    return 0;
}