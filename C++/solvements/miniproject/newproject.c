#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct college //�����ѧ��Ϣ
{
    char name_uni[100]; //��ѧ����
    double jing;        //��ѧ����
    double wei;         //��ѧγ��
    char name[100][20]; //��ѧͬѧ����
    double dis;         //��ѧ����
    int numpeo;         //ͬѧ����
    struct college *next;
};
static double stdjing, stdwei;
typedef struct college C;
void begin(C *head, int *num);
int search(C *head, int *num, char[]); //�Ѵ�ѧ
double deg2rad(double deg);
double greatCircleDistance(double long1, double lat1, double long2, double lat2);
// ����˵���ʾ
void menu(void);
void output(C *head, int *num);
void add(C *head, int *num);
void seekname(C *head, int *num); //���顱ר��
void delete (C *head, int *num);
int main(void)
{
    printf("����׶�԰ȫ���䷹�ն�0.0.1\n");
    printf("Copyleft 2019 ����ΰ\n");
    printf("��ӭʹ������׶�԰ȫ���䷹�նˣ�\n");
    int num = 0;
    int flagcommand = 1; //������������־
    char command[100], ch;
    C *head, *p;                   //ͷ�ڵ�
    head = (C *)malloc(sizeof(C)); //����ͷ�ڵ�
    if (head == NULL)              //����ʧ��,�򷵻�
    {
        printf("no enough memory!\n");
        exit(0);
    }
    head->next = NULL; //ͷ�ڵ��ָ������NULL
    begin(head, &num);

    menu();
    p = head;
    while (flagcommand)
    {
        scanf("%s", command);
        while ((ch = getchar()) != '\n')
            ;
        if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
        {
            // ��
            output(head, &num);
        }
        else if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
        {
            // ��
            printf("��������Ҫ���ҵ�ͬѧ(ÿ������90�ˣ���enterΪ������)��");
            seekname(head, &num);
        }
        else if (strcmp(">>�˳�", command) == 0 || strcmp("�˳�", command) == 0 || strcmp("�����˳�", command) == 0)
        {
            // �˳�
            flagcommand = 0;
        }
        else if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
        {
            // ��
            printf("�������ѧ������ͬѧ������\n");
            add(head, &num);
        }
        else if (strcmp("����˵�", command) == 0 || strcmp(">>����˵�", command) == 0 || strcmp("��������˵�", command) == 0)
        {
            // ����˵�
            menu();
        }
        else if (strcmp("ɾ", command) == 0 || strcmp(">>ɾ", command) == 0 || strcmp("����ɾ", command) == 0)
        {
            // ɾ
            printf("��������Ҫɾ����ͬѧ��");
            delete (head, &num);
        }
        else
        {
            printf("����Ϸ�������������\n��֪�����������롰����˵���\n\n");
        }
    }
    printf("�ļ��Ա��棡�ټ���");
    return 0;
}

void begin(C *head, int *num)
{
    FILE *in;
    char name_uni[1000], ch;
    double jing, wei;
    int i = -1, j, flag;
    C *tail, *pnew;

    *num = 0;
    if ((in = fopen("schools.txt", "r")) == NULL) //���ܴ��ļ�����
    {
        fprintf(stdout, "���ܴ�\"schools.txt\"�ļ���\n");
    }

    tail = head;
    while (fscanf(in, "%s%lf%lf", name_uni, &jing, &wei))
    {
        if (*num == 0)
        {
            stdwei = wei;
            stdjing = jing;
        }
        pnew = (C *)malloc(sizeof(C));
        pnew->next = NULL;
        tail->next = pnew;
        tail = pnew;
        strcpy(pnew->name_uni, name_uni);
        pnew->jing = jing;
        pnew->wei = wei;
        pnew->dis = greatCircleDistance(jing, wei, stdjing, stdwei);
        i = 0;
        while (fscanf(in, "%s", pnew->name[i]))
        {
            printf("%s\n",pnew->name[i]);
            i++;
            if ((getc(in)) == '\n')
                break;
            else if ((getc(in)) == EOF)
                return;
        }
        pnew->numpeo = i;
        (*num)++;
    }
    
}
int search(C *head, int *num, char yours[1000]) //���ѧ����
{
    C *p;
    int i = 0;
    p = head;
    while (1)
    {
        i++;
        p = p->next;
        if (strcmp(yours, p->name_uni) == 0)
            break;
        if (p->next == NULL)
            return 0;
    }
    return i;
}

