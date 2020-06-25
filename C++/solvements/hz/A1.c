#include <stdio.h>
#include <stdlib.h>

unsigned * solve(const unsigned *, int);
void digits(const char *, unsigned *);
unsigned * multiply(const unsigned *, const unsigned *, int);
int decimalPlace(const char *, int);
void output(const unsigned *, int, int);

int main(void) {
    int n, decplace;
    char F[6],  ch;
    unsigned * result, Fdigits[5];
    //n, F as shown in the question
    //decplace is the number of the decimal digits of the answer
    //Fdigits is the digits of F

    while ((ch = getchar()) != EOF) {
        F[0] = ch;
        for (int i = 1; i < 6; i++) 
            F[i] = getchar();
        scanf("%d",&n);
        getchar();

        decplace = decimalPlace(F, n);
        digits(F, Fdigits);
        result = solve(Fdigits, n);
        output(result, decplace, n);
        free(result);
    }

    return 0;
}

/*
 *Description: calculate the corresponding power of the number
 *Parameter:
  @Fdigits: an array to store the digits of F
  @n: as shown in the question
 *Return: the first address of the result(no decimal point)
 */
unsigned * solve(const unsigned * Fdigits, int n) {
    unsigned * result, * nums;

    nums = (unsigned *)malloc(sizeof(Fdigits));
    for (int i = 0; i < 5; i++) nums[i] = Fdigits[i];

    if (n == 1) return nums;
    for (int i = 2; i <= n; i++) {
        result = multiply(nums, Fdigits, 5 * (i - 1));
        free(nums);
        if (i == n) return result;
        nums = (unsigned *)malloc(5 * i * sizeof(unsigned));
        for (int j = 0; j < 5 * i; j++) nums[j] = result[j];
    }
}

/*
 *Description: get the digits of F
 *Parameter:
  @F: as shown in the question
  @Fdigits: an array to store the digits of F
 */
void digits(const char * F, unsigned * Fdigits) {
    int i, j;
    for (i = j = 0; i < 6; i++, j++) {
        if (F[i] == '.') {
            i++;
            if (i == 6) break;
        }
        Fdigits[j] = F[i] - '0';
    }
}

/*
 *Description: calculate the product of two numbers
 *Parameter:
  @nums: a multiplier
  @Fdigits: the digits of F
  @lnums: the length of nums
 *Return: the first address of the result
 */
unsigned * multiply(const unsigned * nums, const unsigned * Fdigits, int lnums) {
    unsigned * result;
    result = (unsigned *)calloc(lnums + 5, sizeof(unsigned));

    for (int i = 4; i >= 0; i--) {
        for (int j = lnums - 1; j >= 0; j--) {
            result[i + j + 1] += Fdigits[i] * nums[j];
        }
    }
    for (int i = lnums + 4; i > 0; i--) {
        result[i - 1] += result[i] / 10;
        result[i] %= 10;
    }

    return result;
}

/*
 *Descripition: determine the final result decimal places
 *Parameter: F, n as shown in the question
 *Return: the number of decimal places
 */
int decimalPlace(const char * F, int n) {
    int decplace = 0, k = 5; //k is the number of decimal digits of F
    for (int i = 0; i < 6; i++) {
        if (F[i] == '.') break;
        k--;
    }
    for (int i = 1; i <= n; i++)
        decplace += k;
    return decplace;
}

/*
 *Description: output according to the question
 *Parameter:
  @result: the digits of the answer
  @decplace: the number of decimal digits of the answer
 */
void output(const unsigned * result, int decplace, int n) {
    int left = 0, right = 5 * n - 1;
    //left is the starting point of printing; right is the ending point of printing

    for (int i = left; i < n * 5 - decplace; i++) {
        if (result[i]) break;
        left++;
    }
    for (int i = right; i >= n * 5 - decplace; i--) {
        if (result[i]) break;
        right--;
    }
    for (int i = left; i <= right; i++) {
        if (i == n * 5 -decplace) putchar('.');
        putchar(result[i] + '0');
    }
    putchar('\n');
}