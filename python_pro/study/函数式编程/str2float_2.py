# -*- coding: utf-8 -*-
from functools import reduce


def str2float(s):
    def change(s):
        if s == '.':
            return s
        else:
            return int(s)

    L = list(map(change, s))

    key = 0
    for i in range(0, len(L)):
        if (isinstance(L[i], str)):
            key = i

    L1 = L[:key]
    L2 = L[key+1:]

    def left_to_float(x, y):
        return 10*x+y

    def right_to_float(x, y):
        return x*0.1 + y 

    
    L2.reverse()
    return reduce(left_to_float, L1) + reduce(right_to_float, L2) / 10


print('str2float(\'123.456\') =', str2float('123.456'))
if abs(str2float('123.456') - 123.456) < 0.00001:
    print('测试成功!')
else:
    print('测试失败!')
