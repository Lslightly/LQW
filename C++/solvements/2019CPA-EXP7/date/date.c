// A. 即便是闰年也没有多的假期，伤心
// 定义一个结构体变量（包含年月日），写一个函数，将结构体通过参数传递给函数，由函数计算该日在本年中是第几天。
// Input Description
// 公元后的任何日子，输入为三个数，年月日，在同一行，用空格分隔
// Output Description
// 输出为一个数
// INPUT 1
// 1908 10 8
// OUTPUT 1
// 282

#include <stdio.h>
#include <stdlib.h>
struct day
{
    long long int year;
    int month;
    int date;
};
typedef struct day D;
void order(D *);
int main(void)
{
    D *p;
    p = (D *)malloc(sizeof(D));
    scanf("%lld%d%d", &(p->year), &(p->month), &(p->date));
    order(p);
    free(p);
}
void order(D *p)
{
    int day = 0;
    if ((p->year % 4 == 0 && p->year % 100 != 0) || (p->year % 400 == 0))
    {
        for (int i = 1; i < p->month && i <= 7; i += 2)
            day += 31;
        if (p->month > 2)
        {
            day += 29;
            for (int j = 4; j < p->month && j <= 6; j += 2)
                day += 30;
        }
        for (int i = 8; i < p->month; i+=2)
            day += 31;
        for (int j = 9; j < p->month; j+=2)
            day += 30;
        day += p->date;
        printf("%d", day);
        return;
    }
    else
    {
        for (int i = 1; i < p->month && i <= 7; i += 2)
            day += 31;
        if (p->month > 2)
        {
            day += 28;
            for (int j = 4; j < p->month && j <= 6; j += 2)
                day += 30;
        }
        for (int i = 8; i < p->month; i+=2)
            day += 31;
        for (int j = 9; j < p->month; j+=2)
            day += 30;
        day += p->date;
        printf("%d", day);
        return;
    }
}