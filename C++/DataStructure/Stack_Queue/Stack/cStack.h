#include <stdlib.h>

#ifndef CSTACK_H_
#define CSTACK_H_


#define OVERFLOW -2
#define ERROR -1
#define OK 0
#define STACK_INIT_SIZE 100 //  初始分配量
#define STACKINCREMENT 10   //  存储空间增量



typedef int SElemType;

typedef struct
{
    SElemType * base;
    SElemType * top;
    int stacksize;
}SqStack;

int InitStack(SqStack & S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(*S.base));
    if (!S.base) return OVERFLOW;
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

bool StackEmpty(SqStack S)
{
    return S.top == S.base;
}

int StackLength(SqStack S)
{
    return S.top - S.base;
}

int GetTop(SqStack S, SElemType & e)
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
        if (!S.base) return OVERFLOW;
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

void ClearStack(SqStack & S)
{
    S.top = S.base;
}

int DestroyStack(SqStack &S)
{
    free(S.base);
    return OK;
}


#endif
