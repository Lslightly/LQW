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
bool SqList<Type>::GetElem(const int i, Type & e)
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
