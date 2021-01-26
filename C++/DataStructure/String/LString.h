#ifndef LSTRING_H_
#define LSTRING_H_ 1
//  串块链存储表示
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define CHUNKSIZE 80
typedef struct Chunk
{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;

typedef struct
{
    Chunk *head, *tail;
    int curlen;
}LString;


#endif