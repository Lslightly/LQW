#include "Polynomial.h"
#include <stdio.h>

int main(void)
{
    {
        Polynomial a, b;
        a.PrintPolyn();
        b.PrintPolyn();
        a.AddPolyn(b).PrintPolyn();
    }
    return 0;
}