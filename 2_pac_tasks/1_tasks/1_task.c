// Monday - M 6
// Tuesday - Tu 7
// Wednesday - W 9
// Thursday - Th 8
// Friday - F 6
// Saturday - Sa 8
// Sunday - Su 6

#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }

    char inputstr[10];
    fscanf(input, "%s", &inputstr);

    int sizestr = sizeof(inputstr);

    
    // int arr[10];
        
    //     for (int i = 0; i < 3; i++) 
    //     {
    //         if (fscanf(input, "%d", &arr[i]) != 1)
    //         {
    //             fclose(input);
    //             fclose(output);
    //             return 1;
    
    
    fprintf(output, "%d", sizestr);
    
    fclose(input);
    fclose(output);
    
    return 0;
}