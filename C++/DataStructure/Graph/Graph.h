#ifndef GRAPH_H_
#define GRAPH_H_ 1
//  图的各种表示形式
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int VRType;
typedef char InfoType;
typedef int VertexType;

#define INFINITY __INT32_MAX__
#define MAX_VERTEX_NUM 20
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind; //  {有向图，有向网，无向图，无向网}
//  数组(邻接矩阵)存储表示
typedef struct ArcCell
{
    VRType adj;     //  顶点关系类型，无权图用0，1表示相邻与否；带权图则为权值类型
    InfoType *info; //  其他信息
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM]; //  顶点向量
    AdjMatrix arcs;
    int arcnum, vexnum; //  边数量，顶点数量
    GraphKind kind;     //  图种类
} MGraph;

//  邻接矩阵构造图G
Status CreateGraph(MGraph &G);
//  邻接矩阵构造有向图
Status CreateDG(MGraph &G);
//  邻接矩阵构造有向网
Status CreateDN(MGraph &G);
//  邻接矩阵构造无向图
Status CreateUDG(MGraph &G);
//  邻接矩阵构造无向网
Status CreateUDN(MGraph &G);
//  找到第一个邻接点
int FirstAdjVex(MGraph G, int v);
//  找到下一个邻接点
int NextAdjVex(MGraph G, int v, int w);

Status CreateGraph(MGraph &G)
{
    scanf("%d", &G.kind);
    switch (G.kind)
    {
    case DG:
        // return CreateDG(G);
    case DN:
        // return CreateDN(G);
    case UDG:
        // return CreateUDG(G);
    case UDN:
        return CreateUDN(G);
    default:
        return ERROR;
    }
}
Status CreateUDN(MGraph &G)
{
    char IncInfo[100];
    scanf("%d%d%s", &G.vexnum, &G.arcnum, IncInfo);
    int i = 0, j = 0, v1, v2, w;
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%d", &G.vexs[i]);
    }
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = {INFINITY, nullptr};
        }
    }
    for (int k = 0; k < G.arcnum; k++)
    {
        scanf("%d%d%d", &v1, &v2, &w);
        G.arcs[v1][v2].adj = w;
        G.arcs[v2][v1] = G.arcs[v1][v2];
    }
    return OK;
}

//  邻接表存储形式
typedef struct ArcNode
{
    int adjvex;              //  该弧所指的顶点的位置
    struct ArcNode *nextarc; //  下一个弧
    InfoType *info;
} ArcNode;
typedef struct VNode
{
    VertexType data;   //  顶点信息
    ArcNode *firstarc; //  第一个邻接点指针
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
    int kind;
} ALGraph;

//  十字链表存储表示
typedef struct ArcBox
{
    int tailvex, headvex;
    struct ArcBox *tlink, *hlink;
    InfoType *info;
} ArcBox;
typedef struct VexNode
{
    VertexType data;
    ArcBox *firstin, *firstout;
} VexNode;
typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM];
    int vexnum, arcnum;
} OLGraph;

Status CreateDG_OL(OLGraph &G)
{
    int i, v1, v2;
    char IncInfo[20];
    ArcBox *p;
    scanf("%d%d%s", &G.vexnum, &G.arcnum, IncInfo);
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%d", &G.xlist[i].data);
        G.xlist[i].firstin = G.xlist[i].firstout = nullptr;
    }
    for (int k = 0; k < G.arcnum; k++)
    {
        scanf("%d%d", &v1, &v2);
        p = (ArcBox *)malloc(sizeof(*p));
        *p = {v1, v2, G.xlist[v2].firstin, G.xlist[v1].firstout, nullptr};
        G.xlist[v2].firstin = G.xlist[v1].firstout = p;
    }
    return OK;
}

//  邻接多重表
typedef enum
{
    unvisited,
    visited
} VisitIf;
typedef struct EBox
{
    VisitIf mark; //  访问标记
    int ivex, jvex;
    struct EBox *ilink, *jlink;
    InfoType *info;
} EBox;
typedef struct VexBox
{
    VertexType data;
    EBox *firstedge;
} VexBox;
typedef struct
{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum, arcnum;
} AMLGraph;

Status InitALGraph(ALGraph &G)
{
    cout << "input number of vertexs and arcs: ";
    cin >> G.vexnum >> G.arcnum;
    cout << "Graph kind:\n0: DiGraph\n1:DiNetwork\n2:UndiGraph\n3:UndiNetwork\n";
    cout << "input the graph kind: ";
    cin >> G.kind;
    for (int i = 0; i < G.vexnum; i++)
    {
        cout << "input number of arcs of " << i << " vertex.\n";
        int num_arcs;
        cin >> num_arcs;
        cout << "the first arc: ";
        G.vertices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
        G.vertices[i].data = i;
        cin >> G.vertices[i].firstarc->adjvex;
        G.vertices[i].firstarc->nextarc = nullptr;
        if (num_arcs == 1) continue;
        ArcNode *p = G.vertices[i].firstarc;
        for (int j = 0; j < num_arcs-1; j++)
        {
            p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
            cin >> p->adjvex;
            p = p->nextarc;
        }
    }
    return OK;
}
#endif