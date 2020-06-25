#include<stdio.h>
int j=12;        //j具有文件作用域(file scope)，外部链接，称为全局变量(global variable)
int f(int);    //函数原型作用域范围开始
static int k=20;    //文件作用域，内部链接，属文件私有
int main(void)
{
    int i=20;             //这个i在main()函数块作用域(block scope)上可见，为自动变量
    for (int i=0;i<5;i++)     //块作用域中定义的i，i的可见范围为for这个语句块，int i=0为i的作用于开始，此声明可以放在块的任意位置
    {
        printf("for:%d\n",i);      //只有内层块才可以访问i
    }                 //i的作用域结束
    if (1)
    {
        int i=11;
        printf("if:%d\n",i);
    }
    while (1)
    {
        int i=2;
        printf("while:%d\n",i);
        break;
    }
    do
    {
        int i=12;
        printf("do while:%d\n",i);
    } while (0);
    printf("%d\n",i);  
    for (int i=0;i<3;i++)
    {
        f(1);
    }
    return 0;
}
// 块的概念适用于for, while, do while, if语句
int f(int a)   
{
    int n=1;
    static int flag=1;             //块作用域的静态变量，不随函数的结束而消失，在程序被载入内存的时候已经执行完毕
    printf("block auto virable:%d block static variaible:%d\n",n++,flag++);
    return a;
}            //函数原型作用域范围结束