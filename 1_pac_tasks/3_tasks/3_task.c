#include <stdio.h>

int count_nines(long long x) {
    int cnt = 0;
    while (x > 0) {
        if (x % 10 == 9) cnt++;
        x /= 10;
    }
    return cnt;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (input == NULL || output == NULL) return 1;

    int n;
    fscanf(input, "%d", &n);

    int result = 0;
    for (int i = 0; i < n; i++) {
        int price;
        fscanf(input, "%d", &price);

        long long before = (long long)price * 100;
        long long after = before - 1;

        int n1 = count_nines(before);
        int n2 = count_nines(after);

        result += (n2 - n1);
    }

    fprintf(output, "%d", result);

    fclose(input);
    fclose(output);
    return 0;
}
