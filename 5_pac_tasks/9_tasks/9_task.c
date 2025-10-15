#include <stdio.h>

#define MAXN 100000
#define MAXQ 100000

typedef long long ll;

typedef struct
{
    ll x; // индекс i
    ll y; // значение A[i]
} Point;

Point hull[MAXN];
int hull_size = 0;

// --- Проверка, удаляется ли средняя точка ---
int bad(Point a, Point b, Point c)
{
    // Проверяем, делает ли точка b оболочку невыпуклой
    return (b.y - a.y) * (c.x - b.x) >= (c.y - b.y) * (b.x - a.x);
}

// --- Добавление точки (i, A[i]) в нижнюю оболочку ---
void add_point(ll i, ll Ai)
{
    Point new_point = {i, Ai};

    while (hull_size >= 2 && bad(hull[hull_size - 2], hull[hull_size - 1], new_point))
    {
        hull_size--;
    }

    hull[hull_size++] = new_point;
}

// --- Поиск оптимальной прямой для данного C ---
int query(ll C)
{
    int left = 0;
    int right = hull_size - 1;

    while (left < right)
    {
        int mid = (left + right) / 2;
        ll val1 = hull[mid].y + C * hull[mid].x;
        ll val2 = hull[mid + 1].y + C * hull[mid + 1].x;

        if (val1 <= val2)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return (int)hull[left].x;
}

// --- Главная функция ---
int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    ll A[MAXN];
    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%lld", &A[i]);
    }

    // Строим нижнюю оболочку
    hull_size = 0;
    for (int i = 0; i < n; i++)
    {
        add_point(i, A[i]);
    }

    int q;
    fscanf(input, "%d", &q);

    for (int j = 0; j < q; j++)
    {
        ll C;
        fscanf(input, "%lld", &C);
        int ans = query(C);
        fprintf(output, "%d\n", ans);
    }

    fclose(input);
    fclose(output);
    return 0;
}