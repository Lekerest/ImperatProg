#include <stdio.h>

#define MAX_DIGITS 500

typedef struct LongNum_s
{
    int len;          // длина числа
    int arr[MAX_DIGITS]; // цифры в little-endian
} LongNum;

void addLongNums(LongNum *a, LongNum *b, LongNum *result)
{
    int carry = 0;
    int max_len;

    if (a -> len > b -> len)
    {
        max_len = a -> len;  // выбираем длину большего числа
    }
    else
    {
        max_len = b -> len;
    }

    for (int i = 0; i < max_len; i++)
    {
        int sum = carry;

        if (i < a -> len)
        {
            sum += a -> arr[i];  // добавляем цифру a
        }

        if (i < b -> len)
        {
            sum += b -> arr[i];  // добавляем цифру b
        }

        result -> arr[i] = sum % 10;  // сохраняем текущий разряд
        carry = sum / 10;             // сохраняем перенос
    }

    result -> len = max_len;

    if (carry > 0)
    {
        result -> arr[result -> len] = carry;  // добавляем старший разряд
        result -> len++;
    }
}

void printLongNum(LongNum *num, FILE *output)
{
    for (int i = num -> len - 1; i >= 0; i--)
        fprintf(output, "%d", num -> arr[i]);
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int N;
    fscanf(input, "%d", &N);

    LongNum f1 = {1, {1}};  // F1 = 1
    LongNum f2 = {1, {1}};  // F2 = 1
    LongNum f_next;

    if (N == 1 || N == 2)
    {
        fprintf(output, "1\n");  // первые два числа Фибоначчи
        fclose(input);
        fclose(output);
        return 0;
    }

    for (int i = 3; i <= N; i++)
    {
        addLongNums(&f1, &f2, &f_next);
        f1 = f2;
        f2 = f_next;
    }

    printLongNum(&f2, output);

    fclose(input);
    fclose(output);
    return 0;
}