#ifndef TWSTACK_H_
#define TWSTACK_H_ 1
//  双向栈
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

#define TWSTACK_INIT_SIZE 100
#define TWSTACK_INCREMENT 10

typedef int ElemType;

typedef struct
{
    ElemType * left_base, *left_top, *right_base, *right_top;
    int stacksize;
}TWStack;

Status InitTWStack(TWStack &S)
{
    if (!(S.left_base = (ElemType *)malloc(sizeof(ElemType) * TWSTACK_INIT_SIZE)))
        exit(OVERFLOW);
    S.stacksize = TWSTACK_INIT_SIZE;
    S.left_top = S.left_base;
    S.right_base = S.left_base+TWSTACK_INIT_SIZE-1;
    S.right_top = S.right_base;
    return OK;
}

Status Push(TWStack &S, int i, ElemType e)
{
    if (i != 1 || i != 2) return ERROR;
    if (S.right_top < S.left_top)
    {
        int left_len = S.left_top - S.left_base, right_len = S.right_base-S.right_top;
        if (!(S.left_base = (ElemType *)realloc(S.left_base, sizeof(ElemType) * (S.stacksize+TWSTACK_INCREMENT))))
            exit(OVERFLOW);
        
        //  S.left_base may point to another place after realloc, so S.left_top & S.right_base & S.right_top must be updated
        S.left_top = S.left_base + left_len;
        S.right_base = S.left_base + S.stacksize-1;
        S.right_top = S.right_base - right_len;

        S.stacksize += TWSTACK_INCREMENT;
        for (ElemType * p = S.right_base; p > S.right_top; p--)
            *(p+TWSTACK_INCREMENT) = *p;
        S.right_top += TWSTACK_INCREMENT;
        S.right_base += TWSTACK_INCREMENT;
    }
    if (i == 1)
    {
        *(S.right_top--) = e;
    }
    else
    {
        *(S.left_top++) = e;
    }
    return OK;
}

Status Pop(TWStack &S, int i, ElemType &e)
{
    if (i == 0)
    {
        if (S.left_base == S.left_top) return ERROR;
        else
        {
            e = *(--S.left_top);
            return OK;
        }
    }
    else
    {
        if (S.right_base == S.right_top) return ERROR;
        else
        {
            e = *(++S.right_top);
            return OK;
        }
    }
}

#endif