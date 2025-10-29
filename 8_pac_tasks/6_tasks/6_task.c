#include <stdio.h>
#include <stdlib.h>

// Структура узла списка
typedef struct Node
{
    int number;           // номер человека
    struct Node *next;    // ссылка на следующего
} Node;

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int totalPeople;  // количество людей N
    int step;         // шаг счёта K
    int index;        // счётчик для циклов
    int count;        // вспомогательная переменная для подсчёта шагов

    fscanf(input, "%d %d", &totalPeople, &step);

    // Создание циклического списка из N человек
    Node *head = NULL;       // начало списка
    Node *prev = NULL;       // предыдущий элемент
    Node *current = NULL;    // текущий элемент

    for (index = 1; index <= totalPeople; index++)
    {
        Node *person = (Node *)malloc(sizeof(Node));
        person->number = index;
        person->next = NULL;

        if (head == NULL)
        {
            head = person;   // первый элемент — голова списка
        }
        else
        {
            prev->next = person; // связываем предыдущего с текущим
        }

        prev = person;
    }

    // замыкаем список в кольцо
    prev->next = head;

    // Указатель на текущего человека (начинаем с первого)
    current = head;
    Node *previous = prev; // перед текущим (для удаления)

    // Пока не останется один человек
    for (index = 0; index < totalPeople; index++)
    {
        // Считаем K-1 шагов
        for (count = 1; count < step; count++)
        {
            previous = current;
            current = current->next;
        }

        // Печатаем номер выбывшего человека
        fprintf(output, "%d\n", current->number);

        // Удаляем текущего из круга
        previous->next = current->next;
        Node *temp = current;
        current = current->next;
        free(temp);

        // Если удалён последний — завершаем
        if (previous == current)
        {
            fprintf(output, "%d\n", current->number);
            free(current);
            break;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}