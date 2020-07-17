#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string add(string a, string b);

int main(void)
{
    string a, b;
    cin >> a >> b;

    cout << add(a, b);
}

string add(string a, string b)
{
    int max_size = (a.size() > b.size()) ? a.size() : b.size(), temp = 0, mem = 0;
    string result;
    result.resize(max_size);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    if (a.size() < max_size)
    {
        mem = a.size();
        a.resize(max_size + 1);
        for (int i = mem; i < max_size; i++)
            a[i] = '0';
        
    }
    if (b.size() < max_size)
    {
        mem = b.size();
        b.resize(max_size + 1);
        for (int i = mem; i < max_size; i++)
            b[i] = '0';

        
    }

    for (int i = 0; i < max_size; i++)
    {
        result[i] = (a[i] - '0' + b[i] - '0' + temp) % 10 + '0';
        temp = (a[i] - '0' + b[i] - '0' + temp) / 10;
    }
    if (temp != 0)
    {
        result.resize(max_size + 1);
        result[max_size] = temp + '0';
    }
    reverse(result.begin(), result.end());
    return result;
}