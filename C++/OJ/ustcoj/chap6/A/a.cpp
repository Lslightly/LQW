//  mind:   reverse the input and deal with it in the normal way.
//          restrict the condition to add '(', ')'
//          "*" & "/" are prior to "+" & "-"
//          "+" & "-" are equal
//          "*" & "/" are equal

//  an example about how the program runs.
//  input:  12+34+*
//  reverse:    *+43+21
//  translate:  (4 + 3) * (2 + 1)
//  reverse:    (1 + 2) * (3 + 4)   (the answer)
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 20

char input[MAX_LENGTH] = ""; //  input

//  function:   translate the reversed input to a reversed normal expression
//              from the beginning to the end
//  parameters:
//              subscript:  the beginning subscript of a substring of input
//              expression: the changing expression
//              flag:   0   no need for ()
//                      1   the former operator is "+" / "-". if "+" / "-" are met, then () are needed
//                      2   the former operator is "*" / "/". () are needed whatever the operator
//                          met is
//  return:     the subscript after one translation operation
//
int translate(int subscript, char expression[20], int flag);

//  function:   translate the reversed input without () and change the subscript
//  parameters:
//              subscript:  the same value as subscript in function translate()
//              expression: the same value as ...
//              flag:       the level of priority of the operator
//              operator_specified: the operator to be written to the translaiton.
//  return:     the expression changed and the subscript changed for the convenience of the following
//              translation.
void no_brackets(int &subscript, char expression[MAX_LENGTH], int flag, const char operator_specified[2]);

//  the only difference between this function and the above one is that this function will add ()
void brackets(int &subscript, char expression[MAX_LENGTH], int flag, const char operator_specified[2]);

int main(void)
{
    scanf("%s", input); // scan the input

    int len = strlen(input);                // length of input
    for (int i = 0; i < (len + 1) / 2; i++) //  reverse the input
    {
        char temp = input[i];
        input[i] = input[len - 1 - i];
        input[len - 1 - i] = temp;
    }

    char ans[MAX_LENGTH] = ""; // the answer
    translate(0, ans, 0);      // the end subscript of input is length of input - 1

    int len_ans = strlen(ans);                  // length of answer
    for (int i = 0; i < (len_ans + 1) / 2; i++) // reverse the answer
    {
        char temp = ans[i];
        ans[i] = ans[len_ans - 1 - i];
        ans[len_ans - 1 - i] = temp;
        if (ans[i] == '(') // '(' -> ')', because the answer is reversed
        {
            ans[i] = ')';
        }
        else if (ans[i] == ')') // ')' -> '('
        {
            ans[i] = '(';
        }
        if (ans[len_ans - 1 - i] == '(')
        {
            ans[len_ans - 1 - i] = ')';
        }
        else if (ans[len_ans - 1 - i] == ')')
        {
            ans[len_ans - 1 - i] = '(';
        }
    }

    printf("%s", ans);
    return 0;
}

int translate(int subscript, char expression[MAX_LENGTH], int flag)
{
    char temp[2] = ""; // temporary string array (to make strcat easier)
    switch (input[subscript])
    {
        case '+':
        {
            if (flag > 0) // () needed. the former operator might be "+-*/"
            {
                brackets(subscript, expression, 0, "+");
                break;
            }
            else // () not needed
            {
                no_brackets(subscript, expression, 0, "+");
                break;
            }
        }
        case '-':
        {
            if (flag > 0)
            {
                brackets(subscript, expression, 0, "-");
                break;
            }
            else
            {
                no_brackets(subscript, expression, 0, "-");
                break;
            }
        }
        case '*':
        {
            if (flag > 1)
            {
                // + isn't prior to *. So only when flag > 1, which means the former operator is "*" / "/",
                // the () is needed
                brackets(subscript, expression, 1, "*");    // 1 means "+" & "-" need (), but it's uncertain for "*/"
                break;
            }
            else
            {
                no_brackets(subscript, expression, 1, "*");
                break;
            }
        }
        case '/':
        {
            if (flag > 1)
            {
                brackets(subscript, expression, 1, "/");
                break;
            }
            else
            {
                no_brackets(subscript, expression, 1, "/");
                break;
            }
        }
        default: // a number
        {
            temp[0] = input[subscript];
            temp[1] = '\0';
            strcat(expression, temp); // add the number
            break;
        }
    }
    return subscript;   //  the subscript stopped in the end of this translation, not the place after this end
}

void no_brackets(int &subscript, char expression[MAX_LENGTH], int flag, const char operator_specified[2])
{
    // eg: ++321 (+ and + is in the same level) = (3 + 2) + 1
    // 1.   3 + 2 need brackets
    // 2.   after (3+2), add "+"
    // 3.   assume that A = (3+2), A + 1 doesn't need brackets
    // subscript + 1 make the subscript move to the beginning of the rest
    subscript = translate(subscript + 1, expression, flag + 1); // 1
    strcat(expression, operator_specified);                     // 2
    subscript = translate(subscript + 1, expression, flag);     // 3
}

void brackets(int &subscript, char expression[MAX_LENGTH], int flag, const char operator_specified[2])
{
    //  similar to the above one
    strcat(expression, "(");
    subscript = translate(subscript + 1, expression, flag + 1);
    strcat(expression, operator_specified);
    subscript = translate(subscript + 1, expression, flag);
    strcat(expression, ")");
}