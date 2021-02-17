#include <iostream>
using namespace std;
bool narcissistic(int value)
{
    int num_digits = 0, i = 0, sum = 0, power = 1, mem = value;
    int digits[100] = {};
    while (value != 0)
    {
        digits[i] = value % 10;
        value /= 10;
        num_digits++;
        i++;
    }
    for (i = 0; i < num_digits; i++)
    {
        power = 1;
        for (int j = 0; j < num_digits; j++)
        {
            power *= digits[i];
        }
        sum += power;
    }
    return sum == mem;
}

int main(void)
{
    int input = 0;
    scanf("%d", &input);
    cout << narcissistic(input);
}