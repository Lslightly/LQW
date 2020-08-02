#include <stdio.h>
#include <stdlib.h>

typedef struct stick
{
    int len;
    bool used;
} stick;

int cmp_len(const void *, const void *);

bool search(stick *array, int n, int try_i, int left, int total);

int all_used(stick *array, int n);

void reset(stick *array, int n);

int main(void)
{
    int n;

    while (scanf("%d", &n) && (n != 0))
    {
        stick *input = new stick[n];
        int sum = 0;

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &input[i].len);
            input[i].used = false;
            sum += input[i].len;
        }

        qsort(input, n, sizeof(stick), cmp_len);

        int max_len = input[0].len;

        bool flag = false;

        for (int left = max_len; left <= sum; left++)
        {
            if (sum % left)
                continue;
            int try_i = 0;
            if (search(input, n, try_i, left, left))
            {
                printf("%d\n", left);
                break;
            }
            reset(input, n);
        }
        delete[] input;
    }
    return 0;
}

int cmp_len(const void *p1, const void *p2)
{
    return ((stick *)p2)->len - ((stick *)p1)->len;
}

bool search(stick *sticks_a, int n, int try_i, int left, int total_left)
{
    bool flag = true;
    if (left == 0)
    {
        if (all_used(sticks_a, n) == -1) return true;
        return search(sticks_a, n, all_used(sticks_a, n), total_left, total_left);
    }
    if (left != 0 && try_i >= n)
        return false;
    while (sticks_a[try_i].len > left || sticks_a[try_i].used == true)
    {
        try_i++;
        if (try_i == n)
            return false;
    }
    while (sticks_a[try_i].len <= left)
    {
        while (sticks_a[try_i].used == true)
        {
            try_i++;
            if (try_i == n)
                return false;
        }
        sticks_a[try_i].used = true;
        flag = search(sticks_a, n, try_i + 1, left - sticks_a[try_i].len, total_left);
        if (flag)
        {
            return true;
        }
        sticks_a[try_i].used = false;
        try_i++;
        if (try_i == n || left == total_left)
            return false;
    }
    return false;
}

void reset(stick *sticks_a, int n)
{
    for (int i = 0; i < n; i++)
    {
        sticks_a[i].used = false;
    }
}

int all_used(stick *sticks_a, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (sticks_a[i].used == false)
            return i;
    }
    return -1;
}