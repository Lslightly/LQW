#include <stdio.h>
#include <stdlib.h>

typedef struct stick
{
    int len;
    bool used;
} stick;

const int MAX_SIZE = 64;

int cmp_len(const void *, const void *);

bool search(stick *array, int n, int try_i, int left, int total);

int all_used(stick *array, int n);

void reset(stick *array, int n);

int main(void)
{
    int n;

    while (scanf("%d", &n) && (n != 0))
    {
        stick input[MAX_SIZE];
        // stick * input = new stick [n];
        int sum = 0;

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &input[i].len);
            input[i].used = false;
            sum += input[i].len;
        }

        qsort(input, n, sizeof(stick), cmp_len);

        // for (int i = 0; i < n; i++)
        // {
        //     printf("%d %d\n", i, input[i].len);
        // }

        int max_len = input[0].len;

        bool flag = false;

        for (int left = max_len; left <= sum; left++)
        {
            if (sum % left)
                continue;
            if (search(input, n, 0, left, left))
            {
                printf("%d\n", left);
                break;
            }
            reset(input, n);
        }
        // delete [] input;
    }
    return 0;
}

int cmp_len(const void *p1, const void *p2)
{
    return ((stick *)p2)->len - ((stick *)p1)->len;
}


//  搜索查找
bool search(stick *sticks_a, int n, int try_i, int left, int total_left)
{
    bool flag = false;
    if (left == 0)  //  没有剩余
    {
        if (all_used(sticks_a, n) == -1)    //  全部stick都用了，并且没有剩余，一路返回true
            return true;
        return search(sticks_a, n, 0, total_left, total_left);  //  有stick没用，需要继续查找，可以的话返回true
    }
    if (left != 0 && try_i >= n)    //  不行的情况：没剩还越界
        return false;
    while (sticks_a[try_i].len > left || sticks_a[try_i].used == true)  //  循环找到合适的stick进行尝试，如果越界说明失败
    {
        try_i++;
        if (try_i == n)
        {
            return false;
        }
    }

    sticks_a[try_i].used = true;    //  尝试使用这个stick进行拼凑
    flag = search(sticks_a, n, try_i + 1, left - sticks_a[try_i].len, total_left);  //  看看剩下的stick能不能拼凑成功
    if (flag)   //  成功
    {
        return true;    //  一路返回true
    }
    sticks_a[try_i].used = false;   //  失败，重新设置没有使用这个stick
    if (0 == try_i || left == total_left) return false; //  第一次尝试也没有功

    do
    {
        try_i++;    //  下一个
        if (try_i == n)   //  越界或者   连用第一个stick拼凑都不行，就算后面能拼出来，第一个stick还是拼不出来
            return false;
    }while(sticks_a[try_i].len == sticks_a[try_i-1].len);   //  相同的就别再试了
    return search(sticks_a, n, try_i, left, total_left);    //  换后面的拼，看看能不能拼出来（原来那根也许还有其他用途）
}

//  重置
void reset(stick *sticks_a, int n)
{
    for (int i = 0; i < n; i++)
    {
        sticks_a[i].used = false;
    }
}

//  判断是否全部使用
//  -1全部，否则返回标
int all_used(stick *sticks_a, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (sticks_a[i].used == false)
            return i;
    }
    return -1;
}