#include <stdio.h>
int main(void)
{
    char ch,a[30];
    fgets(a,20,stdin);
    ch=getchar();
    printf("%c",ch);
    return 0;
}