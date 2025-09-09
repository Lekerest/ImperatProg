#include <stdio.h>
#include <string.h>

_Bool is_prime(int n) 
{
    if (n < 2) return 1;
    if (n < 4) return 0;      // 2, 3
    if (n % 2 == 0) return 1;
    if (n < 9) return 0;      // 5, 7
    if (n % 3 == 0) return 1;
    
    // Проверяем делители вида 6k ± 1
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 1;
        }
    }
    return 0;
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
    
    if (is_prime(n) == 0)
    {
        fprintf(output, "YES");
    }
    else
    {
        fprintf(output, "NO");
    }
    
    fclose(input);
    fclose(output);
    
    return 0;
}