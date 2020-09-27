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
    Polynomial();
    ~Polynomial();
    void PrintPolyn();
    int PolynLength();
    Polynomial &AddPolyn(Polynomial &b);
    void SubtractPolyn(Polynomial &b);
    void MultiplyPolyn(Polynomial &b);
    void Append(double coef, int expn);
    LNode *ListInsert(LNode *e); //  返回插入的指针
    LNode *ListDelete(LNode *e); //  返回删除之后的后面那个节点的指针
};

Polynomial::Polynomial()
{
    head = new LNode;
    head->next = nullptr;
    len = 0;

    printf("Enter the number of items:");
    scanf("%d", &n);

    LNode *p = head;
    for (int i = 0; i < n; i++)
    {
        double coef_in = 0;
        int expn_in = 0;
        scanf("%lf%d", &coef_in, &expn_in);
        Append(coef_in, expn_in);
    }
    n = head->next->expn;
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
        if (p->coef > 0 && p != head->next)
        {
            if (fabs(p->coef - 1) < 0.0001)
            {
                if (p->expn == 1)
                    printf("+x");
                else if (p->expn == 0)
                    printf("+1");
                else
                    printf(" +x^%d", p->expn);
            }
            else
            {
                if (p->expn == 0)
                    printf("+%.2lf", p->coef);
                else
                    printf("+%.2lfx^%d", p->coef, p->expn);
            }
        }
        else if (p->coef < 0)
        {
            if (fabs(p->coef + 1) < 0.0001)
                if (p->expn == 1)
                    printf("-x");
                else
                    printf("-x^%d", p->expn);
            printf("-%.2lfx^%d", p->coef, p->expn);
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
            else
            {
                if (p->expn == 0)
                    printf("%.2lf", p->coef);
                else
                    printf("%.2lfx^%d", p->coef, p->expn);
            }
        }
        p = p->next;
    }
}

int Polynomial::PolynLength()
{
    return len;
}

Polynomial &Polynomial::AddPolyn(Polynomial &b)
{
    LNode *pa = head->next;
    LNode *pa_pre = head;
    LNode *pb = b.head->next;
    while (pa != nullptr && pb != nullptr)
    {
        if (pa->expn > pb->expn)
        {
            pa = pa->next;
        }
        else if (pa->expn < pb->expn)
        {
            LNode *temp = pb->next;
            b.ListDelete(pb);
            this->ListInsert(pb); //  改变pb->next
            pb = temp;
        }
        else
        {
            pa->coef += pb->coef;
            if (fabs(pa->coef) < 0.0001)
            {
                pa = ListDelete(pa);
            }
            pb = pb->next;
        }
    }
    if (pa == nullptr && pb != nullptr)
    {
        while (pb != nullptr)
        {
            LNode *temp = pb->next;
            b.ListDelete(pb);
            ListInsert(pb);
            pb = temp;
        }
    }
    return *this;
}

void Polynomial::Append(double coef, int expn)
{
    if (coef != 0)
    {
        LNode *p_insert = new LNode;
        p_insert->coef = coef;
        p_insert->expn = expn;
        p_insert->next = nullptr;

        LNode *p = head;
        while (p->next != nullptr)
        {
            if (p->next->expn > p_insert->expn)
                p = p->next;
            else
                break;
        }
        LNode *s = p->next;
        p->next = p_insert;
        p_insert->next = s;
        len++;
    }
}

LNode *Polynomial::ListInsert(LNode *e)
{
    LNode *p = head;
    while (p->next != nullptr)
    {
        if (p->next->expn > e->expn)
            p = p->next;
        else
            break;
    }
    LNode *s = p->next;
    p->next = e;
    e->next = s;
    len++;
    return e;
}

LNode *Polynomial::ListDelete(LNode *e)
{
    LNode *p = head;
    while (p->next != nullptr)
    {
        if (p->next->expn != e->expn)
        {
            p = p->next;
        }
        else
            break;
    }
    p->next = e->next;
    delete e;
    return p->next;
}
#endif