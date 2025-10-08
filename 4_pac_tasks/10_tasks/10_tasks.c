#include <stdio.h>
#include <string.h>

const char* edenic[] = {
    "odna",
    "dve",
    "tri",
    "chetyre",
    "pyat'",
    "shest'",
    "sem'",
    "vosem'",
    "devyat'"
};

const char* edenic1[] = {
    "odin",
    "dva",
    "tri",
    "chetyre",
    "pyat'",
    "shest'",
    "sem'",
    "vosem'",
    "devyat'"
};

// 10..19 (для случая 10..19 используем индекс c, где c = chislo % 10)
const char* desyatki[] = {
    "desyat'",
    "odinnadtsat'",
    "dvenadtsat'",
    "trinadtsat'",
    "chetyrnadtsat'",
    "pyatnadtsat'",
    "shestnadtsat'",
    "semnadtsat'",
    "vosemnadtsat'",
    "devyatnadtsat'"
};

// кратные десятки (20,30,...,90) - будем брать desyatki1[b-1] при b != 0 и b != 1
const char* desyatki1[] = {
    "desyat'",
    "dvadtsat'",
    "tridtsat'",
    "sorok",
    "pyat'desyat",
    "shest'desyat",
    "sem'desyat",
    "vosem'desyat",
    "devyanosto"
};

// сотни 100..900 (используем sotni[a-1] при a != 0)
const char* sotni[] = {
    "sto",
    "dvesti",
    "trista",
    "chetyresta",
    "pyat'sot",
    "shest'sot",
    "sem'sot",
    "vosem'sot",
    "devyat'sot"
};

// форма слова "strok" / "stroka" / "stroki" в зависимости от полного числа
const char* padej_strok(int chislo)
{
    int last = chislo % 10;
    int last_two = chislo % 100;

    if (last_two > 9 && last_two < 20)
    {
        return "strok";
    }

    if (last == 1)
    {
        return "stroka";
    }

    if (last >= 2 && last <= 4)
    {
        return "stroki";
    }

    return "strok";
}

// форма для тысяч (возвращаем строку-постфикc или пустую строку, если тысяч нет)
const char* padej_tysich(int chislo)
{
    int grp = (chislo / 1000) % 1000;

    if (grp == 0)
    {
        return "";
    }

    int last = grp % 10;
    int last_two = grp % 100;

    if (last_two > 9 && last_two < 20)
    {
        return "tysyach";
    }

    if (last == 1)
    {
        return "tysyacha";
    }

    if (last >= 2 && last <= 4)
    {
        return "tysyachi";
    }

    return "tysyach";
}

// форма для миллионов
const char* padej_mil(int chislo)
{
    int grp = (chislo / 1000000);

    if (grp == 0)
    {
        return "";
    }

    int last = grp % 10;
    int last_two = grp % 100;

    if (last_two > 9 && last_two < 20)
    {
        return "millionov";
    }

    if (last == 1)
    {
        return "million";
    }

    if (last >= 2 && last <= 4)
    {
        return "milliona";
    }

    return "millionov";
}

// функция, печатающая тройку цифр (0..999) в res. flag == 1 => единицы женского рода (odna/dve), flag == 0 => мужской (odin/dva)
void troiki(int chislo, char* res, int flag)
{
    int a = chislo / 100;
    int b = (chislo / 10) % 10;
    int c = chislo % 10;

    res[0] = '\0';

    if (a != 0)
    {
        strcat(res, sotni[a - 1]);
    }

    if (chislo % 100 > 9 && chislo % 100 < 20)
    {
        if (a != 0)
        {
            strcat(res, " ");
        }
        strcat(res, desyatki[chislo % 10]);
    }
    else
    {
        if (b != 0)
        {
            if (a != 0)
            {
                strcat(res, " ");
            }
            /* b от 1 до 9, но b==1 уже обработано в условии teens */
            strcat(res, desyatki1[b - 1]);
        }

        if (c != 0)
        {
            if (a != 0 || b != 0)
            {
                strcat(res, " ");
            }
            if (flag == 1)
            {
                strcat(res, edenic[c - 1]);
            }
            else
            {
                strcat(res, edenic1[c - 1]);
            }
        }
    }
}

int main(void)
{
    int t;
    if (scanf("%d", &t) != 1)
    {
        return 0;
    }

    for (int i = 0; i < t; i++)
    {
        int d;
        if (scanf("%d", &d) != 1)
        {
            break;
        }

        char str1[160];
        char str2[160];
        char str3[160];

        if (d < 1000)
        {
            /* Для непосредственного количества строк используем женскую форму единиц (odna/dve) */
            troiki(d, str1, 1);
            printf("%s %s\n", str1, padej_strok(d));
        }
        else if (d < 1000000)
        {
            int tys = d / 1000;
            int ost = d % 1000;

            troiki(tys, str1, 1);  /* тысячи — женский род */
            troiki(ost, str2, 1);  /* остаток перед словом "stroka" — женский род */

            /* печатаем тысячи с нужной формой */
            printf("%s %s", str1, padej_tysich(d));

            if (ost != 0)
            {
                printf(" %s %s", str2, padej_strok(ost));
            }
            else
            {
                /* если остатка нет, форму "strok" вычисляем от полного числа d */
                printf(" %s", padej_strok(d));
            }
            printf("\n");
        }
        else
        {
            int mil = d / 1000000;
            int tys = (d / 1000) % 1000;
            int ost = d % 1000;

            troiki(mil, str1, 0);  /* миллионы — мужской род */
            troiki(tys, str2, 1);  /* тысячи — женский род */
            troiki(ost, str3, 1);  /* остаток — женский род */

            /* миллионы */
            printf("%s %s", str1, padej_mil(d));

            /* тысячи, если есть */
            if (tys != 0)
            {
                printf(" %s %s", str2, padej_tysich(d));
            }

            /* остаток */
            if (ost != 0)
            {
                printf(" %s %s", str3, padej_strok(ost));
            }
            else if (tys == 0)
            {
                /* если нет ни тысяч, ни остатков — берем форму от полного числа */
                printf(" %s", padej_strok(d));
            }

            printf("\n");
        }
    }

    return 0;
}