/*
二叉树链式结构实现
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

typedef int Status;

int index_ = 1;
typedef char String[24];
String str;

Status StrAssign(String T, char *chars)
{
    int i;

    if (strlen(chars) > MAXSIZE)
        return ERROR;
    else
    {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
            T[i] = *(chars + i - 1);
        return OK; 
    }
}

typedef char TElemType;
TElemType Nil = ' ';

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

Status visit(TElemType e)
{
    printf("%c ",e);
    return OK;
}

Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

void DestroyBiTree(BiTree *T)
{
    if (*T)
    {
        if ((*T)->lchild)
            DestroyBiTree(&(*T)->lchild);
        if ((*T)->rchild)
            DestroyBiTree(&(*T)->rchild);
        free(*T);
        *T = NULL;
    }
}

/*
构造二叉树T，#表示空树
*/
void CreateBiTree(BiTree *T)
{
    TElemType ch;

    ch = str[index_++];
    if (ch == '#')
        *T = NULL;
    else
    {
        *T = (BiTree) malloc(sizeof(BiTNode));
        if (!*T)
            return;
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

Status BiTreeEmpty(BiTree T)
{
    if (T)
        return FALSE;
    else
        return TRUE;
}

#define ClearBiTree DestroyBiTree

int BiTreeDepth(BiTree T)
{
    int i;
    int j;

    if (!T)
        return 0;

    if (T->lchild)
        i = BiTreeDepth(T->lchild);
    else
        i = 0;
    
    if (T->rchild)
        j = BiTreeDepth(T->rchild);
    else
        j = 0;
    
    return i > j ? i + 1 : j + 1;
}

TElemType Root(BiTree T)
{
    if (BiTreeEmpty(T))
        return Nil;
    else
        return T->data;
}

TElemType Value(BiTree p)
{
    return p->data;
}

void Assign(BiTree p, TElemType value)
{
    p->data = value;
}

void PreOrderTravere(BiTree T)
{
    if (T == NULL)
        return;
    
    printf("%c", T->data);
    PreOrderTravere(T->lchild);
    PreOrderTravere(T->rchild);
}

void InOrderTravere(BiTree T)
{
    if (T == NULL)
        return;
    
    InOrderTravere(T->lchild);
    printf("%c", T->data);
    InOrderTravere(T->rchild);
}

void PostOrderTravere(BiTree T)
{
    if (T == NULL)
        return;
    
    InOrderTravere(T->lchild);
    InOrderTravere(T->rchild);
    printf("%c", T->data);
}

int main()
{
    int i;
    BiTree T;
    TElemType e;
    InitBiTree(&T);

    StrAssign(str, "ABDH#K###E##CFI###G#J##");
    CreateBiTree(&T);
    printf("Init tree, is empty(1) or not(0) :%d, depth = %d\n", BiTreeEmpty(T), BiTreeDepth(T));

    e = Root(T);
    printf("Root of the tree is %c\n", e);

    printf("\nPreOrderTravere:");
    PreOrderTravere(T);
    printf("\nInOrderTravere:");
    InOrderTravere(T);
    printf("\nPostOrderTravere:");
    PostOrderTravere(T);
    printf("\n");

    ClearBiTree(&T);
    printf("Clear tree, is empty(1) or not(0) :%d, depth = %d\n", BiTreeEmpty(T), BiTreeDepth(T));

    return 0;
}
