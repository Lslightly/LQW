#ifndef SQQUEUE_H_
#define SQQUEUE_H_ 1
//  循环队列，空余一个位置来判断队列是空还是满
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int QElemType;

#define MAXQSIZE 100
typedef struct
{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

Status InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(sizeof(*Q.base) * MAXQSIZE);
    if (!Q.base) exit(OVERFLOW);
    Q.front = Q.rear = 0;
    return OK;
}

int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

Status QueueEmpty(SqQueue Q)
{
    if (Q.front == Q.rear) return TRUE;
    else return FALSE;
}

Status QueueFull(SqQueue Q)
{
    if ((Q.rear+1)%MAXQSIZE == Q.front) return TRUE;
    else return FALSE;
}

Status EnQueue(SqQueue &Q, QElemType e)
{
    if (QueueFull(Q)) return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e)
{
    if (QueueEmpty(Q)) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front+1)%MAXQSIZE;
    return OK;
}

#endif