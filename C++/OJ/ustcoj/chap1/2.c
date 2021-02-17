// brief description:   change student's score for justice(GPA)
// To learn more, turn to https://oj.ustc.edu.cn/#/contests/89/problems/B

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  the student informaiton
//  member:
//      name: student's name
//      id: student's id
//      origin_score: student's original score
//      final_score: student's score after the change
typedef struct student
{
    char name[25];
    char id[11];
    int origin_score;
    int final_score;
} Student;

int num_score[102] = {0}; //  the number of students in each score

//  function:   compare the orginal score only
//  Parameters:
//      c1 and c2 are pointers to Student object to be compared
//  Return:
//      > 0, if c1's score < c2's score(to be swapped)
//      < 0, if c1's score > c2's score
int cmp_score(const void *c1, const void *c2);

//  function:   compare the final score first. If two student's scores are equal, compare the id
//  Parameters:
//      the two are pointers to Student object to be compared
//  Return:
//      if c1's score < c2's score, return positive number for qsort() to swap them
//      else if c1's score > c2's score, return negative number so that they won't be swapped
//      else
//          if c1's id < c2's id, return negative number. (no change)
//          else, return positive number. (swap them)
int cmp_ScoreId(const void *c1, const void *c2);

//  function:   get the strange name of one student
//  Parameters:
//      p:  pointer to the first address of student's name array
//      n:  the limited number of character input.
//  Return:
//      the student's name will be stored in the name array of struct student
//      no return
void s_gets(char *p, int n);

//  function:   figure out x, the infimum of A scores
//  Parameters:
//      x: the pointer to x in main()
//      n: the total number of students
//  Return:     x is got
void figure_out_x(int *x, int n);

//  function:   figure out y, the supremum of F scores
//  Parameters:
//      y: the pointer to y in main()
//      n: the total number of students
//  Return:     y is got
void figure_out_y(int *y, int n);

int main(void)
{
    // Initialize
    int n = 0; // the number of students
    scanf("%d", &n);
    getchar();                                                  // read \n
    Student *pStudent = (Student *)malloc(sizeof(Student) * n); //  allocate memory for student

    // input
    for (int i = 0; i < n; i++)
    {
        s_gets(pStudent[i].name, 21); //  the student's strange name is no longer than 20, but \n should be reckoned with
        scanf("%s%d", pStudent[i].id, &pStudent[i].origin_score);
        getchar();                             //  read the \n left in the buffer
        num_score[pStudent[i].origin_score]++; //  the number of students in this score input increases
    }

    int x = 0, y = 0; //  x: the infimum of A scores;
                      //  y: the supremum of F scores;
    //  figure out x
    figure_out_x(&x, n);
    // figure out y
    figure_out_y(&y, n);

    // qsort by score
    qsort(pStudent, n, sizeof(Student), cmp_score);

    // change students' scores
    int F_score = 59;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (pStudent[i].origin_score >= y + 1 && pStudent[i].origin_score <= x - 1) //  [y+1, x-1]
            pStudent[i].final_score = 60 + (24 * (pStudent[i].origin_score - y - 1)) / (x - 2 - y);
        else if (pStudent[i].origin_score >= x && pStudent[i].origin_score <= 100) //  [x, 100]
            pStudent[i].final_score = 85 + (15 * (pStudent[i].origin_score - x)) / (100 - x);
        else //  [0, y]
        {
            pStudent[i].final_score = F_score;
            for (k = i + 1; k < n && pStudent[k].origin_score == pStudent[k - 1].origin_score; k++)
            { // students with same original scores deserves same final scores
                pStudent[k].final_score = F_score;
            }
            i = k - 1;         // because pStudent[k].origin_score != pStudent[k-1].origin_score, i should subtact 1 so that there won't be one student passed
            if (F_score == 50) //  protect those whose scores are lowest
                continue;
            else
            {
                F_score--; //  rank lowered
            }
        }
    }

    // qsort by final score first, then id
    qsort(pStudent, n, sizeof(Student), cmp_ScoreId);

    for (int i = 0; i < n; i++) //  output
    {
        printf("%s\n%d\n", pStudent[i].name, pStudent[i].final_score);
    }
    return 0;
}

void s_gets(char *p, int n)
{
    int i = 0;
    while (i < n)
    {
        p[i] = getchar();
        if (p[i] == '\n')
            break;
        i++;
    }
    p[i] = '\0'; //    replace \n with \0. (ensure p could be a string)
}

int cmp_score(const void *c1, const void *c2)
{
    return (((Student *)c2)->origin_score - ((Student *)c1)->origin_score);
}

int cmp_ScoreId(const void *c1, const void *c2)
{
    int a = ((Student *)c1)->final_score, b = ((Student *)c2)->final_score;
    if (a < b)
        return 1;
    else if (a > b)
        return -1;
    else
    {
        return strcmp(((Student *)c1)->id, ((Student *)c2)->id);
    }
}

void figure_out_x(int *x, int n)
{
    int x_sum = 0;                 //  x_sum:  the number of students whose scores are
                                   //          higher than *x
    for (*x = 101; *x > 0; (*x)--) //  *x could be 101
    {
        x_sum += num_score[*x];
        if (((x_sum + num_score[*x - 1]) * 1.0 / n) - 0.4 > 0 && (x_sum * 1.0 / n) - 0.4 <= 0)
        {
            //  the percent of A students will be more than 40% if more students whose score is *x-1
            //  are added. So stop and the *x now is the correct one
            break;
        }
    }
}

void figure_out_y(int *y, int n)
{
    int F_sum = 0;                // the number of students whose scores are lower than y
    for (int i = 0; i <= 59; i++) //  accumulation
    {
        F_sum += num_score[i];
    }
    if (F_sum * 1.0 / n - 0.05 <= 0) //  the number of student's score in [0, 59] <= 50%
        *y = 59;
    else //  > 50%
    {
        F_sum = 0;
        if (num_score[0] * 1.0 / n - 0.05 > 0) // all 0(the extreme condition)
            *y = -1;
        else // normal condition
        {
            for (*y = 0; *y < 100; (*y)++)
            {
                F_sum += num_score[*y];
                if (((F_sum + num_score[*y + 1]) * 1.0 / n) - 0.05 > 0 && (F_sum * 1.0 / n) - 0.05 <= 0)
                {
                    //  the percent of F students will be more than 5% if more students whose score is *y-1
                    //  are added. So stop and the *y now is the correct one
                    break;
                }
            }
        }
    }
}
