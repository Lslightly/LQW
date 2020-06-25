#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct college //储存大学信息
{
    char name_uni[100]; //大学名称
    double jing;        //大学经度
    double wei;         //大学纬度
    char name[100][20]; //大学同学名字
    double dis;         //大学距离
    int numpeo;         //同学人数
    struct college *next;
};
static double stdjing, stdwei;
typedef struct college C;
void begin(C *head, int *num);
int search(C *head, int *num, char[]); //搜大学
double deg2rad(double deg);
double greatCircleDistance(double long1, double lat1, double long2, double lat2);
// 命令菜单显示
void menu(void);
void output(C *head, int *num);
void add(C *head, int *num);
void seekname(C *head, int *num); //“查”专用
void delete (C *head, int *num);
int main(void)
{
    printf("领军幼儿园全国蹭饭终端0.0.1\n");
    printf("Copyleft 2019 李清伟\n");
    printf("欢迎使用领军幼儿园全国蹭饭终端！\n");
    int num = 0;
    int flagcommand = 1; //命令行跳出标志
    char command[100], ch;
    C *head, *p;                   //头节点
    head = (C *)malloc(sizeof(C)); //创建头节点
    if (head == NULL)              //创建失败,则返回
    {
        printf("no enough memory!\n");
        exit(0);
    }
    head->next = NULL; //头节点的指针域置NULL
    begin(head, &num);

    menu();
    p = head;
    while (flagcommand)
    {
        scanf("%s", command);
        while ((ch = getchar()) != '\n')
            ;
        if (strcmp(">>列", command) == 0 || strcmp("列", command) == 0 || strcmp("》》列", command) == 0)
        {
            // 列
            output(head, &num);
        }
        else if (strcmp(">>查", command) == 0 || strcmp("查", command) == 0 || strcmp("》》查", command) == 0)
        {
            // 查
            printf("请输入您要查找的同学(每次最多查90人，以enter为结束符)：");
            seekname(head, &num);
        }
        else if (strcmp(">>退出", command) == 0 || strcmp("退出", command) == 0 || strcmp("》》退出", command) == 0)
        {
            // 退出
            flagcommand = 0;
        }
        else if (strcmp(">>增", command) == 0 || strcmp("增", command) == 0 || strcmp("》》增", command) == 0)
        {
            // 增
            printf("请输入大学名称与同学姓名：\n");
            add(head, &num);
        }
        else if (strcmp("命令菜单", command) == 0 || strcmp(">>命令菜单", command) == 0 || strcmp("》》命令菜单", command) == 0)
        {
            // 命令菜单
            menu();
        }
        else if (strcmp("删", command) == 0 || strcmp(">>删", command) == 0 || strcmp("》》删", command) == 0)
        {
            // 删
            printf("请输入你要删除的同学：");
            delete (head, &num);
        }
        else
        {
            printf("命令不合法，请重新输入\n不知道命令请输入“命令菜单”\n\n");
        }
    }
    printf("文件以保存！再见！");
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
    if ((in = fopen("schools.txt", "r")) == NULL) //不能打开文件处理
    {
        fprintf(stdout, "不能打开\"schools.txt\"文件。\n");
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
int search(C *head, int *num, char yours[1000]) //查大学有无
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
// 命令菜单显示
void menu(void)
{
    printf("\n列：由近及远排列大学，方便蹭饭\n");
    printf("查：查询该同学的学校及其经纬度以及距离科大的距离\n");
    printf("增：增加同学，如果该学校尚未登记，将要求您输入学校经纬度\n");
    printf("删：删除所有同名同学信息\n");
    // printf("更新：更新输入大学名字\n");
    printf("命令菜单：显示所有可用命令信息\n");
    printf("退出：退出程序\n");
    printf("\n注意：在输入命令时只需输入\"命令\"即可\n\n");
}

void output(C *head, int *num)
{
    C *p;
    p = head;
    int i, j;
    printf("列：\n");
    printf("%-22s   %5s      人数%9s\n", "大学名称", "距离", "同学");
    printf("-----------------------------------------------------\n");
    for (i = 0; i < *num; i++)
    {
        p = p->next;
        printf("%-22s %5d km     %-2d%s     ", p->name_uni, (int)p->dis, p->numpeo, "人");
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
        printf("请重新输入“增”命令并在大学后加空格输入姓名\n\n");
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
                printf("对不起，一次只能增一人且只增第一人\n");
                while ((ch = getchar()) != '\n')
                    ;
            }
        }
    }
    if ((key = search(head, num, yours)) != 0) //有这个大学
    {
        for (int i = 0; i < key; i++)
        {
            p = p->next;
        }
        strcpy(p->name[p->numpeo], name);
        p->numpeo++;
        printf("添加新同学成功\n\n");
    }
    else
    {
        printf("这是一个新大学，请输入经纬度\n");
        while (scanf("%lf%lf", &jing, &wei) != 2 || (jing > 180 || wei > 90 || jing < 0 || wei < 0))
        {
            printf("请输入正确的数值\n");
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
        printf("添加新大学成功\n\n");
    }

    FILE *out;
    int i, k;
    p = head;
    if ((out = fopen("schools.txt", "w")) == NULL)
    {
        printf("不能打开schools.txt文件\n请联系软件开发者");
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
    int i, j = 0, k, flag = 1, sum = 0; //sum为要查人数
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
                    printf("%s %s\n北纬：%lf度  东经：%lf度\n距离科大:%d km\n\n", p->name_uni, p->name[j], p->wei, p->jing, (int)p->dis);
                }
            }
        }
        if (flag == 1)
        {
            printf("没有%s！\n\n", name[k]);
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
        while ((ch = getchar()) == ' ' && ch != '\n') //一连串空格加\n
            ;
        if (ch == '\n')
        {
            printf("请重新输入“删”命令并输入姓名\n");
            return;
        }
        else
        {
            scanf("%s", name);
        }
    }
    else if (ch == '\n')
    {
        printf("请重新输入“删”命令并输入姓名\n");
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
                printf("对不起，一次只能删一人且只删第一人\n");
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
        printf("没有这个同学\n\n");
    }
    else
    {
        printf("删除成功\n\n");
    }

    FILE *out;
    p = head;
    if ((out = fopen("schools.txt", "w")) == NULL)
    {
        printf("不能打开schools.txt文件\n请联系软件开发者");
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