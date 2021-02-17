// id: PB19111682

//  brief description:  RCR command. Judge whether a 16-bit integer x could be changed to
//                      a 16-bit integer y in the following way:
//  origin:             x = ****010 c = 1
//  one change:         x = 1****01 c = 0

#include <stdio.h>


//  Introduction:   execute the RCR operation 17 times and judge whether the situation where x
//                  is equal to y exists.
//  Parameters:     x:16 Bit positive int, the number shifted right
//                  y:16 Bit positive int, the target number
//                  c: 0 or 1, shifted to the highest bit of x
//  Return:         "YES\n" will be printed, if x is able to be equal to y after several times
//                  of RCR operation.
//                  "NO\n" will be printed, if no possibilities exist.
void Judge(int x, int y, int c);  

int main(void)
{
    int tot;                        //  the total number of groups of the input data
    int x, y, c;                    //  x: 16 Bit positive int to be shifted right; 
                                    //  y: 16 Bit positive int, the standard; 
                                    //  c: 0 or 1, to be shifted to the highest bit of x

    scanf("%d", &tot);              //  get the total number of input groups
    for (int i = 0; i < tot; i++)   //  get each group and judge
    {
        scanf("%d%d%d", &x, &y, &c);
        Judge(x, y, c);
    }
    return 0;
}

void Judge(int x, int y, int c)
{
    int temp;                       //  memorize the last bit of x
    for (int i = 0; i < 17; i++)    //  17 times RCR exectued
    {
        temp = x % 2;      
        x >>= 1;                    //  x shifted right
        x += c * 32768;             //  put c to the highest bit of x
        c = temp;                   //  set c to temp for next RCR
        if (x == y)                 //  x equal to y, print "YES\n" and exit the function
        {
            printf("YES\n");
            return ;                //  exit the function
        }
    }
    printf("NO\n");                 //  no possibilities exist
    return ;
}
