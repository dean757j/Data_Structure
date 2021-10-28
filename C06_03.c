/*
线索二叉树
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
typedef char TElemType;

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

typedef enum
{
    /* 0表示指向左右孩子，1表示指向前驱或后继 */
    Link,
    Thread,
} PointerTag;

typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild;
    struct BiThrNode *rchild;
    PointerTag LTag;
    PointerTag RTag;
} BiThrNode, *BiThrTree;

TElemType Nil = '#';

Status visit(TElemType e)
{
    printf("%c ", e);
}

/*
按前序输入二叉树结点值，构造线索二叉树
*/
Status CreateBiThrTree(BiThrTree *T)
{
    TElemType h;

    h = str[index_++];
    if (h == Nil)
        *T = NULL;
    else
    {
        *T = (BiThrTree) malloc(sizeof(BiThrNode));
        if (!*T)
            return ERROR;
        (*T)->data = h;
        CreateBiThrTree(&(*T)->lchild);
        if ((*T)->lchild)
            (*T)->LTag = Link;
        CreateBiThrTree(&(*T)->rchild);
        if ((*T)->rchild)
            (*T)->RTag = Link;            
    }
    return OK;
}

/* 指向刚刚访问过的结点 */
BiThrTree pre;

/*
中序遍历进行中序线索化
*/
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild);
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = pre;
        }
        if (!pre->rchild)
        {
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild);
    }
}

/*
中序遍历二叉树，并将其中序线索化，Thrt指向头结点
*/
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt = (BiThrTree) malloc(sizeof(BiThrNode));
    if (!*Thrt)
        return ERROR;
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = *Thrt;
    if (!T)
        (*Thrt)->lchild = *Thrt;
    else
    {
        (*Thrt)->lchild = T;
        pre = *Thrt;
        InThreading(T);
        pre->rchild = *Thrt;
        pre->RTag = Thread;
        (*Thrt)->rchild = pre;
    }
    return OK;
}

/*
中序遍历二叉线索树的非递归算法，T为头结点
*/
Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    
    p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)
            p = p->lchild;
        if (!visit(p->data))
            return ERROR;
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            visit(p->data);
        }
        p = p->rchild;
    }
    return  OK;
}

int main()
{
    BiThrTree H;
    BiThrTree T;

    StrAssign(str, "ABDH#K###E##CFI###G#J##");
    CreateBiThrTree(&T);
    InOrderThreading(&H, T);
    printf("中序遍历输出线索二叉树:\n");
    InOrderTraverse_Thr(H);
    printf("\n");

    return 0;
}
