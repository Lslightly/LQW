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
typedef char * InfoType;
typedef struct
{
    KeyType key;
    InfoType otherinfo;
}RedType;
typedef struct
{
    RedType r[MAXSIZE+1];   //  r[0]闲置
    int length;
}SqList;

void InsertSort(SqList &L)
{
    int i, j;
    for (i = 2; i <= L.length; i++)
    {
        if (LT(L.r[i].key, L.r[i-1].key))
        {
            L.r[0] = L.r[i];
            L.r[i] = L.r[i-1];
            for (j = i-2; LT(L.r[0].key, L.r[j].key); --j)
                L.r[j+1] = L.r[j];
            L.r[j+1] = L.r[0];
        }
    }
}

#endif