#include "HuffmanTree.h"
#include <cstring>
#include <stdio.h>

void Count(unsigned int w[], int &n, int *table, char chtable[MAX_CHARS], char *source); //  记录文件中的字符个数

void Compress(HuffmanTree &T, unsigned int *w, HuffmanCode code, int &n, int *table, char *source, char *dest);

void Extract(HuffmanTree &HT, HuffmanCode &HC, int &n, char *ex_source);

int main(int argc, char **argv)
{
    unsigned int w[MAX_CHARS] = {0};
    int table[MAX_CHARS] = {0};
    HuffmanTree T = nullptr;
    HuffmanCode code = nullptr;
    int n;

    if (argv[1][0] == '-')
    {
        if (strcmp(argv[1], "-z") == 0)
            Compress(T, w, code, n, table, argv[2], nullptr);
        else if (strcmp(argv[1], "-u") == 0)
            Extract(T, code, n, argv[2]);
        else if (strcmp(argv[1], "-zr") == 0)
            Compress(T, w, code, n, table, argv[2], argv[3]);
        else
            printf("%s option error\n", argv[1]);
    }
    else
    {
        Compress(T, w, code, n, table, argv[1], nullptr);
    }

    return 0;
}

void Count(unsigned int w[MAX_CHARS], int &n, int *table, char chtable[MAX_CHARS], char *source)
{
    int len_source = strlen(source);
    for (int i = 0; i <= len_source; i++)
    {
        if (table[source[i]] == 0)
        {
            n++;
            table[source[i]] = n;
            w[table[source[i]]]++;
            chtable[n] = source[i];
        }
    }
    FILE *fp = freopen(source, "r", stdin);
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

void Compress(HuffmanTree &T, unsigned int *w, HuffmanCode code, int &n, int *table, char *source, char *dest)
{
    char chtable[MAX_CHARS];
    int len_source = strlen(source);
    if (!dest) //  不是重命名
    {
        char * real_dest = (char *)malloc((len_source + 6) * sizeof(*real_dest));
        strcpy(real_dest, source);
        strcat(real_dest, ".huff");
        n = 0;
        Count(w, n, table, chtable, source);
        HuffmanCoding(T, code, w, n);
        FILE *fp = freopen(source, "r", stdin);
        FILE *foutp = freopen(real_dest, "w", stdout);
        PrintHuffmanTree(T, n, chtable);

        
        for (int i = 0; i <= len_source; i++)
            printf("%s", code[table[source[i]]]);
        char ch;
        while ((ch = getchar()) != EOF)
        {
            printf("%s", code[table[ch]]);
        }
    }
    else
    {
        int len_dest = strlen(dest);
        char * real_dest = (char *)malloc((len_dest+1) * sizeof(*real_dest));
        strcpy(real_dest, dest);
        n = 0;
        Count(w, n, table, chtable, source);
        HuffmanCoding(T, code, w, n);
        FILE *fp = freopen(source, "r", stdin);
        FILE *foutp = freopen(real_dest, "w", stdout);
        PrintHuffmanTree(T, n, chtable);

        
        for (int i = 0; i <= len_source; i++)
            printf("%s", code[table[source[i]]]);
        char ch;
        while ((ch = getchar()) != EOF)
        {
            printf("%s", code[table[ch]]);
        }
        
    }
    
    fcloseall();
}

void Extract(HuffmanTree &HT, HuffmanCode &HC, int &n, char *ex_source)
{
    char ex_dest[20];
    int len_ex_source = strlen(ex_source);
    if (len_ex_source <= 5)
        printf("File format wrong\n");
    else if (strcmp(ex_source + len_ex_source - 5, ".huff") != 0)
        printf("File format wrong\n");
    else
    {
        FILE *fin = freopen(ex_source, "r", stdin);
        scanf("%d", &n);
        int m = 2 * n - 1;
        int i = 1;
        char chtable[MAX_CHARS];
        char ch;
        HT = (HuffmanTree)malloc(sizeof(*HT) * (m + 1));
        for (i = 1; i <= n; i++)
        {
            scanf("%c%c%u%u%u%u", &ch, &chtable[i], &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
        }
        for (; i <= m; i++)
        {
            scanf("%u%u%u%u", &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
        }

        i = m;
        int j = 0;  //  ex_dest[j]
        ch = getchar();     //  \n
        do
        {
            ch = getchar();
            if (ch == '0')
                i = HT[i].lchild;
            else
                i = HT[i].rchild;
            if (HT[i].lchild == 0 && HT[i].rchild == 0)
            {
                ch = chtable[i];
                ex_dest[j] = ch;
                j++;
                i = m;
            }
        } while (ch != '\0');
        
        freopen(ex_dest, "w", stdout);
        i = m;
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
}
