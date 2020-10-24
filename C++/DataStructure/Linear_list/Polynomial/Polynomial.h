#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_
#include "../LinkList/LinkList.h"
#include <math.h>
#include <stdio.h>
typedef struct Item //  项
{
    double coef; //  系数
    int expn;    //  指数
} Item;

void clean_input_tail(void);

class Polynomial : public LinkList<Item>   //  继承Item链表
{
public:
    Polynomial(void);                                 //  初始化
    Polynomial(const Polynomial &a);                  //  复制构造函数
    void PrintPolyn();                                //  优化方式打印多项式
    void PrintPolyn_basic();                          //  基础打印
    int PolynLength();                                //  求多项式项数
    Polynomial operator+(const Polynomial &b);        //  两个多项式做加法
    Polynomial operator-(const Polynomial &b);        //  两个多项式做减法
    friend Polynomial operator-(const Polynomial &b); //  多项式取反
    Polynomial operator*(const Polynomial &b);        //  两个多项式做乘法
    Polynomial operator=(const Polynomial &b);        //  赋值
    Polynomial derivate(int n);                       //  n阶导
    LNode<Item> *ListInsert(LNode<Item> e);           //  复制新的e插入，返回插入的指针
    void Input(void);                                 //  输入多项式
    double calculate(double x);                       //  代x计算
};

Polynomial::Polynomial()
{
    head = new LNode<Item>;
    head->next = nullptr;
    len = 0;
    tail = head;
}

Polynomial::Polynomial(const Polynomial &b)
{
    head = new LNode<Item>;
    head->next = nullptr;
    LNode<Item> *pa = head;
    LNode<Item> *pb = b.head->next;
    while (pb != nullptr)
    {
        LNode<Item> *s = new LNode<Item>;
        s->data.coef = pb->data.coef;
        s->data.expn = pb->data.expn;
        s->next = nullptr;
        pa->next = s;
        pa = s;
        pb = pb->next;
    }
}


void Polynomial::PrintPolyn()
{
    PolynLength();
    if (len == 0)   //  0
    {
        printf("1 items, ");
        printf("0\n");
        return;
    }

    printf("%d items, ", len);
    LNode<Item> *p = head->next;
    while (p != nullptr)
    {
        if (p->data.coef > 0 && p != head->next)    //  不是第一项，正数
        {
            if (fabs(p->data.coef - 1) < 0.0001)    //  系数为1
            {
                if (p->data.expn == 1)  //  +x
                    printf("+x");
                else if (p->data.expn == 0) //  +1
                    printf("+1");
                else
                    printf("+x^%d", p->data.expn);  //  +x^expn
            }
            else if (fabs(p->data.coef - int(p->data.coef)) < 0.0001)   // 正整数
            {
                if (p->data.expn == 1)  //  +cx
                    printf("+%dx", int(p->data.coef));
                else if (p->data.expn == 0) //  +c
                    printf("+%d", int(p->data.coef));
                else    //  +cx^expn
                    printf("+%dx^%d", int(p->data.coef), p->data.expn);
            }
            else    // 正小数
            {
                if (p->data.expn == 0)  // +2.33333
                    printf("+%.2lf", p->data.coef);
                else if (p->data.expn == 1) //  +2.33333x
                    printf("+%.2lfx", p->data.coef);
                else    // +2.33333x^expn
                    printf("+%.2lfx^%d", p->data.coef, p->data.expn);
            }
        }
        else if (p->data.coef < 0)  //  负数
        {
            if (fabs(p->data.coef + 1) < 0.0001)    //  -1
                if (p->data.expn == 1)  //  -x
                    printf("-x");
                else if (p->data.expn == 0) //  -1
                    printf("-1");
                else    //  -x^expn
                    printf("-x^%d", p->data.expn);
            else if (fabs(p->data.coef - int(p->data.coef)) < 0.0001)   //  负整数
                if (p->data.expn == 1)  //  -2x
                    printf("%dx", int(p->data.coef));
                else if (p->data.expn == 0) //  -2
                    printf("%d", int(p->data.coef));
                else    //  -2x^expn
                    printf("%dx^%d", int(p->data.coef), p->data.expn);
            else    //  负小数
            {
                if (p->data.expn == 1)  //  -2.333x
                    printf("%.2lfx", p->data.coef);
                else if (p->data.expn == 0) //  -2.333
                    printf("%.2lf", p->data.coef);
                else    // -2.333x^expn
                    printf("%.2lfx^%d", p->data.coef, p->data.expn);
            }
        }
        else    //  正数，还是首项，不能显示正号
        {
            if (fabs(p->data.coef - 1) < 0.0001)    // 1
            {
                if (p->data.expn == 1)  //x
                    printf("x");
                else if (p->data.expn == 0) //1
                    printf("1");
                else
                    printf("x^%d", p->data.expn);   // x^expn
            }
            else if (fabs(p->data.coef - int(p->data.coef)) < 0.0001)   //  正整数
                if (p->data.expn == 1)  //  cx
                    printf("%dx", int(p->data.coef));
                else if (p->data.expn == 0) //c
                    printf("%d", int(p->data.coef));
                else    // cx^expn
                    printf("%dx^%d", int(p->data.coef), p->data.expn);
            else    //  小数
            {
                if (p->data.expn == 0)
                    printf("%.2lf", p->data.coef);
                else if (p->data.expn == 1)
                    printf("%.2lfx", p->data.coef);
                else
                    printf("%.2lfx^%d", p->data.coef, p->data.expn);
            }
        }
        p = p->next;
    }
    putchar('\n');
}

