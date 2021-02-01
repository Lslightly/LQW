#include "../Tree/Tree.h"
#include "Graph.h"

bool visited[MAX_VERTEX_NUM];

//  建立无向图的深度优先生成森林的孩子兄弟链表
void DFSForest(MGraph G, CSTree &T)
{
    T = nullptr;
    int v;
    CSTree p, q;

    for (v = 0; v < G.vexnum; v++)
    {
        visited[v] = false;
    }

    for (v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            p = (CSTree)malloc(sizeof(*p));
            *p = {v, nullptr, nullptr};
            if (!T)
                T = p;
            else
                q = p->nextsibling;
            q = p;
            DFSTree(G, v, p);
        }
    }
}
//  从第v个顶点出发深度优先遍历图G，建立以T为根的生成树
void DFSTree(MGraph G, int v, CSTree &T)
{
    visited[v] = true;
    bool first = true;
    int w;
    CSTree p, q;
    for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
        {
            p = (CSTree)malloc(sizeof(*p));
            *p = {w, nullptr, nullptr};
            if (first)
            {
                T->firstchild = p;
                first = false;
            }
            else
            {
                q->nextsibling = p;
            }
            q = p;
            DFSTree(G, w, q);
        }
    }
}

typedef struct
{
    VertexType adjvex;
    VRType lowcost;
}Closedge;
Closedge closedge[MAX_VERTEX_NUM];
//  求大于0的closedge中最小的那个的下标
int minimum();

//  Prim算法求从u出发构造最小生成树T，输出T的各条边
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{
    int k, j, i;
    k = u;
    for ( j = 0; j < G.vexnum; j++)
    {
        if (j!=k)
        {
            closedge[j] = {u, G.arcs[j][k].adj};
        }
    }
    closedge[k].lowcost = 0;
    for ( i = 1; i < G.vexnum; i++)
    {
        k = minimum();
        printf("%d%d\n", closedge[k].adjvex, G.vexs[k]);
        closedge[k].lowcost = 0;
        for ( j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[k][j].adj < closedge[j].lowcost)
            {
                closedge[j].lowcost = G.arcs[k][j].adj;
                closedge[j].adjvex = G.vexs[k];
            }
        }
    }
}
