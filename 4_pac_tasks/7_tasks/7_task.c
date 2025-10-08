#include <stdio.h>
#include <string.h>

int isPrefix(char *a, char *b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);

    if (lenA > lenB)
    {
        lenA = lenB;
    }

    for (int i = 0; i < lenA; i++)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
    }

    return 1;
}

void findUniquePrefix(char words[100][101], int count, int index, char *prefix)
{
    int len = strlen(words[index]);

    for (int p = 1; p <= len; p++)
    {
        int unique = 1;

        for (int j = 0; j < count; j++)
        {
            if (j == index)
            {
                continue;
            }

            if (strncmp(words[index], words[j], p) == 0)
            {
                unique = 0;
                break;
            }
        }

        if (unique == 1)
        {
            strncpy(prefix, words[index], p);
            prefix[p] = '\0';
            return;
        }
    }

    strcpy(prefix, words[index]);
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    char words[100][101];
    int count = 0;

    while (count < 100 && fscanf(input, "%100s", words[count]) == 1)
    {
        if (strlen(words[count]) == 0)
        {
            break;
        }

        count++;
    }

    char prefixes[100][101];

    for (int i = 0; i < count; i++)
    {
        findUniquePrefix(words, count, i, prefixes[i]);
    }

    for (int i = count - 1; i >= 0; i--)
    {
        fprintf(output, "%s", prefixes[i]);

        if (i > 0)
        {
            fprintf(output, "#");
        }
    }

    fprintf(output, "\n");

    fclose(input);
    fclose(output);

    return 0;
}