#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

#define true 1
#define false 0
char youruni[30];
double yourlongtitude = 0, yourlatitude = 0;
static void CopyToNode(Item item, NODE * pnode);  //将某一学校信息写入某节点
extern char * s_gets(char * , int);
// 初始化链表
void InitializeList(List * plist)
{
    (*plist) = malloc(sizeof(NODE));
    (*plist)->next = NULL;
}

// 确定链表是否为空定义
int ListIsEmpty(const List * plist)
{
    if ((*plist)->next == NULL)
        return true;
    else
        return false;
}

// 确定链表项数
int ListItemNumber(const List * plist)
{
    int num = 0;
    NODE * pnode = (*plist)->next;
    while (pnode != NULL)
    {
        if (pnode->item.peonum != 0) num++;
        pnode = pnode->next;
    }
    return num;
}

// 确定链表是否已满
int ListIsFull(const List * plist)
{
    List pt;
    int full;

    pt = malloc(sizeof(NODE));
    if (pt == NULL)
        full = true;
    else
        full = false;
    free(pt);

    return full;
}

// 在链表末尾添加项(新大学)
int AddItem(Item item, List * plist)
{
    NODE * pnew;
    pnew = malloc(sizeof(NODE));
    if (pnew == NULL)
        return false;
    CopyToNode(item, pnew);
    NODE * ptail = *plist;
    while (ptail->next != NULL)
    {
        ptail = ptail->next;
    }
    ptail->next = pnew;

    return true;
}

// 在某个大学添加某人
int AddName(NODE * pnode, char name[15])
{
    if (pnode->item.peonum + 1 == 16)
        return false;
    else
    {
        strcpy((pnode->item).name_stu[pnode->item.peonum], name);
        pnode->item.peonum += 1;
        return true;
    }
}

// 添加大学item
void AddUni(List * plist)
{
    printf("数据中不含该大学信息，请添加完整,抱歉\n");
    printf("请输入姓名与大学的经纬度：");
    char name[15];
    double longtitude,latitude;
    while (scanf("%s%lf%lf", name, &longtitude, &latitude) != 3)
    {
        printf("请输入正确的格式，例如：张伟 110 30\n");
    }
    Item item;
    strcpy(item.name_uni, youruni);
    item.longitude = longtitude;
    item.latitude = latitude;
    item.peonum = 1;
    strcpy(item.name_stu[0], name);
    AddItem(item, plist);
}

//将某一学校信息写入某节点
void CopyToNode(Item item, NODE * pnode)
{
    pnode->item = item;
    pnode->next = NULL;
}

// 把函数作用于链表中的每一项
void Traverse(List * plist, void(*pfun)(Item *item))
{
    NODE * ptail = (*plist);
    while (ptail != NULL)
    {
        (*pfun)(&(ptail->item));
        ptail = ptail->next;
    }
}

// 释放已分配的内存
void EmptyTheList(List * plist)
{
    NODE * pnode = (*plist)->next;

    while (pnode != NULL)
    {
        (*plist) = pnode->next;
        free(pnode);
        pnode = (*plist);
    }
}

// 按每个节点的dis进行从小到大排序
void SortList(List * plist)
{
    NODE * pnode,* pbefore;
    int num = ListItemNumber(plist);
    for (int i = 0; i < num-1; i++)
    {
        pnode = (*plist)->next;
        pbefore = (*plist);
        while (pnode != NULL && pnode->next != NULL)
        {
            if (pnode->item.dis > pnode->next->item.dis)
            {
                NODE * pt = pnode->next;
                pnode->next = pnode->next->next;
                pbefore->next = pt;
                pt->next = pnode;
            }
            else
            {
                pnode = pnode->next;
                pbefore = pbefore->next;
            }
        }
        
    }
}

