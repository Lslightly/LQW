#ifndef RADIXSORT_H_
#define RADIXSORT_H_ 1
//  基数排序
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

#define MAX_NUM_OF_KEY 8
#define RADIX 10
#define MAX_SPACE 10000
typedef struct
{
    KeyType keys[MAX_NUM_OF_KEY];
    InfoType otherinfo;
    int next;
}SLCell;
typedef struct
{
    SLCell r[MAX_SPACE];
    int keynum;
    int recnum;
}SLList;
typedef int ArrType[RADIX];

void Distribute(SLCell r[MAX_SPACE], int i, ArrType &f, ArrType &e)
{
    int j, p;
    for (j = 0; j < RADIX; j++) f[j] = 0;
    for (p = r[0].next; p; p = r[p].next)
    {
        j = r[p].keys[i];
        if (!f[j]) f[j] = p;
        else r[e[j]].next = p;
        e[j] = p;
    }
}

void Collect(SLCell r[MAX_SPACE], int i, ArrType f, ArrType e)
{
    int j, t;
    for (j = 0; !f[j]; j++)
        ;
    r[0].next = f[j];
    t = e[j];
    while (j < RADIX)
    {
        for (j++; j < RADIX-1 && !f[j]; j++)
            ;
        if (f[j])
        {
            r[t].next = f[j];
            t = e[j];
        }
    }
    r[t].next = 0;
}

void RadixSort(SLList &L)
{
    int i;
    ArrType f, e;
    for (i = 0; i < L.recnum; i++)
        L.r[i].next = i+1;
    L.r[L.recnum].next = 0;
    for (i = 0; i < L.keynum; i++)
    {
        Distribute(L.r, i, f, e);
        Collect(L.r, i, f, e);
    }
}

#endif