//  mind:   find all islands and then calculate the area of territorial sea. memorize the largest

#include <stdio.h>
#include <stdlib.h>

//  a data
typedef struct land
{
    char property;      //  the property of this data. land:* sea:#
    bool belong_to_island;      //  whether this data has belonged to an island. yes, true; no, false
} Land;

Land sea[2000][2000];   //  the total matrix of the sea area, including lands.

//  function:   form the total island
//  parameters:
//      row, column:    the recent place of the land
//      left, right, top, bottom:   the boundary of the island area, including its territorial sea
//      m, n:   the total rows and columns of the input matrix
//  return:
//      the left, right, top, bottom will be changed for the island's expansion
//      after this function, you will get one complete island and the area of its territorial sea can be calculated
//      using left, right, top, bottom.
void Form_islands(int row, int column, int *left, int *right, int *top, int *bottom, int m, int n);

//  function:   judge whether the direction of expansion is valid
//  parameters:
//      row, column:    the recent place of the land
//      m, n:   the total rows and columns of the matrix
//      row_d, column_d:    the direction of the expansion
//                          row_d:  -1 means upward
//                                  0 means no movement
//                                  1 means downward
//                          column_d:   -1 leftward
//                                      0 no movement
//                                      1 rightward
//  return:
//      if the try of movement is valid, return 1
//      else return 0
int judge_expand(int row, int column, int m, int n, int row_d, int column_d);

int main(void)
{
    int m = 0, n = 0; //  m:  rows;   n:  columns
    int largest_area = 0;   // memorize the largest area of the territorial sea

    scanf("%d%d", &m, &n);
    getchar();  //  read '\n'

    for (int i = 0; i < m; i++)     //  initialize
    {
        for (int j = 0; j < n; j++)
        {
            sea[i][j].property = getchar();
            sea[i][j].belong_to_island = false;     //  at the beginning, no lands belong to an island, so assign it false
        }
        getchar();      //  read '\n'
    }

    //  judge each place
    for (int i = 0; i < m; i++)     //  the circle of rows
    {
        for (int j = 0; j < n; j++)     //  the circle of columns
        {
            if ((sea[i][j].property == '*') && (sea[i][j].belong_to_island == false))   //  it'd a land and it hasn't belonged to an island yet
            {
                int left = j, right = j, top = i, bottom = i;       //  initialize the territorial sea, just one point
                int sea_area = 0;   //  the area of territorial sea

                Form_islands(i, j, &left, &right, &top, &bottom, m, n);     //  form its island

                //  count the sea in the area of territory
                for (int k = top; k <= bottom; k++)     //  from the top to the bottom
                {
                    for (int l = left; l <= right; l++)     //  from the far left to the far right
                    {
                        if (sea[k][l].property == '#')      //  a sea
                        {
                            sea_area++;
                        }
                    }
                }
                if (sea_area > largest_area)        // this territorial sea is larger
                {
                    largest_area = sea_area;
                }
            }
        }
    }

    printf("%d", largest_area);
    return 0;
}

void Form_islands(int row, int column, int *left, int *right, int *top, int *bottom, int m, int n)
{
    sea[row][column].belong_to_island = true;   //  the current land has belonged to the island whose entire shape will be exposed soon

    //  explore the current land's neighbour
    for (int r = -1; r <= 1; r++)   //  up/same row/down    r is the initial of "row"
    {
        for (int c = -1; c <= 1; c++)   //  left/same column/right  c is the initial of "column"
        {
            if (r != 0 || c != 0)   //  don't stop your exploring pace at where you are now!
            {
                if (judge_expand(row, column, m, n, r, c))  //  is the try of expansion valid?
                {
                    if (*left == column && c == -1)
                    {
                        (*left)--;  // you have been in the left boundary of the island. continuing to explore left will make the left boundary go left
                    }
                    if (*right == column && c == 1)     //  similar to above
                    {
                        (*right)++;
                    }
                    if (*top == row && r == -1)
                    {
                        (*top)--;
                    }
                    if (*bottom == row && r == 1)
                    {
                        (*bottom)++;
                    }

                    //  now go to the new land to explore more
                    Form_islands(row+r, column+c, left, right, top, bottom, m, n);
                }
            }
        }
    }
}

int judge_expand(int row, int column, int m, int n, int row_d, int column_d)
{
    if (row+row_d > m-1 || row+row_d < 0)   //  out of the range of the matrix, invalid
    {
        return 0;
    }
    if (column+column_d > n-1 || column + column_d < 0)
    {
        return 0;
    }

    if (sea[row+row_d][column+column_d].property == '*' && sea[row+row_d][column+column_d].belong_to_island == false)   // it's a land and it hasn't yet belonged to an island
    {
        return 1;   //  valid, go ahead!
    }
    else    //  a sea or a land that has belonged to an island(tip: this will avoid going back to where you have explored. save the time)
    {
        return 0;
    }
}