#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 251

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    char line[1000];
    fgets(line, sizeof(line), input);

    int N;
    sscanf(line, "%d", &N);

    // Чтение ключа
    int rot[4][MAXN][MAXN];
    for (int i = 0; i < N; i++)
    {
        fgets(line, sizeof(line), input);
        char *tok = strtok(line, " \n");
        for (int j = 0; j < N; j++)
        {
            sscanf(tok, "%d", &rot[0][i][j]);
            tok = strtok(NULL, " \n");
        }
    }

    // Чтение текста
    char text[MAXN][MAXN + 1];
    for (int i = 0; i < N; i++)
    {
        fgets(line, sizeof(line), input);
        strncpy(text[i], line, N);
        text[i][N] = '\0';
    }

    // Генерация поворотов ключа
    for (int r = 0; r < 3; r++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                rot[r + 1][i][j] = rot[r][N - 1 - j][i];
            }
        }
    }

    // Проверка на правильность ключа
    int covered[MAXN][MAXN];
    memset(covered, 0, sizeof(covered));
    for (int r = 0; r < 4; r++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                covered[i][j] += rot[r][i][j];
            }
        }
    }

    int valid = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (covered[i][j] > 1)
            {
                valid = 0;
            }
        }
    }

    if (valid == 0)
    {
        fprintf(output, "No\n");
    }
    
    else
    {
        // Расшифровка текста
        char result[MAXN * MAXN + 1];
        int pos = 0;
        for (int r = 0; r < 4; r++)
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (rot[r][i][j])
                    {
                        result[pos++] = text[i][j];
                    }
                }
            }
        }
        result[pos] = '\0';
        fprintf(output, "%s\n", result);
    }

    fclose(input);
    fclose(output);
    return 0;
}