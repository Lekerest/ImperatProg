#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>  // для установки кодировки консоли в UTF-8

#define MAX_PEOPLE 25
#define MAX_LEN 100

void shuffle(char arr[][MAX_LEN], int n) {
    srand((unsigned int)time(NULL)); // случайное перемешивание
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[MAX_LEN];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

int main() {
    FILE *fin, *fout;
    char people[MAX_PEOPLE][MAX_LEN];
    int count = 0;

    // переводим консоль в UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // читаем inputname.txt
    fin = fopen("inputname.txt", "r");
    if (fin == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть файл inputname.txt\n");
        return 1;
    }
    while (fgets(people[count], MAX_LEN, fin) != NULL && count < MAX_PEOPLE) {
        size_t len = strlen(people[count]);
        if (len > 0 && people[count][len - 1] == '\n') {
            people[count][len - 1] = '\0';
        }
        count++;
    }
    fclose(fin);

    // перемешиваем
    shuffle(people, count);

    // открываем outputname.txt
    fout = fopen("outputname.txt", "w");
    if (fout == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть файл outputname.txt\n");
        return 1;
    }

    // записываем дату генерации
    time_t now = time(NULL);
    fprintf(fout, "Список сгенерирован: %s\n", ctime(&now));

    // записываем нумерованный список (без лишнего \n в конце)
    for (int i = 0; i < count; i++) {
        fprintf(fout, "%d. %s\n", i + 1, people[i]);
    }

    // вручную добавляем пустую строку перед SHA-256
    fprintf(fout, "\n");
    fclose(fout);

    // вычисляем SHA-256 (результат добавляем в конец файла)
    system("sha256sum outputname.txt >> outputname.txt");

    printf("✅ Список успешно сгенерирован и сохранён в outputname.txt\n");
    return 0;
}
