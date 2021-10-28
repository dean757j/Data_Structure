/*
模式匹配KMP
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

typedef char String[MAXSIZE + 1];

/*
生成一个值等于chars的串T
*/
Status StrAssign(String T, char *chars)
{
    int i;
    if(strlen(chars) > MAXSIZE)
        return ERROR;
    else
    {
        T[0] = strlen(chars);
        for(i = 1; i <= T[0]; i++)
            T[i] = *(chars + i - 1);
        return OK;
    }
}

Status ClearString(String S)
{
    S[0] = 0;
    return OK;
}

void StrPrint(String T)
{
    int i;

    for (i = 1; i <= T[0]; i++)
        printf("%c", T[i]);
    printf("\n");
}

void NextPrint(int next[], int length)
{
    int i;

    for (i = 1; i <= length; i++)
        printf("%d", next[i]);
    printf("\n");
}

int StrLength(String S)
{
    return S[0];
}

/*
朴素的模式匹配算法
*/
int Index(String S, String T, int pos)
{
    int i = pos;
    int j = 1;

    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }

    if (j > T[0])
        return i - T[0];
    else
        return 0;
}

/*
通过计算返回子串T的next数组
*/
void get_next(String T, int *next)
{
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;

    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }

}

/*
返回子串T在主串S中第pos个字符后的位置，不存在则返回0
*/
int Index_KMP(String S, String T, int pos)
{
    int i = pos;
    int j = 1;
    int next[255];
    
    get_next(T, next);
    while (i <= S[0] && j <= T[0])
    {
        if (j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}

/*
求模式串T的next函数修正值并存入数组nextval
*/
void get_nextval(String T, int *nextval)
{
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;

    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            if (T[i] != T[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}

int Index_KMP1(String S, String T, int pos)
{
    int i = pos;
    int j = 1;
    int next[255];

    get_nextval(T, next);
    while (i <= S[0] && j <= T[0])
    {
        if (j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}

int main()
{
    int i;
    int *p;
    String s1, s2;

    StrAssign(s1, "abcdex");
    printf("s1 =: ");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc((i + 1) * sizeof(int));
    get_next(s1, p);
    printf("Next = : ");
    NextPrint(p, StrLength(s1));
    printf("\n");

    StrAssign(s1, "abcabx");
    printf("s1 =: ");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc((i + 1) * sizeof(int));
    get_next(s1, p);
    printf("Next = : ");
    NextPrint(p, StrLength(s1));
    printf("\n");

    StrAssign(s1, "ababaaaba");
    printf("s1 =: ");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc((i + 1) * sizeof(int));
    get_next(s1, p);
    printf("Next = : ");
    NextPrint(p, StrLength(s1));
    printf("\n");

    StrAssign(s1, "aaaaaaaab");
    printf("s1 =: ");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc((i + 1) * sizeof(int));
    get_next(s1, p);
    printf("Next = : ");
    NextPrint(p, StrLength(s1));
    printf("\n");

    StrAssign(s1, "ababaaaba");
    printf("s1 =: ");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc((i + 1) * sizeof(int));
    get_next(s1, p);
    printf("Next = : ");
    NextPrint(p, StrLength(s1));
    get_nextval(s1, p);
    printf("NextVal = : ");
    NextPrint(p, StrLength(s1));
    printf("\n");

    StrAssign(s1, "aaaaaaaab");
    printf("s1 =: ");
    StrPrint(s1);
    i = StrLength(s1);
    p = (int *) malloc((i + 1) * sizeof(int));
    get_next(s1, p);
    printf("Next = : ");
    NextPrint(p, StrLength(s1));
    get_nextval(s1, p);
    printf("NextVal = : ");
    NextPrint(p, StrLength(s1));
    printf("\n");

    StrAssign(s1, "00000000000000000000000000000000000000000000000001");
    printf("s1 =: ");
    StrPrint(s1);
    StrAssign(s2,"0000000001");
    printf("s2 =: ");
    StrPrint(s2);
    printf("\n");
    printf(" 主串和子串在第 %d 个字符处首次匹配（朴素模式匹配算法）\n",Index(s1,s2,1));
    printf(" 主串和子串在第 %d 个字符处首次匹配（ KMP 算法）\n",Index_KMP(s1,s2,1));
    printf(" 主串和子串在第 %d 个字符处首次匹配（ KMP 改良算法）\n",Index_KMP1(s1,s2,1));

    return 0;
}
