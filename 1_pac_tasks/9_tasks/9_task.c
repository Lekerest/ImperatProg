#include <stdio.h>

typedef long long ll;

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    ll N;
    fscanf(input, "%lld", &N);
    
    ll count = 0;
    ll max_c;
    // Перебираем первую сторону (самую маленькую)
    for (ll a = 1; a * a * a <= N; a++) {
        
        // Перебираем вторую сторону (среднюю)
        for (ll b = a; a * b * b <= N; b++) {
            
            // Для данных a и b находим максимальную третью сторону
            max_c = N / (a * b);
            
            // Убеждаемся, что c ≥ b (чтобы сохранить порядок a ≤ b ≤ c)
            if (max_c < b) continue;
            
            // Добавляем количество возможных c
            count += (max_c - b + 1);
        }
    }
    
    fprintf(output, "%lld", count);
    
    fclose(input);
    fclose(output);
    return 0;
}