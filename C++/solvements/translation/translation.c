#include <stdio.h>
int main(void)
{
    int n,m,a[1005]={0},i=0,j,flag,tag=0,key,count=0; //tag:memory 下标
    scanf("%d%d",&m,&n); //m:memory,n:number of words
    for (i=0;i<m;i++)
    a[i]=-1;         //a[i]可能为0
    i=0;
    while (i<n)
    {
        scanf("%d",&key);
        flag=0;
        for (j=0;j<m;j++)                  //判断内存中是否有该单词
        {
            if (a[j]==key)
            {
                flag=1;
                break;
            }
        }
        if (!flag)
        {
            a[tag]=key;
            count++;
            tag++;
            if (m==tag) tag=0;   //内存占满，将tag置零来卡掉原先的数据，存入新word
        }
        i++;
    }
    printf("%d",count);
    return 0;
}