#include "HuffmanTree.h"
#include <cstring>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct BitCode
{
    unsigned char *bytecode;
    int bytes;
    int len;
} BitCode;

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
    for (int i = 0; i < len_source; i++) //  给源文件名统计字符
    {
        if (table[source[i]] == 0)
        {
            n++;
            table[source[i]] = n;
            w[table[source[i]]]++;
            chtable[n] = source[i];
        }
        else
        {
            w[table[source[i]]]++;
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
    int bitk = 0;
    unsigned char bytes = 0;
    unsigned char chtable[MAX_CHARS];
    BitCode *bitcode;
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
    HuffmanCoding(T, code, w+1, n);

    FILE *foutp = fopen(real_dest, "wb");

    PrintHuffmanTree(T, n, chtable, foutp);

    int len_pathname = 0;

    for (int i = 0; i < num_files; i++)
    {
        len_pathname = strlen(pathname[i]);
        int table_path;
        fwrite(&len_pathname, sizeof(int), 1, foutp); //  在解压时读入需要加1，因为还有一个\0
        for (int j = 0; j < len_pathname; j++)       //  打印文件名,包括\0符
        {
            table_path = table[pathname[i][j]];
            for (int k = 0; k < strlen(code[table_path]); k++)
            {
                bytes <<= 1;
                bytes += code[table_path][k] - '0';
                ++bitk;
                if (bitk == 8)
                {
                    fwrite(&bytes, sizeof(unsigned char), 1, foutp);
                    bytes = 0;
                    bitk = 0;
                }
            }
        }
        while (bitk != 8 && bitk != 0)
        {
            bytes <<= 1;
            ++bitk;
        }
        if (bitk == 8)
            fwrite(&bytes, sizeof(unsigned char), 1, foutp); //  处理剩余部分
        bytes = 0;
        bitk = 0;
        if (pathname[i][strlen(pathname[i]) - 1] != '/')
        {
            FILE *fp = fopen(pathname[i], "rb");
            fseek(fp, 0L, SEEK_END);
            long flen = ftell(fp);
            fseek(fp, 0L, SEEK_SET);
            fwrite(&flen, sizeof(long), 1, foutp);
            unsigned char u_ch;
            while (!feof(fp) && fread(&u_ch, sizeof(unsigned char), 1, fp))
            {
                for (int i = 0; i < strlen(code[table[u_ch]]); i++)
                {
                    bytes <<= 1;
                    bytes += code[table[u_ch]][i] - '0';
                    ++bitk;
                    if (bitk == 8)
                    {
                        fwrite(&bytes, sizeof(unsigned char), 1, foutp);
                        bytes = 0;
                        bitk = 0;
                    }
                }
            }
            while (bitk != 8 && bitk != 0)
            {
                bytes <<= 1;
                ++bitk;
            }
            if (bitk == 8)
                fwrite(&bytes, sizeof(unsigned char), 1, foutp); //  处理剩余部分
            bytes = 0;
            bitk = 0;
            fclose(fp);
        }
        else
        {
        }
    }
    fclose(foutp);
    // double sum = 0;
    // printf("c w p l r\n");
    // for (int i = 1; i <= n; i++)
    // {
    //     sum += strlen(code[i])*T[i].weight;
    //     printf("%c %u %u %s\n", chtable[i], T[i].weight, T[i].parent,  code[i]);
    // }
    // printf("%lf\n", sum/8);
    return;
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
        // fread(&n, sizeof(int), 1, fin);
        fscanf(fin, "%d", &n);
        int m = 2 * n - 1;
        int i = 1;
        unsigned char chtable[MAX_CHARS];
        { //  读取哈弗曼树
            HT = (HuffmanTree)malloc(sizeof(*HT) * (m + 1));
            for (i = 1; i <= n; i++)
            {
                // scanf("%hhd%u%u%u%u", &chtable[i], &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
                // fread(&chtable[i], sizeof(unsigned char), 1, fin);
                // fread(&HT[i].weight, sizeof(unsigned int), 1, fin);
                // fread(&HT[i].parent, sizeof(unsigned int), 1, fin);
                // fread(&HT[i].lchild, sizeof(unsigned int), 1, fin);
                // fread(&HT[i].rchild, sizeof(unsigned int), 1, fin);
                char ch = fgetc(fin);
                fscanf(fin, "%hhu%u%u%u%u", &chtable[i], &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
            }
            for (; i <= m; i++)
            {
                // scanf("%u%u%u%u", &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
                // fread(&HT[i].weight, sizeof(unsigned int), 1, fin);
                // fread(&HT[i].parent, sizeof(unsigned int), 1, fin);
                // fread(&HT[i].lchild, sizeof(unsigned int), 1, fin);
                // fread(&HT[i].rchild, sizeof(unsigned int), 1, fin);
                fgetc(fin);
                fscanf(fin, "%u%u%u%u",  &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
            }
        }
        fgetc(fin);

        i = m;
        char ch;
        unsigned char u_ch;
        int j = 0;   //  ex_dest[j]
        char bit[8]; //  存放读入字节的每一位，7为MSB
        while (!feof(fin))
        {
            int len_pathname;
            fread(&len_pathname, sizeof(int), 1, fin);
            if (feof(fin))
                break;
            int path_i = 0;
            i = m;
            while (path_i < len_pathname) //  读文件名
            {
                fread(&u_ch, sizeof(unsigned char), 1, fin);
                for (int k = 0; k < 8; k++)
                {
                    bit[k] = u_ch % 2;
                    u_ch /= 2;
                }
                for (int k = 7; k >= 0; k--)
                {
                    if (bit[k] == 0)
                    {
                        i = HT[i].lchild;
                    }
                    else
                    {
                        i = HT[i].rchild;
                    }
                    if (HT[i].lchild == 0 && HT[i].rchild == 0)
                    {
                        u_ch = chtable[i];
                        ex_dest[path_i] = u_ch;
                        path_i++;
                        if (path_i == len_pathname)
                            break;
                        i = m;
                    }
                }
            }
            ex_dest[path_i] = '\0';
            if (ex_dest[strlen(ex_dest) - 1] == '/')
            {
                mkdir(ex_dest, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            }
            else
            {
                FILE *foutp = fopen(ex_dest, "wb");
                i = m;
                long flen;
                fread(&flen, sizeof(long), 1, fin);
                long f_i = 0;
                while (f_i < flen)
                {
                    fread(&u_ch, sizeof(unsigned char), 1, fin);
                    for (int k = 0; k < 8; k++)
                    {
                        bit[k] = u_ch % 2;
                        u_ch /= 2;
                    }
                    for (int k = 7; k >= 0; k--)
                    {
                        if (bit[k] == 0)
                        {
                            i = HT[i].lchild;
                        }
                        else
                        {
                            i = HT[i].rchild;
                        }
                        if (HT[i].lchild == 0 && HT[i].rchild == 0)
                        {
                            u_ch = chtable[i];
                            fwrite(&u_ch, sizeof(unsigned char), 1, foutp);
                            f_i++;
                            if (f_i == flen)
                                break;
                            i = m;
                        }
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
    // fwrite(&n, sizeof(int), 1, foutp);
    fprintf(foutp, "%d\n", n);
    int m = 2 * n - 1;
    for (i = 1; i <= n; i++)
    {
        // printf("%d %u %u %u %u\n", chtable[i], T[i].weight, T[i].parent,T[i].lchild, T[i].rchild);
        // fwrite(&chtable[i], sizeof(unsigned char), 1, foutp);
        // fwrite(&T[i].weight, sizeof(unsigned int), 1, foutp);
        // fwrite(&T[i].parent, sizeof(unsigned int), 1, foutp);
        // fwrite(&T[i].lchild, sizeof(unsigned int), 1, foutp);
        // fwrite(&T[i].rchild, sizeof(unsigned int), 1, foutp);
        fprintf(foutp, "%hhu %u %u %u %u\n", chtable[i], T[i].weight, T[i].parent, T[i].lchild, T[i].rchild);
    }
    for (; i <= m; i++)
    {
        // printf("%u %u %u %u\n", T[i].weight, T[i].parent,T[i].lchild, T[i].rchild);
        // fwrite(&T[i].weight, sizeof(unsigned int), 1, foutp);
        // fwrite(&T[i].parent, sizeof(unsigned int), 1, foutp);
        // fwrite(&T[i].lchild, sizeof(unsigned int), 1, foutp);
        // fwrite(&T[i].rchild, sizeof(unsigned int), 1, foutp);
        fprintf(foutp, "%u %u %u %u\n", T[i].weight, T[i].parent, T[i].lchild, T[i].rchild);
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
