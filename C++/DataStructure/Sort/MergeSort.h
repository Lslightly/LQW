#ifndef MERGESORT_H_
#define MERGESORT_H_ 1
//  归并排序
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

void Merge(RedType SR[MAXSIZE], RedType TR[MAXSIZE], int i, int m, int n)
{
    int j, k;
    for (j = m+1, k = i; i <= m && j <= n; ++k)
    {
        if (LQ(SR[i].key, SR[j].key)) TR[k] = SR[i++];
        else TR[k] = SR[j++];
    }
    if (i <= m)
        for (; k <= n; ++k)
            TR[k] = SR[i++];
    if (j <= n)
        for (; k <= n; ++k)
            TR[k] = SR[j++];
}

void MSort(RedType SR[MAXSIZE], RedType TR1[MAXSIZE], int s, int t)
{
    if (s == t) TR1[s] = SR[s];
    else
    {
        RedType * TR2 = (RedType *)malloc(sizeof(*TR2) * MAXSIZE);
        int m = (s+t)/2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m+1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void MergeSort(SqList &L)
{
    MSort(L.r, L.r, 1, L.length);
}

#endif