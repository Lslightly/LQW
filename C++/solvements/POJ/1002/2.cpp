#include <cstring>
#include <stdio.h>

int phone[10][10][10][10][10][10][10] = {0};

void trans(char *);

int map(char transformed);

int main(void)
{
    int n;
    char temp[201] = "";

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", temp);
        trans(temp);
    }

    bool flag = false;
    for (int i0 = 0; i0 < 10; i0++)
    {
        for (int i1 = 0; i1 < 10; i1++)
        {
            for (int i2 = 0; i2 < 10; i2++)
            {
                for (int i3 = 0; i3 < 10; i3++)
                {
                    for (int i4 = 0; i4 < 10; i4++)
                    {
                        for (int i5 = 0; i5 < 10; i5++)
                        {
                            for (int i6 = 0; i6 < 10; i6++)
                            {
                                if (phone[i0][i1][i2][i3][i4][i5][i6] >= 2)
                                {
                                    printf("%c%c%c-%c%c%c%c %d\n", i0+'0', i1+'0', i2+'0', i3+'0', i4+'0', i5+'0', i6+'0', phone[i0][i1][i2][i3][i4][i5][i6]);
                                    flag = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (!flag)
        printf("No duplicates.");
    return 0;
}

void trans(char *str)
{
    int number[7] = {0};

    int count = 0, len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] <= '9' && str[i] >= '0')
        {
            number[count] = str[i] - '0';
            count++;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            number[count] = map(str[i]);
            count++;
        }
    }
    phone[number[0]][number[1]][number[2]][number[3]][number[4]][number[5]][number[6]]++;
}

int map(char transformed)
{
    if (transformed >= 'A' && transformed <= 'C')
        return 2;
    else if (transformed >= 'D' && transformed <= 'F')
        return 3;
    else if (transformed >= 'G' && transformed <= 'I')
        return 4;
    else if (transformed >= 'J' && transformed <= 'L')
        return 5;
    else if (transformed >= 'M' && transformed <= 'O')
        return 6;
    else if (transformed == 'P' || transformed >= 'R' && transformed <= 'S')
        return 7;
    else if (transformed >= 'T' && transformed <= 'V')
        return 8;
    else if (transformed >= 'W' && transformed <= 'Y')
        return 9;

    return 0;
}
