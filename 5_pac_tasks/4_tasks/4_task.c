#include <stdio.h>
#include <math.h>

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int n;
    fscanf(input, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        double Ax, Ay, Bx, By, Cx, Cy;
        fscanf(input, "%lf %lf %lf %lf %lf %lf", &Ax, &Ay, &Bx, &By, &Cx, &Cy);

        // вычисление векторов
        double a_left_x = Bx - Ax;
        double a_left_y = By - Ay;
        double a_right_x = Cx - Ax;
        double a_right_y = Cy - Ay;

        // скалярное
        double dot = a_left_x * a_right_x + a_left_y * a_right_y;
        
        // векторное
        double cross = a_left_x * a_right_y - a_left_y * a_right_x;
        
        // (atan2)(|AB||AC| |sin|, |AB||AC| |cos|) = (atan2)(|sin|, |cos|)
        double radians = atan2(fabs(cross), dot);

        // перевод в градусы
        double degrees = radians * 180.0 / acos(-1.0);

        fprintf(output, "%.20g\n", degrees);
    }

    fclose(input);
    fclose(output);
    return 0;
}