int Polynomial::PolynLength()
{
    LNode<Item> *p = head;
    int i = 0;
    while (p->next != nullptr)
    {
        ++i;
        p = p->next;
    }
    len = i;
    return len;
}

Polynomial Polynomial::operator+(const Polynomial &b)
{
    LNode<Item> *pa = head->next;
    LNode<Item> *pb = b.head->next;
    Polynomial c;   //  创建新的链表
    while (pa != nullptr && pb != nullptr)  //  遍历两个链表
    {
        if (pa->data.expn > pb->data.expn)  //  pa指数更大，插入c
        {
            c.ListInsert(*pa);  //  这里可以防止pa中的系数为0的项插入到c中
            pa = pa->next;
        }
        else if (pa->data.expn < pb->data.expn)
        {
            c.ListInsert(*pb);
            pb = pb->next;
        }
        else    //  pa，pb指数相同
        {
            LNode<Item> temp;
            temp.data.coef = pa->data.coef + pb->data.coef;
            temp.data.expn = pa->data.expn;
            c.ListInsert(temp);
            pa = pa->next;
            pb = pb->next;
        }
    }
    if (pb != nullptr)  //  pb未完全部插入
    {
        while (pb != nullptr)
        {
            LNode<Item> *temp = pb;
            c.ListInsert(*pb);
            pb = pb->next;
        }
    }
    if (pa != nullptr)
    {
        while (pa != nullptr)
        {
            LNode<Item> *temp = pa;
            c.ListInsert(*pa);
            pa = pa->next;
        }
    }
    return c;
}

int cmp_expn_larger(const Item a, const Item b)
{
    return a.expn <= b.expn;
}

LNode<Item> *Polynomial::ListInsert(LNode<Item> e)
{
    if (fabs(e.data.coef) < 0.00001)    //  如果e的系数为0，则不插入
        return nullptr;
    LNode<Item> *p = nullptr;
    LNode<Item> *insert = new LNode<Item>;
    insert->data.coef = e.data.coef;
    insert->data.expn = e.data.expn;    //  new一块空间，防止被自动清理内存
    p = LocateElem(e.data, cmp_expn_larger);    //  通过LinkList的LocateElem方法找到合适的位置插入
    if (p != nullptr)   //  表示p指数小于等于e的指数
    {
        if (p->data.expn == e.data.expn)    //  表示p指数等于e的指数
        {
            delete insert;  //  及时释放insert，因为没用
            p->data.coef += e.data.coef;    //  加入系数
            return p;
        }
    }
    LNode<Item> *p_pripr = PriorPos(p); //  找到p应该插入位置的前面一个节点
    LNode<Item> *s = p_pripr->next; //  下面为插入该节点
    p_pripr->next = insert;
    insert->next = s;
    if (insert->next == nullptr)    //  在最后插入要改变tail
        tail = insert;
    len++;
    return insert;
}

