#include <stdio.h>

int main(void)
{
    double income[12] = {0}, sum = 0.0;
    for (int i = 0; i < 12; i++)
    {
        scanf("%lf", &income[i]);
        sum += income[i];
    }
    printf("$%.2lf", sum/12);
    return 0;
}