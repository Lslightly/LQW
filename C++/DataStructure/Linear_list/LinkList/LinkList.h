#ifndef LINKLIST_H_
#define LINKLIST_H_
template <class Type>
class LNode{
public:
    Type data;
    LNode * next;
};

template <class Type>
class LinkList{
private:
    LNode<Type> * head;
public:
    LinkList();
    ~LinkList();
    void ClearList(void);
    bool ListEmpty(void);
    int ListLength(void);
    bool GetElem(const int i, Type & e);
    int LocateElem(const Type e, bool (* compare)(const Type a, const Type b));
    bool PriorElem(const Type cur_e, Type & pre_e);
    bool NextElem(const Type cur_e, Type & next_e);
    bool ListInsert(int i, const Type e);
    bool ListDelete(const int i, Type & e);
    bool ListTraverse(bool (* visit)(Type & e));
};

template <class Type>
LinkList<Type>::LinkList()
{
    head = new LNode<Type>;
    head->next = nullptr;
}

template <class Type>
LinkList<Type>::~LinkList()
{
    LNode<Type> * p = head;
    LNode<Type> * s = p->next;
    while (p != nullptr)
    {
        delete p;
        p = s;
        if (p != nullptr) s = p->next;
    }
}

template <class Type>
void LinkList<Type>::ClearList(void)
{
    LNode<Type> * p = head->next;
    LNode<Type> * temp = nullptr;
    while (p != nullptr)
    {
        temp = p->next;
        delete p;
        p = temp;
    }
}

template <class Type>
bool LinkList<Type>::ListEmpty(void)
{
    return (head->next == nullptr);
}

template <class Type>
int LinkList<Type>::ListLength(void)
{
    int i = 0;
}
#endif