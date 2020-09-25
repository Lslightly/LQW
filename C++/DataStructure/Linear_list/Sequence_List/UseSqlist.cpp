#include <stdio.h>
#include "Sqlist.h"

int main(void)
{
    SqList<int> list= SqList<int>();
    
    int num = 0;
    int temp = 0;
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &temp);
        list.ListInsert(list.ListLength(), temp);
    }
    for (int i = 0; i < num; i++)
    {
        if (list.GetElem(i, temp))
        {
            printf("%d ", temp);
        }
    }
    printf("\n");
    return 0;
}