//  High-precision multiplication of floats;
//  Mind:   it's actually the high-precision multiplication of int, but the digits of decimal should be concerned while putting the result
//  Notice! the largest digits of result in this problem won't be larger than 70 as I respect.

#include <stdio.h>
#include <string.h>

// Function:    Clear the zero in the left and right, change the decimal to int and store the int in base
// Parameters:  origin: the original input float stored in a char array
//              Digits_of_decimal:  the digits of decimal, which will increase after the function
//              result: the result after multiplying one time.
//              base:   the multiplicand
//              base_len:   the digits of base
//              result_len: the digits of result
// Return:      zeros in the left and right will be cleared
//              base and result store the valid number
//              base_len and result_len stores the digits of valid number
//              Digits_of_decimal is reduced after clearing zeros in the right of decimal point
void CleartheZero(char * origin, int * Digits_of_decimal, int * result, int * base, int * base_len, int * result_len);

// Function:    do the multiplication operation one time
// Parameters:  result: the result after multiplying one time
//              base:   the multiplicand
//              base_len:   the digits of base
//              result_len: the digits of result
// Return:
//              multiplication operation done one time
//              result updated, result_len updated
void Multiplication(int * result, const int * base, int base_len, int * result_len);

int main(void)
{
    char origin[6] = {""}; // stores the input
    do
    {
        // each loop initializes the value

        int Digits_of_decimal = 0, times = 0, result[70] = {0}, base[5] = {0}, base_len = 5, result_len = 5; 
        // Digits_of_decimal:    the digits of decimal
        // times:   the multiplication operated times
        // base:    the input without decimal point and zero in the left and right, so it only needs 5 sizeof(int)
        // result:  the base^times
        // result_len:  the digits of result
        // base_len:    the digits of base(result_len is equal to base_len at the beginning)

        for (int i = 0; i < 6; i++) 
        {
            origin[i] = getchar();
            if (origin[i] == '.')
            {
                Digits_of_decimal = 5-i; // calculate the digits of decimal while zero in the right still exists
            }
            else if (origin[i] == EOF)  // if the input character is EOF, then the program has to be shut down.(all have been put)
            {
                return 0;
            }
        }

        getchar();  // read ' '
        scanf("%d", &times);

        // change the original input into int to make the multiplication easier and store some important information
        CleartheZero(origin, &Digits_of_decimal, result, base, &base_len, &result_len);

        // the digits of decimal have been changed by the upper function and this sentence will calculate the final digits after several times of multiplication
        Digits_of_decimal *= times;  

        for (int i = 0; i < times-1; i++)   // execute the multiplication several times
        {
            Multiplication(result, base, base_len, &result_len);
        }

        if (Digits_of_decimal >= result_len) // this case is like .01234, the result_len is 4, but the digits of decimal is 5
        {
            putchar('.');
            for (int i = 0; i < Digits_of_decimal - result_len; i++) // make up the output with 0
            {
                putchar('0');
            }
            for (int i = result_len-1; i >= 0; i--) // output the result
            {
                putchar(result[i]+'0');
            }
        }
        else // like 32432.312321
        {
            for (int i = result_len-1; i >= Digits_of_decimal; i--) // output the number before decimal point
            {
                putchar(result[i]+'0');
            }
            if (Digits_of_decimal != 0) // if the input is like "231.",then the decimal point won't be output
                putchar('.');
            for (int i = Digits_of_decimal-1; i>=0; i--) // normal case like "232.234". output the rest
            {
                putchar(result[i]+'0');
            }
        }
        putchar('\n');
    }while (getchar() != EOF);  // read '\n'
    return 0;
}

void CleartheZero(char * origin, int * Digits_of_decimal, int * result, int * base, int * base_len, int * result_len)
{
    int flag = 0, i = 0, rightflag = 1, num = 0; 
    // flag:    the subcript of the first number not equaled to 0, 
    // rightflag:   the value that judges 0 should be stored into base. 1 means no. 0 means yes
    // num:     a changeable subscript, the number of valid number

    // clear zero in the right of decimal point
    for (i = 5; i >=0; i--) 
    {
        if (origin[i] == '0') // each number cleared causes the base_len, result_len, Digits_of_decimal reduced
        {
            (*base_len)--;
            (*result_len)--;
            (*Digits_of_decimal)--;
        }
        else
        {
            break;
        }
    }

    // clear zeros in the left
    i = 0;
    while (origin[i] == '0' || origin[i] == '.') // '.' is ignored
    {
        if (origin[i] == '0') // also the base_len and the result_len will be reduced, but Digits_of_decimal has been determined already
        {
            (*base_len)--;
            (*result_len)--;
        }
        i++;
    }
    flag = i;   // store the first not 0 subscript searching from left

    for (i = 5; i>=flag; i--)   // from the right to the left store the valid number
    {
        if (origin[i] != '.')   // change the decimal to int, so '.' shouldn't be stored
        {
            if (rightflag && origin[i] == '0') // 0 shouldn't be stored
            {
                continue;
            }
            else    // not 0, or 0 is in the middle
            {
                rightflag = 0;
                result[num] = base[num] = origin[i] - '0';
                num++;
            }
        }
        else // all numbers including 0 before '.' should be stored. they are all valid.
        {
            rightflag = 0;  // unfreeze the restriction on 0
        }
    }
}

void Multiplication(int * result, const int * base, int  base_len, int * result_len)
{
    int copy_of_result[70] = {0}; // copy the result because the result will have new values
    for (int i = 0; i < *result_len; i++)
    {
        copy_of_result[i] = result[i];
        result[i] = 0; // set all to zero
    }
    for (int i = 0; i < base_len; i++)
    {
        for (int j = 0; j < *result_len; j++)
        {
            result[i+j] += copy_of_result[j] * base[i]; // every subscript is engaged in the multiplication, just like the way we multiply two number
            result[i+j+1] += result[i+j] / 10; // carry
            result[i+j] %= 10;  // the rest after carrying the number
        }
    }
    for (int i = 69; i >=0; i--)
    {
        if (result[i] != 0)     // search for a nonzero int backward from 69
        {
            (*result_len) = i+1;  // store the digits
            break;
        }
    }
}
