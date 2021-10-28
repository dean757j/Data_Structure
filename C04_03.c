/*
链栈
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType;

typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct
{
    LinkStackPtr top;
    int count;
} LinkStack;

Status visit(SElemType c)
{
    printf("%d ", c);
    return OK;
}

Status InitStack(LinkStack  *S)
{
    S->top = (LinkStackPtr) malloc(sizeof(StackNode));
    if (!S->top)
        return ERROR;
    S->top = NULL;
    S->count = 0;
    return OK;
}

Status ClearStack(LinkStack *S)
{
    LinkStackPtr p, q;
    p = S->top;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    S->count = 0;
    return OK;
}

Status StackEmpty(LinkStack S)
{
    if (S.count == 0)
        return TRUE;
    else
        return FALSE;
}

int StackLength(LinkStack S)
{
    return S.count;
}

Status GetTop(LinkStack S, SElemType *e)
{
    if (S.top == NULL)
        return ERROR;
    else
        *e = S.top->data;
    return OK;
}

Status Push(LinkStack *S, SElemType e)
{
    LinkStackPtr s = (LinkStackPtr) malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top;
    S->top = s;
    S->count++;
    return OK;
}

Status Pop(LinkStack *S, SElemType *e)
{
    LinkStackPtr p;
    if (StackEmpty(*S))
        return ERROR;

    p = S->top;
    *e = S->top->data;
    S->top =  p->next;
    free(p);
    S->count--;
    return OK;
}

Status StackTraverse(LinkStack S)
{
    LinkStackPtr p;
    p = S.top;
    while (p)
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
    LinkStack s;
    SElemType e;

    if (InitStack(&s) == OK)
    {
        for (i = 1; i <= 10; i++)
            Push(&s, i);
    }

    printf("Stack ele:\n");
    StackTraverse(s);

    Pop(&s, &e);
    printf("Pop ele = %d\n", e);
    printf("Stack is empty(1) or not(0) = %d\n", StackEmpty(s));

    GetTop(s, &e);
    printf("Top ele = %d length = %d\n", e, StackLength(s));

    ClearStack(&s);
    printf("After clear Stack is empty(1) or not(0) = %d\n", StackEmpty(s));

    return 0;
}
