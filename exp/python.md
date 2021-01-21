# 函数
## 函数参数
在Python中定义函数，可以用必选参数、默认参数、可变参数、关键字参数和命名关键字参数，这5种参数都可以组合使用。但是请注意，参数定义的顺序必须是：必选参数、默认参数、可变参数、命名关键字参数和关键字参数。
## 递归
* ***解决递归调用栈溢出的方法是通过尾递归优化***，事实上尾递归和循环的效果是一样的，所以，把循环看成是一种特殊的尾递归函数也是可以的。
* 尾递归是指，在函数返回的时候，***调用自身本身，并且，return语句不能包含表达式***。这样，编译器或者解释器就可以把尾递归做优化，使递归本身无论调用多少次，都只占用***一个栈帧***，不会出现栈溢出的情况
> 遗憾的是：Python标准的解释器没有针对尾递归做优化，任何递归函数都存在栈溢出的问题。

# 高级特性
## 切片
* tuple是一种“不变的list”，可做切片操作
```python
L = ['Micheal', 'Mike', 'Jane']
# L[x:y:step] 从x到y(不包括y)的元素,step表示步长
# x不存在表示从0开始
# y不存在表示到-1为止,包括-1
print(L[:3])  # 从索引0开始不包含索引3
print(L[-2:-1])  # 不包括-1
print(L[-2:])
print(L[::2])
print((0, 1, 2, 3, 4, 5, 6)[:3])
print('THREELWLQO'[-9::2])

```
## 迭代
* 只要是可迭代对象，无论有无下标，都可以迭代，比如dict、list、tuple
* 默认情况下，dict迭代的是key。如果要迭代value，可以用*for value in d.values()*，如果要同时迭代key和value，可以用*for k, v in d.items()* 。
```python
for i in [1, 2, 3]:
    print(i, end="")
print()
for i in (1, 2, 3, 4):
    print(i, end="")
print()
for i in {'a': 1, 'b': 2, 'c': 3}:
    print(i, end="")
print()
for i in {'a': 1, 'b': 2, 'c': 3}.values():
    print(i, end="")
print()
for i, j in {'a': 1, 'b': 2, 'c': 3}.items():
    print(i, j, end=" ")
print()
for i in 'ABC':
    print(i, end="")
print()
# 判断是否为可迭代对象
# 方法是通过collections模块的Iterable类型判断：
from collections import Iterable

print(isinstance('abc', Iterable))
print(isinstance([1, 2, 3], Iterable))
print(isinstance(123, Iterable))

# 迭代索引和元素本身
for i, value in enumerate(['A', 'B', 'C']):
    print(i, value)
```
## 列表生成式
* range(1, 11)表示[1, 11)整数
* list(range(1, 11))生成1~10整数列表
```python
# 生成1~10整数
L = list(range(1, 11))
print(L)

# 生成x^2
L = [x * x for x in range(1, 11)]
print(L)

# 生成偶数x^2
L = [x * x for x in range(1, 11) if x % 2 == 0]
print(L)

# 两重循环
L = [m + n for m in 'ABC' for n in 'XYZ']
print(L)

# 当前目录下所有文件与目录名
import os

L = [d for d in os.listdir('.')]
print(L)

# 使用两个变量来生成list
d = {'x': 'A', 'y': 'B', 'z': 'C'}
L = [k + '=' + v for k, v in d.items()]
print(L)

# 变小写
L = ['Hello', 'World', 'IBM', 'Apple']
L = [s.lower() for s in L]
print(L)
```
## 生成器generator
* 我们创建了一个generator后，基本上永远不会调用next()，而是通过***for循环***来迭代它，并且不需要关心StopIteration的错误。
* 如果一个函数定义中包含***yield***关键字，那么这个函数就不再是一个普通函数，而是一个generator
* 变成generator的函数，在每次调用next()的时候执行，***遇到yield语句返回***，再次执行时从上次返回的yield语句处继续执行。
```python
# next()函数获取下一个返回值


# Fibonacci数列生成器定义
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b     # 对应赋值
        n = n + 1
    return 'done'


# 0~9平方数生成器
g = (x * x for x in range(10))
print(g)
for i in g:
    print(i)
for n in fib(6):
    print(n)

```
```python
# https://www.liaoxuefeng.com/wiki/1016959663602400/1017318207388128
def triangles():
    l = [1]
    while 1:
        yield l
        l.append(0)
        for i in range(0, len(l) - 1):
            l[len(l) - 1 - i] = l[len(l) - i - 1] + l[len(l) - i - 2]


n = 0
results = []
for t in triangles():
    print(t)
    results.append(t)  # 这里不是应该将t加在results末尾吗？为什么会是复制
    print(results)
    n = n + 1
    if n == 10:
        break

if results == [
    [1],
    [1, 1],
    [1, 2, 1],
    [1, 3, 3, 1],
    [1, 4, 6, 4, 1],
    [1, 5, 10, 10, 5, 1],
    [1, 6, 15, 20, 15, 6, 1],
    [1, 7, 21, 35, 35, 21, 7, 1],
    [1, 8, 28, 56, 70, 56, 28, 8, 1],
    [1, 9, 36, 84, 126, 126, 84, 36, 9, 1]
]:
    print('测试通过!')
else:
    print('测试失败!')
```
> 此题为一道测试题(~~谁不知道这是一道测试题啊。。。~~),测试你对某坑(~~非cwk~~)的掌握程度
> 
> list作为一个非常基础的知识，却有一个非常巨大的坑，在将lista添加到listb中时，改变lista的值，你会得到一个新的listb(~~谁不知道呢~~)，再将lista添加到这个listb中，你会得到listb中有两个lista的值(~~这有什么好奇怪的~~)，然后改变lista的值，打印listb。。。等。。。等。。。等。。。等。。。。。。！！！listb的两个值都变成了修改后的lista的值！！！

##### Want to learn more? Click the button here.

[~~深拷贝与浅拷贝~~](https://blog.csdn.net/sctec/article/details/84976288)~~**No, you can't.**~~

> 切片为浅拷贝
```python
a = [1, 2, [3, 4]]
b = a[:]
print(a is b)
a[2][0] = 'hey'
print(a)
print(b)

# 结果
# False
# [1, 2, ['hey', 4]]
# [1, 2, ['hey', 4]]
```
