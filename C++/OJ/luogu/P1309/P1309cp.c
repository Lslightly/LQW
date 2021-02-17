#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct player
{
    int id;
    long int s;
    long int w;
}Player;

void Quicksorts(Player * p, int left, int right); // 按照score排名

void Quicksortid(Player * p, int left, int right); // 按照id排名

void swap(Player * a, Player * b);

void Same_s_seek(Player * p, int left, int right);

void WinorLose(Player * p, int n);

int main(void)
{
    int n, r, q;
    scanf("%d%d%d", &n, &r, &q);
    Player * p = (Player *)malloc(sizeof(Player) * 2 *n);
    for (int i = 0; i < 2*n; i++)
    {
        scanf("%ld", &p[i].s);
        p[i].id = i+1;
    }
    for (int i = 0; i < 2*n; i++)
    {
        scanf("%ld", &p[i].w);
    }
    for (int i = 0; i < r; i++)
    {
        Quicksorts(p, 0, 2*n-1);
        Same_s_seek(p, 0, 2*n-1);
        WinorLose(p, 2*n);
    }
    Quicksorts(p, 0, 2*n-1);
    Same_s_seek(p, 0, 2*n-1);
    printf("%d", p[q-1].id);
}

void Quicksorts(Player * p, int left, int right)
{
    if (right <= left) return ;
    if (right - left +1 <=10)
    {
        for (int i = left; i<right; i++)
        {
            int flag = 1;
            for (int j = right; j>=i+1; j--)
            {
                if (p[j].s > p[j-1].s)
                {
                    swap(&p[j], &p[j-1]);
                    flag = 0;
                }
            }
            if (flag) break;
        }
    }
    int i = left, j =  right, pivot = rand()%(right-left+1) + left, k, flag = 0;
    swap(&p[left], &p[pivot]);
    while (i<j)
    {
        while (p[left].s >= p[j].s && i<j)
            j--;
        while (p[left].s <= p[i].s && i<j)
            i++;
        swap(&p[i], (i==j)?&p[left]:&p[j]);
    }
    Quicksorts(p, left, i-1);
    Quicksorts(p, j+1, right);
}

void Quicksortid(Player * p, int left, int right)
{
    if (right <= left) return ;
    if (right - left +1 <=10)
    {
        for (int i = left; i<right; i++)
        {
            int flag = 1;
            for (int j = right; j>=i+1; j--)
            {
                if (p[j].id < p[j-1].id)
                {
                    swap(&p[j], &p[j-1]);
                    flag = 0;
                }
            }
            if (flag) break;
        }
    }

    int i = left, j =  right, pivot = rand()%(right-left+1) + left;
    swap(&p[left], &p[pivot]);
    while (i<j)
    {
        while (p[left].id <= p[j].id && i<j)
            j--;
        while (p[left].id >= p[i].id && i<j)
            i++;
        swap(&p[i], (i==j)?&p[left]:&p[j]);
    }
    Quicksortid(p, left, i-1);
    Quicksortid(p, i+1, right);

}

void swap(Player * a, Player * b)
{
    Player c = *a;
    *a = *b;
    *b = c;
}

void Same_s_seek(Player * p, int left, int right)
{
    for (int i = right; i>=left+1; i--)
    {
        int k = i;
        while (p[i].s == p[i-1].s)
        {
            i--;
            if (i == left) break;
        }
        if (i<k) Quicksortid(p, i, k);
    }
}

void WinorLose(Player * p, int n)
{
    for (int i = 0; i < n; i+=2)
    {
        if (p[i].w > p[i+1].w)
            p[i].s++;
        else
            p[i+1].s++;
    }
}
