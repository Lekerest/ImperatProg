#include <stdio.h>
#include <string.h>

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt) {
    int len = 0;
    *oLowerCnt = *oUpperCnt = *oDigitsCnt = 0;

    for (int i = 0; iStr[i] != '\0'; i++) 
    {
        char c = iStr[i];
        len++;

        if (c >= 'a' && c <= 'z') 
        {
            (*oLowerCnt)++;
        }

        else if (c >= 'A' && c <= 'Z') 
        {
            (*oUpperCnt)++;
        }

        else if (c >= '0' && c <= '9') 
        {
            (*oDigitsCnt)++;
        }
    }
    return len;
}

int main(void) 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output) 
    {
        return 1;
    }

    char line[102];
    int lineNo = 0;

    while (fgets(line, sizeof(line), input)) 
    {
        int l = strlen(line);

        if (l > 0) 
        {
            line[l - 1] = '\0';
        }

        int lowerCnt, upperCnt, digitCnt;
        
        int len = calcLetters(line, &lowerCnt, &upperCnt, &digitCnt);
        
        int letterCnt = lowerCnt + upperCnt;

        fprintf(output,
                "Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n",
                ++lineNo, len, letterCnt, lowerCnt, upperCnt, digitCnt);
    }

    fclose(input);
    fclose(output);
    return 0;
}