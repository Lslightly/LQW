#include <stdio.h>
int main(void)
{
    char input[62510]={'\0'},a; //输入变一维数组感觉比较好处理
    int i=0,j_11=0,j_21=0,num,gap=0,rule_11[14000]={0},rule_21[10000]={0};
    while ((a=getchar())!='E')      //输入
    {
        if (a!='\n')
        {
           input[i]=a;
           i++;
        }
    }
    num=i;
    
    i=0;

    while (i<num)            //分别计算11分制与21分制的输赢分 存至rule...[],输出每一行以rule[2*i]赢,rule[2*i+1]输形式存储，满足成局条件，i++；
    {
        (input[i]-'W'==0)?(rule_11[j_11]++,rule_21[j_21]++):(rule_11[j_11+1]++,rule_21[j_21+1]++);    //输赢
        ((rule_11[j_11]>=11||rule_11[j_11+1]>=11)&&(rule_11[j_11]-rule_11[j_11+1]>=2||rule_11[j_11+1]-rule_11[j_11]>=2))?j_11+=2:(1);  //11分制成局条件判断与换行存储所需的下标变换
        ((rule_21[j_21]>=21||rule_21[j_21+1]>=21)&&(rule_21[j_21]-rule_21[j_21+1]>=2||rule_21[j_21+1]-rule_21[j_21]>=2))?j_21+=2:(1);  //21分制....
        i++;
    }
    for (i=0;i<=j_11;i+=2)
    {
        printf("%d:%d\n",rule_11[i],rule_11[i+1]);
    }
    printf("\n");
    for (i=0;i<=j_21;i+=2)
    {
        printf("%d:%d\n",rule_21[i],rule_21[i+1]);
    }
    return 0;
}