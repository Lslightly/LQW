#include <stdio.h>

int main(void)
{
    double input = 0;
    while (scanf("%lf", &input) && (input - 0.0) >= 0.0001)
    {
        int cards = 1;
        double sum = 1.0/(cards+1);
        while (sum < input)
        {
            cards++;
            sum += 1.0/(cards+1);
        }
        printf("%d card(s)\n", cards);
    }
    return 0;
}