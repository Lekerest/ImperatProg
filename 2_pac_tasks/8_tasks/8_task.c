#include <stdio.h>

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");
    
    if (input_file == NULL || output_file == NULL) {
        return 1;
    }

    int day, month, year, days_to_add;
    fscanf(input_file, "%d %d %d %d", &day, &month, &year, &days_to_add);
    
    // Переводим дату в общее количество дней от начала эры
    long long total_days = 0;
    
    // Добавляем дни из всех предыдущих лет
    for (int current_year = 1; current_year < year; current_year++) 
    {
        if ((current_year % 400 == 0) || (current_year % 4 == 0 && current_year % 100 != 0)) 
        {
            total_days += 366; // високосный год
        } 
        else 
        {
            total_days += 365; // обычный год
        }
    }
    
    // Добавляем дни из предыдущих месяцев текущего года
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) 
    {
        days_in_month[1] = 29; // високосный год
    }
    
    for (int current_month = 1; current_month < month; current_month++) 
    {
        total_days += days_in_month[current_month - 1];
    }
    
    // Добавляем дни текущего месяца
    total_days += day - 1;
    
    // Прибавляем нужное количество дней
    total_days += days_to_add;
    
    // Переводим обратно из общего количества дней в дату
    int result_year = 1;
    int result_month = 1;
    int result_day = 1;
    
    // Определяем год
    while (total_days >= 0) 
    {
        int days_in_current_year = 365;
        if ((result_year % 400 == 0) || (result_year % 4 == 0 && result_year % 100 != 0)) 
        {
            days_in_current_year = 366;
        }
        
        if (total_days < days_in_current_year) 
        {
            break;
        }
        
        total_days -= days_in_current_year;
        result_year++;
    }
    
    // Определяем месяц
    int result_days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((result_year % 400 == 0) || (result_year % 4 == 0 && result_year % 100 != 0)) 
    {
        result_days_in_month[1] = 29;
    }
    
    for (int current_month = 0; current_month < 12; current_month++) 
    {
        if (total_days < result_days_in_month[current_month]) 
        {
            result_month = current_month + 1;
            result_day = total_days + 1;
            break;
        }
        total_days -= result_days_in_month[current_month];
    }
    
    fprintf(output_file, "%d %d %d", result_day, result_month, result_year);
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}