#include "Stack.h"
#include <stdio.h>

void ten_to_x(int x);

int main(void)
{
    while (1)
    {
        int sys = 0;
        if (scanf("%d", &sys) == 0) break;
        if (sys <= 10 && sys > 1)
            ten_to_x(sys);
    }
    return 0;
}

void ten_to_x(int x)
{
    SqStack<int> S = SqStack<int>();

    int N = 0;
    scanf("%d", &N);

    while (N)
    {
        S.Push(N % x);
        N /= x;
    }
    while (!S.StackEmpty())
    {
        int e = 0;
        S.Pop(e);
        printf("%d", e);
    }
    putchar('\n');
}