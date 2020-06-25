#include<stdio.h>
long int x[21][21][21]={1};
long int w(long int,long int,long int);
int main(void)
{
    long int a[10000],b[10000],c[10000];
    int i=-1;
    do
    {
        i++;
        scanf("%ld%ld%ld",&a[i],&b[i],&c[i]);
    } while ((a[i]!=-1||b[i]!=-1||c[i]!=-1));
    
    int j=0;
    while (j<i)
    {
        printf("w(%ld, %ld, %ld) = %ld\n",a[j],b[j],c[j],w(a[j],b[j],c[j]));
        j++;
    }
    return 0;
}
long int w(long int a,long int b,long int c)
{
    if ((a<=0)||(b<=0)||(c<=0)) return 1;
    else if ((a>20)||(b>20)||(c>20))
    {
        if (!x[20][20][20])
        x[20][20][20]=w(20,20,20);
        return x[20][20][20];
    }
    else if (x[a][b][c]) return x[a][b][c];
    else
    {
        if ((a<b)&&(b<c)) 
        {
            x[a][b][c]=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
             return x[a][b][c];
        }
        else 
        {
            x[a][b][c]=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
            return x[a][b][c];
        }
    }
    
}