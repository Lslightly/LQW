#ifndef DLTREE_H_
#define DLTREE_H_ 1
//  键树、数字查找树
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef char Record;

#define MAXKEYLEN 16
typedef struct
{
    char ch[MAXKEYLEN];
    int num; //  关键字长度
} KeysType;
typedef enum
{
    LEAF,
    BRANCH
} NodeKind;
typedef struct DLTNode
{
    char symbol;
    struct DLTNode *next;
    NodeKind kind;
    union
    {
        Record *infoptr;       //  叶子结点的记录指针
        struct DLTNode *first; //  孩子链指针
    };
} DLTNode, *DLTree;

Record *SearchDLTree(DLTree T, KeysType K)
{
    DLTree p = T->first;
    int i = 0;
    while (p && i < K.num)
    {
        while (p && p->symbol < K.ch[i])
            p = p->next;
        if (p && p->symbol == K.ch[i])
        {
            p = p->first;
            ++i;
        }
        else
        {
            p = nullptr;
        }
    }
    if (p && p->kind == LEAF)
        return p->infoptr;
    else
        return nullptr;
}
#endif