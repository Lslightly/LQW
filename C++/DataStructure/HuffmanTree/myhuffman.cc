#include <stdio.h>
#include "HuffmanTree.h"
#include <cstring>

void Count(unsigned int w[], int &n, int *table, char chtable[MAX_CHARS], char * source);   //  记录文件中的字符个数

void Compress(HuffmanTree & T, unsigned int *w, HuffmanCode code, int n, int *table, char *source);

void Extract(HuffmanTree & HT, HuffmanCode &HC, int &n);

int main(int argc, char ** argv)
{
    unsigned int w[MAX_CHARS] = {0};
    int table[MAX_CHARS] = {0};
    HuffmanTree T = nullptr;
    HuffmanCode code = nullptr;
    int n;

    Compress(T, w, code, MAX_CHARS, table, argv[1]);
    // Extract(T, code, n);
    return 0;
}

void Count(unsigned int w[MAX_CHARS], int &n, int *table, char chtable[MAX_CHARS], char * source)
{
    FILE * fp = freopen(source , "r", stdin);
    char ch;
    while ((ch = getchar()) != EOF)
    {
        if (table[ch] == 0)
        {
            n++;
            table[ch] = n;
            w[table[ch]]++;
            chtable[n] = ch;
        }
        else
        {
            w[table[ch]]++;
        }
    }
    fcloseall();
}

void Compress(HuffmanTree & T, unsigned int *w, HuffmanCode code, int n, int *table, char * source)
{
    char chtable[MAX_CHARS];
    char dest[20];
    strcpy(dest, source);
    strcat(dest, ".huff");
    n = 0;
    Count(w, n, table, chtable, source);
    HuffmanCoding(T, code, w, n);
    FILE * fp = freopen(source, "r", stdin);
    FILE * foutp = freopen(dest, "w", stdout);
    PrintHuffmanTree(T, n, chtable);
    char ch;
    while ((ch = getchar()) != EOF)
    {
        printf("%s", code[table[ch]]);
    }
    fcloseall();
}

void Extract(HuffmanTree & HT, HuffmanCode &HC, int &n)
{
    FILE * fin = freopen("/home/liqingwei/mygit/MyRepo/C++/DataStructure/HuffmanTree/mississippi.txt.huff", "r", stdin);
    FILE * fout = freopen("/home/liqingwei/mygit/MyRepo/C++/DataStructure/HuffmanTree/mississippi.txt1", "w", stdout);
    scanf("%d", &n);
    int m = 2*n-1;
    int i =1;
    char chtable[MAX_CHARS];
    char ch;
    HT = (HuffmanTree)malloc(sizeof(*HT)*(m+1));
    for (i = 1; i <= n; i++)
    {
        scanf("%c%c%u%u%u%u",&ch, &chtable[i], &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
    }
    for (; i<= m; i++)
    {
        scanf("%u%u%u%u", &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
    }

    i = m;
    ch = getchar();
    while ((ch = getchar()) != EOF)
    {
        if (ch == '0')
        {
            i = HT[i].lchild;
        }
        else
        {
            i = HT[i].rchild;
        }
        if (HT[i].lchild == 0 && HT[i].rchild == 0)
        {
            putchar(chtable[i]);
            i = m;
        }
    }
}
