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
