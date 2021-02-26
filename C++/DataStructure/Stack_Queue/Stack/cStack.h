#ifndef CSTACK_H_
#define CSTACK_H_
//  Stack
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

#define STACK_INIT_SIZE 100 //  初始分配量
#define STACKINCREMENT 10   //  存储空间增量



typedef char SElemType;

typedef struct
{
    SElemType * base;
    SElemType * top;
    int stacksize;
}SqStack;

//  构造空栈
Status InitStack(SqStack &S);
//  销毁栈
Status DestroyStack(SqStack &S);
//  把S置为空栈
Status ClearStack(SqStack &S);
//  若S为空栈，返回TRUE，否则返回FALSE
Status StackEmpty(SqStack S);
//  返回S的元素个数
int StackLength(SqStack S);
//  用e返回栈顶元素，如果栈空，则返回ERROR
Status GetTop(SqStack S, SElemType &e);
//  插入元素e为新栈顶元素
Status Push(SqStack &S, SElemType e);
//  若栈不空，则删除栈顶元素，用e返回其值，否则返回ERROR
Status Pop(SqStack &S, SElemType &e);
//  遍历
Status StackTraverse(SqStack S, Status (*visit)());

Status InitStack(SqStack & S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(*S.base));
    if (!S.base) exit(-1);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status StackEmpty(SqStack S)
{
    if (S.top == S.base) return TRUE;
    else return FALSE;
}

int StackLength(SqStack S)
{
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType & e)
{
    if (S.top == S.base) return ERROR;
    e = *(S.top-1);
    return OK;
}

int Push(SqStack & S, SElemType e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base, sizeof(*S.base)*(S.stacksize+STACKINCREMENT));
        if (!S.base) exit(-1);
        S.top = S.base+S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *(S.top++) = e;
    return OK;
}

int Pop(SqStack & S, SElemType & e)
{
    if (S.top == S.base) return ERROR;
    e = *(--S.top);
    return OK;
}

Status ClearStack(SqStack & S)
{
    S.top = S.base;
    return OK;
}

Status DestroyStack(SqStack &S)
{
    free(S.base);
    return OK;
}


#endif
