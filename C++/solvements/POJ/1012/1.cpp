#include <stdio.h>

int main(void)
{
    for (int k = 1; k < 14; k++)
    {
        int num_killed = 0, m = k + 1, position = -1;
        bool flag = true;

        while (1)
        {
            num_killed = 0;
            position = -1;
            flag = true;
            while (num_killed < k)
            {
                position += m;
                position %= 2 * k - num_killed;
                num_killed++;
                if (position < k)
                {
                    flag = false;
                    break;
                }
                position--;
            }
            if (flag == false)
            {
                m++;
                if ((m - 1) % (2 * k) < k)
                    m += k;
            }
            else
            {
                printf("%d,", m);
                break;
            }
        }
    }

    return 0;
}