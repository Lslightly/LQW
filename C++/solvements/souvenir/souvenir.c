// luogu P5662 solution
#include <stdio.h>
int max(int,int);
int main(void)
{
    int t,n,m,num[102]={0},a[102][102]={0},gap[102][102]={0},flag=1,k,start=0,end,f[2000]={0};
    scanf("%d%d%d",&t,&n,&m);   //t:天数,n:种数,m：钱
    for (int i=1;i<=t;i++)
    {
        for (int j=1;j<=n;j++)
        scanf("%d",&a[i][j]);
    }

    for (int i=1;i<t;i++)       //计算每一天与下一天的利润差
    {
        for (int j=1;j<=n;j++)
        gap[i][j]=a[i+1][j]-a[i][j];
    }
    flag=0;
    for (int i=1;i<t;i++)           //判断哪天开始有盈利
    {
        for (int j=1;j<=n;j++)
        {
            if (gap[i][j]>0)
            {
                flag=1;
                break;
            }
        }
        if (flag)
        {
            start=i;        //start储存那天开始有盈利
            break;
        }
    }


    if (!flag) printf("%d",m);       //哪天都没有盈利就输出
    else                      
    {
        end=t-1;
        flag=0;
        for (int i=end;i>=1;i--)
        {
            for (int j=1;j<=n;j++)
            {
                if (gap[i][j]>0)
                { 
                 flag=1;
                 break;
                }
            }
            if (flag)
            {
              end=i;                 //哪天之后没有盈利
              break;
            }
        }
        for (int i=start;i<=end;i++)
        {
                for (int j=1;j<=m;j++)
                f[j]=0;
            for (int i1=1;i1<=n;i1++)          //背包问题解法，时间复杂度O（nm）
            {
                for (int j=a[i][i1];j<=m;j++)
                {
                    f[j]=max(f[j],f[j-a[i][i1]]+gap[i][i1]);
                }
            }
            if (f[m]>0) m+=f[m];
        }
    printf("%d",m);
    }
    return 0;
}
int max(int a,int b)
{
    int ans;
    (a>b)?(ans=a):(ans=b);
    return ans;
}