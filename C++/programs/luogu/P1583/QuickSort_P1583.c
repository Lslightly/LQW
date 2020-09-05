#include<stdio.h>
#include<stdlib.h>

typedef struct person
{
    int id;  //编号
    int W;  //权值
    int D;  //序号
}person;

int E[11] = {0};

void QuickSort(person ** p, int left, int right);  //快排

void BubbleSort(person ** p, int left, int right, int n);  //冒泡排k比较小的情况

void Swap(person * a, person * b);  //交换指针

int main(void)
{
    int n, k;
    person * p[20001];
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; i++)
    {
        p[i] = (person *)malloc(sizeof(person));
    }
    for (int i = 1; i < 11; i++)
    {
        scanf("%d", &E[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &(p[i]->W));
        p[i]->id = i;
    }
    QuickSort(p, 1, n);
    for (int i = 1; i <= n; i++)
    {
        p[i]->W += E[(i-1) % 10 + 1];
    }
    for (int i = 1; i <= k; i++)
    {
        for (int j = n; j > i; j--)
        {
            if (p[j]->W > p[j-1]->W)
            {
                Swap(p[j], p[j-1]);
            }
            else if (p[j]->W == p[j-1]->W && p[j]->id < p[j-1]->id)
            {
                Swap(p[j], p[j-1]);
            }
        }
    }
    for (int i = 1; i <= k; i++)
    {
        printf("%d ", p[i]->id);
    }
}

void QuickSort(person ** p, int left, int right)
{
    if (right <= left)
        return ;
    else if (right - left + 1 <= 10)
        BubbleSort(p, left, right, right - left + 1);
    else
    {
        int i = left, j = right, pivot = rand() % (right - left + 1) + left, k, flag = 0;
        Swap(p[left], p[pivot]);
        while (i < j)
        {
            while (p[left]->W >= p[j]->W && i < j)
            {
                if (p[j]->W == p[left]->W)
                {
                    for (k = j-1; k > i; k--)
                    {
                        if (p[k]->W != p[j]->W)
                        {
                            Swap(p[k], p[j]);
                            break;
                        }
                    }
                    if (k == i)
                    {
                        if (p[k]->W >= p[left]->W)
                        {
                            Swap(p[k], p[left]); 
                        }
                        else
                        {
                            Swap(p[j], p[i]);
                            Swap(p[left], p[i-1]);
                            i--;
                            j--;
                        }
                        BubbleSort(p, i, j, j-i+1);
                        flag = 1;
                        break;
                    }
                    else
                    {
                        BubbleSort(p, k, j-1, j-i+1);
                        continue;
                    }    
                }
                j--;
            }
            if (flag) break;
            while (p[left]->W <= p[i]->W && i < j)
            {
                if (p[i]->W == p[left]->W)
                {
                    for (k = i+1; k < j; k++)
                    {
                        if (p[k]->W != p[i]->W)
                        {
                            Swap(p[k], p[i]);
                            break;
                        }
                    }
                    if (k == j)
                    {
                        Swap(p[j], p[left]);
                        BubbleSort(p, i, j, j-i+1);
                        flag = 1;
                        break;
                    }
                    else
                    {
                        BubbleSort(p, i+1, k, k-i);
                        continue;
                    }
                }
                i++;
            }
            if (flag) break;
            Swap(p[i], (i == j)?p[left]: p[j]); 
        }
        QuickSort(p, left, i-1);
        QuickSort(p, j+1, right);     
    }    
}

void Swap(person * a, person * b)
{
    person t = *a;
    *a = *b;
    *b = t;
}

void BubbleSort(person ** p, int left, int right, int n)
{
    for (int i = left+1; i <= right; i++)
    {
        for (int j = right; j >=i; j--)
        {
            if (p[j]->W > p[j-1]->W)
            {
                Swap(p[j], p[j-1]);
            }
            else if (p[j]->W == p[j-1]->W)
            {
                if (p[j]->id < p[j-1]->id)
                {
                    Swap(p[j], p[j-1]);
                }
            }
        }
    }
}

