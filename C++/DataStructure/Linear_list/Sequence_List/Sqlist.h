#ifndef Sqlist_H
#define Sqlist_H 1

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#include <stdlib.h>

template <class Type>
class SqList{
private:
    Type * elem;
    int length;
    int listsize;
public:
    SqList();
    ~SqList();
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
    template<Type> friend void MergeList_Sq(SqList<Type> La, SqList<Type> Lb, SqList<Type> & Lc);
};

template <class Type>
SqList<Type>::SqList()
{
    elem = (Type *)malloc(sizeof(Type) * LIST_INIT_SIZE);
    length = 0;
    listsize = LIST_INIT_SIZE;
}

template <class Type>
SqList<Type>::~SqList()
{
    free(elem);
}

template <class Type>
void SqList<Type>::ClearList(void)
{
    length = 0;
    listsize = LIST_INIT_SIZE;
}

template <class Type>
bool SqList<Type>::ListEmpty(void)
{
    return length == 0;
}

template <class Type>
int SqList<Type>::ListLength(void)
{
    return length;
}

template <class Type>
bool SqList<Type>::GetElem(const int i, Type &e)
{
    if (i >= length)
    {
        return false;
    }
    else
    {
        e = elem[i];
        return true;
    }
}

template <class Type>
int SqList<Type>::LocateElem(const Type e, bool (*compare)(const Type a, const Type b))
{
    int i = 1;
    Type * p = elem;
    while (i <= length && !(*compare)(*p++, e)) ++i;
    if (i <= length) return i;
    else return 0;
}

bool equal(const int a, const int b)
{
    return a == b;
}

template <class Type>
bool SqList<Type>::PriorElem(const Type cur_e, Type &pre_e)
{
    int cur_i = LocateElem(cur_e, equal);
    if (cur_i == 0)
    {
        return false;
    }
    else
    {
        pre_e = elem[cur_i - 1];
        return true;
    }
    return false;
}

template <class Type>
bool SqList<Type>::NextElem(const Type cur_e, Type &next_e)
{
    int cur_i = LocateElem(cur_e, equal);
    if (cur_i == length - 1)
    {
        return false;
    }
    else
    {
        next_e = elem[cur_i + 1];
        return true;
    }
    return false;
}

//  在第i个位置之前插入e
//  i的合法值为1<=i<=length+1
template <class Type>
bool SqList<Type>::ListInsert(int i, const Type e)
{
    if (i < 1 || i > length+1)  //  i值不合法
    {
        return false;
    }
    if (length >= listsize)     //  储存空间已满
    {
        Type *newbase = (Type *)realloc(elem, sizeof(Type) * (LIST_INIT_SIZE + LISTINCREMENT));
        if (!newbase)
        {
            return false;
        }
        elem = newbase;
        listsize += LISTINCREMENT;
    }
    Type * q = &elem[i-1];
    Type * p = elem + length - 1;
    for (; p >= q; p--) *(p+1) = *p;
    *q = e;
    length++;
    return true;
}

//  删除第i个元素，用e返回
//  i的合法值范围1<=i<=length
template <class Type>
bool SqList<Type>::ListDelete(const int i, Type &e)
{
    if (i < 1 || i > length)    //  超出范围
    {
        return false;
    }
    Type * p = &elem[i-1];
    Type * q = elem + length -1;
    e = *p;
    for (; p < q; p++) *p = *(p+1);
    length--;
    return true;
}

template <class Type>
bool SqList<Type>::ListTraverse(bool (*visit)(Type &e))
{
    for (int i = 0; i < length; i++)
    {
        if (visit(elem[i]) == false)
        {
            return false;
        }
    }
    return true;
}

//  La，Lb的元素已经按照非递减的顺序排列
template <class Type>
void MergeList_Sq(SqList<Type> La, SqList<Type> Lb, SqList<Type> & Lc)
{
    Type * pa = La.elem; Type * pb = Lb.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;

    Type * pc = Lc.elem = (Type *)malloc(Lc.listsize * sizeof(*pc));

    if (!Lc.elem) exit(-1);
    Type * pa_last = La.elem + La.length - 1;
    Type * pb_last = Lb.elem + Lb.length - 1;

    while (pa <= pa_last && pb <= pb_last)
    {
        if (*pa <= *pb) *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while (pa <= pa_last) *pc++ = *pa++;
    while (pb <= pb_last) *pc++ = *pb++;
}
#endif