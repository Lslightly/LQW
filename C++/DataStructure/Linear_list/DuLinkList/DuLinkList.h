#ifndef DULINKLIST_H_
#define DULINKLIST_H_ 1
//  双向循环链表
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

typedef struct DuLNode
{
    ElemType data;
    struct DuLNode * prior;
    struct DuLNode * next;
}DuLNode, * DuLinkList;

int ListLength_DuL(DuLinkList L)
{
    DuLinkList p = L->next;
    int length = 0;
    while (p != L)
    {
        ++length;
        p = p->next;
    }
    return length;
}

DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
    int length = ListLength_DuL(L);
    if (i > length+1 || i <= 0) return nullptr;

    DuLinkList p = L;
    while (i)
    {
        p = p->next;
        --i;
    }
    return p;
}


//  在带头结点的双链循环线性表中第i个位置前插入元素e
//  i的合法值为1<=i<=length+1
Status ListInsert_DuL(DuLinkList &L, int i, ElemType e)
{
    DuLinkList p;
    if (!(p = GetElemP_DuL(L, i)))  //  在L中确定插入位置指针p
        return ERROR;               //  i等于表长+1时，p指向头结点；大于表长+1时，p=NULL
    
    DuLinkList s;
    if (!(s = (DuLinkList)malloc(sizeof(*s)))) return ERROR;
    s->data = e;
    s->prior = p->prior; p->prior = s;
    s->next = p; s->prior->next = s;
    return OK;
}

//  删除带头结点的双链循环线性表第i个元素，i的合法值为1<=i<=length
Status ListDelete_DuL(DuLinkList &L, int i, ElemType &e)
{
    DuLinkList p;
    if (!(p = GetElemP_DuL(L, i))) return ERROR;

    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}

#endif
