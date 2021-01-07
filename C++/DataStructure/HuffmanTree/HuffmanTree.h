#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

#define MAX_CHARS 1000
typedef struct HTNode
{
    unsigned int i;
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char ** HuffmanCode;

void Select(HuffmanTree & HT, int i, int & s1, int & s2);

void HuffmanDecoding(HuffmanTree & HT, HuffmanCode &HC, int &n);

int cmp_weight(const HTNode & a, const HTNode & b);

//  HC: Huffman Code
void HuffmanCoding(HuffmanTree & HT, HuffmanCode & HC, unsigned int * w, int n)
{
    int m = 0, i = 0;
    int s1, s2;
    HuffmanTree p = nullptr;

    if (n <= 1) return ;
    m = 2*n-1;
    HT = (HuffmanTree)malloc(sizeof(HTNode)*(m+1));
    
    // for (p = HT+1, i = 1; i <= n; ++i, ++p, ++w) *p = {*w, 0, 0, 0};

    // for (; i <= m; ++i, ++p) *p = {0, 0, 0, 0};

    // for (i = n+1; i <= m; i++)
    // {
    //     Select(HT, i-1, s1, s2);
    //     HT[s1].parent = i;  HT[s2].parent = i;
    //     HT[i].lchild = s1; HT[i].rchild = s2;
    //     HT[i].weight = HT[s1].weight + HT[s2].weight;
    // }
    Priority_Queue<HTNode> HT_queue;

    HT_queue.init(HT_queue, m, cmp_weight);
    for (p = HT+1, i = 1; i <= n; i++, ++w, ++p)
    {
        *p = {(unsigned int)i, *w, 0, 0, 0};
        HT_queue.enqueue(HT_queue, *p);
    }
    
    for (i = n+1; i <= m; i++)
    {
        HTNode min1, min2;
        HT_queue.dequeue(HT_queue, min1);
        HT_queue.dequeue(HT_queue, min2);
        // unsigned int mini = (min1.i < min2.i)?min1.i:min2.i;
        // unsigned int maxi = (mini == min1.i)?min2.i:min1.i;
        HT[i] = {(unsigned int)i, min1.weight+min2.weight, 0, min1.i, min2.i};
        HT[min1.i].parent = (unsigned int)i;
        HT[min2.i].parent = (unsigned int)i;
        HT_queue.enqueue(HT_queue, HT[i]);
    }

    HC = (HuffmanCode)malloc(sizeof(*HC)*(n+1));
    char * cd = (char *)malloc(n * sizeof(char));

    cd[n-1] = '\0';
    for (i = 1; i<=n; i++)
    {
        int start = n-1, f = HT[i].parent, c = i;

        for (; f != 0; c = f, f = HT[c].parent)
        {
            if (HT[f].lchild == c) cd[--start] = '0';
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
