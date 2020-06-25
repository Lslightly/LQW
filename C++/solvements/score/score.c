#include<stdio.h>
void studentave(int a[][5],double ave[]);    //学生平均分
void subjectave(int a[][5]);    //课程平均分
void seek(int a[][5],int);          //最高分数
void variance(int a[][5],double ave[]);      //方差
int main(void)
{
    int score[10][5];
    double ave[10]={0};
    int i,j,max=0;
    for (i=0;i<10;i++)
    {
        for (j=0;j<5;j++)
        {
        scanf("%d",&score[i][j]);
        if (score[i][j]>max) max=score[i][j];
        }
    }

    studentave(score,ave);
    subjectave(score);
    seek(score,max);
    variance(score,ave);
return 0;
}
void studentave(int a[][5],double b[10])
{
    int ave;
    int j,i;
    for (i=0;i<9;i++)
    {
        ave=0;
        for (j=0;j<5;j++)
        {
            ave+=a[i][j];
        }
        printf("%lf ",ave/5.0);
        b[i]=ave/5.0;
    }
    ave=0;
    for (j=0;j<5;j++)
    {
        ave+=a[i][j];
    }
    printf("%lf\n",ave/5.0);
    b[i]=ave/5.0;
}
void subjectave(int a[][5])
{
    int ave;
    int j,i;
    for (i=0;i<4;i++)
    {
        ave=0;
        for (j=0;j<10;j++)
        {
            ave+=a[j][i];
        }
        printf("%lf ",ave/10.0);
    }
    ave=0;
    for (j=0;j<10;j++)
    {
        ave+=a[j][i];
    }
    printf("%lf\n",ave/10.0);
}
void seek(int a[][5],int max)
{
    int maxi[50],maxj[50];
    int i,j;
    for (i=0;i<10;i++)
    {
        for (j=0;j<5;j++)
        {
            if (max==a[i][j]) printf("%d %d\n",i,j);
        }
    }
}
void variance(int a[][5],double b[10])
{
    double former,latter;
    for (int i=0;i<10;i++)
    {
       former+=b[i]*b[i];
       latter+=b[i];
    }
    former/=10.0;
    latter=(latter/10.0)*(latter/10.0);
    printf("%lf",former-latter);
}