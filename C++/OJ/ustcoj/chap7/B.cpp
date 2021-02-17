//  main idea:  each mosquitoe has a try. Wrong? former mosquitoes has a new retry
#include <stdio.h>
#include <stdlib.h>

int is_matched[100] = {0};  //  whether the human has been liked. 0 means not yet, 1 means yes

typedef struct mosquitoe   //  store the information of mosquitie
{
    int like[100];  //  "id"s of humans the mosquitoe likes
    int num_like;   //  the number of humans he likes
    int goal;       //  his dream human
    int id;         //  his id
} Mosquitoe;

Mosquitoe input[100];   //  the input

//  function:   the mosquitoe whose id is the serial number will have a try
//  parameters:
//      serial_number:  the id number of the mosquitoe
//      n:  the total number of mosquitoes
//  return:
//      true:   this serie of tries is correct
//      false:  this serie of tries is wrong, a new try is required 
bool have_a_try(int serial_number, int n);

//  function:   compare the two numbers of humans two mosquitoes like
//  parameter:
//      p1:     will be changed to (Mosquitoe *) for comparation
//      p2:     the same as above
//  return:
//      if p1's number of humans p1 likes is fewer than p2's, return nagative number for not swapping
//      else if ... is larger than ..., return positive number for changing
//      else return 0
int cmp(const void *p1, const void *p2);

int main(void)
{
    int n = 0, i = 0, j = 0;    //  n: as the problem required. i & j: loop variables
    scanf("%d", &n);

    for (int k = 0; k < n; k++)     //  initialize
    {
        input[k].num_like = 0;
        input[k].goal = 0;
        input[k].id = k;
        for (int l = 0; l < 100; l++)
        {
            input[k].like[l] = 0;
        }
    }

    while (scanf("%d", &input[i].like[j]) != EOF)   //  input
    {
        (input[i].num_like)++;
        if (getchar() == '\n')      //  a new mosquitoe's data will be inputed later
        {
            i++;    //  new mosquitoe
            j = 0;
        }
        else
        {
            j++;
        }
    }
    
    qsort(input, n, sizeof(Mosquitoe), cmp);    //  make the mosquitoe whose number of humans he likes is fewest the first
                                                //  ascending order makes the process of deciding who to like more quickly
    have_a_try(0, n);       //  the first mosquitoe has a try and the second and ...

    for (int k = 0; k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            if (input[l].id == k)   //  due to qsort() has disorganized the input array, so we need to print according to the id of mosquitoe
            {
                printf("%d\n", input[l].goal);
            }
            
        }
        
    }

    return 0;
}

bool have_a_try(int serial_number, int n)
{
    if (serial_number == n)     //  the last mosquitoe has succeeded in finding his goal
    {
        return true;
    }

    for (int i = 0; i < input[serial_number].num_like; i++) //  have a try in all his likes
    {
        if (is_matched[input[serial_number].like[i]] == 0)  //  the human hasn't been occupied by a mosquitoe
        {
            is_matched[input[serial_number].like[i]] = 1;   //  make the human the goal
            if (have_a_try(serial_number + 1, n))           //  the following mosquitoes all have a successful try.
            {
                input[serial_number].goal = input[serial_number].like[i];   //  set the goal
                return true;    //  succeed
            }
            else
            {
                is_matched[input[serial_number].like[i]] = 0;   //  this is not a good try, next one
            }
        }
    }
    return false;   //  all failed(who took away my princess? i will find it)
}

int cmp(const void *p1, const void *p2)
{
    return ((Mosquitoe *)p1)->num_like - ((Mosquitoe *)p2)->num_like;
}
