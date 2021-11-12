/*
排序
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_LENGTH_INSERT_SORT 7
#define MAXSIZE 10000

typedef int Status;

typedef struct
{
    int r[MAXSIZE + 1];
    int length;
} SqList;

void swap(SqList *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

void print(SqList L)
{
    int i;

    for (i = 1; i < L.length; i++)
        printf("%d,", L.r[i]);
    printf("%d", L.r[i]);
    printf("\n");
}

void BubbleSort0(SqList *L)
{
    int i, j;

    for (i = 1; i < L->length; i++)
    {
        for (j = i + 1; j <= L->length; j++)
        {
            if (L->r[i] > L->r[j])
                swap(L, i, j);
        }
    }
}

void BubbleSort(SqList *L)
{
    int i, j;

    for (i = 1; i < L->length; i++)
    {
        for (j = L->length - 1; j >= i; j--)
        {
            if (L->r[j] > L->r[j + 1])
                swap(L, j, j + 1);
        }
    }
}

void BubbleSort2(SqList *L)
{
    int i, j;
    Status flag = TRUE;

    for (i = 1; i < L->length && flag; i++)
    {
        flag = FALSE;
        for (j = L->length - 1; j >= i; j--)
        {
            if (L->r[j] > L->r[j + 1])
            {
                swap(L, j , j + 1);
                flag = TRUE;
            }
        }
    }
}

/* 简单选择排序 */
void SelectSort(SqList *L)
{
    int i, j;
    int min;

    for (i = 1; i < L->length; i++)
    {
        min = i;
        for (j = i + 1; j <= L->length; j++)
        {
            if (L->r[min] > L->r[j])
                min = j;
        }
        if (i != min)
            swap(L, i, min);
    }

}

/* 直接插入排序 */
void InsertSort(SqList *L)
{
    int i, j;
    
    for (i = 2; i <= L->length; i++)
    {
        if (L->r[i] < L->r[i - 1])
        {
            L->r[0] = L->r[i];
            for (j = i - 1; L->r[j] > L->r[0]; j--)
                L->r[j + 1] = L->r[j];
            L->r[j + 1] = L->r[0];
        }
    }
}

/* 希尔排序 */
void ShellSort(SqList *L)
{
    int i, j;
    int k = 0;
    int increment = L->length;

    do
    {
        increment = increment / 3 + 1;
        for (i = increment + 1; i <= L->length; i++)
        {
            if (L->r[i] < L->r[i - increment])
            {
                L->r[0] = L->r[i];
                for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
                    L->r[j + increment] = L->r[j];
                L->r[j + increment] = L->r[0];
            }
            //printf("第%d次排序结果:", ++k);
            //print(*L);
        }
    } while (increment > 1);
}

void HeapAdjust(SqList *L, int s, int m)
{
    int temp;
    int j;
    
    temp = L->r[s];
    for (j = 2 * s; j <= m; j *= 2)
    {
        if (j < m && L->r[j] < L->r[j + 1])
            j++;
        if (temp >= L->r[j])
            break;
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}

/* 堆排序 */
void HeapSort(SqList *L)
{
    int i;

    for (i = L->length / 2; i > 0; i--)
        HeapAdjust(L, i, L->length);

    for (i = L->length; i > 1; i--)
    {
        swap(L, 1, i);
        HeapAdjust(L, 1, i - 1);
    }
}

/* 归并排序 */
void Merge(int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;

    for (j = m + 1, k = i; i <= m && j <=n; k++)
    {
        if (SR[i] < SR[j])
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }
    if (i <= m)
    {
        for (l = 0; l <= m - i; l++)
            TR[k + l] = SR[i + l];
    }
    if (j <= n)
    {
        for (l = 0; l <= n - j; l++)
            TR[k + l] = SR[j + l];
    }
}

void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE + 1];

    if (s == t)
        TR1[s] = SR[s];
    else
    {
        m = (s + t) / 2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m + 1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void MergeSort(SqList *L)
{
    MSort(L->r, L->r, 1, L->length);
}

void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;

    while ( i <= n - 2 * s + 1)
    {
        Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
        i = i + 2 * s;
    }
    if (i < n - s + 1)
        Merge(SR, TR, i, i + s - 1, n);
    else
    {
        for (j = i; j <= n; j++)
            TR[j] = SR[j];
    }
}

void MergeSort2(SqList *L)
{
    int *TR = (int *) malloc(L->length * sizeof(int));
    int k = 1;
    
    while (k < L->length)
    {
        MergePass(L->r, TR, k, L->length);
        k = 2 * k;
        MergePass(TR, L->r, k, L->length);
        k = 2 * k;
    }
}

int Partition(SqList *L, int low, int high)
{
    int pivotkey;

    pivotkey = L->r[low];
    while (low < high)
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        swap(L, low, high);
        while (low < high && L->r[low] <= pivotkey)
            low++;
        swap(L, low, high);
    }
    return low;
}

void QSort(SqList *L, int low, int high)
{
    int pivot;
    
    if (low < high)
    {
        pivot = Partition(L, low, high);
        QSort(L, low, pivot - 1);
        QSort(L, pivot + 1, high);
    }
}

/* 快速排序 */
void QuickSort(SqList *L)
{
    QSort(L, 1, L->length);
}

int Partition1(SqList *L, int low, int high)
{
    int pivotkey;
    int m = low + (high - low) / 2;

    if (L->r[low] > L->r[high])
        swap(L, low, high);
    if (L->r[m] > L->r[high])
        swap(L, high, m);
    if (L->r[m] >L->r[low])
        swap(L, m, low);

    pivotkey = L->r[low];
    L->r[0] = pivotkey;
    while (low < high)
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        swap(L, low, high);
        while (low < high && L->r[low] <= pivotkey)
            low++;
        swap(L, low, high);
    }
    L->r[low] = L->r[0];
    return low;
}

void QSort1(SqList *L, int low, int high)
{
    int pivot;

    if ((high - low) > MAX_LENGTH_INSERT_SORT)
    {
        while (low < high)
        {
            pivot = Partition1(L, low, high);
            QSort1(L, low, pivot - 1);
            low = pivot + 1;
        }
    }
    else
        InsertSort(L);
}

void QuickSort1(SqList *L)
{
    QSort1(L, 1, L->length);
}

#define N 9

int main()
{
    int i;
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20};

    SqList I0, I1, I2, I3, I4, I5, I6, I7, I8, I9, I10;

    for (i = 0; i < N; i++)
        I0.r[i + 1] = d[i];
    I0.length = N;
    I1 = I2 = I3 = I4 = I5 = I6 = I7 = I8 = I9 = I10 = I0;
    printf("排序前：\n") ;
    print(I0);

    printf("初级冒泡排序：\n");
    BubbleSort0(&I0);
    print(I0);

    printf("冒泡排序：\n");
    BubbleSort(&I1);
    print(I1);

    printf("改进冒泡排序：\n");
    BubbleSort2(&I2);
    print(I2);

    printf("选择排序：\n");
    SelectSort(&I3);
    print(I3);

    printf("直接插入排序：\n");
    InsertSort(&I4);
    print(I4);

    printf("希尔排序：\n");
    ShellSort(&I5);
    print(I5);

    printf("堆排序：\n");
    HeapSort(&I6);
    print(I6);

    printf("归并排序（递归）：\n");
    MergeSort(&I7);
    print(I7);

    printf("归并排序（非递归）：\n");
    MergeSort2(&I8);
    print(I8);

    printf("快速排序：\n");
    QuickSort(&I9);
    print(I9);

    printf("改进快速排序：\n");
    QuickSort1(&I10);
    print(I10);

    return 0;
}
