#ifndef TRUELINKLIST_H_
#define TRUELINKLIST_H_ 1
//  实际应用链表
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
    struct LNode *next;
}*Link, *Position;

typedef struct
{
    Link head, tail;
    int length;
}LinkList;

//  分配由p指向的值为e的结点，并返回OK；若分配失败，则返回ERROR
Status MakeNode(Link &p, ElemType e);

//  释放p所指向的结点
void FreeNode(Link &p);

//  构造一个空的线性链表L
Status InitList(LinkList &L);

//  销毁线性链表L，L不再存在
Status DestroyList(LinkList &L);

//  将线性链表重置为空表，并且释放原链表的结点空间
Status ClearList(LinkList &L);

//  已知h指向线性表的头结点，将s所指结点插入在第一个结点之前
Status InsFirst(LinkList &L, Link h, Link s);

//  已知h指向线性表的头结点，删除链表中第一个结点并以q返回
Status DelFirst(LinkList &L, Link h, Link &q);

//  将指针s所指的一串结点链接在L的最后一个结点后面，并改变L的尾指针以指向新的尾结点
Status Append(LinkList &L, Link s);

//  删除线性链表L的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Status Remove(LinkList &L, Link &q);

//  已知p指向线性链表L的一个结点，将s所指结点插入在p所指结点之前，并修改指针p指向新插入的结点
Status InsBefore(LinkList &L, Link &p, Link s);

//  已知p指向线性链表L的一个结点，将s所指结点插入在p所指结点之后，并修改指针p指向新插入的结点
Status InsAfter(LinkList &L, Link &p, Link s);

//  已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
Status SetCurElem(Link &p, ElemType e);

//  已知p指向线性链表中一个结点，返回p所指结点中数据元素的值
ElemType GetCurElem(Link p);

//  若线性链表为空，则返回TRUE，否则返回FALSE
Status ListEmpty(LinkList L);

//  返回线性链表L的元素个数
int ListLength(LinkList L);

//  返回线性链表L中头结点的位置
Position GetHead(LinkList L);

//  返回线性链表L尾结点的位置
Position GetTail(LinkList L);

//  已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，若无直接前驱，返回NULL
Position PriorPos(LinkList L, Link p);

//  已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置，若无直接前驱，返回NULL
Position NextPos(LinkList L, Link p);

//  返回p指示线性链表L中第i个结点的位置并返回OK，i不合法时返回ERROR
Status LocatePos(LinkList L, int i, Link &p);

//  返回线性链表L中第一个与e满足函数*compare判定关系的元素的位置，若不存在，返回NULL
Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType));

//  依次对L的每个元素调用visit()。一旦visit()失败，则操作失败
Status ListTraverse(LinkList L, Status (*visit)(Link &p));


Status MakeNode(Link &p, ElemType e)
{
    p = (Link)malloc(sizeof(*p));
    if (!p) return ERROR;
    p->data = e;
    p->next = nullptr;
}
void FreeNode(Link &p)
{
    free(p);
}
Status InitList(LinkList &L)
{
    L.head = (Link)malloc(sizeof(*L.head));
    if (!L.head) return ERROR;
    L.head->next = nullptr;
    L.tail = L.head;
    L.length = 0;
    return OK;
}
Status DestroyList(LinkList &L)
{
    ClearList(L);
    free(L.head);
    L.head = L.tail = nullptr;
    L.length = 0;
    return OK;
}
Status ClearList(LinkList &L)
{
    Link p = L.head->next;
    Link p_next = nullptr;
    while (p)
    {
        p_next = p->next;
        free(p);
        p = p_next;
    }
    L.tail = L.head;
    L.length = 0;
    return OK;
}
Status InsFirst(LinkList &L, Link h, Link s)
{
    s->next = h->next;
    h->next = s;
    L.length++;
    return OK;
}
Status DelFirst(LinkList &L, Link h, Link &q)
{
    q = h->next;
    h->next = q->next;
    q->next = nullptr;
    L.length--;
    return OK;
}
Status Append(LinkList &L, Link s)
{
    int s_len = 0;
    Link p = s;
    Link p_pre = nullptr;
    while (p)
    {
        ++s_len;
        p_pre = p;
        p = p->next;
    }
    L.length += s_len;

    L.tail->next = s;
    if (p_pre) L.tail = p_pre;
    return OK;
}
Status Remove(LinkList &L, Link &q)
{
    if (L.length == 0) return ERROR;
    q = L.tail;
    Link p = L.head;
    while (p->next != L.tail)
    {
        p = p->next;
    }
    L.tail = p;
    --L.length;
    return OK;
}
Status InsBefore(LinkList &L, Link &p, Link s)
{
    if (p == L.head) return ERROR;
    Link p_pre = PriorPos(L, p);
    if (!p_pre) return ERROR;
    s->next = p;
    p_pre->next = s;
    L.length++;
    p = s;
    return OK;
}
Status InsAfter(LinkList &L, Link &p, Link s)
{
    if (!p) return ERROR;
    if (p == L.tail) L.tail = s;
    s->next = p->next;
    p->next = s;
    p = s;
    L.length++;
    return OK;
}
Status SetCurElem(Link &p, ElemType e)
{
    p->data = e;
    return OK;
}
ElemType GetCurElem(Link p)
{
    return p->data;
}
Status ListEmpty(LinkList L)
{
    if (L.length == 0) return TRUE;
    else return FALSE;
}
int ListLength(LinkList L)
{
    return L.length;
}
Position GetHead(LinkList L)
{
    return L.head;
}
Position GetTail(LinkList L)
{
    return L.tail;
}
Position PriorPos(LinkList L, Link p)
{
    Link p_pre = L.head;
    while (p_pre->next != p)
    {
        p_pre = p_pre->next;
    }
    return p_pre;
}
Position NextPos(LinkList L, Link p)
{
    return p->next;
}
Status LocatePos(LinkList L, int i, Link &p)
{
    if (i < 1 || i > L.length) return ERROR;
    p = L.head;
    while (i)
    {
        p = p->next;
        --i;
    }
    return OK;
}
Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    Link p = L.head->next;
    while (p)
    {
        if ((*compare)(e, p->data) == TRUE) break;
    }
    return p;
}
Status ListTraverse(LinkList L, Status (*visit)(Link &p))
{
    Link p = L.head->next;
    while (p)
    {
        if ((*visit)(p) == FALSE) return FALSE;
    }
    return TRUE;
}
Status ListInsert_L(LinkList &L, int i, ElemType e)
{
    Link h, s;
    if (!LocatePos(L, i-1, h)) return ERROR;
    if (!MakeNode(s, e)) return ERROR;

    InsFirst(L, h, s);
    return OK;
}
Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc, Status (*compare)(ElemType, ElemType))
{
    if (!InitList(Lc)) return ERROR;
    Position ha = GetHead(La);
    Position hb = GetHead(Lb);
    Position pa = NextPos(La, ha);
    Position pb = NextPos(Lb, hb);
    while (pa && pb)
    {
        ElemType a = GetCurElem(pa);
        ElemType b = GetCurElem(pb);
        if ((*compare)(a, b) <= 0)
        {
            Link q;
            DelFirst(La, ha, q);
            Append(Lc, q);
            pa = NextPos(La, ha);
        }
        else
        {
            Link q;
            DelFirst(Lb, hb, q);
            Append(Lc, q);
            pb = NextPos(Lb, hb);
        }
    }
    if (pa) Append(Lc, pa);
    else Append(Lc, pb);

    FreeNode(ha);
    FreeNode(hb);
    return OK;
}
#endif