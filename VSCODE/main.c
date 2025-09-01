#include <stdio.h>
#include <math.h>
#include <windows.h>

// Функция: выводит приветственное сообщение
void PrintHello() {
    printf("Hello World\n");
}

// Функция: ввод двух чисел по отдельности, проверка и сумма
void CalculateSum() {
    int numberA, numberB;

    // Ввод A
    do {
        printf("Введите число A (>= 0): ");
        scanf("%d", &numberA);

        if (numberA < 0) {
            printf("Ошибка: A должно быть больше или равно 0\n");
        }
    } while (numberA < 0);

    // Ввод B
    do {
        printf("Введите число B (<= 100): ");
        scanf("%d", &numberB);

        if (numberB > 100) {
            printf("Ошибка: B должно быть меньше или равно 100\n");
        }
    } while (numberB > 100);

    int sum = numberA + numberB;
    printf("Сумма: %d\n", sum);
}

// Функция: ввод двух чисел сразу, проверка и операции
void CalculateOperationsMultiplicationRemainder() {
    int numberA, numberB;

    do {
        printf("Введите два числа A и B (A >= 0, B <= 100) через пробел: ");
        int inputResult = scanf("%d %d", &numberA, &numberB);

        if (inputResult != 2) {
            printf("Ошибка: нужно ввести два числа\n");

            // Очистка буфера
            while (getchar() != '\n');
            continue;
        }

        if (numberA < 0) {
            printf("Ошибка: A должно быть больше или равно 0\n");
        }
        if (numberB > 100) {
            printf("Ошибка: B должно быть меньше или равно 100\n");
        }
    } while (numberA < 0 || numberB > 100);

    int multiplication = numberA * numberB;
    printf("Произведение: %d\n", multiplication);

    int remainder = numberA % numberB;
    printf("Остаток от деления %d на %d: %d\n", numberA, numberB, remainder);
}

void CalculateOperationsDivisionAverage() {
    int numberA, numberB;

    do {
        printf("Введите два числа A и B (A >= 0, B <= 100) через пробел: ");
        int inputResult = scanf("%d %d", &numberA, &numberB);

        if (inputResult != 2) {
            printf("Ошибка: нужно ввести два числа\n");

            // Очистка буфера
            while (getchar() != '\n');
            continue;
        }

        if (numberA < 0) {
            printf("Ошибка: A должно быть больше или равно 0\n");
        }
        if (numberB > 100) {
            printf("Ошибка: B должно быть меньше или равно 100\n");
        }
    } while (numberA < 0 || numberB > 100);

    int division = numberA / numberB;
    printf("Деление: %d\n", division);

    float averageAB = (float)(numberA + numberB) / 2;
    printf("Среднее арифметическое %d c %d: %.2f\n", numberA, numberB, averageAB);
}

void SummaNaturalNumbers() 
{
    int numberA;
    int SummaNumbers = 0;
     
    do 
    {
        printf("Введите число A (A > 0): ");
        int inputResult = scanf("%d", &numberA);

        if (inputResult != 1) 
        {
            printf("Ошибка: нужно ввести одно число\n");

            // Очистка буфера
            while (getchar() != '\n');
            continue;
        }
        if (numberA <= 0) 
        {
            printf("Ошибка: A должно быть больше 0\n");
        }
    } while (numberA <= 0);

    for (int i = 1; i <= numberA; i++)
    {
        SummaNumbers += i;
    }
    printf("Сумма натуральных чисел последовательности 1 -> %d : %d\n", numberA, SummaNumbers);

}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    /*PrintHello();
    CalculateSum();
    CalculateOperationsMultiplicationRemainder();
    CalculateOperationsDivisionAverage();*/
    SummaNaturalNumbers();

    return 0;
}
