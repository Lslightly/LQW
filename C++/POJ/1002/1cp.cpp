#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>

const int num_digits_phone = 7;

using namespace std;

class phone_number_std
{
private:
    string number;
    int times;

public:
    phone_number_std();
    phone_number_std(string);
    phone_number_std(const phone_number_std &);
    string show_number();
    int show_times();
    void add_times() { times++; };
    // int operator=(phone_number_std);
};

int map(char transformed);

void output(phone_number_std *phone, int count);

void time_sort(phone_number_std * phone, int count);

void phone_sort(phone_number_std * phone, int count);

void swap(phone_number_std & p1, phone_number_std & p2);

int cmp_time(const void *, const void *);

int cmp_phone(const void *, const void *);

int main(void)
{
    int n = 0, count = 0, i = 0;
    phone_number_std phone[5000];
    string temp = "";
    bool exist = false;
    
    
    scanf("%d", &n);
    getchar();
    for (i = 0; i < n; i++)
    {
        getline(cin, temp);
        for (int j = 0; j < count; j++)
        {
            if ((phone_number_std(temp)).show_number() == phone[j].show_number())
            {
                phone[j].add_times();
                exist = true;
                break;
            }
        }
        if (!exist)
        {
            phone[count] = phone_number_std(temp);
            phone[count].add_times();
            count++;
        }
        exist = false;
    }

    qsort(phone, count, sizeof(phone_number_std), cmp_time);

    i = 0;
    while (phone[i].show_times() >= 2)
    {
        i++;
        if (i == count) break;
    }
    count = i;

    if (count == 0)
    {
        cout << "No duplicates.";
        return 0;
    }

    qsort(phone, count, sizeof(phone_number_std), cmp_phone);

    output(phone, count);
    return 0;
}

phone_number_std::phone_number_std()
{
    number.resize(num_digits_phone + 1);
    times = 0;
}

phone_number_std::phone_number_std(string str)
{
    number.resize(num_digits_phone + 1);
    times = 0;

    int count = 0;
    for (int i = 0; i < str.size(); i++)
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
    int len = st.number.size();
    char * temp = new char [len+1];
    st.number.copy(temp, st.number.size(), 0);
    number = temp;
    times = st.times;
}

string phone_number_std::show_number()
{
    return number;
}

int phone_number_std::show_times()
{
    return times;
}

void time_sort(phone_number_std * phone, int count)
{
    bool flag = false;
    for (int i = 0; i < count-1; i++)
    {
        flag = false;
        for (int j = count - 1; j > i; j--)
        {
            if (phone[j].show_times() > phone[j-1].show_times())
            {
                swap(phone[j], phone[j-1]);
                flag = true;
            }
        }
        if (!flag)
        {
            break;
        }
    }
}

void phone_sort(phone_number_std * phone, int count)
{
    bool flag = false;
    for (int i = 0; i < count-1; i++)
    {
        flag = false;
        for (int j = count - 1; j > i; j--)
        {
            if (phone[j].show_number() < phone[j-1].show_number())
            {
                swap(phone[j], phone[j-1]);
                flag = true;
            }
        }
        if (!flag)
        {
            break;
        }
    }
}
void swap(phone_number_std & p1, phone_number_std & p2)
{
    phone_number_std temp = p1;
    p1 = p2;
    p2 = temp;
}

int cmp_time(const void *p1, const void *p2)
{
    return ((phone_number_std *)p2)->show_times() - ((phone_number_std *)p1)->show_times();
}

int cmp_phone(const void *p1, const void *p2)
{
    return (((phone_number_std *)p1)->show_number() > ((phone_number_std *)p2)->show_number())?-1:1;
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


void output(phone_number_std *phone, int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            putchar((phone[i].show_number())[j]);
        }
        putchar('-');
        for (int j = 3; j < num_digits_phone; j++)
        {
            putchar((phone[i].show_number())[j]);
        }
        printf(" %d\n", phone[i].show_times());
    }
}
