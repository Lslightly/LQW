#ifndef STATICSEARCHTABLE_H_
#define STATICSEARCHTABLE_H_ 1
//  静态查找表
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

//  顺序表的查找
typedef struct
{
    SElemType * elem;
    int length;
}SSTable;

int Search_Seq(SSTable ST, KeyType key);
int Search_Bin(SSTable ST, KeyType key);

//  顺序查找，若成功，返回位置，否则返回0
//  ASL = (n+1)/2
int Search_Seq(SSTable ST, KeyType key)
{
    int i;
    ST.elem[0].key = key;
    for (i = ST.length; !EQ(ST.elem[i].key, key); --i)
        ;
    return i;
}

//  ASL = log(n+1)-1
int Search_Bin(SSTable ST, KeyType key)
{
    int low = 1, high = ST.length;
    int mid;
    while (low <= high)
    {
        mid = (low + high)/2;
        if (EQ(ST.elem[mid].key, key)) return mid;
        else if (LT(ST.elem[mid].key, key))
        {
            low = mid+1;
        }
        else
        {
            high = mid-1;
        }
    }
    return 0;
}

void SecondOptimal(BiTree &T, SElemType R[MAX_SEARCH_NUM], float sw[MAX_SEARCH_NUM], int low, int high)
{
    int i, min, dw, j;
    i = low;
    min = abs(sw[high]-sw[low]);
    dw = sw[high]+sw[low-1];
    for ( j = low+1; j <= high; j++)
    {
        if (abs(dw - sw[j] - sw[j-1]) < min)
        {
            i = j;
            min = abs(dw - sw[j] - sw[j-1]);
        }
    }
    T = (BiTree)malloc(sizeof(*T));
    T->data = R[i].key;
    if (i == low) T->lchild = nullptr;
    else SecondOptimal(T->lchild, R, sw, low, i-1);
    if (i == high) T->rchild = nullptr;
    else SecondOptimal(T->rchild, R, sw, i+1, high);
}
#endif