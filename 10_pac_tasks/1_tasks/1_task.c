#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // ---------- ЧТЕНИЕ ВХОДНЫХ ДАННЫХ ----------
    int N;
    int K;

    fscanf(input, "%d %d", &N, &K);

    // ---------- ЗАДАЧА ИОСИФА ----------
    int result = 0;

    for (int i = 1; i <= N; i++)
    {
        result = (result + K) % i;
    }

    result = result + 1;

    // ---------- ВЫВОД ОТВЕТА ----------
    fprintf(output, "%d\n", result);

    fclose(input);
    fclose(output);

    return 0;
}