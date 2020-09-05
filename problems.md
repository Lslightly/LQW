#### settings(gnome-control-center)在按到``Details``消失

暂行解决方法：``StackOverFlow``

```
dconf reset -f /org/gnome/control-center/
```

> 恢复后按``Detail``仍然会炸，原因未知
> 解决方法原因未知，应该是重置的意思