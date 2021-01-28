#ifndef MPLIST_H_
#define MPLIST_H_ 1
//  多元多项式
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef float AtomType;

typedef enum
{
    ATOM,
    LIST
} ElemTag;
typedef struct GLNode
{
    ElemTag tag;
    int exp;
    union
    {
        AtomType coef;  //  原子节点值域
        struct GLNode * hp;
    };
    struct GLNode *tp;
} * MPList;

#endif