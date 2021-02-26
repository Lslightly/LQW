#ifndef DCLINKLIST_H_
#define DCLINKLIST_H_ 1
//  双向循环链表

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

typedef struct DCLNode
{
    struct DCLNode * prior, * next;
    ElemType data;
}DCLNode, *DCLinkList;

typedef struct FreqDCLNode
{
    struct FreqDCLNode *prior, *next;
    ElemType data;
    int freq;
}FreqDCLNode, *FreqLinkList;



#endif