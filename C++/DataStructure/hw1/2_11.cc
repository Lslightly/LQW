#include "../Linear_list/Sequence_List/Sqlist.h"

template <class Type>
Status Insert_in_order(SqList<Type> &va, Type e)
{
    int i, j;
    if (va.length >= va.listsize)
    {
        if (!va.elem = (Type *)realloc(va.elem, (va.listsize+LISTINCREMENT) * sizeof(Type)))
            exit(OVERFLOW);
        va.listsize += LISTINCREMENT;
    }
    for (i = 0; i < va.length && va.elem[i] < e; i++)
        ;
    va.length += 1;
    for (j = va.length-1; j > i; j--)   va.elem[j] = va.elem[j-1];
    va.elem[j] = e;
    return OK;
}
