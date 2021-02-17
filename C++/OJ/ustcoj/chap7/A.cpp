//  main idea:  fix the first one and distribute the rest, which is a subproblem.
//              in the subproblem, when distributing number, we shouldn't give one place a number larger than top
//              this limit can make the distribution in descending order
#include <stdio.h>

//  function:   figure out the number of methods of distribution
//  parameters:
//      total:  the total number needed to be distributed
//      num_of_place:   the number of places available
//      top:    in each place, the number distributed is limited so that the distribution could be in descending order
//  return:     the number of methods of distribution
//              -1 means this distribution is impossible
int distribute(int total, int num_of_place, int top);

int main(void)
{
    int n = 0, k = 0, num_of_methods = 0, temp = 0;     //  n, k as the quesiton required. num_of_methods:  number of methods. temp: temporary number

    while (scanf("%d%d", &n, &k) != EOF)
    {
        num_of_methods = 1;     //  in the case of "20 4" input, 17 1 1 1 is a method
        for (int i = n - k; i >= 1; i--)    //  i from 16 to 1, 17 - i will be distributed in rest places
        {
            //  -1 means there are no possible method if we give the first place i.
            //  let alone larger number given to the rest places
            if ((temp = distribute(n - k + 1 - i, k - 1, i-1)) != -1)
            {
                num_of_methods += temp;
            }
            else
            {
                break;
            }
        }
        printf("%d\n", num_of_methods);
    }
    return 0;
}

int distribute(int total, int num_of_place, int top)
{
    int num_of_method = 0, temp = 0;    //  num_of_method:  number of methods in this situation. temp:  temporary number

    //  there is only one place available. so if total is fewer than top and it's not 0, that means the only one place will get the total, which is legal!
    if (num_of_place == 1 && total != 0 && total <= top)
    {
        return 1;
    }
    else if (num_of_place == 1 && total > top)  //  what the only one place gets is illegal!(must fewer than top)
    {
        return -1;
    }
    if (total == 0)     //  before entering this function, the pioneer took all and left nothing
    {
        return 1;
    }
    
    for (int i = (top < total) ? top : total; i >= 0; i--)  //  i must be fewer than top. besides, it shouldn't be larger than total
    {
        if ((temp = distribute(total-i, num_of_place-1, i)) == -1)  //  this i distribution is illegal, let alone following "i"s
        {
            break;
        }
        else
        {
            num_of_method += temp;
        }
    }
    return num_of_method;
}