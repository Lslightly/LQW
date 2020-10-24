#include "Polynomial.h"
#include <stdio.h>

const int SIZE = 100;

static int num_polyn = 0;

void input_ch(Polynomial **polys);

void menu(void);

void display(Polynomial **polys);

void display_all(Polynomial **polys);

void create(Polynomial **polys);

void add(Polynomial **polys);

void subtract(Polynomial **polys);

void multiply(Polynomial **polys);

void derivate(Polynomial **polys);

void calculate(Polynomial **polys);

void delete_my(Polynomial **polys);

void delete_all(Polynomial **polys);

void display_basic(Polynomial **polys);

bool is_num_0(void); //  检查个数是否为0

int input_ni(void); //  输入对第几个多项式进行操作，一定要合法，返回ni-1

int main(void)
{
    menu();
    Polynomial *polyns[100] = {nullptr};
    input_ch(polyns);
    return 0;
}

void input_ch(Polynomial **polys)
{
    int order = 0;
    bool quit_flag = false;
    int input_i1 = 0, input_i2 = 0;
    while (scanf("%d", &order) == 1)
    {
        switch (order)  //  命令判断
        {
        case 1:
            menu();
            break;
        case 2:
            create(polys);
            break;
        case 3:
            if (is_num_0()) //  如果多项式数量为0则不能进行运算
                break;
            display(polys);
            break;
        case 4:
            if (is_num_0())
                break;
            display_all(polys);
            break;
        case 5:
            if (is_num_0())
                break;
            add(polys);
            break;
        case 6:
            if (is_num_0())
                break;
            subtract(polys);
            break;
        case 8:
            if (is_num_0())
                break;
            multiply(polys);
            break;
        case 9:
            if (is_num_0())
                break;
            derivate(polys);
            break;
        case 10:
            if (is_num_0())
                break;
            calculate(polys);
            break;
        case 7:
            if (is_num_0())
                break;
            delete_my(polys);
            break;
        case 11:
            if (is_num_0())
                break;
            delete_all(polys);
            break;
        case 12:
            if (is_num_0())
                break;
            display_basic(polys);
            break;
        default:
            quit_flag = true;   //  不是上述情况，退出
            break;
        }
        getchar();
        if (quit_flag)
            break;
    }
    delete_all(polys);
}

void menu(void)
{
    printf("**********OPERATIONS***********\n\
*****1.   menu            *****\n\
*****2.   create          *****\n\
*****3.   display         *****\n\
*****4.   display all     *****\n\
*****5.   add             *****\n\
*****6.   subtract        *****\n\
*****7.   delete          *****\n\
*****8.   multiply        *****\n\
*****9.   derivate        *****\n\
*****10.  calculate       *****\n\
*****11.  delete all      *****\n\
*****12.  display(basic)  *****\n\
**********OPERATIONS***********\n");
}

void display(Polynomial **polys)
{
    int ni = 0;
    ni = input_ni();
    polys[ni]->PrintPolyn();
}

void display_all(Polynomial **polys)
{
    for (int i = 0; i < num_polyn; i++)
    {
        printf("Poly%d: ", i+1);
        polys[i]->PrintPolyn();
    }
}

void create(Polynomial **polys)
{
    polys[num_polyn] = new Polynomial();
    polys[num_polyn]->Input();
    num_polyn++;
}

void add(Polynomial **polys)
{
    int input_i1 = 0, input_i2 = 0;
    input_i1 = input_ni();
    input_i2 = input_ni();
    polys[num_polyn] = new Polynomial();
    *polys[num_polyn] = (*polys[input_i1]) + (*polys[input_i2]);
    num_polyn++;
    (*polys[num_polyn - 1]).PrintPolyn();
}

void subtract(Polynomial **polys)
{
    int input_i1 = 0, input_i2 = 0;
    input_i1 = input_ni();
    input_i2 = input_ni();
    polys[num_polyn] = new Polynomial();
    *polys[num_polyn] = (*polys[input_i1]) - (*polys[input_i2]);
    num_polyn++;
    (*polys[num_polyn - 1]).PrintPolyn();
}

void multiply(Polynomial **polys)
{
    int input_i1 = 0, input_i2 = 0;
    input_i1 = input_ni();
    input_i2 = input_ni();
    polys[num_polyn] = new Polynomial();
    *polys[num_polyn] = (*polys[input_i1]) * (*polys[input_i2]);
    num_polyn++;
    (*polys[num_polyn - 1]).PrintPolyn();
}

void derivate(Polynomial **polys)
{
    int ni = 0;
    ni = input_ni();

    int times = 0;
    printf("Please input times you want to derivate:");
    while (scanf("%d", &times) == 0 || times <= 0)
    {
        printf("\nPlease input positive integer:");
    }
    polys[num_polyn] = new Polynomial();
    *polys[num_polyn] = polys[ni]->derivate(times);
    num_polyn++;
    (*polys[num_polyn - 1]).PrintPolyn();
}

void calculate(Polynomial **polys)
{
    double x = 0;
    int ni = 0;
    ni = input_ni();

    printf("Please input x:");
    scanf("%lf", &x);

    polys[ni]->PrintPolyn();
    printf("%lf\n", polys[ni]->calculate(x));
}

void delete_my(Polynomial **polys)
{
    int ni = 0;
    ni = input_ni();

    delete polys[ni];
    for (int i = ni; i < num_polyn - 1; i++)
    {
        polys[i] = polys[i + 1];
    }
    num_polyn--;
}

void delete_all(Polynomial **polys)
{
    for (int i = 0; i < num_polyn; i++)
    {
        delete polys[i];
    }
    num_polyn = 0;
}

int input_ni(void)
{
    int ni = 0;
    printf("Please input which polynomial you want to operate:");
    while (scanf("%d", &ni) == 0 || !(ni >= 1 && ni <= num_polyn))
    {
        printf("\nPlease input integer from %d to %d:", 1, num_polyn);
    }
    return ni - 1;
}

bool is_num_0(void)
{
    if (num_polyn == 0)
    {
        printf("Please create new polynomials\n");
        return true;
    }
    return false;
}

void display_basic(Polynomial **polys)
{
    int ni = 0;
    ni = input_ni();
    polys[ni]->PrintPolyn_basic();
}
