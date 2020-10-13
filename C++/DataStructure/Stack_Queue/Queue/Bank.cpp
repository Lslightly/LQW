#include <stdio.h>
#include <random>
#include "Queue.h"

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
}Bank;

typedef struct Customer
{
    int arrival_time;
    int amount;
    int duration;
}Customer;

Bank bank = {0, 0, 0, 0, 10, 8, 6000};

void OpenForDay(void);  //  开张

void CustomerArrive(LNode<Event> * e, Queue<Customer> & q1, Queue<Customer> & q2);  //  顾客到达

void CustomerDepature(LNode<Event> *e, Queue<Customer> & q1, Queue<Customer> & q2);    //  顾客离开

int main(void)
{
    scanf("%d%d", &bank.total_money, &bank.closetime);
    bank.pre_money = bank.total_money;

    Queue<Customer> q1 = Queue<Customer>();
    Queue<Customer> q2 = Queue<Customer>();
    OpenForDay();
    while (!EventList.ListEmpty())
    {
        LNode<Event> * p = EventList.GetHead();
        if (p->data.Ntype == 0)
        {
            CustomerArrive(p, q1, q2);
        }
        else
        {
            CustomerDepature(p, q1, q2);
        }
    }
    return 0;
}

void OpenForDay(void)
{
    Customer p;
    p.amount = rand() % (2*bank.amount_max)-bank.amount_max;
    p.arrival_time = rand()%bank.intertime_max;
    p.duration = rand()%bank.duration_max;
    
    LNode<Event> * e = new LNode<Event>;
    e->data.Ntype = 0;
    e->data.OccurTime = p.arrival_time;
    e->data.cus = p;
    EventList.InsFirst(e);
}

void CustomerArrive(LNode<Event> *e, Queue<Customer> & q1, Queue<Customer> & q2)
{
    if (e->data.cus.amount > 0)
    {
        if (q1.QueueEmpty())
        {
            q1.EnQueue(e->data.cus);
            EventList.InsBefore()
        }
    }
}