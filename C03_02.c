/*
线性表链式存储
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20

typedef int Status;
typedef int ELemType;

Status visit(ELemType c)
{
    printf("%d ", c);
    return OK;
}

typedef struct Node
{
    ELemType data;
    struct Node *next;
} Node, *LinkList;

/*
初始化顺序线性表
*/
Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));
    if (!(*L))
        return ERROR;

    (*L)->next = NULL;
    return OK;
}

Status ListEmpty(LinkList L)
{
    if (L->next)
        return FALSE;
    else
        return TRUE;
}

/*
整表删除
*/
Status ClearList(LinkList *L)
{
    Node *p; 
    Node *q;

    p = (*L)->next;

    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }

    (*L)->next = NULL;

    return OK;
} 

int ListLength(LinkList L)
{
    int i = 0;
    Node *p = L->next;

    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}

/*
e返回L中第i个元素的值
*/
Status GetElem(LinkList L, int i, ELemType *e)
{
    int j = 1;
    Node *p;
    p = L->next;

    while (p && j < i)
    {
        p = p->next;
        j++;
    }

    if (!p || j > i)
        return ERROR;
    
    *e = p->data;
    return OK;
}

/*
返回表中值为e的位置
*/
int LocateElem(LinkList L, ELemType e)
{
    int i = 0;
    Node *p = L->next;
    while (p)
    {
        i++;
        if (p->data == e)
            return i;
        p = p->next;
    }
    return 0;
}

/*
在表中第i个位置前插入元素e
*/
Status ListInsert(LinkList *L, int i, ELemType e)
{
    int j;
    Node *p;
    Node *s;
    p = *L;
    j = 1;

    while (p && j < i)
    {
        p = p->next;
        j++;
    }

    if (!p || j > i)
        return ERROR;

    s = (Node *) malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

/*
删除L的第i个元素，并用e返回其值
*/
Status ListDelete(LinkList *L, int i, ELemType *e)
{
    int j;
    Node *p;
    Node *q;
    p = *L;
    j = 1;

    while (p->next && j < i)
    {
        p = p->next;
        j++;
    }

    if(!(p->next) || j > i)
        return ERROR;

    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

Status ListTraverse(LinkList L)
{
    Node *p = L->next;
    while (p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

/*
头插法随机产生n个元素的表
*/
void CreateListHead(LinkList *L, int n)
{
    Node *p;
    int i;

    srand(time(0));
    *L = (LinkList) malloc(sizeof(Node));
    (*L)->next = NULL;

    for (i = 0; i < n; i++)
    {
        p = (LinkList) malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

/*
尾插法随机产生n个元素的表
*/
void CreateListTail(LinkList *L, int n)
{
    Node *p;
    Node *r;
    int i;

    srand(time(0));
    *L = (LinkList) malloc(sizeof(Node));
    r = *L;
    for (i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

int main()
{
    LinkList L;
    ELemType e;
    Status i;
    int j, k;

    i = InitList(&L);
    printf("After init: listlength = %d\n", ListLength(L));

    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j);
    printf("After inser 1~5 at head:");
    ListTraverse(L);
    printf("listlength = %d\n", ListLength(L));

    i = ListEmpty(L);
    printf("L is empty(1) or not(0): %d\n", i);

    i = ClearList(&L);
    printf("After clear: listlength = %d\n", ListLength(L));
    i = ListEmpty(L);
    printf("L is empty(1) or not(0): %d\n", i);

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    printf("After inser 1~10 at tail:");
    ListTraverse(L);
    printf("listlength = %d\n", ListLength(L));

    ListInsert(&L, 1, 0);
    printf("After inser 0 at head:");
    ListTraverse(L);
    printf("listlength = %d\n", ListLength(L));

    GetElem(L, 5, &e);
    printf("the 5th ele = %d\n", e);

    for (j = 3; j <= 4; j++)
    {
        k = LocateElem(L, j);
        if (k)
            printf("the %dth ele = %d\n", k, j);
        else
            printf("do not have ele = %d\n", j);
    }

    k = ListLength(L);
    for (j = k + 1; j > k; j--)
    {
        i = ListDelete(&L, j, &e);
        if (i == ERROR)
            printf("fail to delete %dth ele\n", j);
        else
            printf("delete %dth ele = %d\n", j, e);
    }

    printf("L ele is: ");
    ListTraverse(L);

    j = 5;
    ListDelete(&L, j, &e);
    printf("delete %dth ele = %d\n", j, e);

    printf("L ele is: ");
    ListTraverse(L);

    i = ClearList(&L);
    printf("After clear: listlength = %d\n", ListLength(L));

    CreateListHead(&L, 20);
    printf("After ListHead: ");
    ListTraverse(L);

    i = ClearList(&L);
    printf("After clear: listlength = %d\n", ListLength(L));

    CreateListTail(&L, 20);
    printf("After ListHead: ");
    ListTraverse(L);

    return 0;
}
