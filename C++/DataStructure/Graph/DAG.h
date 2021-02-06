#ifndef DAG_H_
#define DAG_H_ 1
//  有向无环图
#include "Graph.h"
#include <stack>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM]);
//  若G没有回路，则输出G的一个拓扑序列，返回OK，否则返回ERROR
Status TopologicalSort(ALGraph G)
{
    int indegree[MAX_VERTEX_NUM];
    int i, count, k;
    ArcNode *p;
    FindInDegree(G, indegree);
    stack<int> S;
    for (i = 0; i < G.vexnum; i++)
    {
        if (!indegree[i])
            S.push(i);
    }
    count = 0;
    while (!S.empty())
    {
        i = S.top();
        S.pop();
        printf("%d, %d\n", i, G.vertices[i].data);
        ++count;
        for (p = G.vertices[i].firstarc; p; p = p->nextarc)
        {
            k = p->adjvex;
            if (!(--indegree[k]))
                S.push(k);
        }
        {
            if (count < G.vexnum)
                return ERROR;
            else
                return OK;
        }
    }
}
int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];
//  求各顶点事件的最早发生时间ve，T为拓扑序列顶点栈，S为零入度顶点栈
Status TopologicalOrder(ALGraph G, stack<int> &T)
{
    int indegree[MAX_VERTEX_NUM];
    int i, j, k, count;
    ArcNode *p;
    stack<int> S;
    FindInDegree(G, indegree);
    for (i = 0; i < G.vexnum; i++)
    {
        if (!indegree[i])
            S.push(i);
    }
    for (i = 0; i < G.vexnum; i++)
    {
        ve[i] = 0;
    }
    count = 0;
    while (!S.empty())
    {
        j = S.top();
        S.pop();
        T.push(j);
        ++count;
        for (p = G.vertices[j].firstarc; p; p = p->nextarc)
        {
            k = p->adjvex;
            if (--indegree[k] == 0)
                S.push(k);
            if (ve[j] + *(p->info) > ve[k])
                ve[k] = ve[j] + *(p->info);
        }
    }
    if (count < G.vexnum)
        return ERROR;
    else
        return OK;
}

//  G为有向网，输出G的各项关键活动
Status CriticalPath(ALGraph G)
{
    stack<int> T;
    if (!TopologicalOrder(G, T))
        return ERROR;

    int i, j, k, dut;
    ArcNode *p;

    for (i = 0; i < G.vexnum; i++)
    {
        vl[i] = ve[G.vexnum - 1];
    }

    while (!T.empty())
    {
        for (j = T.top(), T.pop(), p = G.vertices[j].firstarc; p; p = p->nextarc)
        {
            k = p->adjvex;
            dut = *(p->info);
            if (vl[k] - dut < vl[j])
                vl[j] = vl[k] - dut;
        }
    }
    for (j = 0; j < G.vexnum; j++)
    {
        for (p = G.vertices[j].firstarc; p; p = p->nextarc)
        {
            k = p->adjvex;
            dut = *(p->info);
            int ee = ve[j];
            int el = ve[k] - dut;
            if (ee == el)
                printf("%d%d\n", j, k);
        }
    }
    return OK;
}
#endif
