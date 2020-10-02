#include "Polynomial.h"
#include <stdio.h>

Polynomial input_poly(void);

void input_ch(Polynomial * polys);

int main(void)
{
    FILE *fp = freopen("1.txt", "r", stdin);
    printf("\
    ENTER + to add the two polynomials\n\
    ENTER - to subtract the two polynomials\n\
    ENTER * to multiply the two polynomials\n\
    ENTER d to derivate the polynomial\n\
    ENTER x to calculate the polynomial\n\
    ENTER q to quit\n");
    char ch = 0;
    Polynomial a[2];
    for (int k = 0; k < 2; k++)
    {
        a[k] = input_poly();
    }
    input_ch(a);
    return 0;
}

Polynomial input_poly(void)
{
    printf("Enter the number of items:\n");
    Polynomial a;
    int n_in = 0;
    scanf("%d", &n_in);

    for (int i = 0; i < n_in; i++)
    {
        double coef_in = 0;
        int expn_in = 0;
        scanf("%lf%d", &coef_in, &expn_in);
        Polynomial b = Polynomial();
        b.ListInsert(LNode<Item>({coef_in, expn_in}));
        a = a + b;
    }
    return a;
}

void input_ch(Polynomial * polys)
{
    char ch = 0;
    while (ch = getchar())
    {
        if (ch == '+')
        {
            (polys[0] + polys[1]).PrintPolyn();
        }
        else if (ch == '-')
        {
            (polys[0] - polys[1]).PrintPolyn();
        }
        else if (ch == '*')
        {
            (polys[0] * polys[1]).PrintPolyn();
        }
        else if (ch == 'd')
        {
            int na = 0, nb = 0;
            scanf("%d", &na);
            polys[0].derivate(na).PrintPolyn();
            scanf("%d", &nb);
            polys[1].derivate(nb).PrintPolyn();
        }
        else if (ch == 'x')
        {
            double x = 0;
            scanf("%lf", &x);
            printf("%lf\n", polys[0].calculate(x));
        }
        else if (ch == 'q')
        {
            break;
        }
        else if (ch == 'a')
            polys[0].PrintPolyn();
        else if (ch == 'b')
            polys[1].PrintPolyn();
    }

}