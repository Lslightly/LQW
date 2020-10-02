#include "Polynomial.h"
#include <stdio.h>

int main(void)
{ 
    // FILE * fp = freopen("1.txt","r", stdin);
    printf("\
    ENTER + to add the two polynomials\n\
    ENTER - to subtract the two polynomials\n\
    ENTER * to multiply the two polynomials\n\
    ENTER d to derivate the polynomial\n\
    ENTER x to calculate the polynomial\n\
    ENTER q to quit\n");
    char ch = 0;
    Polynomial a, b;
    a.PrintPolyn();
    b.PrintPolyn();
    while (ch = getchar())
    {
        if (ch == '+')
        {
            (a+b).PrintPolyn();
        }
        else if (ch == '-')
        {
            (a-b).PrintPolyn();
        }
        else if (ch == '*')
        {
            (a*b).PrintPolyn();
        }
        else if (ch == 'd')
        {
            int na = 0, nb = 0;
            scanf("%d", &na);
            a.derivate(na).PrintPolyn();
            scanf("%d", &nb);
            b.derivate(nb).PrintPolyn();
        }
        else if (ch == 'x')
        {
            double x =0;
            scanf("%lf", &x);
            printf("%lf\n", a.calculate(x));
        }
        else if (ch == 'q')
        {
            break;
        }
        else if (ch == 'a')
            a.PrintPolyn();
        else if (ch == 'b')
            b.PrintPolyn();
    }
    return 0;
}