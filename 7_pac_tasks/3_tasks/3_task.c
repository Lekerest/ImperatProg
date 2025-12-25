#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ListNode
{
    char text[8];
    struct ListNode *next;
} ListNode;

ListNode *list_heads[1000001];

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // ---------- ЧТЕНИЕ КОЛИЧЕСТВА ЗАПИСЕЙ ----------
    // В первой строке входного файла записано N — сколько пар (key, string) будет дальше.
    int record_count;
    fscanf(input, "%d", &record_count);

    // ---------- ИНИЦИАЛИЗАЦИЯ МАССИВА ГОЛОВ СПИСКОВ ----------
    // list_heads[key] будет хранить указатель на первый узел списка для этого key.
    // Пока ничего не считали — все списки пустые, значит головы равны NULL.
    for (int i = 0; i <= 1000000; i++)
    {
        list_heads[i] = NULL;
    }

    // ---------- ЧТЕНИЕ ВХОДНЫХ ПАР И ДОБАВЛЕНИЕ В СПИСКИ ----------
    // Для каждой пары (key, string):
    // 1) создаём новый узел
    // 2) кладём строку в узел
    // 3) добавляем узел в конец списка list_heads[key]
    //
    // Почему "в конец":
    // чтобы сохранить порядок добавления строк для одинакового key.
    for (int i = 0; i < record_count; i++)
    {
        int key;
        char buffer[8];

        // Считываем одну запись: число key и строку (до 7 символов)
        fscanf(input, "%d %s", &key, buffer);

        // Создаём новый узел списка в динамической памяти
        ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));

        // Копируем строку в поле узла
        strcpy(new_node->text, buffer);

        // Новый узел пока последний, поэтому next = NULL
        new_node->next = NULL;

        // Если список для этого key пустой, новый узел становится головой
        if (list_heads[key] == NULL)
        {
            list_heads[key] = new_node;
        }
        else
        {
            // Иначе идём до последнего элемента списка
            ListNode *current = list_heads[key];

            while (current->next != NULL)
            {
                current = current->next;
            }

            // Прицепляем новый узел в конец
            current->next = new_node;
        }
    }



    // ---------- ВЫВОД РЕЗУЛЬТАТА В ПОРЯДКЕ КЛЮЧЕЙ ----------
    // Требуется вывести все записи так, чтобы сначала шли меньшие key, потом большие.
    // Для каждого key:
    // 1) берём голову списка list_heads[key]
    // 2) проходим по списку
    // 3) печатаем "key string" для каждого узла
    for (int key = 0; key <= 1000000; key++)
    {
        ListNode *current = list_heads[key];

        while (current != NULL)
        {
            fprintf(output, "%d %s\n", key, current->text);
            current = current->next;
        }
    }

    // ---------- ЗАВЕРШЕНИЕ РАБОТЫ С ФАЙЛАМИ ----------
    fclose(input);
    fclose(output);

    return 0;
}