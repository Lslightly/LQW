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
#endif