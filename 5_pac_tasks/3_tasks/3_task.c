#include <stdio.h>
#include <string.h>

typedef struct Label_s 
{
    char name[16]; // имя автора (заканчивается нулём)
    int age;        // возраст автора (сколько лет)
} 
Label;

typedef struct NameStats_s 
{
    int cntTotal; // сколько всего подписей
    int cntLong;  // сколько подписей с именами длиннее 10 букв
} 
NameStats;

typedef struct AgeStats_s 
{
    int cntTotal;  // сколько всего подписей
    int cntAdults; // сколько подписей взрослых (>= 18 лет)
    int cntKids;   // сколько подписей детей (< 14 лет)
} 
AgeStats;

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges)
{
    oNames -> cntTotal = cnt;
    oNames -> cntLong = 0;

    oAges -> cntTotal = cnt;
    oAges -> cntAdults = 0;
    oAges -> cntKids = 0;

    for (int i = 0; i < cnt; i++)
    {
        int len = strlen(arr[i].name);

        if (len > 10)
        {
            oNames->cntLong++;
        }

        if (arr[i].age >= 18)
        {
            oAges->cntAdults++;
        }

        else if (arr[i].age < 14)
        {
            oAges->cntKids++;
        }
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

    int n;
    fscanf(input, "%d", &n);

    Label labels[n];

    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%15s %d let", labels[i].name, &labels[i].age);
    }

    NameStats nameStats;
    AgeStats ageStats;

    calcStats(labels, n, &nameStats, &ageStats);

    fprintf(output, "names: total = %d\n", nameStats.cntTotal);
    fprintf(output, "names: long = %d\n", nameStats.cntLong);
    fprintf(output, "ages: total = %d\n", ageStats.cntTotal);
    fprintf(output, "ages: adult = %d\n", ageStats.cntAdults);
    fprintf(output, "ages: kid = %d", ageStats.cntKids);

    fclose(input);
    fclose(output);
    return 0;
}