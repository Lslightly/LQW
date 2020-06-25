#include <stdio.h>
int max(int,int);
int main(void)
{
    int n,v,c[200]={0},w[200]={0},f[105][105]={0},i,j,k;
    scanf("%d%d",&n,&v);
    for (i=1;i<=n;i++)
    {
        scanf("%d%d",&c[i],&w[i]);
    }
    for (i=1;i<=n;i++)
    {
        for ( j = 1; j <= v; j++)
        {
            for (k=0;k<=j/c[i];k++)
            {
                if (j>=k*c[i])
                {
                    f[i][j]=max(f[i][j],f[i-1][j-k*c[i]]+k*w[i]);
                }
                
            }
        }
    }
    printf("%d",f[n][v]);
    return 0;
}
int max(int a,int b)
{
    int ans;
    (a>b)?(ans=a):(ans=b);
    return ans;
}