#include <stdio.h>
#include "LinkList.h"

int main(void)
{
    LinkList<int> list_a = LinkList<int>();

    int n = 0, temp = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp);
        LNode<int> * p = new LNode<int>;
        p->data = temp; 
        list_a.InsFirst(p);
    }
    list_a.PrintList();

    LinkList<int> list_b = LinkList<int>();
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp);
        LNode<int> * p = new LNode<int>;
        p->data = temp;
        list_b.InsFirst(p);
    }
    list_b.PrintList();

    list_a.Append(list_b.GetHead()->next);
    list_a.PrintList();

    list_a.Remove();
    list_a.PrintList();

    return 0;
}
