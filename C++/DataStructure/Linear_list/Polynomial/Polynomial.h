#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_
#include <math.h>
#include <stdio.h>
typedef struct LNode
{
    double coef;
    int expn;
    LNode *next;
} LNode;

class Polynomial
{
private:
    LNode *head;
    int n;
    int len;

public:
    Polynomial(void);
    Polynomial(double coef, int expn);
    Polynomial(const Polynomial &a);
    ~Polynomial();
    void PrintPolyn();
    int PolynLength();
    Polynomial operator+(const Polynomial &b);
    Polynomial operator-(const Polynomial &b);
    friend Polynomial operator-(const Polynomial &b);
    Polynomial operator*(const Polynomial &b);
    Polynomial &operator=(const Polynomial &b);
    Polynomial derivate(int n);
    LNode *ListInsert(LNode e); //  返回插入的指针
    LNode *ListDelete(LNode e); //  返回删除那个节点的指针
    double calculate(double x);
};

Polynomial::Polynomial()
{
    head = new LNode;
    head->next = nullptr;
    len = 0;

    printf("Enter the number of items:");
    int n_in = 0;
    scanf("%d", &n_in);

    LNode *p = head;
    for (int i = 0; i < n_in; i++)
    {
        double coef_in = 0;
        int expn_in = 0;
        scanf("%lf%d", &coef_in, &expn_in);
        Polynomial b = Polynomial(coef_in, expn_in);
        if (b.head->next != nullptr)
            ListInsert(*(b.head->next));
    }
    if (head->next != nullptr)
        n = head->next->expn;
    else
    {
        LNode * p = new LNode;
        p->next = nullptr;
        p->expn = 0;
        p->coef = 0;
        head->next = p;
        n = 0;
    }
}

Polynomial::Polynomial(double coef, int expn)
{
    head = new LNode;
    head->next = nullptr;
    len = 0;
    n = 0;
    if (fabs(coef) > 0.0001)
    {
        LNode *p = new LNode;
        p->coef = coef;
        p->expn = expn;
        p->next = nullptr;
        head->next = p;
        ++len;
        n = expn;
    }
    else if (fabs(coef) < 0.0001 && expn == 0)
    {
        LNode *p = new LNode;
        p->coef = 0;
        p->expn = expn;
        p->next = nullptr;
        head->next = p;
        ++len;
        n = expn;
    }
}

Polynomial::Polynomial(const Polynomial &b)
{
    head = new LNode;
    head->next = nullptr;
    LNode *pa = head;
    LNode *pb = b.head->next;
    while (pb != nullptr)
    {
        LNode *s = new LNode;
        s->coef = pb->coef;
        s->expn = pb->expn;
        s->next = nullptr;
        pa->next = s;
        pa = s;
        pb = pb->next;
    }
}

Polynomial::~Polynomial()
{
    LNode *p = head;
    LNode *s = p->next;
    while (p != nullptr)
    {
        s = p->next;
        delete p;
        p = s;
    }
}

void Polynomial::PrintPolyn()
{
    LNode *p = head->next;
    while (p != nullptr)
    {
        if (fabs(p->coef) < 0.0001 && p->expn == 0)
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
        if (p->coef > 0 && p != head->next)
        {
            if (fabs(p->coef - 1) < 0.0001)
            {
                if (p->expn == 1)
                    printf("+x");
                else if (p->expn == 0)
                    printf("+1");
                else
                    printf("+x^%d", p->expn);
            }
            else if (fabs(p->coef - int(p->coef)) < 0.0001)
            {
                if (p->expn == 1)
                    printf("+%dx", int(p->coef));
                else if (p->expn == 0)
                    printf("+%d", int(p->coef));
                else
                    printf("+%dx^%d", int(p->coef), p->expn);
            }
            else
            {
                if (p->expn == 0)
                    printf("+%.2lf", p->coef);
                else if (p->expn == 1)
                    printf("+%.2lfx", p->coef);
                else
                    printf("+%.2lfx^%d", p->coef, p->expn);
            }
        }
        else if (p->coef < 0)
        {
            if (fabs(p->coef + 1) < 0.0001)
                if (p->expn == 1)
                    printf("-x");
                else if (p->expn == 0)
                    printf("-1");
                else
                    printf("-x^%d", p->expn);
            else if (fabs(p->coef - int(p->coef)) < 0.0001)
                if (p->expn == 1)
                    printf("%dx", int(p->coef));
                else if (p->expn == 0)
                    printf("%d", int(p->coef));
                else
                    printf("%dx^%d", int(p->coef), p->expn);
            else
            {
                if (p->expn == 1)
                    printf("%.2lfx", p->coef);
                else if (p->expn == 0)
                    printf("%.2lf", p->coef);
                else
                    printf("%.2lfx^%d", p->coef, p->expn);
            }
        }
        else
        {
            if (fabs(p->coef - 1) < 0.0001)
            {
                if (p->expn == 1)
                    printf("x");
                else if (p->expn == 0)
                    printf("1");
                else
                    printf("x^%d", p->expn);
            }
            else if (fabs(p->coef - int(p->coef)) < 0.0001)
                if (p->expn == 1)
                    printf("%dx", int(p->coef));
                else if (p->expn == 0)
                    printf("%d", int(p->coef));
                else
                    printf("%dx^%d", int(p->coef), p->expn);
            else
            {
                if (p->expn == 0)
                    printf("%.2lf", p->coef);
                else if (p->expn == 1)
                    printf("%.2lfx", p->coef);
                else
                    printf("%.2lfx^%d", p->coef, p->expn);
            }
        }
        p = p->next;
    }
    putchar('\n');
}

