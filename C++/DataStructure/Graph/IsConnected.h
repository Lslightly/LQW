#include "../Tree/Tree.h"
#include "Graph.h"

bool Visited[MAX_VERTEX_NUM];

//  从第v个顶点出发深度优先遍历图G，建立以T为根的生成树
void DFSTree(MGraph G, int v, CSTree &T)
{
    Visited[v] = true;
    bool first = true;
    int w;
    CSTree p, q;
    for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!Visited[w])
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
//  建立无向图的深度优先生成森林的孩子兄弟链表
void DFSForest(MGraph G, CSTree &T)
{
    T = nullptr;
    int v;
    CSTree p, q;

    for (v = 0; v < G.vexnum; v++)
    {
        Visited[v] = false;
    }

    for (v = 0; v < G.vexnum; v++)
    {
        if (!Visited[v])
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

typedef struct
{
    VertexType adjvex;
    VRType lowcost;
} Closedge;
Closedge closedge[MAX_VERTEX_NUM];
//  求大于0的closedge中最小的那个的下标
int minimum();

//  Prim算法求从u出发构造最小生成树T，输出T的各条边
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{
    int k, j, i;
    k = u;
    for (j = 0; j < G.vexnum; j++)
    {
        if (j != k)
        {
            closedge[j] = {u, G.arcs[j][k].adj};
        }
    }
    closedge[k].lowcost = 0;
    for (i = 1; i < G.vexnum; i++)
    {
        k = minimum();
        printf("%d%d\n", closedge[k].adjvex, G.vexs[k]);
        closedge[k].lowcost = 0;
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[k][j].adj < closedge[j].lowcost)
            {
                closedge[j].lowcost = G.arcs[k][j].adj;
                closedge[j].adjvex = G.vexs[k];
            }
        }
    }
}

int count = 0;
int low[MAX_VERTEX_NUM];
//  从第v0个顶点出发，深度优先遍历图G，查找并输出关节点
void DFSArticul(ALGraph G, int v0)
{
    int min, w;
    ArcNode * p;
    Visited[v0] = min = ++count;
    for (p = G.vertices[v0].firstarc; p; p=p->nextarc)
    {
        w = p->adjvex;
        if (Visited[w] == 0)
        {
            DFSArticul(G, w);
            if (low[w] < min) min = low[w];
            if (low[w] >= Visited[v0]) printf("%d %d", v0, G.vertices[v0].data);
        }
        else if (Visited[w] < min)  min = Visited[w];
    }
    low[v0] = min;
}
//  连通图G以邻接表的形式存储，查找并输出G上全部关节点。count为全局量
void FindArticul(ALGraph G)
{
    count = 1;
    Visited[0] = 1; //  邻接表上0号顶点是生成树的根
    int i = 0, v;
    for (i = 0; i < G.vexnum; i++)
        Visited[i] = 0;
    ArcNode *p = G.vertices[0].firstarc;
    v = p->adjvex;
    DFSArticul(G, v);
    if (count < G.vexnum)
    {
        printf("0 %d", G.vertices[0].data);
        while (p->nextarc)
        {
            p = p->nextarc;
            v = p->adjvex;
            if (Visited[v] == 0) DFSArticul(G, v);
        }
    }
}
