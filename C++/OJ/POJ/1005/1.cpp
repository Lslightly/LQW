#include <stdio.h>
#include <cmath>
const int shrink = 50;
int main(void)
{
    int n = 0;
    scanf("%d", &n);

    double x = 0.0, y = 0.0;
    double r_lasty = 0.0, r_thisy = 0.0, dis = 0.0;
    for (int No = 1; No <= n; No++)
    {
        scanf("%lf%lf", &x, &y);
        dis = sqrt(x*x+y*y);

        int year = 1;
        r_thisy = sqrt(2/M_PI*shrink*year);
        while (r_thisy < dis)
        {
            year++;
            r_thisy = sqrt(2/M_PI*shrink*year);
        }
        printf("Property %d: This property will begin eroding in year %d.\n", No, year);
    }
    printf("END OF OUTPUT.");
    return 0;
}