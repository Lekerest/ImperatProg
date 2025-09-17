#include <stdio.h>

// Функция для проверки возможности размещения двух прямоугольников внутри третьего
int canPlace(int a_width, int a_height, int b_width, int b_height, int c_width, int c_height) {
    // Проверяем различные варианты размещения:
    
    // Вариант 1: оба прямоугольника размещены горизонтально рядом
    if (b_width + c_width <= a_width && b_height <= a_height && c_height <= a_height) 
    {
        return 1;
    }
    
    // Вариант 2: оба прямоугольника размещены вертикально друг на друге
    if (b_height + c_height <= a_height && b_width <= a_width && c_width <= a_width) 
    {
        return 1;
    }
    
    // Вариант 3: один горизонтально, другой вертикально - разные комбинации
    
    // B горизонтально, C вертикально справа
    if (b_width <= a_width && c_height <= a_height && 
        b_height <= a_height && c_width <= a_width - b_width) 
    {
        return 1;
    }
    
    // B горизонтально, C вертикально слева
    if (c_width <= a_width && b_height <= a_height && 
        c_height <= a_height && b_width <= a_width - c_width) 
    {
        return 1;
    }
    
    // B вертикально, C горизонтально сверху
    if (b_height <= a_height && c_width <= a_width && 
        b_width <= a_width && c_height <= a_height - b_height) 
    {
        return 1;
    }
    
    // B вертикально, C горизонтально снизу
    if (c_height <= a_height && b_width <= a_width && 
        c_width <= a_width && b_height <= a_height - c_height)
    {
        return 1;
    }
    
    return 0;
}

int main() 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }
    
    int a[2], b[2], c[2];

    // Считываем размеры прямоугольников
    fscanf(input, "%d %d %d %d %d %d", 
          &a[0], &a[1], 
          &b[0], &b[1], 
          &c[0], &c[1]);

    int result = 0;
    
    // Проверяем все возможные комбинации поворотов прямоугольников B и C
    // Каждый прямоугольник можно повернуть 2 способами (0° и 90°)
    // Всего 2 × 2 = 4 комбинации
    
    // Комбинация 1: B и C без поворота
    if (canPlace(a[0], a[1], b[0], b[1], c[0], c[1]) || 
        canPlace(a[1], a[0], b[0], b[1], c[0], c[1])) 
    {
        result = 1;
    }
    
    // Комбинация 2: B без поворота, C повернут
    if (!result && (canPlace(a[0], a[1], b[0], b[1], c[1], c[0]) || 
                   canPlace(a[1], a[0], b[0], b[1], c[1], c[0]))) 
    {
        result = 1;
    }
    
    // Комбинация 3: B повернут, C без поворота
    if (!result && (canPlace(a[0], a[1], b[1], b[0], c[0], c[1]) || 
                   canPlace(a[1], a[0], b[1], b[0], c[0], c[1]))) 
    {
        result = 1;
    }
    
    // Комбинация 4: B и C повернуты
    if (!result && (canPlace(a[0], a[1], b[1], b[0], c[1], c[0]) || 
                   canPlace(a[1], a[0], b[1], b[0], c[1], c[0]))) 
    {
        result = 1;
    }

    if (result) {
        fprintf(output, "YES");
    } else {
        fprintf(output, "NO");
    }

    fclose(input);
    fclose(output);
    return 0;
}