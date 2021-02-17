//  main mind:  find the longest distance in up, down, left and right direction, then +1. record the distance for next asks.
#include <stdio.h>
#include <string.h>

//  function:   find the longest distance in up, down, left and right direction, then +1. record the distance for next asks.
//  parameters:
//      n, m:   rows and columns
//      i, j:   the current position
//      h:      height
//  return:     the longest distance starting from the current position
int find_longest(int n, int m, int i, int j, int h[100][100]);

//  function:   figure out the larger number between a and b, and return it
//  parameters:
//      a, b:   numbers to be compared
//  return:     the larger one
int max(int a, int b);

int start_here[100][100] = {0}; //  record the longest distance starting from the current position

int main(void)
{
    int n = 0, m = 0, h[100][100] = {0}, longest_dis = 0, temp = 0; //  n, m:   rows and columns
                                                                    //  h:      height
                                                                    //  longest_dis:    longest distance
                                                                    //  temp:   temporary number

    //  input
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &h[i][j]);
        }
    }

    //  find the longest distance
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            //  the current position hasn't been passed by.
            //  it might be the starting point of the longest distance
            //  start_here[i][j] != 0 means that the place has been passed by and it belongs to a path.
            //  so it's unnecessary to seek the longest distance starting from here again.
            if (start_here[i][j] == 0)
            {
                temp = find_longest(n, m, i, j, h);
                if (longest_dis < temp) //  starting from here, the distance is longer
                {
                    longest_dis = temp;
                }
            }
        }
    }
    printf("%d", longest_dis);
    return 0;
}

int find_longest(int n, int m, int i, int j, int h[100][100])
{
    if (start_here[i][j] != 0) //  return the distance that has been calculated before
    {
        return start_here[i][j];
    }
    else //  not calculated yet
    {
        int max_direction = 0; //  in up, down, left, right four directions, the largest one will be recorded
        if (j - 1 >= 0)        //  left(not beyond the border)
        {
            if (h[i][j] > h[i][j - 1]) //  turning left is allowed
            {
                max_direction = find_longest(n, m, i, j - 1, h); //  record it to be compared
            }
        }
        if (j + 1 <= m - 1) //  right(not beyond the border)
        {
            if (h[i][j] > h[i][j + 1]) //  turning right is allowed
            {
                //  compare the longest distance in the right direction with ones in other direcitons
                max_direction = max(max_direction, find_longest(n, m, i, j + 1, h));
            }
        }
        if (i - 1 >= 0) //  up
        {
            if (h[i][j] > h[i - 1][j]) //  going up is allowed
            {
                max_direction = max(max_direction, find_longest(n, m, i - 1, j, h));
            }
        }
        if (i + 1 <= n - 1) //  down
        {
            if (h[i][j] > h[i + 1][j])
            {
                max_direction = max(max_direction, find_longest(n, m, i + 1, j, h));
            }
        }
        start_here[i][j] = max_direction + 1; //  the current position is also one step
        return start_here[i][j];
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}