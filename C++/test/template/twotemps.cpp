#include <stdio.h>

template <typename T>
void Swap(T &a, T &b);

template <typename T>
void Swap(T *a, T *b, int n);

#define N 1000

int main(void)
{
    int x = 1, y = 2;
    printf("original x:%d\toriginal y:%d\n", x, y);
    Swap(x, y);
    printf("x swapped:%d\ty swapped:%d\n", x, y);

    int a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[N] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    printf("original a array:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\noriginal b array:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");
    Swap(a, b, 10);
    printf("a swapped:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\nb swapped:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");
    return 0;
}

template <typename T>
void Swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <typename T>
void Swap(T *a, T *b, int n)
{
    T temp;
    for (int i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
