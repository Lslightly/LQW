#include <stdio.h>
#include <math.h>

int main(void)
{
    double numerator = 0, denominator = 0;
    printf("Input the numerator and denominator and calculate arctan(numerator/denominator) in rad system:");
    scanf("%lf%lf", &numerator, &denominator);
    printf("%lf", atan(numerator/denominator)*180/3.1415926);
}