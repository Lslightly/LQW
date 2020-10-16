#ifndef QUEUE_H_
#define QUEUE_H_
#include "../../Linear_list/LinkList/LinkList.h"

typedef struct customer
{
    int arrival_time;
    int amount;
    int duration;
}Customer;

template <class Type>
class Queue : public LinkList<Customer>
{
public:
    Queue();
    void ClearQueue();                   //  清空队列
    bool QueueEmpty();                   //  队列为空，返回true;否则返回false
    int QueueLength();                   //  返回元素个数
    bool GetHead(Type &e);               //  若队列不空，e返回对头元素；否则返回false;
    bool EnQueue(Type e);                //  插入队尾，插入失败返回false;
    bool DeQueue(Type &e);               //  队不空，删除并返回队头元素，返回true，否则返回false；
    bool QueueTraverse(bool (*visit)()); //  对队列中每个元素执行*visit, 若失败，返回false
};

template <class Type>
Queue<Type>::Queue()
{
    head = new LNode<Type>;
    head->next = nullptr;
    tail = head;
}

template <class Type>
void Queue<Type>::ClearQueue()
{
    LNode<Type> *p = head->next;
    LNode<Type> *s = nullptr;
    while (p != nullptr)
    {
        DeQueue();
    }
}

template <class Type>
bool Queue<Type>::QueueEmpty()
{
    return head->next == nullptr;
}

template <class Type>
int Queue<Type>::QueueLength()
{
    LNode<Type> *p = head;
    int len = 0;
    while (p->next != nullptr)
    {
        ++len;
        p = p->next;
    }
    return len;
}

template <class Type>
bool Queue<Type>::GetHead(Type &e)
{
    if (QueueEmpty())
        return false;
    e = head->next->data;
    return true;
}

template <class Type>
bool Queue<Type>::EnQueue(Type e)
{
    LNode<Type> *p = new LNode<Type>;
    if (p == nullptr)
        return false;
    *p = LNode<Type>(e);
    tail->next = p;
    p->next = nullptr;
    tail = p;
    return true;
}

template <class Type>
bool Queue<Type>::DeQueue(Type &e)
{
    if (QueueEmpty())
    {
        return false;
    }
    else
    {
        LNode<Type> *p = head->next;
        e = p->data;
        head->next = p->next;
        delete p;
        return true;
    }
}

template <class Type>
bool Queue<Type>::QueueTraverse(bool (*visit)())
{
    return ListTraverse(visit);
}
#endif