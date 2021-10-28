/*
顺序队列
*/
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int QElemType;

typedef struct
{
    QElemType data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

Status visit(QElemType c)
{
    printf("%d ", c);
    return OK;
}

Status InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status ClearQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status QueueEmpty(SqQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

Status GetHead(SqQueue Q, QElemType *e)
{
    if (Q.front == Q.rear)
        return ERROR;
    *e = Q.data[Q.front];
    return OK;
}

Status EnQueue(SqQueue *Q, QElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e)
{
    if (Q->front == Q->rear)
        return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) %MAXSIZE;
    return OK;
}

Status QueueTraverse(SqQueue Q)
{
    int i, j;
    i = Q.front;
    j = QueueLength(Q);

    while (j)
    {
        visit(Q.data[i]);
        i = (i + 1) % MAXSIZE;
        j--;
    }

    printf("\n");
    return OK;
}

int main()
{
    Status j;
    int i = 0;
    int l;
    QElemType d;
    SqQueue Q;
    InitQueue(&Q);
    printf("After init, queue is empty(1) or not(0): %d\n", QueueEmpty(Q));

    //printf("Please input int ele(count <= %d), end with -1:\n", MAXSIZE - 1);
    do
    {
        //scanf("%d", &d);
        d = i + 100;
        if (d == -1)
            break;
        i++;
        EnQueue(&Q, d);
    }while (i < MAXSIZE - 1);
    printf("Queue ele:\n");
    QueueTraverse(Q);

    printf("Length of the queue = %d\n", QueueLength(Q));
    printf("Queue is empty(1) or not(0): %d\n", QueueEmpty(Q));

    printf("%d times DeQ adn EnQ:\n", MAXSIZE);
    for (l = 1; l <= MAXSIZE; l++)
    {
        DeQueue(&Q, &d);
        printf("De ele = %d, En ele = %d\n", d, l + 1000);
        d = l + 1000;
        EnQueue(&Q, d);
    }
    l = QueueLength(Q);

    printf("Queue ele:\n");
    QueueTraverse(Q);

    if (l - 2 > 0)
        printf("DE %d ele:\n", l - 2);
    while (QueueLength(Q) > 2)
    {
        DeQueue(&Q, &d);
        printf("De ele %d\n", d);
    }

    printf("Queue ele:\n");
    QueueTraverse(Q);

    j = GetHead(Q, &d);
    if (j)
        printf("Head ele = %d\n", d);
    
    ClearQueue(&Q);
    printf("After clear, queue is empty(1) or not(0): %d\n", QueueEmpty(Q));

    return 0;
}
