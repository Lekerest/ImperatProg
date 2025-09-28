#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    int N, M;
    if (fscanf(input, "%d %d", &N, &M) != 2)
    {
        fclose(input);
        fclose(output);
        return 1;
    }

    // массив значений функции (f[x] = y, если определено; иначе 0)
    int f[N + 1];
    for (int i = 1; i <= N; i++)
    {
        f[i] = 0;
    }

    int values[M];      // список значений (y)
    int values_count = 0;
    int is_function = 1;

    for (int i = 0; i < M; i++)
    {
        int x, y;
        fscanf(input, "%d %d", &x, &y);

        if (f[x] == 0)
        {
            f[x] = y;
            values[values_count++] = y;
        }
        else
        {
            if (f[x] != y)
            {
                is_function = 0; // неоднозначность
            }
        }
    }

    if (!is_function)
    {
        fprintf(output, 0);
        fclose(input);
        fclose(output);
        return 0;
    }

    int result[6];
    int rcount = 0;

    // 1) функция
    result[rcount++] = 1;

    // 2) всюду определённая
    int everywhere_defined = 1;
    for (int i = 1; i <= N; i++)
    {
        if (f[i] == 0)
        {
            everywhere_defined = 0;
            break;
        }
    }
    if (everywhere_defined)
    {
        result[rcount++] = 2;
    }

    // 3) инъективная
    int injective = 1;
    for (int i = 0; i < values_count && injective; i++)
    {
        for (int j = i + 1; j < values_count; j++)
        {
            if (values[i] == values[j])
            {
                injective = 0;
                break;
            }
        }
    }
    if (injective)
    {
        result[rcount++] = 3;
    }

    // 4) сюръективная
    int surjective = 1;
    for (int u = 1; u <= N; u++)
    {
        int found = 0;
        for (int i = 0; i < values_count; i++)
        {
            if (values[i] == u)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            surjective = 0;
            break;
        }
    }
    if (surjective)
    {
        result[rcount++] = 4;
    }

    // 5) биективная
    if (injective && surjective)
    {
        result[rcount++] = 5;
    }

    // вывод результата
    for (int i = 0; i < rcount; i++)
    {
        if (i > 0)
        {
            fprintf(output, " ");
        }
        fprintf(output, "%d", result[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}