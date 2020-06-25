#include <stdio.h>
int main(void)
{
    int a[5]={100,200,300,400,500};
    int *p1,*p2,*p3;
    const int * p4=a;
    p1=a;
    p2=&a[3];
    p3=p1+4;
    printf("p1+4:%d\n",*p3);           //指针加整数
    printf("p2-1:%d\n",*(p2-1));         // 指针减整数
    printf("p3-p1:%d\n",p3-p1);               //指针减指针
    printf("const int *p4:%d,p4++:%d",*p4,*(p4++));
    return 0;
}