#include <stdio.h>

#define MAX_ID 1000

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    int N;
    fscanf(input, "%d", &N);

    int fragments[MAX_ID + 1] = {0};
    int totalTime[MAX_ID + 1] = {0};
    int used[MAX_ID + 1] = {0};

    for (int i = 0; i < N; i++)
    {
        int id;
        int duration;

        if (fscanf(input, "%d %d", &id, &duration) != 2)
        {
            break;
        }

        fragments[id]++;
        totalTime[id] += duration;
        used[id] = 1;
    }

    // Определяем ширину столбцов для форматирования
    int w1 = 0;
    int w2 = 0;
    int w3 = 0;

    for (int id = 0; id <= MAX_ID; id++)
    {
        if (used[id] == 1)
        {
            int len1 = 0;
            int len2 = 0;
            int len3 = 0;

            int tmp;

            tmp = id;
            if (tmp == 0)
            {
                len1 = 1;
            }
            else
            {
                while (tmp > 0)
                {
                    len1++;
                    tmp /= 10;
                }
            }

            tmp = fragments[id];
            if (tmp == 0)
            {
                len2 = 1;
            }
            else
            {
                while (tmp > 0)
                {
                    len2++;
                    tmp /= 10;
                }
            }

            tmp = totalTime[id];
            if (tmp == 0)
            {
                len3 = 1;
            }
            else
            {
                while (tmp > 0)
                {
                    len3++;
                    tmp /= 10;
                }
            }

            if (len1 > w1)
            {
                w1 = len1;
            }

            if (len2 > w2)
            {
                w2 = len2;
            }

            if (len3 > w3)
            {
                w3 = len3;
            }
        }
    }

    for (int id = 0; id <= MAX_ID; id++)
    {
        if (used[id] == 1)
        {
            fprintf(output, "+");
            for (int i = 0; i < w1 + 2; i++)
            {
                fprintf(output, "-");
            }
            fprintf(output, "+");
            for (int i = 0; i < w2 + 2; i++)
            {
                fprintf(output, "-");
            }
            fprintf(output, "+");
            for (int i = 0; i < w3 + 2; i++)
            {
                fprintf(output, "-");
            }
            fprintf(output, "+\n");

            fprintf(output, "| %*d | %*d | %*d |\n",
                    w1, id, w2, fragments[id], w3, totalTime[id]);
        }
    }

    // Заключительная линия (если таблица не пустая)
    for (int id = MAX_ID; id >= 0; id--)
    {
        if (used[id] == 1)
        {
            fprintf(output, "+");
            for (int i = 0; i < w1 + 2; i++)
            {
                fprintf(output, "-");
            }
            fprintf(output, "+");
            for (int i = 0; i < w2 + 2; i++)
            {
                fprintf(output, "-");
            }
            fprintf(output, "+");
            for (int i = 0; i < w3 + 2; i++)
            {
                fprintf(output, "-");
            }
            fprintf(output, "+\n");
            break;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}