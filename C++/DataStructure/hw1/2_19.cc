#include "../Linear_list/CLinkList/LinkList.h"

Status DeleteRange(LinkList &L, int mink, int maxk)
{
    LNode *p = L->next;
    LNode *pre_p = L;
    while (p && p->data <= mink)
    {
        p = p->next;
        pre_p = pre_p->next;
    }
    while (p && p->data > mink && p->data < maxk)
    {
        pre_p->next = p->next;
        free(p);
        p = pre_p->next;
    }
    return OK;
}
