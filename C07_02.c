/*
邻接表创建
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXVEX 100

typedef int Status;
typedef char VertexType;
typedef int EdgeType;

/* 边表结点 */
typedef struct EdgeNode
{
    int adjvex;
    EdgeType info;
    struct EdgeNode *next;
} EdgeNode;

/*  顶点表结点 */
typedef struct VertexNode
{
    VertexType data;
    EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numNodes;
    int numEdges;
} GraphAdjList;

void CreateALGraph(GraphAdjList *G)
{
    int i, j, k;
    EdgeNode *e;

    printf("输入顶点数和边数：\n");
    scanf("%d %d", &G->numNodes, &G->numEdges);
    for (i = 0; i < G->numNodes; i++)
    {
        printf("输入顶点信息：\n");
        scanf(" %c", &G->adjList[i].data);
        G->adjList[i].firstedge = NULL;
    }
    for (k = 0; k < G->numEdges; k++)
    {
        printf("输入边（vi，vj）的顶点序号：\n");
        scanf(" %d %d", &i, &j);
        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;

        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = e;
    }
}

int main()
{
    GraphAdjList G;
    CreateALGraph(&G);

    return 0;
}
