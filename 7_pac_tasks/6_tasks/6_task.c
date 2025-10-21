#include <stdio.h>
#include <stdlib.h>

/* ====== Узел двусвязного кольцевого списка со вспомогательной головой ====== */
typedef struct Node
{
    struct Node *prev;
    struct Node *next;
    double value;
} Node;

/* Вспомогательная функция: получить указатель на Node по адресу поля value */
static Node *ptr2node(double *p)
{
    Node tmp;
    unsigned long off = (unsigned long)((char *)&tmp.value - (char *)&tmp);
    return (Node *)((char *)p - off);
}

/* Создать пустой список, вернуть указатель на value головы */
double *initList(void)
{
    Node *head = (Node *)malloc(sizeof(Node));
    if (head == NULL)
    {
        return NULL;
    }
    head->next = head;
    head->prev = head;
    head->value = 0.0;
    return &head->value;
}

/* Полностью освободить список */
void freeList(double *head_val)
{
    if (head_val == NULL)
    {
        return;
    }
    Node *head = ptr2node(head_val);
    Node *cur = head->next;
    while (cur != head)
    {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    free(head);
}

/* Вставка после where */
double *addAfter(double *where_val, double val)
{
    Node *w = ptr2node(where_val);
    Node *nd = (Node *)malloc(sizeof(Node));
    if (nd == NULL)
    {
        return NULL;
    }
    nd->value = val;
    nd->next = w->next;
    nd->prev = w;
    w->next->prev = nd;
    w->next = nd;
    return &nd->value;
}

/* Вставка перед where */
double *addBefore(double *where_val, double val)
{
    Node *w = ptr2node(where_val);
    Node *nd = (Node *)malloc(sizeof(Node));
    if (nd == NULL)
    {
        return NULL;
    }
    nd->value = val;
    nd->prev = w->prev;
    nd->next = w;
    w->prev->next = nd;
    w->prev = nd;
    return &nd->value;
}

/* Удалить узел */
void erase(double *what_val)
{
    Node *n = ptr2node(what_val);
    n->prev->next = n->next;
    n->next->prev = n->prev;
    free(n);
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        if (input)
        {
            fclose(input);
        }
        if (output)
        {
            fclose(output);
        }
        return 0;
    }

    int T;
    if (fscanf(input, "%d", &T) != 1)
    {
        fclose(input);
        fclose(output);
        return 0;
    }

    for (int t = 0; t < T; t++)
    {
        int Q;
        fscanf(input, "%d", &Q);

        double *head = initList();
        if (head == NULL)
        {
            fclose(input);
            fclose(output);
            return 0;
        }

        double **vals = (double **)malloc(Q * sizeof(double *));
        if (vals == NULL)
        {
            freeList(head);
            fclose(input);
            fclose(output);
            return 0;
        }

        int created = 0;

        for (int i = 0; i < Q; i++)
        {
            int type;
            fscanf(input, "%d", &type);

            if (type == 1)
            {
                /* добавить ПЕРЕД idx (если idx=-1, в начало) */
                int idx;
                double v;
                fscanf(input, "%d %lf", &idx, &v);
                double *p;
                if (idx == -1)
                {
                    p = addAfter(head, v);
                }
                else
                {
                    p = addBefore(vals[idx], v);
                }
                vals[created++] = p;
            }
            else if (type == -1)
            {
                /* добавить ПОСЛЕ idx (если idx=-1, в конец) */
                int idx;
                double v;
                fscanf(input, "%d %lf", &idx, &v);
                double *p;
                if (idx == -1)
                {
                    p = addBefore(head, v);
                }
                else
                {
                    p = addAfter(vals[idx], v);
                }
                vals[created++] = p;
            }
            else if (type == 0)
            {
                /* удалить элемент по индексу */
                int idx;
                fscanf(input, "%d", &idx);
                double *p = vals[idx];
                fprintf(output, "%0.3lf\n", *p);
                erase(p);
            }
        }

        fprintf(output, "===\n");

        Node *H = ptr2node(head);
        Node *cur = H->next;
        while (cur != H)
        {
            fprintf(output, "%0.3lf\n", cur->value);
            cur = cur->next;
        }
        fprintf(output, "===\n");

        free(vals);
        freeList(head);
    }

    fclose(input);
    fclose(output);
    return 0;
}