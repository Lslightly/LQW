#include "../Linear_list/Sequence_List/Sqlist.h"

template<class Type>
Status DeleteSame(SqList<Type> &A, SqList<Type> &B, SqList<Type> &C)
{
    int i_a = 0, i_b = 0, i_c = 0;
    int deleted_len = 0;
    bool * is_deleted = (bool *)malloc((A.length) * sizeof(bool));
    while (i_a < A.length && i_b < B.length && i_c < C.length)
    {
        if (B.elem[i_b] < C.elem[i_c])  i_b++;
        else if (B.elem[i_b] > C.elem[i_c]) i_c++;
        else
        {
            if (A.elem[i_a] == B.elem[i_b])
            {
                is_deleted[i_a] = true;
                deleted_len++;
                i_a++;
            }
            else if (A.elem[i_a] > B.elem[i_b])
            {
                i_b++;
                i_c++;
            }
            else
            {
                is_deleted[i_a] = false;
                i_a++;
            }
        }
    }
    while (i_a < A.length)  is_deleted[i_a] = false;
    
    Type * new_elem = (Type *)malloc(sizeof(Type) * (A.length-deleted_len));
    int j = 0;
    for (i = 0; i < A.length; i++)
        if (!is_deleted[i])
        {
            new_elem[j] = A.elem[i];
            j++;
        }
    free(A.elem);
    A.elem = new_elem;
    return OK;
}