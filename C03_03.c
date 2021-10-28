/*
静态链表
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000

typedef int Status;
typedef char ElemType;

Status visit(ElemType c)
{
    printf("%c ",c);
    return OK;
}

typedef struct
{
    ElemType data;
    int cur;
} Component, StaticLinkList[MAXSIZE];

Status InitList(StaticLinkList space)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
        space[i].cur = i + 1;
    space[MAXSIZE - 1].cur = 0;
    return OK;
}

/*
返回备用链表下标
*/
int Malloc_SSL(StaticLinkList space)
{
    int i = space[0].cur;
    if (space[0].cur)
        space[0].cur = space[i].cur;

    return i;
}

/*
将下标为k的空闲结点回收到备用链表
*/
void Free_SSL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k; 
}

int ListLength(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;

    while (i)
    {
        j++;
        i = L[i].cur;
    }
    return j;
}

/*
在第i个元素前插入新元素e
*/
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
    int j, k, l;
    k = MAXSIZE - 1;
    if (i < 1 || i > ListLength(L) + 1)
        return ERROR;
    j = Malloc_SSL(L);
    if (j)
    {
        L[j].data = e;
        for (l = 1; l <= i - 1; l++)
            k = L[k].cur;
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

/*
删除L中第i个元素
*/
Status ListDelete(StaticLinkList L, int i)
{
    int j, k;
    if (i < 1 || i > ListLength(L))
        return ERROR;
    k = MAXSIZE - 1;
    for (j = 1; j <= i - 1; j++)
        k = L[k].cur;
    j = L[k].cur;
    L[k].cur = L[j].cur;
    Free_SSL(L, j);
    return OK;
}

Status ListTraverse(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;
    while (i)
    {
        visit(L[i].data);
        i = L[i].cur;
        j++;
    }
    printf("\n");
    return OK;
}

int main()
{
    StaticLinkList L;
    Status i;
    
    i = InitList(L);
    printf("After Init, length = %d\n", ListLength(L));

    i = ListInsert(L, 1, 'F');
    i = ListInsert(L, 1, 'E');
    i = ListInsert(L, 1, 'D');
    i = ListInsert(L, 1, 'B');
    i = ListInsert(L, 1, 'A');

    printf("Insert FEDBA at head:\n");
    ListTraverse(L);

    i = ListInsert(L, 3, 'C');
    printf("Insert C betweent B and D:\n");
    ListTraverse(L);

    i = ListDelete(L, 1);
    printf("Delete A:\n");
    ListTraverse(L);

    return 0;
}
