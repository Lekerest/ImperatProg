#include <stdio.h>
#include <math.h>

// Функция: выводит приветственное сообщение
void PrintHello() {
    printf("Hello World!\n");
}

// Функция: ввод двух чисел по отдельности, проверка и сумма
void CalculateSum() {
    int numberA, numberB;

    // Ввод A
    do {
        printf("Введите число A (0 <= A <= 100): ");
        scanf("%d", &numberA);

        if (numberA < 0 || numberA > 100) {
            printf("Ошибка: A должно быть в пределах от 0 до 100\n");
        }
    } while (numberA < 0 || numberA > 100);

    // Ввод B
    do {
        printf("Введите число B (0 <= B <= 100): ");
        scanf("%d", &numberB);

        if (numberB < 0 || numberB > 100) {
            printf("Ошибка: B должно быть в пределах от 0 до 100\n");
        }
    } while (numberB < 0 || numberB > 100);

    int sum = numberA + numberB;
    printf("Сумма: %d\n", sum);
}

void CalculateOperationsMultiplicationRemainder() {
    int numberA, numberB;

    do {
        printf("Введите два числа A и B (0 <= A <= 100, 0 <= B <= 100) через пробел: ");
        int inputResult = scanf("%d %d", &numberA, &numberB);

        if (inputResult != 2) {
            printf("Ошибка: нужно ввести два числа\n");
            while (getchar() != '\n');
            continue;
        }

        if (numberA < 0 || numberA > 100) {
            printf("Ошибка: A должно быть в пределах от 0 до 100\n");
        }
        if (numberB < 0 || numberB > 100) {
            printf("Ошибка: B должно быть в пределах от 0 до 100\n");
        }
    } while (numberA < 0 || numberA > 100 || numberB < 0 || numberB > 100);

    int multiplication = numberA * numberB;
    printf("Произведение: %d\n", multiplication);

    if (numberB != 0) {
        int remainder = numberA % numberB;
        printf("Остаток от деления %d на %d: %d\n", numberA, numberB, remainder);
    } else {
        printf("Ошибка: деление на ноль невозможно\n");
    }
}

void CalculateOperationsDivisionAverage() {
    int numberA, numberB;

    do {
        printf("Введите два числа A и B (0 <= A <= 100, 0 <= B <= 100) через пробел: ");
        int inputResult = scanf("%d %d", &numberA, &numberB);

        if (inputResult != 2) {
            printf("Ошибка: нужно ввести два числа\n");
            while (getchar() != '\n');
            continue;
        }

        if (numberA < 0 || numberA > 100) {
            printf("Ошибка: A должно быть в пределах от 0 до 100\n");
        }
        if (numberB < 0 || numberB > 100) {
            printf("Ошибка: B должно быть в пределах от 0 до 100\n");
        }
    } while (numberA < 0 || numberA > 100 || numberB < 0 || numberB > 100);

    if (numberB != 0) {
        int division = numberA / numberB;
        printf("Деление: %d\n", division);
    } else {
        printf("Ошибка: деление на ноль невозможно\n");
    }

    float averageAB = (float)(numberA + numberB) / 2;
    printf("Среднее арифметическое %d c %d: %.2f\n", numberA, numberB, averageAB);
}

void SummaNaturalNumbers() {
    int numberA;
    int SummaNumbers = 0;
     
    do {
        printf("Введите число A (0 <= A <= 100): ");
        int inputResult = scanf("%d", &numberA);

        if (inputResult != 1) {
            printf("Ошибка: нужно ввести одно число\n");
            while (getchar() != '\n');
            continue;
        }
        if (numberA < 0 || numberA > 100) {
            printf("Ошибка: A должно быть в пределах от 0 до 100\n");
        }
    } while (numberA < 0 || numberA > 100);

    SummaNumbers = (numberA * (numberA + 1)) / 2;
    printf("Сумма натуральных чисел последовательности 1 -> %d : %d\n", numberA, SummaNumbers);
}

int main() {
    PrintHello();
    CalculateSum();
    CalculateOperationsMultiplicationRemainder();
    CalculateOperationsDivisionAverage();
    SummaNaturalNumbers();

    return 0;
}