int Polynomial::PolynLength()
{
    LNode *p = head;
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
    LNode *pa = head->next;
    LNode *pb = b.head->next;
    Polynomial c = Polynomial(0, 0);
    while (pa != nullptr && pb != nullptr)
    {
        if (pa->expn > pb->expn)
        {
            c.ListInsert(*pa);
            pa = pa->next;
        }
        else if (pa->expn < pb->expn)
        {
            c.ListInsert(*pb);
            pb = pb->next;
        }
        else
        {
            LNode *temp = new LNode;
            temp->coef = pa->coef + pb->coef;
            temp->expn = pa->expn;
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
            LNode *temp = pb;
            c.ListInsert(*pb);
            pb = pb->next;
        }
    }
    if (pa != nullptr)
    {
        while (pa != nullptr)
        {
            LNode *temp = pa;
            c.ListInsert(*pa);
            pa = pa->next;
        }
    }
    n = c.head->next->expn;
    return c;
}

LNode *Polynomial::ListInsert(LNode e)
{
    LNode *p = head;
    LNode *insert = new LNode;
    insert->coef = e.coef;
    insert->expn = e.expn;
    while (p->next != nullptr)
    {
        if (p->next->expn > e.expn)
            p = p->next;
        else
            break;
    }
    if (p->next != nullptr)
    {
        if (p->next->expn == e.expn)
        {
            p->next->coef += e.coef;
            return p->next;
        }
    }
    LNode *s = p->next;
    p->next = insert;
    insert->next = s;
    len++;
    return insert;
}

LNode *Polynomial::ListDelete(LNode e)
{
    LNode *p = head;
    while (p->next != nullptr)
    {
        if (p->next->expn != e.expn)
        {
            p = p->next;
        }
        else
            break;
    }
    LNode *s = p->next;
    p->next = p->next->next;
    return s;
}

Polynomial operator-(const Polynomial &b)
{
    Polynomial c = Polynomial(0, 0);
    LNode *p = b.head->next;
    while (p != nullptr)
    {
        Polynomial temp = Polynomial(-p->coef, p->expn);
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
    Polynomial c = Polynomial(0, 0);
    LNode *pa = head->next;
    while (pa != nullptr)
    {
        LNode *pb = b.head->next;
        while (pb != nullptr)
        {
            Polynomial temp = Polynomial(pa->coef * pb->coef, pa->expn + pb->expn);
            c = c + temp;
            pb = pb->next;
        }
        pa = pa->next;
    }
    return c;
}

Polynomial &Polynomial::operator=(const Polynomial &b)
{
    head = new LNode;
    head->next = nullptr;
    LNode *pa = head;
    LNode *pb = b.head->next;
    while (pb != nullptr)
    {
        LNode *s = new LNode;
        s->coef = pb->coef;
        s->expn = pb->expn;
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

    Polynomial c = Polynomial(0, 0);

    LNode *p = head->next;
    while (p != nullptr)
    {
        Polynomial temp = Polynomial(p->coef * p->expn, p->expn - 1);
        c = c + temp;
        p = p->next;
    }
    return c;
}

double Polynomial::calculate(double x)
{
    double sum = 0, temp = 1;

    LNode *p = head->next;
    while (p != nullptr)
    {
        temp = 1;
        for (int i = 0; i < p->expn; i++)
        {
            temp *= x;
        }
        sum += temp * p->coef;
        p = p->next;
    }
    return sum;
}
#endif