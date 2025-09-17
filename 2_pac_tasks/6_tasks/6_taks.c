#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    int min_range;
    fscanf(input, "%d", &min_range);

    int max_range;
    fscanf(input, "%d", &max_range);

    int need_count_number;
    fscanf(input, "%d", &need_count_number);

    int count_progress = 0;

    for (int step = 1; step <= max_range - min_range; step++) 
    {
        for (int buf_min_range = min_range; buf_min_range <= max_range; buf_min_range++) 
        {
            int first_in_range = buf_min_range;
            
            int last_in_range = first_in_range + step * (need_count_number - 1);
            if (last_in_range > max_range) continue;
            
            if (last_in_range + step <= max_range) continue;
            
            count_progress++;
        }
    }

    fprintf(output, "%d", count_progress);

    fclose(input);
    fclose(output);
    
    return 0;
}