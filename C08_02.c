/*
二叉排序树BinarySortTree
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

typedef int Status;

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if (!T)
    {
        *p = f;
        return FALSE;
    }
    else if (key == T->data)
    {
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
        return SearchBST(T->lchild, key, T, p);
    else
        return SearchBST(T->rchild, key, T, p);
}

Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;

    if (!SearchBST(*T, key, NULL, &p))
    {
        s = (BiTree) malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = NULL;
        s->rchild = NULL;
        if (!p)
            *T = s;
        else if (key < p->data)
            p->lchild = s;
        else
            p->rchild = s;
        return TRUE;
    }
    else
        return FALSE;
}

Status Delete(BiTree *p)
{
    BiTree q, s;

    if ((*p)->rchild == NULL)
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if ((*p)->lchild == NULL)
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else
    {
        q = *p;
        s = (*p)->lchild;
        while (s->rchild)
        {
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;
        if (q != *p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
        free(s);
    }
    return TRUE;
}

Status DeleteBST(BiTree *T, int key)
{
    if (!*T)
        return FALSE;
    else
    {
        if (key == (*T)->data)
            return Delete(T);
        else if (key < (*T)->data)
            return DeleteBST(&(*T)->lchild, key);
        else
            return DeleteBST(&(*T)->rchild, key);
    }
}

int main()
{
    int i;
    int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
    BiTree T = NULL;

    for (i = 0; i < 10; i ++)
        InsertBST(&T, a[i]);
    DeleteBST(&T, 93);
    DeleteBST(&T, 47);

    return 0;
}
