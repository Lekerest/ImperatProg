#include <stdio.h>
#include <stdlib.h>

char *concat(char *pref, char *suff) {
    // Находим конец pref
    while (*pref) {
        pref++;
    }
    // Копируем suff в конец pref
    while (*suff) {
        *pref = *suff;
        pref++;
        suff++;
    }
    // Завершающий нулевой символ
    *pref = '\0';
    return pref; // указатель на '\0'
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");

    if (!fin || !fout) {
        return 1;
    }

    int N;
    fscanf(fin, "%d", &N);

    // Выделяем достаточно большой буфер
    // Макс. N=10000, длина строки ≤100 → 1 000 000 символов
    char *result = (char *)malloc(1100000 * sizeof(char));
    if (!result) {
        return 1;
    }

    result[0] = '\0'; // изначально пустая строка

    char buffer[128]; // буфер для чтения строк (100 символов + запас)

    for (int i = 0; i < N; i++) {
        fscanf(fin, "%s", buffer);
        concat(result, buffer);
    }

    fprintf(fout, "%s\n", result);

    free(result);
    fclose(fin);
    fclose(fout);
    return 0;
}