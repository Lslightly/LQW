#include <stdio.h>

int max(int a, int b);

int main(void)
{
    const int T_p = 23, T_e = 28, T_i = 33;
    int p = 0, e = 0, i = 0, d = 0, count = 1;
    while (scanf("%d%d%d%d", &p, &e, &i, &d) && (p != -1))
    {
        p %= T_p;
        e %= T_e;
        i %= T_i;
        int date = max(max(max(p, e), i), d);
        if (date == d)
            date++;
        while (((date - p) % T_p != 0) || ((date - e) % T_e != 0) || ((date - i) % T_i != 0))
            date++;
        printf("Case %d: the next triple peak occurs in %d days.\n", count, date-d);
        count++;
    }
    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}