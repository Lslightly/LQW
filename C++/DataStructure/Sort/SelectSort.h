#ifndef SELECTSORT_H_
#define SELECTSORT_H_ 1
//  选择排序
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

int SelectMinKey(SqList L, int i)
{
    int min = L.r[i].key;
    int mini = i;
    for (int k = i+1; k <= L.length; ++k)
    {
        if (LT(L.r[k].key, min))
        {
            min = L.r[k].key;
            mini = k;
        }
    }
    return mini;
}

void SelectSort(SqList &L)
{
    int i, j;
    for (i = 1; i < L.length; i++)
    {
        j = SelectMinKey(L, i);
        if (i != j) swap(L.r[i], L.r[j]);
    }
}

typedef SqList HeapType;

//  大根堆
void HeapAdjust(HeapType &H, int s, int m)
{
    RedType rc = H.r[s];
    int j;
    for (j = 2*s; j <= m; j*=2)
    {
        if (j < m && LT(H.r[j].key, H.r[j+1].key)) ++j;
        if (!LT(rc.key, H.r[j].key)) break;
        H.r[s] = H.r[j];
        s = j;
    }
    H.r[s] = rc;
}

void HeapSort(HeapType &H)
{
    int i, l;
    for (i = H.length/2; i > 0; --i)
        HeapAdjust(H, i, H.length);
    for (i = H.length; i > 1; --i)
    {
        swap(H.r[1], H.r[i]);
        HeapAdjust(H, 1, i-1);
    }
}
#endif