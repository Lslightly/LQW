#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

#define MAX_CHARS 1000
typedef struct HTNode
{
    unsigned int i;     //  i为在HT中的编号
    unsigned int weight;//  权重
    unsigned int parent, lchild, rchild;    //  左右孩子双亲指针
}HTNode, * HuffmanTree;

typedef char ** HuffmanCode;

//  在下标<=i的范围内选择最小的两个没有parent的节点，通过s1,s2返回下标
void Select(HuffmanTree & HT, int i, int & s1, int & s2);

//  哈夫曼编码
//  n为叶子节点个数
void HuffmanDecoding(HuffmanTree & HT, HuffmanCode &HC, int &n);

//  权值比较函数
int cmp_weight(const HTNode & a, const HTNode & b);

//  HC: Huffman Code
void HuffmanCoding(HuffmanTree & HT, HuffmanCode & HC, unsigned int * w, int n)
{
    int m = 0, i = 0;
    int s1, s2;
    HuffmanTree p = nullptr;

    m = 2*n-1;
    HT = (HuffmanTree)malloc(sizeof(HTNode)*(m+1));
    
    Priority_Queue<HTNode> HT_queue;

    //  构造哈夫曼树
    HT_queue.init(HT_queue, m, cmp_weight);
    for (p = HT+1, i = 1; i <= n; i++, ++w, ++p)    //  先将叶子节点全部入队
    {
        *p = {(unsigned int)i, *w, 0, 0, 0};
        HT_queue.enqueue(HT_queue, *p);
    }
    
    for (i = n+1; i <= m; i++)  //  通过这么多此循环，将哈弗曼树的所有节点都构造出来
    {
        HTNode min1, min2;
        HT_queue.dequeue(HT_queue, min1);
        HT_queue.dequeue(HT_queue, min2);
        HT[i] = {(unsigned int)i, min1.weight+min2.weight, 0, min1.i, min2.i};  //  构造parent节点
        HT[min1.i].parent = (unsigned int)i;
        HT[min2.i].parent = (unsigned int)i;
        HT_queue.enqueue(HT_queue, HT[i]);
    }

    //  构造哈夫曼编码
    //  从下往上构造
    HC = (HuffmanCode)malloc(sizeof(*HC)*(n+1));
    char * cd = (char *)malloc(n * sizeof(char));

    cd[n-1] = '\0';
    for (i = 1; i<=n; i++)
    {
        int start = n-1, f = HT[i].parent, c = i;

        for (; f != 0; c = f, f = HT[c].parent)
        {
            if (HT[f].lchild == c) cd[--start] = '0';   //  判断左右孩子来决定是加0还是加1
            else cd[--start] = '1';
        }

        HC[i] = (char *)malloc((n-start) * sizeof(char));
        strcpy(HC[i], cd+start);
    }
    free(cd);
}

void Select(HuffmanTree & HT, int i, int & s1, int &s2)
{
    s1 = 0, s2 = 0;
    int min1 = __INT32_MAX__, min2 = __INT32_MAX__;
    for (int j = 1; j <= i; j++)
    {
        if (HT[j].parent == 0 && HT[j].weight < min1)
        {
            s1 = j;
            min1 = HT[j].weight;
        }
    }
    for (int j = 1; j <= i; j++)
    {
        if (HT[j].parent == 0 && HT[j].weight >= min1 && HT[j].weight < min2 && j != s1)
        {
            s2 = j;
            min2 = HT[j].weight;
        }
    }
    if (s1 > s2)
    {
        int t = s1;
        s1 = s2;
        s2 = t;
    }
}

int cmp_weight(const HTNode & a, const HTNode & b)
{
    return a.weight - b.weight;
}
