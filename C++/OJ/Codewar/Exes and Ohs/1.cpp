#include <iostream>
#include <string>
using namespace std;
bool XO(const std::string& str);

int main(void)
{
    cout << XO("zxx\noo");
    return 0;
}

bool XO(const std::string& str)
{
    int num_x = 0, num_o = 0;
    for (long  i = 0; i < str.length(); i++)
    {
        if (str[i] == 'x' || str[i] == 'X')
        {
            num_x++;
        }
        else if (str[i] == 'o' || str[i] == 'O')
        {
            num_o++;
        }
    }
    if (num_o == num_x)
    {
        return true;
    }
    else
    {
        return false;
    }
}