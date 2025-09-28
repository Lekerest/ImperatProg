#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    int N, M, i;
    fscanf(input, "%d %d", &N, &M);

    int value[N + 1]; // value[x] = y, если x -> y
    int used[N + 1];  // для проверки инъекции
    int y_count[N + 1]; // для проверки сюръекции

    for (i = 1; i <= N; i++)
    {
        value[i] = 0;   // 0 = ещё не задано
        used[i] = 0;
        y_count[i] = 0;
    }

    int x, y;
    int is_function = 1;

    for (i = 0; i < M; i++)
    {
        fscanf(input, "%d %d", &x, &y);

        if (value[x] == 0)
        {
            value[x] = y;
        }
        else
        {
            if (value[x] != y)
            {
                is_function = 0;
            }
        }

        y_count[y]++;
    }

    if (!is_function)
    {
        fprintf(output, "0\n");
        fclose(input);
        fclose(output);
        return 0;
    }

    int result[5];
    for (i = 0; i < 5; i++)
    {
        result[i] = 0;
    }

    // 1. Функция
    result[0] = 1;

    // 2. Всюду определённая функция
    int everywhere_defined = 1;
    for (i = 1; i <= N; i++)
    {
        if (value[i] == 0)
        {
            everywhere_defined = 0;
            break;
        }
    }
    if (everywhere_defined)
    {
        result[1] = 2;
    }

    // 3. Инъекция
    int injective = 1;
    for (i = 1; i <= N; i++)
    {
        if (y_count[i] > 1)
        {
            injective = 0;
            break;
        }
    }
    if (injective)
    {
        result[2] = 3;
    }

    // 4. Сюръекция
    int surjective = 1;
    for (i = 1; i <= N; i++)
    {
        if (y_count[i] == 0)
        {
            surjective = 0;
            break;
        }
    }
    if (surjective)
    {
        result[3] = 4;
    }

    // 5. Биекция
    if (injective && surjective)
    {
        result[4] = 5;
    }

    int first = 1;
    for (i = 0; i < 5; i++)
    {
        if (result[i] != 0)
        {
            if (!first)
            {
                fprintf(output, " ");
            }
            fprintf(output, "%d", result[i]);
            first = 0;
        }
    }
    fprintf(output, "\n");

    fclose(input);
    fclose(output);
    return 0;
}