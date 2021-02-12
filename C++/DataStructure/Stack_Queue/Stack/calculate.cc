#include <map>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

int add(int a, int b)
{
    return a + b;
}
int sub(int a, int b)
{
    return a - b;
}
int mul(int a, int b)
{
    return a * b;
}
int divide(int a, int b)
{
    return a / b;
}

typedef int (*func)(int a, int b);
class Solution
{
public:
    int calculate(string s)
    {
        map<char, int> priority = {
            {'+', 0},
            {'-', 0},
            {'*', 1},
            {'/', 1},
            {' ', -1}};
        map<char, func> map_func = {
            {'+', add},
            {'-', sub},
            {'*', mul},
            {'/', divide},
        };
        stack<int> stk_operand;
        stack<char> stk_operator;
        string number = "";
        int len_s = s.length();
        int i = 0;
        int a, b;
        for (; i < len_s; i++)
        {
            switch (s[i])
            {
            case ' ':
                if (number != "")
                {
                    stk_operand.push(stoi(number));
                    number = "";
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                if (number != "")
                {
                    stk_operand.push(stoi(number));
                    number = "";
                }
                while (!stk_operator.empty() && priority[s[i]] <= priority[stk_operator.top()])
                {
                    char op = stk_operator.top();
                    stk_operator.pop();
                    b = stk_operand.top();
                    stk_operand.pop();
                    a = stk_operand.top();
                    stk_operand.pop();
                    stk_operand.push(map_func[op](a, b));
                }
                stk_operator.push(s[i]);
                break;
            default:
                number += s[i];
                break;
            }
        }
        if (number != "")
        stk_operand.push(stoi(number));
        while (!stk_operator.empty())
        {
            char op = stk_operator.top();
            stk_operator.pop();
            b = stk_operand.top();
            stk_operand.pop();
            a = stk_operand.top();
            stk_operand.pop();
            stk_operand.push(map_func[op](a, b));
        }
        return stk_operand.top();
    }
};

int main()
{
    string s;
    Solution S;
    getline(cin, s);
    cout << S.calculate(s);
    return 0;
}