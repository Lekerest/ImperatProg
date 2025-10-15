#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIG 101

typedef struct {
    char digits[MAX_DIG];
    int len;
    int sign;  // 1: positive, -1: negative, 0: zero
} BigInt;

// Функция нормализации (удаление ведущих нулей)
void normalize(BigInt *b) {
    while (b->len > 1 && b->digits[b->len - 1] == 0) {
        b->len--;
    }
    if (b->len == 1 && b->digits[0] == 0) {
        b->sign = 0;
    }
}

// Создание BigInt из строки
BigInt from_string(const char *s) {
    BigInt res;
    memset(res.digits, 0, sizeof(res.digits));
    int negative = 0;
    if (s[0] == '-') {
        negative = 1;
        s++;
    }
    int slen = strlen(s);
    res.len = slen;
    for (int i = 0; i < slen; i++) {
        res.digits[i] = s[slen - 1 - i] - '0';
    }
    normalize(&res);
    if (res.sign == 0) {
        res.sign = 0;
    } else {
        res.sign = negative ? -1 : 1;
    }
    return res;
}

// Сравнение абсолютных значений двух BigInt (игнорируя знак)
int compare_abs(BigInt a, BigInt b) {
    if (a.len != b.len) {
        return a.len > b.len ? 1 : -1;
    }
    for (int i = a.len - 1; i >= 0; i--) {
        if (a.digits[i] != b.digits[i]) {
            return a.digits[i] > b.digits[i] ? 1 : -1;
        }
    }
    return 0;
}

// Сложение двух BigInt
BigInt add(BigInt a, BigInt b) {
    if (a.sign == 0) return b;
    if (b.sign == 0) return a;
    if (a.sign != b.sign) {
        if (a.sign == -1) {
            a.sign = 1;
            return sub(b, a);
        } else {
            b.sign = 1;
            return sub(a, b);
        }
    }
    // Одинаковые знаки
    BigInt res;
    res.sign = a.sign;
    int carry = 0;
    int maxl = (a.len > b.len ? a.len : b.len);
    res.len = 0;
    for (int i = 0; i < maxl || carry; i++) {
        int sum = carry;
        if (i < a.len) sum += a.digits[i];
        if (i < b.len) sum += b.digits[i];
        res.digits[res.len++] = sum % 10;
        carry = sum / 10;
    }
    normalize(&res);
    return res;
}

// Вычитание двух BigInt (a - b)
BigInt sub(BigInt a, BigInt b) {
    if (b.sign == 0) return a;
    if (a.sign == 0) {
        b.sign = -b.sign;
        return b;
    }
    if (a.sign != b.sign) {
        b.sign = -b.sign;
        return add(a, b);
    }
    // Одинаковые знаки
    int cmp = compare_abs(a, b);
    if (cmp == 0) {
        BigInt zero;
        zero.sign = 0;
        zero.len = 1;
        zero.digits[0] = 0;
        return zero;
    }
    if (cmp < 0) {
        BigInt res = sub(b, a);
        res.sign = -res.sign;
        return res;
    }
    // |a| > |b|
    BigInt res;
    res.sign = a.sign;
    int borrow = 0;
    res.len = 0;
    for (int i = 0; i < a.len; i++) {
        int diff = a.digits[i] - borrow;
        if (i < b.len) diff -= b.digits[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.digits[res.len++] = diff;
    }
    normalize(&res);
    return res;
}

// Умножение двух BigInt
BigInt mul(BigInt a, BigInt b) {
    BigInt res;
    if (a.sign == 0 || b.sign == 0) {
        res.sign = 0;
        res.len = 1;
        res.digits[0] = 0;
        return res;
    }
    res.sign = a.sign * b.sign;
    res.len = a.len + b.len;
    memset(res.digits, 0, res.len);
    for (int i = 0; i < a.len; i++) {
        long long carry = 0;
        for (int j = 0; j < b.len || carry; j++) {
            long long prod = res.digits[i + j] +
                             (long long)a.digits[i] * (j < b.len ? b.digits[j] : 0) +
                             carry;
            res.digits[i + j] = prod % 10;
            carry = prod / 10;
        }
    }
    normalize(&res);
    return res;
}

// Преобразование BigInt в строку
char *to_string(BigInt b) {
    if (b.sign == 0) {
        return strdup("0");
    }
    char *s = (char *)malloc(b.len + 2);
    int pos = 0;
    if (b.sign == -1) {
        s[pos++] = '-';
    }
    for (int i = b.len - 1; i >= 0; i--) {
        s[pos++] = b.digits[i] + '0';
    }
    s[pos] = '\0';
    return s;
}

int main() {
    int N;
    scanf("%d", &N);
    
    // Массив для хранения последовательности
    BigInt sequence[1001];
    
    // Цикл чтения и вычисления элементов последовательности
    for (int k = 0; k < N; k++) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            // Явное число - читаем как строку
            char buf[102];
            scanf("%s", buf);
            sequence[k] = from_string(buf);
        } else {
            // Операция над предыдущими элементами
            int a_idx, b_idx;
            scanf("%d %d", &a_idx, &b_idx);
            BigInt aa = sequence[a_idx];
            BigInt bb = sequence[b_idx];
            if (t == 1) {
                sequence[k] = add(aa, bb);
            } else if (t == 2) {
                sequence[k] = sub(aa, bb);
            } else if (t == 3) {
                sequence[k] = mul(aa, bb);
            }
        }
    }
    
    // Вывод всех элементов последовательности
    for (int i = 0; i < N; i++) {
        char *str = to_string(sequence[i]);
        printf("%s\n", str);
        free(str);
    }
    
    return 0;
}