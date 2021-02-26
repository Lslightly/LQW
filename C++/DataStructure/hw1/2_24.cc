#include "../Linear_list/CLinkList/LinkList.h"

Status MergeList(LinkList &C, LinkList &A, LinkList &B)
{
    LinkList pa = A->next, pb = B->next;
    LinkList pc = nullptr;
    LinkList temp_a, temp_b;
    while (pa && pb)
    {
        if (pa->data < pb->data)
        {
            C = pa;
            temp_a = pa->next;
            C->next = pc;
            pc = C;
            pa = temp_a;
        }
        else
        {
            C = pb;
            temp_b = pb->next;
            C->next = pc;
            pc = C;
            pb = temp_b;
        }
    }
    while (pa)
    {
        C = pa;
        temp_a = pa->next;
        C->next = pc;
        pc = C;
        pa = temp_a;
    }
    while (pb)
    {
        C = pb;
        temp_b = pb->next;
        C->next = pc;
        pc = C;
        pb = temp_b;
    }
    return OK;
}