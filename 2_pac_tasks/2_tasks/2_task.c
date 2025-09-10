#include <stdio.h>
#include <string.h>

int hexCharToInt(char ch) 
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return -1;
}

int hexStringToInt(char str[3]) 
{
    int first = hexCharToInt(str[0]);
    int second  = hexCharToInt(str[1]);
    
    if (first == -1 || second == -1) return -1;
    
    return first * 16 + second;
}

int main() 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }

    char inputstr[7];
    fscanf(input, "%6s", inputstr);

    char colorA[3], colorB[3], colorC[3];

    strncpy(colorA, inputstr + 0, 2);
    colorA[2] = '\0';
    int valueA = hexStringToInt(colorA);

    strncpy(colorB, inputstr + 2, 2);
    colorB[2] = '\0';
    int valueB = hexStringToInt(colorB);

    strncpy(colorC, inputstr + 4, 2);
    colorC[2] = '\0';
    int valueC = hexStringToInt(colorC);

    if (valueA == -1 || valueB == -1 || valueC == -1) {
        fprintf(output, "%d %d %d", -1, -1, -1);
    } else {
        fprintf(output, "%d %d %d", valueA, valueB, valueC);
    }

    fclose(input);
    fclose(output);
    return 0;
}