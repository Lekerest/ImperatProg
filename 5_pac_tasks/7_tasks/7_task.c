#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    double p;
    double s;
    double l;
} Asymp;

int cmp(double a, double b)
{
    const double eps = 1e-9;
    if (fabs(a - b) < eps)
    {
        return 0;
    }
    return a > b ? 1 : -1;
}

int compare_Asymp(Asymp a, Asymp b)
{
    int cp = cmp(a.p, b.p);
    if (cp != 0)
    {
        return cp;
    }
    int cs = cmp(a.s, b.s);
    if (cs != 0)
    {
        return cs;
    }
    return cmp(a.l, b.l);
}

Asymp parse(const char* line)
{
    Asymp res;
    res.p = 1.0;
    res.s = 0.0;
    res.l = 0.0;
    char inside[100];
    
    if (sscanf(line, "O( %[^)] )", inside) != 1)
    {
        // Предполагаем корректный ввод, ошибка не обрабатывается
        return res;
    }
    
    // Разбор внутренней части на токены
    char copy[100];
    strcpy(copy, inside);
    char* token = strtok(copy, " ");
    
    while (token != NULL)
    {
        if (strcmp(token, "1") == 0)
        {
            // Константа, ничего не меняем
            token = strtok(NULL, " ");
            continue;
        }
        
        if (strstr(token, "logN^") == token)
        {
            // logN^l с указанной степенью
            sscanf(token + 5, "%lf", &res.l);
        }
        
        else if (strcmp(token, "logN") == 0)
        {
            // logN без степени, l=1
            res.l = 1.0;
        }
        
        else if (strstr(token, "N^") == token)
        {
            // N^s с указанной степенью
            sscanf(token + 2, "%lf", &res.s);
        }
        
        else if (strcmp(token, "N") == 0)
        {
            // N без степени, s=1
            res.s = 1.0;
        }
        
        else if (strstr(token, "^N") != NULL)
        {
            // p^N
            sscanf(token, "%lf^N", &res.p);
        }
        token = strtok(NULL, " ");
    }
    return res;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    char buf[100];
    fgets(buf, sizeof(buf), input);
    int Q;
    sscanf(buf, "%d", &Q);

    for (int i = 0; i < Q; i++)
    {
        char line1[100];
        char line2[100];
        fgets(line1, sizeof(line1), input);
        fgets(line2, sizeof(line2), input);
        Asymp a = parse(line1);
        Asymp b = parse(line2);
        int res = compare_Asymp(a, b);
        fprintf(output, "%d\n", res);
    }

    fclose(input);
    fclose(output);
    return 0;
}