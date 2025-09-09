#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }
    
    int H, M, S, K;
    fscanf(input, "%d %d %d %d", &H, &M, &S, &K);
    
    int total_seconds = H * 3600 + M * 60 + S;
    
    total_seconds += K;
    
    int new_H = total_seconds / 3600;
    int remaining_seconds = total_seconds % 3600;
    int new_M = remaining_seconds / 60;
    int new_S = remaining_seconds % 60;
    
    new_H = new_H % 24;
    
    fprintf(output, "%d %d %d", new_H, new_M, new_S);
    
    fclose(input);
    fclose(output);
    
    return 0;
}