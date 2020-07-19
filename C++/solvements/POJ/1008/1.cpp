#include <stdio.h>
#include <cstring>
const int days_Ha_m = 20, days_Ha_y = 365, num_Tz = 13, name_Tz = 20, days_Tz_y = 260;

class Date
{
public:
    int Ha_d, Ha_m, Ha_y;
    int Tz_num, Tz_name, Tz_y;
    int days;
    Date();
    Date(int d, int m, int y);
};

int main(void)
{
    char Ha_dic[19][7] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
    char Tz_name[name_Tz][10] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};


    int n = 0;
    scanf("%d", &n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        int day = 0, month = 0, year = 0;
        char temp[7] = "";
        scanf("%d. %s%d", &day, temp, &year);
        for (int j = 0; j < 19; j++)
        {
            if (strcmp(Ha_dic[j], temp) == 0)
            {
                month = j;
                break;
            }
        }
        
        Date date = Date(day, month, year);
        printf("%d %s %d\n", date.Tz_num, Tz_name[date.Tz_name], date.Tz_y);
    }
    return 0;
}

Date::Date()
{
    Ha_d = 0; 
    Ha_m = 0;
    Ha_y = 0; 
    Tz_y =0;
    Tz_num =0; 
    Tz_name = 0;
    days = 0;
}

Date::Date(int d, int m, int y)
{
    Ha_d = d;
    Ha_m = m;
    Ha_y = y;
    days = Ha_d + Ha_m * days_Ha_m + Ha_y * days_Ha_y;

    Tz_y = days / days_Tz_y;
    Tz_name = (days % days_Tz_y) % name_Tz;
    Tz_num = (days % days_Tz_y) % num_Tz+1;
}