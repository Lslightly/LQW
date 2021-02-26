#include "../Linear_list/Sequence_List/Sqlist.h"
#include "../Stack_Queue/Stack/cStack.h"

Status isMatched(SqList<char> str)
{
    SqStack S;
    InitStack(S);
    int len = str.ListLength();
    for (int i = 0; i < len; i++)
    {
        char ch;
        str.GetElem(i, ch);
        if (ch == '(' || ch == '[' || ch == '{')
            Push(S, ch);
        else
        {
            if (StackEmpty(S) == TRUE) return FALSE;
            char top;
            Pop(S, top);
            switch (ch)
            {
            case '}':
                if (top != '{') return FALSE;
                break;
            case ']':
                if (top != '[') return FALSE;
                break;
            case ')':
                if (top != '(') return FALSE;
                break;
            default:
                return FALSE;
                break;
            }
        }
    }
    return StackEmpty(S);
}