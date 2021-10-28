/*
串
*/
#include <stdio.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40

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

Status StrCopy(String T, String S)
{
    int i;

    for (i = 0; i <= S[0]; i++)
        T[i] = S[i];
    return OK;
}

Status StrEmpty(String S)
{
    if (S[0] == 0)
        return TRUE;
    else
        return FALSE;
}

/*
比较字符串S和T，若S>T返回值大于0，S=T返回值为0，S<T返回值<0
*/
int StrCompare(String S, String T)
{
    int i;

    for (i = 1; i <= S[0] && i <= T[0]; i++)
    {
        if (S[i] != T[i])
            return S[i] - T[i];
    }
    return S[0] - T[0];
}

int StrLength(String S)
{
    return S[0];
}

Status ClearString(String S)
{
    S[0] = 0;
    return OK;
}

/*
S1和S2连接成新串T
*/
Status Concat(String T, String S1, String S2)
{
    int i;

    if (S1[0] + S2[0] <= MAXSIZE)
    {
        for (i = 1; i <= S1[0]; i++)
            T[i] = S1[i];
        for (i = 1; i <= S2[0]; i++)
            T[S1[0] + i] = S2[i];
        T[0] = S1[0] + S2[0];
        return TRUE;
    }
    else
    {
        for (i = 1; i <= S1[0]; i++)
            T[i] = S1[i];
        for (i = 1; i <= MAXSIZE - S1[0]; i++)
            T[S1[0] + i] = S2[i];
        T[0] = MAXSIZE;
        return FALSE;
    }
}

/*
用Sub返回串S的第pos个字符起长度为len的字串
*/
Status SubString(String Sub, String S, int pos, int len)
{
    int i;

    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR;

    for (i = 1; i <= len; i++)
        Sub[i] = S[pos + i - 1];
    Sub[0] = len;
    return OK;
}

/*
返回子串T在主串S中第pos个字符后的位置，不存在则返回0
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
返回子串T在主串S中第pos个字符后的位置，不存在则返回0
*/
int Index2(String S, String T, int pos)
{
    int n, m, i;
    String sub;

    if (pos > 0)
    {
        n = StrLength(S);
        m = StrLength(T);
        i = pos;

        while (i <= n - m + 1)
        {
            SubString(sub, S, i, m);
            if (StrCompare(sub, T) != 0)
                i++;
            else
                return i;
        }
    }
    return 0;
}

/*
在串S的第pos个字符前插入串T
*/
Status StrInsert(String S, int pos, String T)
{
    int i;
    if (pos < 1 || pos > S[0] + 1)
        return ERROR;
    
    if (S[0] + T[0] <= MAXSIZE)
    {
        for (i = S[0]; i>= pos; i--)
            S[i + T[0]] = S[i];
        for (i = pos; i < pos + T[0]; i++)
            S[i] = T[i - pos + 1];
        S[0] = S[0] + T[0];
        return TRUE;
    }
    else
    {
        for (i = MAXSIZE; i >= pos + T[0]; i--)
            S[i] = S[i - T[0]];
        for (i = pos; i < pos + T[0]; i++)
            S[i] = T[i - pos + 1];
        S[0] = MAXSIZE;
        return FALSE;
    }
}

/*
从串S中删除第pos个字符起长度为len的子串
*/
Status StrDelete(String S, int pos, int len)
{
    int i;
    
    if (pos < 1 || pos > S[0] - len + 1 || len < 0)
        return ERROR;
    
    for (i = pos + len; i <= S[0]; i++)
        S[i - len] = S[i];
    S[0] -= len;
    return OK;
}

/*
用V替换主串S中出现的所有与T相等的不重叠的子串
*/
Status Replace(String S, String T, String V)
{
    int i = 1;
    if (StrEmpty(T))
        return ERROR;
    
    do
    {
        i = Index(S, T, i);
        if (i)
        {
            StrDelete(S, i, StrLength(T));
            StrInsert(S, i, V);
            i += StrLength(V);
        }
    } while (i);
    return OK;
}

void StrPrint(String T)
{
    int i;

    for (i = 1; i <= T[0]; i++)
        printf("%c", T[i]);
    printf("\n");
}

int main()
{
    int i, j;
    Status k;
    char s;
    String t, s1, s2;

    k = StrAssign(s1, "abcd");
    printf("String len = %d, is empty(1) or not(0): %d\n", StrLength(s1), StrEmpty(s1));

    StrCopy(s2, s1);
    printf("Copy s1, s2:\n");
    StrPrint(s2);

    k = StrAssign(s2, "efghijk");

    i = StrCompare(s1, s2);
    if (i < 0)
        s = '<';
    else if (i == 0)
        s = '=';
    else
        s = 'v';
    printf("String s1 %c s2\n", s);
    
    k = Concat(t, s1, s2);
    printf("Concat s1 and s2, t:\n");
    StrPrint(t);
    if (k == FALSE)
        printf("Concat is full\n");

    ClearString(s1);
    printf("Clear s1:\n");
    StrPrint(s1);
    printf("String len = %d, is empty(1) or not(0): %d\n", StrLength(s1), StrEmpty(s1));

    i = 2;
    j = 3;
    printf("Substr pos = %d len = %d\n", i, j);
    k = SubString(s2, t, i, j);
    if (k)
    {
        printf("s2:\n");
        StrPrint(s2);
    }

    i = 4;
    j = 2;
    printf("Dlestr pos = %d len = %d\n", i, j);
    StrDelete(t, i, j);
    printf("After delete, t:\n");
    StrPrint(t);

    i = StrLength(s2) / 2;
    printf("Before insert, s2:\n");
    StrPrint(s2);
    printf("Before insert, t:\n");
    StrPrint(t);
    StrInsert(s2, i, t);
    printf("After insert, s2:\n");
    StrPrint(s2);

    i = Index(s2, t, 1);
    printf("s2's %dth ele begin = t\n", i);

    SubString(t, s2, 1, 1);
    printf("After sub s2 pos 1 len 1, t:\n");
    StrPrint(t);

    Concat(s1, t, t);
    printf("Concat t and t, s1:\n");
    StrPrint(s1);

    Replace(s2, t, s1);
    printf("After replace, s2:\n");
    StrPrint(s2);

    return 0;
}
