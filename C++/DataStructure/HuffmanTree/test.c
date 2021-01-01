#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    int a = 0;
    if (0 == mkdir("a/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        printf("success\n");
    return 0;
}