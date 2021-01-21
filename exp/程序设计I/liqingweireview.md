# 复习
期末考试时间：1月7日下午2：30-4：30

#### 变量多次使用重新赋值
````c
for (int i=0;i<100;i++)
{
    sum=0;   //就是这里
    for (int j=0;j<i;j++)
    sum+=j;
}
````
#### 循环输入去\n
````c
    while ((ch=getchar())!=EOF)
    {
        ...
    }
````
#### +与=优先级(等号优先级超低)
````c
#include <stdio.h>
int main(void)
{
    int x=0,b=2;
    x=3+b=x+3;  //赋给报错，先运算+,在运算=，优先级不同
    x=(b=x+3,b+3);
}
````
>**常用优先级比较顺序 () > {++ , -- , ! } > {\* , / , %} > {+ , -} >{== , !=} >  && > ||  >{ ?: } > {各种赋值符} > { , }**

#### 字符常量
\x5c    (x  16进制)字符16\*5+1\*12=92

\101  (八进制)字符64\*1+8\*0+1\*1=65

字符串"A\x11T\101C"的长度是 5。

"a" 不是字符常量，是字符串常量
#### 初始化
int t1=t2=10;   错误

#### 一个个输入字符常量
````c
#include <stdio.h>
int main(void)
{
    char a,b,c;
    scanf("%c%c%c",&a,&b,&c);
    printf("%c%c%c",a,b,c);
    return 0;
}
// 结果
// 1 2（中间有空格）
// 1 2
````
#### 看看这注释 You see see, you see see
````
#include <stdio.h>
     void main()
     {    int a=0,b=0;
          a=10; /*给a赋值
　        b=20; 给b赋值 */
          printf("a+b=%d\n",a+b);
     }
````
求输出结果 10
#### 找错
````c
#include <stdio.h>
     void main();
     {     /*programming*/
          printf("programming!\n");
     }  
#include <stdio.h>
     void main()
     {     /*/ programming /*/
          printf("programming!\n");
     }
#include <stdio.h>   
     void main()
     {     /*/*programming*/*/
          printf("programming!\n");
     }  
include <stdio.h>
    void main()
    {     /*programming*/
         printf("programming!\n");
    }
````
#### 整型的表示
````c
#include <stdio.h>   
     void main( )
     {
           int x=102,y=012; 
           printf("%2d,%2d\n",x,y);
     }
````
结果 102,10  **！！！**
这个0是八进制
````c
#include <stdio.h>   
     void main( )
     {
           int x=102,y=0x41; 
           printf("%2d,%2d\n",x,y);
     }
````
结果 102,65
0x 十六进制
#### printf()
转换
- %u无符号十进制
- %o无符号八进制
- %x无符号十六进制
- \-左对齐
- \+显示正负号
- .数字 
    - %.2f%.2lf%.2e 小数点右边位数2
    - %.2s 待打印字符最大数量2
    - %.2d 待打印数字最小位数
    ````
    int y=1;
    printf("%.2d",y);
    //输出结果01
    ````
-  \* 表示对应输入量不赋给一个变量说明
-  \012 输出8*1+2对应字符
-  \101 输出64\*1+8\*0+1\*1对应字符
-  \x41 输出16*4+1对应字符
#### scanf()
转换说明
- %o,%x分别解释为八、十六进制
- 数字 最大字段宽度
#### 缩进
````
 if (a>2) 
       if (b>2) 
           x = 2 ;
 else x = 3;
````
````c
 if (a>2) 
       if (b>2) 
           x = 2 ;
       else x = 3;  //就是这么变态
````
>else就近原则

#### if else与 ? : 判断条件
- 非零即为真，并不只有1

#### switch()
````c
#include <stdio.h>
int main(void)
{
      switch (1)
      {
      case 1:printf("1");
      case 2:printf("2");
      case 3:printf("3");
            break;
      
      default:
      printf("1");
            break;
      }
      return 0;
}
// 123
````
>一路向下，只要没有阻挡
#### . ->
    student.name
    p->name

#### 文件有关
````c
struct student
{
    char name[20];
    int id;
};
struct stu[20];
FILE *fp;
fread(&stu[i],sizeof(struct student),1,fp);  //1表示读一个student字节数的数据
fwrite(stu[i],sizeof(struct student),1,fp);  //1表示输出1个student结构所占字节的数据
rewind(fp); //文件标记返回文件头
fseek(fp,50L,0);    //50L用long类型 0：开始位置 1:文件当前位置 2： 文件末尾位置
i=ftell(fp);    //存放文件当前位置
````
#### 输出%
````
printf("%%");
````   
#### 错误输出
````c
printf("%d\n",m/2.0+1);
````
>结果0