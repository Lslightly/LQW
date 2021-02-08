#ifndef QUICKSORT_H_
#define QUICKSORT_H_ 1
//  快速排序
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

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

int Partition(SqList &L, int low, int high)
{
    int pivotkey = L.r[low].key;
    L.r[0] = L.r[low];
    while (low < high)
    {
        while (low < high && L.r[high].key >= pivotkey)
            --high;
        L.r[low] = L.r[high];
        while (low < high && L.r[low].key <= pivotkey)
            ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}

void QSort(SqList &L, int low, int high)
{
    int pivotloc;
    if (low < high)
    {
        pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc-1);
        QSort(L, pivotloc+1, high);
    }
}

void QuickSort(SqList &L)
{
    QSort(L, 1, L.length);
}

#endif