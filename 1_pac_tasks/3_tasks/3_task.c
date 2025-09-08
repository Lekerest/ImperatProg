#include <stdio.h>
#include <string.h>

int count_nines(double num) {
    char str[50];
    sprintf(str, "%.2f", num);
    
    int count = 0;
    for (int j = 0; str[j] != '\0'; j++) {
        if (str[j] == '9') {
            count++;
        }
    }
    return count;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }
    
    int n;
    if (fscanf(input, "%d", &n) != 1) 
    {
        fclose(input);
        fclose(output);
        return 1;
    }
    
    int additional_seven = 0;

    for (int i = 0; i < n; i++) 
    {
        double number;
        if (fscanf(input, "%lf", &number) != 1) {
            fclose(input);
            fclose(output);
            return 1;
        }
        
        int nines_before = count_nines(number);
        
        number -= 0.01;
        
        int nines_after = count_nines(number);
        
        additional_seven += (nines_after - nines_before);
    }
    
    fprintf(output, "%d", additional_seven);
    
    fclose(input);
    fclose(output);
    
    return 0;
}