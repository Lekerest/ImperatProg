#include <stdio.h>

#define RECORD_SIZE 47
#define NAME_SIZE 21
#define MAX_FILES 1000

// Функция чтения 4-байтового числа в формате Little-endian
unsigned int read_le32(unsigned char *p)
{
    return ((unsigned int)p[0]) |
           ((unsigned int)p[1] << 8) |
           ((unsigned int)p[2] << 16) |
           ((unsigned int)p[3] << 24);
}

// Функция чтения 8-байтового числа в формате Little-endian
unsigned long long read_le64(unsigned char *p)
{
    return ((unsigned long long)p[0]) |
           ((unsigned long long)p[1] << 8) |
           ((unsigned long long)p[2] << 16) |
           ((unsigned long long)p[3] << 24) |
           ((unsigned long long)p[4] << 32) |
           ((unsigned long long)p[5] << 40) |
           ((unsigned long long)p[6] << 48) |
           ((unsigned long long)p[7] << 56);
}

// Функция сравнения имён файлов по ASCII
int compare_names(char *a, char *b)
{
    int i = 0;
    while (a[i] && b[i] && a[i] == b[i])
        i++;
    return (unsigned char)a[i] - (unsigned char)b[i];
}

// Структура файла
struct FileInfo
{
    char name[NAME_SIZE + 1];       // имя (строка)
    unsigned char raw[RECORD_SIZE]; // исходные 47 байт для вывода
};

int main(void)
{
    FILE *input = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "wb");

    if (!input || !output)
        return 0;

    unsigned char header[20];
    fread(header, 1, 20, input);

    unsigned int N = read_le32(header);
    unsigned long long A = read_le64(header + 4);
    unsigned long long B = read_le64(header + 12);

    struct FileInfo files[MAX_FILES];
    int count = 0;

    // Чтение N файлов
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned char rec[RECORD_SIZE];
        fread(rec, 1, RECORD_SIZE, input);

        unsigned char is_dir = rec[29];
        unsigned char hidden = rec[46];
        unsigned long long C = read_le64(rec + 30);
        unsigned long long M = read_le64(rec + 38);

        // Проверка условий:
        // не директория, не скрытый, создан не раньше A, изменён не позже B
        if (is_dir == 0 && hidden == 0 && C >= A && M <= B)
        {
            int j;
            for (j = 0; j < NAME_SIZE && rec[j]; j++)
                files[count].name[j] = rec[j];
            files[count].name[j] = 0;

            for (j = 0; j < RECORD_SIZE; j++)
                files[count].raw[j] = rec[j];

            count++;
        }
    }

    // Пузырьковая сортировка по имени
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (compare_names(files[i].name, files[j].name) > 0)
            {
                struct FileInfo temp = files[i];
                files[i] = files[j];
                files[j] = temp;
            }
        }
    }

    // Выводим только отобранные и отсортированные записи
    for (int i = 0; i < count; i++)
    {
        fwrite(files[i].raw, 1, RECORD_SIZE, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}