#ifndef GLIST2_H_
#define GLIST2_H_ 1
//  广义表的拓展线性链表存储表示
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int AtomType;

typedef enum
{
    ATOM,
    LIST
} ElemTag;
typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct GLNode * hp;     //  表结点表头指针
    };
    struct GLNode * tp;         //  相当于next域，指向下一个元素
} * GList;

#endif