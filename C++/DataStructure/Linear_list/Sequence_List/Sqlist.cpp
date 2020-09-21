#include "Sqlist.h"

template <class Type>
SqList<Type>::SqList()
{
    elem = new Type[LIST_INIT_SIZE];
    length = 0;
    listsize = LIST_INIT_SIZE;
}

template <class Type>
SqList<Type>::~SqList()
{
    delete[] elem;
    free(listsize);
    free(length);
}

template <class Type>
void SqList<Type>::ClearList(void)
{
    delete[] elem;
    elem = new Type[LIST_INIT_SIZE];
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
        return elem[i];
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

bool equal(const int a, const int b)
{
    return a == b;
}

template <class Type>
bool SqList<Type>::NextElem(const Type cur_e, Type &next_e)
{
    int cur_i = LocateElem(cur_e, equal);
    if (cur_i == length-1)
    {
        return false;
    }
    else
    {
        next_e = elem[cur_i+1];
        return true;
    }
    return false;
}

template <class Type>
bool SqList<Type>::ListInsert(const int i, const Type e)
{

}