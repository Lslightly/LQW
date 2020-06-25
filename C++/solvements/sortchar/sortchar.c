// C. 又是排序，排序真是练习题常客
/*分别对输入的10个等长字符串的内部按ascii码升序排序，并输出排序后的字符串。

Input Description
1. 字符串长度，int

2. 10个字符串，char


Output Description
排序后的十个字符串，字符串之间以'\n'分隔，最后一个字符串末尾不要加'\n'。

Sample
INPUT 

5
asdfg
uytre
lkjhg
zxcvb
mnbvc
trewq
oiuyt
lkmnj
plkmj
pokmj
OUTPUT 

adfgs
ertuy
ghjkl
bcvxz
bcmnv
eqrtw
iotuy
jklmn
jklmp
jkmop
*/

// 用malloc分配内存给指针数组
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
void sort(char *p, int);
int main(void)
{
    char *p[10];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < N; i++)
    {
        p[i] = (char *)malloc((n + 3) * sizeof(char)); //分配内存给指针数组
        scanf("%s", p[i]);
        sort(p[i], n);
    }
    for (int i = 0; i < N - 1; i++)
    {
        printf("%s\n", p[i]);
    }
    printf("%s\n", p[N - 1]);
    for (int i = 0; i < N; i++)
    {
        free(p[i]);
    }
}
void sort(char *p, int n)
{
    char ch;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
            if (p[j] > p[j + 1])
            {
                ch = p[j];
                p[j] = p[j + 1];
                p[j + 1] = ch;
            }
    }
}
