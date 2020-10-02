#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_
#include "../LinkList/LinkList.h"
#include <math.h>
#include <stdio.h>
typedef struct Item
{
    double coef;
    int expn;
} Item;

class Polynomial : LinkList<Item>
{
private:
    int n;
public:
    Polynomial(void);
    // ~Polynomial();
    Polynomial(const Polynomial &a);                  //  复制构造函数
    void PrintPolyn();                                //  打印多项式
    int PolynLength();                                //  求最高次
    Polynomial operator+(const Polynomial &b);        //  两个多项式做加法
    Polynomial operator-(const Polynomial &b);        //  两个多项式做减法
    friend Polynomial operator-(const Polynomial &b); //  多项式取反
    Polynomial operator*(const Polynomial &b);        //  两个多项式做乘法
    Polynomial operator=(const Polynomial &b);        //  赋值
    Polynomial derivate(int n);                       //  n阶导
    LNode<Item> *ListInsert(LNode<Item> e);           //  复制新的e插入，返回插入的指针
    LNode<Item> *ListDelete(LNode<Item> e);           //  返回删除那个节点的指针
    double calculate(double x);
};

Polynomial::Polynomial()
{
    head = new LNode<Item>;
    head->next = nullptr;
    len = 0;
    tail = head;
}

// Polynomial::Polynomial(double coef, int expn)
// {
//     head = new LNode<Item>;
//     head->next = nullptr;
//     len = 0;
//     n = 0;
//     if (fabs(coef) > 0.0001)
//     {
//         LNode<Item> *p = new LNode<Item>;
//         p->data.coef = coef;
//         p->data.expn = expn;
//         p->next = nullptr;
//         head->next = p;
//         ++len;
//         n = expn;
//     }
//     else if (fabs(coef) < 0.0001 && expn == 0)
//     {
//         LNode<Item> *p = new LNode<Item>;
//         p->data.coef = 0;
//         p->data.expn = expn;
//         p->next = nullptr;
//         head->next = p;
//         ++len;
//         n = expn;
//     }
// }

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

// Polynomial::~Polynomial()
// {
//     LNode<Item> *p = head;
//     LNode<Item> *s = p->next;
//     while (p != nullptr)
//     {
//         s = p->next;
//         delete p;
//         p = s;
//     }
// }

