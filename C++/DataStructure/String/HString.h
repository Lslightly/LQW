#ifndef HSTRING_H_
#define HSTRING_H_ 1
//  堆分配存储表示串
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef struct
{
    char *ch;
    int length;
} HString;

//  生成一个其值等于串常量chars的串T
Status StrAssign(HString &T, char *chars);
//  返回串长
int StrLength(HString T);
//  若S>T，返回值>0;S==T，返回值=0；S<T，返回值<0
int StrCompare(HString S, HString T);
//  将S清为空串
Status ClearString(HString &S);
//  用T返回由S1，S2联结而成的新串
Status Concat(HString &T, HString S1, HString S2);
//  1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos+1
//  返回串S的第pos位置起长为len的子串
Status SubString(HString &Sub, HString S, int pos, int len);

//  1<=pos<=StrLength(S)+1。在串S的第pos个字符前插入串T
Status StrInsert(HString &S, int pos, HString T)
{
    if (pos < 1 || pos > S.length + 1)
        return ERROR;
    if (T.length)
    {
        if (!(S.ch = (char *)realloc(S.ch, sizeof(*S.ch) * (S.length + T.length)))) //  重新分配内存
            exit(OVERFLOW);
        for (int i = S.length - 1; i >= pos - 1; i--)
            S.ch[i + T.length] = S.ch[i];
        for (int i = 0; i < T.length; i++)
            S.ch[pos - 1 + i] = T.ch[i];
        S.length += T.length;
    }
    return OK;
}

Status StrAssign(HString &T, char *chars)
{
    if (T.ch)
        free(T.ch);
    int i = 0;
    char *c;
    for (i = 0, c = chars; *c; i++, c++)
        ;
    if (!i)
    {
        T.ch = nullptr;
        T.length = 0;
    }
    else
    {
        if (!(T.ch = (char *)malloc(sizeof(char) * i)))
            exit(OVERFLOW);
        for (int j = 0; j < i; j++)
        {
            T.ch[j] = chars[j];
        }
        T.length = i;
    }
    return OK;
}

int StrLength(HString S)
{
    return S.length;
}

int StrCompare(HString S, HString T)
{
    for (int i = 0; i < S.length && i < T.length; i++)
    {
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    }
    return S.length - T.length; //  不等长但是前面的字符可能完全相同
}

Status ClearString(HString &S)
{
    if (S.ch)
    {
        free(S.ch);
        S.ch = nullptr;
    }
    S.length = 0;
    return OK;
}

Status Concat(HString &T, HString S1, HString S2)
{
    if (T.ch) free(T.ch);
    if (!(T.ch = (char *)malloc(sizeof(char) * (S1.length + S2.length))))
        exit(OVERFLOW);
    int i = 0;
    for (; i < S1.length; i++)
    {
        T.ch[i] = S1.ch[i];
    }
    T.length = S1.length + S2.length;
    for (; i < T.length; i++)
    {
        T.ch[i] = S2.ch[i-S1.length];
    }
    return OK;
}

Status SubString(HString &Sub, HString S, int pos, int len)
{
    if (pos < 1 || pos > S.length || len < 0 || len > S.length-pos+1)
        return ERROR;
    if (Sub.ch) free(Sub.ch);
    if (!len)
    {
        Sub.ch = nullptr;
        Sub.length = 0;
    }
    else
    {
        if (!(Sub.ch = (char *)malloc(sizeof(char) * len)))
            exit(OVERFLOW);
        int i = 0;
        for (; i < len; i++)
        {
            Sub.ch[i] = S.ch[pos-1+i];
        }
        Sub.length = len;
    }
    return OK;
}

#endif