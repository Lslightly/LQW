#include<string.h>
#include <stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX_NUM 110
char str_text[MAX_NUM], substr[MAX_NUM],str_text_origin[MAX_NUM];
/*
Linked list use: store matching substring information
Type: Singly Linked List
Member meaning:1.match_position is used to store the matched position 
(-1 means no substring information is stored)
2.char match_substr is used to store the matching substring
*/
struct match_str
{
    int match_position;
    char match_substr[MAX_NUM];
}ans[10*MAX_NUM];
int main()
{
    int i,flag,match_num;
    int STRUPR(char* str_text, char* substr);
    int match1(char* str_text, char* substr, char* str_text_origin);
    int match2(char* str_text, char* substr, char* str_text_origin);
    int cmp(const void* a, const void* b);
    for (i = 0; i < 10*MAX_NUM; i++)
    {
        ans[i].match_position = -1;//Initialize the matching position to -1
    }
    scanf("%s%s", str_text, substr);
    strcpy(str_text_origin, str_text);
    flag=STRUPR(str_text,substr);
    if (flag == 0)
    {
       match_num = match1( str_text, substr,  str_text_origin);
    }
    else
    {
       match_num = match2( str_text,substr, str_text_origin);
    }
    qsort(ans, match_num, sizeof(ans[0]), cmp);
    printf("%d %s\n", ans[0].match_position, ans[0].match_substr);
    for (i = 1; ans[i].match_position != -1; i++)
    {
        if((strcmp(ans[i].match_substr,ans[i-1].match_substr)!=0)||(ans[i].match_position!=ans[i-1].match_position))
        {
            printf("%d %s\n", ans[i].match_position, ans[i].match_substr);
        }
    }

}
/*
 function:Convert all English letters in the input string to uppercase
 Parameters: pointers to the two input strings
 Return value: Whether there is a '#' tag(1 means yes, 0 means no)
*/
int STRUPR(char* str_text, char* substr)
{
   int i = 0,flag=0;//flag is used to mark whether there is a '#' in the substring
    for (i = 0; str_text[i] != '\0'; i++)
    {
        if (str_text[i] >= 'a')
        {
            str_text[i] -= 32;
        }
    }
    for (i = 0; substr[i] != '\0'; i++)
    {
        if (substr[i] >= 'a')
        {
            substr[i] -= 32;
        }
        if (substr[i] == '#')
        {
            flag=1;
        }
    }
    return flag;
}
/*
function:
1.Starting from the first digit of the text string, whether it is equal to the substring character by character
(if the substring encounters a '?', The text string automatically skips to the next digit).
If they are not equal, the text string is compared from the second digit, untill the substring reads '\ 0',
indicating that the match was successful.
2.Store the matched substring information
Parameters: pointers to text strings and substrings after uniform case,
and pointers to the original text strings
*/
int match1(char* str_text, char* substr,char*str_text_origin)
{
    int i,j,k=0;
    for (i=0;str_text[i]!='\0';i++)
    {
        for (j = 0; substr[j] != '\0'; j++)
        {
            if (substr[j] == '?')
            {
                continue;
            }
            else if (substr[j] != str_text[i + j])
            {
                break;
            }
        }
        if (substr[j] == '\0')//Find a matching substring
        {
            ans[k].match_position = i;
            strncpy(ans[k].match_substr, str_text_origin + i, j);
                k++;
        }
    }

    return k;
}
/*
Function: Matches a text string if the substring has "#"
Divided into three cases to handle: "#" in the first, last and middle
Parameters: pointers to text strings and substrings after uniform case, and pointers to the original text strings
*/
int match2(char* str_text, char* substr, char* str_text_origin)
{
    int i, j, k = 0, n, I, J;
    if (substr[0] == '#')
    {
        for (i = 0; str_text[i] != '\0'; i++)
        {
            for (j = 1; substr[j] != '\0'; j++)
            {
                if (substr[j] == '?')
                {
                    continue;
                }
                else if (substr[j] != str_text[i + j - 1])
                {
                    break;
                }
            }
            if (substr[j] == '\0')//Find a matching substring
            {
                for (n = i; n >= 0; n--)
                {
                    ans[k].match_position = n;
                    strncpy(ans[k].match_substr, str_text_origin + n, j - 1 + i - n);

                    k++;

                }

            }
        }

    }
    else
    {
        for (i = 0; str_text[i] != '\0'; i++)
        {
            for (j = 0; substr[j] != '#'; j++)
            {
                if (substr[j] == '?')
                {
                    continue;
                }
                else if (substr[j] != str_text[i + j])
                {
                    break;
                }
            }
            if (substr[j] == '#')//Find a matching substring
            {
                if (substr[j + 1] == '\0')
                {
                    I = i;
                    while (str_text[I] != '\0')
                    {
                        I++;
                    }

                    for (n = I - i; n >= 0; n--)
                    {
                        ans[k].match_position = i;
                        strncpy(ans[k].match_substr, str_text_origin + i, j + n);
                        k++;

                    }
                }
                else
                {
                    I = i + j;
                    J = j + 1;
                    for (I = i + j; str_text[I] != '\0'; I++)
                    {
                        for (J = j + 1; substr[J] != '\0'; J++)
                        {
                            if (substr[J] == '?')
                            {
                                continue;
                            }
                            else if (substr[J] != str_text[I + J - j - 1])
                            {
                                break;
                            }
                        }
                        if (substr[J] == '\0')//Find a matching substring
                        {
                            for (n = I - i - j; n >= 0; n--)
                            {
                                ans[k].match_position =i;
                                strncpy(ans[k].match_substr, str_text_origin + i, J - 1 + I - i - j);
                                k++;
                            }
                        }
                    }

                }
            }

        }

    }
    return k;
}

 /*
Function: Compare students by grades and student numbers
*/
    int cmp(const void* a, const void* b)
    {
        struct match_str* c = (struct match_str*)a;
        struct match_str* d = (struct match_str*)b;
        if (c->match_position != d->match_position)
            return (c->match_position - d->match_position);
        else
            return strcmp(c->match_substr, d->match_substr);
    }
