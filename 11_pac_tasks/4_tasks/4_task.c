#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_SIZE 131071
#define MAX_LINE 256

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
    while (*s) { h = h * 131 + (unsigned char)(*s); s++; }
    return h % HT_SIZE;
}

void parseBio(char *line, Bio *b)
{
    char *p = line;
    p++; // пропустить первую кавычку
    int i = 0;
    while (*p && *p != '"' && i < 30) b->name[i++] = *p++;
    b->name[i] = 0;
    while (*p && (*p < '0' || *p > '9')) p++;
    b->year = atoi(p);
    while (*p && *p != '"') p++;
    p++;
    i = 0;
    while (*p && *p != '"' && i < 10) b->country[i++] = *p++;
    b->country[i] = 0;
}

void parseMovie(char *line, char *actor, char *movie)
{
    char *p = line;
    p++;
    int i = 0;
    while (*p && *p != '"' && i < 30) actor[i++] = *p++;
    actor[i] = 0;
    while (*p && *p != '"') p++;
    p++;
    i = 0;
    while (*p && *p != '"' && i < 20) movie[i++] = *p++;
    movie[i] = 0;
}

int main(void)
{
    FILE *fin = fopen("input.txt","r");
    FILE *fout = fopen("output.txt","w");
    if (!fin || !fout) return 1;

    int N; fscanf(fin,"%d\n",&N);
    Bio *table[HT_SIZE] = {0};

    char line[MAX_LINE];
    for (int i = 0; i < N; i++)
    {
        fgets(line, MAX_LINE, fin);
        Bio *b = (Bio*)malloc(sizeof(Bio));
        parseBio(line,b);
        unsigned long idx = hash(b->name);
        b->next = table[idx];
        table[idx] = b;
    }

    int M; fscanf(fin,"%d\n",&M);
    for (int i = 0; i < M; i++)
    {
        fgets(line, MAX_LINE, fin);
        char actor[31], movie[21];
        parseMovie(line, actor, movie);
        unsigned long idx = hash(actor);
        for (Bio *p = table[idx]; p; p = p->next)
            if (strcmp(p->name, actor)==0)
                fprintf(fout,"\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                        p->name,p->year,p->country,actor,movie);
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