#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>

const int num_digits_phone = 7;

using namespace std;

class phone_number_std
{
public:
    char number[num_digits_phone+1];
    int times;
    phone_number_std();
    phone_number_std(char *);
    phone_number_std(const phone_number_std &);
    // int operator=(phone_number_std);
};

int map(char transformed);

void output(phone_number_std *phone, int count);

int cmp_num(const void *, const void *);

void time_sort(phone_number_std * phone, int &count);

int main(void)
{
    int n = 0, count = 0, i = 0;
    phone_number_std phone[100001];
    char temp[201] = "";
    bool exist = false;
    
    
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s", temp);
        for (int j = 0; j < count; j++)
        {
            if (strcmp((phone_number_std(temp)).number, phone[j].number) == 0)
            {
                phone[j].times++;
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            phone[count] = phone_number_std(temp);
            phone[count].times++;
            count++;
        }
        exist = false;
    }

    for (i = 0; i < count; i++)
    {
        if (phone[i].times == 1)
        {
            int j = i;
            while (phone[j].times == 1)
            {
                j++;
                if (j == count) break;
            }
            for (int k = j; k < count; k++)
            {
                phone[k-j+i] = phone[k];
            }
            count -= j-i;
            i--;
        }
    }

    if (count == 0)
    {
        printf("No duplicates.");
        return 0;
    } 

    qsort(phone, count, sizeof(phone_number_std), cmp_num); 

    output(phone, count);
    return 0;
}

phone_number_std::phone_number_std()
{
    
}

phone_number_std::phone_number_std(char * str)
{
    times = 0;

    int count = 0, len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] <= '9' && str[i] >= '0')
        {
            number[count] = str[i];
            count++;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            number[count] = map(str[i]) + '0';
            count++;
        }
    }
}

phone_number_std::phone_number_std(const phone_number_std & st)
{
    strcpy(number, st.number);
    times = st.times;
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

int cmp_num(const void * p1, const void * p2)
{
    return strcmp(((phone_number_std *)p1)->number, ((phone_number_std *)p2)->number);
}

int cmp_time(const void * p1, const void * p2)
{
    return ((phone_number_std *)p2)->times - ((phone_number_std *)p1)->times;
}

void output(phone_number_std *phone, int count)
{
    bool samenum = false;
    for (int i = 0; i < count; i++)
    {
        if (phone[i].times == 1) continue;
        samenum = true;
        for (int j = 0; j < 3; j++)
        {
            putchar((phone[i].number)[j]);
        }
        putchar('-');
        for (int j = 3; j < num_digits_phone; j++)
        {
            putchar((phone[i].number)[j]);
        }
        printf(" %d\n", phone[i].times);
    }
    if (!samenum)
    {
        printf("No duplicates.");
    }
}

void time_sort(phone_number_std * phone, int & count)
{
    bool isswapped = false;
    for (int i = 0; i < count-1; i++)
    {
        isswapped = false;
        for (int j = count - 1; j > i; j--)
        {
            if (phone[j].times == 1 || phone[j-1].times == 1) count--;
            if (phone[j].times > phone[j-1].times)
            {
                swap(phone[j], phone[j-1]);
                isswapped = true;
            }
        }
        if (!isswapped) break;
    }
    
}