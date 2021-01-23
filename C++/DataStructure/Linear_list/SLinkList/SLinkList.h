#ifndef SLINKLIST_H_
#define SLINKLIST_H_ 1

//  静态链表，指针由数组下标确定

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

#define MAXSIZE 200

typedef struct
{
    ElemType data;
    int cur;
}component, SLinkList[MAXSIZE];

//  S[0].cur指示第一个结点所在的位置

//  在静态单链线性表中查找第一个值为e的元素
//  若找到，返回位序，否则返回0
int LocateElem_SL(SLinkList S, ElemType e)
{
    int i = S[0].cur;
    while (i && S[i].data != e) i = S[i].cur;
    return i;
}

//  将一维数组space中各分量链成一个备用链表,space[0].cur为头指针
//  "0"表示空指针
void InitSpace_SL(SLinkList &space)
{
    for (int i = 0; i < MAXSIZE-1; ++i) space[i].cur = i+1;
    space[MAXSIZE-1].cur = 0;
}

//  若备用空间链表非空，则返回分配的结点下标，否则返回0
int Malloc_SL(SLinkList &space)
{
    int i = space[0].cur;
    if (space[0].cur) space[0].cur = space[i].cur;
    return i;
}

//  将下标为k的结点回收到备用链表中
void Free_SL(SLinkList &space, int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

//  依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A)的静态链表，S为头指针
//  时间复杂度O(m*n)
void difference(SLinkList &space, int &S)
{
    InitSpace_SL(space);
    S = Malloc_SL(space);   //  生成S的头结点
    int r = S;      //  r指向S的当前最后结点
    int m, n;       //  A和B的元素个数
    scanf("%d%d", &m, &n);
    int j, i;
    for (j = 1; j <= m; j++)    //  建立A的链表
    {
        i = Malloc_SL(space);
        scanf("%d", &space[i].data);
        space[r].cur = i;       //  尾插法
        r = i;
    }
    space[r].cur = 0;

    int b, p, k;
    for (j = 1; j <= n; j++)    //  依次输入B的元素，求对称差
    {
        scanf("%d", &b);
        p = S;              //  如果找到相同的，p为这个相同结点的前驱
        k = space[S].cur;   //  k指向S的第一个结点

        while (k != space[r].cur && space[k].data != b)
        {
            k = space[k].cur;
            p = k;
        }
        if (k == space[r].cur)  //  以A表的尾结点作为头结点进行头插法
        {
            i = Malloc_SL(space);
            space[i].data = b;
            space[i].cur = space[r].cur;
            space[r].cur = i;
        }
        else
        {
            space[p].cur = space[k].cur;
            Free_SL(space, k);
            if (r == k) r = p;      //  如果删除的是r所指结点，则需要修改尾指针
        }
    }
}

#endif