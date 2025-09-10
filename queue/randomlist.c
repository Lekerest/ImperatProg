#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PEOPLE 25    // максимум строк
#define MAX_LEN 100      // максимум символов в строке

void shuffle(char arr[][MAX_LEN], int n) {
    srand((unsigned int)time(NULL));
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

    fin = fopen("inputname.txt", "r");
    if (fin == NULL) {
        perror("Ошибка открытия inputname.txt");
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

    shuffle(people, count);

    fout = fopen("outputname.txt", "w");
    if (fout == NULL) {
        perror("Ошибка открытия outputname.txt");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fout, "%d. %s\n", i + 1, people[i]);
    }
    fclose(fout);

    return 0;
}