#include <stdio.h>
#include <string.h>

const int max_n = 200;

bool used[200] = {0};

typedef struct node
{
    int goal;
    int rank;
    char ch;
} node;

void k_replacement(node *sequence, int k, int n);

//  计算轮换的阶
void rank(node *sequence, int n);

int main(void)
{
    int n = 0, temp = 0, k = 0;
    while (scanf("%d", &n) && (n != 0))
    {
        node *sequence = new node[n];

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &temp);
            sequence[i].goal = temp - 1;
            sequence[i].rank = 0;
        }
        rank(sequence, n);

        char *str = new char[n + 1];
        while (scanf("%d", &k) && (k != 0))
        {
            getchar();
            fgets(str, n + 1, stdin);
            for (int i = ((str[strlen(str) - 1] == '\n') ? strlen(str) - 1 : strlen(str)); i < n; i++)
            {
                str[i] = ' ';
            }
            for (int i = 0; i < n; i++)
            {
                sequence[i].ch = str[i];
            }

            k_replacement(sequence, k, n);

            for (int i = 0; i < n; i++)
            {
                putchar(sequence[i].ch);
            }
            putchar('\n');
        }

        putchar('\n');
    }

    return 0;
}

void rank(node *sequence, int n)
{
    int count = 0, mem = 0;
    for (int i = 0; i < n; i++)
    {
        count = 0;
        if (sequence[i].rank == 0)
        {
            mem = i;
            do
            {
                count++;
                mem = sequence[mem].goal;
                if (sequence[mem].rank != 0)
                {
                    count = sequence[mem].rank;
                    break;
                }
            } while (mem != i);
            sequence[i].rank = count;
        }
    }
}

void k_replacement(node *sequence, int k, int n)
{
    int times = 0;
    for (int i = 0; i < n; i++)
    {
        if (used[i] == true)
        {
            continue;
        }
        used[i] = true;
        times = k % sequence[i].rank;

        int l = i;
        char mem = sequence[l].ch, temp = 0;

        do
        {
            for (int j = 0; j < times; j++)
            {
                l = sequence[l].goal;
            }
            used[l] = true;
            temp = sequence[l].ch;
            sequence[l].ch = mem;
            mem = temp;
        }while (l != i);
    }
    for (int i = 0; i < max_n; i++)
    {
        used[i] = false;
    }
    
}