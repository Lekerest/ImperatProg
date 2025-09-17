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

    char hex[7];
    fscanf(input, "%6s", hex);

    int r1 = HexCharToInt(hex[0]);
    int r2 = HexCharToInt(hex[1]);
    
    int red;
    if (r1 == -1 || r2 == -1) 
    {
        red = -1;
    } 
    else 
    {
        red = r1 * 16 + r2;
    }

    int g1 = HexCharToInt(hex[2]);
    int g2 = HexCharToInt(hex[3]);

    int green;
    if (g1 == -1 || g2 == -1) 
    {
        green = -1;
    } 
    else 
    {
        green = g1 * 16 + g2;
    }

    int b1 = HexCharToInt(hex[4]);
    int b2 = HexCharToInt(hex[5]);

    int blue;
    if (b1 == -1 || b2 == -1) 
    {
        blue = -1;
    } 
    else 
    {
        blue = b1 * 16 + b2;
    }

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