#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    int length;
    fscanf(input, "%d", &length);

    int count = 0;
    int power = 1;
    int result = 0;
    int is_first = 1;

    for (int i = 0; i < length; i++) 
    {
        char c;
        fscanf(input, " %c", &c);

        if (c == '1') 
        {
            result += power;
        }
        power *= 2;
        count++;

        if (count == 8) 
        {
            if (is_first) 
            {
                fprintf(output, "%d", result);
                is_first = 0;
            } 
            else 
            {
                fprintf(output, " %d", result);
            }

            count = 0;
            power = 1;
            result = 0;
        }
    }

    // если осталось
    if (count > 0) 
    {
        if (is_first) 
        {
            fprintf(output, "%d", result);
        } 
        else 
        {
            fprintf(output, " %d", result);
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}
