/*程序进入时首先显示帮助信息，在帮助信息的提示下，不断完成以下功能，直到退出
列出帮助信息
列：列出所有学生信息，要求使用排序方法按距离中国科学技术大学由近到远列出所有学生信息（4分）
查：查询某个学生信息，根据输入学生姓名来查询得到学生的以下信息【学生姓名】、【输入大学】、【输入大学经纬度】、【距离中国科大距离】（4分）
增：根据输入的信息添加学生，如果输入学校经纬度存在于文件中国部分大学位置信息的话，直接添加，不存在的话，要求添加经纬度信息；使用【列】功
能查看增加的学生是否成功（4分）
删：根据输入的学生姓名删除学生信息；使用【列】功能查看删除的学生是否成功（4分）
退出：退出并保存所有学生信息到文件里，这里助教会检查添加和删除的信息是否保存成功。保存的信息包括【学生姓名】、【学生输入学校】、【输入学校
经纬度信息】（4分）
bonus加分，有助教认为的新功能或者良好的交互形式会酌情加分，用结构体链表会倾向于加分。*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
struct college //储存大学信息
{
    char name_uni[N]; //大学名称
    double jing;      //大学经度
    double wei;       //大学纬度
    char name[N][20]; //大学同学名字
    double dis;       //大学距离
    int numpeo;       //同学人数
};
// 排序
void sort(struct college c[N], int *num, int order[N]);
// 读入文件与开始菜单
FILE *begin(struct college c[N], int *num, int order[N]);
// 输入自己的大学
int your(struct college c[N], int *, FILE *, char yours[], int *order, int *key);
// 删
int delete (struct college c[N], int *num, FILE *out, char name[N], char yours[N], int order[N], int *key);
// 增加
void add(struct college c[], int *, char uni[], char name[], FILE *, int *order, int k);
// 查人
void seekname(char[], const struct college c[], int num, char yours[N], int order[N]);
// 命令菜单显示
void menu(void);
// 查找有无大学
int search(const struct college c[], char yours[N], int num, int *order);
// 下面三个计算距离
double deg2rad(double deg);
double greatCircleDistance(double long1, double lat1, double long2, double lat2);
void dis(struct college c[], int num, int key);
// 排序与列
void output(const struct college c[], int order[N], int *num);

int main(int argc, char *argv[])
{
    int num = 0, key = -1, i, j, t, flag, a, back;
    char ch; //输入姓名所用
    char command[N], name[N], uni[N], yours[N];
    struct college c[N];
    int order[N] = {0};  //记录大学距离远近排名的下标
    int flagcommand = 1; //命令行跳出标志
    double jing, wei;
    FILE *in;
    // 读入文件与开始菜单
    printf("123");
    in = begin(c, &num, order);
    // 必须先输入大学
    a = your(c, &num, in, yours, &order[0], &key);
    sort(c, &num, order);
    if (a == 1)
        return 0;

    flagcommand = 1;
    // 判断执行命令区
    while (flagcommand)
    {
        scanf("%s", command);
        if (strcmp(">>列", command) == 0 || strcmp("列", command) == 0 || strcmp("》》列", command) == 0)
        {
            // 列
            output(c, order, &num);
        }
        else if (strcmp(">>查", command) == 0 || strcmp("查", command) == 0 || strcmp("》》查", command) == 0)
        {
            // 查
            scanf("%s", name); //command用作name，节省内存空间
            seekname(name, c, num, yours, &order[0]);
        }
        else if (strcmp(">>退出", command) == 0 || strcmp("退出", command) == 0 || strcmp("》》退出", command) == 0)
        {
            // 退出
            flagcommand = 0;
        }
        else if (strcmp(">>增", command) == 0 || strcmp("增", command) == 0 || strcmp("》》增", command) == 0)
        {
            // 增
            scanf("%s%s", uni, name);
            while (getchar() != '\n')
                ;
            add(c, &num, uni, name, in, order, key);
        }
        else if (strcmp("命令菜单", command) == 0 || strcmp(">>命令菜单", command) == 0 || strcmp("》》命令菜单", command) == 0)
        {
            // 命令菜单
            menu();
        }
        else if (strcmp("删", command) == 0 || strcmp(">>删", command) == 0 || strcmp("》》删", command) == 0)
        {
            // 删
            scanf("%s", name);
            while (getchar() != '\n')
                ;
            back = delete (c, &num, in, name, yours, &order[0], &key);
            printf("%d\n", num);
            if (back == 1)
            {
                printf("您输入的大学已经没有同学了，无法测算距离，请更新大学或者增加回同学或者退出\n");
                flagcommand = 1;
                while (flagcommand)
                {
                    scanf("%s", command);
                    if (strcmp(">>退出", command) == 0 || strcmp("退出", command) == 0 || strcmp("》》退出", command) == 0)
                    {
                        // 退出
                        flagcommand = 0;
                    }
                    else if (strcmp(">>增", command) == 0 || strcmp("增", command) == 0 || strcmp("》》增", command) == 0)
                    {
                        // 增
                        scanf("%s%s", uni, name);
                        while (getchar() != '\n')
                            ;
                        add(c, &num, uni, name, in, order, key);
                        //  a = your(c, &num, in, yours);
                        break;
                    }
                    // else if (strcmp(">>更新", command) == 0 || strcmp("更新", command) == 0 || strcmp("》》更新", command) == 0)
                    // {
                    //     a = your(c, &num, in, yours);
                    //     break;
                    // }
                    else
                    {
                        printf("命令不合法，请重新输入\n");
                    }
                }
            }
            else
            {
            }
        }
        // else if (strcmp(">>更新", command) == 0 || strcmp("更新", command) == 0 || strcmp("》》更新", command) == 0)
        // {
        //     a = your(c, &num, in, yours);
        // }
        else
        {
            printf("命令不合法，请重新输入\n");
        }
    }
    printf("文件以保存！再见！");
    fclose(in);
    return 0;
}
// 读入文件与开始菜单
FILE *begin(struct college c[N], int *num, int *order)
{
    int key = -1, i, j, t, flag;
    char ch; //输入姓名所用
    char yours[N], command[N], name[N], uni[N];
    int flagcommand = 1; //命令行跳出标志
    double jing, wei;
    FILE *in;
    if ((in = fopen("schools.txt", "r")) == NULL) //不能打开文件处理
    {
        fprintf(stdout, "不能打开\"schools.txt\"文件。\n");
    }
    fscanf(in, "%s%lf%lf", c[*num].name_uni, &c[*num].jing, &c[*num].wei);
    do //文件读入
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
        while ((ch = getc(in)) != '\n') //读人名
        {
            if (ch == ' ') //第一次必读空格或者\n        ???
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
    printf("领军幼儿园全国蹭饭终端0.0.1\n");
    printf("Copyleft 2019 李清伟\n");
    printf("欢迎使用领军幼儿园全国蹭饭终端！\n");
    for (i = 0; i < *num; i++)
    {
        order[i] = i;
    }
    return in;
    fclose(in);
}
// 输入自己的大学
int your(struct college c[N], int *num, FILE *in, char yours[N], int *order, int *key)
{
    int i, j, t, flag, a;
    char ch; //输入姓名所用
    char command[N], name[N], uni[N];
    int flagcommand = 1; //命令行跳出标志
    double jing, wei;
    printf("您输入的大学是：");
    scanf("%s", yours); //你的大学是？
    while (getchar() != '\n')
        ;
    // 看看有没有这个大学
    *key = search(c, yours, *num, order);
    if (*key == -1) //没有这个大学
    {
        printf("\n抱歉，并没有查找到你输入的 %s。\n对此，有以下命令：\n", yours);
        printf("增 [学校] [姓名]([学校经度] [学校纬度]) ：增加同学，如果该学校尚未登记，将要求您输入学校经纬度\n");
        printf("更新：更新输入大学名字\n");
        printf("退出：退出程序\n");
        printf("输入格式如下：\n>>增 哈尔滨佛学院 *** (126.670966 45.782211)(输入经纬度时括号不必输入)\n(查询经纬度网站：http://api.map.baidu.com/lbsapi/getpoint/index.html)\n>>更新\n>>退出\n");
        while (flagcommand)
        {
            scanf("%s", command);
            while (getchar() != '\n')
                ;
            if (strcmp(">>退出", command) == 0 || strcmp("退出", command) == 0 || strcmp("》》退出", command) == 0)
            {
                printf("欢迎下次使用！再见！");
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(">>增", command) == 0 || strcmp("增", command) == 0 || strcmp("》》增", command) == 0)
            {
                scanf("%s%s", uni, name);
                add(c, num, uni, name, in, order, *key);
                dis(c, *num, *key);
                *key = search(c, uni, *num, order);
                flagcommand = 0;
            }
            // else if (strcmp(">>更新", command) == 0 || strcmp("更新", command) == 0 || strcmp("》》更新", command) == 0)
            // {
            //     a = your(c, num, in, yours);
            // }
            else
            {
                printf("命令不合法，请重新输入\n");
            }
        }
    }
    else //有这个大学
    {
        printf("你输入的 %s 存在，有以下可用命令:\n", yours);
        menu();
    }
    dis(c, *num, *key); //算距离
    return 0;
}
// 下面三个计算距离
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
// 排序
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
// 列
void output(const struct college c[], int order[N], int *num)
{
    int i, j, t;
    FILE *out;
    out=fopen("schools.txt","w");
    printf("列：\n");
    printf("%-22s   %5s %15s\n", "大学名称", "距离", "同学");
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

// 查大学
int search(const struct college c[], char yours[N], int num, int order[N])
{
    // 查一下有这个大学吗
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
        return order[i]; //有，返回下标
        printf("%d\n", order[i]);
    }
    else
        return -1; //没有，返回-1
}

// 命令菜单显示
void menu(void)
{
    printf("\n列：按照距离你输入的大学由近及远排列大学，并列出该校的同学，方便蹭饭\n");
    printf("查 [姓名]：查询该同学输入学校及其经纬度以及距离你学校的距离\n");
    printf("增 [学校] [姓名] ([学校经度] [学校纬度])：增加同学，如果该学校尚未登记，将要求您输入学校经纬度\n");
    printf("删 [姓名]：删除同学信息\n");
    printf("更新：更新输入大学名字\n");
    printf("命令菜单：显示所有可用命令信息\n");
    printf("退出：退出程序\n");
    printf("输入格式如下(>>也包括在内)：\n>>列\n>>查 ***\n>>增 哈尔滨佛学院 李清伟 126.670966 45.782211\n>>删 ***\n>>更新\n>>命令菜单\n>>退出\n");
}

// 查人
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
                printf("%s %s\n北纬：%lf度  东经：%lf度\n距离%s:%d km\n\n", c[order[i]].name_uni, c[order[i]].name[j], c[order[i]].wei, c[order[i]].jing, yours, (int)c[order[i]].dis);
            }
        }
    }
    if (flag == 1)
        printf("查无此人！\n\n");
}

// 增加
void add(struct college c[], int *num, char uni[N], char name[N], FILE *in, int *order, int k)
{
    double dis;
    int i;
    if ((in = fopen("schools.txt", "w")) == NULL) //不能打开文件处理
    {
        fprintf(stdout, "不能打开\"schools.txt\"文件。\n");
    }
    double jing, wei;
    int key = search(c, uni, *num, order);
    if (key == -1)
    {
        printf("这是一个新大学，请输入经纬度\n");
        scanf("%lf%lf", &jing, &wei);
        while (getchar() != '\n')
            ;
        dis = greatCircleDistance(jing, wei, c[order[0]].jing, c[order[0]].wei);
        printf("%s", c[*num - 1].name_uni);
        for (i = 0; i < *num - 1; i++) //插排
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
        printf("\n添加大学成功\n\n现有以下可用命令：\n");
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
        printf("\n添加名字成功\n\n现有以下可用命令：\n");
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

// 删
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