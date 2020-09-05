// 分数线划定
#include<stdio.h>
#include<stdlib.h>

typedef struct competitor
{
    int id;
    int score;
}Player;

int BubbleSort(Player ** p, int n, int m);

int main(void)
{
    int n, m, standard;  // n为总人数，m为拟录取志愿者人数，计算后为入围分数线所在名次
    Player * p[5005];  // 5000个人

    scanf("%d%d", &n, &m);
    m = (int)(m * 1.5);  // 面试分数线为排名第m×150%（向下取整）名的选手的分数，而最终进入面试的选手为笔试成绩不低于面试分数线的所有选手
    for (int i = 0; i < n; i++)
    {
        p[i] = (Player *)malloc(sizeof(Player));
        scanf("%d%d", &(p[i]->id), &(p[i]->score));
    }
    int num = BubbleSort(p, n, m);
    printf("%d %d\n", p[m-1]->score, num);
    for (int i = 0; i < num; i++)
    {
        printf("%d %d\n", p[i]->id, p[i]->score);
    }
    for (int i = 0; i < n; i++)
    {
        free(p[i]);
    }
    return 0;
}

int BubbleSort(Player ** p, int n, int m)
{
    Player * t;
    int i;
    for (i = 0; i < n-1; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            if (p[j]->score > p[j-1]->score)
            {
                t = p[j];
                p[j] = p[j-1];
                p[j-1] = t;
            }
            else if (p[j]->score == p[j-1]->score)
            {
                if (p[j]->id < p[j-1]->id)
                {
                    t = p[j];
                    p[j] = p[j-1];
                    p[j-1] = t;
                }
            }
        }
        if (i >= m && p[i]->score < p[m-1]->score) break;   
    }
    if (i != n-1) return i;
    else
    {
        if (p[i]->score == p[m-1]->score)
            return n;
        else return n-1;
    }
}
