#include <stdio.h>

char *concat(char *pref, char *suff) 
{
    // Находим конец pref
    while (*pref != '\0') 
    {
        pref++;
    }

    // Копируем suff в конец pref
    while (*suff != '\0') 
    {
        *pref = *suff;
        pref++;
        suff++;

    }

    *pref = '\0';
    return pref;
}

int main() 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    int N;
    fscanf(input, "%d", &N);
    char result[N * 101];
    result[0] = '\0';

    char buffer[101];

    for (int i = 0; i < N; i++) 
    {
        fscanf(input, "%s", buffer);
        concat(result, buffer);
    }

    fprintf(output, "%s", result);

    fclose(input);
    fclose(output);
    return 0;
}