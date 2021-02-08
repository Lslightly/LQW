#ifndef INSERTSORT_H_
#define INSERTSORT_H_ 1
//  插入排序
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define MAXSIZE 20
#define LT(a, b) ((a) < (b))
#define EQ(a, b) ((a) == (b))
#define LQ(a, b) ((a) <= (b))
typedef int KeyType;
typedef char *InfoType;
typedef struct
{
    KeyType key;
    InfoType otherinfo;
} RedType;
typedef struct
{
    RedType r[MAXSIZE + 1]; //  r[0]闲置
    int length;
} SqList;

//  直接插入排序
//  稳定排序
void InsertSort(SqList &L)
{
    int i, j;
    for (i = 2; i <= L.length; i++)
    {
        if (LT(L.r[i].key, L.r[i - 1].key))
        {
            L.r[0] = L.r[i];
            L.r[i] = L.r[i - 1];
            for (j = i - 2; LT(L.r[0].key, L.r[j].key); --j)
                L.r[j + 1] = L.r[j];
            L.r[j + 1] = L.r[0];
        }
    }
}

//  折半插入排序
void BInsertSort(SqList &L)
{
    int i, j, low, high;
    for (i = 2; i <= L.length; i++)
    {
        L.r[0] = L.r[i];
        low = 1;
        high = i - 1;
        while (low <= high)
        {
            int m = (low + high) / 2;
            if (LT(L.r[0].key, L.r[m].key))
                high = m - 1;
            else
                low = m + 1;
        }
        for (j = i - 1; j >= high + 1; --j)
            L.r[j + 1] = L.r[j];
        L.r[j + 1] = L.r[0];
    }
}

//  表排序
#define SIZE 100
typedef struct
{
    RedType rc; //  记录项
    int next;   //  指针项
} SLNode;
typedef struct
{
    SLNode r[SIZE]; //  0号单元为表头结点
    int length;     //  链表当前长度
} SLinkListType;    //   静态链表

//  根据静态链表中各节点的指针进行重排
void Arrange(SLinkListType &SL)
{
    int p, i, q;
    p = SL.r[0].next;
    for (i = 1; i < SL.length; i++)
    {
        while (p < i)
            p = SL.r[p].next;
        q = SL.r[p].next;
        if (p != i)
        {
            SLNode temp = SL.r[p];
            SL.r[p] = SL.r[i];
            SL.r[i] = temp;
            SL.r[i].next = p;
        }
        p = q;
    }
}

//  希尔插入排序
void ShellInsert(SqList &L, int dk)
{
    int i, j;
    for (i = dk+1; i <= L.length; i++)
    {
        if (LT(L.r[i].key, L.r[i-dk].key))
        {
            L.r[0] = L.r[i];
            for (j = i-dk; j > 0 && LT(L.r[0].key, L.r[j].key); j -= dk)
                L.r[j+dk] = L.r[j];
            L.r[j+dk] = L.r[0];
        }
    }
}

void ShellSort(SqList &L, int *dlta, int t)
{
    int k;
    for (k = 0; k < t; k++)
        ShellInsert(L, dlta[k]);
}
#endif