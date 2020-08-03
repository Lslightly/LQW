#include <stdio.h>

const int num_value = 6;

//  计算总价值
int total_value(int num_stone[num_value], int n);

int dfs(int num_stone[num_value], int cur_i, int now_value, int goal_value);

int main(void)
{
    int collections = 1;
    while (1)
    {
        int num_stone[num_value] = {0}, goal_value = 0;
        for (int i = 0; i < num_value; i++)
        {
            scanf("%d", &num_stone[i]);
        }
        if ((goal_value = total_value(num_stone, num_value-1)) % 2)
        {
            printf("Collection #%d:\nCan't be divided.\n\n", collections);
            collections++;
            continue;
        }
        if (goal_value == 0) return 0;
        goal_value /= 2;
        if (dfs(num_stone, num_value-1, 0, goal_value) == 0)
        {
            printf("Collection #%d:\nCan be divided.\n\n", collections);
            collections++;
            continue;
        }
        else
        {
            printf("Collection #%d:\nCan't be divided.\n\n", collections);
            collections++;
            continue;
        }
    }
    return 0;
}

int total_value(int num_stone[num_value], int n)
{
    int sum = 0;
    for (int i = 0; i <= n; i++)
    {
        sum += (i+1)*num_stone[i];
    }
    return sum;
}

int dfs(int num_stone[num_value], int cur_i, int now_value, int goal_value)
{
    int temp = 0;
    if (now_value == goal_value)
        return 0;
    if (now_value + total_value(num_stone, cur_i) < goal_value) return -1;
    for (int i = ((goal_value - now_value)/(cur_i+1) < num_stone[cur_i])?(goal_value - now_value)/(cur_i+1):num_stone[cur_i]; i >= 0; i--)
    {
        if ((temp = dfs(num_stone, cur_i-1, now_value+(cur_i+1)*i, goal_value)) == 0)
            return 0;
        else if (temp == -1)
            break;
    }
    return 1;
}