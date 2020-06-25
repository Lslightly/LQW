#include <stdio.h>
#include <stdlib.h>
typedef struct std
{
    int id;
    struct std *before;
    struct std *next;
} S;
int main(void)
{
    S *head, *p, *pnew, *pbefore, *phead, *tail;
    int n, num = 0;
    head = (S *)malloc(sizeof(S));
    tail = head;
    tail->next = NULL;
    while ((scanf("%d", &n)) != EOF)
    {
        pnew = (S *)malloc(sizeof(S));
        pnew->before = tail;
        pnew->next = NULL;
        pnew->id = n;
        tail->next = pnew;
        tail = pnew;
        num++;
    }
    pnew = (S *)malloc(sizeof(S));
    pnew->before = tail;
    pnew->next = NULL;
    tail->next = pnew;
    tail = pnew;

    p = head->next;
    while (p->next != tail)
    {
        for (; p->next != tail;)
        {
            if (p->id > p->next->id)
            {
                p->before->next = p->next;
                p->next->before = p->before;
                p->before = p->next;
                p->next = p->next->next;
                p->next->before = p;
                p->before->next = p;
            }
            else
            {
                p = p->next;
            }
        }
        tail = tail->before;
        p = head->next;
    }
    p=head->next;
    while (p->next->next!=NULL)
    {
        printf("%d ",p->id);
        p=p->next;
    }
    printf("%d",p->id);
    return 0;
}
