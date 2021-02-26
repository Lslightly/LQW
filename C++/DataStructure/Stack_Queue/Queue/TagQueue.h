#ifndef TAGQUEUE_H_
#define TAGQUEUE_H_ 1
//  带tag域的循环队列，利用所有的空间
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define MAXQSIZE 100
template <typename QElemType>
struct TagQueue
{
    QElemType *base;
    int front, rear;
    bool tag;   //  0表示队头队尾相同时为空，1表示队头队尾相同时为满
};

template <typename QElemType>
Status InitQueue(TagQueue<QElemType> &Q)
{
    if (!(Q.base = (QElemType *)malloc(sizeof(QElemType) * MAXQSIZE)))
        exit(OVERFLOW);
    Q.front = Q.rear = 0;
    tag = 0;
}

template <typename QElemType>
int QueueLength(TagQueue<QElemType> &Q)
{
    return (Q.front-Q.rear+MAXQSIZE)%MAXQSIZE;
}

template <typename QElemType>
Status QueueEmpty(TagQueue<QElemType> Q)
{
    if (Q.front == Q.rear && Q.tag == 0) return TRUE;
    else return FALSE;

}

template <typename QElemType>
Status QueueFull(TagQueue<QElemType> Q)
{
    if (Q.front == Q.rear && Q.tag == 1) return TRUE;
    else return FALSE;
}

template <typename QElemType>
Status EnQueue(TagQueue<QElemType> &Q, QElemType e)
{
    if (QueueFull(Q) == TRUE) return ERROR;
    else
    {
        Q.base[Q.rear++] = e;
        Q.rear %= MAXQSIZE;
        if (Q.front == Q.rear) Q.tag = 1;
    }
    return OK;
}

template <typename QElemType>
Status DeQueue(TagQueue<QElemType> &Q, QElemType &e)
{
    if (QueueEmpty(Q) == TRUE) return ERROR;
    else
    {
        e = Q.base[Q.front++];
        Q.front %= MAXQSIZE;
        if (Q.front == Q.rear) Q.tag = 0;
    }
    return OK;
}

#endif