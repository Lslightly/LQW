# https://www.liaoxuefeng.com/wiki/1016959663602400/1017318207388128
# -*- coding: utf-8 -*-
def triangles():
    l = [1]
    while 1:
        yield l[:]
        l.append(0)
        for i in range(0, len(l) - 1):
            l[len(l) - 1 - i] = l[len(l) - i - 1] + l[len(l) - i - 2]


n = 0
results = []
for t in triangles():
    results.append(t)  # 这里不是应该将t加在results末尾吗？为什么会是复制
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
