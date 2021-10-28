/*
线性表顺序存储
*/
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20

typedef int Status;
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status ListEmpty(SqList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}

int ListLength(SqList L)
{
    return L.length;
}

/* 
用e返回L中第i个元素的值
*/
Status GetELem(SqList L, int i, ElemType *e)
{
    if (L.length == 0 || i < 1 || i > L.length)
        return ERROR;
    *e = L.data[i - 1];
    return OK;
}

/*
返回值为e的元素的位置，不存在则返回0
*/
int LocateElem(SqList L, ElemType e)
{
    int i;
    
    if (L.length == 0)
        return 0;
    for (i = 0; i < L.length; i++)
    {
        if (e == L.data[i])
            return i + 1;
    }
    if (i >= L.length)
        return 0;
}

/*
在L中第i个位置插入新的元素e
*/
Status ListInsert(SqList *L, int i, ElemType e)
{
    int j;

    if (L->length == MAXSIZE)
        return ERROR;
    if (i < 1 || i > L->length + 1)
        return ERROR;
    if (i <= L->length)
    {
        for (j = L->length - 1; j >= i - 1; j--)
            L->data[j + 1] = L->data[j];
    }
    L->data[i - 1] = e;
    L->length++;

    return OK;
}

/*
删除L的第i个元素，并用e返回其值
*/
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int j;

    if (L->length == 0)
        return ERROR;
    if (i < 1 || i > L->length)
        return ERROR;
    *e = L->data[i - 1];
    for (j = i; j <= L->length - 1; j++)
        L->data[j - 1] = L->data[j];
    L->length--;

    return OK;
}

Status ListTraverse(SqList L)
{
    int i;

    for (i = 0; i < L.length; i++)
        printf("%d ", L.data[i]);
    printf("\n");
    
    return OK;
}

void unionL(SqList *La, SqList Lb)
{
    int La_len, Lb_len;
    int i;
    ElemType e;

    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);
    for (i = 1; i <= Lb_len; i++)
    {
        GetELem(Lb, i, &e);
        if (!LocateElem(*La, e))
            ListInsert(La, ++La_len, e);
    }

}

int main()
{
    SqList L;
    ElemType e;
    Status i;
    int j, k;

    i = InitList(&L);
    printf("InitList: L.length = %d\n", L.length);
    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j);
    printf("insert 1~5: data = ");
    ListTraverse(L);

    printf("L.Length = %d\n", L.length);
    i = ListEmpty(L);
    printf("L is empty or not %d\n", i);

    i = ClearList(&L);
    i = ListEmpty(L);
    printf("After clear L is empty or not %d\n", i);

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    
    printf("insert 1~10: data = ");
    ListTraverse(L);
    printf("L.Length = %d\n", L.length);

    ListInsert(&L, 1, 0);
    printf("insert 0: data = ");
    ListTraverse(L);
    printf("L.Length = %d\n", L.length);

    GetELem(L, 5, &e);
    printf("The 5th ele val = %d\n", e);

    for (j = 3; j <= 4; j++)
    {
        k = LocateElem(L, j);
        if (k)
            printf("The %dth ele val is %d\n", k, j);
        else
            printf("do not have val %d\n", j);
    }

    k = ListLength(L);
    for (j = k + 1; j >= k; j--)
    {
        i = ListDelete(&L, j, &e);
        if (i == ERROR)
            printf("delete %dth ele failed\n", j);
        else
            printf("delete %dth ele val is %d\n", j, e);
    }

    printf("L is : ");
    ListTraverse(L);

    j = 5;
    ListDelete(&L, j, &e);
    printf("delete %dth ele val is %d\n", j, e);

    printf("L is : ");
    ListTraverse(L);

    SqList Lb;
    i = InitList(&Lb);
    for (j = 6; j <= 15; j++)
        i = ListInsert(&Lb, 1, j);
    
    unionL(&L, Lb);

    printf("Lb is : ");
    ListTraverse(Lb);
    printf("L after union Lb : ");
    ListTraverse(L);

    return 0;
}
