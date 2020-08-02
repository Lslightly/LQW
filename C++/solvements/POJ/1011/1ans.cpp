#include <algorithm>
#include <iostream>
using namespace std;
int n;
bool dfs(int *part, int *visit, int len, int num, int nowlen, int ind)
{
    if (num == n)
        return true;
    int lastnum = -1;
    for (int i = ind; i <= n; i++)
    {
        if (visit[i] == 1 || part[i] == lastnum)
            continue;
        visit[i] = 1;
        if (nowlen + part[i] < len)
        {
            if (dfs(part, visit, len, num + 1, nowlen + part[i], i))
                return true;
            else
                lastnum = part[i];
        }
        else if (nowlen + part[i] == len)
        {
            if (dfs(part, visit, len, num + 1, 0, 0))
                return true;
            else
                lastnum = part[i];
        }
        visit[i] = false;
        if (nowlen == 0)
            break;
    }
    return false;
}
bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    int part[65];
    int visit[65];
    while (1)
    {
        cin >> n;
        if (n != 0)
        {
            int val;
            int sum = 0;
            for (int i = 0; i < n; i++)
            {
                cin >> val;
                part[i] = val;
                visit[i] = 0;
                sum = sum + val;
            }
            sort(part, part + n, cmp);
            int max = part[1];
            //cout<<max<<endl;
            bool flag = false;
            for (int i = max; i <= sum / 2; i++)
            {
                if (sum % i == 0)
                {
                    if (dfs(part, visit, i, 0, 0, 0))
                    {
                        cout << i << endl;
                        flag = true;
                        break;
                    }
                }
            }
            if (!flag)
                cout << sum << endl;
        }
        else
            break;
    }

    return 0;
}
