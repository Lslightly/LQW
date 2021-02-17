#include <stdio.h>
unsigned int countBits(unsigned long long n);
int main(void)
{
    printf("%u", countBits(1234));
    return 0;
}

unsigned int countBits(unsigned long long n)
{
    int count = 0;
    while (n != 0)
    {
        if (n % 2 == 1)
        {
            count++;
        }
        n /= 2;
    }
    return count;
}