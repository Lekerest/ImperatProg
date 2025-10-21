#include <stdio.h>

#define MAX 1024

// Функция чтения 4-байтового числа в формате Little-endian
unsigned int read_le32(unsigned char *p)
{
    return ((unsigned int)p[0]) |
           ((unsigned int)p[1] << 8) |
           ((unsigned int)p[2] << 16) |
           ((unsigned int)p[3] << 24);
}

// Функция чтения 8-байтового числа в формате Little-endian
unsigned long long read_le64(unsigned char *p)
{
    return ((unsigned long long)p[0]) |
           ((unsigned long long)p[1] << 8) |
           ((unsigned long long)p[2] << 16) |
           ((unsigned long long)p[3] << 24) |
           ((unsigned long long)p[4] << 32) |
           ((unsigned long long)p[5] << 40) |
           ((unsigned long long)p[6] << 48) |
           ((unsigned long long)p[7] << 56);
}

// Функция чтения double (8 байт в little-endian)
double read_double(unsigned char *p)
{
    union
    {
        unsigned char b[8];
        double d;
    } u;

    int i;
    for (i = 0; i < 8; i++)
    {
        u.b[i] = p[i];
    }

    return u.d;
}

int main(void)
{
    FILE *input = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output)
    {
        return 0;
    }

    unsigned char buf[MAX];
    int n = fread(buf, 1, MAX, input);
    fclose(input);

    int pos = 0;

    // Читаем размер документа (int32)
    int size = (int)read_le32(buf);
    pos += 4;

    fprintf(output, "{\n");

    int first = 1;

    // Основной цикл по полям
    while (pos < size - 1)
    {
        unsigned char type = buf[pos++];
        if (type == 0)
        {
            break;
        }

        // Читаем имя поля
        char name[128];
        int ni = 0;
        while (buf[pos] != 0)
        {
            name[ni++] = buf[pos++];
        }
        name[ni] = 0;
        pos++; // пропустить завершающий нулевой байт

        if (!first)
        {
            fprintf(output, ",\n");
        }
        first = 0;

        // добавлен отступ 4 пробела
        fprintf(output, "    \"%s\": ", name);

        // Чтение значения в зависимости от типа
        if (type == 1)
        {
            double val = read_double(buf + pos);
            pos += 8;
            fprintf(output, "%0.15g", val);
        }
        else if (type == 2)
        {
            int L = (int)read_le32(buf + pos);
            pos += 4;

            fprintf(output, "\"");
            int i;
            for (i = 0; i < L - 1; i++)
            {
                fprintf(output, "%c", buf[pos++]);
            }
            fprintf(output, "\"");

            pos++; // пропустить завершающий 0 байт
        }
        else if (type == 8)
        {
            unsigned char b = buf[pos++];
            if (b)
            {
                fprintf(output, "true");
            }
            else
            {
                fprintf(output, "false");
            }
        }
        else if (type == 10)
        {
            fprintf(output, "null");
        }
        else if (type == 16)
        {
            int v = (int)read_le32(buf + pos);
            pos += 4;
            fprintf(output, "%d", v);
        }
        else if (type == 18)
        {
            long long v = (long long)read_le64(buf + pos);
            pos += 8;
            fprintf(output, "%lld", v);
        }
    }

    fprintf(output, "\n}");

    fclose(output);
    return 0;
}