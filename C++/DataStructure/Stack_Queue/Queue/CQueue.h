#ifndef CQUEUE_H_
#define CQUEUE_H_ 1
//  Queue
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

//  构造一个空队列Q
Status InitQueue(LinkQueue &Q);
//  销毁队列Q
Status DestroyQueue(LinkQueue &Q);
//  将Q清为空队列
Status ClearQueue(LinkQueue &Q);
//  若队列Q为空队列，则返回TRUE，否则返回FALSE
Status QueueEmpty(LinkQueue &Q);
//  返回队列长度
int QueueLength(LinkQueue Q);
//  若队列不空，则用e返回队头，返回OK；否则返回ERROR
Status GetHead(LinkQueue Q, QElemType &e);
//  入队
Status EnQueue(LinkQueue &Q, QElemType e);
//  若队不空，出队以e返回，返回OK；否则返回ERROR
Status DeQueue(LinkQueue &Q, QElemType &e);
//  遍历
Status QueueTraverse(LinkQueue Q, Status (*visit)());


Status InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(*Q.front));
    if (!Q.front) exit(OVERFLOW);
    Q.front->next = nullptr;
    return OK;
}
Status DestroyQueue(LinkQueue &Q)
{
    ClearQueue(Q);
    free(Q.front);
    return OK;
}
Status ClearQueue(LinkQueue &Q)
{
    QueuePtr p = Q.front->next;
    while (p)
    {
        Q.rear = p->next;
        free(p);
        p = Q.rear;
    }
    Q.rear = Q.front;
    Q.front->next = nullptr;
    return OK;
}
Status QueueEmpty(LinkQueue &Q)
{
    if (Q.rear == Q.front) return TRUE;
    else return FALSE;
}
int QueueLength(LinkQueue Q)
{
    int len = 0;
    QueuePtr p = Q.front->next;
    while (p)
    {
        ++len;
        p = p->next;
    }
    return len;
}
Status GetHead(LinkQueue Q, QElemType &e)
{
    if (QueueEmpty(Q)) return ERROR;
    e = Q.front->next->data;
    return OK;
}
Status EnQueue(LinkQueue &Q, QElemType e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(*p));
    if (!p) return ERROR;
    p->data = e;
    p->next = nullptr;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}
Status DeQueue(LinkQueue &Q, QElemType &e)
{
    if (QueueEmpty(Q)) return ERROR;
    e = Q.front->next->data;
    QueuePtr p = Q.front->next;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;  //  如果刚好删除最后一个元素，则需要将rear置为front
    free(p);
    return OK;
}
Status QueueTraverse(LinkQueue Q, Status (*visit)())
{
    QueuePtr p = Q.front->next;
    while (p)
    {
        if ((*visit)() == FALSE) return FALSE;
    }
    return TRUE;
}
#endif