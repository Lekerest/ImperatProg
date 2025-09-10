#include <stdio.h>
#include <string.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }

    char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    char inputstr[10];
    fscanf(input, "%s", &inputstr);

    int count = 0;
    int index = -1;
    for (int i = 0; i < 7; i++) 
    {
        if (strncmp(inputstr, days[i], strlen(inputstr)) == 0) 
        {
            count++;
            index = i;  
        }
    }

    if (count == 0) 
    {
        fprintf(output, "Invalid");
    } 
    else if (count > 1) 
    {
        fprintf(output, "Ambiguous");
    } else 
    {
        fprintf(output, "%d", index + 1);
    }
    
    fclose(input);
    fclose(output);
    
    return 0;
}