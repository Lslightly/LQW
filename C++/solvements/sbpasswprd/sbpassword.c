#include <stdio.h>
int main(void)
{
    int i,n;
    char a[51]={' '};
    scanf("%d%s",&n,a);
    for (i=0;(a[i]<='z'&&a[i]>='a');i++)
    {
        if (a[i]+n>'z') a[i]='a'-('z'-a[i])-1;
        printf("%c",a[i]+n);
    }
    return 0;
}