#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, k;
    long int sum = 0;
    long int linesum = 0;
    long int idsum = 0;
    scanf("%d%d", &n, &k);

    int *c = (int *)malloc(sizeof(int) * n); // c表示城市
    scanf("%d", &c[0]);
    linesum += c[0];
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &c[i]);
        linesum += c[i];
        sum += c[i - 1] * c[i];
    }
    sum += c[n - 1] * c[0];

    int *id = (int *)malloc(sizeof(int) * k); // id首都
    int circle;                               // 循环指标
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &id[i]);
        id[i]--;
        idsum += c[id[i]];
        sum += (linesum - c[(id[i] + 1) % n] - c[(id[i] == 0) ? n - 1 : id[i] - 1] - c[id[i]]) * c[id[i]];
    }
    for (int i = 0; i < k; i++)
    {
        long int msum = 0;
        int j = (i+1)%k;
        if (id[j]-id[i] == 1||id[i]-id[j] == n-1)
            sum -= (idsum - c[id[i]] - c[id[j]])*c[id[i]];
        else
        {
            sum-=(idsum - c[id[i]])*c[id[i]];
        }
        idsum -= c[id[i]];
    }
    printf("%ld", sum);
    return 0;
}