#include <stdio.h>
#include <stdlib.h>

// Функция для копирования строки из source в destination (аналог strcpy, но без string.h)
void str_copy(char *destination, const char *source)
{
    while (*source) // пока не достигнут конец строки
    {
        *destination = *source; // копируем символ
        destination++;
        source++;
    }
    *destination = '\0'; // ставим завершающий нулевой символ
}

int main(void)
{
    // Файлы ввода и вывода
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int requestCount; // Общее количество запросов
    fscanf(input, "%d", &requestCount); // Читаем количество запросов из файла

    // Массив указателей на строки, каждая строка хранится отдельно в динамической памяти
    char **stringStorage = (char **)calloc(requestCount, sizeof(char *));

    // Переменные для обработки запросов
    int requestType;     // Тип запроса (0 - создать, 1 - удалить, 2 - вывести, 3 - посчитать символ)
    int stringLength;    // Длина создаваемой строки
    int stringId;        // Идентификатор строки (номер запроса, при котором она была создана)
    char inputBuffer[100005]; // Буфер для временного хранения вводимой строки
    int createdCount = 0;     // Количество созданных строк (их идентификаторы идут от 0)
    int index;           // Индекс цикла для перебора запросов
    char currentChar;    // Символ, количество вхождений которого нужно посчитать
    char *currentPtr;    // Указатель для прохода по символам строки
    int charCount;       // Счётчик вхождений символа

    // Основной цикл обработки запросов
    for (index = 0; index < requestCount; index++)
    {
        fscanf(input, "%d", &requestType); // Читаем тип запроса

        // 0 — создание новой строки
        if (requestType == 0)
        {
            fscanf(input, "%d %s", &stringLength, inputBuffer); // Читаем длину и саму строку

            // Выделяем память под строку
            char *newString = (char *)malloc((stringLength + 1) * sizeof(char));

            // Копируем строку в выделенный участок памяти
            str_copy(newString, inputBuffer);

            // Сохраняем указатель в массиве (идентификатор = порядковый номер создания)
            stringStorage[createdCount++] = newString;
        }

        // 1 — удаление ранее созданной строки
        else if (requestType == 1)
        {
            fscanf(input, "%d", &stringId); // Считываем идентификатор строки для удаления

            if (stringStorage[stringId]) // Проверяем, что строка существует
            {
                free(stringStorage[stringId]); // Освобождаем память
                stringStorage[stringId] = NULL; // Помечаем как удалённую
            }
        }

        // 2 — вывод содержимого строки
        else if (requestType == 2)
        {
            fscanf(input, "%d", &stringId); // Читаем идентификатор строки

            if (stringStorage[stringId]) // Проверяем, что строка существует
            {
                fprintf(output, "%s\n", stringStorage[stringId]); // Печатаем в файл вывода
            }
        }

        // 3 — подсчёт количества вхождений символа в строке
        else if (requestType == 3)
        {
            fscanf(input, "%d %c", &stringId, &currentChar); // Считываем ID и символ

            charCount = 0; // Обнуляем счётчик
            if (stringStorage[stringId]) // Проверяем, что строка существует
            {
                currentPtr = stringStorage[stringId]; // Начинаем обход строки
                while (*currentPtr)
                {
                    if (*currentPtr == currentChar)
                    {
                        charCount++; // Если символ совпал — увеличиваем счётчик
                    }
                    currentPtr++; // Переходим к следующему символу
                }
            }
            fprintf(output, "%d\n", charCount); // Выводим результат
        }
    }

    // В конце программы — освобождаем память всех оставшихся строк
    for (index = 0; index < createdCount; index++)
    {
        if (stringStorage[index])
        {
            free(stringStorage[index]);
        }
    }

    // Освобождаем массив указателей
    free(stringStorage);

    // Закрываем файлы
    fclose(input);
    fclose(output);

    return 0;
}