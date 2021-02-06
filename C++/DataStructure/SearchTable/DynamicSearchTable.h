#ifndef DSTABLE_H_
#define DSTABLE_H_ 1
//  动态查找
#include <stdlib.h>
#include "../Tree/BiTree.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define MAX_SEARCH_NUM 100
// typedef float KeyType;
typedef int KeyType;
// typedef char * KeyType;

typedef struct
{
    KeyType key;
}SElemType;

#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))

// #define EQ(a, b) (!strcmp((a), (b)))
// #define LT(a, b) (strcmp((a), (b)) < 0)
// #define LQ(a, b) (strcmp((a), (b)) <= 0)

BiTree SearchBST(BiTree T, KeyType key)
{
    if (!T || EQ(T->data, key)) return T;
    else if (LT(T->data, key)) return SearchBST(T->rchild, key);
    else return SearchBST(T->lchild, key);
}

//  f指向T的双亲
//  若查找成功，p返回数据结点指针，返回TRUE
//  否则p返回路径上最后一个结点，返回FALSE
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p)
{
    if (!T) //  查找不成功
    {
        p = f;
        return FALSE;
    }
    else if (EQ(T->data, key))
    {
        p = T;
        return TRUE;
    }
    else if (LT(T->data, key))
    {
        return SearchBST(T->rchild, key, T, p);
    }
    else
    {
        return SearchBST(T->lchild, key, T, p);
    }
}

Status InsertBST(BiTree &T, SElemType e)
{
    BiTree p, s;
    if (!SearchBST(T, e.key, nullptr, p))
    {
        s = (BiTree)malloc(sizeof(*s));
        s->data = e.key;
        s->lchild = s->rchild = nullptr;
        if (!p) T = s;
        else if (LT(p->data, s->data)) p->rchild = s;
        else p->lchild = s;
        return TRUE;
    }
    else return FALSE;
}
#endif