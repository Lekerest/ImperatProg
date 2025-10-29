#include <stdio.h>

void print_in_base(FILE *out, long long number, int base)
{
    if (number == 0)
    {
        return;
    }

    int remainder = number % base;
    number = number / base;

    print_in_base(out, number, base);

    if (remainder < 10)
    {
        fprintf(out, "%c", remainder + '0');
    }
    else
    {
        fprintf(out, "%c", remainder - 10 + 'a');
    }
}

int main() 
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");
    
    if (input_file == NULL || output_file == NULL) 
    {
        return 1;
    }

    int source_base, target_base;
    fscanf(input_file, "%d %d", &source_base, &target_base);

    // инт - 2 147 483 647
    long long decimal_number = 0;
    char ch;

    // читаем число посимвольно
    while (fscanf(input_file, " %c", &ch) == 1) 
    {
        int digit_value;

        if (ch >= '0' && ch <= '9') 
        {
            digit_value = ch - '0';
        } 
        else if (ch >= 'a' && ch <= 'z') 
        {
            digit_value = ch - 'a' + 10;
        }
        else if (ch >= 'A' && ch <= 'Z') 
        {
            digit_value = ch - 'A' + 10;
        }
        else 
        {
            fclose(input_file);
            fclose(output_file);
            return 1; // некорректный символ
        }

        decimal_number = decimal_number * source_base + digit_value;
    }

    // случай числа 0
    if (decimal_number == 0) 
    {
        fprintf(output_file, "0");
    } 
    else 
    {
        print_in_base(output_file, decimal_number, target_base);
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}