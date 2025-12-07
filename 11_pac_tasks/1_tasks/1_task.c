#include <stdio.h>
#include <stdlib.h>

#define HT_SIZE 1000003

unsigned hsh(unsigned x)
{
    return (x * 1293921838u) % HT_SIZE;
}

int main(void)
{
    FILE *in = fopen("input.txt", "rb");
    if (!in) return 1;

    int n;
    if (fread(&n, sizeof(int), 1, in) != 1) { fclose(in); return 1; }

    int *vals = malloc((size_t)n * sizeof(int));
    fread(vals, sizeof(int), n, in);
    fclose(in);

    int *tab = malloc((size_t)HT_SIZE * sizeof(int));
    unsigned char *used = calloc((size_t)HT_SIZE, 1);
    int *out = malloc((size_t)n * sizeof(int));
    int outc = 0;

    for (int i = 0; i < n; ++i)
    {
        int v = vals[i];
        unsigned p = hsh((unsigned)v);
        while (used[p] && tab[p] != v) p = (p + 1) % HT_SIZE;
        if (!used[p]) { used[p] = 1; tab[p] = v; out[outc++] = v; }
    }

    FILE *outf = fopen("output.txt", "wb");
    if (outf)
    {
        fwrite(&outc, sizeof(int), 1, outf);
        fwrite(out, sizeof(int), outc, outf);
        fclose(outf);
    }

    free(vals);
    free(tab);
    free(used);
    free(out);
    return 0;
}