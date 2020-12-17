#include <stdio.h>
#include <string.h>

typedef float KeyType;
typedef int KeyType;
typedef char * KeyType;


typedef struct
{
    KeyType key;
    char * info;
}ElemType;

//  number type
#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) < (b))
#define LQ(a,b) ((a) <= (b))

//  string type
// #define EQ(a,b) (!strcmp((a), (b)))
// #define LT(a,b) (strcmp((a), (b)) < 0)
// #define LQ(a,b) (strcmp((a), (b)) <= 0)

template <class ElemType, class KeyType>
class StaticSearchTable
{
private:
    ElemType * elem;
    int length;
public:
    StaticSearchTable(int n, KeyType l);
    ~StaticSearchTable();
    Search_Seq(KeyType key);
};

template <class ElemType, class KeyType>
StaticSearchTable<ElemType, KeyType>::StaticSearchTable(int n, KeyType l)
{
    
}

template <class ElemType, class KeyType>
StaticSearchTable<ElemType, KeyType>::~StaticSearchTable()
{

}

template <class ElemType, class KeyType>
StaticSearchTable<ElemType, KeyType>::Search_Seq(KeyType key)
{
    this->elem[0].key = key;
    for (int i = this->length; !EQ(this->elem[i].key, key); --i);
    return i;
}
