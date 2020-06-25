/*�������ʱ������ʾ������Ϣ���ڰ�����Ϣ����ʾ�£�����������¹��ܣ�ֱ���˳�
�г�������Ϣ
�У��г�����ѧ����Ϣ��Ҫ��ʹ�����򷽷��������й���ѧ������ѧ�ɽ���Զ�г�����ѧ����Ϣ��4�֣�
�飺��ѯĳ��ѧ����Ϣ����������ѧ����������ѯ�õ�ѧ����������Ϣ��ѧ�����������������ѧ�����������ѧ��γ�ȡ����������й��ƴ���롿��4�֣�
���������������Ϣ���ѧ�����������ѧУ��γ�ȴ������ļ��й����ִ�ѧλ����Ϣ�Ļ���ֱ����ӣ������ڵĻ���Ҫ����Ӿ�γ����Ϣ��ʹ�á��С���
�ܲ鿴���ӵ�ѧ���Ƿ�ɹ���4�֣�
ɾ�����������ѧ������ɾ��ѧ����Ϣ��ʹ�á��С����ܲ鿴ɾ����ѧ���Ƿ�ɹ���4�֣�
�˳����˳�����������ѧ����Ϣ���ļ���������̻�����Ӻ�ɾ������Ϣ�Ƿ񱣴�ɹ����������Ϣ������ѧ������������ѧ������ѧУ����������ѧУ
��γ����Ϣ����4�֣�
bonus�ӷ֣���������Ϊ���¹��ܻ������õĽ�����ʽ������ӷ֣��ýṹ������������ڼӷ֡�*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
struct college //�����ѧ��Ϣ
{
    char name_uni[N]; //��ѧ����
    double jing;      //��ѧ����
    double wei;       //��ѧγ��
    char name[N][20]; //��ѧͬѧ����
    double dis;       //��ѧ����
    int numpeo;       //ͬѧ����
};
// ����
void sort(struct college c[N], int *num, int order[N]);
// �����ļ��뿪ʼ�˵�
FILE *begin(struct college c[N], int *num, int order[N]);
// �����Լ��Ĵ�ѧ
int your(struct college c[N], int *, FILE *, char yours[], int *order, int *key);
// ɾ
int delete (struct college c[N], int *num, FILE *out, char name[N], char yours[N], int order[N], int *key);
// ����
void add(struct college c[], int *, char uni[], char name[], FILE *, int *order, int k);
// ����
void seekname(char[], const struct college c[], int num, char yours[N], int order[N]);
// ����˵���ʾ
void menu(void);
// �������޴�ѧ
int search(const struct college c[], char yours[N], int num, int *order);
// ���������������
double deg2rad(double deg);
double greatCircleDistance(double long1, double lat1, double long2, double lat2);
void dis(struct college c[], int num, int key);
// ��������
void output(const struct college c[], int order[N], int *num);

int main(int argc, char *argv[])
{
    int num = 0, key = -1, i, j, t, flag, a, back;
    char ch; //������������
    char command[N], name[N], uni[N], yours[N];
    struct college c[N];
    int order[N] = {0};  //��¼��ѧ����Զ���������±�
    int flagcommand = 1; //������������־
    double jing, wei;
    FILE *in;
    // �����ļ��뿪ʼ�˵�
    printf("123");
    in = begin(c, &num, order);
    // �����������ѧ
    a = your(c, &num, in, yours, &order[0], &key);
    sort(c, &num, order);
    if (a == 1)
        return 0;

    flagcommand = 1;
    // �ж�ִ��������
    while (flagcommand)
    {
        scanf("%s", command);
        if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
        {
            // ��
            output(c, order, &num);
        }
        else if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
        {
            // ��
            scanf("%s", name); //command����name����ʡ�ڴ�ռ�
            seekname(name, c, num, yours, &order[0]);
        }
        else if (strcmp(">>�˳�", command) == 0 || strcmp("�˳�", command) == 0 || strcmp("�����˳�", command) == 0)
        {
            // �˳�
            flagcommand = 0;
        }
        else if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
        {
            // ��
            scanf("%s%s", uni, name);
            while (getchar() != '\n')
                ;
            add(c, &num, uni, name, in, order, key);
        }
        else if (strcmp("����˵�", command) == 0 || strcmp(">>����˵�", command) == 0 || strcmp("��������˵�", command) == 0)
        {
            // ����˵�
            menu();
        }
        else if (strcmp("ɾ", command) == 0 || strcmp(">>ɾ", command) == 0 || strcmp("����ɾ", command) == 0)
        {
            // ɾ
            scanf("%s", name);
            while (getchar() != '\n')
                ;
            back = delete (c, &num, in, name, yours, &order[0], &key);
            printf("%d\n", num);
            if (back == 1)
            {
                printf("������Ĵ�ѧ�Ѿ�û��ͬѧ�ˣ��޷�������룬����´�ѧ�������ӻ�ͬѧ�����˳�\n");
                flagcommand = 1;
                while (flagcommand)
                {
                    scanf("%s", command);
                    if (strcmp(">>�˳�", command) == 0 || strcmp("�˳�", command) == 0 || strcmp("�����˳�", command) == 0)
                    {
                        // �˳�
                        flagcommand = 0;
                    }
                    else if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
                    {
                        // ��
                        scanf("%s%s", uni, name);
                        while (getchar() != '\n')
                            ;
                        add(c, &num, uni, name, in, order, key);
                        //  a = your(c, &num, in, yours);
                        break;
                    }
                    // else if (strcmp(">>����", command) == 0 || strcmp("����", command) == 0 || strcmp("��������", command) == 0)
                    // {
                    //     a = your(c, &num, in, yours);
                    //     break;
                    // }
                    else
                    {
                        printf("����Ϸ�������������\n");
                    }
                }
            }
            else
            {
            }
        }
        // else if (strcmp(">>����", command) == 0 || strcmp("����", command) == 0 || strcmp("��������", command) == 0)
        // {
        //     a = your(c, &num, in, yours);
        // }
        else
        {
            printf("����Ϸ�������������\n");
        }
    }
    printf("�ļ��Ա��棡�ټ���");
    fclose(in);
    return 0;
}
// �����ļ��뿪ʼ�˵�
FILE *begin(struct college c[N], int *num, int *order)
{
    int key = -1, i, j, t, flag;
    char ch; //������������
    char yours[N], command[N], name[N], uni[N];
    int flagcommand = 1; //������������־
    double jing, wei;
    FILE *in;
    if ((in = fopen("schools.txt", "r")) == NULL) //���ܴ��ļ�����
    {
        fprintf(stdout, "���ܴ�\"schools.txt\"�ļ���\n");
    }
    fscanf(in, "%s%lf%lf", c[*num].name_uni, &c[*num].jing, &c[*num].wei);
    do //�ļ�����
    {
        key = search(c, c[*num].name_uni, *num, order);
        if (key != -1)
        {
            (*num)--;
            i = c[key].numpeo - 1;
            j = 0;
            flag = 0;
        }
        else
        {
            key = *num;
            i = -1;
            j = 0;
            flag = 0;
        }
        while ((ch = getc(in)) != '\n') //������
        {
            if (ch == ' ') //��һ�αض��ո����\n        ???
            {
                i++;
                j = 0;
                flag = 0;
                while ((ch = getc(in)) == ' ')
                    ;
                if (ch != '\n')
                {
                    c[key].name[i][j] = ch;
                    j++;
                    flag = 1;
                }
                else
                    break;
            }
            else
            {
                c[key].name[i][j] = ch;
                j++;
                flag = 1;
            }
        }
        if (i == -1)
            c[key].numpeo = 0;
        else
        {
            if (flag)
                c[key].numpeo = i + 1;
            else
                c[key].numpeo = i;
        }
        (*num)++;
    } while (fscanf(in, "%s%lf%lf", c[*num].name_uni, &c[*num].jing, &c[*num].wei) == 3);

    // printf("OK!Let's go!\n");
    printf("����׶�԰ȫ���䷹�ն�0.0.1\n");
    printf("Copyleft 2019 ����ΰ\n");
    printf("��ӭʹ������׶�԰ȫ���䷹�նˣ�\n");
    for (i = 0; i < *num; i++)
    {
        order[i] = i;
    }
    return in;
    fclose(in);
}
// �����Լ��Ĵ�ѧ
int your(struct college c[N], int *num, FILE *in, char yours[N], int *order, int *key)
{
    int i, j, t, flag, a;
    char ch; //������������
    char command[N], name[N], uni[N];
    int flagcommand = 1; //������������־
    double jing, wei;
    printf("������Ĵ�ѧ�ǣ�");
    scanf("%s", yours); //��Ĵ�ѧ�ǣ�
    while (getchar() != '\n')
        ;
    // ������û�������ѧ
    *key = search(c, yours, *num, order);
    if (*key == -1) //û�������ѧ
    {
        printf("\n��Ǹ����û�в��ҵ�������� %s��\n�Դˣ����������\n", yours);
        printf("�� [ѧУ] [����]([ѧУ����] [ѧУγ��]) ������ͬѧ�������ѧУ��δ�Ǽǣ���Ҫ��������ѧУ��γ��\n");
        printf("���£����������ѧ����\n");
        printf("�˳����˳�����\n");
        printf("�����ʽ���£�\n>>�� ��������ѧԺ *** (126.670966 45.782211)(���뾭γ��ʱ���Ų�������)\n(��ѯ��γ����վ��http://api.map.baidu.com/lbsapi/getpoint/index.html)\n>>����\n>>�˳�\n");
        while (flagcommand)
        {
            scanf("%s", command);
            while (getchar() != '\n')
                ;
            if (strcmp(">>�˳�", command) == 0 || strcmp("�˳�", command) == 0 || strcmp("�����˳�", command) == 0)
            {
                printf("��ӭ�´�ʹ�ã��ټ���");
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(">>��", command) == 0 || strcmp("��", command) == 0 || strcmp("������", command) == 0)
            {
                scanf("%s%s", uni, name);
                add(c, num, uni, name, in, order, *key);
                dis(c, *num, *key);
                *key = search(c, uni, *num, order);
                flagcommand = 0;
            }
            // else if (strcmp(">>����", command) == 0 || strcmp("����", command) == 0 || strcmp("��������", command) == 0)
            // {
            //     a = your(c, num, in, yours);
            // }
            else
            {
                printf("����Ϸ�������������\n");
            }
        }
    }
    else //�������ѧ
    {
        printf("������� %s ���ڣ������¿�������:\n", yours);
        menu();
    }
    dis(c, *num, *key); //�����
    return 0;
}
// ���������������
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
void dis(struct college c[], int num, int key)
{
    for (int i = 0; i < num; i++)
    {
        c[i].dis = greatCircleDistance(c[i].jing, c[i].wei, c[key].jing, c[key].wei);
    }
}
// ����
void sort(struct college c[N], int *num, int order[N])
{
    int i, j, t;
    for (i = 0; i < *num - 1; i++)
    {
        for (j = 0; j < *num - i - 1; j++)
        {
            if (c[order[j]].dis > c[order[j + 1]].dis)
            {
                t = order[j];
                order[j] = order[j + 1];
                order[j + 1] = t;
            }
        }
    }
}
// ��
void output(const struct college c[], int order[N], int *num)
{
    int i, j, t;
    FILE *out;
    out=fopen("schools.txt","w");
    printf("�У�\n");
    printf("%-22s   %5s %15s\n", "��ѧ����", "����", "ͬѧ");
    printf("-----------------------------------------------------\n");
    for (i = 0; i < *num; i++)
    {
        if (c[order[i]].numpeo != 0)
        {
            fprintf(out,"%s %lf %lf ", c[order[i]].name_uni,c[order[i]].jing,c[order[i]].wei);
            printf("%d  %-22s %5d km          ", i, c[order[i]].name_uni, (int)c[order[i]].dis);
            for (j = 0; j < c[order[i]].numpeo-1; j++)
                {printf("%s ", c[order[i]].name[j]);
                 fprintf(out,"%s ", c[order[i]].name[j]);
                }
               printf("%s ", c[order[i]].name[j]);
                 fprintf(out,"%s\n", c[order[i]].name[j]);
            printf("\n");
            
        }
    }
    printf("%d\n", *num);
    fclose(out);
}

// ���ѧ
int search(const struct college c[], char yours[N], int num, int order[N])
{
    // ��һ���������ѧ��
    int i = 0;
    for (i = 0; i < num; i++)
    {
        if (strcmp(yours, c[order[i]].name_uni) == 0)
        {
            break;
        }
    }
    if (i != num)
    {
        return order[i]; //�У������±�
        printf("%d\n", order[i]);
    }
    else
        return -1; //û�У�����-1
}

// ����˵���ʾ
void menu(void)
{
    printf("\n�У����վ���������Ĵ�ѧ�ɽ���Զ���д�ѧ�����г���У��ͬѧ������䷹\n");
    printf("�� [����]����ѯ��ͬѧ����ѧУ���侭γ���Լ�������ѧУ�ľ���\n");
    printf("�� [ѧУ] [����] ([ѧУ����] [ѧУγ��])������ͬѧ�������ѧУ��δ�Ǽǣ���Ҫ��������ѧУ��γ��\n");
    printf("ɾ [����]��ɾ��ͬѧ��Ϣ\n");
    printf("���£����������ѧ����\n");
    printf("����˵�����ʾ���п���������Ϣ\n");
    printf("�˳����˳�����\n");
    printf("�����ʽ����(>>Ҳ��������)��\n>>��\n>>�� ***\n>>�� ��������ѧԺ ����ΰ 126.670966 45.782211\n>>ɾ ***\n>>����\n>>����˵�\n>>�˳�\n");
}

// ����
void seekname(char name[N], const struct college c[N], int num, char yours[N], int *order)
{
    int flag = 1;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < c[order[i]].numpeo; j++)
        {
            if (strcmp(name, c[order[i]].name[j]) == 0)
            {
                flag = 0;
                printf("%s %s\n��γ��%lf��  ������%lf��\n����%s:%d km\n\n", c[order[i]].name_uni, c[order[i]].name[j], c[order[i]].wei, c[order[i]].jing, yours, (int)c[order[i]].dis);
            }
        }
    }
    if (flag == 1)
        printf("���޴��ˣ�\n\n");
}

// ����
void add(struct college c[], int *num, char uni[N], char name[N], FILE *in, int *order, int k)
{
    double dis;
    int i;
    if ((in = fopen("schools.txt", "w")) == NULL) //���ܴ��ļ�����
    {
        fprintf(stdout, "���ܴ�\"schools.txt\"�ļ���\n");
    }
    double jing, wei;
    int key = search(c, uni, *num, order);
    if (key == -1)
    {
        printf("����һ���´�ѧ�������뾭γ��\n");
        scanf("%lf%lf", &jing, &wei);
        while (getchar() != '\n')
            ;
        dis = greatCircleDistance(jing, wei, c[order[0]].jing, c[order[0]].wei);
        printf("%s", c[*num - 1].name_uni);
        for (i = 0; i < *num - 1; i++) //����
        {
            if (dis >= c[order[i]].dis && dis <= c[order[i + 1]].dis)
            {
                for (int j = *num; j > i + 1; j--)
                {
                    order[j] = order[j - 1];
                }
                break;
            }
        }
        order[i + 1] = *num;
        (*num)++;
        strcpy(c[order[i + 1]].name_uni, uni);
        c[order[i + 1]].jing = jing;
        c[order[i + 1]].wei = wei;
        strcpy(c[order[i + 1]].name[0], name);
        c[order[i + 1]].numpeo = 1;
        c[order[i + 1]].dis = dis;
        printf("%s", c[*num - 1].name_uni);
        printf("\n��Ӵ�ѧ�ɹ�\n\n�������¿������\n");
        menu();
        for (int i = 0; i < *num; i++)
        {
            fprintf(in, "%s %lf %lf ", c[order[i]].name_uni, c[order[i]].jing, c[order[i]].wei);
            for (int j = 0; j < c[order[i]].numpeo - 1; j++)
            {
                fprintf(in, "%s ", c[order[i]].name[j]);
            }
            fprintf(in, "%s\n", c[order[i]].name[c[order[i]].numpeo - 1]);
        }
    }
    else
    {
        strcpy(c[key].name[c[key].numpeo], name);
        c[key].numpeo += 1;
        printf("\n������ֳɹ�\n\n�������¿������\n");
        menu();
        for (int i = 0; i < *num; i++)
        {
            fprintf(in, "%s %lf %lf ", c[i].name_uni, c[i].jing, c[i].wei);
            for (int j = 0; j < c[i].numpeo - 1; j++)
            {
                fprintf(in, "%s ", c[i].name[j]);
            }
            fprintf(in, "%s\n", c[i].name[c[i].numpeo - 1]);
        }
    }
    fclose(in);
}

// ɾ
int delete (struct college c[N], int *num, FILE *out, char name[N], char yours[N], int order[N], int *key)
{
    out = fopen("schools.txt", "w");
    int i, j, k, l;
    for (i = 0; i < *num; i++)
    {
        for (j = 0; j < c[order[i]].numpeo; j++)
        {
            if (strcmp(c[order[i]].name[j], name) == 0)
            {
                for (k = j + 1; k < c[order[i]].numpeo; k++)
                {
                    strcpy(c[order[i]].name[k - 1], c[order[i]].name[k]);
                }
                c[order[i]].numpeo--;
                if (c[order[i]].numpeo == 0)
                {
                    for (k = i + 1; k < *num; k++)
                    {
                        // strcpy(c[order[k - 1]].name_uni, c[order[k]].name_uni);
                        // c[order[k - 1]].jing = c[order[k]].jing;
                        // c[order[k - 1]].wei = c[order[k]].wei;
                        // c[order[k - 1]].numpeo = c[order[k]].numpeo;
                        // for (l = 0; l < c[order[k]].numpeo; l++)
                        // {
                        //     strcpy(c[order[k - 1]].name[l], c[order[k]].name[l]);
                        // }
                        order[k - 1] = order[k];
                    }
                    (*num)--;
                    printf("%d\n", *num);
                    i--;
                    break;
                }
                j--;
            }
        }
    }
    for (i = 0; i < *num; i++)
    {
        fprintf(out, "%s %lf %lf ", c[order[i]].name_uni, c[order[i]].jing, c[order[i]].wei);
        for (j = 0; j < c[order[i]].numpeo - 1; j++)
        {
            fprintf(out, "%s ", c[order[i]].name[j]);
        }
        fprintf(out, "%s\n", c[order[i]].name[j]);
    }
    fclose(out);
}