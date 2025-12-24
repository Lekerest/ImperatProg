#include <stdio.h>
#include <string.h>

char value[200001][8];
int nextv[200001];
int head;
int N;
int F;
int Q;

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    // ---------- ЧТЕНИЕ КОЛИЧЕСТВА ТЕСТОВ ----------
    // В первой строке файла задано T — сколько тестовых случаев нужно обработать.
    int test_count;
    fscanf(input, "%d", &test_count);

    // ---------- ОБРАБОТКА КАЖДОГО ТЕСТА ----------
    // Каждый тест содержит:
    // 1) N F Q
    // 2) N узлов (строка + next)
    // 3) Q операций (вставки и удаления)
    while (test_count > 0)
    {
        test_count = test_count - 1;

        // ---------- ЧТЕНИЕ ПАРАМЕТРОВ ТЕСТА ----------
        // N — количество существующих узлов (индексы 0..N-1)
        // F — индекс первого элемента списка (голова)
        // Q — количество операций
        fscanf(input, "%d %d %d", &N, &F, &Q);

        // Текущая голова списка
        head = F;

        // ---------- ЧТЕНИЕ ИСХОДНЫХ УЗЛОВ ----------
        // Для каждого узла i (0..N-1) читаем:
        // value[i] — строка узла
        // nextv[i] — индекс следующего узла или -1
        for (int i = 0; i < N; i++)
        {
            fscanf(input, "%s %d", value[i], &nextv[i]);
        }

        // ---------- ПОДГОТОВКА К ДОБАВЛЕНИЮ НОВЫХ УЗЛОВ ----------
        // Новые узлы должны получать индексы N, N+1, N+2, ...
        // Поэтому next_free_index хранит индекс первой свободной позиции.
        int next_free_index = N;

        // ---------- ОБРАБОТКА Q ОПЕРАЦИЙ ----------
        // Формат операции:
        // type idx
        //
        // type = 0: вставка нового узла
        //   если idx = -1: вставить в начало списка
        //   иначе: вставить после узла idx
        //   вывод: индекс нового узла
        //
        // type = 1: удалить узел
        //   если idx = -1: удалить первый узел
        //   иначе: удалить узел после idx
        //   вывод: строка удалённого узла
        for (int operation_index = 0; operation_index < Q; operation_index++)
        {
            int type;
            int idx;
            fscanf(input, "%d %d", &type, &idx);

            // ---------- ОПЕРАЦИЯ ВСТАВКИ ----------
            if (type == 0)
            {
                // Считываем строку нового узла
                char new_value[8];
                fscanf(input, "%s", new_value);

                // Создаём новый узел в массиве:
                // новый индекс = next_free_index
                int new_index = next_free_index;

                // Копируем строку в хранилище узла
                strcpy(value[new_index], new_value);

                // Сдвигаем next_free_index, чтобы следующий новый узел получил следующий индекс
                next_free_index = next_free_index + 1;

                // Вставка в начало списка
                if (idx == -1)
                {
                    // Новый узел начинает указывать на старую голову
                    nextv[new_index] = head;

                    // Голова списка теперь становится new_index
                    head = new_index;
                }
                else
                {
                    // Вставка после узла idx:
                    // 1) Новый узел указывает на того, на кого раньше указывал idx
                    nextv[new_index] = nextv[idx];

                    // 2) idx теперь указывает на новый узел
                    nextv[idx] = new_index;
                }

                // По условию при вставке печатаем индекс нового узла
                fprintf(output, "%d\n", new_index);
            }

            // ---------- ОПЕРАЦИЯ УДАЛЕНИЯ ----------
            else
            {
                int deleted_index;

                // Удаление первого узла
                if (idx == -1)
                {
                    // Удаляемый узел — это голова
                    deleted_index = head;

                    // Новая голова — следующий после удалённого
                    head = nextv[head];
                }
                else
                {
                    // Удаление узла после idx:
                    // deleted_index — это nextv[idx]
                    deleted_index = nextv[idx];

                    // Перешиваем указатель:
                    // idx начинает указывать на узел после удалённого
                    nextv[idx] = nextv[deleted_index];
                }

                // По условию при удалении печатаем строку удалённого узла
                fprintf(output, "%s\n", value[deleted_index]);
            }
        }

        // ---------- ВЫВОД ТЕКУЩЕГО СПИСКА ПОСЛЕ ВСЕХ ОПЕРАЦИЙ ----------
        // Печатаем разделитель, затем все строки в порядке цепочки, затем снова разделитель.
        fprintf(output, "===\n");

        int current_index = head;
        while (current_index != -1)
        {
            fprintf(output, "%s\n", value[current_index]);
            current_index = nextv[current_index];
        }

        fprintf(output, "===\n");
    }

    // ---------- ЗАВЕРШЕНИЕ РАБОТЫ С ФАЙЛАМИ ----------
    fclose(input);
    fclose(output);

    return 0;
}