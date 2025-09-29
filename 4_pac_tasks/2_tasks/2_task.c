#include <stdio.h>

void reverse(char *start, int len)
{
    int i;
    char temp;
    for (i = 0; i < len / 2; i++)
    {
        temp = start[i];
        start[i] = start[len - i - 1];
        start[len - i - 1] = temp;
    }
}

int my_strlen(const char *s)
{
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    int N;
    fscanf(input, "%d", &N);

    char buffer[101];

    for (int i = 0; i < N; i++)
    {
        fscanf(input, "%s", buffer);

        int len = my_strlen(buffer);

        reverse(buffer, len);

        fprintf(output, "%s\n", buffer);
    }

    fclose(input);
    fclose(output);
    return 0;
}