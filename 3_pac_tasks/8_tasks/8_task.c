#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 1;
    }

    int n, i;
    fscanf(input, "%d", &n);

    if (n == 0)
    {
        fprintf(output, "0");
        fclose(input);
        fclose(output);
        return 0;
    }

    int heights[n];
    for (i = 0; i < n; i++)
    {
        fscanf(input, "%d", &heights[i]);
    }

    int left_max[n];
    int right_max[n];

    left_max[0] = heights[0];
    for (i = 1; i < n; i++)
    {
        if (heights[i] > left_max[i - 1])
        {
            left_max[i] = heights[i];
        }
        else
        {
            left_max[i] = left_max[i - 1];
        }
    }

    right_max[n - 1] = heights[n - 1];
    for (i = n - 2; i >= 0; i--)
    {
        if (heights[i] > right_max[i + 1])
        {
            right_max[i] = heights[i];
        }
        else
        {
            right_max[i] = right_max[i + 1];
        }
    }

    long long water = 0;
    int min_height;

    for (i = 0; i < n; i++)
    {
        if (left_max[i] < right_max[i])
        {
            min_height = left_max[i];
        }
        else
        {
            min_height = right_max[i];
        }

        if (min_height > heights[i])
        {
            water += min_height - heights[i];
        }
    }

    fprintf(output, "%lld", water);
    fclose(input);
    fclose(output);
    return 0;
}