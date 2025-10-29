#include <stdio.h>
#include <stdlib.h>

// Функция построения массива LPS (Longest Prefix Suffix)
// Используется в алгоритме Кнута-Морриса-Пратта для ускорения поиска подстроки
void build_lps(const char *pattern, int *lps, int patternLength)
{
    int length = 0;    // длина текущего совпавшего префикса
    int index = 1;     // позиция в шаблоне

    lps[0] = 0;        // первый элемент массива LPS всегда 0

    // цикл по шаблону для вычисления LPS-массива
    while (index < patternLength)
    {
        if (pattern[index] == pattern[length])
        {
            length++;                // увеличиваем длину совпавшего префикса
            lps[index] = length;     // сохраняем значение
            index++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1]; // откатываемся по ранее найденным совпадениям
            }
            else
            {
                lps[index] = 0;      // совпадений нет, значение = 0
                index++;
            }
        }
    }
}

// Потоковая реализация КМП без фиксированного размера буфера
// Последовательность читается блоками, что позволяет работать с очень большими файлами
long long kmp_stream(FILE *input, long long totalLength, const char *pattern, int patternLength)
{
    int *lps = (int *)malloc(patternLength * sizeof(int)); // массив LPS
    build_lps(pattern, lps, patternLength);

    // Вычисляем динамический размер буфера:
    // Если файл очень большой — выделяем 1 МБ
    // Если файл небольшой — выделяем 1% от его длины (но не меньше 1 байта)
    size_t bufferSize;

    if (totalLength / 100 > 1024 * 1024)
    {
        bufferSize = 1024 * 1024;       // буфер 1 МБ
    }
    else
    {
        bufferSize = totalLength / 100 + 1;   // 1% от размера файла
    }

    char *buffer = (char *)malloc(bufferSize); // буфер для чтения

    // Рабочие переменные
    long long matchCount = 0;  // общее количество найденных повторов шаблона
    long long processed = 0;   // количество обработанных символов
    int currentState = 0;      // текущая позиция в шаблоне (состояние автомата)
    int symbol;                // текущий символ из файла
    size_t bytesRead;          // сколько байт прочитано за раз
    size_t i;                  // индекс для прохода по буферу

    // Основной цикл чтения и обработки файла блоками
    while (processed < totalLength)
    {
        // Определяем, сколько байт читаем в этот раз
        size_t toRead;

        // Вычисляем, сколько байт осталось обработать
        if (totalLength - processed > bufferSize)
        {
            // Если осталось больше, чем размер буфера — читаем полный буфер
            toRead = bufferSize;
        }
        else
        {
            // Если осталось меньше — читаем только остаток
            toRead = (size_t)(totalLength - processed);
        }
        bytesRead = fread(buffer, 1, toRead, input);
        if (bytesRead == 0)
        {
            break; // достигнут конец файла
        }

        // Проходим по всем символам буфера
        for (i = 0; i < bytesRead; i++)
        {
            symbol = buffer[i];

            // Пропускаем все невалидные символы
            if (!(symbol == 'A' || symbol == 'C' || symbol == 'G' || symbol == 'U' || symbol == 'T' ||
                  symbol == 'a' || symbol == 'c' || symbol == 'g' || symbol == 'u' || symbol == 't'))
            {
                continue;
            }

            // Приводим символ к верхнему регистру
            if (symbol >= 'a' && symbol <= 'z')
            {
                symbol -= 32;
            }

            // Шаг алгоритма КМП
            while (currentState > 0 && pattern[currentState] != symbol)
            {
                currentState = lps[currentState - 1];
            }

            if (pattern[currentState] == symbol)
            {
                currentState++;
            }

            // Если найдено полное совпадение шаблона "GGGGCC"
            if (currentState == patternLength)
            {
                matchCount++; // увеличиваем счётчик повторов

                // Если найдено больше 30 повторов — патология
                if (matchCount > 30)
                {
                    free(buffer);
                    free(lps);
                    return matchCount;
                }

                // продолжаем поиск с учётом перекрытий
                currentState = lps[currentState - 1];
            }

            processed++; // обновляем количество обработанных символов
        }
    }

    free(buffer);
    free(lps);
    return matchCount; // возвращаем общее число повторов
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");   // файл с последовательностью РНК
    FILE *output = fopen("output.txt", "w"); // файл для вывода результата

    long long sequenceLength; // длина последовательности
    fscanf(input, "%lld", &sequenceLength);

    fgetc(input); // пропускаем перевод строки после числа длины

    const char pattern[] = {'G', 'G', 'G', 'G', 'C', 'C'}; // искомый шаблон GGGGCC
    int patternLength = 6;                                 // длина шаблона

    // Запуск алгоритма КМП на потоке ввода
    long long totalMatches = kmp_stream(input, sequenceLength, pattern, patternLength);

    // Вывод результата в зависимости от количества найденных повторов
    if (totalMatches > 30)
    {
        fprintf(output, "Pathogenic\n");
    }
    else
    {
        fprintf(output, "Non-pathogenic\n");
    }

    fclose(input);
    fclose(output);

    return 0;
}