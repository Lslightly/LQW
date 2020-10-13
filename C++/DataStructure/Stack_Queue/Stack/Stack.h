#ifndef STACK_H_
#define STACK_H_

#define STACK_INIT_SIZE 100 //  初始分配量
#define STACKINCREMENT 10   //  存储空间增量

#include <cstring>

template <class Type>
class SqStack
{
public:
    Type *base; //  栈底
    Type *top;  //  栈顶, 指向最后一个元素的后面的指针
    int stacksize;
    SqStack();                                  //  初始化栈
    ~SqStack();                                 //  销毁栈
    void ClearStack(void);                      //  清空栈
    bool StackEmpty(void);                      //  栈为空，返回true; 否则返回false
    int StackLength(void);                      //  返回长度
    Type &GetTop(void);                         //  返回栈顶元素
    bool Push(Type e);                          //  压栈
    bool Pop(Type &e);                          //  出栈
    bool StackTraverse(bool (*visit)(Type &e)); //  遍历，若(* visit)返回false则返回false
};

template <class Type>
SqStack<Type>::SqStack()
{
    base = new Type[STACK_INIT_SIZE];
    top = base;
    stacksize = STACK_INIT_SIZE;
}

template <class Type>
SqStack<Type>::~SqStack()
{
    delete[] base;
    stacksize = 0;
}

template <class Type>
void SqStack<Type>::ClearStack(void)
{
    top = base;
}

template <class Type>
bool SqStack<Type>::StackEmpty(void)
{
    return top - base == 0;
}

template <class Type>
int SqStack<Type>::StackLength(void)
{
    return top - base;
}

template <class Type>
Type &SqStack<Type>::GetTop(void)
{
    return *top;
}

template <class Type>
bool SqStack<Type>::Push(Type e)
{
    if (top - base == stacksize)
    {
        Type *base_new = new Type[stacksize + STACKINCREMENT];
        if (base_new == nullptr)
            return false;
        memcpy(base_new, base, top - base);
        delete[] base;
        base = base_new;
    }
    *top++ = e;
    return true;
}

template <class Type>
bool SqStack<Type>::Pop(Type &e)
{
    if (top == base)
        return false;
    e = *--top;
    return true;
}

template <class Type>
bool SqStack<Type>::StackTraverse(bool (*visit)(Type &e))
{
    Type *i;
    for (; i < top; i++)
    {
        if (!(*visit)(*i))
            return false;
    }
    return true;
}
#endif