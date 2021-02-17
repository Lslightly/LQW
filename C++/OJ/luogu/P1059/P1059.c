// 去重排序
#include <stdio.h>
#include <stdlib.h>

void RemoveTheSame(int * a, int * n);  // 去重
void QuickSort(int * a, int left, int right); // 排序
void Swap(int * a, int * b); // 交换

int main(void)
{
    int n, a[100] = {0}; // n个数,最多100个要排序数
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    RemoveTheSame(a, &n);
    printf("%d\n", n);
    QuickSort(a, 0, n-1);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}

void RemoveTheSame(int * a, int * n)
{
    int k, step;
    for (int i = 0; i < *n; i++)
    {
        for (int j = i+1; j < *n; j++)
        {
            if (a[i] == a[j])
            {
                for (k = j+1; k < *n && a[k] == a[j]; k++)
                    ;
                step = k-j;
                for (; k < *n; k++)
                {
                    a[k-step] = a[k];
                }
                *n -= step;
            }
        }
    }
}

void QuickSort(int * a, int left, int right)
{
    if (right <= left)
        return ;
    else
    {
        int i = left, j = right, pivot = rand() % (right - left + 1) + left;
        Swap(&a[left], &a[pivot]);
        while (i < j)
        {
            while (a[j] >= a[left] && i < j)
                j--;
            while (a[i] <= a[left] && i < j)
                i++;
            Swap(&a[i], (i == j)?&a[left]: &a[j]);
        }
        QuickSort(a, left, i-1);
        QuickSort(a, j+1, right);
    }
}

void Swap(int * a, int * b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
