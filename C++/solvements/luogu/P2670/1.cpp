#include <stdio.h>

void input(int &n, int &m, bool condition[100][100]);

int count(bool condition[100][100], int i, int j, int n, int m);

int main(void)
{
    int n = 0, m = 0;
    bool condition[100][100] = {};

    input(n, m, condition);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (condition[i][j])
            {
                putchar('0' + count(condition, i, j, n, m));
            }
            else
            {
                putchar('*');
            }
        }
        putchar('\n');
    }
}

void input(int &n, int &m, bool condition[100][100])
{
    char temp = 0;

    scanf("%d%d", &n, &m);
    getchar();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            temp = getchar();
            if (temp == '*')
            {
                condition[i][j] = false;
            }
            else
            {
                condition[i][j] = true;
            }
        }
        getchar();
    }
}

int count(bool condition[100][100], int i, int j, int n, int m)
{
    int num = 0;

    bool left = true, right = true, up = true, down = true;

    if (i == 0) up = false;
    if (i == n-1) down = false;
    if (j == 0) left = false;
    if (j == m-1) right = false;
    
    for (int pos_i = i-1; pos_i <= i+1; pos_i++)
    {
        if (pos_i == i-1 && !up)
            continue;
        if (pos_i == i+1 && !down)
            continue;
        
        for (int pos_j = j-1; pos_j <= j+1; pos_j++)
        {
            if (pos_j == j-1 && !left)
                continue;
            if (pos_j == j+1 && !right)
                continue;
            if (!condition[pos_i][pos_j]) num++;
        }
    }
    return num;
}