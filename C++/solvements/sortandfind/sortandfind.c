#include <stdio.h>
#include <string.h>
void sort(int a[],char b[][10]);
int main(void)
{
    char name[10][10]={" "};
    int id[10]={0},n;
    for (int i=0;i<10;i++)
    scanf("%s%d",name[i],&id[i]);
    scanf("%d",&n);
    sort(id,name);
    printf("%s",name[n-1]);
    return 0;
}
void sort(int a[10],char b[][10])
{
    int i,j,t;
    char ch[10];
    for (i=0;i<9;i++)
    {
        for (j=9;j>=i+1;j--)
        {
            if (a[j]<a[j-1])
            {
                t=a[j];
                a[j]=a[j-1];
                a[j-1]=t;
                strcpy(ch,b[j]);
                strcpy(b[j],b[j-1]);
                strcpy(b[j-1],ch);
            }
        }
    }
    for (i=0;i<10;i++)
    printf("%s\n",b[i]);
}
