// brief descripition:  figure out the shortest serie of operations which act on clocks with random times ranging among 3, 6, 9, 12
//                      and finally change them all to 12 o'clock. Each operation makes specific clocks' hands rotate 90 degrees clockwise

#include <stdio.h>

char ans[4][4][4][4][4][4][4][4][4][54] = {""};     // answer

// function:    make clocks' hands rotate 90 degrees several times(the clocks are ones operated in the input which_operation)
// Parameters:  operation:  the whole operations array(won't be changed, so const)
//              clock:      the whole clock array
//              times:      times needed to rotate the clocks' hands
//              which_operation:    which_operation figures out clocks needed to be operated
// Return:      clocks will be changed several times as requested
void rotate_clockwise_some_times(const int operation[9][10], int clock[9], int times[9], int which_operation);

// function:    return the clocks operated several times in which_operation
// Parameters:  operation:  the whole operations array(won't be changed, so const)
//              clock:      the whole clock array
//              times:      times needed to rotate the clocks' hands
//              which_operation:    which_operation figures out clocks needed to be operated
// Return:      clocks will be changed back to the original status
void return_to_origin(const int operation[9][10], int clock[9], int times[9], int which_operation);

int main(void)
{
    int operation[9][10] = {{3, 0, 1, 2},    //  as the problem requested
                            {4, 0, 1, 3, 4}, //  the first element in each row is the number of clocks needed to be operated
                            {3, 0, 3, 6},    //  the following are the subscripts of clocks
                            {4, 1, 2, 4, 5},
                            {5, 1, 3, 4, 5, 7},
                            {3, 2, 5, 8},
                            {4, 3, 4, 6, 7},
                            {4, 4, 5, 7, 8},
                            {3, 6, 7, 8}};

    //  find all answers
    for (int i0 = 0; i0 < 4; i0++)
    {
        for (int i1 = 0; i1 < 4; i1++)
        {
            for (int i2 = 0; i2 < 4; i2++)
            {
                for (int i3 = 0; i3 < 4; i3++)
                {
                    for (int i4 = 0; i4 < 4; i4++)
                    {
                        for (int i5 = 0; i5 < 4; i5++)
                        {
                            for (int i6 = 0; i6 < 4; i6++)
                            {
                                for (int i7 = 0; i7 < 4; i7++)
                                {
                                    for (int i8 = 0; i8 < 4; i8++)
                                    {
                                        int clock[9] = {0}, times[9] = {0};                 //  clock:  the status of clocks    times:  operation times(there are 9 operations)
                                        int mintimes = 0, min_operation[9] = {0}, maxi = 0; //  mintimes:   the minimum of the sum of all operation times
                                                                                            //  min_operaiton:  stores the times of each operaiton if the sum of times are the minimum
                                                                                            //  maxi:       the subscript of the last but not 0 times operaiton so that I could output more easily

                                        clock[0] = i0;
                                        clock[1] = i1;
                                        clock[2] = i2;
                                        clock[3] = i3;
                                        clock[4] = i4;
                                        clock[5] = i5;
                                        clock[6] = i6;
                                        clock[7] = i7;
                                        clock[8] = i8;
                                        for (times[0] = 1; times[0] <= 4; times[0]++) // the 0 operation's times enumerated
                                        {
                                            for (int j0 = 1; j0 <= operation[0][0]; j0++) // specific clocks' hands rotated
                                            {
                                                clock[operation[0][j0]] = (clock[operation[0][j0]] + 1) % 4;
                                            }
                                            for (times[1] = 1; times[1] <= 4; times[1]++) //  1st operaiton's times enumerated
                                            {
                                                for (int j1 = 1; j1 <= operation[1][0]; j1++)
                                                {
                                                    clock[operation[1][j1]] = (clock[operation[1][j1]] + 1) % 4;
                                                }
                                                times[2] = (4 - clock[0]) % 4; // 2nd operation's times has been determined by the two above operations(0 clock won't be changed later)
                                                rotate_clockwise_some_times(operation, clock, times, 2);
                                                for (times[3] = 1; times[3] <= 4; times[3]++) // 3rd operation's times enumerated
                                                {
                                                    for (int j3 = 1; j3 <= operation[3][0]; j3++)
                                                    {
                                                        clock[operation[3][j3]] = (clock[operation[3][j3]] + 1) % 4;
                                                    }

                                                    times[4] = (4 - clock[1]) % 4;                           //   1st clock won't be changed later, so 4th operation times has been determined
                                                    rotate_clockwise_some_times(operation, clock, times, 4); //  rotate the hands several times

                                                    times[5] = (4 - clock[2]) % 4; //   2nd clock ...
                                                    rotate_clockwise_some_times(operation, clock, times, 5);

                                                    times[6] = (4 - clock[3]) % 4; //   3rd clock ...
                                                    rotate_clockwise_some_times(operation, clock, times, 6);

                                                    times[7] = (4 - clock[4]) % 4; //   4th clock ...
                                                    rotate_clockwise_some_times(operation, clock, times, 7);

                                                    times[8] = (4 - clock[6]) % 4; //   6th clock ...
                                                    rotate_clockwise_some_times(operation, clock, times, 8);

                                                    int flag = 1, sum_times = 0; //  flag:   if the serie of operation finally succeeds, then turn to 1, or turn to 0.
                                                                                 //  sum_times:  the sum of times to compare with the mintimes
                                                    for (int i = 0; i < 9; i++)
                                                    {
                                                        sum_times += times[i] % 4; //  calculate the sum of times. if times is 4, that means 0 change
                                                        if (clock[i] != 0)         //  a clock haven't been changed to 0(12 o'clock), so this serie of operation is incorrect.
                                                        {
                                                            flag = 0;
                                                            break;
                                                        }
                                                    }
                                                    if (flag) // the serie of operation succeed
                                                    {
                                                        if ((sum_times < mintimes) || (mintimes == 0)) // this serie is shorter than former one
                                                        {
                                                            for (int i = 0; i < 9; i++)
                                                            {
                                                                min_operation[i] = times[i] % 4;
                                                                if (min_operation[i] != 0)
                                                                {
                                                                    maxi = i; // to make output easier
                                                                }
                                                            }
                                                        }
                                                    }

                                                    //  4~8 operations return to the original status for the 3rd operation enumeration
                                                    //  4~8 are determined by 3rd, so they shouldn't affect the 3rd operation's change.
                                                    for (int i = 4; i <= 8; i++)
                                                    {
                                                        return_to_origin(operation, clock, times, i);
                                                    }
                                                }
                                                //  2nd operation returns to the original status for the 0, 1st operation enumeration(remove the effect of 2nd operation)
                                                for (int j2 = 1; j2 <= operation[2][0]; j2++)
                                                {
                                                    clock[operation[2][j2]] = (4 + (clock[operation[2][j2]] - times[2]) % 4) % 4;
                                                }
                                            }
                                        }

                                        int k = 0;
                                        for (int i = 0; i < 9; i++)     //  store answers
                                        {
                                            if (min_operation[i] != 0 && i != maxi) // normal output
                                            {
                                                for (int j = 0; j < min_operation[i]; j++)
                                                {
                                                    ans[i0][i1][i2][i3][i4][i5][i6][i7][i8][k] = i + '0';
                                                    ans[i0][i1][i2][i3][i4][i5][i6][i7][i8][k+1] = ' ';
                                                    k += 2;
                                                }
                                            }
                                            else if (i == maxi) //  the last but not 0 operation times
                                            {
                                                for (int j = 0; j < min_operation[i] - 1; j++)
                                                {
                                                    ans[i0][i1][i2][i3][i4][i5][i6][i7][i8][k] = i + '0';
                                                    ans[i0][i1][i2][i3][i4][i5][i6][i7][i8][k+1] = ' ';
                                                    k += 2;
                                                }
                                                ans[i0][i1][i2][i3][i4][i5][i6][i7][i8][k] = i + '0';
                                                ans[i0][i1][i2][i3][i4][i5][i6][i7][i8][k+1] = '\0';    //  no space at the end of output line
                                                k += 2;
                                            }
                                        }
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int input[9] = {0}; // the input clock status
    do
    {
        for (int i = 0; i < 9; i++)
        {
            if ((scanf("%d", &input[i])) == EOF)  // the file end is input
                return 0;
            input[i] = (input[i] / 3) % 4;  // change 3, 6, 9, 12 => 1, 2, 3, 0
        }
        
        //  answer the question
        printf("%s\n", ans[input[0]][input[1]][input[2]][input[3]][input[4]][input[5]][input[6]][input[7]][input[8]]);
    }while (getchar() != EOF);
    return 0;
}

void rotate_clockwise_some_times(const int operation[9][10], int clock[9], int times[9], int which_operation)
{
    for (int i = 1; i <= operation[which_operation][0]; i++)
    {
        clock[operation[which_operation][i]] = (clock[operation[which_operation][i]] + times[which_operation]) % 4; //  specific clocks will be changed seceral times
    }
}

void return_to_origin(const int operation[9][10], int clock[9], int times[9], int which_operation)
{
    for (int i = 1; i <= operation[which_operation][0]; i++)
    {
        clock[operation[which_operation][i]] = (4 + (clock[operation[which_operation][i]] - times[which_operation]) % 4) % 4; // "4 + " removes the effect of minus number and ensures the result will be positive
    }
}
