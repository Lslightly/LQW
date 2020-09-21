#ifndef Sqlist_H
#define Sqlist_H 1
template <class Type>
class SqList{
    Type * elem;
    int length;
    int listsize;
    SqList();
    ~SqList();
    void ClearList(void);
    bool ListEmpty(void);
    int ListLength(void);
    bool GetElem(const int i, Type & e);
    int LocateElem(const Type e, bool (* compare)(const Type a, const Type b));
    bool PriorElem(const Type cur_e, Type & pre_e);
    bool NextElem(const Type cur_e, Type & next_e);
    bool ListInsert(const int i, const Type e);
    bool ListDelete(const int i, Type & e);
    bool ListTraverse((* visit)());
};

#endif