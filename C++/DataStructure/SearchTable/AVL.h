#ifndef AVL_H_
#define AVL_H_ 1
//  AVL Tree
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

typedef struct BSTNode
{
    SElemType data;
    int bf;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

void R_Rotate(BSTree &p)
{
    BSTree lc;
    lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

void L_Rotate(BSTree &p)
{
    BSTree rc;
    rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

#define LH +1
#define EH 0
#define RH -1

Status InsertAVL(BSTree &T, SElemType e, bool &taller)
{
    if (!T)
    {
        T = (BSTree)malloc(sizeof(*T));
        T->data = e;
        T->lchild = T->rchild = nullptr;
        T->bf = EH;
        taller = TRUE;
    }
    else
    {
        if (EQ(e.key, T->data.key))
        {
            taller = FALSE;
            return 0;
        }
        if (LT(e.key, T->data.key))
        {
            if (!InsertAVL(T->lchild, e, taller)) return 0;
            if (taller)
            {
                switch (T->bf)
                {
                case LH:
                    LeftBalance(T);
                    taller = FALSE;
                    break;
                case EH:
                    T->bf = LH;
                    taller = TRUE;
                    break;
                case RH:
                    T->bf = EH;
                    taller = FALSE;
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            if (!InsertAVL(T->rchild, e, taller)) return 0;
            if (taller)
            {
                switch (T->bf)
                {
                case LH:
                    T->bf = EH;
                    taller = FALSE;
                    break;
                case EH:
                    T->bf = RH;
                    taller = TRUE;
                    break;
                case RH:
                    RightBalance(T);
                    taller = FALSE;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 1;
}

void LeftBalance(BSTree &T)
{
    BSTree lc = T->lchild;
    BSTree rd;
    switch (lc->bf)
    {
    case LH:
        T->bf = lc->bf = EH;
        R_Rotate(T);
        break;
    case RH:
        rd = lc->rchild;
        switch (rd->bf)
        {
        case LH:
            T->bf = RH;
            lc->bf = EH;
            break;
        case RH:
            T->bf = EH;
            lc->bf = LH;
        default:
            break;
        }
        rd->bf = EH;
        L_Rotate(T->lchild);
        R_Rotate(T);
    default:
        break;
    }
}

void RightBalance(BSTree &T)
{
    BSTree rc = T->rchild;
    BSTree ld;
    switch (rc->bf)
    {
    case RH:
        T->bf = rc->bf = EH;
        L_Rotate(T);
        break;
    case LH:
        ld = rc->lchild;
        switch (ld->bf)
        {
        case RH:
            T->bf = LH;
            rc->bf = EH;
            break;
        case LH:
            T->bf = EH;
            rc->bf = RH;
        default:
            break;
        }
        R_Rotate(T->rchild);
        L_Rotate(T);
    default:
        break;
    }
}
#endif