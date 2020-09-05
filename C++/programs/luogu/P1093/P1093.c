#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 300

typedef struct student
{
    int id;
    int chinese;
    int maths;
    int english;
    int total;
}Student;

int Judge(Student p[SIZE], char * standard, int left, int right, int direction); // direct为-1表示p[i]<p[j]，0表示相等，1表示p[i]>p[j],-2表示<=,2表示>=,返回1表示真

void Quicksort(Student p[SIZE], char * standard, int left, int right, int direction);

void swap(Student * a, Student * b);

void SameJudge(Student p[SIZE], char * standard, int left, int right);

int main(void)
{
    int n;
    scanf("%d", &n);
    Student * p = (Student *)malloc(sizeof(Student) * n);
    for (int i = 0; i<n; i++)
    {
        scanf("%d%d%d", &p[i].chinese, &p[i].maths, &p[i].english);
        p[i].id = i+1;
        p[i].total = p[i].chinese + p[i].maths + p[i].english;
    }
    Quicksort(p, "total", 0, n-1, 1);
    for (int i = 0; i<5; i++)
    {
        printf("%d %d\n", p[i].id, p[i].total);
    }
}

void swap(Student * a, Student * b)
{
    Student c = *a;
    *a = *b;
    *b = c;
}

void Quicksort(Student p[SIZE], char * standard, int left, int right, int direction)
{
    if (right <= left) return ;
    int i = left, j= right, pivot = rand()%(right - left +1) + left;
    swap(&p[left], &p[pivot]);
    while (i<j)
    {
        while (Judge(p, standard, left, j, (direction/abs(direction)*2)) && i<j)
            j--;
        while (Judge(p, standard, left, i, -direction/abs(direction)*2) && i<j)
            i++;
        swap(&p[i], (i==j)?&p[left]:&p[j]);
    }
    Quicksort(p, standard, left, i-1, direction);
    Quicksort(p, standard, i+1, right, direction);
    SameJudge(p, standard, left, right);
}

void SameJudge(Student p[SIZE], char * standard, int left, int right)
{
    for (int i = left; i<right; i++)
    {
        int k = i;
        while (Judge(p, standard, i, i+1, 0) && i < right)
            i++;
        if (strcmp(standard, "total") == 0)
            Quicksort(p, "chinese", k, i, 1);
        else if (strcmp(standard, "chinese") == 0)
            Quicksort(p, "id", k, i, -1);
    }
}

int Judge(Student p[SIZE], char * standard, int left, int right, int direction)
{
    int a, b;
    if (strcmp(standard, "total") == 0)
    {
        a = p[left].total;
        b =p[right].total;
    }
    else if (strcmp(standard, "chinese") == 0)
    {
        a = p[left].chinese;
        b = p[right].chinese;
    }
    else if (strcmp(standard, "id") == 0)
    {
        a = p[left].id;
        b = p[right].id;
    }
    if (direction == 2)
            if (a >= b)
                return 1;
            else
                return 0;
        else if (direction == -2)
            if (a <= b)
                return 1;
            else
                return 0;
        else if (direction == 1)
            if (a > b)
                return 1;
            else
                return 0;
        else if (direction == -1)
            if (a < b)
                return 1;
            else
                return 0;
        else if (direction == 0)
            if (a == b)
                return 1;
            else
                return 0;

}
