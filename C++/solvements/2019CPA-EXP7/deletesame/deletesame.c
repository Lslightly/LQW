// B. 退学就被删学号了
// 有两个链表a和b，设结点中包含学号、姓名。从a链表中删去和b链表中有相同学号的那些结点。

// Input Description
// 首先输入两个数字m和n，分别表示链表a和b结点数。
// 随后输入m+n行，每行包含学号和姓名，中间用空格隔开。
// 前m行每行表示链表a每个结点的数据，后n行每行表示链表b每个结点的数据

// Output Description
// 输出删除操作后链表a每个结点的数据，每行表示一个结点，学号和姓名用一个空格隔开。
// 如果删除操作后链表a不含结点，则输出-1
// Samples
// INPUT 1 
// 3 3
// PB001 student1
// PB002 student2
// PB003 student3
// PB004 student4
// PB002 student2
// PB005 student5
// OUTPUT 1 
// PB001 student1
// PB003 student3

// INPUT 2 
// 1 1
// PB001 student1
// PB001 student1
// OUTPUT 2 
// -1
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct stu
{
    char name[50];
    char id[50];
    struct stu * next;
};
typedef struct stu S;
int main(void)
{
    int n,m;
    S*ahead,*bhead,*pnew,*ap,*bp,*apdel,*bpdel,*atail,*btail;
    ahead=(S*)malloc(sizeof(S));
    bhead=(S*)malloc(sizeof(S));
    atail=ahead;
    btail=bhead;
    atail->next=NULL;
    btail->next=NULL;
    scanf("%d%d",&m,&n);
    for (int i=0;i<m;i++)
    {
        pnew=(S*)malloc(sizeof(S));
        pnew->next=NULL;
        scanf("%s%s",pnew->id,pnew->name);
        atail->next=pnew;
        atail=pnew;
    }
    for (int i=0;i<n;i++)
    {
        pnew=(S*)malloc(sizeof(S));
        pnew->next=NULL;
        scanf("%s%s",pnew->id,pnew->name);
        btail->next=pnew;
        btail=pnew;
    }
    for (ap=ahead->next;ap!=NULL;ap=ap->next)
    {
        for (bp=bhead->next;bp!=NULL;bp=bp->next)
        {
            if (strcmp(ap->id,bp->id)==0)
            {
                for (apdel=ahead;apdel->next!=ap;apdel=apdel->next);
                for (bpdel=bhead;bpdel->next!=bp;bpdel=bpdel->next);
                apdel->next=ap->next;
                free(ap);
                ap=apdel;
                bpdel->next=bp->next;
                free(bp);
                bp=bpdel;
            }
        }
    }
    if (ahead->next==NULL) printf("-1");
    else
    {
        for (ap=ahead->next;ap!=NULL;ap=ap->next)
        {
            printf("%s %s\n",ap->id,ap->name);
        }
    }
}