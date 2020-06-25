// B. 约瑟夫环问题-死亡报数
// 有n个人围成一圈，顺序排号。从第1个人开始报数（从1到3报数），凡是报到3的人退出圈子，问最后留下的是原来第几号的那位。

// Input Description
// 输入一个正整数n，n<1000000

// Output Description
// 输出最后留下的编号（注意编号是从1开始）

// Samples
// INPUT 1 

// 10
// OUTPUT 1 

// 4
// INPUT 2 

// 666
// OUTPUT 2 

// 401

#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    long long int n;
    int *p;
    scanf("%lld",&n);
    p=(int *)malloc(n*sizeof(int)+1);
    long long int i=0,left=n;
    for (i=1;i<=n;i++)
    {
        *(p+i)=1;
    }
    int key=1;
    int flag=0;
    i=1;
    while (left>1)
    {
        if (*(p+i)&&key==3)
        {
            *(p+i)=0;
            key=1;
            flag=1;
        }
        else if (*(p+i))
        {
            key++;
        }
        i++;
        if (i==n+1) i=1;
        if (flag==1)
        {
            left--;
            flag=0;
        }
    }
    for (i=1;*(p+i)==0;i++);
    printf("%lld",i);
    free(p);
}