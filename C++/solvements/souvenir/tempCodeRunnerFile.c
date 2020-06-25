#include <stdio.h>
int main(void)
{
    int t,n,m,num[100]={0},a[100][100]={0},gap[100][100]={0},max,maxj[100]={0},flag=1,k,start=0,end;
    scanf("%d%d%d",&t,&n,&m);
    for (int i=0;i<t;i++)
    {
        for (int j=0;j<n;j++)
        scanf("%d",&a[i][j]);
    }

    for (int i=0;i<t-1;i++)       //计算每一天与下一天的利润差
    {
        for (int j=0;j<n;j++)
        gap[i][j]=a[i+1][j]-a[i][j];
    }
    flag=0;
    for (int i=0;i<t-1;i++)           //判断哪天开始有盈利
    {
        for (int j=0;j<n;j++)
        {
            if (gap[i][j]>0)
            {
                flag=1;
                break;
            }
        }
        if (flag)
        {
            start=i;
            break;
        }
    }


    if (!flag) printf("%d",m);       //哪天都没有盈利就输出
    else                       //start储存那天开始有盈利
    {
        end=t-2;
        flag=0;
        for (int i=end;i>=0;i--)
        {
            for (int j=0;j<n;j++)
            {
                if (gap[i][j]>0)
                { 
                 flag=1;
                 break;
                }
            }
            if (flag)
            {
              end=i;
              break;
            }
        }
        for (int i=start;i<=end;i++)
        {
           max=-10000;
           for (int j=0;j<n;j++)
           {
               gap[i][j]=a[i+1][j]-a[i][j];
               if (max<gap[i][j]*(m/a[i][j])) max=gap[i][j]*(m/a[i][j]),maxj[0]=j;
            }
            if (max>0)
            {
                gap[i][maxj[0]]=-10000;
                k=-1;
                do
                {
                    flag=0;
                    if(max>0)
                    {
                    k++;
                    num[k]=m/a[i][maxj[k]];
                    m-=num[k]*a[i][maxj[k]];
                    max=-10000;
                    
                     for (int j=0;j<n;j++)
                    {
                         if (a[i][j]<=m&&max<gap[i][j]*(m/a[i][j])) 
                         {
                           max=gap[i][j]*(m/a[i][j]);
                            maxj[k+1]=j;
                            flag=1;
                         }
                     }
                    gap[i][maxj[k+1]]=-10000;
                    }
                } while (flag);
        for (int l=0;l<k+1;l++)
        m+=num[l]*a[i+1][maxj[l]];
        }
    }
    printf("%d",m);
    }
    return 0;
}