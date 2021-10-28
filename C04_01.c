/*
顺序栈
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
    int top;
} SqStack;

Status visit(SElemType c)
{
    printf("%d ", c);
    return OK;
}

Status InitStack(SqStack *S)
{
    S->top = -1;
    return OK;
}

Status ClearStack(SqStack *S)
{
    S->top = -1;
    return OK;
}

Status StackEmpty(SqStack S)
{
    if (S.top == -1)
        return TRUE;
    else   
        return FALSE;
}

int StackLength(SqStack S)
{
    return S.top + 1;
}

/*
返回栈顶元素
*/
Status GetTop(SqStack S, SElemType *e)
{
    if (S.top == -1)
        return ERROR;
    else
        *e = S.data[S.top];
    return OK;
}

Status Push(SqStack *S, SElemType e)
{
    if (S->top == MAXSIZE - 1)
        return ERROR;
    S->top++;
    S->data[S->top] = e;
    return OK;
}

Status Pop(SqStack *S, SElemType *e)
{
    if (S->top == -1)
        return ERROR;
    *e = S->data[S->top];
    S->top--;
    return OK;
}

Status StackTraverse(SqStack S)
{
    int i = 0;
    while (i <= S.top)
    {
        visit(S.data[i++]);
    }
    printf("\n");
    return OK;
}

int main()
{
    int i;
    SqStack S;
    SElemType e;

    if (InitStack(&S) == OK)
    {
        for (i = 1; i <= 10; i++)
            Push(&S, i);
    }

    printf("Stack ele:\n");
    StackTraverse(S);
    
    Pop(&S, &e);
    printf("Pop ele = %d\n", e);

    printf("Stack is empty(1) or not(0) = %d\n", StackEmpty(S));
    
    GetTop(S, &e);
    printf("Top ele = %d length = %d\n", e, StackLength(S));

    ClearStack(&S);
    printf("Stack is empty(1) or not(0) = %d\n", StackEmpty(S));

    return 0;
}
