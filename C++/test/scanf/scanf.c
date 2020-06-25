#include <stdio.h>
int main(void)
{
    char name[100][20];
    int i=0;
    while (scanf("%s",name[i]))
    {
        i++;
        if ((getchar())=='\n') break;
    }
    for (int j=0;j<i;j++)
    {
        printf("%s ",name[j]);
    }
    
}