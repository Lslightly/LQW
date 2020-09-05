#include <stdio.h>
#include <stdlib.h>

void Partition2(int left, int right, int * a);  //分成两半继续排序
void swap(int * a, int * b);  //交换
void BubbleSort(int left, int right,int * a);  //对小于10的元素数组进行冒泡排序提高效率

int main()
{
    int n = 0;
    int a[100000] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    Partition2(0, n-1, a);
    for (int i = 0; i < n-1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("%d", a[n-1]);
    return 0;    
}

void Partition2(int left, int right, int * a)
{
    if (left >= right)
        return ;
    else if (right - left <=10)
    {
        BubbleSort(left, right, a);
    }
    else
    {
        int i = left, j = right, k, flag = 0; //随机挑选一个数为枢轴元素
        int pivot = rand() % (right - left + 1) + left; 
        swap(&a[left], &a[pivot]);  //将随机挑选的枢轴元素与第一个元素交换，方便快速排序
        while (i < j)
        {
            while (a[j] >= a[left] && i < j)  //j逼近
            {
                if (a[j] == a[left])
                {
                    for (k = j-1; k > i; k--)
                    {
                        if (a[k] != a[j])
                        {
                            swap(&a[k], &a[j]);
                            break;
                        }
                    }
                    if (k == i)
                    {
                        if (a[i] <= a[left])
                            swap(&a[i], &a[left]);
                        else
                        {
                            swap(&a[j], &a[i]);
                            swap(&a[left], &a[i-1]);
                            i--;
                            j--;
                        }
                        flag = 1;
                        break;
                    }
                    else continue;
                }
                j--;
            }
            if (flag) break;
            while (a[i] <= a[left] && i < j)  //i逼近
            {
                if (a[i] == a[left] && i != left)
                {
                    for (k = i+1; k < j; k++)
                    {
                        if (a[k] != a[i])
                        {
                            swap(&a[k], &a[i]);
                            break;
                        }
                    }
                    if (k == j)
                    {
                        swap(&a[left], &a[j]);
                        flag = 1;
                        break;
                    }
                    else continue;
                }
                i++;
            }
            if (flag) break;
            swap(&a[i], (i == j)?&a[left]:&a[j]);  //如果i ！= j，则交换，因为一大一小，否则将i位置的数丢到最前面进行下一次排序，原本a[left]的相对位置已排好
        }
        Partition2(left, i-1, a);
        Partition2(j+1, right, a);
    }
}

void swap(int * a, int * b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void BubbleSort(int left, int right, int * a)
{
    for (int i = left + 1; i <= right; i++)
    {
        for (int j = i; j > left && a[j] < a[j-1]; j--)
        {
            swap(&a[j], &a[j-1]);
        }
    }
}
