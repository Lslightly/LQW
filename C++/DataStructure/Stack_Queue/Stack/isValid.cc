#include <stack>
#include <string>

using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> ST;
        size_t len = s.length();
        for (int i = 0; i < len; i++)
        {
            switch (s[i])
            {
            case '(':
            case '[':
            case '{':
                ST.push(s[i]);
                break;
            case ')':
                if (ST.empty()) return false;
                if (ST.top() != '(')
                    return false;
                ST.pop();
                break;
            case ']':
                if (ST.empty()) return false;
                if (ST.top() != '[')
                    return false;
                ST.pop();
                break;
            case '}':
                if (ST.empty()) return false;
                if (ST.top() != '{')
                    return false;
                ST.pop();
                break;
            }
        }
        return ST.empty();
    }
};