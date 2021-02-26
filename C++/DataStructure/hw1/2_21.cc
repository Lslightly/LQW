#include "../Linear_list/Sequence_List/Sqlist.h"

template<class Type>
Status ReverseSqList(SqList<Type> &L)
{
    int boundary = L.length-1;
    int mid = (boundary+1)/2;
    int i;
    for (i = 0; i < mid; i++)
    {
        L.elem[i] += L.elem[boundary-i];
        L.elem[boundary-i] += L.elem[i];
        L.elem[i] -= L.elem[boundary -i];
        L.elem[boundary-i] += 2*L.elem[i];
        L.elem[i] = -L.elem[i];
    }
}