#include <stdio.h>

#define m 3

typedef int KeyType;

typedef bool Record;

typedef struct BTNode
{
    int keynum;                 //  关键字个数
    struct BTNode * parent;     //  指向双亲节点
    KeyType key[m+1];           //  关键字向量
    struct BTNode * ptr[m+1];   //  子树指针向量
    Record * recptr[m+1];       //  记录指针向量
}BTNode, * BTree;

typedef struct
{
    BTNode * pt;        //  指向找到的节点
    int i;              //  关键字序号
    bool tag;           //  true:查找成功;false:失败
}Result;                //  BTree查找结果类型

Result SearchBTree(BTree T, KeyType K)
{
    BTree p = T, q = nullptr;
    bool found = false;
    int i = 0;

    while (p && !found)
    {
        i = Search(p, K);   //  在p->key[1..keynum]中查找，i使得p->key[i] <= K < p->key[i+1]
        if (i > 0 && p->key[i] == K) found = true;
        else
        {
            q = p; p = p->ptr[i];
        }
    }
    if (found) return {p, i, 1};
    else return {q, i, 0};
}

int Search(BTree p, KeyType K)
{
    int i = 1;
    if (p->key[1] > K) return 0;
    for (i = 1; i < p->keynum; i++)
    {
        if (p->key[i] <= K && p->key[i+1] > K)
            return i;
    }
    return i;
}