double deg2rad(double deg)
{
    double l = -1.0;
    double PI = acos(l);
    return (deg * PI / 180.0);
}
double greatCircleDistance(double long1, double lat1, double long2, double lat2)
{
    if (lat1 == lat2 && long1 == long2)
        return 0.0;
    static const int R = 6371; // Radius of the Earth, in km
    return R * acos(cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
                        cos(deg2rad(long1 - long2)) +
                    sin(deg2rad(lat1)) * sin(deg2rad(lat2)));
}
// ����˵���ʾ
void menu(void)
{
    printf("\n�У��ɽ���Զ���д�ѧ������䷹\n");
    printf("�飺��ѯ��ͬѧ��ѧУ���侭γ���Լ�����ƴ�ľ���\n");
    printf("��������ͬѧ�������ѧУ��δ�Ǽǣ���Ҫ��������ѧУ��γ��\n");
    printf("ɾ��ɾ������ͬ��ͬѧ��Ϣ\n");
    // printf("���£����������ѧ����\n");
    printf("����˵�����ʾ���п���������Ϣ\n");
    printf("�˳����˳�����\n");
    printf("\nע�⣺����������ʱֻ������\"����\"����\n\n");
}

void output(C *head, int *num)
{
    C *p;
    p = head;
    int i, j;
    printf("�У�\n");
    printf("%-22s   %5s      ����%9s\n", "��ѧ����", "����", "ͬѧ");
    printf("-----------------------------------------------------\n");
    for (i = 0; i < *num; i++)
    {
        p = p->next;
        printf("%-22s %5d km     %-2d%s     ", p->name_uni, (int)p->dis, p->numpeo, "��");
        for (j = 0; j < p->numpeo - 1; j++)
        {
            printf("%s ", p->name[j]);
        }
        printf("%s", p->name[j]);
        printf("\n");
    }
    printf("\n");
}
void add(C *head, int *num)
{
    char yours[1000], name[1000], ch;
    int key, j = 0;
    double jing, wei, dis;
    C *p, *pnew, *tail;
    p = head;
    scanf("%s", yours);
    while ((ch = getchar()) == ' ')
        ;
    if (ch == '\n')
    {
        printf("���������롰��������ڴ�ѧ��ӿո���������\n\n");
        return;
    }
    else
    {
        name[j] = ch;
        j++;
        while ((ch = getchar()) != '\n' && ch != ' ')
        {
            name[j] = ch;
            j++;
        }
        name[j] = '\0';
        if (ch != '\n')
        {
            while ((ch = getchar()) == ' ')
                ;
            if (ch != '\n')
            {
                printf("�Բ���һ��ֻ����һ����ֻ����һ��\n");
                while ((ch = getchar()) != '\n')
                    ;
            }
        }
    }
    if ((key = search(head, num, yours)) != 0) //�������ѧ
    {
        for (int i = 0; i < key; i++)
        {
            p = p->next;
        }
        strcpy(p->name[p->numpeo], name);
        p->numpeo++;
        printf("�����ͬѧ�ɹ�\n\n");
    }
    else
    {
        printf("����һ���´�ѧ�������뾭γ��\n");
        while (scanf("%lf%lf", &jing, &wei) != 2 || (jing > 180 || wei > 90 || jing < 0 || wei < 0))
        {
            printf("��������ȷ����ֵ\n");
            while (getchar() != '\n')
                ;
        }
        dis = greatCircleDistance(jing, wei, stdjing, stdwei);
        for (p = p->next; (p->dis < dis) && ((p->next)->dis < dis) && ((p->next)->next != NULL); p = p->next)
            ;
        if ((p->next)->next == NULL)
            p = p->next;
        pnew = (C *)malloc(sizeof(C));
        pnew->next = p->next;
        strcpy(pnew->name_uni, yours);
        strcpy(pnew->name[0], name);
        pnew->numpeo = 1;
        pnew->dis = dis;
        pnew->jing = jing;
        pnew->wei = wei;
        p->next = pnew;
        (*num)++;
        printf("����´�ѧ�ɹ�\n\n");
    }

    FILE *out;
    int i, k;
    p = head;
    if ((out = fopen("schools.txt", "w")) == NULL)
    {
        printf("���ܴ�schools.txt�ļ�\n����ϵ���������");
    }
    for (i = 0; i < *num; i++)
    {
        p = p->next;
        fprintf(out, "%s  %lf  %lf  ", p->name_uni, p->jing, p->wei);
        for (j = 0; j < p->numpeo - 1; j++)
        {
            fprintf(out, "%s  ", p->name[j]);
        }
        fprintf(out, "%s\n", p->name[j]);
    }
    fclose(out);
}
void seekname(C *head, int *num)
{
    int i, j = 0, k, flag = 1, sum = 0; //sumΪҪ������
    char name[100][30], ch;
    C *p;
    while (scanf("%s", name[sum]))
    {
        sum++;
        if ((getchar()) == '\n')
            break;
    }
    for (k = 0; k < sum; k++)
    {
        flag = 1;
        p = head;
        for (i = 0; i < *num; i++)
        {
            p = p->next;
            for (j = 0; j < p->numpeo; j++)
            {
                if (strcmp(name[k], p->name[j]) == 0)
                {
                    flag = 0;
                    printf("%s %s\n��γ��%lf��  ������%lf��\n����ƴ�:%d km\n\n", p->name_uni, p->name[j], p->wei, p->jing, (int)p->dis);
                }
            }
        }
        if (flag == 1)
        {
            printf("û��%s��\n\n", name[k]);
        }
    }
}
void delete (C *head, int *num)
{
    char name[1000], ch;
    C *pdel, *p;
    int i, j = 0, k, flag = 1, delnum = 0;
    ch = getchar();
    if (ch == ' ')
    {
        while ((ch = getchar()) == ' ' && ch != '\n') //һ�����ո��\n
            ;
        if (ch == '\n')
        {
            printf("���������롰ɾ�������������\n");
            return;
        }
        else
        {
            scanf("%s", name);
        }
    }
    else if (ch == '\n')
    {
        printf("���������롰ɾ�������������\n");
        return;
    }
    else
    {
        name[j] = ch;
        j++;
        while ((ch = getchar()) != '\n' && ch != ' ')
        {
            name[j] = ch;
            j++;
        }
        name[j] = '\0';
        if (ch != '\n')
        {
            while ((ch = getchar()) == ' ')
                ;
            if (ch != '\n')
            {
                printf("�Բ���һ��ֻ��ɾһ����ֻɾ��һ��\n");
                while ((ch = getchar()) != '\n')
                    ;
            }
        }
    }
    flag = 1;
    pdel = head;
    for (i = 0; i < *num; i++)
    {
        pdel = pdel->next;
        for (j = 0; j < pdel->numpeo; j++)
        {
            if (strcmp(name, pdel->name[j]) == 0)
            {
                flag = 0;
                for (k = j + 1; k < pdel->numpeo; k++)
                {
                    strcpy(pdel->name[k - 1], pdel->name[k]);
                }
                pdel->numpeo--;
                if (pdel->numpeo == 0)
                {
                    for (p = head; (p->next)->numpeo != 0; p = p->next)
                        ;
                    p->next = pdel->next;
                    free(pdel);
                    pdel = p;
                    delnum++;
                }
            }
        }
    }
    (*num) -= delnum;
    if (flag == 1)
    {
        printf("û�����ͬѧ\n\n");
    }
    else
    {
        printf("ɾ���ɹ�\n\n");
    }

    FILE *out;
    p = head;
    if ((out = fopen("schools.txt", "w")) == NULL)
    {
        printf("���ܴ�schools.txt�ļ�\n����ϵ���������");
    }
    for (i = 0; i < *num; i++)
    {
        p = p->next;
        fprintf(out, "%s  %lf  %lf ", p->name_uni, p->jing, p->wei);
        for (j = 0; j < p->numpeo - 1; j++)
        {
            fprintf(out, "%s  ", p->name[j]);
        }
        fprintf(out, "%s\n", p->name[j]);
    }
    fclose(out);
}