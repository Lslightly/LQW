#include <stdio.h>
int main(void)
{
    int letter[26]={0},max,maxi,i,j,k;
    char input[4][102];
    for (i=0;i<4;i++)
    fgets(input[i],103,stdin);
    for (i=0;i<4;i++)             //统计字母
    {
        for (j=0;input[i][j]!='\0';j++)
        if (input[i][j]<='Z'&&input[i][j]>='A')
        letter[input[i][j]-'A']++;
    }
    max=0;
    for (i=0;i<26;i++)
    {
        if (letter[i]>max)
        {
            max=letter[i];
            maxi=i;
        }
    }

    for (i=max;i>=1;i--)
    {
        for (j=0;j<26;j++)
        {
            if (letter[j]>=i)
            {
                k=j+1;
                while (letter[k]<i&&k<26) k++;
                if (k==26)
                {
                    printf("*\n");
                    break;
                }
                else 
                {
                    printf("* ");
                }
                
            }
            else
            {
                printf("  ");
            }
        }
    }
    for (i=0;i<25;i++)
    {
        printf("%c ",'A'+i);
    }
    printf("Z");
    return 0;
}