// 将链表打印
void PrintList(List * plist)
{
    (*plist) = (*plist)->next;
    while ((*plist) != NULL)
    {
        if ((*plist)->item.peonum != 0)
        {
            printf("%20s%5lfkm    ",(*plist)->item.name_uni,(*plist)->item.dis);
            for (int i = 0; i< (*plist)->item.peonum-1; i++)
            {
                printf("%s ",(*plist)->item.name_stu[i]);
            }
            printf("%s\n",(*plist)->item.name_stu[(*plist)->item.peonum-1]);
        }
        (*plist) = (*plist)->next;
    }
}

// 逐一比对大学名称
NODE * Judgeuni(List * plist, char uni[30])
{
    NODE * pnode = (*plist)->next;
    while (pnode != NULL)
    {
        if (strcmp(pnode->item.name_uni, uni) == 0)
        {
            return pnode;
        }
        pnode = pnode->next;
    }
    return NULL;
}

// 查询某人
NODE * Seeksb(List *plist, char name[15])
{
    NODE * pnode = (*plist)->next;
    while (pnode != NULL)
    {
        for (int i = 0; i < pnode->item.peonum; i++)
        {
            if (strcmp(pnode->item.name_stu[i], name) == 0)
            {
                return pnode;
            }
        }
        pnode = pnode->next;
    }
    return NULL;
}

// 删除某人
void  DeleteName(List *plist, char name[15])
{
    NODE * aimnode;
    if ((aimnode = Seeksb(plist, name))== NULL)
    {
        printf("没有这个人");
        return ;
    }
    if ((strcmp(aimnode->item.name_uni, youruni) == 0) && (aimnode->item.peonum == 1) && (strcmp(aimnode->item.name_stu[0], name)))
    {
        printf("这是你所在的学校，不可以删完所有的同学。");
        return ;
    }
    if ((aimnode->item.peonum == 1) && (strcmp(aimnode->item.name_stu[0], name) == 0))
    {
        printf("该学校只有一个人，如果删除，该学校信息也将被删除，你愿意吗？(y/n):");
        char option[5];
        fgets(option, 5, stdin);
        while (1)
        {
            if (strcmp(option, "y\n") == 0)
            {
                printf("好吧，哎～\n");
                strcpy(aimnode->item.name_stu[0], "");
                aimnode->item.peonum = 0;
                DeleteNode(plist, aimnode);
            }
            else if (strcmp(option, "n\n") == 0)
            {
                printf("你真好~\n");
            }
            else
            {
                printf("请重新输入命令y/n:");
                fgets(option, 5, stdin);
            }
        }
    }
    else
    {
        for (int i = 0; i < aimnode->item.peonum; i++)
        {
            if (strcmp(aimnode->item.name_stu[i], name) == 0)
            {
                for (int j = i+1; j <aimnode->item.peonum; j++)
                {
                    strcpy(aimnode->item.name_stu[j-1], aimnode->item.name_stu[j]);
                }
                aimnode->item.peonum -= 1;
                printf("删除成功\n");
            }
        }
    }
}

// 删除某节点
void DeleteNode(List * plist, NODE * pnode)
{
    NODE * p = (*plist);
    while (p->next != pnode)
    {
        p = p->next;
    }
    p->next = pnode->next;
    free(pnode);
}

// 将链表写入文件
void PrintIntoFile(List * plist)
{
    FILE * in = NULL;
    if ((in = fopen("schools.txt", "w")) == NULL)
    {
        printf("打开文件失败\n");
    }
    int num = ListItemNumber(plist);
    NODE * pnode = (*plist)->next;
    for (int i = 0; i < num; i++)
    {
        fprintf(in, "%s ", pnode->item.name_uni);
        for (int j = 0; j < pnode->item.peonum; j++)
        {
            fprintf(in, "%s ", pnode->item.name_stu[j]);
        }
        fprintf(in, "%lf %lf\n", pnode->item.longitude, pnode->item.latitude);
    }
    fclose(in);
}

