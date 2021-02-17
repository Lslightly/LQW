//  brief description:
//  string T is much longer than string P, look for all subscripts in T, where a substring equals to P begins.
//  # equals to several character, ? equals to one character

#include <stdio.h>
#include <string.h>

//  function:       all UPPERCASE to lowercase, no change to the input
//  Parameters:     str: a string needed to be changed
//  Return:         a pointer to the first address of the lowercase string
char *my_strlwr(char *str);

//  functiong:      Judge whether the part of pattern beginning in pattern_left is equal to the part of text beginning in text_left;
//  Parameters:     text:   the T string
//                  pattern:    the P string
//                  text_left:  the starting subscript of text
//                  pattern_left:   the starting subscript of pattern
//                  text_right:     the end subscript of text needed to be compared
//                  pattern_right:  the end subscript of text needed to be compared
//  Return:         if they are not equal, return -2
//                  else return the subscipt of the end letter for output;
int IsEqual(char *text, char *pattern, int text_left, int pattern_left, int text_right, int pattern_right);

int main(void)
{
    char text_origin[501] = {}, *text = NULL, *pattern = NULL, pattern_origin[501] = {}; 
    // nouns with "_origin" mean input data, otherwise they have been changed to lowercase
    int text_len = 0, pattern_len = 0;
    int whereis_pound = -1; // if there isn't pound(#) sign, whereis_pound = -1; else whereis_pound = the subscipt of #

    // change the input string into the same lowercase format
    scanf("%s%s", text_origin, pattern_origin);
    text = my_strlwr(text_origin);
    text_len = strlen(text);
    pattern = my_strlwr(pattern_origin);
    pattern_len = strlen(pattern);

    for (int i = 0; i < pattern_len; i++) // to find where is #
    {
        if (pattern[i] == '#')
        {
            whereis_pound = i;
            break;
        }
    }

    if (whereis_pound == -1) // no #, so no character will be passed and compare text and pattern directly
    {
        int right = 0;                     // the end of the substring needed to be output
        for (int i = 0; i < text_len; i++) // from 0 to the last of the text compare the text and pattern
        {
            if ((right = IsEqual(text, pattern, i, 0, text_len - 1, pattern_len - 1)) != -2) // equal
            {
                printf("%d ", i);
                for (int j = i; j <= right; j++)
                    putchar(text_origin[j]); // as requested, output the original substring
                putchar('\n');
            }
        }
    }
    else if (whereis_pound != pattern_len - 1) // # is not at the end of the pattern
    {
        int right = 0; // the end subscript
        for (int i = 0; i < text_len; i++)
        {
            // the substring of pattern before # is equal to the substring of text
            if ((right = IsEqual(text, pattern, i, 0, text_len - 1, whereis_pound - 1)) != -2)
            {
                // skip some characters in text and compare the following part of text with the part of pattern after #
                // j = right + 1 means the subscript after the substring of text which has been compared
                for (int j = right + 1; j < text_len; j++)
                {
                    // the substring of pattern after # is equal to the substring of text
                    if ((right = IsEqual(text, pattern, j, whereis_pound + 1, text_len - 1, pattern_len - 1)) != -2)
                    {
                        printf("%d ", i);
                        for (int k = i; k <= right; k++)
                        {
                            putchar(text_origin[k]);
                        }
                        putchar('\n');
                    }
                }
            }
        }
    }
    else // # is at the end of the pattern
    {
        int right = 0;
        for (int i = 0; i < text_len; i++)
        {
            // the substring of pattern before # is equal to the substring of text
            if ((right = IsEqual(text, pattern, i, 0, text_len - 1, pattern_len - 2)) != -2)
            {
                for (int j = right; j < text_len; j++)
                {
                    printf("%d ", i);
                    for (int k = i; k <= right; k++)
                        putchar(text_origin[k]);
                    for (int k = right + 1; k <= j; k++) // after the right, all letters should be output, for they are equal to #
                        putchar(text_origin[k]);
                    putchar('\n');
                }
            }
        }
    }
}

char *my_strlwr(char *str)
{
    int length = strlen(str);
    char *result = new char[length + 1]; // '\0' should be considered
    for (int i = 0; i < length; i++)
    {
        if (str[i] <= 'Z' && str[i] >= 'A') // UPPERCASE to lowercase
            result[i] = str[i] + 32;
        else // no change, including ?, #
            result[i] = str[i];
    }
    result[length] = '\0';
    return result;
}

int IsEqual(char *text, char *pattern, int text_left, int pattern_left, int text_right, int pattern_right)
{
    int i = text_left, j = pattern_left;
    int flag = 1; // are the substring of text and pattern equal? yes, 1; no 0
    for (; j <= pattern_right; j++)
    {
        if ((text[i] != pattern[j]) && (pattern[j] != '?')) // not equal
        {
            flag = 0;
            break;
        }
        if ((i == text_right) && (j < pattern_right))
        { // the text subscript has reached the end(the part of text to short) but the part of pattern is too long.
            // Obviously not equal
            flag = 0;
            break;
        }
        i++; // i++ simutaneously
    }
    if (flag)         //  equal
        return i - 1; // i added one more time in the last interation, so -1
    else              // not equal
        return -2;
}
