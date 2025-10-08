#include <stdio.h>
#include <string.h>

int isDelimiter(char c) 
{
    return (c == '.' || c == ',' || c == ';' || c == ':');
}

void processWord(char *word, FILE *output) 
{
    if (strlen(word) == 0)
    {
        return;
    }

    int upperCount = 0;
    int length = 0;

    for (int i = 0; word[i] != '\0'; i++) 
    {
        char c = word[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            length++;
            if (c >= 'A' && c <= 'Z')
            {
                upperCount++;
            }
        }
    }

    if (length > 0)
    {
        fprintf(output, "%d/%d %s\n", upperCount, length, word);
    }
}

int main(void) 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    char line[1000005];
    if (fgets(line, sizeof(line), input)) 
    {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        char word[1000005];
        int wIndex = 0;

        for (int i = 0; line[i] != '\0'; i++) 
        {
            char c = line[i];
            if (isDelimiter(c))
            {
                word[wIndex] = '\0';
                processWord(word, output);
                wIndex = 0;
            }
            else
            {
                word[wIndex++] = c;
            }
        }

        word[wIndex] = '\0';
        processWord(word, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}