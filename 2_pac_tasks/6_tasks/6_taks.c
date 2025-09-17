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
        // Для каждого шага проверяем все стартовые позиции
        for (int start = min_range; start <= max_range; start++) 
        {
            // Вычисляем последний элемент прогрессии
            int last = start + step * (need_count_number - 1);
            
            // Пропускаем если последний элемент выходит за границы
            if (last > max_range) continue;
            
            // Проверяем что элемент перед первым не в диапазоне
            if (start - step >= min_range) continue;
            
            // Проверяем что элемент после последнего не в диапазоне
            if (last + step <= max_range) continue;
            
            count_progress++;
        }
    }

    fprintf(output, "%d", count_progress);

    fclose(input);
    fclose(output);
    
    return 0;
}