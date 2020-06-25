#include <stdio.h>

int main(void)
{
    double a, b, c, d = 0, e = 4.0, f = 0, g = 0;
    while (d < 70 / 29.2)
    {
        f = g = 0;
        e = 2.4;
        while (e < 2.5)
        {
            f = g = 0;
            int flag = 0;
            while (f < 70/15.9)
            {
                g = 0;
                while (g < 0.5)
                {
                    a = -26.852441 + 13.854015 * d + 1.523835 * e + 0.208539 * f + 53.26761 * g;
                    b = 86.289553 - 34.966529 * d - 3.922086 * e + 0.812768 * f - 140.085864 * g;
                    c = 76.745111 - 38.834791 * d -5.054858 * e - 13.577357 * f -95.245667 * g;
                    if ((a > 5 && a < 7) && b > 0 && c > 0 && b < 1.5 && b > 1 && d > 0.6)
                    {
                        printf("a=%lf b=%lf c=%lf d=%lf e=%lf f=%lf g=%lf \nprototal=%lf\nfattotal=%lf\nCHOtotal=%lf\n",a, b, c, d, e, f, g, 7.5 * a+1.9*b+1.4*c+16.9*d+3.1*e+15.9*f,\
                        0.5*a+0.7*b+0.3*c+29.2*d+3.5*e+3.4*f+100*g,\
                        79*a+28*b+3*c+1.1*d+4.6*e+1.5*f);
                        flag = 1;
                        break;
                    }
                    g += 0.01;
                }
                f += 0.01;
            }
            e += 0.01;
        }
        d += 0.01;
    }
}