/*
B树BTree
*/
#include <stdio.h>
#include <stdlib.h> 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

#define m 3
#define N 17
#define MAX 5

typedef int Status;

typedef struct BTNode
{
    int keynum;
    struct BTNode *parent;
    struct Node
    {
        int key;
        struct BTNode *ptr;
        int recptr;
    } node[m + 1];
} BTNode, *BTree;

typedef struct
{
    BTNode *pt;
    int i;
    int tag;
} Result;

int Search(BTree p, int K)
{
    int i = 0;
    int j;

    for (j = 1; j <= p->keynum; j++)
    {
        if (p->node[j].key <= K)
            i = j;
    }
    return i;
}

Result SearchBTree(BTree T, int K)
{
    BTree p = T;
    BTree q = NULL;
    Status found = FALSE;
    int i = 0;
    Result r;

    while (p && !found)
    {
        i = Search(p, K);
        if (i > 0 && p->node[i].key == K)
            found = TRUE;
        else
        {
            q = p;
            p = p->node[i].ptr;
        }
    }
    r.i = i;
    if (found)
    {
        r.pt = p;
        r.tag = 1;
    }
    else
    {
        r.pt = q;
        r.tag = 0;
    }
    return r;
}

void Insert(BTree *q, int i, int key, BTree ap)
{
    int j;

    for (j = (*q)->keynum; j > i; j--)
        (*q)->node[j + 1] = (*q)->node[j];
    (*q)->node[i + 1].key = key;
    (*q)->node[i + 1].ptr = ap;
    (*q)->node[i + 1].recptr = key;
    (*q)->keynum++;
}

void split(BTree *q, BTree *ap)
{
    int i;
    int s  = (m + 1) / 2;
    *ap = (BTree) malloc(sizeof(BTNode));
    (*ap)->node[0].ptr = (*q)->node[s].ptr;

    for (i = s + 1; i <= m; i++)
    {
        (*ap)->node[i - s] = (*q)->node[i];
        if ((*ap)->node[i - s].ptr)
            (*ap)->node[i - s].ptr->parent = *ap;
    }
    (*ap)->keynum = m - s;
    (*ap)->parent = (*q)->parent;
    (*q)->keynum = s - 1;
}

void NewRoot(BTree *T, int key, BTree ap)
{
    BTree p;
    p = (BTree) malloc(sizeof(BTNode));
    p->node[0].ptr = *T;
    *T = p;
    if((*T)->node[0].ptr)
        (*T)->node[0].ptr->parent = *T;
    (*T)->parent = NULL;
    (*T)->keynum = 1;
    (*T)->node[1].key = key;
    (*T)->node[1].recptr = key;
    (*T)->node[1].ptr = ap;
    if ((*T)->node[1].ptr)
        (*T)->node[1].ptr->parent = *T;
}

void InsertBTree(BTree *T, int key, BTree q, int i)
{
    BTree ap = NULL;
    Status finished = FALSE;
    int s;
    int rx;
    
    rx = key;
    while (q && !finished)
    {
        Insert(&q, i, rx, ap);
        if (q->keynum < m)
            finished = TRUE;
        else
        {
            s = (m + 1) / 2;
            rx = q->node[s].recptr;
            split(&q, &ap);
            q = q->parent;
            if (q)
                i = Search(q, key);
        }
    }
    if (!finished)
        NewRoot(T, rx, ap);
}

void print(BTNode c, int i)
{
    printf("(%d)\n", c.node[i].key);
}

int main()
{
    int r[N] = {22, 16, 41, 58, 8, 11, 12, 16, 17, 22, 23, 31, 41, 52, 58, 59, 61};
    BTree T = NULL;
    Result s;
    int i;

    for (i = 0; i < N; i++)
    {
        s = SearchBTree(T, r[i]);
        if (!s.tag)
            InsertBTree(&T, r[i], s.pt, s.i);
    }

    printf("请输入待查找的关键字：");
    scanf("%d", &i);
    s = SearchBTree(T, i);
    if (s.tag)
        print(*(s.pt), s.i);
    else
        printf("未找到\n");

    return 0;
}
