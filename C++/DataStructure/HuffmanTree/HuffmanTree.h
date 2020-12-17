#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char ** HuffmanCode;

//  HC: Huffman Code
void HuffmanCoding(HuffmanTree & HT, HuffmanCode & HC, int * w, int n)
{
    int m = 0, i = 0;
    HuffmanTree p = nullptr;

    if (n <= 1) return ;
    m = 2*n-1;
    HT = (HuffmanTree)malloc(sizeof((m+1) * sizeof(HTNode)));
    
    for (p = HT+1, i = 1; i <= n; ++i, ++p, ++w) *p = {*w, 0, 0, 0};

    for (; i <= m; ++i) *p = {0, 0, 0, 0};

    for (i = n+1; i <= m; i++)
    {
        int s1, s2;
        Select(HT, i-1, s1, s2);
        HT[s1].parent = i;  HT[s2].parent = i;
        HT[i].lchild = s1; HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    HC = (HuffmanCode)malloc((n+1) * sizeof(char *));
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
    int min_1 = __INT32_MAX__, min_2 = __INT32_MAX__;
    int min1_order = 0, min2_order = 0;
    for (int j = 1; j <= i; j++)
    {
        // if (min_1 > HT[j].weight && HT[j].parent == 0)
    }
}