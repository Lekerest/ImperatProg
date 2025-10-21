#include <stdio.h>

#define MAX_N 100000
#define MAX_Q 100000

// структура узла
struct Node
{
    int value;
    int next;
    int prev;
};

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int T;
    fscanf(input, "%d", &T);

    for (int t = 0; t < T; t++)
    {
        int N, F, L, Q;
        fscanf(input, "%d %d %d %d", &N, &F, &L, &Q);

        struct Node nodes[MAX_N + MAX_Q];

        for (int i = 0; i < N; i++)
        {
            fscanf(input, "%d %d %d", &nodes[i].value, &nodes[i].next, &nodes[i].prev);
        }

        int total = N;

        for (int q = 0; q < Q; q++)
        {
            int type, idx, val;
            fscanf(input, "%d %d", &type, &idx);

            if (type == 0)
            {
                int del = idx;

                if (nodes[del].prev != -1)
                {
                    nodes[nodes[del].prev].next = nodes[del].next;
                }
                else
                {
                    F = nodes[del].next;
                }

                if (nodes[del].next != -1)
                {
                    nodes[nodes[del].next].prev = nodes[del].prev;
                }
                else
                {
                    L = nodes[del].prev;
                }

                fprintf(output, "%d\n", nodes[del].value);
            }
            else
            {
                fscanf(input, "%d", &val);
                int newIndex = total++;
                nodes[newIndex].value = val;

                if (type == 1)
                {
                    if (idx == -1)
                    {
                        nodes[newIndex].prev = -1;
                        nodes[newIndex].next = F;

                        if (F != -1)
                        {
                            nodes[F].prev = newIndex;
                        }
                        else
                        {
                            L = newIndex;
                        }

                        F = newIndex;
                    }
                    else
                    {
                        nodes[newIndex].next = nodes[idx].next;
                        nodes[newIndex].prev = idx;

                        if (nodes[idx].next != -1)
                        {
                            nodes[nodes[idx].next].prev = newIndex;
                        }
                        else
                        {
                            L = newIndex;
                        }

                        nodes[idx].next = newIndex;
                    }
                }
                else if (type == -1)
                {
                    if (idx == -1)
                    {
                        nodes[newIndex].next = -1;
                        nodes[newIndex].prev = L;

                        if (L != -1)
                        {
                            nodes[L].next = newIndex;
                        }
                        else
                        {
                            F = newIndex;
                        }

                        L = newIndex;
                    }
                    else
                    {
                        nodes[newIndex].prev = nodes[idx].prev;
                        nodes[newIndex].next = idx;

                        if (nodes[idx].prev != -1)
                        {
                            nodes[nodes[idx].prev].next = newIndex;
                        }
                        else
                        {
                            F = newIndex;
                        }

                        nodes[idx].prev = newIndex;
                    }
                }

                fprintf(output, "%d\n", newIndex);
            }
        }

        fprintf(output, "===\n");

        int cur = F;
        while (cur != -1)
        {
            fprintf(output, "%d\n", nodes[cur].value);
            cur = nodes[cur].next;
        }

        fprintf(output, "===\n");
    }

    fclose(input);
    fclose(output);
    return 0;
}