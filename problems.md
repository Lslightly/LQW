#### settings(gnome-control-center)在按到``Details``消失(solved)

暂行解决方法：``StackOverFlow``

```
dconf reset -f /org/gnome/control-center/
```

> 恢复后按``Detail``仍然会炸，原因未知
> 解决方法原因未知，应该是重置的意思

### 9.13

#### GDM界面混乱(unsolved)

在刚开机时进入的GDM界面，按下enter键输入密码时，原来的背景不消失，而且触碰其他地方展示出下拉栏之后，取消展示下拉栏，下拉栏仍然会保留，相当于点哪里哪里出现东西之后不会消失

#### 从aliyun源切换会ustc源之后会有package超前，``sudo apt upgrade``会显示``package broken``(solved)

* 解决方法：切换会aliyun源，更新

#### D盘在升级file之后无法查找(solved)

* 解决方法：挂载D盘并设置开机自动挂载
  * [方法网址](https://blog.csdn.net/qq_35451572/article/details/79541106)