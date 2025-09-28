#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    char line[1001];

    if (fscanf(input, "%1000[^\n]", line) != 1)
    {
        fclose(input);
        fclose(output);
        return 0;
    }

    int first_word = 1;
    char *p = line;

    while (*p != '\0')
    {
        while (*p == ' ')
        {
            p++;
        }

        if (*p == '\0')
        {
            break;
        }

        char *start = p;

        while (*p != '\0' && *p != ' ')
        {
            p++;
        }

        char *end = p - 1;
        int word_len = (int)(end - start + 1);

        if (!first_word)
        {
            fprintf(output, " ");
        }

        if (word_len == 1)
        {
            fprintf(output, "%c", *start);
        }
        else
        {
            fprintf(output, "%c%d%c", *start, word_len - 2, *end);
        }

        first_word = 0;
    }

    fclose(input);
    fclose(output);
    return 0;
}