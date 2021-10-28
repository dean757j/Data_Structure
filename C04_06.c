/*
链队列
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

Status visit(QElemType c)
{
    printf("%d ", c);
    return OK;
}

Status InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
    if (!Q->front)
        return ERROR;
    Q->front->next = NULL;
    return OK;
}

Status DestroyQueue(LinkQueue *Q)
{
    while (Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

Status ClearQueue(LinkQueue *Q)
{
    QueuePtr p, q;
    Q->rear = Q->front;
    p = Q->front->next;
    Q->front->next = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    return OK;
}

Status QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

int QueueLength(LinkQueue Q)
{
    int i = 0;
    QueuePtr p;

    p = Q.front;
    while (Q.rear != p)
    {
        i++;
        p = p->next;
    }
    return i;
}

Status GetHead(LinkQueue Q, QElemType *e)
{
    QueuePtr p;

    if (Q.front == Q.rear)
        return ERROR;

    p = Q.front->next;
    *e = p->data;
    return OK;
}

Status EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr s;
    s = (QueuePtr) malloc(sizeof(QNode));
    if (!s)
        return ERROR;

    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e)
{
    QueuePtr p;
    if (Q->front == Q->rear)
        return ERROR;

    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return OK;
}

Status QueueTraverse(LinkQueue Q)
{
    QueuePtr p;
    p = Q.front->next;
    while(p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

int main()
{
    int i;
    QElemType d;
    LinkQueue q;
    i = InitQueue(&q);
    if (i)
        printf("Init Queue success\n");
    printf("Queue is empty(1) or not(0): %d\n", QueueEmpty(q));
    printf("Length of the queue = %d\n", QueueLength(q));
    
    EnQueue(&q, -5);
    EnQueue(&q, 5);
    EnQueue(&q, 10);
    printf("After EnQ -5, 5, 10 , length of the queue = %d\n", QueueLength(q));
    printf("Queue is empty(1) or not(0): %d\n", QueueEmpty(q));
    printf("Queue ele:\n");
    QueueTraverse(q);

    i = GetHead(q, &d);
    if (i == OK)
        printf("Head ele = %d\n", d);
    
    DeQueue(&q, &d);
    printf("Deq ele = %d\n", d);
    printf("Queue ele:\n");
    QueueTraverse(q);

    i = GetHead(q, &d);
    if (i == OK)
        printf("Head ele = %d\n", d);

    ClearQueue(&q);
    if (q.front != NULL && q.rear != NULL)
        printf("After clear, q.front = %p, q.rear = %p\n", q.front, q.rear);
    else
        printf("After clear NULL!\n");
    
    DestroyQueue(&q);
    
    if (q.front != NULL && q.rear != NULL)
        printf("After destroy, q.front = %p, q.rear = %p\n", q.front, q.rear);
    else
        printf("After destroy NULL!\n");
    
    return 0;
}
