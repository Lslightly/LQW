// File:    P3952.c
// Author:  qingwei
// Date:    2020/02/08 14:16:57
#include <stdio.h>
#include <string.h>

void Judge(void);  // 判断输入的程序时间复杂度是否正确
int max(int a, int b);  // 判断两数大小
int line(char (* value)[102], int * num, int * flag);  // 判断每行输入，若为F，返回阶数，若为E，返回-1
int Judgegrammar(char (* value)[102], int * num);  // 判断语法是否正确,正确返回0，错误返回1;

int main(void)
{
    int t = 0;      // t个程序
    scanf("%d", &t);
    for (int i = 0; i < t; i++)  // t个程序的输入
    {
        Judge();
    }
    return 0;
}

void Judge(void)
{
    int L = 0, statement = 0, tmp = 0, flag = 0;  // L行代码  statement 小明的判断, flag标志语法的正确与否，正确为0，错误为1
    scanf("%d O(", &L);
    if (scanf("%d", &tmp) == 1)
    {
        statement = 0;
        getchar();
        getchar();
    }
    else
    {
        scanf("n^%d)", &statement);
        getchar();
    }
    
    int maxh[102] = {0}, maxm[102] = {0}, w, height = 0, f, valuenum = 0; //maxh用于计算height高度的最大阶数，maxm用来保存height-1高度的初始阶数, w为临时阶数计算变量, height表示高度，有一个F加1，有一个E减1，初始为0. f用来储存F输入阶数; valuenum用来记录变量个数
    char value[102];  // 记录value 

    for (int i = 0; i < L; i++)
    {
        f = line(&value, &valuenum, &flag);
        if (f != -2)    // F
        {
            height++;
            maxm[height] = f;
            maxh[height] = f;
        }
        else    // E
        {
            if (flag == 0)
            {
                if (maxh[height] == -1) maxh[height] = 0;
                if (maxm[height-1] != -1 || height == 1)
                maxh[height-1] = max(maxm[height-1]+maxh[height], maxh[height-1]);
                maxh[height] = 0;
                maxm[height] = 0;
                height--;
            }
        }
    }
    if (flag != 0)
        printf("ERR\n");
    else if (height != 0)
        printf("ERR\n");
    else
    {
        if (maxh[0] == statement)
            printf("Yes\n");
        else
            printf("No\n"); 
    }
}

int max(int a, int b)
{
    return (a > b)?a:b;
}

int line(char (* value)[102], int * num, int * flag)
{
    char base;  //base
    int a = 0, b = 0;  //a为左边的数，b为右边的数
    int w;
    if (scanf("%c", &base) && base == 'E')
    {
        getchar();
        *flag += Judgegrammar(value, num);
        (*num)--;
        if (*num < 0)
        {
            *num = 0;
            *flag += 1;
        }
        return -2;
    }
    else
    {
        getchar();
        scanf("%c", &(*value)[*num]);
        (*num)++;
        getchar();
        if (scanf("%d", &a) == 0)  // 左边的数为n
        {
            getchar();
            getchar();
            if (scanf("%d", &b) == 0)  //右边的数为n
            {
                w = 0;
                getchar();
                getchar();
            }
            else    //右边的数为数
            {
                getchar();
                w = -1;
            }
        }
        else    // 左边的数为数
        {
            getchar();
            if (scanf("%d", &b) == 0)   // 右边的数为n
            {
                getchar();
                w = 1;
                getchar();
            }
            else    // 右边的数为数
            {
                if (a > b)
                    w = -1;
                else
                    w = 0;
                getchar();
            }
        }
        return w;
    }
}

int Judgegrammar(char (*value)[102], int * num)
{
    for (int i = 0; i < *num; i++)
    {
        for (int j = i+1; j < *num; j++)
        {
            if ((*value)[i] == (*value)[j])
                return 1;
        }
    }
    return 0;
}

