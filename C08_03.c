/*
平衡二叉树AVLTree
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
    int bf;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

void R_Rotate(BiTree *P)
{
    BiTree L;
    L = (*P)->lchild;
    (*P)->lchild = L->rchild;
    L->rchild = *P;
    *P = L;
}

void L_Rotate(BiTree *P)
{
    BiTree R;
    R = (*P)->rchild;
    (*P)->rchild = R->lchild;
    R->lchild = *P;
    *P = R;
}

#define LH +1
#define EH 0
#define RH -1

void LeftBalance(BiTree *T)
{
    BiTree L, Lr;
    L = (*T)->lchild;
    
    switch (L->bf)
    {
        case LH:
            (*T)->bf = EH;
            L->bf = EH;
            R_Rotate(T);
            break;
        case RH:
            Lr = L->rchild;
            switch (Lr->bf)
            {
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = EH;
                    L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lchild);
            R_Rotate(T);
    }
}

void RightBalance(BiTree *T)
{
    BiTree R, Rl;
    R = (*T)->rchild;
    
    switch (R->bf)
    {
        case RH:
            (*T)->bf = EH;
            R->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            Rl = R->lchild;
            switch (Rl->bf)
            {
                case RH:
                    (*T)->bf = LH;
                    R->bf = EH;
                    break;
                case EH:
                    (*T)->bf = EH;
                    R->bf = EH;
                    break;
                case LH:
                    (*T)->bf = EH;
                    R->bf = RH;
                    break;
            }
            Rl->bf = EH;
            R_Rotate(&(*T)->rchild);
            L_Rotate(T);
    }
}

Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T)
    {
        *T = (BiTree) malloc(sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else
    {
        if (e == (*T)->data)
        {
            *taller = FALSE;
            return FALSE;
        }
        if (e < (*T)->data)
        {
            if (!InsertAVL(&(*T)->lchild, e, taller))
                return FALSE;
            if (taller)
            {
                switch ((*T)->bf)
                {
                    case LH:
                        LeftBalance(T);
                        *taller = FALSE;
                        break;
                    case EH:
                        (*T)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                }
            }
        }
        else
        {
            if (!InsertAVL(&(*T)->rchild, e, taller))
                return FALSE;
            if (*taller)
            {
                switch ((*T)->bf)
                {
                    case LH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                    case EH:
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;
                    case RH:
                        RightBalance(T);
                        *taller = FALSE;
                        break;
                }
            }
        }
    }
    return TRUE;
}

int main()
{
    int i;
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    BiTree T = NULL;
    Status taller;

    for (i = 0; i < 10; i ++)
        InsertAVL(&T, a[i], &taller);

    return 0;
}
