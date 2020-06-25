#include <stdio.h>
int max(int,int);
int main(void)
{
    int w[10000]={0},v[10000]={0},dp[30000]={0},n,m;
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++)
    {
        scanf("%d%d",&w[i],&v[i]);
    }
    for (int i=0;i<n;i++)
    {
        for (int j=m;w[i]<=j;j--)
        {
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    printf("%d",dp[m]);
    return 0;
}
int max(int a,int b)
{
    return ((a>b)?a:b);
}