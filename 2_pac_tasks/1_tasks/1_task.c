#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        return 1;
    }

    char c1 = '\0', c2 = '\0', c3 = '\0', c4 = '\0', c5 = '\0';
    char c6 = '\0', c7 = '\0', c8 = '\0', c9 = '\0', c10 = '\0';

    fscanf(input, "%c%c%c%c%c%c%c%c%c%c",
           &c1, &c2, &c3, &c4, &c5,
           &c6, &c7, &c8, &c9, &c10);

    int count = 0;
    int result = 0;

    // Monday 
    if ((c1=='M') &&
        (c2=='o' || c2=='\0') &&
        (c3=='n' || c3=='\0') &&
        (c4=='d' || c4=='\0') &&
        (c5=='a' || c5=='\0') &&
        (c6=='y' || c6=='\0') &&
        (c7=='\0')) {
        count++; result = 1;
    }

    // Tuesday 
    if ((c1=='T') &&
        (c2=='u' || c2=='\0') &&
        (c3=='e' || c3=='\0') &&
        (c4=='s' || c4=='\0') &&
        (c5=='d' || c5=='\0') &&
        (c6=='a' || c6=='\0') &&
        (c7=='y' || c7=='\0') &&
        (c8=='\0')) {
        count++; result = 2;
    }

    // Wednesday 
    if ((c1=='W') &&
        (c2=='e' || c2=='\0') &&
        (c3=='d' || c3=='\0') &&
        (c4=='n' || c4=='\0') &&
        (c5=='e' || c5=='\0') &&
        (c6=='s' || c6=='\0') &&
        (c7=='d' || c7=='\0') &&
        (c8=='a' || c8=='\0') &&
        (c9=='y' || c9=='\0') &&
        (c10=='\0')) {
        count++; result = 3;
    }

    // Thursday 
    if ((c1=='T') &&
        (c2=='h' || c2=='\0') &&
        (c3=='u' || c3=='\0') &&
        (c4=='r' || c4=='\0') &&
        (c5=='s' || c5=='\0') &&
        (c6=='d' || c6=='\0') &&
        (c7=='a' || c7=='\0') &&
        (c8=='y' || c8=='\0') &&
        (c9=='\0')) {
        count++; result = 4;
    }

    // Friday 
    if ((c1=='F') &&
        (c2=='r' || c2=='\0') &&
        (c3=='i' || c3=='\0') &&
        (c4=='d' || c4=='\0') &&
        (c5=='a' || c5=='\0') &&
        (c6=='y' || c6=='\0') &&
        (c7=='\0')) {
        count++; result = 5;
    }

    // Saturday
    if ((c1=='S') &&
        (c2=='a' || c2=='\0') &&
        (c3=='t' || c3=='\0') &&
        (c4=='u' || c4=='\0') &&
        (c5=='r' || c5=='\0') &&
        (c6=='d' || c6=='\0') &&
        (c7=='a' || c7=='\0') &&
        (c8=='y' || c8=='\0') &&
        (c9=='\0')) {
        count++; result = 6;
    }

    // Sunday 
    if ((c1=='S') &&
        (c2=='u' || c2=='\0') &&
        (c3=='n' || c3=='\0') &&
        (c4=='d' || c4=='\0') &&
        (c5=='a' || c5=='\0') &&
        (c6=='y' || c6=='\0') &&
        (c7=='\0')) {
        count++; result = 7;
    }

    // Результат 
    if (count == 0) {
        fprintf(output, "Invalid");
    } else if (count > 1) {
        fprintf(output, "Ambiguous");
    } else {
        fprintf(output, "%d", result);
    }

    fclose(input);
    fclose(output);
    return 0;
}