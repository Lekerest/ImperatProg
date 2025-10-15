#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 21
#define MAX_CLUES 21
#define MAX_POSS 32768
#define MAX_SOLS 1024

typedef struct
{
    unsigned int rows[MAXN];
} Sol;

int row_clues_cnt[MAXN];
int row_clues[MAXN][MAX_CLUES];
int col_clues_cnt[MAXN];
int col_clues[MAXN][MAX_CLUES];

unsigned int row_poss[MAXN][MAX_POSS];
int row_poss_cnt[MAXN];

unsigned int col_poss[MAXN][MAX_POSS];
int col_poss_cnt[MAXN];

Sol all_sols[MAX_SOLS];
int sols_cnt;

void gen(int pos, int cid, int run, int *clues, int clues_size, unsigned int mask, int len, unsigned int *res, int *cnt)
{
    if (pos == len)
    {
        if (cid == clues_size && run == 0)
        {
            res[*cnt] = mask;
            (*cnt)++;
        }
        return;
    }

    // Размещение '.'
    if (run == 0)
    {
        gen(pos + 1, cid, 0, clues, clues_size, mask, len, res, cnt);
    }

    // Размещение '*'
    int can = 1;
    if (run == 0)
    {
        if (cid >= clues_size)
        {
            can = 0;
        }
        if (pos > 0 && (mask & (1u << (pos - 1))))
        {
            can = 0;
        }
    }
    if (can)
    {
        unsigned int new_mask = mask | (1u << pos);
        int new_cid = cid;
        int new_run;
        if (run == 0)
        {
            new_run = clues[cid] - 1;
        }
        else
        {
            new_run = run - 1;
        }
        if (new_run == 0)
        {
            new_cid++;
        }
        if (new_run >= 0)
        {
            gen(pos + 1, new_cid, new_run, clues, clues_size, new_mask, len, res, cnt);
        }
    }
}

void solve(int r, unsigned int *placed, unsigned int *col_pref, int X, int Y)
{
    if (r == X)
    {
        if (sols_cnt < MAX_SOLS)
        {
            memcpy(all_sols[sols_cnt].rows, placed, X * sizeof(unsigned int));
            sols_cnt++;
        }
        return;
    }
    for (int i = 0; i < row_poss_cnt[r]; i++)
    {
        unsigned int rm = row_poss[r][i];
        placed[r] = rm;
        unsigned int new_col_pref[MAXN];
        int ok = 1;
        for (int j = 0; j < Y; j++)
        {
            unsigned int bit = (rm & (1u << j)) ? (1u << r) : 0;
            new_col_pref[j] = col_pref[j] | bit;
            int match = 0;
            for (int p = 0; p < col_poss_cnt[j]; p++)
            {
                unsigned int cm = col_poss[j][p];
                if ((cm & ((1u << (r + 1)) - 1)) == new_col_pref[j])
                {
                    match = 1;
                    break;
                }
            }
            if (!match)
            {
                ok = 0;
                break;
            }
        }
        if (ok)
        {
            solve(r + 1, placed, new_col_pref, X, Y);
        }
    }
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL)
    {
        return 1;
    }

    char buf[1024];
    fgets(buf, sizeof(buf), input);
    int X;
    sscanf(buf, "%d", &X);

    // Чтение описаний для строк
    for (int i = 0; i < X; i++)
    {
        fgets(buf, sizeof(buf), input);
        char *tok = strtok(buf, " \n");
        int k;
        if (tok)
        {
            k = atoi(tok);
            row_clues_cnt[i] = k;
            tok = strtok(NULL, " \n");
            for (int j = 0; j < k; j++)
            {
                if (tok)
                {
                    row_clues[i][j] = atoi(tok);
                    tok = strtok(NULL, " \n");
                }
            }
        }
        else
        {
            row_clues_cnt[i] = 0;
        }
    }

    fgets(buf, sizeof(buf), input);
    int Y;
    sscanf(buf, "%d", &Y);

    // Чтение описаний для столбцов
    for (int i = 0; i < Y; i++)
    {
        fgets(buf, sizeof(buf), input);
        char *tok = strtok(buf, " \n");
        int k;
        if (tok)
        {
            k = atoi(tok);
            col_clues_cnt[i] = k;
            tok = strtok(NULL, " \n");
            for (int j = 0; j < k; j++)
            {
                if (tok)
                {
                    col_clues[i][j] = atoi(tok);
                    tok = strtok(NULL, " \n");
                }
            }
        }
        else
        {
            col_clues_cnt[i] = 0;
        }
    }

    // Предвычисление возможных конфигураций для строк
    for (int i = 0; i < X; i++)
    {
        int cnt = 0;
        gen(0, 0, 0, row_clues[i], row_clues_cnt[i], 0, Y, row_poss[i], &cnt);
        row_poss_cnt[i] = cnt;
    }

    // Предвычисление возможных конфигураций для столбцов
    for (int i = 0; i < Y; i++)
    {
        int cnt = 0;
        gen(0, 0, 0, col_clues[i], col_clues_cnt[i], 0, X, col_poss[i], &cnt);
        col_poss_cnt[i] = cnt;
    }

    // Запуск решения
    unsigned int placed[MAXN];
    unsigned int col_pref[MAXN];
    memset(col_pref, 0, sizeof(col_pref));
    sols_cnt = 0;
    solve(0, placed, col_pref, X, Y);

    // Вывод результатов
    if (sols_cnt == 0)
    {
        fprintf(output, "no solutions\n");
    }
    else
    {
        for (int k = 0; k < sols_cnt; k++)
        {
            for (int i = 0; i < X; i++)
            {
                for (int j = 0; j < Y; j++)
                {
                    char c = (all_sols[k].rows[i] & (1u << j)) ? '*' : '.';
                    fprintf(output, "%c", c);
                }
                fprintf(output, "\n");
            }
            if (k < sols_cnt - 1)
            {
                fprintf(output, "next\n");
            }
            else
            {
                fprintf(output, "end\n");
            }
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}