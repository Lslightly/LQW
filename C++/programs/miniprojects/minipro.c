#include <stdio.h>
#include <string.h>
#include "list.h"
char * s_gets(char * , int);
int main(void)
{
    char cmd[20];
    List list;
    InitializeList(&list);
    Input(&list);
    Menu();
    do
    {
        if (s_gets(cmd, 20) == NULL || cmd[0] == '\0')
            ;
        else
        {
            if (strcmp(cmd, "列") == 0)
            {
                print(&list);
                PrintIntoFile(&list);
            }
            else if (strcmp(cmd, "查") == 0)
            {
                seek(&list);
                PrintIntoFile(&list);
            }
            else if (strcmp(cmd, "增") == 0)
            {
                add(&list);
                PrintIntoFile(&list);
            }
            else if (strcmp(cmd, "删") == 0)
            {
                delete(&list);
                PrintIntoFile(&list);
            }
            else if (strcmp(cmd, "help") == 0)
            {
                Menu();
            }
            else if (strcmp(cmd, "清屏") == 0)
            {
                
            }
            else if (strcmp(cmd, "更新") == 0)
            {
                UpdateUni(&list);
                PrintIntoFile(&list);
            }
            else if (strcmp(cmd, "退出") == 0)
            {
                Exit(&list);
            }
            else 
            {
                printf("请重新输入命令（不知道请输入“help”）：");
            }
        }
    } while (1);
    
    return 0;
}
char * s_gets(char *st, int n)
{
    char * ret_val;
    char * find;
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
        {
            while (getchar() != '\n')
            {
                continue;
            }
        }
    }
    return ret_val;
}