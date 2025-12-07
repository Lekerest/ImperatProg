#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bio
{
    char name[31];
    int year;
    char country[11];
} Bio;

static int cmp_bio(const void *a, const void *b)
{
    const Bio *x = (const Bio *)a;
    const Bio *y = (const Bio *)b;

    return strcmp(x->name, y->name);
}

static int lower_bound_bio(Bio *a, int n, const char *key)
{
    int l = 0;
    int r = n;

    while (l < r)
    {
        int m = l + (r - l) / 2;

        if (strcmp(a[m].name, key) < 0)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }

    return l;
}

int main(void)
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    int n;
    fscanf(input_file, "%d\n", &n);

    Bio *bio = (Bio *)malloc((size_t)n * sizeof(Bio));

    for (int i = 0; i < n; i++)
    {
        fscanf(input_file, "\"%30[^\"]\" %d \"%10[^\"]\"\n", bio[i].name, &bio[i].year, bio[i].country);
    }

    qsort(bio, (size_t)n, sizeof(Bio), cmp_bio);

    int m;
    fscanf(input_file, "%d\n", &m);

    for (int i = 0; i < m; i++)
    {
        char actor[31];
        char movie[21];

        fscanf(input_file, "\"%30[^\"]\" \"%20[^\"]\"\n", actor, movie);

        int pos = lower_bound_bio(bio, n, actor);

        while (pos < n && strcmp(bio[pos].name, actor) == 0)
        {
            fprintf(output_file, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                    bio[pos].name, bio[pos].year, bio[pos].country, actor, movie);

            pos++;
        }
    }

    free(bio);

    fclose(input_file);
    fclose(output_file);

    return 0;
}