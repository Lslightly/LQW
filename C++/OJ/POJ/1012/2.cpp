#include<iostream>
#include <vector>
using namespace std;

int result;
int n;
bool jud(int num, int i, int cur)
{
    if (num == n)
        return true;
    else
    {
        if ((i + cur - 1) % num < n)
            return false;
        return jud(num - 1, i, (i + cur - 1) % num);
    }
}

int main()
{
    while (cin >> n && n)
    {
        for (int i = n + 1;; i++)
        {
            if (jud(2 * n, i, 0))
            {
                cout << i << endl;
                break;
            }
        }
    }
}