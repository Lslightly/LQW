#include <stdlib.h>
#include "Sqlist.h"

template <class Type>
SqList<Type>::SqList()
{
    elem = (Type *)malloc(sizeof(Type) * LIST_INIT_SIZE);
    length = 0;
    listsize = LIST_INIT_SIZE;
}

template <class Type>
SqList<Type>::~SqList()
{
    free(elem);
}

template <class Type>
void SqList<Type>::ClearList(void)
{
    free(elem);
    elem = (Type *)malloc(sizeof(Type) * LIST_INIT_SIZE);
    length = 0;
    listsize = LIST_INIT_SIZE;
}

template <class Type>
bool SqList<Type>::ListEmpty(void)
{
    return length == 0;
}

template <class Type>
int SqList<Type>::ListLength(void)
{
    return length;
}

template <class Type>
bool SqList<Type>::GetElem(const int i, Type &e)
{
    if (i >= length)
    {
        return false;
    }
    else
    {
        e = elem[i];
        return true;
    }
}

template <class Type>
int SqList<Type>::LocateElem(const Type e, bool (*compare)(const Type a, const Type b))
{
    for (int i = 0; i < length; i++)
    {
        if (compare(elem[i], e))
        {
            return i;
        }
    }
    return -1;
}

bool equal(const int a, const int b)
{
    return a == b;
}

template <class Type>
bool SqList<Type>::PriorElem(const Type cur_e, Type &pre_e)
{
    int cur_i = LocateElem(cur_e, equal);
    if (cur_i == 0)
    {
        return false;
    }
    else
    {
        pre_e = elem[cur_i - 1];
        return true;
    }
    return false;
}

template <class Type>
bool SqList<Type>::NextElem(const Type cur_e, Type &next_e)
{
    int cur_i = LocateElem(cur_e, equal);
    if (cur_i == length - 1)
    {
        return false;
    }
    else
    {
        next_e = elem[cur_i + 1];
        return true;
    }
    return false;
}

template <class Type>
bool SqList<Type>::ListInsert(int i, const Type e)
{
    if (i < 0 || i > length)
    {
        return false;
    }
    if (length >= listsize)
    {
        Type *newbase = (Type *)realloc(elem, sizeof(Type) * (LIST_INIT_SIZE + LISTINCREMENT));
        if (!newbase)
        {
            return false;
        }
        elem = newbase;
        listsize += LISTINCREMENT;
    }
    for (int j = length - 1; j >= i; j--)
    {
        elem[j + 1] = elem[j];
    }
    elem[i] = e;
    length++;
    return true;
}

template <class Type>
bool SqList<Type>::ListDelete(const int i, Type &e)
{
    if (i < 0 || i >= length)
    {
        return false;
    }
    e = elem[i];
    for (int j = i; j < length - 1; j++)
    {
        elem[j] = elem[j + 1];
    }
    length--;
    return true;
}

template <class Type>
bool SqList<Type>::ListTraverse(bool (*visit)(Type &e))
{
    for (int i = 0; i < length; i++)
    {
        if (visit(elem[i]) == false)
        {
            return false;
        }
    }
    return true;
}
