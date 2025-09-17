#include <stdio.h>

int main() 
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");
    
    if (input_file == NULL || output_file == NULL) 
    {
        return 1;
    }

    int source_base, target_base;
    char number_string[100];
    
    fscanf(input_file, "%d %d %s", &source_base, &target_base, number_string);
    
    long long decimal_number = 0;
    int current_position = 0;
    
    // Перевод из исходной системы в десятичную
    while (number_string[current_position] != '\0') 
    {
        int digit_value;
        char current_char = number_string[current_position];
        
        if (current_char >= '0' && current_char <= '9') 
        {
            digit_value = current_char - '0';
        } 
        else if (current_char >= 'a' && current_char <= 'z') 
        {
            digit_value = current_char - 'a' + 10;
        }
        else if (current_char >= 'A' && current_char <= 'Z') 
        {
            digit_value = current_char - 'A' + 10;
        }
        else 
        {
            // Некорректный символ
            fclose(input_file);
            fclose(output_file);
            return 1;
        }

        decimal_number = decimal_number * source_base + digit_value;
        current_position++;
    }
    
    // Обработка случая, когда число равно 0
    if (decimal_number == 0) 
    {
        fprintf(output_file, "0");
        fclose(input_file);
        fclose(output_file);
        return 0;
    }
    
    // Перевод из десятичной системы в целевую
    char result[100];
    int result_index = 0;
    long long temp_number = decimal_number;
    
    while (temp_number > 0) 
    {
        int remainder = temp_number % target_base;
        temp_number = temp_number / target_base;
        
        // Используем строчные буквы как указано в ТЗ
        if (remainder < 10) 
        {
            result[result_index] = remainder + '0';
        } 
        else 
        {
            result[result_index] = remainder - 10 + 'a';  // строчные буквы!
        }
        result_index++;
    }
    
    // Выводим результат в обратном порядке
    for (int i = result_index - 1; i >= 0; i--) 
    {
        fprintf(output_file, "%c", result[i]);
    }

    fclose(input_file);
    fclose(output_file);
    
    return 0;
}