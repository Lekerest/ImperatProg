#include <stdio.h>
#include <stdlib.h>


// ---------- ХЕШ-ФУНКЦИЯ ----------
// Преобразует состояние генератора в индекс хеш-таблицы.
// Здесь берём остаток по размеру таблицы, чтобы получить диапазон 0..2097152-1.
unsigned long long hsh(unsigned long long x)
{
    return x % 2097152;
}


int main(void)
{
    // ---------- ОТКРЫТИЕ ВХОДНОГО И ВЫХОДНОГО ФАЙЛОВ ----------
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // ---------- ЧТЕНИЕ ПАРАМЕТРОВ ----------
    unsigned long long modulo;
    unsigned long long multiplier_a;
    unsigned long long multiplier_b;
    unsigned long long add_c;

    fscanf(input, "%llu %llu %llu %llu", &modulo, &multiplier_a, &multiplier_b, &add_c);
    fclose(input);


    // ---------- СОЗДАНИЕ ХЕШ-ТАБЛИЦЫ ----------
    // states — хранит встреченные состояния
    // steps  — хранит номер шага, на котором состояние впервые встретилось
    // used   — показывает, занята ли ячейка
    unsigned long long *states = (unsigned long long *)malloc(2097152 * sizeof(unsigned long long));
    unsigned long long *steps = (unsigned long long *)malloc(2097152 * sizeof(unsigned long long));
    unsigned char *used = (unsigned char *)calloc(2097152, 1);

    // ---------- НАЧАЛЬНОЕ СОСТОЯНИЕ И ПЕРЕМЕННЫЕ ПОИСКА ЦИКЛА ----------
    unsigned long long current_state = 1;
    unsigned long long current_step = 0;

    unsigned long long left_border = 0;
    unsigned long long right_border = 0;

    // ---------- ПОИСК ПОВТОРНОГО СОСТОЯНИЯ ----------
    // Как только состояние повторилось, значит нашли цикл:
    // left_border  — шаг первого появления этого состояния
    // right_border — текущий шаг (момент повторения)
    while (1)
    {
        unsigned long long index = hsh(current_state);

        while (used[index] && states[index] != current_state)
        {
            index = (index + 1) % 2097152;
        }

        if (used[index])
        {
            left_border = steps[index];
            right_border = current_step;
            break;
        }

        used[index] = 1;
        states[index] = current_state;
        steps[index] = current_step;

        // ---------- ПЕРЕХОД К СЛЕДУЮЩЕМУ СОСТОЯНИЮ ----------
        current_state = (current_state * current_state * multiplier_a + current_state * multiplier_b + add_c) % modulo;

        current_step = current_step + 1;
    }

    // ---------- ВЫВОД ОТВЕТА ----------
    fprintf(output, "%llu %llu\n", left_border, right_border);

    // ---------- ОСВОБОЖДЕНИЕ ПАМЯТИ И ЗАКРЫТИЕ ФАЙЛА ----------
    free(states);
    free(steps);
    free(used);

    fclose(output);

    return 0;
}