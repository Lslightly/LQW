#include <stdio.h>
#include <cstring>

const int num_coin = 12;

bool judge(int * weigh_coin, char left[7], char right[7], char info_weigh[7]);

int main(void)
{
    int n = 0;
    scanf("%d", &n);

    for (int cases = 0; cases < n; cases++)
    {
        char left[3][7] = {""}, right[3][7] = {""}, info_weigh[3][5] = {""};
        int weigh_coin[num_coin] = {0};
        bool real_coin[num_coin] = {true};
        for (int i = 0; i < num_coin; i++)
        {
            weigh_coin[i] = 1;
            real_coin[i] = false;
        }
        
        for (int i = 0; i < 3; i++)
        {
            scanf("%s%s%s", left[i], right[i], info_weigh[i]);
            if (strcmp("even", info_weigh[i]) == 0)
            {
                for (int j = 0; j < strlen(left[i]); j++)
                {
                    real_coin[left[i][j]-'A'] = true;
                    real_coin[right[i][j]-'A'] = true;
                }
            }
        }
        
        for (int i = 0; i < num_coin; i++)
        {
            int j = 0;
            if (real_coin[i]) continue;
            weigh_coin[i] = 0;
            for (j = 0; j < 3; j++)
            {
                if (judge(weigh_coin, left[j], right[j], info_weigh[j]) == false)
                    break;
            }
            
            if (j == 3)
            {
                printf("%c is the counterfeit coin and it is light.\n", 'A'+i);
                break;
            }
            weigh_coin[i] = 2;
            for (j = 0; j < 3; j++)
            {
                if (judge(weigh_coin, left[j], right[j], info_weigh[j]) == false)
                    break;
            }
            
            if (j==3)
            {
                printf("%c is the counterfeit coin and it is heavy.\n", 'A'+i);
                break;
            }
            weigh_coin[i] = 1;
        }
        
    }
    
    return 0;
}

bool judge(int * weigh_coin, char left[7], char right[7], char info_weigh[7])
{
    int sum_left = 0, sum_right = 0;
    for (int i = 0; i < strlen(left); i++)
    {
        sum_left+=weigh_coin[left[i]-'A'];
        sum_right += weigh_coin[right[i]-'A'];
    }
    
    if (strcmp("even", info_weigh) == 0)
    {
        return sum_left == sum_right;
    }
    else if (strcmp("up", info_weigh) == 0)
    {
        return sum_left > sum_right;
    }
    else if (strcmp("down", info_weigh) == 0)
    {
        return sum_left < sum_right;
    }
    return false;
}