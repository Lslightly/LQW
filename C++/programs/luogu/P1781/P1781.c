#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct candidate
{
    int id; // id编号,是第x位-1
    char vote[110]; // 选票数，以字符串形式储存
    int lvote;  // 选票位数
}Cand;

void SeekThePresident(Cand ** p, int n);  // 挑选票数最大的人

int main(void)
{
    int n;  // 人数
    Cand * p[20];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        p[i] = (Cand *)malloc(sizeof(Cand));
        scanf("%s",p[i]->vote);
        p[i]->id = i;
        p[i]->lvote = strlen(p[i]->vote);
    }
    SeekThePresident(p, n);
    return 0;
}

void SeekThePresident(Cand ** p, int n)
{
    Cand * t;
    for (int j = n-1; j > 0; j--)
    {
        if (p[j]->lvote > p[j-1]->lvote)
        {
            t = p[j];
            p[j] = p[j-1];
            p[j-1] = t;
        }
        else if (p[j]->lvote == p[j-1]->lvote)
        {
            if (strcmp(p[j]->vote, p[j-1]->vote) > 0)
            {
                t = p[j];
                p[j] = p[j-1];
                p[j-1] = t;
            }
        }
    }
    printf("%d\n%s", p[0]->id+1, p[0]->vote);
}
