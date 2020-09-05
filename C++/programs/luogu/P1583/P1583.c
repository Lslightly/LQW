#include<stdio.h>
#include<stdlib.h>

typedef struct person
{
    int id;  //编号
    int w;  //权值
}person;

int E[11] = {0};

void SameSort(person p[], int n);  //相同w排序

void Quicksort(person p[], int left, int right);  //先快排

void Quicksortid(person p[], int left, int right); //按id快排

void Swap(person * a, person * b);  //交换指针

int main(void)
{
    int n, k;
    person * p;
    scanf("%d%d", &n, &k);
    p = (person *)malloc(sizeof(person) * (n+1));
    for (int i = 1; i < 11; i++)
    {
        scanf("%d", &E[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &(p[i].w));
        p[i].id = i;
    }
    Quicksort(p, 1, n);
    SameSort(p, n);
    for (int i = 1; i <= n; i++)
    {
        p[i].w += E[(i-1) % 10 + 1];
    }
    Quicksort(p, 1, n);
    SameSort(p, n);
    for (int i = 1; i <= k; i++)
    {
        printf("%d ", p[i].id);
    }
}

void Swap(person * a, person * b)
{
    person t = *a;
    *a = *b;
    *b = t;
}

void SameSort(person p[20001], int n)
{
    for (int j = n; j >=2 ; j--)
    {
        if (p[j].w == p[j-1].w)
        {
            int k = j-1;
            while (p[k-1].w == p[k].w)
                k--;
            Quicksortid(p, k, j);
            j = k;
        }
    }
}

void Quicksort(person p[20001], int left, int right)
{
    if (right <= left)
        return ;
    else
    {
        int i = left, j = right, pivot = rand()%(right - left + 1) + left;
        Swap(&p[pivot], &p[left]);
        while (i < j)
        {
            while (p[j].w <= p[left].w && i<j)
                j--;
            while (p[i].w >= p[left].w && i<j)
                i++;
            Swap(&p[i], (i == j)?&p[left]:&p[j]);
        }
        Quicksort(p, left, i-1);
        Quicksort(p, i+1, right);
    }
}

void Quicksortid(person p[20001], int left, int right)
{
    if (right <= left)
        return ;
    else
    {
        int i = left, j = right, pivot = rand() % (right - left +1 ) + left;
        Swap(&p[pivot], &p[left]);
        while (i<j)
        {
            while (p[j].id >= p[left].id && i<j)
                j--;
            while (p[i].id <= p[left].id && i<j)
                i++;
            Swap(&p[i], (i==j)?&p[left]:&p[j]);
        }
        Quicksortid(p, left, i-1);
        Quicksortid(p, i+1, right);
    }
}
