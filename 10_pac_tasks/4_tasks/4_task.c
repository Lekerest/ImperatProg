#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct AtomEntry
{
    char name[32];
    int count;
};

struct AtomMap
{
    struct AtomEntry *entries;
    int size;
    int capacity;
};

void init_map
(
    struct AtomMap *m
)
{
    m->entries = NULL;
    m->size = 0;
    m->capacity = 0;
}

void map_add
(
    struct AtomMap *m,
    const char *name,
    int cnt
)
{
    for (int i = 0; i < m->size; i++)
    {
        if (strcmp(m->entries[i].name, name) == 0)
        {
            m->entries[i].count += cnt;
            return;
        }
    }

    if (m->size == m->capacity)
    {
        int new_capacity;

        if (m->capacity == 0)
        {
            new_capacity = 4;
        }
        else
        {
            new_capacity = m->capacity * 2;
        }

        struct AtomEntry *new_entries =
            (struct AtomEntry *)malloc(sizeof(struct AtomEntry) * new_capacity);

        for (int i = 0; i < m->size; i++)
        {
            new_entries[i] = m->entries[i];
        }

        free(m->entries);

        m->entries = new_entries;
        m->capacity = new_capacity;
    }

    strcpy(m->entries[m->size].name, name);
    m->entries[m->size].count = cnt;
    m->size = m->size + 1;
}

void map_merge
(
    struct AtomMap *dest,
    struct AtomMap *src,
    int multiplier
)
{
    for (int i = 0; i < src->size; i++)
    {
        map_add(dest, src->entries[i].name, src->entries[i].count * multiplier);
    }
}

int cmp_atoms
(
    const void *a,
    const void *b
)
{
    const struct AtomEntry *x = (const struct AtomEntry *)a;
    const struct AtomEntry *y = (const struct AtomEntry *)b;
    return strcmp(x->name, y->name);
}

int read_number
(
    const char *s,
    int *pos,
    int length
)
{
    int value = 0;
    int i = *pos;

    if (i >= length || !isdigit(s[i]))
    {
        return 1;
    }

    while (i < length && isdigit(s[i]))
    {
        value = value * 10 + (s[i] - '0');
        i++;
    }

    *pos = i;
    return value;
}

int main()
{
    char *formula = (char *)malloc(350000);
    scanf("%s", formula);

    int length = (int)strlen(formula);

    struct AtomMap stack[300000];
    int top = 0;

    init_map(&stack[top]);

    int i = 0;

    while (i < length)
    {
        char c = formula[i];

        if (c == '(')
        {
            top++;
            init_map(&stack[top]);
            i++;
        }
        else if (c == ')')
        {
            i++;

            int mul = read_number(formula, &i, length);

            map_merge(&stack[top - 1], &stack[top], mul);

            free(stack[top].entries);
            top--;
        }
        else if (isupper(c))
        {
            char name[32];
            int p = 0;

            name[p] = c;
            p++;
            i++;

            while (i < length && islower(formula[i]))
            {
                name[p] = formula[i];
                p++;
                i++;
            }

            name[p] = '\0';

            int mul = read_number(formula, &i, length);

            map_add(&stack[top], name, mul);
        }
        else
        {
            i++;
        }
    }

    qsort(stack[0].entries, stack[0].size, sizeof(struct AtomEntry), cmp_atoms);

    for (int k = 0; k < stack[0].size; k++)
    {
        printf("%s", stack[0].entries[k].name);

        if (stack[0].entries[k].count > 1)
        {
            printf("%d", stack[0].entries[k].count);
        }
    }

    printf("\n");

    for (int k = 0; k <= top; k++)
    {
        free(stack[k].entries);
    }

    free(formula);

    return 0;
}
