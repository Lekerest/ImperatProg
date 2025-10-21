#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1000005  // максимальная длина входной строки

typedef struct Tokens_s
{
    int num;     // количество слов
    char **arr;  // массив указателей на слова
} Tokens;

// латинская буква?
int is_letter(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return 1;
    }
    if (ch >= 'a' && ch <= 'z')
    {
        return 1;
    }
    return 0;
}

// по ТЗ: сигнатуры сохраняем, но фактически считаем разделителем "не букву"
void tokensSplit(Tokens *tokens, const char *str, const char *delims)
{
    int i = 0;
    int in_word = 0;
    int count = 0;

    if (tokens->arr == NULL)
    {
        // первый проход: только считаем слова
        while (str[i] != '\0')
        {
            char ch = str[i];

            if (is_letter(ch))
            {
                if (!in_word)
                {
                    count++;
                    in_word = 1;
                }
            }
            else
            {
                in_word = 0;
            }

            i++;
        }

        tokens->num = count;
    }
    else
    {
        // второй проход: выделяем и заполняем
        tokens->num = 0;
        i = 0;
        in_word = 0;

        while (str[i] != '\0')
        {
            if (is_letter(str[i]))
            {
                if (!in_word)
                {
                    int start = i;
                    int len = 0;

                    // идём по слову
                    while (str[i] != '\0' && is_letter(str[i]))
                    {
                        i++;
                        len++;
                    }

                    // выделяем память под слово
                    char *w = (char *)malloc((len + 1) * sizeof(char));
                    if (w == NULL)
                    {
                        return; // при OOM просто выходим (по ТЗ поведение не регламентировано)
                    }

                    // копируем
                    {
                        int k;
                        for (k = 0; k < len; k++)
                        {
                            w[k] = str[start + k];
                        }
                        w[len] = '\0';
                    }

                    tokens->arr[tokens->num] = w;
                    tokens->num = tokens->num + 1;

                    in_word = 0;
                    continue; // i уже на первом разделителе после слова
                }
            }
            else
            {
                in_word = 0;
            }

            i++;
        }
    }
}

// корректное освобождение (можно вызывать повторно)
void tokensFree(Tokens *tokens)
{
    if (tokens->arr != NULL)
    {
        int i;
        for (i = 0; i < tokens->num; i++)
        {
            if (tokens->arr[i] != NULL)
            {
                free(tokens->arr[i]);
                tokens->arr[i] = NULL;
            }
        }
        free(tokens->arr);
        tokens->arr = NULL;
    }
    tokens->num = 0;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // читаем всё до EOF
    static char s[MAX_LEN];
    int n = 0;
    int c;

    while ((c = fgetc(input)) != EOF)
    {
        if (n + 1 < MAX_LEN)
        {
            s[n++] = (char)c;
        }
        else
        {
            break;
        }
    }
    s[n] = '\0';

    // delims по ТЗ передаётся, но мы разбиваем "как простая версия": не буква => разделитель
    const char *delims = ""; // не используется в логике, сигнатура сохранена

    Tokens tokens;
    tokens.num = 0;
    tokens.arr = NULL;

    // первый проход: посчитать слова
    tokensSplit(&tokens, s, delims);

    // выделить массив указателей ровно на num
    if (tokens.num > 0)
    {
        tokens.arr = (char **)malloc((size_t)tokens.num * sizeof(char *));
        if (tokens.arr == NULL)
        {
            fprintf(output, "0\n");
            fclose(input);
            fclose(output);
            return 0;
        }
    }
    else
    {
        tokens.arr = NULL;
    }

    // второй проход: наполнить массив словами
    tokensSplit(&tokens, s, delims);

    // вывод
    fprintf(output, "%d\n", tokens.num);
    if (tokens.arr != NULL)
    {
        int i;
        for (i = 0; i < tokens.num; i++)
        {
            fprintf(output, "%s\n", tokens.arr[i]);
        }
    }

    tokensFree(&tokens);
    tokensFree(&tokens);

    fclose(input);
    fclose(output);
    return 0;
}