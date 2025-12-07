#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 131071

typedef struct ActorBiography
{
    char name[31];
    int birth_year;
    char country[11];
    struct ActorBiography *next;
} ActorBiography;

unsigned long compute_hash(const char *string)
{
    unsigned long hash_value = 0;

    while (*string)
    {
        hash_value = hash_value * 131 + (unsigned char)(*string);
        string++;
    }

    return hash_value % HASH_TABLE_SIZE;
}

int main(void)
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    int count_actor_biography;
    fscanf(input_file, "%d\n", &count_actor_biography);

    ActorBiography *hash_table[HASH_TABLE_SIZE] = {0};

    for (int i = 0; i < count_actor_biography; i++)
    {
        ActorBiography *new_record = (ActorBiography *)malloc(sizeof(ActorBiography));

        fscanf(input_file, "\"%30[^\"]\" %d \"%10[^\"]\"\n",
               new_record->name,
               &new_record->birth_year,
               new_record->country);

        unsigned long hash_index = compute_hash(new_record->name);

        new_record->next = hash_table[hash_index];
        hash_table[hash_index] = new_record;
    }

    int count_actor_in_movie;
    fscanf(input_file, "%d\n", &count_actor_in_movie);

    for (int i = 0; i < count_actor_in_movie; i++)
    {
        char actor_name[31];
        char movie_name[21];

        fscanf(input_file, "\"%30[^\"]\" \"%20[^\"]\"\n", actor_name, movie_name);

        unsigned long hash_index = compute_hash(actor_name);

        ActorBiography *current = hash_table[hash_index];

        while (current != NULL)
        {
            if (strcmp(current->name, actor_name) == 0)
            {
                fprintf(output_file, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                        current->name,
                        current->birth_year,
                        current->country,
                        actor_name,
                        movie_name);
            }

            current = current->next;
        }
    }

    fclose(input_file);
    fclose(output_file);

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        ActorBiography *current = hash_table[i];

        while (current != NULL)
        {
            ActorBiography *next_record = current->next;
            free(current);
            current = next_record;
        }
    }

    return 0;
}
