#ifndef ARRAY_H_
#define ARRAY_H_ 1
//  数组
#include <stdlib.h>
#include <stdarg.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

#define MAX_ARRAY_DIM 8 //  数组维数最大值
typedef struct
{
    ElemType * base;    //  数组元素基址
    int dim;            //  数组维数
    int *bounds;        //  数组维界基址
    int *constants;     //  数组映像函数常量基址
}Array;

//  若维数dim和随后各维长度合法，则构造相应的数组A，然后OK
Status InitArray(Array &A, int dim, ...);
//  销毁数组A
Status DestroyArray(Array &A);
//  A是n维数组，e是元素变量，随后是n个下标。若下标不越界，则e赋为指定元素，返回OK
Status Value(Array A, ElemType &e, ...);
//  A是n维数组，e是元素变量，随后是n个下标。若下标不越界，则e赋给指定元素，返回OK
Status Assign(Array &A, ElemType e, ...);

Status InitArray(Array &A, int dim, ...)
{
    if (dim < 1 || dim > MAX_ARRAY_DIM) return ERROR;
    A.dim = dim;
    A.bounds = (int *)malloc(sizeof(int) * dim);
    if (!A.bounds) exit(OVERFLOW);
    int elemtotal = 1;
    va_list ap;
    va_start(ap, dim);
    for (int i = 0; i<dim; i++)
    {
        A.bounds[i] = va_arg(ap, int);
        if (A.bounds[i] < 0) return ERROR;
        elemtotal *= A.bounds[i];
    }
    va_end(ap);
    A.base = (ElemType *)malloc(sizeof(*A.base) * elemtotal);
    if (!A.base) exit(OVERFLOW);
    A.constants = (int *)malloc(sizeof(int) * dim);
    if (!A.constants) exit(OVERFLOW);
    A.constants[dim-1] = 1;
    for (int i = dim-2; i >= 0; i--)
    {
        A.constants[i] = A.constants[i+1] * A.bounds[i+1];
    }
    return OK;
}

Status DestroyArray(Array &A)
{
    if (!A.base) return ERROR;
    free(A.base);
    A.base = nullptr;
    if (!A.bounds) return ERROR;
    free(A.bounds);
    A.bounds = nullptr;
    if (!A.constants) return ERROR;
    free(A.constants);
    A.constants = nullptr;
    return OK;
}

Status Locate(Array A, va_list ap, int &off)
{
    int ind;
    off = 0;
    for (int i = 0; i < A.dim; i++)
    {
        ind = va_arg(ap, int);
        if (ind < 0 || ind >= A.bounds[i]) return OVERFLOW;
        off += A.constants[i] * ind;
    }
    return OK;
}

Status Value(Array A, ElemType &e, ...)
{
    va_list ap;
    va_start(ap, e);
    int off;
    int result;
    if ((result = Locate(A, ap, off)) <= 0) return result;
    e = *(A.base + off);
    va_end(ap);
    return OK;
}

Status Assign(Array &A, ElemType e, ...)
{
    va_list ap;
    int off;
    int result;
    va_start(ap, e);
    if ((result = Locate(A, ap, off)) <= 0)
        return result;
    *(A.base + off) = e;
    va_end(ap);
    return OK;
}

#endif