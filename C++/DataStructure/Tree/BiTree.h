#ifndef BITREE_H_
#define BITREE_H_ 1
//  顺序存储结构存储二叉树
#include <stack>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int TElemType;

#define MAX_TREE_SIZE 100
typedef TElemType SqBiTree[MAX_TREE_SIZE];

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//  按先序次序输入二叉树的值，空格字符表示空树，构造二叉链表表示二叉树
Status CreateBiTree(BiTree &T);
//  先序遍历
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
//  中序遍历
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
//  后序遍历
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e));
//  层次遍历
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));

Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T)
    {
        if (visit(T->data))
            if (PreOrderTraverse(T->lchild, visit))
                if (PreOrderTraverse(T->rchild, visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T)
    {
        if (InOrderTraverse(T->lchild, visit))
            if (visit(T->data))
                if (InOrderTraverse(T->rchild, visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T)
    {
        if (PostOrderTraverse(T->lchild, visit))
            if (PostOrderTraverse(T->rchild, visit))
                if (visit(T->data))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status InOrderTraverseNoRecursion1(BiTree T, Status (*visit)(TElemType e))
{
    stack<BiTree> S;
    BiTree p;
    S.push(T);
    while (!S.empty())
    {
        while (p = S.top())
        {
            S.push(p->lchild);
        }
        p = S.top();
        S.pop();
        if (!S.empty())
        {
            p = S.top();
            S.pop();
            if (!visit(p->data))
                return ERROR;
        }
    }
    return OK;
}

Status InOrderTraverseNoRecursion2(BiTree T, Status (*visit)(TElemType e))
{
    stack<BiTree> S;
    BiTree p = T;
    while (p || !S.empty())
    {
        if (p)
        {
            S.push(p);
            p = p->lchild;
        }
        else
        {
            p = S.top();
            S.pop();
            if (!visit(p->data))
                return ERROR;
            p = p->rchild;
        }
    }
    return OK;
}

//  先序次序输入二叉树节点的值
Status CreateBiTree(BiTree &T)
{
    char ch = getchar();
    if (ch == ' ') T = nullptr;
    else
    {
        if (!(T = (BiTree)malloc(sizeof(*T)))) exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}


//  线索二叉树
typedef enum PointerTag {Link, Thread};     //  线索还是指针
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode * lchild, * rchild;    //  左右孩子指针
    PointerTag LTag, RTag;                  //  左右标志
}BiThrNode, * BiThrTree;

//  设立头结点，lchild指向根节点，rchild指向中序遍历最后一个节点
//  中序遍历第一个结点lchild指向头结点，中序遍历最后一个结点rchild指向头结点
Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e))
{
    BiThrTree p = T->lchild;    //  p指向根结点
    while (p != T)
    {
        while (p->LTag == Link) p = p->lchild;
        if (!visit(p->data)) return ERROR;
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            if (!visit(p->data)) return ERROR;
        }
        p = p->rchild;
    }
    return OK;
}

BiThrTree pre;

void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild);
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = pre;
        }
        if (!pre->rchild)
        {
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild);
    }
}

//  中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
    if (!(Thrt = (BiThrTree)malloc(sizeof(*Thrt)))) exit(OVERFLOW);
    Thrt->LTag = Link;
    Thrt->RTag = Thread;
    Thrt->rchild = Thrt;
    if (!T) Thrt->lchild = Thrt;
    else
    {
        Thrt->lchild = T;
        pre = Thrt;
        InThreading(T);
        pre->rchild = Thrt;
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
    return OK;
}

#endif