#ifndef DULINKLIST_H_
#define DULINKLIST_H_ 1
//  双向链表
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



#endif
