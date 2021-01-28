#ifndef MATRIX_H_
#define MATRIX_H_ 1
//  稀疏矩阵
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

//  1.  三元组顺序表
#define MAXSIZE 12500
typedef struct
{
    int i, j; //  行下标，列下标
    ElemType e;
} Triple;

typedef struct
{
    Triple data[MAXSIZE + 1]; //  非零元三元组表，data[0]未用
    int mu, nu, tu;           //  矩阵行数，列数，非零元个数
} TSMatrix;

Status TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu)
    {
        int q = 1;
        for (int col = 1; col <= M.nu; col++)
        {
            for (int p = 1; p <= M.tu; p++)
            {
                if (M.data[p].j == col)
                {
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].e = M.data[p].e;
                    ++q;
                }
            }
        }
    }
    return OK;
}

Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int *num = (int *)malloc(sizeof(int) * (M.nu + 1));
    int *cpot = (int *)malloc(sizeof(int) * (M.nu + 1));
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu)
    {
        int col, q, p, t;
        for (col = 1; col <= M.nu; col++)
            num[col] = 0;
        for (t = 1; t <= M.tu; t++)
            num[M.data[t].j]++;
        cpot[1] = 1;
        for (col = 2; col <= M.nu; col++)
        {
            cpot[col] = cpot[col - 1] + num[col - 1];
        }
        for (p = 1; p <= M.tu; p++)
        {
            col = M.data[p].j;
            q = cpot[col];
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }
    return OK;
}

#define MAXRC 200
//  2.  行逻辑链接的顺序表
typedef struct
{
    Triple data[MAXSIZE + 1]; //  非零三元组表
    int rpos[MAXRC + 1];      //  各行第一个元素的位置表
    int mu, nu, tu;           //  行数、列数、非零元个数
} RLSMatrix;

Status MultiSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{
    if (M.nu != N.mu)
        return ERROR;
    Q.mu = M.mu;
    Q.nu = N.nu;
    Q.tu = 0;
    int *ctemp = (int *)malloc(sizeof(int) * (Q.nu + 1));
    int arow;
    if (M.tu * N.tu != 0)
    {
        for (arow = 1; arow <= M.mu; arow++)
        {
            for (int i = 1; i <= Q.nu; i++)
            {
                ctemp[i] = 0;
            }

            Q.rpos[arow] = Q.tu + 1;
            int tp;
            if (arow < M.mu)
                tp = M.rpos[arow + 1];
            else
                tp = M.tu + 1;

            int p, q;
            int brow, ccol;
            int t;
            for (p = M.rpos[arow]; p < tp; p++)
            {
                brow = M.data[p].j;
                if (brow < N.mu)
                    t = N.rpos[brow + 1];
                else
                    t = N.tu + 1;
                for (q = N.rpos[brow]; q < t; q++)
                {
                    ccol = N.data[q].j;
                    ctemp[ccol] += N.data[q].e * M.data[p].e;
                }
            }
            for (ccol = 1; ccol <= Q.nu; ccol++)
            {
                if (ctemp[ccol])
                {
                    if (++Q.tu > MAXSIZE)
                        return ERROR;
                    Q.data[Q.tu] = {arow, ccol, ctemp[ccol]};
                }
            }
        }
    }
    return OK;
}

//  3.  十字链表
typedef struct OLNode
{
    int i, j;
    ElemType e;
    struct OLNode *right, *down;
} OLNode, *OLink;

typedef struct
{
    OLink *rhead, *chead;
    int mu, nu, tu;
} CrossList;

Status CreateSMatrix_OL(CrossList &M)
{
    int m, n, t;
    M.mu = m;
    M.nu = n;
    M.tu = t;
    if (!(M.rhead = (OLink *)malloc(sizeof(*M.rhead) * (m + 1))))
        exit(OVERFLOW);
    if (!(M.chead = (OLink *)malloc(sizeof(*M.chead) * (n + 1))))
        exit(OVERFLOW);

    for (int i = 0; i <= m; i++)
        M.rhead[i] = nullptr;
    for (int i = 0; i <= n; i++)
        M.rhead[i] = nullptr;
    int i, j, e;
    OLink p, q;
    for (scanf("%d%d%d", &i, &j, &e); i != 0; scanf("%d%d%d", &i, &j, &e))
    {
        if (!(p = (OLink)malloc(sizeof(*p))))
            exit(OVERFLOW);
        p->i = i;
        p->j = j;
        p->e = e;
        if (M.rhead[i] == nullptr || M.rhead[i]->j > j)
        {
            p->right = M.rhead[i];
            M.rhead[i] = p;
        }
        else
        {
            for (q = M.rhead[i]; (q->right) && q->right->j < j; q = q->right)
                ;
            p->right = q->right;
            q->right = p;
        }
        if (M.chead[j] == nullptr || M.chead[j]->i > i)
        {
            p->down = M.chead[j];
            M.chead[j] = p;
        }
        else
        {
            for (q = M.chead[j]; (q->down) && q->down->i < i; q = q->down)
                ;
            p->down = q->down;
            q->down = p;
        }
    }
    return OK;
}

//  将B矩阵加到A上
Status AddSMatrix(CrossList &A, CrossList B)
{
    int i, j;
    OLink pa, pb, pre;
    OLink *hl = (OLink *)malloc(sizeof(*hl) * (A.nu));
    for (j = 1; j <= A.nu; j++)
    {
        hl[j] = A.chead[j];
    }

    for (i = 1; i <= A.mu; i++)
    {
        pa = A.rhead[i];
        pb = B.rhead[i];
        pre = nullptr;

        while (!pb)
        {
            OLink p = (OLink)malloc(sizeof(*p));
            p->i = pb->i;
            p->j = pb->j;
            p->e = pb->e;
            if (!pa || pa->j > pb->j)
            {
                if (!pre)
                    A.rhead[p->i] = p;
                else
                    pre->right = p;
                p->right = pa;
                pre = p;
                if (!A.chead[p->j] || A.chead[p->j]->i > p->i)
                {
                    p->down = A.chead[p->j];
                    A.chead[p->j] = p;
                }
                else
                {
                    for (; hl[p->j]->down && hl[p->j]->down->i < p->i; hl[p->j] = hl[p->j]->down)
                        ;
                    p->down = hl[p->j]->down;
                    hl[p->j]->down = p;
                }
                hl[p->j] = p;
            }
            else if (pa && pa->j < pb->j)
            {
                pre = pa;
                pa = pa->right;
            }
            else if (pa->j == pb->j)
            {
                pa->e += pb->e;
                if (!pa->e)
                {
                    if (!pre)
                        A.rhead[pa->i] = A.rhead[pa->i]->right;
                    else
                        pre->right = pa->right;
                    p = pa;
                    pa = pa->right;

                    if (A.chead[p->j] == p)
                        A.chead[p->j] = hl[p->j] = p->down;
                    else
                        hl[p->j]->down = p->down;
                    free(p);
                }
            }
        }
    }
}
#endif