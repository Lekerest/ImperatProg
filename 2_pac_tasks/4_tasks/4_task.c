#include <stdio.h>

int main()
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    if (input_file == NULL || output_file == NULL)
    {
        return 1;
    }

    int a1, a2, b1, b2, c1, c2;
    fscanf(input_file, "%d %d %d %d %d %d", &a1, &a2, &b1, &b2, &c1, &c2);

    int can_fit = 0;

    if ((b1 + c1 <= a1 && ( (b2 <= a2 && c2 <= a2) )) ||
        (b1 + c2 <= a1 && ( (b2 <= a2 && c1 <= a2) )) ||
        (b2 + c1 <= a1 && ( (b1 <= a2 && c2 <= a2) )) ||
        (b2 + c2 <= a1 && ( (b1 <= a2 && c1 <= a2) )) ||

        (b1 + c1 <= a2 && ( (b2 <= a1 && c2 <= a1) )) ||
        (b1 + c2 <= a2 && ( (b2 <= a1 && c1 <= a1) )) ||
        (b2 + c1 <= a2 && ( (b1 <= a1 && c2 <= a1) )) ||
        (b2 + c2 <= a2 && ( (b1 <= a1 && c1 <= a1) )) ||

        (b2 + c2 <= a1 && ( (b1 <= a2 && c1 <= a2) )))
        
    {
        can_fit = 1;
    }

    if (can_fit)
    {
        fprintf(output_file, "YES");
    }
    else
    {
        fprintf(output_file, "NO");
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}