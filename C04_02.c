/*
两栈共享空间
*/
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int SElemType;

typedef struct
{
    SElemType data[MAXSIZE];
    int top1;
    int top2;
} SqDoubleStack;

Status visit(SElemType c)
{
    printf("%d ", c);
    return OK;
}

Status InitSatack(SqDoubleStack *S)
{
    S->top1  = -1;
    S->top2 = MAXSIZE;
    return OK;
}

Status ClearStack(SqDoubleStack *S)
{
    S->top1  = -1;
    S->top2 = MAXSIZE;
    return OK;
}

Status StackEmpty(SqDoubleStack S)
{
    if (S.top1 == -1 && S.top2 == MAXSIZE)
        return TRUE;
    else
        return FALSE;
}

int StackLength(SqDoubleStack S)
{
    return (S.top1 + 1 + MAXSIZE - S.top2);
}

Status Push(SqDoubleStack *S, SElemType e, int stackNumber)
{
    if (S->top1 + 1 == S->top2)
        return ERROR;
    if (stackNumber == 1)
        S->data[++S->top1] = e;
    else if (stackNumber == 2)
        S->data[--S->top2] = e;
    return OK;
}

Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S->top1 == -1)
            return ERROR;
        *e = S->data[S->top1--];
    }
    else if (stackNumber == 2)
    {
        if (S->top2 == MAXSIZE)
            return ERROR;
        *e = S->data[S->top2++];
    }
    return OK;
}

Status StackTraverse(SqDoubleStack S)
{
    int i = 0;

    while (i <= S.top1)
    {
        visit(S.data[i++]);
    }
    printf(" | ");
    i = S.top2;
    while (i < MAXSIZE)
    {
        visit(S.data[i++]);
    }
    printf("\n");
    return OK;
}

int main()
{
    int i;
    SqDoubleStack s;
    SElemType e;

    if (InitSatack(&s) == OK)
    {
        for (i = 1; i <= 5; i++)
            Push(&s, i, 1);
        for (i = MAXSIZE; i >= MAXSIZE - 2; i--)
            Push(&s, i, 2);
    }

    printf("Stack ele:\n");
    StackTraverse(s);
    printf("Stack length = %d\n", StackLength(s));

    Pop(&s, &e, 2);
    printf("Pop ele = %d\n", e);
    printf("Stack is empty(1) or not(0) = %d\n", StackEmpty(s));

    for (i = 6; i <= MAXSIZE - 2; i++)
        Push(&s, i, 1);
    
    printf("Stack ele:\n");
    StackTraverse(s);

    printf("Push 100, Stack is full(0) or not(1) = %d\n", Push(&s, 100, 1));
    printf("Stack ele:\n");
    StackTraverse(s);

    ClearStack(&s);
    printf("After clear Stack is empty(1) or not(0) = %d\n", StackEmpty(s));

    return 0;
}
