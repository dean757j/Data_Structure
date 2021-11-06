/*
邻接矩阵深度和广度遍历
*/
#include <stdio.h>

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

typedef struct
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes;
    int numEdges;
} MGraph;

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

Boolean visited[MAXVEX];

/*
邻接矩阵的深度优先递归算法
*/
void DFS(MGraph G, int i)
{
    int j;

    visited[i] = TRUE;
    printf("%c ", G.vexs[i]);
    for (j = 0; j < G.numVertexes; j++)
    {
        if (G.arc[i][j] == 1 && !visited[j])
            DFS(G, j);
    }
}

/*
邻接矩阵的深度遍历操作
*/
void DFSTraverse(MGraph G)
{
    int i;

    for (i = 0; i < G.numVertexes; i++)
        visited[i] = FALSE;
    for (i = 0 ; i < G.numVertexes; i++)
    {
        if (!visited[i])
            DFS(G, i);
    }
}

/*
邻接矩阵的广度遍历算法
*/
void BFSTraverse(MGraph G)
{
    int i;
    int j;
    Queue Q;

    for (i = 0; i < G.numVertexes; i++)
        visited[i] = FALSE;
    InitQueue(&Q);
    for (i = 0; i < G.numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = TRUE;
            printf("%c ", G.vexs[i]);
            EnQueue(&Q, i);
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &i);
                for (j = 0; j < G.numVertexes; j++)
                {
                    if (G.arc[i][j] == 1 && !visited[j])
                    { 
                        visited[j] = TRUE;
                        printf("%c ", G.vexs[j]);
                        EnQueue(&Q, j);
                    }
                }
            }
        }
    }
}

int main()
{
    MGraph G;
    CreateMGraph(&G);
    printf("\n深度遍历：");
    DFSTraverse(G);
    printf("\n广度遍历：");
    BFSTraverse(G);
    printf("\n");

    return 0;
}
