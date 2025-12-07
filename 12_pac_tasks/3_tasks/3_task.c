#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int value;
    unsigned int priority;
    struct Node *left;
    struct Node *right;
} Node;

static unsigned int next_random(unsigned int *state)
{
    *state = (*state) * 1103515245u + 12345u;
    return *state;
}

static Node *create_node(int value, unsigned int priority)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->value = value;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;

    return node;
}

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

static void split(Node *root, int value, Node **left_part, Node **right_part)
{
    if (root == NULL)
    {
        *left_part = NULL;
        *right_part = NULL;
        return;
    }

    if (root->value < value)
    {
        split(root->right, value, &root->right, right_part);
        *left_part = root;
        return;
    }

    split(root->left, value, left_part, &root->left);
    *right_part = root;
}

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

    if (left_part->priority < right_part->priority)
    {
        left_part->right = merge(left_part->right, right_part);
        return left_part;
    }

    right_part->left = merge(left_part, right_part->left);
    return right_part;
}

static Node *insert_node(Node *root, Node *node)
{
    Node *left_part;
    Node *right_part;

    split(root, node->value, &left_part, &right_part);

    left_part = merge(left_part, node);
    return merge(left_part, right_part);
}

static Node *erase_value(Node *root, int value)
{
    Node *left_part;
    Node *middle_part;
    Node *right_part;

    split(root, value, &left_part, &right_part);
    split(right_part, value + 1, &middle_part, &right_part);

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

    int operations_count;
    fscanf(input_file, "%d", &operations_count);

    Node *root = NULL;
    unsigned int random_state = 123456789u;

    for (int i = 0; i < operations_count; i++)
    {
        char operation[16];
        int value;

        fscanf(input_file, "%15s %d", operation, &value);

        if (strcmp(operation, "add") == 0)
        {
            if (contains(root, value))
            {
                fprintf(output_file, "dupe\n");
            }
            else
            {
                root = insert_node(root, create_node(value, next_random(&random_state)));
                fprintf(output_file, "added\n");
            }
        }
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

    free_tree(root);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