void Polynomial::PrintPolyn()
{
    LNode<Item> *p = head->next;
    while (p != nullptr)
    {
        if (fabs(p->data.coef) < 0.0001 && p->data.expn == 0)
        {
            if (p != head->next)
            {
                p = p->next;
                continue;
            }
            else
            {
                printf("0");
                p = p->next;
                continue;
            }
        }
        if (p->data.coef > 0 && p != head->next)
        {
            if (fabs(p->data.coef - 1) < 0.0001)
            {
                if (p->data.expn == 1)
                    printf("+x");
                else if (p->data.expn == 0)
                    printf("+1");
                else
                    printf("+x^%d", p->data.expn);
            }
            else if (fabs(p->data.coef - int(p->data.coef)) < 0.0001)
            {
                if (p->data.expn == 1)
                    printf("+%dx", int(p->data.coef));
                else if (p->data.expn == 0)
                    printf("+%d", int(p->data.coef));
                else
                    printf("+%dx^%d", int(p->data.coef), p->data.expn);
            }
            else
            {
                if (p->data.expn == 0)
                    printf("+%.2lf", p->data.coef);
                else if (p->data.expn == 1)
                    printf("+%.2lfx", p->data.coef);
                else
                    printf("+%.2lfx^%d", p->data.coef, p->data.expn);
            }
        }
        else if (p->data.coef < 0)
        {
            if (fabs(p->data.coef + 1) < 0.0001)
                if (p->data.expn == 1)
                    printf("-x");
                else if (p->data.expn == 0)
                    printf("-1");
                else
                    printf("-x^%d", p->data.expn);
            else if (fabs(p->data.coef - int(p->data.coef)) < 0.0001)
                if (p->data.expn == 1)
                    printf("%dx", int(p->data.coef));
                else if (p->data.expn == 0)
                    printf("%d", int(p->data.coef));
                else
                    printf("%dx^%d", int(p->data.coef), p->data.expn);
            else
            {
                if (p->data.expn == 1)
                    printf("%.2lfx", p->data.coef);
                else if (p->data.expn == 0)
                    printf("%.2lf", p->data.coef);
                else
                    printf("%.2lfx^%d", p->data.coef, p->data.expn);
            }
        }
        else
        {
            if (fabs(p->data.coef - 1) < 0.0001)
            {
                if (p->data.expn == 1)
                    printf("x");
                else if (p->data.expn == 0)
                    printf("1");
                else
                    printf("x^%d", p->data.expn);
            }
            else if (fabs(p->data.coef - int(p->data.coef)) < 0.0001)
                if (p->data.expn == 1)
                    printf("%dx", int(p->data.coef));
                else if (p->data.expn == 0)
                    printf("%d", int(p->data.coef));
                else
                    printf("%dx^%d", int(p->data.coef), p->data.expn);
            else
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
    Item e = {0, 0};
    LNode<Item> temp = LNode<Item>(e);
    Polynomial c; //= Polynomial();
    c.ListInsert(e);
    while (pa != nullptr && pb != nullptr)
    {
        if (pa->data.expn > pb->data.expn)
        {
            if (fabs(pa->data.coef) > 0.0001)
                c.ListInsert(*pa);
            pa = pa->next;
        }
        else if (pa->data.expn < pb->data.expn)
        {
            if (fabs(pb->data.coef) > 0.0001)
                c.ListInsert(*pb);
            pb = pb->next;
        }
        else
        {
            LNode<Item> *temp = new LNode<Item>;
            temp->data.coef = pa->data.coef + pb->data.coef;
            temp->data.expn = pa->data.expn;
            if (fabs(temp->data.coef) > 0.0001)
                c.ListInsert(*temp);
            delete temp;
            pa = pa->next;
            pb = pb->next;
        }
    }
    if (pb != nullptr)
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
    n = c.head->next->data.expn;
    return c;
}

int cmp_expn_larger(const Item a, const Item b)
{
    return a.expn <= b.expn;
}

LNode<Item> *Polynomial::ListInsert(LNode<Item> e)
{
    LNode<Item> *p = nullptr;
    LNode<Item> *insert = new LNode<Item>;
    insert->data.coef = e.data.coef;
    insert->data.expn = e.data.expn;
    p = LocateElem(e.data, cmp_expn_larger);
    if (p != nullptr)
    {
        if (p->data.expn == e.data.expn)
        {
            p->data.coef += e.data.coef;
            return p;
        }
    }
    LNode<Item> *p_pripr = PriorPos(p);
    LNode<Item> *s = p_pripr->next;
    p_pripr->next = insert;
    insert->next = s;
    if (insert->next == nullptr)
        tail = insert;
    len++;
    return insert;
}

int cmp_coef_equal(const Item a, const Item b)
{
    return fabs(a.coef - b.coef) < 0.0001;
}

LNode<Item> *Polynomial::ListDelete(LNode<Item> e)
{
    // LNode<Item> *p = head;
    // while (p->next != nullptr)
    // {
    //     if (p->next->data.expn != e.data.expn)
    //     {
    //         p = p->next;
    //     }
    //     else
    //         break;
    // }
    // LNode<Item> *s = p->next;
    // p->next = p->next->next;
    // return s;
    LNode<Item> *p = nullptr;
    p = LocateElem(e.data, cmp_coef_equal); //  确定e所在位置结点位置
    LNode<Item> *p_prior = PriorPos(p);     //  p的前面
    p_prior->next = p->next;                //  断开p
    return p;
}

Polynomial operator-(const Polynomial &b)
{
    Polynomial c; //= Polynomial();
    c.ListInsert(LNode<Item>({0, 0}));
    LNode<Item> *p = b.head->next;
    while (p != nullptr)
    {
        Polynomial temp = Polynomial();
        temp.ListInsert(LNode<Item>({-p->data.coef, p->data.expn}));
        c = c + temp;
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
    Polynomial c; //= Polynomial();
    c.ListInsert(LNode<Item>({0, 0}));
    LNode<Item> *pa = head->next;
    while (pa != nullptr)
    {
        LNode<Item> *pb = b.head->next;
        while (pb != nullptr)
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
        return this->derivate(n - 1).derivate(1);
    }

    Polynomial c; //= Polynomial();
    c.ListInsert(LNode<Item>({0, 0}));

    LNode<Item> *p = head->next;
    while (p != nullptr)
    {
        Polynomial temp = Polynomial();
        temp.ListInsert(LNode<Item>({p->data.coef * p->data.expn, p->data.expn - 1}));
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
#endif