// 计算距离
void CalculateDis(Item *item)
{
    item->dis = greatCircleDistance(item->longitude, item->latitude, yourlongtitude, yourlatitude);
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

// 读入文件
void Input(List * plist)
{
    FILE * in = NULL;
    in = fopen("schools.txt", "r");
    if (in  == NULL)
    {
        printf("未能成功打开文件\n");
        exit(0);
    }
    char nameuni[30];
    char name[15];
    int num = 0;
    while (fscanf(in, "%s", nameuni) != EOF)
    {
        Item item;
        num = 0;
        strcpy(item.name_uni, nameuni);
        while (fscanf(in, "%s", name))
        {
            strcpy(item.name_stu[num], name);
            num++;
        }
        fscanf(in, "%lf%lf", &item.longitude, &item.latitude);
        item.peonum = num;
        if (AddItem(item, plist) == 0)
        {
            printf("节点添加失败\n");
            exit(0);
        }
    }
    UpdateUni(plist);
    fclose(in);
}

// 更新所在大学名称
void UpdateUni(List * plist)
{
    while (1)
    {
        int flag = 0;
        printf("你所在的大学：");
        scanf("%s", youruni);
        printf("确定吗？(y/n)");
        while (1)
        {
            char option[5];
            fgets(option, 5, stdin);
            if (strcmp(option,"y\n") == 0)
            {
                flag = 1;
                break;
            }
            else if (strcmp(option, "n\n") == 0)
            {
                flag = 0;
                break;
            }
            else
            {
                printf("请重新输入命令(y/n)：");
            }
        }
        if (flag) break;
    }

    NODE * yours = Judgeuni(plist, youruni);
    if (yours == NULL)
    {
        AddUni(plist);
        yours = Judgeuni(plist, youruni);
    }
    yourlongtitude = yours->item.longitude;
    yourlatitude = yours->item.latitude;
    Traverse(plist, CalculateDis);
    SortList(plist);
}

// 显示菜单
void Menu(void)
{
    printf("你有如下命令可用:\n");
    printf("列：   列出当前储存的所有学校与同学信息，按照与你的学校的距离从近到远排列\n");
    printf("查:    查询你所输入的学生信息\n");
    printf("增：   增加某同学，如果该同学所在的学校在数据库中存在，则自动添加；否则要求输入该学校的经纬度\n");
    printf("删：   删除某同学\n");
    printf("help：   显示该菜单\n");
    printf("清屏：   清空屏幕，让你的屏幕更加简洁\n");
    printf("更新：    更新你所在的大学");
    printf("退出：   保存并退出");
    printf("请输入你的命令：");
}

// 保存并退出程序
void Exit(List * plist)
{
    PrintIntoFile(plist);
    printf("文件已成功保存，欢迎下次使用～");
    exit(0);
}

// 列
void print(List * list)
{
    PrintList(list);
    PrintIntoFile(list);
    printf("可继续输入命令（不知道请输入“help”）:");
}

// 查
void seek(List * list)
{
                char name[15];
                do
                {
                    if (s_gets(name, 15) == NULL || name[0] == '\0')
                        ;
                    else
                    {
                        NODE * pnode;
                        if ((pnode = Seeksb(list, name)) == NULL)
                            printf("未查询到%s\n", name);
                        else
                        {
                            printf("%s %s\n",name, pnode->item.name_uni);
                            printf("经度：%lf 纬度：%lf\n", pnode->item.longitude, pnode->item.latitude);
                            printf("距离%s: %lf km\n\n", youruni, pnode->item.dis);
                        }
                        printf("是否继续查询同学，y/n?:");
                        char option[5];
                        int flag = 0;
                        do
                        {
                            if (s_gets(option, 5) == NULL || option[0] == '\0')
                                ;
                            else if (strcmp(option, "n") == 0)
                            {
                                flag = 1;
                                break;
                            }
                            else if (strcmp(option, "y") == 0)
                            {
                                break;
                            }
                            else
                            {
                                printf("请输入正确的指令y/n：");
                            }
                            
                        } while (1);
                        if (flag) break;
                    }
                } while (1);
                printf("可继续输入命令（不知道请输入“help”）：");
}

// 增
void add(List * list)
{
                printf("请输入同学姓名与大学:");
                do
                {
                    char nameuni[30], name[15];
                    while (scanf("%s%s", name, nameuni) != 2)
                    {
                        while (getchar() != '\n')
                            ;
                        printf("请重新输入\n");
                    }
                    NODE * pnode = Seeksb(list, name);
                    if (pnode == NULL)
                    {
                        NODE * aimnode = Judgeuni(list, nameuni);
                        if (aimnode == NULL)
                        {
                            printf("数据中不含%s信息，请添加完整,抱歉\n", nameuni);
                            printf("请输入该大学经纬度：");
                            double longtitude, latitude;
                            while (scanf("%lf%lf", &longtitude, &latitude) != 2 || longtitude > 180 || longtitude < 0 || latitude > 90 || latitude < 0)
                            {
                                while (getchar() != '\n')
                                    ;
                                printf("请输入正确的经纬度，经度大于0小于180，纬度大于0小于90\n");
                            }
                            Item item;
                            strcpy(item.name_uni, nameuni);
                            strcpy(item.name_stu[0], name);
                            item.peonum = 1;
                            item.longitude = longtitude;
                            item.latitude = latitude;
                            CalculateDis(&item);
                            AddItem(item, list);
                            SortList(list);
                            printf("添加成功\n");
                        }
                        else
                        {
                            if (AddName(pnode, name))
                            {
                                printf("添加成功");
                            }
                            else
                            {
                                printf("添加失败，每个学校最多15人");
                            }
                        }
                        
                    }
                    else
                    {
                        printf("该同学已存在，是否输出ta的信息?(y/n)\n");
                        char option[5];
                        do
                        {
                            if (s_gets(option, 5) == NULL || option[0] == '\0')
                                ; 
                            else if (strcmp(option, "y") == 0)
                            {
                                printf("%s %s\n",name, pnode->item.name_uni);
                                printf("经度：%lf 纬度：%lf\n", pnode->item.longitude, pnode->item.latitude);
                                printf("距离%s: %lf km\n\n", youruni, pnode->item.dis);
                                break;
                            }
                            else if (strcmp(option, "n") == 0)
                            {
                                printf("好吧～\n");
                                break;
                            }
                            else
                            {
                                printf("请输入正确的指令y/n：");
                            }
                        } while (1);
                    }
                    printf("是否继续添加同学，y/n?:");
                    char option[5];
                    int flag = 0;
                    do
                    {
                        if (s_gets(option, 5) == NULL || option[0] == '\0')
                            ;
                        else if (strcmp(option, "n") == 0)
                        {
                            flag = 1;
                            break;
                        }
                        else if (strcmp(option, "y") == 0)
                        {
                            break;
                        }
                        else
                        {
                            printf("请输入正确的指令y/n：");
                        }
                        
                    } while (1);
                    if (flag) break;
                } while (1);
                printf("可继续输入命令（不知道请输入“help”）：");
}

// 删
void delete(List * list)
{
    printf("请输入你要删除的同学：");
    char name[15];
    do
    {
                    if (s_gets(name, 15) == NULL || name[0] == '\0')
                        ;
                    else
                    {
                        DeleteName(list, name);
                        printf("是否继续删除同学，y/n?:");
                        char option[5];
                        int flag = 0;
                        do
                        {
                            if (s_gets(option, 5) == NULL || option[0] == '\0')
                                ;
                            else if (strcmp(option, "n") == 0)
                            {
                                flag = 1;
                                break;
                            }
                            else if (strcmp(option, "y") == 0)
                            {
                                break;
                            }
                            else
                            {
                                printf("请输入正确的指令y/n：");
                            }
                            
                        } while (1);
                        if (flag) break;
                    }
    } while (1);
    printf("可继续输入命令（不知道请输入“help”）：");
}