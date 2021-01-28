#ifndef SSTRING_H_
#define SSTRING_H_ 1
//  定长顺序表示串
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN + 1]; //  0号单元存储串长

int Index(SString S, SString T, int pos);
int Index_KMP(SString S, SString T, int pos);
void get_next(SString T, int *next);

//  用T返回由S1和S2联结而成的新串。若未截断，则返回TRUE；否则返回FALSE
Status Concat(SString &T, SString S1, SString S2)
{
    Status uncut;
    int i = 1;
    if (S1[0] + S2[0] <= MAXSTRLEN)
    {
        for (; i <= S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (; i <= S1[0] + S2[0]; i++)
        {
            T[i] = S2[i - S1[0]];
        }
        T[0] = S1[0] + S2[0];
        uncut = TRUE;
    }
    else if (S1[0] < MAXSTRLEN)
    {
        for (; i <= S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (; i <= MAXSTRLEN; i++)
        {
            T[i] = S2[i - S1[0]];
        }
        T[0] = MAXSTRLEN;
        uncut = FALSE;
    }
    else
    {
        for (; i <= MAXSTRLEN; i++)
        {
            T[i] = S1[i];
        }
        T[0] = MAXSTRLEN;
        uncut = FALSE;
    }
    return uncut;
}

//  用Sub返回串S中的第pos个字符开始长度为len的子串
//  其中，1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos+1
Status SubString(SString &Sub, SString S, int pos, int len)
{
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1) return ERROR;
    int i = 1;
    for (; i <= len; i++)
    {
        Sub[i] = S[pos+i-1];
    }
    Sub[0] = len;
    return OK;
}

//  返回子串T在主串S第pos个字符之后的位置，若不存在，返回0。
//  T非空，1<=pos<=StrLength(S)
//  时间复杂度O(n+m)
int Index(SString S, SString T, int pos)
{
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[i])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i-j+2;
            j = 1;
        }
    }
    if (j > T[0]) return i-j+1;
    else return 0;
}

//  利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
//  其中，T非空，1<=pos<=StrLength(S)
int Index_KMP(SString S, SString T, int pos)
{
    int i = pos, j = 1;
    int * next = (int *)malloc(sizeof(int)*(T[0]+1));
    get_next(T, next);
    while (i <= S[0] && j <= T[0])
    {
        if (j == 0 || S[i] == T[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > T[0]) return i-j+1;
    else return 0;
}

void get_next(SString T, int *next)
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

void get_nextval(SString T, int *nextval)
{
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            ++i;
            ++j;
            if (T[i] != T[j]) nextval[i] = j;
            else nextval[i] = nextval[j];
        }
        else j = nextval[j];
    }
}

int StrLength(SString S)
{
    return S[0];
}

int StrCompare(SString S, SString T)
{
    int i;
    for (i = 1; i <= S[0] && i <= T[0]; i++)
    {
        if (S[i] != T[i]) return S[i] - T[i];
    }
    return S[0] - T[0];
}

Status StrCopy(SString &T, SString S)
{
    T[0] = S[0];
    for (int i = 1; i <= S[0]; i++)
    {
        T[i] = S[i];
    }
    return OK;
}

Status ClearStr(SString &S)
{
    S[0] = 0;
    return OK;
}

Status StrEmpty(SString S)
{
    if (S[0] == 0) return TRUE;
    else return FALSE;
}
#endif