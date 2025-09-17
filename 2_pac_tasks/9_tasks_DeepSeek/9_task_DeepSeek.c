#include <stdio.h>

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");
    
    if (input_file == NULL || output_file == NULL) {
        return 1;
    }

    char current_char;
    int in_block_comment = 0;
    int in_line_comment = 0;
    int prev_char = -1; // -1 означает отсутствие предыдущего символа

    while (fscanf(input_file, "%c", &current_char) == 1) {
        if (in_block_comment) {
            // Ищем конец блочного комментария */
            if (prev_char == '*' && current_char == '/') {
                in_block_comment = 0;
                prev_char = -1; // сбрасываем предыдущий символ
            } else {
                // Сохраняем только переводы строки
                if (current_char == '\n') {
                    fprintf(output_file, "%c", current_char);
                }
                prev_char = current_char;
            }
        } else if (in_line_comment) {
            // Ждём конца строки
            if (current_char == '\n') {
                in_line_comment = 0;
                fprintf(output_file, "%c", current_char);
                prev_char = -1;
            } else {
                prev_char = current_char;
            }
        } else {
            // Проверяем начало комментариев
            if (prev_char == '/' && current_char == '*') {
                in_block_comment = 1;
                prev_char = -1;
            } else if (prev_char == '/' && current_char == '/') {
                in_line_comment = 1;
                prev_char = -1;
            } else {
                // Выводим предыдущий символ если он был (и это не начало комментария)
                if (prev_char != -1) {
                    fprintf(output_file, "%c", prev_char);
                }
                prev_char = current_char;
            }
        }
    }

    // Выводим последний символ если не в комментарии
    if (!in_block_comment && !in_line_comment && prev_char != -1) {
        fprintf(output_file, "%c", prev_char);
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}