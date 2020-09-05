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
