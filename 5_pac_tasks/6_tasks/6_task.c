#include <stdio.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int N;
    fscanf(input, "%d", &N);

    int digits[3000] = {1}; // начальное число 1
    int len = 1;

    for (int i = 2; i <= N; i++)
    {
        int carry = 0;

        for (int j = 0; j < len; j++)
        {
            int temp = digits[j] * i + carry;
            digits[j] = temp % 10;
            carry = temp / 10;
        }

        while (carry > 0)
        {
            digits[len] = carry % 10;
            carry /= 10;
            len++;
        }
    }

    for (int i = len - 1; i >= 0; i--)
    {
        fprintf(output, "%d", digits[i]);
    }
    fprintf(output, "\n");

    fclose(input);
    fclose(output);

    return 0;
}