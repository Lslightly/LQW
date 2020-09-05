#include <stdio.h>
template <typename T>
void swap(T &a, T &b);

int main(void)
{
    int m = 5;
    double x = 14.3;
    printf("m:%d\tx:%lf\n", m, x);
    swap<double>(m, x);
    printf("m:%d\tx:%lf\n", m, x);
    return 0;
}

template <typename T>
void swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}
