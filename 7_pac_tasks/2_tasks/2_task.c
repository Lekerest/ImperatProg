#include <stdio.h>

#define MAX_N 100000
#define MAX_Q 100000
#define MAX_LEN 7  // длина слова ≤7 + 1 под '\0'

// структура узла списка
struct Node
{
    char str[MAX_LEN + 1];
    int next;
};

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int T;
    fscanf(input, "%d", &T);

    for (int test = 0; test < T; test++)
    {
        int N, F, Q;
        fscanf(input, "%d %d %d", &N, &F, &Q);

        struct Node nodes[MAX_N + MAX_Q];
        int total = N;

        for (int i = 0; i < N; i++)
        {
            fscanf(input, "%s %d", nodes[i].str, &nodes[i].next);
        }

        for (int q = 0; q < Q; q++)
        {
            int type, idx;
            fscanf(input, "%d %d", &type, &idx);

            if (type == 0)
            {
                char val[MAX_LEN + 1];
                fscanf(input, "%s", val);

                int newIndex = total;
                total++;

                int j;
                for (j = 0; j < MAX_LEN + 1; j++)
                {
                    nodes[newIndex].str[j] = val[j];
                    if (val[j] == 0)
                    {
                        break;
                    }
                }

                if (idx == -1)
                {
                    nodes[newIndex].next = F;
                    F = newIndex;
                }
                else
                {
                    nodes[newIndex].next = nodes[idx].next;
                    nodes[idx].next = newIndex;
                }

                fprintf(output, "%d\n", newIndex);
            }
            else if (type == 1)
            {
                int del;
                if (idx == -1)
                {
                    del = F;
                    F = nodes[F].next;
                }
                else
                {
                    del = nodes[idx].next;
                    nodes[idx].next = nodes[del].next;
                }

                fprintf(output, "%s\n", nodes[del].str);
            }
        }

        fprintf(output, "===\n");

        int cur = F;
        while (cur != -1)
        {
            fprintf(output, "%s\n", nodes[cur].str);
            cur = nodes[cur].next;
        }

        fprintf(output, "===\n");
    }

    fclose(input);
    fclose(output);
    return 0;
}
