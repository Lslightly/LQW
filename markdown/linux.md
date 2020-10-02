## ls:
* 列出文件与文件夹，其中蓝色为文件夹，白色为文件,绿色拥有所有权限，可读可写...
* “/”表示根目录下（绝对路径），没有表示相对路径
* ./当前  ../表示上一级目录 /表示根目录
* ls -l 以详细列表形式列出
* ls -la (list all)列出包括隐藏文件的文件与文件夹，隐藏文件以“.”开头
* ls -lh 将文件大小以合适的方式列出，与 ls -l 差不多
* 详细列出的list中第一列中
  * ``-``代表文件，``d``代表文件夹
  * 后面有三组``rwx``分别表示用户，用户组，其他人的读、写、运行权限
    * ``r``代表读
    * ``w``代表写，修改
    * ``x``代表运行
    * ``-``代表没有该权限
    * 对于``d``文件夹，``x``表示能够进入文件夹，``w``表示可在该目录下进行写入操作，``r``表示可以查看该目录（仅该目录，不包括内部）的信息
## pwd
* 当前位置
## cd
* change directory
* 语法与ls相似
* cd ~到home/***处
* "./" "../" "/"可用
* ``cd -``回到之前的位置
## mkdir
* 创建文件夹
* 一起创建 mkdir -p files/a/b/c/d
## touch
* 创建新文件
* touch a.txt /home/name/b.txt
## cp
* copy
* cp /home/name/a.txt /home/ (名字不变)
* cp a.txt /home/name/b.txt(可重新命名)
* (复制文件夹)cp *-r* a /home/name/b(复制a文件夹至...并命名为b)
## mv
* 移动、重命名
* mv a.txt /b.txt(移动至根目录并重命名)
## rm
* rm: 移除文件(有提示)
* rm -f(force,强制移除文件，无提示)
* rm -rf(强制移除文件夹里的所有内容)
* *表示若干个字符
## cat
* 直接打开一个文件
* cat (路径)
* 文件合并
* cat (路径) (路径)...(路径) > (路径) 合并到一个文件
## 输出重定向
* /> 覆盖输出至某文件
* />>: 末尾追加输出至某文件
# linux进阶操作
## df
* 查看磁盘空间
* df -h(有空间大小换算的显示方法)
## free
* 查看内存使用情况
* free -m(以MB为单位显示内存占用情况)
* free -g(以GB为单位显示内存使用情况)
* free(以KB为单位显示内存使用情况)
## head
* 查看一个文件的前n行，不指定则默认显示前10行
* head -n (路径)(n为数字)
## tail
* 查看一个文件的末n行，不指定则默认显示后10行
* tail -n (路径)(n为数字)
* 查看一个文件的动态变化(系统日志)
* tail -f (路径)
## less
* 查看文件，以较少的内容进行输出
* less (路径)
* 数字：跳转到第几行
* 空格键：翻页
* 上下：上一行，下一行
## wc
* 统计文件内容信息(包括行数、单词数、字节数)
* wc -lwc (路径)
    - l:行数
    - w:单词数(依照空格判断单词数量)
    - c:字节数
## date
* 操作时间与日期(读取、设置)，shel脚本
* date
* date +%F <=> date "+%Y-%m-%d"(年月日)
* date '+%F %T'(年月日时分秒)(引号视为整体) <=> date '+%Y-%m-%d %H:%M:%S'
* 获取之前或之后的某个时间(备份)
* date -d "-1 **day**" "+%Y-%m-%d %H:%M:%S"(1天前)
## cal
* 操作日历
* cal(输出当月日历) <=> cal -1
* cal -3(输出上个月下个月本月日历)
* cal -y 年份(输出某年日历)
## 管道
* 管道符|
* 过滤 ls / |grep ye(过滤输出文档名称含"ye"的文件)
* ls (路径) | wc -l(统计文件数)
# 高级操作
## hostname
* 操作主机名((读取，临时设置)
* hostname 输出完整主机名
* hostname -f 输出主机名中的FQDN(全限定域名)
## id
* 查看用户基本信息(用户id，组id，附加组id等等)
* 用户信息/ect/passwd
* 组信息/etc/group
## whoami
* 我是谁(一般用于shell脚本)
## ps -ef
* 用于查看服务器的进程信息
* -e <=> -A: 表示列出全部进程
* -f: 显示全部的字段
* 字段标题：
  - UID：该进程执行的用户ID
  - PID：进程ID
  - PPID：该进程的父级进程ID(如果找不到一个程序的PPID，称该进程为僵尸进程，是无效的)
  - C：CPU占用率(%)
  - STIME：进程启动时间
  - TTY：终端设备：发起该进程的设备识别符号，“？”表示该进程不是由终端发起的
  - TIME：进程的执行时间
  - CMD：该进程的名称或路径
* ps -ef | grep gnome-panel(显示一个表示没有，因为ps也表示一个进程，该进程即为该命令)
## top
* 查看服务器进程占的资源(动态显示)
* 退出按q
* 字段名称：
    - PID：进程ID
    - USER：进程对应用户
    - PR：优先级
    - VIRT(虚拟内存)：申请500MB内存，实际使用320MB，此时的VIRT为500MB
    - RES(常驻内存)：申请500MB内存，实际使用320MB，此时RES为320MB
    - SHR(共享内存)：申请500MB内存，实际使用320MB，其中还包含对其他进程的调用，则需要扣除该共享内存
    > 计算一个进程的实际使用内存 = (RES) - (SHR)
    - **S：表示进行的状态(sleeping,S表示睡眠，R表示运行)**
    - **%CPU：CPU占用百分比**
    - **%MEM：内存占用百分比**
    - TIME+：执行时间
    - **COMMAND：进程的名称或路径**
* 运行top快捷键：
   - **M：内存从大到小排序**
   - **P：CPU从大到小排列**
   - 1：显示多个CPU
## du -sh
* 查看目录的真实大小
* 选项含义
    - \-s:只显示汇总的大小
    - \-h:表示以较高可读性的形式显示
* du -sh (路径)
## find
* 查找文件
* find (路径范围) \[选项\] \[选项的值\]
* 选项:
    - \-name:按照文档名称进行搜索(支持模糊搜索)
    - \-type:按照文档类型进行搜索
        - 文档类型："\-"表示文件，find时用f替换，“d“表示文件夹
## service
* 控制一些软件服务的启动、停止、重启
* service 服务名 start/stop/restart
## kill
* 杀死进程
* kill 进程PID (配合ps一起使用)
* killall 进程名称
## ifconfig
* 操作网卡
## reboot
* 重启
* reboot -w(模拟重启，不重启)
## uptime
* 输出计算机持续在线时间(从开机以来到现在运行的时间)
* uptime
## uname
* 获取计算机相关信息
* uname (获取操作系统的类型)
* uname -a (all:表示获取全部系统信息，包括：类型，全部主机名，内核版本，发布时间，开源计划)
## netstat -tnlp
* 查看网络连接状态
* netstat -tnlp
    - \-t：表示列出tcp协议的连接
    - \-n：表示将地址从字母组合转化成IP地址，将协议转化成端口号来表示
    - \-l：表示只显示”state(状态)“列中其值为LISTEN(监听)的连接
    - \-p：显示发起连接的进程PID和名称

## 如何获取帮助文件
### man
* 手册(manual,包含Linux中全部命令的手册)
* man (命令)
* man 代号
  * 1：shell环境中可操作的命令与执行文件
  * 5：配置文件或某些文件的格式
  * 8：系统管理员可用管理命令
* ``man -f man``用来查询跟``man``相关的说明文件(有代号)
* ``man -k 命令、文件``为关键字(apropos)查询
> apropos用关键字查询手册
* ``whatis`` <==> ``man -f``
* ``apropos`` <==> ``man -k``
### info
* 有点像tree
* ``Tab``切换节点，``Enter``进入节点
* ``p``上一节点，``n``下一节点
### ``/usr/share/doc``
* 文档

## 快捷键
* ctrl+u：删除光标前
* ctrl+k：删除光标后
* wc -l /etc/passwd(统计当前系统共几个用户)
* cd：直接返回当前账户家目录
## sudo
* super user do
#### apt-get
* sudo apt-get install *** 安装
* sudo apt-get remove *** 卸载
* sudo apt-get update 更新


# 9.7
## 关机重启相关
### ``sync``

* 将内存中尚未更新的数据写入磁盘

##　shutdown
* 关机　(服务器慎用)
* shutdown -h now "关机提示"或 shutdown -h 15:25 ”关机提示“
* -c    关机取消
* -r    重启
* -k    “只发送消息，不关机”

# 9.13
## 切换登录界面（GDM）背景

[知乎链接](https://zhuanlan.zhihu.com/p/51112469)

* 需要修改``/usr/share/gnome-shell/theme/ubuntu.css``文件中的``lockDialogGroup``
* 将``resources:///...``改为``file:///...``

> 桌面背景默认放置路径为``/usr/share/backgrounds``


## 重新使用grub引导程序

1. 将``/etc/default/grub``中的``GRUB_TIMEOUT_STYLE=hidden``注释掉
2. 添加windows启动项
   1.  ``sudo grub-install /dev/sda1``，sda1是``Microsoft basic data``
   2.  ``cd /etc/grub.d``
   3.  ``sudo gedit 40_custom``
   4.  其中编辑如下
```
menuentry "Windows 10"{
    set root='(hd0,1)'
    chainloader (${root})/EFI/Microsoft/Boot/bootmgfw.efi
}
```
* 成功


## 修改文件与文件夹属性与权限

1.  修改所属用户组
    1.  ``chgrp``(change group)
    2.  组名要在``/etc/group``下有存储
    3.  使用案例``chgrp users test.txt``
    4.  ``-R``选项直接修改文件夹的所有文件的所属用户组
    5.  ``chgrp [-R] file/dir``
2. 修改文件拥有者
   1. ``chown``(change owner)
   2. owner要在``/etc/passwd``下有存储
   3. 顺便修改所属用户组
   4. ``-R``类似
   5. 方法``chown [-R] user[:group] file/dir``
   6. 案例``chown root:root test.txt``,冒号后面的为group
3. ``cp``会复制执行者的属性和权限
4. 修改权限
   1. ``chmod``
   2. 数字修改法
      1. 各权限对应数字
         1. ``r-4``
         2. ``w-2``
         3. ``x-1``
      2. 三种身份（owner，group，others）拥有权限为数字之和
      3. 使用方法``chmod [-R] xyz file/dir``
   3. vim编辑shell脚本，要运行，其他人不可修改``chmod 755 test.sh``
      1. 7:rwx
      2. 5:r-x
   4. 符号修改法
      1. 字母符号代表的意思
         1. ``u`` <=> user
         2. ``g`` <=> group
         3. ``o`` <=> others
         4. ``a`` <=> all
         5. ``+`` 加入权限
         6. ``-`` 删除权限
         7. ``=`` 设置权限
      2. 案例``chmod u=rwx,go=rx .bashrc``
      3. 案例``chmod a+w .bashrc``
5. ``rwx``对于文件与文件夹
   1. 文件
      1. ``r`` <=> ``read``
      2. ``w`` <=> ``write``
      3. ``x`` <=> ``execute``
   2. 文件夹
      1. ``r`` <=> ``read contents in dir``
      2. ``w`` <=> ``modify contents in dir``
      3. ``x`` <=> ``access dir``

## 查看Ubuntu版本

* ``lsb_release -a``