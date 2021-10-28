/*
二叉树顺序结构实现
编译选项 -lm
*/
#include <stdio.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100
/* 二叉树最大结点数 */
#define MAX_TREE_SIZE 100

typedef int Status;
typedef int TElemType;
typedef TElemType SqBitTree[MAX_TREE_SIZE];

typedef struct
{
    /* 结点的层 */
    int level;
    /* 本层序号，按满二叉树算 */
    int order;
} Position;

TElemType Nil = 0;

Status visit(TElemType c)
{
    printf("%d ", c);
    return OK;
}

/*
构造空二叉树T
*/
Status InitBiTree(SqBitTree T)
{
    int i;

    for (i = 0; i < MAX_TREE_SIZE; i++)
        T[i] = Nil;
    return OK;
}

/*
按层次序输入二叉树结点的值，构造顺序存储的二叉树
*/
Status CreateBitree(SqBitTree T)
{
    int  i = 0;

    while (i < 10)
    {
        T[i] = i + 1;

        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil)
        {
            printf("出现无双亲的非根结点%d\n", T[i]);
            return ERROR;
        }
        i++;
    }

    while (i < MAX_TREE_SIZE)
    {
        T[i] = Nil;
        i++;
    }

    return OK;
}

#define ClearBiTree InitBiTree

Status BiTreeEmpty(SqBitTree T)
{
    if (T[0] == Nil)
        return TRUE;
    else
        return FALSE;
}

/*
返回T的深度
*/
int BiTreeDepth(SqBitTree T)
{
    int i;
    int j = -1;

    for (i = MAX_TREE_SIZE - 1; i >= 0; i--)
    {
        if (T[i] != Nil)
            break;
    }
    i++;
    do
    {
        j++;
    } while (i >= powl(2, j));
    return j;
}

/*
T不空，e返回T的根，否则error
*/
Status Root(SqBitTree T, TElemType *e)
{
    if (BiTreeEmpty(T))
        return ERROR;
    else
    {
        *e = T[0];
        return OK;
    }
}

/*
返回处于位置e的结点的值
*/
TElemType Value(SqBitTree T, Position e)
{
    return T[(int) powl(2, e.level - 1) + e.order - 2];
}

/*
给处于位置e的结点赋新值
*/
Status Assign(SqBitTree T, Position e, TElemType value)
{
    int i = (int) powl(2, e.level - 1) + e.order - 2;
    /* 给叶子赋非空值但双亲为空 */
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)
        return ERROR;
    /* 给双亲赋空值但有叶子 */
    else if (value == Nil && (T[i * 2 + 1] != Nil || T[i * 2 + 2] != Nil))
        return ERROR;
    T[i] = value;
    return OK;
}
/*
返回非根结点e的双亲
*/
TElemType Parent(SqBitTree T, TElemType e)
{
    int i;

    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e)
            return T[(i + 1) / 2 - 1];
    }
    return Nil;
}

/*
返回e的左孩子
*/
TElemType LeftChild(SqBitTree T, TElemType e)
{
    int i;

    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e)
            return T[i * 2 + 1];
    }
    return Nil;
}

/*
返回e的右孩子
*/
TElemType RightChild(SqBitTree T, TElemType e)
{
    int i;

    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e)
            return T[i * 2 + 2];
    }
    return Nil;
}

/*
返回e的左兄弟
*/
TElemType LeftSibling(SqBitTree T, TElemType e)
{
    int i;

    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e && i % 2 == 0)
            return T[i - 1];
    }
    return Nil;
}

/*
返回e的右兄弟
*/
TElemType RightSibling(SqBitTree T, TElemType e)
{
    int i;

    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e && i % 2)
            return T[i + 1];
    }
    return Nil;
}

void PreTraverse(SqBitTree T, int e)
{
    visit(T[e]);
    if (T[2 * e + 1] != Nil)
        PreTraverse(T, 2 * e + 1);
    if (T[2 * e + 2] != Nil)
        PreTraverse(T, 2 * e + 2);
}

/*
先序遍历
*/
Status PreOrderTraverse(SqBitTree T)
{
    if (!BiTreeEmpty(T))
        PreTraverse(T, 0);
    printf("\n");
    return OK;
}

void InTraverse(SqBitTree T, int e)
{
    if (T[2 * e + 1] != Nil)
        InTraverse(T, 2 * e + 1);
    visit(T[e]);
    if (T[2 * e + 2] != Nil)
        InTraverse(T, 2 * e + 2);
}

/*
中序遍历
*/
Status InOrderTraverse(SqBitTree T)
{
    if (!BiTreeEmpty(T))
        InTraverse(T, 0);
    printf("\n");
    return OK;
}

void PostTraverse(SqBitTree T, int e)
{
    if (T[2 * e + 1] != Nil)
        PostTraverse(T, 2 * e + 1);
    if (T[2 * e + 2] != Nil)
        PostTraverse(T, 2 * e + 2);
    visit(T[e]);
}

/*
后序遍历
*/
Status PostOrderTraverse(SqBitTree T)
{
    if (!BiTreeEmpty(T))
        PostTraverse(T, 0);
    printf("\n");
    return OK;
}

/*
层序遍历二叉树
*/
void LevelOrderTraverse(SqBitTree T)
{
    int i = MAX_TREE_SIZE - 1;
    int j;

    while (T[i] = Nil)
        i--;
    for (j = 0; j <= i; j++)
    {
        if (T[j] != Nil)
            visit(T[j]);
    }
    printf("\n");
}

/*
按本层序号输出二叉树
*/
void Print(SqBitTree T)
{
    int j, k;
    Position p;
    TElemType e;

    for (j = 1; j <= BiTreeDepth(T); j++)
    {
        printf("第%d层：", j);
        for (k = 1; k <= powl(2, j - 1); k++)
        {
            p.level = j;
            p.order = k;
            e = Value(T, p);
            if (e != Nil)
                printf("%d:%d",k, e);
        }
        printf("\n");
    }
}

int main()
{
    Status i;
    Position p;
    TElemType e;
    SqBitTree T;
    
    InitBiTree(T);
    CreateBitree(T);
    printf("Init tree, is empty(1) or not(0) :%d, depth = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("Root of the tree is %d\n", e);
    else
        printf("Empty tree");

    printf("层序遍历二叉树：");
    LevelOrderTraverse(T);

    printf("前序遍历二叉树：");
    PreOrderTraverse(T);

    printf("中序遍历二叉树：");
    InOrderTraverse(T);

    printf("后序遍历二叉树：");
    PostOrderTraverse(T);

    printf("修改结点层号3序号2\n");
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    printf("待修改结点原值%d，新值为50\n", e);
    e = 50;
    Assign(T, p, e);

    printf("前序遍历二叉树：");
    PreOrderTraverse(T);
    printf("结点%d的双亲为%d\n", e, Parent(T, e));
    printf("左右孩子分别为：%d %d\n", LeftChild(T,e),RightChild(T,e));
    printf("左右兄弟分别为：%d %d\n", LeftSibling(T,e),RightSibling(T,e));

    ClearBiTree(T);
    printf("Clear tree, is empty(1) or not(0) :%d, depth = %d\n", BiTreeEmpty(T), BiTreeDepth(T));
    if (i)
        printf("Root of the tree is %d\n", e);
    else
        printf("Empty tree");

    return 0;
}
