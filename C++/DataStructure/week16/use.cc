#include <stdio.h>
#include "../Sort/Sort.h"

int main()
{
    SqList L;
    CreateSqList(L);
    MergeSort1(L);
    PrintSqList(L);
    return 0;
}

