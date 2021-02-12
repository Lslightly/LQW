//  多级双向链表
#include <iostream>
#include <string.h>

#define MAX_NODE_SIZE 1000

using namespace std;
typedef struct Node
{
    int val;
    Node *prev;
    Node *next;
    Node *child;
}Node;

typedef struct MLDL
{
    Node *head;
}MLDL;

class Solution
{
public:
    Node *flatten(Node *head);
    void Initialize(MLDL &L);
    void CreateMLDL(Node *&head, int level, int num_level[MAX_NODE_SIZE], int val[MAX_NODE_SIZE], int levels);
    void Print(const MLDL &L);
    int Split(string input, int num_level[MAX_NODE_SIZE], int val[MAX_NODE_SIZE]);
};

int main(void)
{
    MLDL L;
    Solution S;
    S.Initialize(L);
    S.flatten(L.head);
    S.Print(L);
    return 0;
}

Node *Solution::flatten(Node *head)
{
    Node *p = head;
    Node *endp;
    while (p)
    {
        if (p->child)
        {
            endp = flatten(p->child);
            endp->next = p->next;
            p->next = p->child;
            p->child = nullptr;
            if (endp->next) endp->next->prev = endp;
            p->next->prev = p;
            if (!endp->next)
            {
                p = endp;
                break;
            }
            else p = endp->next;
        }
        else
        {
            if (!p->next)
            {
                break;
            }
            p = p->next;
        }
        
    }
    return p;
}

void Solution::Initialize(MLDL &L)
{
    string input;
    getline(cin, input);
    int num_level[MAX_NODE_SIZE] = {0};
    int val[MAX_NODE_SIZE] = {0};
    int levels = 0;
    levels = Split(input, num_level, val);
    L.head = nullptr;
    CreateMLDL(L.head, 0, num_level, val, levels);
}

void Solution::Print(const MLDL &L)
{
    Node *p = L.head;
    cout << '[';
    while (p && p->next)
    {
        cout << p->val << ',';
        p = p->next;
    }
    cout << p->val << ']';
}

//  返回levels
int Solution::Split(string input, int num_level[MAX_NODE_SIZE], int val[MAX_NODE_SIZE])
{
    size_t num_index = input.find_first_of('[')+1;
    size_t next_index;
    string part;
    int levels = 0;
    bool flag_newline = false;
    int num_nodes = 0;
    while ((next_index = input.find_first_of(',', num_index)) != string::npos)
    {
        part = input.substr(num_index, next_index-num_index);
        if (part != "null")
        {
            flag_newline = true;
            num_level[levels]++;
            val[num_nodes] = stoi(part);
        }
        else if (part == "null" && !flag_newline)   //  新行的null
        {
            val[num_nodes] = 0;
        }
        else
        {
            levels++;
            num_nodes--;
            flag_newline = false;
        }
        num_nodes++;
        num_index = next_index+1;
    }
    next_index = input.find_first_of(']', num_index);
    part = input.substr(num_index, next_index-num_index);
    num_level[levels]++;
    val[num_nodes] = stoi(part);
    levels++;
    return levels;
}

void Solution::CreateMLDL(Node *&head, int level, int num_level[MAX_NODE_SIZE], int val[MAX_NODE_SIZE], int levels)
{
    head = (Node *)malloc(sizeof(Node) * num_level[level]);
    int i;
    for (i = 0; i < num_level[level]; i++, val++)
    {
        head[i].val = *val;
        head[i].next = (i == num_level[level]-1)?nullptr:head+i+1;
        head[i].prev = (i == 0)?nullptr:head+i-1;
        head[i].child = nullptr;
    }
    if (level < levels)
    {
        for (i = 0; i < num_level[level] && *val == 0; ++i, ++val)
            ;
        CreateMLDL(head[i].child, level+1, num_level, val, levels);
    }
}

