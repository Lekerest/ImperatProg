#include <stdio.h>
#include <string.h>

int readTime(char *iStr, int *oHours, int *oMinutes, int *oSeconds)
{
    int h = -1;
    int m = -1;
    int s = -1;
    int parts = 0;

    // Проверяем наличие символа '|'
    for (int i = 0; iStr[i] != '\0'; i++)
    {
        if (iStr[i] == '|')
        {
            return 0;
        }
    }

    parts = sscanf(iStr, "%d:%d:%d", &h, &m, &s);

    if (parts < 2)
    {
        return 0;
    }

    if (h < 0 || h > 23)
    {
        return 0;
    }

    if (m < 0 || m > 59)
    {
        return 0;
    }

    if (parts == 3)
    {
        if (s < 0 || s > 59)
        {
            return 0;
        }
    }

    // Заполняем выходные параметры (учитываем NULL)
    if (oHours != NULL)
    {
        *oHours = h;
    }

    if (oMinutes != NULL)
    {
        if (parts >= 2)
        {
            *oMinutes = m;
        }
    }

    if (oSeconds != NULL)
    {
        if (parts == 3)
        {
            *oSeconds = s;
        }

        if (parts == 2)
        {
            *oSeconds = 0;
        }
    }

    return 1;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    char str[17];

    if (fgets(str, sizeof(str), input) != NULL)
    {
        int len = strlen(str);

        if (len > 0)
        {
            if (str[len - 1] == '\n')
            {
                str[len - 1] = '\0';
            }
        }

        int h = -1;
        int m = -1;
        int s = -1;
        int res;

        // 1. Все указатели заданы
        res = readTime(str, &h, &m, &s);

        if (res == 0)
        {
            h = -1;
            m = -1;
            s = -1;
        }

        fprintf(output, "%d %d %d %d\n", res, h, m, s);

        // 2. oSeconds == NULL
        h = -1;
        m = -1;
        s = -1;

        res = readTime(str, &h, &m, NULL);

        if (res == 0)
        {
            h = -1;
            m = -1;
        }

        fprintf(output, "%d %d %d\n", res, h, m);

        // 3. oMinutes == NULL, oSeconds == NULL
        h = -1;
        m = -1;
        s = -1;

        res = readTime(str, &h, NULL, NULL);

        if (res == 0)
        {
            h = -1;
        }

        fprintf(output, "%d %d\n", res, h);
    }

    fclose(input);
    fclose(output);

    return 0;
}