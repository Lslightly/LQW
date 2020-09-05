# https://www.liaoxuefeng.com/wiki/1016959663602400/1017329367486080
from functools import reduce

DIGIT = {'1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '0': 0, '.': '.'}


def str2float(s):
    def spilt1(s):
        return DIGIT[s]

    def ls2float1(x, y):
        return 10 * x + y

    def ls2float2(x, y):
        return x * 0.1 + y

    L = list(map(spilt1, s))
    for i in L:
        if isinstance(L[i], str):
            key = i
            break
    L1 = L[key + 1:]
    L1.reverse()
    return reduce(ls2float1, L[:key]) + reduce(ls2float2, L1) / 10


print('str2float(\'123.456\') =', str2float('123.456'))
if abs(str2float('123.456') - 123.456) < 0.00001:
    print('测试成功!')
else:
    print('测试失败!')
