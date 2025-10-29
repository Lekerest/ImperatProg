#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PEOPLE 25
#define MAX_LEN 100

void shuffle(char arr[][MAX_LEN], int n) {
    srand((unsigned int)time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        if (i == j) continue; // ничего не делаем, если совпали индексы

        char temp[MAX_LEN];
        memcpy(temp, arr[i], MAX_LEN);
        memcpy(arr[i], arr[j], MAX_LEN);
        memcpy(arr[j], temp, MAX_LEN);
    }
}

int main() {
    FILE *fin, *fout;
    char people[MAX_PEOPLE][MAX_LEN];
    int count = 0;

    fin = fopen("inputname.txt", "r");
    if (!fin) {
        perror("Ошибка открытия inputname.txt");
        return 1;
    }

    while (count < MAX_PEOPLE && fgets(people[count], MAX_LEN, fin)) {
        size_t len = strlen(people[count]);
        if (len > 0 && people[count][len - 1] == '\n')
            people[count][len - 1] = '\0';
        count++;
    }
    fclose(fin);

    if (count == 0) {
        printf("Файл пустой!\n");
        return 0;
    }

    shuffle(people, count);

    fout = fopen("outputname.txt", "w");
    if (!fout) {
        perror("Ошибка создания outputname.txt");
        return 1;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char datetime[64];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", t);

    fprintf(fout, "Список сгенерирован: %s\n\n", datetime);
    for (int i = 0; i < count; i++)
        fprintf(fout, "%d. %s\n", i + 1, people[i]);

    fclose(fout);
    printf("✅ Список успешно сгенерирован и сохранён в outputname.txt\n");
    return 0;
}