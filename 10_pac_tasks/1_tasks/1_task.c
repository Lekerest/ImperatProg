#include <stdio.h>

int main()
{
    int N;
    long long K;

    if (scanf("%d %lld", &N, &K) != 2)
    {
        return 0;
    }

    long long result = 0;

    for (int i = 1; i <= N; i++)
    {
        result = (result + K) % i;
    }

    result = result + 1;

    printf("%lld\n", result);

    return 0;
}
