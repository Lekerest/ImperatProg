#include <stdio.h>
#include <stdlib.h>

#define HT_SIZE 2097152

unsigned long long hsh(unsigned long long x)
{
    return x % HT_SIZE;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    unsigned long long M, a, b, c;
    fscanf(input, "%llu %llu %llu %llu", &M, &a, &b, &c);
    fclose(input);

    unsigned long long *states = (unsigned long long *)malloc(HT_SIZE * sizeof(unsigned long long));
    unsigned long long *steps = (unsigned long long *)malloc(HT_SIZE * sizeof(unsigned long long));
    unsigned char *used = (unsigned char *)calloc(HT_SIZE, 1);

    unsigned long long state = 1;
    unsigned long long step = 0;
    unsigned long long l = 0, r = 0;

    while (1)
    {
        unsigned long long idx = hsh(state);
        while (used[idx] && states[idx] != state) idx = (idx + 1) % HT_SIZE;

        if (used[idx])
        {
            l = steps[idx];
            r = step;
            break;
        }

        used[idx] = 1;
        states[idx] = state;
        steps[idx] = step;

        state = (state * state * a + state * b + c) % M;
        step++;
    }

    fprintf(output, "%llu %llu\n", l, r);

    free(states);
    free(steps);
    free(used);
    fclose(output);
    return 0;
}