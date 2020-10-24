#ifndef LINKLIST_H_
#define LINKLIST_H_
#include <stdio.h>
template <class Type>
class LNode
{
public:
    Type data;
    LNode<Type> *next;
    LNode();
    LNode(Type e); //  创建data=e结点
    ~LNode();
};

template <class Type>
class LinkList
{
public:
    LNode<Type> *head;
    LNode<Type> *tail;
    int len;

    void PrintList();                                        //  打印链表
    LinkList();                                              //  构造空线性链表
    ~LinkList();                                             //  销毁链表
    void ClearList(void);                                    //  将链表重置为空
    void InsFirst(LNode<Type> *ins);                         //  将ins插入头结点之后
    LNode<Type> *DelFirst(void);                             //  删除第一个结点并返回指针
    void Append(LNode<Type> *s);                             //  将s所指的一串结点链接到尾结点后
    LNode<Type> *Remove(void);                               //  删除尾结点并返回
    void InsBefore(LNode<Type> *p, LNode<Type> *s);          //  p为链表中已知结点，s要插入p前面，p指向新插入的结点
    void InsAfter(LNode<Type> *p, LNode<Type> *s);           //  p为链表中已知结点，s要插入p后面，p指向新插入的结点
    void SetCurElem(LNode<Type> *p, Type e);                 //  p为链表中已知结点，用e更新p的data
    Type GetCurElem(LNode<Type> *p);                         //  p为链表中已知结点，返回p->data
    bool ListEmpty(void);                                    //  返回链表是否为空，空true
    int ListLength(void);                                    //  返回链表长度
    LNode<Type> *GetHead(void);                              //  返回头结点位置
    LNode<Type> *GetTail(void);                              //  返回尾结点位置
    LNode<Type> *PriorPos(LNode<Type> *p);                   //  返回p直接前驱的位置, nullptr之前设为tail
    LNode<Type> *NextPos(LNode<Type> *p);                    //  返回p直接后驱的位置
    bool LocatePos(int i, LNode<Type> *&p);                  //  用p返回第i个结点的位置,返回true; 若i不合法，返回false, p = nullptr
    bool GetElem(const int i, Type &e);                      //  返回第i个结点的data
    LNode<Type> *LocateElem(const Type e, int (*compare)(const Type a, const Type b)); //  返回与e匹配的结点位置，若不匹配，返回nullptr
    bool ListTraverse(bool (*visit)());
};

template <class Type>
LinkList<Type>::LinkList()
{
    head = new LNode<Type>;
    head->next = nullptr;
    tail = head;
    len = 0;
}

template <class Type>
LinkList<Type>::~LinkList()
{
    LNode<Type> *p = head;
    LNode<Type> *s = nullptr;
    while (p != nullptr)
    {
        s = p->next;
        delete p;
        p = s;
    }
}

template <class Type>
void LinkList<Type>::ClearList(void)
{
    LNode<Type> *p = head->next;
    LNode<Type> *temp = nullptr;
    while (p != nullptr)
    {
        temp = p->next;
        delete p;
        p = temp;
    }
}

template <class Type>
void LinkList<Type>::InsFirst(LNode<Type> *ins)
{
    if (ins != nullptr)
    {
        LNode<Type> *p = head->next;
        head->next = ins;
        ins->next = p;
        if (p == nullptr)
        {
            tail = ins;
        }
        ++len;
    }
}

template <class Type>
LNode<Type> *LinkList<Type>::DelFirst(void)
{
    LNode<Type> *p = head->next;
    if (p != nullptr)
    {
        head->next = p->next;
        if (tail == p)
        {
            tail == head;
        }
        --len;
    }
    head->next = p->next;
    return p;
}

template <class Type>
void LinkList<Type>::Append(LNode<Type> *s)
{
    tail->next = s;
    while (s != nullptr)
    {
        tail = s;
        ++len;
        s = s->next;
    }
}

template <class Type>
LNode<Type> *LinkList<Type>::Remove(void)
{
    if (head == tail)
        return nullptr; //  不允许删除头结点
    LNode<Type> *p = head;
    while (p != nullptr && p->next != tail)
    {
        p = p->next;
    }
    LNode<Type> *s = p->next;
    p->next = tail->next;
    --len;
    return s;
}

template <class Type>
void LinkList<Type>::InsBefore(LNode<Type> *p, LNode<Type> *s)
{
    LNode<Type> *p1 = head;
    while (p1 != nullptr && p1->next != p)
    {
        p1 = p1->next;
    }
    LNode<Type> *temp = p1->next;
    p1->next = s;
    s->next = temp;
    p = s;
    ++len;
}

template <class Type>
void LinkList<Type>::InsAfter(LNode<Type> *p, LNode<Type> *s)
{
    LNode<Type> *temp = p->next;
    p->next = s;
    s->next = temp;
    ++len;
    p = s;
}

template <class Type>
void LinkList<Type>::SetCurElem(LNode<Type> *p, Type e)
{
    p->data = e;
}

template <class Type>
Type LinkList<Type>::GetCurElem(LNode<Type> *p)
{
    return p->data;
}

template <class Type>
bool LinkList<Type>::ListEmpty(void)
{
    if (len == 0)
        return true;
    else
        return false;
}

template <class Type>
int LinkList<Type>::ListLength(void)
{
    return len;
}

template <class Type>
LNode<Type> *LinkList<Type>::GetHead(void)
{
    return head;
}

template <class Type>
LNode<Type> *LinkList<Type>::GetTail(void)
{
    return tail;
}

template <class Type>
LNode<Type> *LinkList<Type>::PriorPos(LNode<Type> *p)
{
    if (p == nullptr)
        return tail; //  nullptr前设为tail
    LNode<Type> *s = head;
    while (s != nullptr && s->next != p)
    {
        s = s->next;
    }
    return s;
}

template <class Type>
LNode<Type> *LinkList<Type>::NextPos(LNode<Type> *p)
{
    return p->next;
}

template <class Type>
bool LinkList<Type>::LocatePos(int i, LNode<Type> *&p)
{
    if (i > len)
    {
        p = nullptr;
        return false;
    }
    else
    {
        LNode<Type> *s = head;
        for (int j = 0; j < i; j++)
        {
            s = s->next;
        }
        p = s;
        return true;
    }
}

template <class Type>
bool LinkList<Type>::GetElem(const int i, Type &e)
{
    LNode<Type> *p = nullptr;
    if (LocatePos(i, p))
    {
        e = p->data;
        return true;
    }
    else
    {
        e = 0;
        return false;
    }
}

template <class Type>
LNode<Type> *LinkList<Type>::LocateElem(const Type e, int (*compare)(const Type a, const Type b))
{
    LNode<Type> *p = head->next;
    while (p != nullptr)
    {
        if ((*compare)(p->data, e))
            return p;
        p = p->next;
    }
    return p;
}

template <class Type>
bool LinkList<Type>::ListTraverse(bool (*visit)())
{
    LNode<Type> *p = head->next;
    while (p != nullptr)
    {
        if (!(*visit)(p->data))
            return false;
    }
    return true;
}

template <class Type>
LNode<Type>::LNode()
{
    next = nullptr;
}

template <class Type>
LNode<Type>::LNode(Type e)
{
    data = e;
    next = nullptr;
}

template <class Type>
LNode<Type>::~LNode()
{
    next = nullptr;
}

template <class Type>
void LinkList<Type>::PrintList(void)
{
    LNode<int> *p = head->next;
    while (p != nullptr)
    {
        printf("%d->", p->data);
        p = p->next;
    }
    printf(" %d\n", len);
}
#endif