#include <stdio.h>

int HexCharToInt(char ch) 
{
    if (ch >= '0' && ch <= '9') 
    {
        return ch - '0';
    }
    if (ch >= 'A' && ch <= 'F') 
    {
        return ch - 'A' + 10;
    }
    if (ch >= 'a' && ch <= 'f') 
    {
        return ch - 'a' + 10;
    }
    return -1;
}

int main() 
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) 
    {
        return 1;
    }

    char c1, c2, c3, c4, c5, c6;
    if (fscanf(input, "%c%c%c%c%c%c", &c1, &c2, &c3, &c4, &c5, &c6) != 6) 
    {
        fprintf(output, "%d %d %d", -1, -1, -1);
        fclose(input);
        fclose(output);
        return 0;
    }

    int r1 = HexCharToInt(c1);
    int r2 = HexCharToInt(c2);
    int g1 = HexCharToInt(c3);
    int g2 = HexCharToInt(c4);
    int b1 = HexCharToInt(c5);
    int b2 = HexCharToInt(c6);

    int red   = (r1 == -1 || r2 == -1) ? -1 : r1 * 16 + r2;
    int green = (g1 == -1 || g2 == -1) ? -1 : g1 * 16 + g2;
    int blue  = (b1 == -1 || b2 == -1) ? -1 : b1 * 16 + b2;

    if (red == -1 || green == -1 || blue == -1) 
    {
        fprintf(output, "%d %d %d", -1, -1, -1);
    } 
    else 
    {
        fprintf(output, "%d %d %d", red, green, blue);
    }

    fclose(input);
    fclose(output);
    return 0;
}