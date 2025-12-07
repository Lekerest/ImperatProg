#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_SIZE 131071

typedef struct Bio
{
    char name[31];
    int year;
    char country[11];
    struct Bio *next;
} Bio;

unsigned long hash(const char *s)
{
    unsigned long h = 0;
    while (*s)
    {
        h = h * 131 + (unsigned char)(*s);
        s++;
    }
    return h % HT_SIZE;
}

int main(void)
{
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 1;

    int N;
    fscanf(fin, "%d\n", &N);

    Bio *table[HT_SIZE] = {0};

    for (int i = 0; i < N; i++)
    {
        Bio *b = (Bio *)malloc(sizeof(Bio));
        fscanf(fin, "\"%30[^\"]\" %d \"%10[^\"]\"\n", b->name, &b->year, b->country);
        unsigned long idx = hash(b->name);
        b->next = table[idx];
        table[idx] = b;
    }

    int M;
    fscanf(fin, "%d\n", &M);

    for (int i = 0; i < M; i++)
    {
        char actor[31], movie[21];
        fscanf(fin, "\"%30[^\"]\" \"%20[^\"]\"\n", actor, movie);
        unsigned long idx = hash(actor);
        for (Bio *p = table[idx]; p; p = p->next)
        {
            if (strcmp(p->name, actor) == 0)
            {
                fprintf(fout, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                        p->name, p->year, p->country, actor, movie);
            }
        }
    }

    fclose(fin);
    fclose(fout);

    for (int i = 0; i < HT_SIZE; i++)
    {
        Bio *p = table[i];
        while (p)
        {
            Bio *tmp = p;
            p = p->next;
            free(tmp);
        }
    }

    return 0;
}