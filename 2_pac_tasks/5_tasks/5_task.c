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

    char inputstr[length+1];
    fscanf(input, "%s", inputstr);

    int is_first = 1;
    int position = 0;

    while (length - position >= 8)
    {
        int result = 0;
        int power = 1;
        
        for (int i = 0; i < 8; i++) 
        {
            if (inputstr[position + i] == '1') 
            {
                result += power;
            }
            power *= 2;
        }
        
        if (is_first) 
        {
            fprintf(output, "%d", result);
            is_first = 0;
        } 
        else 
        {
            fprintf(output, " %d", result);
        }
        
        position += 8;
    }

    if (position < length) 
    {
        int result = 0;
        int power = 1;
        
        for (int i = position; i < length; i++) {
            if (inputstr[i] == '1') {
                result += power;
            }
            power *= 2;
        }
        
        if (is_first) {
            fprintf(output, "%d", result);
        } else {
            fprintf(output, " %d", result);
        }
    }

    fclose(input);
    fclose(output);
    
    return 0;
}