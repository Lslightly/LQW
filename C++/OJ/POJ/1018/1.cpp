#include <stdio.h>
#include <stdlib.h>

typedef struct manufacture
{
    int B; //  bandtidth
    int P; //  price
} manufacture;

bool Bandwidth[10000] = {0}; //  是否使用

int cmp_B(const void *p1, const void *p2);

//  return the min price of min_price manufactures
int meet_min_price(manufacture *manu, int condition_B);

int main(void)
{
    int t = 0;
    scanf("%d", &t);

    for (int z = 0; z < t; z++)
    {
        int n = 0;
        scanf("%d", &n);

        manufacture *device[100] = {0};
        for (int i = 0; i < n; i++)
        {
            int mi = 0;
            scanf("%d", &mi);

            device[i] = new manufacture[mi + 1];
            device[i][0].B = 0;
            device[i][0].P = mi;
            for (int j = 0; j < mi; j++)
            {
                scanf("%d%d", &device[i][j + 1].B, &device[i][j + 1].P);
                Bandwidth[device[i][j + 1].B] = true;
            }
            qsort(device[i], mi + 1, sizeof(manufacture), cmp_B);
        }

        int min_B = device[0][device[0][0].P].B;

        for (int i = 0; i < n; i++)
        {
            if (device[i][device[i][0].P].B < min_B)
            {
                min_B = device[i][device[i][0].P].B;
            }
        }

        double max_BP = 0;
        while (min_B != 0)
        {
            if (Bandwidth[min_B] == false)
            {
                min_B--;
                continue;
            }

            int total_price = 0;
            for (int i = 0; i < n; i++)
            {
                total_price += meet_min_price(device[i], min_B);
            }
            if (min_B * 1.0 /total_price > max_BP)
            {
                max_BP = min_B * 1.0 /total_price;
            }

            min_B--;
        }
        printf("%.3lf\n", max_BP);
        
    }
}

int cmp_B(const void *p1, const void *p2)
{
    return ((manufacture *)p1)->B - ((manufacture *)p2)->B;
}

int meet_min_price(manufacture *manu, int condition_B)
{
    int min_p = manu[manu[0].P].P;
    for (int i = 0; i < manu[0].P; i++)
    {
        if (manu[i].B >= condition_B && manu[i].P <= min_p)
        {
            min_p = manu[i].P;
        }
    }
    return min_p;
}
