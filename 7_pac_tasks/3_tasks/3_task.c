#include <stdio.h>

#define MAX_KEYS 1000001
#define MAX_LEN 8

// структура узла списка
struct Node
{
    char str[MAX_LEN];
    int next;
};

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 0;
    }

    int N;
    fscanf(input, "%d", &N);

    struct Node nodes[N];
    int head[MAX_KEYS];
    int tail[MAX_KEYS];

    for (int i = 0; i < MAX_KEYS; i++)
    {
        head[i] = -1;
        tail[i] = -1;
    }

    int key;
    for (int i = 0; i < N; i++)
    {
        fscanf(input, "%d %s", &key, nodes[i].str);

        nodes[i].next = -1;

        if (head[key] == -1)
        {
            head[key] = i;
            tail[key] = i;
        }
        else
        {
            nodes[tail[key]].next = i;
            tail[key] = i;
        }
    }

    for (int k = 0; k < MAX_KEYS; k++)
    {
        int cur = head[k];
        while (cur != -1)
        {
            fprintf(output, "%d %s\n", k, nodes[cur].str);
            cur = nodes[cur].next;
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}