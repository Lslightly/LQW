#include "HuffmanTree.h"
#include <cstring>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct BitCode
{
    unsigned char * bytecode;
    int bytes;
}BitCode;


void PrintHuffmanTree(HuffmanTree T, int n, unsigned char chtable[], FILE *foutp);

void Count(unsigned int w[], int &n, int *table, unsigned char chtable[MAX_CHARS], const char *source); //  记录文件中的字符个数

void Compress(HuffmanTree &T, unsigned int *w, HuffmanCode code, int &n, int *table, char *source, char *dest);

void Extract(HuffmanTree &HT, HuffmanCode &HC, int &n, char *ex_source);

void GenerateBitCode(HuffmanCode HC, BitCode *&bitcode, int n);

int read_dir_r(char *path, char pathname[][MAX_CHARS], int &num_files);

int main(int argc, char **argv)
{
    unsigned int w[MAX_CHARS] = {0};
    int table[MAX_CHARS] = {0};
    HuffmanTree T = nullptr;
    HuffmanCode code = nullptr;
    int n;

    // char **test;
    // test = (char **)malloc(10 * sizeof(*test));
    // test[1] = (char *)malloc(11 * sizeof(char));
    // scanf("%s", test[1]);
    // BitCode *t1;
    // t1 = (BitCode *)malloc(sizeof(BitCode) * 2);
    // GenerateBitCode(test, t1, 1);
    // printf("%hhx", t1[1].bytecode[0]);
    // printf("%hhx", t1[1].bytecode[1]);
    // return 0;

    if (argv[1][0] == '-')
    {
        if (strcmp(argv[1], "-z") == 0)
            Compress(T, w, code, n, table, argv[2], nullptr);
        else if (strcmp(argv[1], "-u") == 0)
            Extract(T, code, n, argv[2]);
        else if (strcmp(argv[1], "-zr") == 0)
            Compress(T, w, code, n, table, argv[2], argv[3]);
        else if (strcmp(argv[1], "-d") == 0)
            Compress(T, w, code, n, table, argv[2], nullptr);
        else if (strcmp(argv[1], "-dr") == 0)
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

void Count(unsigned int w[MAX_CHARS], int &n, int *table, unsigned char chtable[MAX_CHARS], const char *source)
{
    int len_source = strlen(source);
    for (int i = 0; i <= len_source; i++) //  给源文件名统计字符
    {
        if (table[source[i] + 128] == 0) //  +128变unsigned char
        {
            n++;
            table[source[i] + 128] = n;
            w[table[source[i] + 128]]++;
            chtable[n] = source[i] + 128;
        }
        else
        {
            w[table[source[i] + 128]]++;
        }
    }
    if (source[strlen(source) - 1] == '/')
        return; //  文件夹不需要读内容
    FILE *fp = fopen(source, "rb");
    if (fp == nullptr)
        printf("error while open file");
    // FILE *fout = fopen(dest, "wb");
    unsigned char u_ch;
    while (!feof(fp) && fread(&u_ch, sizeof(unsigned char), 1, fp)) //  给源文件统计字符
    {
        // fwrite(&u_ch, sizeof(unsigned char), 1, fout); //  复制一遍文件
        if (table[u_ch] == 0)
        {
            n++;
            table[u_ch] = n;
            w[table[u_ch]]++;
            chtable[n] = u_ch;
        }
        else
        {
            w[table[u_ch]]++;
        }
    }
    fclose(fp);
    // fclose(fout);
}

void Compress(HuffmanTree &T, unsigned int *w, HuffmanCode code, int &n, int *table, char *source, char *dest)
{
    unsigned char chtable[MAX_CHARS];
    BitCode * bitcode;
    char pathname[256][MAX_CHARS];
    int num_files = 0;
    read_dir_r(source, pathname, num_files); //  读取每个文件，包括文件夹的路径
    int len_source = strlen(source);
    char *real_dest = (char *)malloc((len_source + 6) * sizeof(*real_dest));
    strcpy(real_dest, source);
    if (!dest) //  不是重命名
    {
        strcat(real_dest, ".huff");
    }
    else
    {
        strcpy(real_dest, dest);
    }
    n = 0;
    for (int i = 0; i < num_files; i++)
    {
        Count(w, n, table, chtable, pathname[i]);
    }
    HuffmanCoding(T, code, w, n);
    bitcode = (BitCode *)malloc(sizeof(*bitcode) * (n+1));
    GenerateBitCode(code, bitcode, n);
    FILE *foutp = fopen(real_dest, "wb");
    PrintHuffmanTree(T, n, chtable, foutp);

    int len_pathname = 0;

    for (int i = 0; i < num_files; i++)
    {
        len_pathname = strlen(pathname[i]);
        for (int j = 0; j <= len_pathname; j++)
            // fwrite(bitcode[table[pathname[i][j] + 128]].bytecode, sizeof(unsigned char), bitcode[table[pathname[i][j] + 128]].bytes, foutp);
            fwrite(code[table[pathname[i][j] + 128]], sizeof(char), strlen(code[table[pathname[i][j] + 128]]), foutp);
        if (pathname[i][strlen(pathname[i]) - 1] != '/')
        {
            FILE *fp = fopen(pathname[i], "rb");
            unsigned char u_ch;
            while (!feof(fp) && fread(&u_ch, sizeof(unsigned char), 1, fp))
            {
                // fwrite(bitcode[table[u_ch]].bytecode, sizeof(unsigned char), bitcode[table[u_ch]].bytes, foutp);
                fwrite(code[table[u_ch]], sizeof(char), strlen(code[table[u_ch]]), foutp);
                // printf("%s", code[table[ch+128]]);
            }
            char ch = '\n';
            fwrite(&ch, sizeof(char), 1, foutp);
            fclose(fp);
        }
        else
        {
        }
    }
    // }
}

void Extract(HuffmanTree &HT, HuffmanCode &HC, int &n, char *ex_source)
{
    char ex_dest[MAX_CHARS];
    int len_ex_source = strlen(ex_source);
    if (len_ex_source <= 5)
        printf("File format wrong\n");
    else if (strcmp(ex_source + len_ex_source - 5, ".huff") != 0)
        printf("File format wrong\n");
    else
    {
        FILE *fin = fopen(ex_source, "rb");
        fread(&n, sizeof(int), 1, fin);
        int m = 2 * n - 1;
        int i = 1;
        unsigned char chtable[MAX_CHARS];
        HT = (HuffmanTree)malloc(sizeof(*HT) * (m + 1));
        for (i = 1; i <= n; i++)
        {
            // scanf("%hhd%u%u%u%u", &chtable[i], &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
            fread(&chtable[i], sizeof(unsigned char), 1, fin);
            fread(&HT[i].weight, sizeof(unsigned int), 1, fin);
            fread(&HT[i].parent, sizeof(unsigned int), 1, fin);
            fread(&HT[i].lchild, sizeof(unsigned int), 1, fin);
            fread(&HT[i].rchild, sizeof(unsigned int), 1, fin);
        }
        for (; i <= m; i++)
        {
            // scanf("%u%u%u%u", &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
            fread(&HT[i].weight, sizeof(unsigned int), 1, fin);
            fread(&HT[i].parent, sizeof(unsigned int), 1, fin);
            fread(&HT[i].lchild, sizeof(unsigned int), 1, fin);
            fread(&HT[i].rchild, sizeof(unsigned int), 1, fin);
        }

        i = m;
        char ch;
        unsigned char u_ch;
        int j = 0; //  ex_dest[j]

        while (!feof(fin))
        {
            j = 0;
            do
            {
                // ch = getchar();
                fread(&ch, sizeof(char), 1, fin);
                if (ch == '0')
                    i = HT[i].lchild;
                else if (ch == '1')
                    i = HT[i].rchild;
                else
                    break;

                if (HT[i].lchild == 0 && HT[i].rchild == 0)
                {
                    u_ch = chtable[i];
                    ex_dest[j] = u_ch - 128;
                    j++;
                    i = m;
                    if (u_ch == '\0' + 128)
                        break;
                }
            } while (1);

            if (ex_dest[strlen(ex_dest) - 1] == '/')
            {
                mkdir(ex_dest, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            }
            else
            {
                if (feof(fin)) break;
                FILE *foutp = fopen(ex_dest, "wb");
                i = m;
                while (!feof(fin) && fread(&ch, sizeof(char), 1, fin))
                {
                    if (ch == '0')
                    {
                        i = HT[i].lchild;
                    }
                    else if (ch == '1')
                    {
                        i = HT[i].rchild;
                    }
                    else
                    {
                        break;
                    }
                    if (HT[i].lchild == 0 && HT[i].rchild == 0)
                    {
                        // putchar(chtable[i]);
                        fwrite(&chtable[i], sizeof(unsigned char), 1, foutp);
                        i = m;
                    }
                }
                fclose(foutp);
            }
        }
        fclose(fin);
    }
}

void PrintHuffmanTree(HuffmanTree T, int n, unsigned char chtable[MAX_CHARS], FILE *foutp)
{
    int i = 1;
    // printf("%d\n", n);
    fwrite(&n, sizeof(int), 1, foutp);
    int m = 2 * n - 1;
    for (i = 1; i <= n; i++)
    {
        // printf("%d %u %u %u %u\n", chtable[i], T[i].weight, T[i].parent,T[i].lchild, T[i].rchild);
        fwrite(&chtable[i], sizeof(unsigned char), 1, foutp);
        fwrite(&T[i].weight, sizeof(unsigned int), 1, foutp);
        fwrite(&T[i].parent, sizeof(unsigned int), 1, foutp);
        fwrite(&T[i].lchild, sizeof(unsigned int), 1, foutp);
        fwrite(&T[i].rchild, sizeof(unsigned int), 1, foutp);
    }
    for (; i <= m; i++)
    {
        // printf("%u %u %u %u\n", T[i].weight, T[i].parent,T[i].lchild, T[i].rchild);
        fwrite(&T[i].weight, sizeof(unsigned int), 1, foutp);
        fwrite(&T[i].parent, sizeof(unsigned int), 1, foutp);
        fwrite(&T[i].lchild, sizeof(unsigned int), 1, foutp);
        fwrite(&T[i].rchild, sizeof(unsigned int), 1, foutp);
    }
}

//  递归读取输入根目录下的所有文件，包括文件夹，储存到pathname中，文件夹会在最后加一个/符号, pathname从0号单元开始
int read_dir_r(char *path, char pathname[][MAX_CHARS], int &num_files)
{
    DIR *dp = nullptr;
    struct dirent *st;
    struct stat sta;
    int ret = 0;
    char tmp_name[1024] = {0};
    dp = opendir(path);
    if (dp == nullptr)
    {
        strcpy(pathname[num_files], path);
        num_files++;
        return 0;
    }
    else
    {
        strcpy(tmp_name, path);
        if (path[strlen(path) - 1] != '/')
            strcat(tmp_name, "/");
        strcpy(pathname[num_files], tmp_name);
        num_files++;
    }

    while (1)
    {
        st = readdir(dp);
        if (st == nullptr)
        {
            break;
        }

        strcpy(tmp_name, path);
        if (path[strlen(path) - 1] != '/')
            strcat(tmp_name, "/");
        strcat(tmp_name, st->d_name);
        ret = stat(tmp_name, &sta);
        if (ret < 0)
        {
            printf("read stat fail\n");
            return -1;
        }

        if (S_ISDIR(sta.st_mode))
        {
            if (strcmp(".", st->d_name) == 0 || strcmp("..", st->d_name) == 0)
                continue;
            else
            {
                read_dir_r(tmp_name, pathname, num_files);
            }
        }
        else
        {
            strcpy(pathname[num_files], tmp_name);
            num_files++;
        }
    }
    closedir(dp);
    return 0;
}

void GenerateBitCode(HuffmanCode HC, BitCode * &bitcode_a, int n)
{
    int i = 1;
    for (; i <= n; i++)
    {
        int bytes = (strlen(HC[i])-1)/8+1;
        bitcode_a[i].bytecode = (unsigned char*)malloc((bytes) * sizeof(unsigned char));
        bitcode_a[i].bytes = bytes;

        int j = 0, k = 0;
        int len_HC = strlen(HC[i]);
        for (; j < bytes; j++)
        {
            bitcode_a[i].bytecode[j] = 0;
            for (k = 0; k < 8; k++)
            {
                bitcode_a[i].bytecode[j] <<= 1;
                if (8*j+k < len_HC)
                    bitcode_a[i].bytecode[j] += HC[i][8*j+k]-'0';
            }
        }
    }
}


// if (mode == FILE_MODE)  //  单文件模式
// {
//     unsigned char chtable[MAX_CHARS];
//     int len_source = strlen(source);
//     char *real_dest = (char *)malloc((len_source + 6) * sizeof(*real_dest));
//     strcpy(real_dest, source);
//     if (!dest) //  不是重命名
//     {
//         strcat(real_dest, ".huff");
//     }
//     else
//     {
//         strcpy(real_dest, dest);        //  目标文件被重命名
//     }
//     n = 0;
//     Count(w, n, table, chtable, source);
//     HuffmanCoding(T, code, w, n);
//     FILE *fp = fopen(source, "rb");
//     FILE *foutp = fopen(real_dest, "wb");
//     PrintHuffmanTree(T, n, chtable, foutp); //  打印哈弗曼树的信息

//     // for (int i = 0; i <= len_source; i++)
//     //     printf("%s", code[table[source[i]+128]]);

//     for (int i = 0; i <= len_source; i++)   //  文件名压缩字符串
//         fwrite(code[table[source[i] + 128]], sizeof(char), strlen(code[table[source[i] + 128]]), foutp);
//     unsigned char ch;
//     while (!feof(fp) && fread(&ch, sizeof(unsigned char), 1, fp))   //  文件内容字符串
//     {
//         fwrite(code[table[ch]], sizeof(char), strlen(code[table[ch]]), foutp);
//         // printf("%s", code[table[ch+128]]);
//     }

//     fclose(fp);
//     fclose(foutp);
// }
// if (mode == DIR_MODE)  //  压缩文件夹
// {