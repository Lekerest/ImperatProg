#include <stdio.h>

int is_leap_year(int year)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    {
        return 1;
    }
    return 0;
}

int main()
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    if (input_file == NULL || output_file == NULL)
    {
        return 1;
    }

    int day, month, year, days_to_add;
    fscanf(input_file, "%d %d %d %d", &day, &month, &year, &days_to_add);

    long long total_days = 0;

    // Считаем дни всех предыдущих лет
    int current_year = 1;
    while (current_year < year)
    {
        total_days += is_leap_year(current_year) ? 366 : 365;
        current_year++;
    }

    // Считаем дни предыдущих месяцев текущего года
    int m1 = 31, m2 = 28, m3 = 31, m4 = 30, m5 = 31, m6 = 30;
    int m7 = 31, m8 = 31, m9 = 30, m10 = 31, m11 = 30, m12 = 31;

    if (is_leap_year(year))
    {
        m2 = 29;
    }

    if (month > 1) total_days += m1;
    if (month > 2) total_days += m2;
    if (month > 3) total_days += m3;
    if (month > 4) total_days += m4;
    if (month > 5) total_days += m5;
    if (month > 6) total_days += m6;
    if (month > 7) total_days += m7;
    if (month > 8) total_days += m8;
    if (month > 9) total_days += m9;
    if (month > 10) total_days += m10;
    if (month > 11) total_days += m11;

    total_days += day - 1;
    total_days += days_to_add;

    // Определяем год
    int result_year = 1;
    while (1)
    {
        int days_in_year = is_leap_year(result_year) ? 366 : 365;
        if (total_days < days_in_year)
        {
            break;
        }
        total_days -= days_in_year;
        result_year++;
    }

    // Определяем месяц и день
    int dm1 = 31, dm2 = 28, dm3 = 31, dm4 = 30, dm5 = 31, dm6 = 30;
    int dm7 = 31, dm8 = 31, dm9 = 30, dm10 = 31, dm11 = 30, dm12 = 31;

    if (is_leap_year(result_year))
    {
        dm2 = 29;
    }

    int result_month = 1;
    while (1)
    {
        int days_in_month = 0;
        if (result_month == 1) days_in_month = dm1;
        else if (result_month == 2) days_in_month = dm2;
        else if (result_month == 3) days_in_month = dm3;
        else if (result_month == 4) days_in_month = dm4;
        else if (result_month == 5) days_in_month = dm5;
        else if (result_month == 6) days_in_month = dm6;
        else if (result_month == 7) days_in_month = dm7;
        else if (result_month == 8) days_in_month = dm8;
        else if (result_month == 9) days_in_month = dm9;
        else if (result_month == 10) days_in_month = dm10;
        else if (result_month == 11) days_in_month = dm11;
        else if (result_month == 12) days_in_month = dm12;

        if (total_days < days_in_month)
        {
            break;
        }
        total_days -= days_in_month;
        result_month++;
    }

    int result_day = total_days + 1;

    fprintf(output_file, "%d %d %d", result_day, result_month, result_year);

    fclose(input_file);
    fclose(output_file);
    return 0;
}
