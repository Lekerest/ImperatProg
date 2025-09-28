#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    int n, i, j;
    fscanf(input, "%d", &n);

    char s[n];
    for (i = 0; i < n; i++)
    {
        fscanf(input, " %c", &s[i]);
    }

    int pivot = -1;
    for (i = n - 2; i >= 0; i--)
    {
        if (s[i] < s[i + 1])
        {
            pivot = i;
            break;
        }
    }

    int swap_idx = pivot + 1;
    for (i = pivot + 1; i < n; i++)
    {
        if (s[i] > s[pivot] && s[i] <= s[swap_idx])
        {
            swap_idx = i;
        }
    }

    char temp = s[pivot];
    s[pivot] = s[swap_idx];
    s[swap_idx] = temp;

    for (i = pivot + 1; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (s[i] > s[j])
            {
                char t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (i != 0)
        {
            fprintf(output, " ");
        }
        fprintf(output, "%c", s[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}