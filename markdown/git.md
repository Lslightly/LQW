[git教程](https://www.liaoxuefeng.com/wiki/896043488029600)
Git是分布式版本控制系统
1. mkdir \<仓库名>
2. cd learngit
3. git init
> 创建版本库
4. git add \<file>
> 将文件添加到仓库中(文件一定要先放在仓库下)
5. git commit -m \<message>
> \-m表示本次提交的说明，commit可以一次提交很多文件
6. git status
> 仓库当前的状态
7. git diff
> 查看difference
8. git log
> 显示从最近到最远的提交日志
9. git log --pretty=oneline
> 显示结果中前面一大串为commit id
10. git reset --hard HEAD^
> 回退到上一个版本
11. git reset --hard \<版本号前几位>
> 穿越到未来的版本，前提知道版本号，若将命令行关闭，有下面的解决方法
12. git reflog
> Git提供了一个命令git reflog用来记录你的每一次命令
13. git diff HEAD -- \<file>
> 比较工作区和版本库里面最新版本的区别
14. git checkout -- \<file>
> 一种是readme.txt自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态(恢复到最新版本)；本质上是用版本库的版本替换工作区的版本。
> 
> 一种是readme.txt已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。
>
> --很重要
15. git reset HEAD \<file>
> 把暂存区的修改撤销掉（unstage），重新放回工作区,用HEAD表示最新的版本。
16. git rm \<file>
> 将版本库的文件删除
17. ssh-keygen -t rsa -C "youremail@example.com"
> 在用户主目录下创建.ssh目录
18. git remote add origin \<ssh>
> 关联库
19. git push -u origin master
> 推送，加上-u以后简化命令
20. git remote -v
> 查看当前关联库
21. git remote set-url origin \<ssh>
> 切换关联远程库


工作区(Working Directory)：电脑能看到的目录

版本库(Repository)：隐藏目录.git

.git中有stage(暂存区)，master(分支)，head(指向master的指针)

Git跟踪管理的是修改，而非文件
