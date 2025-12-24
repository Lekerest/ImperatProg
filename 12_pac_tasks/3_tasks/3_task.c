#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int value;                 // ключ (значение) узла: по нему работает BST-свойство
    unsigned int priority;     // приоритет узла: по нему работает heap-свойство (меньше -> выше)
    struct Node *left;         // левое поддерево (все значения меньше value)
    struct Node *right;        // правое поддерево (все значения больше value)
} Node;


/*
    ---------- ГЕНЕРАЦИЯ ПСЕВДОСЛУЧАЙНОГО PRIORITY ----------
    Линейный конгруэнтный генератор (LCG):
    state = state * A + B
    Возвращаем новое состояние как "случайное" число.

    Для treap важно, чтобы priority:
    - не зависел от value
    - выглядел случайным, чтобы дерево не вырождалось
*/
static unsigned int next_random(unsigned int *state)
{
    *state = (*state) * 1103515245u + 12345u;
    return *state;
}


/*
    ---------- СОЗДАНИЕ УЗЛА ----------
    Выделяем память под Node, заполняем value и priority,
    детей делаем NULL.
*/
static Node *create_node(int value, unsigned int priority)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->value = value;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;

    return node;
}


/*
    ---------- ПРОВЕРКА НАЛИЧИЯ VALUE В ДЕРЕВЕ ----------
    Это обычный поиск в BST по полю value:
    - если value меньше -> идём влево
    - если value больше -> идём вправо
    - если равно -> найдено
*/
static int contains(Node *root, int value)
{
    while (root != NULL)
    {
        if (value < root->value)
        {
            root = root->left;
        }
        else if (value > root->value)
        {
            root = root->right;
        }
        else
        {
            return 1;
        }
    }

    return 0;
}


/*
    ---------- SPLIT ----------
    split(root, value, &L, &R) разделяет treap на два treap-а:

    L: все узлы с key (value узла) < value
    R: все узлы с key (value узла) >= value

    Важно: split НЕ создаёт новые узлы.
    Он только "перешивает" указатели left/right так, чтобы получились два корректных treap-а.
*/
static void split(Node *root, int value, Node **left_part, Node **right_part)
{
    if (root == NULL)
    {
        *left_part = NULL;
        *right_part = NULL;
        return;
    }

    // Если текущий узел точно уходит в левую часть (root->value < value),
    // то делим его правое поддерево: там могут быть и < value, и >= value.
    if (root->value < value)
    {
        split(root->right, value, &root->right, right_part);
        *left_part = root;
        return;
    }

    // Иначе root->value >= value: узел идёт в правую часть,
    // а делить нужно левое поддерево.
    split(root->left, value, left_part, &root->left);
    *right_part = root;
}


/*
    ---------- MERGE ----------
    merge(L, R) склеивает два treap-а в один, при условии:
    все ключи в L < все ключи в R.

    Корень выбирается по priority:
    - меньший priority должен быть выше (min-heap по priority)
*/
static Node *merge(Node *left_part, Node *right_part)
{
    if (left_part == NULL)
    {
        return right_part;
    }

    if (right_part == NULL)
    {
        return left_part;
    }

    // Если левый корень имеет меньший priority, он становится корнем результата,
    // а правую часть нужно приклеить в его right поддерево.
    if (left_part->priority < right_part->priority)
    {
        left_part->right = merge(left_part->right, right_part);
        return left_part;
    }

    // Иначе правый корень становится корнем результата,
    // а левую часть нужно приклеить в его left поддерево.
    right_part->left = merge(left_part, right_part->left);
    return right_part;
}


/*
    ---------- ВСТАВКА УЗЛА ----------
    Вставляем node (уже созданный узел) в treap root:

    1) split(root, node->value) -> L (< value), R (>= value)
    2) merge(L, node) -> добавляем node в конец "левой области"
    3) merge(result, R) -> склеиваем обратно

    Здесь предполагается, что дубликатов нет (в main это проверяется contains()).
*/
static Node *insert_node(Node *root, Node *node)
{
    Node *left_part;
    Node *right_part;

    split(root, node->value, &left_part, &right_part);

    left_part = merge(left_part, node);
    return merge(left_part, right_part);
}


/*
    ---------- УДАЛЕНИЕ ЗНАЧЕНИЯ ----------
    Идея удаления через 2 split:

    1) split(root, value)       -> L (< value), R (>= value)
    2) split(R, value + 1)      -> M (< value+1, но >= value) и R2 (>= value+1)
       То есть M содержит узлы со значением ровно value (если они есть).

    3) Если M не пусто, удаляем корень M и склеиваем его детей merge(M->left, M->right)
    4) Склеиваем обратно: merge(L, M) затем merge(result, R2)
*/
static Node *erase_value(Node *root, int value)
{
    Node *left_part;
    Node *middle_part;
    Node *right_part;

    split(root, value, &left_part, &right_part);
    split(right_part, value + 1, &middle_part, &right_part);

    // middle_part либо NULL (значения не было), либо содержит ровно value
    if (middle_part != NULL)
    {
        Node *new_middle = merge(middle_part->left, middle_part->right);
        free(middle_part);
        middle_part = new_middle;
    }

    root = merge(left_part, middle_part);
    root = merge(root, right_part);

    return root;
}


/*
    ---------- LOWER_BOUND ----------
    Находим минимальное значение >= value.
    Это чистый BST-поиск по value (priority не участвует):

    Если root->value >= value:
      - root->value кандидат в ответ
      - но может быть лучше (меньше) слева -> идём влево

    Если root->value < value:
      - ответ должен быть больше -> идём вправо
*/
static int lower_bound(Node *root, int value, int *result)
{
    int found = 0;

    while (root != NULL)
    {
        if (root->value >= value)
        {
            *result = root->value;
            found = 1;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return found;
}


/*
    ---------- ОСВОБОЖДЕНИЕ ПАМЯТИ ----------
    Рекурсивно удаляем дерево (postorder):
    сначала дети, потом текущий узел.
*/
static void free_tree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}


int main(void)
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    // Считываем количество операций
    int operations_count;
    fscanf(input_file, "%d", &operations_count);

    Node *root = NULL;

    // Начальное состояние генератора priority (seed)
    unsigned int random_state = 123456789u;

    // Обрабатываем операции по одной (online)
    for (int i = 0; i < operations_count; i++)
    {
        char operation[16];
        int value;

        // Считываем строку операции и число
        fscanf(input_file, "%15s %d", operation, &value);

        // add value: добавить, если нет; иначе dupe
        if (strcmp(operation, "add") == 0)
        {
            if (contains(root, value))
            {
                fprintf(output_file, "dupe\n");
            }
            else
            {
                Node *node = create_node(value, next_random(&random_state));
                root = insert_node(root, node);
                fprintf(output_file, "added\n");
            }
        }
        // remove value: удалить, если есть; иначе miss
        else if (strcmp(operation, "remove") == 0)
        {
            if (contains(root, value))
            {
                root = erase_value(root, value);
                fprintf(output_file, "removed\n");
            }
            else
            {
                fprintf(output_file, "miss\n");
            }
        }
        // lower value: минимальный элемент >= value, иначе ###
        else
        {
            int answer;

            if (lower_bound(root, value, &answer))
            {
                fprintf(output_file, "%d\n", answer);
            }
            else
            {
                fprintf(output_file, "###\n");
            }
        }
    }

    // Освобождаем все узлы treap
    free_tree(root);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
