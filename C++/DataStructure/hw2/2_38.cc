#include "../Linear_list/CLinkList/DCLinkList.h"

void Insert(FreqLinkList &L, FreqLinkList ins)
{
    FreqLinkList p = ins->prior;
    while (p != L && p->freq <= ins->freq) p = p->prior;
    ins->next = p->next;
    ins->prior = p;
    p->next = ins;
    ins->next->prior = p;
}

FreqLinkList Locate(FreqLinkList &L, ElemType x)
{
    FreqLinkList p = L->next;
    while (p->data != x)
        p = p->next;
    if (p != L)
    {
        p->freq++;
        p->prior->next = p->next;
        p->next->prior = p->prior;
        Insert(L, p);
    }
    return p;
}