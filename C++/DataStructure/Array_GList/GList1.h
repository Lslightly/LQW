#ifndef GLIST1_H_
#define GLIST1_H_ 1
//  广义表的头尾链表存储表示
#include <stdlib.h>
#include "../String/SString.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef char AtomType;

typedef enum
{
    ATOM,
    LIST
} ElemTag;
typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom; //  原子节点值域
        struct
        {
            struct GLNode *hp, *tp; //  hp表头，tp表尾
        } ptr;                      //  表结点指针域
    };
} * GList;

int GListDepth(GList L)
{
    if (!L)
        return 1;
    if (L->tag == ATOM)
        return 0;
    int max;
    int dep;
    GList pp;
    for (max = 0, pp = L; pp; pp = pp->ptr.tp)
    {
        dep = GListDepth(L->ptr.hp);
        if (dep > max)
            max = dep;
    }
    return max + 1;
}

Status CopyGList(GList &T, GList L)
{
    if (!L)
        T = nullptr;
    else
    {
        if (!(T = (GList)malloc(sizeof(*T))))
            exit(OVERFLOW);
        T->tag = L->tag;
        if (L->tag == ATOM)
        {
            T->atom = L->atom;
        }
        else
        {
            CopyGList(T->ptr.hp, L->ptr.hp);
            CopyGList(T->ptr.tp, T->ptr.tp);
        }
    }
    return OK;
}

Status serve(SString &str, SString &hstr)
{
    int n = StrLength(str);
    int i = 0, k = 0;
    char ch;
    do
    {
        ++i;
        ch = str[i];
        if (ch == '(') ++k;
        else if (ch == ')') --k;
    } while (i < n && (ch != ',' || k != 0));
    if (i < n)
    {
        SubString(hstr, str, 1, i-1);
        SubString(str, str, i+1, n-i);
    }
    else
    {
        StrCopy(hstr, str);
        ClearStr(str);
    }
    
}

//  emp = "()"
Status CreateGList(GList &L, SString S)
{
    GList p, q;
    SString sub, hsub, emp;
    
    if (StrCompare(S, emp) == 0) L = nullptr;
    else
    {
        if (!(L = (GList)malloc(sizeof(*L)))) exit(OVERFLOW);
        if (StrLength(S) == 1)
        {
            L->tag = ATOM;
            L->atom = S[1];
        }
        else
        {
            L->tag = LIST;
            p = L;
            SubString(sub, S, 2, StrLength(S)-2);
            do
            {
                serve(sub, hsub);
                CreateGList(L->ptr.hp, hsub);
                q = p;
                if (!StrEmpty(sub))
                {
                    if (!(p = (GLNode *)malloc(sizeof(*p)))) exit(OVERFLOW);
                    p->tag = LIST;
                    q->ptr.tp = p;
                }
            } while (!StrEmpty(sub));
            q->ptr.tp = nullptr;
        }
    }
    return OK;
}
#endif