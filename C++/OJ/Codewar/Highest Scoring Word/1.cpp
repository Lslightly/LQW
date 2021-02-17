#include <iostream>
#include <string>
inline int AlphaToInt(char);
std::string highestScoringWord(const std::string &str)
{
    std::string key;
    int begin_pos = 0, i = 0;
    int count = 0, max_count = 0;
    for (i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            if (count > max_count)
            {
                key = str.substr(begin_pos, i-begin_pos); 
                max_count = count;
            }
            count = 0;
            begin_pos = i + 1;
        }
        else
        {
            count += AlphaToInt(str[i]);
        }
    }
    if (count > max_count)
    {
        key = str.substr(begin_pos, i-begin_pos);
        max_count = count;
    }
    return key;
}

inline int AlphaToInt(char alpha)
{
    return alpha - 'a' + 1;
}

int main(void)
{
    std::string input;
    std::getline(std::cin, input);
    std::cout << highestScoringWord(input);
}