#ifndef TREE_H_
#define TREE_H_ 1
//  树
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;

#define MAX_TREE_SIZE 100

//  双亲表示法
typedef struct PTNode   //  结点结构
{
    TElemType data;
    int parent;         //  双亲位置域
}PTNode;
typedef struct
{
    PTNode nodes[MAX_TREE_SIZE];
    int r, n;           //  树的位置和结点数
}PTree;

//  孩子表示法
typedef struct CTNode
{
    int child;
    struct CTNode * next;
} * ChildPtr;
typedef struct
{
    TElemType data;
    ChildPtr firstchild;
}CTBox;
typedef struct
{
    CTBox nodes[MAX_TREE_SIZE];
    int n, r;
}CTree;

//  孩子双亲表示法，每个结点既有双亲，又有孩子链表
typedef struct
{
    TElemType data;
    int parent;
    ChildPtr firstchild;
}PCTBox;
typedef struct
{
    PCTBox nodes[MAX_TREE_SIZE];
    int n, r;
}PCTree;

//  二叉树表示法，二叉链表表示法，孩子兄弟表示法
typedef struct CSNode
{
    TElemType data;
    struct CSNode * firstchild, * nextsibling;
}CSNode, *CSTree;

//  等价类的划分
typedef PTree MFSet;

//  找到S中i所在的子集
int find_mfset(MFSet S, int i)
{
    if (i < 1 || i > S.n) return -1;    //  i不属于S中任意集合
    int j;
    for (j = i; S.nodes[j].parent > 0; j = S.nodes[j].parent)
        ;
    return j;
}

//  合并两个互不相交的子集，S.nodes[i],S.nodes[j]为两个不相交子集的根结点
Status merge_mfset(MFSet &S, int i, int j)
{
    if (i < 1 || i > S.n || j < 1 || j > S.n)
        return ERROR;
    S.nodes[i].parent = j;
    return OK;
}

//  合并两个不相交的子集的优化算法，一定会将结点数较少的树的根结点连到结点数较多的树的根结点下面，这里采用根结点的parent值储存树结点个数的相反数
Status mix_mfset(MFSet &S, int i, int j)
{
    if (i < 1 || i > S.n || j < 1 || j > S.n)
        return ERROR;
    if (S.nodes[i].parent > S.nodes[j].parent)  //  j的树结点数更多
    {
        S.nodes[j].parent += S.nodes[i].parent;
        S.nodes[i].parent = j;
    }
    else
    {
        S.nodes[i].parent += S.nodes[j].parent;
        S.nodes[j].parent = i;
    }
    return OK;
}

//  确定i所在子集，并将从根到i的路径上所有点都变成根的孩子结点
int fix_mfset(MFSet &S, int i)
{
    if (i < 1 || i > S.n) return -1;
    int j;
    for (j = i; S.nodes[j].parent > 0; j = S.nodes[j].parent)
        ;
    int k, t;
    for (k = i; k != j; k=t)
    {
        t = S.nodes[k].parent;
        S.nodes[k].parent = j;
    }
    return j;
}
#endif