int cmp_coef_equal(const Item a, const Item b)
{
    return fabs(a.coef - b.coef) < 0.0001;
}

Polynomial operator-(const Polynomial &b)
{
    Polynomial c; 
    LNode<Item> *p = b.head->next;
    while (p != nullptr)
    {
        Polynomial temp = Polynomial();
        temp.ListInsert(LNode<Item>({-p->data.coef, p->data.expn}));    //  插入系数取反项
        c = c + temp;   //  将temp多项式与c相加
        p = p->next;
    }
    return c;
}

Polynomial Polynomial::operator-(const Polynomial &b)
{
    return (*this) + (-b);
}

Polynomial Polynomial::operator*(const Polynomial &b)
{
    Polynomial c; 
    LNode<Item> *pa = head->next;
    while (pa != nullptr)   //  pa外层遍历
    {
        LNode<Item> *pb = b.head->next;
        while (pb != nullptr)   //  pb内层遍历
        {
            Polynomial temp = Polynomial();
            temp.ListInsert(LNode<Item>({pb->data.coef * pa->data.coef, pa->data.expn + pb->data.expn}));
            c = c + temp;
            pb = pb->next;
        }
        pa = pa->next;
    }
    return c;
}

Polynomial Polynomial::operator=(const Polynomial &b)
{
    head = new LNode<Item>;
    head->next = nullptr;
    LNode<Item> *pa = head;
    LNode<Item> *pb = b.head->next;
    while (pb != nullptr)
    {
        LNode<Item> *s = new LNode<Item>;
        s->data.coef = pb->data.coef;
        s->data.expn = pb->data.expn;
        s->next = nullptr;
        pa->next = s;
        pa = s;
        pb = pb->next;
    }
    return *this;
}

Polynomial Polynomial::derivate(int n)
{
    if (n != 1)
    {
        return this->derivate(n - 1).derivate(1);   //  假设得到了n-1阶导的结果，返回再求一次导，即n阶导的结果
    }

    Polynomial c; 

    LNode<Item> *p = head->next;
    while (p != nullptr)
    {
        Polynomial temp = Polynomial();
        temp.ListInsert(LNode<Item>({p->data.coef * p->data.expn, p->data.expn - 1}));  //  多项式求导公式
        c = c + temp;
        p = p->next;
    }
    return c;
}

double Polynomial::calculate(double x)
{
    double sum = 0, temp = 1;

    LNode<Item> *p = head->next;
    while (p != nullptr)
    {
        temp = 1;
        for (int i = 0; i < p->data.expn; i++)
        {
            temp *= x;
        }
        sum += temp * p->data.coef;
        p = p->next;
    }
    return sum;
}

void Polynomial::Input(void)
{
    printf("Enter the number of items:\n");
    int n_in = 0;
    scanf("%d", &n_in);

    printf("Enter coefs and expns:\n");
    for (int i = 0; i < n_in; i++)
    {
        double coef_in = 0;
        int expn_in = 0;
        scanf("%lf%d", &coef_in, &expn_in);
        Polynomial b = Polynomial();
        b.ListInsert(LNode<Item>({coef_in, expn_in}));  //  将项插入b作为一个多项式进行运算
        *this = *this + b;  //  将b加到*this上可以去b中的0
    }
}

void Polynomial::PrintPolyn_basic()
{
    PolynLength();
    if (len == 0)
    {
        printf("1 0 0\n");
        return;
    }
    printf("%d ", len);
    LNode<Item> *p = head->next;
    while (p != nullptr)
    {
        printf("%lf %d ", p->data.coef, p->data.expn);
        p = p->next;
    }
    putchar('\n');
}
#endif
