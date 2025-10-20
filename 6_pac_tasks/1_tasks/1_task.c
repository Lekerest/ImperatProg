#include <stdio.h>

// функция определения порядка байт в системе
int is_little_endian(void)
{
    unsigned short test = 0x1;
    // Пример: 0x0001
	// Little-endian: 01 00
	// Big-endian: 00 01
    return *((unsigned char *)&test) == 0x1;
    // 1 le 0 be
}

// функция перестановки байт
unsigned int swap_endian(unsigned int x)
{
    return ((x >> 24) & 0x000000FF) |
           ((x >> 8)  & 0x0000FF00) |
           ((x << 8)  & 0x00FF0000) |
           ((x << 24) & 0xFF000000);
}

int main(void)
{
    FILE *input = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "wb");

    unsigned int N;
    fread(&N, 4, 1, input);

    unsigned int N_swapped = swap_endian(N);
    int file_little_endian;

    if (N >= 1 && N <= 10000)
    {
        file_little_endian = is_little_endian();
    }
    else
    {
        N = N_swapped;
        file_little_endian = !is_little_endian();
    }

    int sum = 0;

    for (unsigned int i = 0; i < N; i++)
    {
        int num;
        fread(&num, 4, 1, input);

        if (file_little_endian != is_little_endian())
        {
            num = (int)swap_endian((unsigned int)num);
        }

        sum += num;
    }

    unsigned int result = (unsigned int)sum;

    if (file_little_endian != is_little_endian())
    {
        result = swap_endian(result);
    }

    fwrite(&result, 4, 1, output);
    // ptr - Указатель на область памяти, откуда берутся данные для записи
    // size - Размер одного элемента (в байтах)
    // count - Количество таких элементов
    // stream - Указатель на файловый поток (открытый через fopen)

    fclose(input);
    fclose(output);

    return 0;
}