/*
邻接表深度和广度遍历
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int Boolean;

typedef char VertexType;
typedef int EdgeType;
typedef int QElemType;

#define MAXSIZE 9
#define MAXEDGE 15
#define MAXVEX 9
#define INFINITY 65535

typedef char VertexType;
typedef int EdgeType;
typedef int QElemType;

typedef struct
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes;
    int numEdges;
} MGraph;

/* 边表结点 */
typedef struct EdgeNode
{
    int adjvex;
    int weight;
    struct EdgeNode *next;
} EdgeNode;

/*  顶点表结点 */
typedef struct VertexNode
{
    int in;
    VertexType data;
    EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes;
    int numEdges;
} graphAdjList, *GraphAdjList;

typedef struct
{
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;

Status InitQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status QueueEmpty(Queue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

Status EnQueue(Queue *Q, QElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

Status DeQueue(Queue *Q, QElemType *e)
{
    if (Q->front == Q->rear)
        return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) %MAXSIZE;
    return OK;
}

void CreateMGraph(MGraph *G)
{
    int i;
    int j;

    G->numVertexes = 9;
    G->numEdges = 15;

    G->vexs[0] = 'A';
    G->vexs[1] = 'B';
    G->vexs[2] = 'C';
    G->vexs[3] = 'D';
    G->vexs[4] = 'E';
    G->vexs[5] = 'F';
    G->vexs[6] = 'G';
    G->vexs[7] = 'H';
    G->vexs[8] = 'I';

    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = 0; j < G->numVertexes; j++)
            G->arc[i][j] = 0;
    }

    G->arc[0][1] = 1;
    G->arc[0][5] = 1;

    G->arc[1][2] = 1;
    G->arc[1][8] = 1;
    G->arc[1][6] = 1;

    G->arc[2][3] = 1;
    G->arc[2][8] = 1;

    G->arc[3][4] = 1;
    G->arc[3][6] = 1;
    G->arc[3][7] = 1;
    G->arc[3][8] = 1;

    G->arc[4][5] = 1;
    G->arc[4][7] = 1;

    G->arc[5][6] = 1;

    G->arc[6][7] = 1;

    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = i; j < G->numVertexes; j++)
            G->arc[j][i] = G->arc[i][j];
    }
}

/*
利用邻接矩阵构建邻接表
*/
void CreateALGraph(MGraph G, GraphAdjList *GL)
{
    int i;
    int j;
    EdgeNode *e;

    *GL = (GraphAdjList) malloc(sizeof(graphAdjList));
    (*GL)->numVertexes = G.numVertexes;
    (*GL)->numEdges = G.numEdges;
    for (i = 0; i < G.numVertexes; i++)
    {
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].firstedge = NULL;
    }

    for (i = 0; i < G.numVertexes; i++)
    {
        for (j = 0; j < G.numVertexes; j++)
        {
            if (G.arc[i][j] == 1)
            {
                e = (EdgeNode *) malloc(sizeof(EdgeNode));
                e->adjvex = j;
                e->next = (*GL)->adjList[i].firstedge;
                (*GL)->adjList[i].firstedge = e;
                (*GL)->adjList[j].in++;
            }
        }
    }
}

Boolean visited[MAXSIZE];

/*
邻接表的深度优先递归算法
*/
void DFS(GraphAdjList GL, int i)
{
    EdgeNode *p;
    
    visited[i] = TRUE;
    printf("%c ", GL->adjList[i].data);
    p = GL->adjList[i].firstedge;
    while (p)
    {
        if (!visited[p->adjvex])
            DFS(GL, p->adjvex);
        p = p->next;
    }
}

/*
邻接表的深度遍历操作
*/
void DFSTraverse(GraphAdjList GL)
{
    int i;

    for (i = 0; i < GL->numVertexes; i++)
        visited[i] = FALSE;
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (!visited[i])
            DFS(GL, i);
    }
}

/*
邻接表的广度遍历算法
*/
void BFSTraverse(GraphAdjList GL)
{
    int i;
    EdgeNode *p;
    Queue Q;

    for (i = 0; i < GL->numVertexes; i++)
        visited[i] = FALSE;
    InitQueue(&Q);
    for (i = 0 ; i < GL->numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = TRUE;
            printf("%c ", GL->adjList[i].data);
            EnQueue(&Q, i);
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &i);
                p = GL->adjList[i].firstedge;
                while (p)
                {
                    if (!visited[p->adjvex])
                    {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", GL->adjList[p->adjvex].data);
                        EnQueue(&Q, p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
}

int main()
{
    MGraph G;
    GraphAdjList GL;
    CreateMGraph(&G);
    CreateALGraph(G, &GL);

    printf("\n深度遍历：");
    DFSTraverse(GL);
    printf("\n广度遍历：");
    BFSTraverse(GL);
    printf("\n");

    return 0;
}
