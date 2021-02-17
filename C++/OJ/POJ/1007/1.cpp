#include <cstring>
#include <stdio.h>

class DNA
{
public:
    char order[51];
    int rev_order;
    DNA(char *);
    DNA();
    DNA(const DNA &);
};

void rev_sort(DNA *dna, int m);

void swap(DNA &, DNA &);

int main(void)
{
    int n = 0, m = 0;
    char temp[51] = "";
    DNA DNA_bunch[100];

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%s", temp);
        DNA_bunch[i] = DNA(temp);
    }
    rev_sort(DNA_bunch, m);

    for (int i = 0; i < m; i++)
    {
        printf("%s\n", DNA_bunch[i].order);
    }
    return 0;
}

DNA::DNA()
{
    // strcpy(order, "");
    // rev_order = 0;
}

DNA::DNA(char *str)
{
    strcpy(order, str);
    int len = strlen(str);

    rev_order = 0;
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (str[i] > str[j])
                rev_order++;
        }
    }
}

DNA::DNA(const DNA & st)
{
    strcpy(order, st.order);
    rev_order = st.rev_order;
}

void rev_sort(DNA * dna, int m)
{
    for (int i = 0; i < m-1; i++)
    {
        for (int j = m-1; j > i; j--)
        {
            if (dna[j].rev_order < dna[j-1].rev_order)
                swap(dna[j], dna[j-1]);
        }
    }
}

void swap(DNA & p1, DNA & p2)
{
    DNA temp = p1;
    p1 = p2;
    p2 = temp;
}