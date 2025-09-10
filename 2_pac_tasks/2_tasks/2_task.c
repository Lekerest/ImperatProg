#include <stdio.h>
int main(void)
{
    int n;
    freopen("input.txt", "r", stdin);//r-файл для чтения
    freopen("output.txt", "w", stdout);//w-файл для записи
    /*имя,режим доступа\парам.,поток станд.ввод\вывод*/
    scanf("%d", &n);
    printf("n = %d", n);
    fclose(stdin);//закрытие потока
    fclose(stdout);
    return 0;
}