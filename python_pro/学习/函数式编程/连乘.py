# https://www.liaoxuefeng.com/wiki/1016959663602400/1017329367486080
from functools import reduce


def prod(L):
    def pai(x, y):
        return x * y

    return reduce(pai, L)


print('3 * 5 * 7 * 9 =', prod([3, 5, 7, 9]))
if prod([3, 5, 7, 9]) == 945:
    print('测试成功!')
else:
    print('测试失败!')