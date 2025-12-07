#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

static Node *create_node(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->value = value;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static Node *insert_value(Node *root, int value)
{
    if (root == NULL)
    {
        return create_node(value);
    }

    if (value < root->value)
    {
        root->left = insert_value(root->left, value);
        return root;
    }

    if (value > root->value)
    {
        root->right = insert_value(root->right, value);
        return root;
    }

    root->count++;
    return root;
}

static void write_inorder(Node *root, FILE *output_file)
{
    if (root == NULL)
    {
        return;
    }

    write_inorder(root->left, output_file);

    for (int i = 0; i < root->count; i++)
    {
        fwrite(&root->value, sizeof(int), 1, output_file);
    }

    write_inorder(root->right, output_file);
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
    FILE *input_file = fopen("input.txt", "rb");
    FILE *output_file = fopen("output.txt", "wb");

    int count_numbers;
    fread(&count_numbers, sizeof(int), 1, input_file);

    Node *root = NULL;

    for (int i = 0; i < count_numbers; i++)
    {
        int value;
        fread(&value, sizeof(int), 1, input_file);

        root = insert_value(root, value);
    }

    write_inorder(root, output_file);

    free_tree(root);

    fclose(input_file);
    fclose(output_file);

    return 0;
}
