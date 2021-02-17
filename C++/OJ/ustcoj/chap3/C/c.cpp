// File:    c.cpp
// Author:  Lslightly
// Date:    2020/03/06 20:22:10
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct line
{
    char s_given_string[21];
    char s_prefix[21];
    int i_string_len;
}line_string[20];

// compare the given strings
// return 1 if p1.s_given_string < p2.s_given_string, else return -1;(there won't be conditions that two given strings are equal)
int string_cmp(const void * p1, const void * p2);

// it is a recursive function
// each time it will narrow the range until left == right, which means that no others are equal to it, thus the substring before the subscript i is its prefix, it will be stored.
void Mysort(int left, int right, int i);

int main(void)
{
    int i_num_lines = 0, i = 0;

    while (scanf("%s", line_string[i].s_given_string) != EOF)
    {
        line_string[i].i_string_len = strlen(line_string[i].s_given_string);
        i_num_lines++;
        i++;
    }
    
    qsort(line_string, i_num_lines, sizeof(struct line), string_cmp);
    Mysort(0, i_num_lines-1, 0);

    for (int i = 0; i < i_num_lines; i++)
    {
        printf("%s %s\n", line_string[i].s_given_string, line_string[i].s_prefix);
    }
    return 0;
}

void Mysort(int left, int right, int i)
{
    for (int j = left; j < right; j++)
    {
        if (i >= line_string[j].i_string_len)
        {
            strncpy(line_string[j].s_prefix, line_string[j].s_given_string, i);
            left = j+1;
        }
        else
        {
             if (line_string[j].s_given_string[i] != line_string[j+1].s_given_string[i])
             {
                 if (j > left)
                 {
                    Mysort(left, j, i+1);
                    left = j+1;
                 }
                 else
                 {
                    strncpy(line_string[j].s_prefix, line_string[j].s_given_string, i);
                 }
             }
        }
    }
    if (right <= left)
    {
        strncpy(line_string[right].s_prefix, line_string[right].s_given_string, i);
    }
    else
    {
        Mysort(left, right, i+1);
    }
    return ;
}

int string_cmp(const void * p1, const void * p2)
{
    return strcmp(((struct line *)p1)->s_given_string, ((struct line *)p2)->s_given_string);
}
