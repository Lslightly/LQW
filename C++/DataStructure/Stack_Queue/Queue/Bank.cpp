#include "Queue.h"
#include <random>
#include <stdio.h>

typedef struct Event
{
    int OccurTime;
    int Ntype;
    Customer cus;
} Event;

LinkList<Event> EventList = LinkList<Event>();

typedef struct Bank
{
    int total_money;
    int closetime;
    int total_time;
    int pre_money;
    int intertime_max;
    int duration_max;
    int amount_max;
    int total_person;
} Bank;

Bank bank = {0, 0, 0, 0, 10, 30, 10000, 0};

void OpenForDay(void); //  开张

void CustomerArrive(LNode<Event> *e, Queue<Customer> &q1, Queue<Customer> &q2); //  顾客到达

void CustomerDepature(LNode<Event> *e, Queue<Customer> &q1, Queue<Customer> &q2); //  顾客离开

int cmp(Event a, Event b); //  a先发生，返回0，b先发生，返回1

int check(Queue<Customer> &q2, int time); //  检查q2列,若可借钱，返回借钱结束后的时间，time为check开始的时间

int main(void)
{
    scanf("%d%d", &bank.total_money, &bank.closetime);
    bank.pre_money = bank.total_money;

    Queue<Customer> q1 = Queue<Customer>();
    Queue<Customer> q2 = Queue<Customer>();
    OpenForDay();
    while (!EventList.ListEmpty())
    {
        LNode<Event> *p = EventList.DelFirst();
        if (p->data.Ntype == 0)
        {
            CustomerArrive(p, q1, q2);
        }
        else
        {
            CustomerDepature(p, q1, q2);
        }
    }

    int q1_len = q1.QueueLength(), q2_len = q2.QueueLength();
    Customer temp;
    if (q1_len != 0)
    {
        for (int i = 0; i < q1_len; i++)
        {
            q1.DeQueue(temp);
            bank.total_time += bank.closetime - temp.arrival_time;
        }
    }
    if (q2_len != 0)
    {
        for (int i = 0; i < q2_len; i++)
        {
            q2.DeQueue(temp);
            bank.total_time += bank.closetime - temp.arrival_time;
        }
    }
    printf("%lf\n", bank.total_time * 1.0 / bank.total_person);
    return 0;
}

void OpenForDay(void)
{
    Event p;
    p.cus.amount = bank.amount_max- rand() % (2 * bank.amount_max);
    p.cus.arrival_time = rand() % bank.intertime_max;
    p.cus.duration = rand() % bank.duration_max;
    p.Ntype = 0;
    p.OccurTime = p.cus.arrival_time;

    LNode<Event> *e = new LNode<Event>;
    *e = LNode<Event>(p);
    EventList.InsFirst(e);
}

void CustomerArrive(LNode<Event> *e, Queue<Customer> &q1, Queue<Customer> &q2)
{
    bank.total_person++;
    Event next_arrive = {
        0,
        0,
        {rand() % bank.intertime_max + e->data.OccurTime, bank.amount_max - rand() % (2 * bank.amount_max), rand() % bank.duration_max}};
    next_arrive.OccurTime = next_arrive.cus.arrival_time;
    LNode<Event> *node_next_arrive = new LNode<Event>;
    if (next_arrive.OccurTime < bank.closetime)
    {
        *node_next_arrive = LNode<Event>(next_arrive);
        EventList.InsBefore(EventList.LocateElem(next_arrive, cmp), node_next_arrive);
    }

    if (q1.QueueEmpty())
    {
        if (e->data.cus.amount + bank.total_money >= 0) //  q1队伍是空的而且这个人金额加上银行金额大于等于0
        {
            Event leave = {
                e->data.cus.arrival_time + e->data.cus.duration,
                1,
                e->data.cus};
            LNode<Event> *node_leave = new LNode<Event>;
            *node_leave = LNode<Event>(leave);
            EventList.InsBefore(EventList.LocateElem(leave, cmp), node_leave);
            q1.EnQueue(e->data.cus);
        }
        else    //  银行支付不了
        {
            q2.EnQueue(e->data.cus);
        }
    }
    else
    {
        q1.EnQueue(e->data.cus);
    }
}

void CustomerDepature(LNode<Event> *e, Queue<Customer> &q1, Queue<Customer> &q2)
{
    if (e->data.cus.amount > 0)
        bank.pre_money = bank.total_money;
    bank.total_money += e->data.cus.amount;
    bank.total_time += e->data.OccurTime - e->data.cus.arrival_time;

    Customer temp = {0};
    if (e->data.Ntype == 1)
        q1.DeQueue(temp);
    else if (e->data.Ntype == 2)
        q2.DeQueue(temp);

    int q2_len = q2.QueueLength();
    int time = e->data.OccurTime;
    for (int i = 0; i < q2_len; i++)
    {
        time = check(q2, time);
        if (bank.total_money < bank.pre_money)
            break;
    }

    if (!q1.QueueEmpty())
    {
        Customer q1_head;
        q1.GetHead(q1_head);
        if (q1_head.amount > 0)
        {
            Event next_leave = {
                time + q1_head.duration,
                1,
                q1_head};
            LNode<Event> *p = new LNode<Event>;
            *p = LNode<Event>(next_leave);
            EventList.InsBefore(EventList.LocateElem(next_leave, cmp), p);
        }
        else if (q1_head.amount < 0)
        {
            if (q1_head.amount + bank.total_money < 0)
            {
                q2.EnQueue(q1_head);
            }
            else
            {
                Event next_leave = {
                    time + q1_head.duration,
                    1,
                    q1_head};
                LNode<Event> *p = new LNode<Event>;
                *p = LNode<Event>(next_leave);
                EventList.InsBefore(EventList.LocateElem(next_leave, cmp), p);
            }
        }
    }
}

int cmp(Event a, Event b)
{
    return (a.OccurTime - b.OccurTime <= 0) ? 0 : 1;
}

int check(Queue<Customer> &q2, int time)
{
    Customer cus;
    q2.DeQueue(cus);
    if (cus.amount + bank.total_money >= 0)
    {
        time += cus.duration;
        bank.total_money += cus.amount;
        bank.total_time += time - cus.arrival_time;
    }
    else
    {
        q2.EnQueue(cus);
    }
    return time;
}