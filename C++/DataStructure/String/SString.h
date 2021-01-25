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
#endif