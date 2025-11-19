#include <stdio.h>
#include <stdlib.h>

struct Point
{
    int x;
    int y;
    long long dist2;
};

long long distance2
(
    int x,
    int y
)
{
    long long a = x;
    long long b = y;
    return a * a + b * b;
}

int compare_points
(
    const void *a,
    const void *b
)
{
    const struct Point *p1 = (const struct Point *)a;
    const struct Point *p2 = (const struct Point *)b;

    if (p1->dist2 < p2->dist2)
    {
        return -1;
    }
    else if (p1->dist2 > p2->dist2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int k;

    if (scanf("%d", &k) != 1)
    {
        return 0;
    }

    int capacity = 10000;

    struct Point *points =
        (struct Point *)malloc(sizeof(struct Point) * capacity);

    int n = 0;

    while (1)
    {
        int x;
        int y;

        if (scanf("%d %d", &x, &y) != 2)
        {
            break;
        }

        points[n].x = x;
        points[n].y = y;
        points[n].dist2 = distance2(x, y);

        n++;

        if (n == capacity)
        {
            int new_capacity = capacity * 2;

            struct Point *new_points =
                (struct Point *)malloc(sizeof(struct Point) * new_capacity);

            for (int i = 0; i < n; i++)
            {
                new_points[i] = points[i];
            }

            free(points);

            points = new_points;
            capacity = new_capacity;
        }
    }

    qsort(points, n, sizeof(struct Point), compare_points);

    for (int i = 0; i < k && i < n; i++)
    {
        printf("%d %d\n", points[i].x, points[i].y);
    }

    free(points);

    return 0;
}
