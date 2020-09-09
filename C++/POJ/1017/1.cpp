#include <stdio.h>

const int num_size = 6;

int max(int a, int b);

int min(int a, int b);

//  返回最少数量的packages
//      size_count:     每个size的数量
//      S_size:         每个size的面积
//      S_total:        总面积
int min_packages(int size_count[num_size], int S_size[num_size], int S_total);

int main(void)
{
    // freopen("../1017.in", "r", stdin);
    // freopen("../1017.ans", "w", stdout);
    int count = 0;
    while (1) //  循环输入并重置
    {
        int size_count[num_size] = {0};    //  每个size的数量
        int S_size[num_size] = {0};        //  每个size的面积
        int S_total = num_size * num_size; //  总面积
        bool flag_end = true;

        // count++;
        // scanf("%*d");
        for (int i = 0; i < num_size; i++)
        {
            scanf("%d", &size_count[i]);
            S_size[i] = (i + 1) * (i + 1);
            if (size_count[i] != 0)
            {
                flag_end = false;
            }
        }
        if (flag_end) //  全0
        {
            break;
        }

        printf("%d\n", min_packages(size_count, S_size, S_total));
    }
    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int min_packages(int size_count[num_size], int S_size[num_size], int S_total)
{
    int packages = 0;

    //  6*6
    packages += size_count[5];
    size_count[5] = 0;

    //  5*5
    packages += size_count[4];
    size_count[0] -= min(size_count[0], size_count[4] * 11);
    size_count[4] = 0;

    //  4*4
    packages += size_count[3];
    if (size_count[1] < 5 * size_count[3])
    {
        size_count[0] -= min(size_count[0], 4 * (5*size_count[3] - size_count[1]));
        size_count[1] = 0;
    }
    else
    {
        size_count[1] -= 5 * size_count[3];
    }
    size_count[3] = 0;

    // 3*3
    packages += (size_count[2]+3) / 4;
    int left = size_count[2] % 4;
    switch (left)
    {
    case 1:
        if (size_count[1] <= 5)
        {
            size_count[0] -= min(size_count[0], 7 + (5 - size_count[1]) * 4);
            size_count[1] = 0;
        }
        else
        {
            size_count[0] -= 7;
            size_count[1] -= 5;
        }
        break;
    case 2:
        if (size_count[1] <= 3)
        {
            size_count[0] -= min(size_count[0], 6 + (3 - size_count[1]) * 4);
            size_count[1] = 0;
        }
        else
        {
            size_count[0] -= 6;
            size_count[1] -= 3;
        }
        break;
    case 3:
        if (size_count[1] <= 1)
        {
            size_count[0] -= min(size_count[0], 5 + (1 - size_count[1]) * 4);
            size_count[1] = 0;
        }
        else
        {
            size_count[0] -= 5;
            size_count[1] -= 1;
        }
        break;
    default:
        break;
    }
    size_count[2] = 0;

    //2*2
    packages += (size_count[1]+8) / 9;
    left = size_count[1] % 9;
    if (left)
    {
        if (size_count[0] <= S_total - 4*left)
        {
            size_count[0] = 0;
        }
        else
        {
            size_count[0] -= S_total-4*left;
        }
    }
    size_count[1] = 0;

    packages += (size_count[0] + 35)/36;
    size_count[0] = 0;
    return packages;
}
