#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    int id;
    char name[20];
    int endScore;
    int judgeScore;
    int isClassLeader;
    int isWestern;
    int numofEssay;
    int scholarship;
}Student;

void Swap(Student * a, Student * b)
{
    Student c = *a;
    *a = *b;
    *b = c;
}

void Quicksort(Student p[100], int left, int right)
{
    if (right <= left) return ;
    int i = left, j = right, pivot = rand()%(right - left +1) + left;
    Swap(&p[left], &p[pivot]);
    while (i<j)
    {
        while (p[left].scholarship >= p[j].scholarship && i<j)
            j--;
        while (p[left].scholarship <= p[i].scholarship && i<j)
            i++;
        Swap(&p[i], (i==j)?&p[left]:&p[j]);
    }
    Quicksort(p, left, i-1);
    Quicksort(p, i+1, right);
}

void Quicksortid(Student p[100], int left, int right)
{
    if (right <= left) return ;
    int i = left, j = right, pivot = rand()%(right - left +1) + left;
    Swap(&p[left], &p[pivot]);
    while (i<j)
    {
        while (p[left].id <= p[j].id && i<j)
            j--;
        while (p[left].id >= p[i].id && i<j)
            i++;
        Swap(&p[i], (i==j)?&p[left]:&p[j]);
    }
    Quicksortid(p, left, i-1);
    Quicksortid(p, i+1, right);

}

void SameSort(Student p[100], int n)
{
    int k = 0;
    while (p[k].scholarship == p[k+1].scholarship)
    {
        k++;
        if (k == n-1)
            break;
    }
    Quicksortid(p, 0, k);
}

void CalculateTheScholarship(Student * p)
{
    if (p->endScore > 80 && p->numofEssay >= 1)
        p->scholarship += 8000;
    if (p->endScore > 85 && p->judgeScore > 80)
        p->scholarship += 4000;
    if (p->endScore > 90)
        p->scholarship += 2000;
    if (p->endScore > 85 && p->isWestern)
        p->scholarship += 1000;
    if (p->judgeScore > 80 && p->isClassLeader)
        p->scholarship += 850;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    Student * p = (Student *)malloc(sizeof(Student) * n);
    for (int i = 0; i <n; i++)
    {
        char isWestern, isClassLeader;

        p[i].id = i;
        scanf("%s%d%d%*c%c%*c%c%d", p[i].name, &p[i].endScore, &p[i].judgeScore, &isClassLeader, &isWestern, &p[i].numofEssay);
        if (isClassLeader == 'Y')
            p[i].isClassLeader = 1;
        else
            p[i].isClassLeader = 0;
        if (isWestern == 'Y')
            p[i].isWestern = 1;
        else
            p[i].isWestern = 0;
        p[i].scholarship = 0;
        CalculateTheScholarship(&p[i]);
    }
    Quicksort(p, 0, n-1);
    SameSort(p, n);
    
    int sum = 0;
    for (int i=0; i<n; i++)
        sum += p[i].scholarship;
    printf("%s\n%d\n%d", p[0].name, p[0].scholarship, sum);
}
