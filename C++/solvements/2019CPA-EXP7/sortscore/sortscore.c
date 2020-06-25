#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stu
{
    char id[12];
    int score;
    struct stu * next;
};
typedef struct stu S;
int main(void)
{
    int a, b, n,t,i,j,key;
    char temp[12];
    S*p,*pnew,*head,*tail,*pbefore;
    head=(S*)malloc(sizeof(S));
    tail=head;
    tail->next=NULL;
    scanf("%d%d", &a, &b);
    n = a + b;
    for (i=0;i<n;i++)
    {
        pnew=(S*)malloc(sizeof(S));
        pnew->next=NULL;
        scanf("%s%d",pnew->id,&pnew->score);
        tail->next=pnew;
        tail=pnew;
    }
    for (i=0;i<n-1;i++)
    {

        pbefore=head;
        for (j=0;j<n-i-1;j++)
        {
            p=pbefore->next;
            if ((key=strcmp(p->id,p->next->id))>0)
            {
                strcpy(temp,p->id);
                strcpy(p->id,p->next->id);
                strcpy(p->next->id,temp);
                t=p->score;
                p->score=p->next->score;
                p->next->score=t;
                pbefore=pbefore->next;
            }
            else if (key==0)
            {
                pnew=p->next->next;
                free(p->next);
                p->next=pnew;
                n--;
                j--;
            }
            else
            {
                pbefore=pbefore->next;
            }
            
        }
    }
    p=head;
    for (i=0;i<n-1;i++)
    {
        p=p->next;
        printf("%s %d\n",p->id,p->score);
    }
    p=p->next;
    printf("%s %d",p->id,p->score);
}