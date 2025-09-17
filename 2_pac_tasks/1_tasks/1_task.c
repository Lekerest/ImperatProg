#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }

    char s[11];
    fscanf(input, "%10s", s);

    int length = 0;
    while (s[length] != '\0') {
        length++;
    }

    int possible[7] = {1, 1, 1, 1, 1, 1, 1};
    int count = 7;

    // Проверяем каждый день недели
    char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    
    for (int i = 0; i < 7; i++) {
        int match = 1;
        for (int j = 0; j < length; j++) {
            if (s[j] != days[i][j]) {
                match = 0;
                break;
            }
        }
        if (!match) {
            possible[i] = 0;
            count--;
        }
    }

    if (count == 0) {
        fprintf(output, "Invalid");
    } else if (count > 1) {
        fprintf(output, "Ambiguous");
    } else {
        for (int i = 0; i < 7; i++) {
            if (possible[i]) {
                fprintf(output, "%d", i + 1);
                break;
            }
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}