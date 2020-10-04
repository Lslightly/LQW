#include <stdio.h>
#include "Queue.h"

int main(void)
{
    Queue<int> a = Queue<int>();
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i< n; i++)
    {
        int temp = 0;
        scanf("%d", &temp);
        a.EnQueue(temp);
    }
    for (int i = 0; i < n; i++)
    {
        int e = 0;
        a.DeQueue(e);
        printf("%d ", e);
        if (!a.QueueEmpty())
            printf("not empty\n");
    }
    putchar('\n');
    return 0;
}