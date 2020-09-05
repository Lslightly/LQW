#ifndef LIST_H_
#define LIST_H_

#define STUSIZE 15
typedef struct college
{
    double longitude;
    double latitude;
    char name_uni[30];
    char name_stu[STUSIZE][10];
    double dis;
    int peonum;
} Item;

typedef struct node
{
    Item item;
    struct node * next;
} NODE;

typedef NODE * List;


/*函数原型*/

/*操作：    初始化一个链表
  前提：    plist指向一个链表
  后置：    链表初始化为空*/
void InitializeList(List * plist);

/*操作：        确定链表是否为空定义，plist指向一个已初始化的链表
  后置条件：    如果链表为空，则返回true; 否则返回false */
int ListIsEmpty(const List * plist);

// 操作：       确定链表项数，plist指向一个已初始化的链表
// 后置条件:    返回项数(除head节点)
int ListItemNumber(const List * plist);

// 操作：       确定链表是否已满，plist指向一个已初始化的链表
// 后置条件：   如果已满，返回True；否则返回False
int ListIsFull(const List * plist);

// 操作：   在链表末尾添加项(新大学)
// 前置条件：   item是一个待添加的项，plist指向一个已初始化的链表
// 后置条件：   如果可以，该函数返回True，否则返回False
int AddItem(Item item, List * plist);

// 操作：   在某个大学添加某人
// 前置条件：   pnode指向一个已初始化的节点，name为添加同学的名字
// 后置条件：   如果添加成功，该函数返回True；否则返回False 
int AddName(NODE * pnode, char name[15]);

// 操作：   添加大学item
void AddUni(List * plist);

// 操作：   把函数作用于链表中的每一项
//         plist指向一个已初始化的链表
//         pfun指向一个函数，该函数接受一个Item类型的参数，无返回值
// 后置条件：   pfun指向的函数作用于链表中的每一项一次
void Traverse(List * plist, void(*pfun)(Item * item));

// 操作：   释放已分配的内存(如果有的话)
//         plist指向一个已初始化的链表
// 后置条件：   释放了已分配的内存，链表设置为只有head节点
void EmptyTheList(List * plist);

// 操作：   按每个节点的dis进行从小到大排序
//         plist指向一个已初始化的链表
// 后置条件：   链表按每个节点的dis进行排序
void SortList(List * plist);

// 操作：   将链表打印
//          plist指向一个已初始化的链表
// 后置条件：   按一定格式输出链表
void PrintList(List * plist);

// 操作：   逐一比对大学名称
//          plist指向一个已初始化的链表
//          uni为大学名称
// 后置条件：   存在这个大学，返回该大学所在节点指针；否则返回NULL
NODE * Judgeuni(List * plist, char uni[30]);

// 操作：   查询某人
//         plist指向一个已初始化的链表
//         name为一个人的姓名
// 后置条件：   存在这个人，返回这个人所在大学的节点指针；否则返回NULL
NODE * Seeksb(List *plist, char name[15]);

// 操作：   删除某人
//         plist指向一个已初始化的链表
//         name为一个人的姓名
// 后置条件：   若删了这个人之后他所在的大学人数>0，则输出删除成功；否则，若他所在的大学人数=0，若他所在的大学为你所在的大学，则输出“不能删除”，否则输出“删除成功”并删除那个节点
void  DeleteName(List *plist, char name[15]);

// 操作：   删除某节点
//          该节点非头节点
// 后置条件：   删除该节点并重连链表，输出“删除**大学成功”
void DeleteNode(List * plist, NODE * pnode);

// 操作：    将链表写入文件
// 后置条件：   schools文件被修改
void PrintIntoFile(List * plist);

// 操作:    计算距离
// 后置条件：   将距离写入链表中
void CalculateDis(Item *item);
double deg2rad(double deg);
double greatCircleDistance(double long1, double lat1, double long2, double lat2);

// 操作：   读入文件
// 后置条件：   将信息储存至链表中
void Input(List * plist);

// 操作：   更新所在大学名称
// 后置条件：   重置距离
void UpdateUni(List * plist);

// 操作：   显示菜单
void Menu(void);

// 操作：   保存并退出程序
void Exit(List * plist);

// 操作：列
void print(List * list);

// 操作：查
void seek(List * list);

// 操作：增
void add(List * list);

// 操作：删
void delete(List * list);


#endif