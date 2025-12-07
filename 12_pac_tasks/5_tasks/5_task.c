#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bio
{
    char name[31];
    int year;
    char country[11];
} Bio;

typedef struct Role
{
    char actor[31];
    char movie[21];
} Role;

static int cmp_bio(const void *a, const void *b)
{
    const Bio *x = (const Bio *)a;
    const Bio *y = (const Bio *)b;

    return strcmp(x->name, y->name);
}

static int cmp_role(const void *a, const void *b)
{
    const Role *x = (const Role *)a;
    const Role *y = (const Role *)b;

    return strcmp(x->actor, y->actor);
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

    int m;
    fscanf(input_file, "%d\n", &m);

    Role *role = (Role *)malloc((size_t)m * sizeof(Role));

    for (int i = 0; i < m; i++)
    {
        fscanf(input_file, "\"%30[^\"]\" \"%20[^\"]\"\n", role[i].actor, role[i].movie);
    }

    qsort(bio, (size_t)n, sizeof(Bio), cmp_bio);
    qsort(role, (size_t)m, sizeof(Role), cmp_role);

    int i = 0;
    int j = 0;

    while (i < n && j < m)
    {
        int c = strcmp(bio[i].name, role[j].actor);

        if (c < 0)
        {
            i++;
        }
        else if (c > 0)
        {
            j++;
        }
        else
        {
            int i2 = i;
            int j2 = j;

            while (i2 < n && strcmp(bio[i2].name, bio[i].name) == 0)
            {
                i2++;
            }

            while (j2 < m && strcmp(role[j2].actor, role[j].actor) == 0)
            {
                j2++;
            }

            for (int a = i; a < i2; a++)
            {
                for (int b = j; b < j2; b++)
                {
                    fprintf(output_file, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                            bio[a].name, bio[a].year, bio[a].country, role[b].actor, role[b].movie);
                }
            }

            i = i2;
            j = j2;
        }
    }

    free(role);
    free(bio);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
