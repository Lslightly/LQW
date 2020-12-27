#include "Sort.h"

int main(void)
{
    SqList L;
    CreateSqList(L);
    for (int i = 0; i < 5; i++)
    {
        int t;
        scanf("%d", &t);
        InsertHeap(L, {t, nullptr});
    }
    PrintSqList(L);
}