#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    freopen("SimpleTimerResult1.txt", "r", stdin);

    double result[205] = {0};
    int num[13] = {0};
    int sum = 0;
    double sigma = 0.073378606, average = 3.1962651;
    int possibility[3] = {0};
    for (int i = 0; i < 200; i++)
    {
        scanf("%lf", &result[i]);
        if (result[i] >= 3.02109 && result[i] < 3.047613846)
        {
            num[0]++;
        }
        else if (result[i] >= 3.047613846 && result[i] < 3.074137692)
        {
            num[1]++;
        }
        else if (result[i] >= 3.074137692 && result[i] < 3.100661538)
        {
            num[2]++;
        }
        else if (result[i] >= 3.100661538 && result[i] < 3.127185385)
        {
            num[3]++;
        }
        else if (result[i] >= 3.127185385 && result[i] < 3.153709231)
        {
            num[4]++;
        }
        else if (result[i] >= 3.153709231 && result[i] < 3.180233077)
        {
            num[5]++;
        }
        else if (result[i] >= 3.180233077 && result[i] < 3.206756923)
        {
            num[6]++;
        }
        else if (result[i] >= 3.206756923 && result[i] < 3.233280769)
        {
            num[7]++;
        }
        else if (result[i] >= 3.233280769 && result[i] < 3.259804615)
        {
            num[8]++;
        }
        else if (result[i] >= 3.259804615 && result[i] < 3.286328462)
        {
            num[9]++;
        }
        else if (result[i] >= 3.286328462 && result[i] < 3.312852308)
        {
            num[10]++;
        }
        else if (result[i] >= 3.312852308 && result[i] < 3.339376154)
        {
            num[11]++;
        }
        else
        {
            num[12]++;
        }
        if (result[i] >= average - sigma && result[i] <= average + sigma)
        {
            possibility[0] += 1;
        }
        if (result[i] >= average - 2*sigma && result[i] <= average + 2 * sigma)
        {
            possibility[1] += 1;
        }
        if (result[i] > average - 3 * sigma && result[i] < average + 3 * sigma)
        {
            possibility[2]++;
        }
    }

    for (int i = 0; i < 13; i++)
    {
        printf("%d %d\n", i + 1, num[i]);
        sum += num[i];
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%d %lf\n",possibility[i], possibility[i]/200.0);
    }
    
}