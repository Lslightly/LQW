//一件物品
#include <stdio.h>        
int main(void)
{
    int t,n,m,num=0,a[100]={0};
    scanf("%d%d%d",&t,&n,&m);
    for (int i=0;i<t;i++)
    scanf("%d",&a[i]);
    for (int i=0;i<t-1;i++)
    {
        if (a[i]<a[i+1]) 
        {
            num=m/a[i];
            m-=num*a[i];
            m+=num*a[i+1];
        }
    }
    printf("%d",m);
    return 0;
}