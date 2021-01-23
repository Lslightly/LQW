#ifndef LINKLIST_H_
#define LINKLIST_H_ 1
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

typedef struct LNode
{
    ElemType data;
    struct LNode * next;
}LNode, *LinkList;

//  L为带头结点的单链表的头指针
//  当第i个元素存在时，赋给e并返回OK，否则返回ERROR
Status GetElem_L(LinkList L, int i, ElemType &e)
{
    LNode * p = L->next; int j = 1;
    while (p && j < i)
    {
        p = p->next; ++j;
    }
    if (!p || j > i)    return ERROR;   //  i不存在，即小于等于0
    e = p->data;
    return OK;
}

//  在带头结点的单链线性表第i个位置前插入元素e
Status ListInsert(LinkList &L, int i, ElemType e)
{
    LNode * p = L; int j = 0;
    while (p && j < i-1)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i-1) return ERROR;
    LinkList s = (LinkList)malloc(sizeof(*s));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//  在带头结点的单链线性表中删除第i个元素，由e返回其值
Status ListDelete_L(LinkList &L, int i, ElemType &e)
{
    LinkList p = L; int j = 0;
    while (p->next && j < i-1)    //  寻找第i个结点的前驱，循环结束后p为第i个结点的前驱
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i-1)    return ERROR; //  i的位置不合理
    LinkList q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return OK;
}

//  头插法
//  逆位序输入n个元素的值，建立带头结点的单链线性表L
void CreateList_L(LinkList &L, int n)
{
    L = (LinkList)malloc(sizeof(*L));
    L->next = nullptr;
    for (int i = n; i > 0; i--)
    {
        LinkList p = (LinkList)malloc(sizeof(*p));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
}

//  已知单链线性表La和Lb的元素按值非递减排列
//  归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
    LinkList pa = La->next; LinkList pb = Lb->next;
    LinkList pc;
    Lc = pc = La;   //  用La的头结点作为Lc的头结点
    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa; pc = pa; pa = pa->next;
        }
        else
        {
            pc->next = pb; pc = pb; pb = pb->next;
        }
    }
    pc->next = pa?pa:pb;    //  插入剩余段
    free(Lb);
}
#endif
