#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    char inputstr[n + 1];
    fscanf(input, "%s", inputstr);

    int count = 0;
    char movestr[9];
    int length = strlen(inputstr);
    int is_first = 1;

    while (length >= 8)
    {
        strncpy(movestr, inputstr + (count * 8), 8);  
        movestr[8] = '\0';
        
        int result = 0;
        for(int i = 0; i < 8; i++)
        {
            if(movestr[i] == '1')
            {
                result += pow(2, i);
            }
        }
        
        if (is_first == 1) 
        {
            fprintf(output, "%d", result);
            is_first = 0;
        } 
        else 
        {
            fprintf(output, " %d", result);
        }
        
        count++;
        length -= 8;
    }

    int result = 0;
    int cnt = 0;
    for(int i = count * 8; inputstr[i] != '\0'; i++)
    {
        if(inputstr[i] == '1')
        {
            result += pow(2, cnt);
        }   
        cnt++;
    }
    
    if (cnt > 0) 
    {
        if (is_first == 1) 
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